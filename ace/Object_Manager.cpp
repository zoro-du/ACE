// $Id$

#define ACE_BUILD_DLL

#include "ace/Object_Manager.h"
#include "ace/Containers.h"
#include "ace/Service_Repository.h"
#include "ace/Log_Msg.h"
#include "ace/Synch.h"

#if !defined (__ACE_INLINE__)
#include "ace/Object_Manager.i"
#endif /* __ACE_INLINE__ */

// Singleton pointer.
ACE_Object_Manager *ACE_Object_Manager::instance_ = 0;

ACE_Object_Manager::ACE_Object_Manager (void)
  : shutting_down_(0)
{
  ACE_NEW (registered_objects_, ACE_Unbounded_Queue<ACE_Cleanup_Info>);

  ACE_MT (ACE_NEW (lock_, ACE_Thread_Mutex));

#if defined (ACE_HAS_NONSTATIC_OBJECT_MANAGER)
  // Store the address of this static instance so that instance ()
  // doesn't allocate a new one when called.
  instance_ = this;
#endif /* ACE_HAS_NONSTATIC_OBJECT_MANAGER */

#if defined (ACE_HAS_TSS_EMULATION)
  // Initialize the main thread's TS storage.
  ACE_TSS_Emulation::tss_open (ts_storage_);
#endif /* ACE_HAS_TSS_EMULATION */
}

ACE_Object_Manager::~ACE_Object_Manager (void)
{
  // Acquire the mutex here.  This should be called from the main
  // thread.  Any other threads that attempt to acquire the mutex will
  // block.  They should be killed when the Thread_Manager is
  // destroyed, below; so they should never proceed beyond that.
  ACE_MT (ACE_GUARD (ACE_Thread_Mutex, ace_mon, *lock_));

  ACE_Cleanup_Info info;

  // Call all registered cleanup hooks, in reverse order of
  // registration.  Before starting, mark this object as being
  // destroyed - then if during the course of shutting things down,
  // some object tries to register, it won't be.
  shutting_down_ = 1;
  ACE_Trace::stop_tracing ();
  while (registered_objects_ &&
         registered_objects_->dequeue_head (info) != -1)
    {
      if (info.cleanup_hook_ == (ACE_CLEANUP_FUNC) ace_cleanup_destroyer)
        {
          //
          ace_cleanup_destroyer ((ACE_Cleanup *) info.object_, info.param_);
        }
      else
        {
          (*info.cleanup_hook_) (info.object_, info.param_);
        }
    }

  // This call closes and deletes all ACE library services and
  // singletons.  This closes the ACE_Thread_Manager, which cleans
  // up all running threads.
  ACE_Service_Config::close ();

  // Close the main thread's TSS, including its Log_Msg instance.
  ACE_OS::cleanup_tss ();

  ACE_MT (delete lock_;  lock_ = 0);

  delete registered_objects_;
  registered_objects_ = 0;

  // Close the ACE_Allocator.
  ACE_Allocator::close_singleton ();

# if defined (ACE_HAS_THREADS)
  // Close the ACE_Allocator and ACE_Static_Object_Lock.
  ACE_Static_Object_Lock::close_singleton ();
# endif /* ACE_HAS_THREADS */

#if defined (ACE_HAS_TSS_EMULATION)
  // Close the thread's local TS storage.
  ACE_TSS_Emulation::tss_close (ts_storage_);
#endif /* ACE_HAS_TSS_EMULATION */
}

ACE_Object_Manager *
ACE_Object_Manager::instance (void)
{
  // This function should be call during construction of static
  // instances, so it's not thread safe.

  if (instance_ == 0)
    ACE_NEW_RETURN (instance_, ACE_Object_Manager, 0);

  return instance_;
}

int
ACE_Object_Manager::at_exit_i (void *object,
                               ACE_CLEANUP_FUNC cleanup_hook,
                               void *param)
{
  ACE_MT (ACE_GUARD_RETURN (ACE_Thread_Mutex, ace_mon, *lock_, -1));

  if (shutting_down_)
    {
      errno = EAGAIN;
      return -1;
    }

  // Check for already in queue, and return 1 if so.
  ACE_Cleanup_Info *info = 0;
  for (ACE_Unbounded_Queue_Iterator<ACE_Cleanup_Info> iter (*registered_objects_);
       iter.next (info) != 0;
       iter.advance ())
    {
      if (info->object_ == object)
        {
          // The object has already been registered.
          errno = EEXIST;
          return -1;
        }
    }

  ACE_Cleanup_Info new_info;
  new_info.object_ = object;
  new_info.cleanup_hook_ = cleanup_hook;
  new_info.param_ = param;

  // Returns -1 and sets errno if unable to allocate storage.  Enqueue
  // at the head and dequeue from the head to get LIFO ordering.
  return registered_objects_->enqueue_head (new_info);
}

void *ACE_Object_Manager::managed_object[ACE_MAX_MANAGED_OBJECTS] = { 0 };

u_int ACE_Object_Manager::next_managed_object = 0;

template <class TYPE>
int
ACE_Managed_Object<TYPE>::get_object (u_int &id, TYPE *&object)
{
  // Use the ACE_Object_Manager instance's lock.
  ACE_MT (ACE_Thread_Mutex &lock = *ACE_Object_Manager::instance ()->lock_);
  ACE_MT (ACE_GUARD_RETURN (ACE_Thread_Mutex, ace_mon, lock, -1));

  if (id == 0)
    {
      // User is requesting a new object.
      if (ACE_Object_Manager::next_managed_object < ACE_MAX_MANAGED_OBJECTS)
        {
          // Allocate a new object, store it in the table, and return it.
          ACE_NEW_RETURN (object, TYPE, -1);
          if (object == 0)
            {
              errno = ENOMEM;
              return -1;
            }
          else
            {
              ACE_Object_Manager::managed_object[
                ACE_Object_Manager::next_managed_object++] = object;
              return 0;
            }
        }
      else
        {
          // No more managed_object table slots.
          object = 0;
          errno = ENOSPC;
          return -1;
        }
    }
  else if (id >= ACE_Object_Manager::next_managed_object)
    {
      // Unknown, non-zero id.
      object = 0;
      errno = ENOENT;
      return -1;
    }
  else
    {
      // id is known, so return the object.  Cast its type based
      // on the type of the function template parameter.
      object = (TYPE *) ACE_Object_Manager::managed_object[id];
      return 0;
    }
}

template <class TYPE>
TYPE *
ACE_Managed_Object<TYPE>::get_object (u_int &id)
{
  // Use the ACE_Object_Manager instance's lock.
  ACE_MT (ACE_Thread_Mutex &lock = *ACE_Object_Manager::instance ()->lock_);
  ACE_MT (ACE_GUARD_RETURN (ACE_Thread_Mutex, ace_mon, lock, 0));

  if (id == 0 || id >= ACE_Object_Manager::next_managed_object)
    {
      return 0;
    }
  else
    {
      // id is known, so return the object.  Cast its type based
      // on the type of the function template parameter.
      return (TYPE *) ACE_Object_Manager::managed_object[id];
    }
}

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)
# if defined (ACE_MT_SAFE) && (ACE_MT_SAFE != 0)
    template class ACE_Managed_Object <ACE_Thread_Mutex>;
# endif /* ACE_MT_SAFE */
template class ACE_Unbounded_Queue<ACE_Cleanup_Info>;
template class ACE_Unbounded_Queue_Iterator<ACE_Cleanup_Info>;
template class ACE_Node<ACE_Cleanup_Info>;
#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)
# if defined (ACE_MT_SAFE) && (ACE_MT_SAFE != 0)
#   pragma instantiate ACE_Managed_Object <ACE_Thread_Mutex>
# endif /* ACE_MT_SAFE */
#pragma instantiate ACE_Unbounded_Queue<ACE_Cleanup_Info>
#pragma instantiate ACE_Unbounded_Queue_Iterator<ACE_Cleanup_Info>
#pragma instantiate ACE_Node<ACE_Cleanup_Info>
#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */
