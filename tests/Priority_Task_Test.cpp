// $Id$

// ============================================================================
//
// = LIBRARY
//    tests
// 
// = FILENAME
//    Priority_Task_Test.cpp
//
// = DESCRIPTION
//      This is a simple test to illustrate the priority mechanism of
//      ACE Tasks.  
//
// = AUTHOR
//    Doug Schmidt
// 
// ============================================================================

#include "ace/Service_Config.h"
#include "ace/Task.h"
#include "ace/Sched_Params.h"
#include "test_config.h"

#if defined (ACE_HAS_THREADS)

class Priority_Task : public ACE_Task<ACE_MT_SYNCH>
{
public:
  Priority_Task (void);

  int open (void *);
  int svc (void);

private:
  int priority_;
};

Priority_Task::Priority_Task (void)
  : ACE_Task<ACE_MT_SYNCH> (ACE_Service_Config::thr_mgr ()),
    priority_ (0)
{
}

int
Priority_Task::open (void *arg)
{
  this->priority_ = *(int *) arg;

  long flags = THR_NEW_LWP;
#if defined (THR_SCHED_FIFO)
  // To get FIFO scheduling with PTHREADS.  Instead of doing this,
  // OS.h should be fixed to defined THR_SCHED_FIFO on non-PTHREADS
  // platforms, such as Solaris with STHREADS and without PTHREADS.
  flags |= THR_SCHED_FIFO;
#endif /* THR_SCHED_FIFO */

  // Become an active object.
  if (this->activate (flags, 1, 0, this->priority_) == -1)
    {
      // On Linux, only the superuser can set the policy to other
      // than ACE_SCHED_OTHER.  But with ACE_SCHED_OTHER, there is
      // only 1 thread priority value, 0.  So, let the superuser
      // run an interesting test, but for other users use priority 0.

      ACE_DEBUG ((LM_DEBUG, "(%t) task activation at priority %d with flags "
                            "%ld failed; retry at priority 0 with with flags "
                            "%ld\n",
                  this->priority_, flags, THR_NEW_LWP));

      flags = THR_NEW_LWP;
      this->priority_ = 0;

      if (this->activate (flags, 1, 1, this->priority_) == -1)
        {
          ACE_DEBUG ((LM_ERROR, "(%t) task activation at priority 0 failed, exiting!\n%a", -1));
        }
    }

  return 0;
}

int
Priority_Task::svc (void)
{
  // Set up logging for this thread.
  ACE_NEW_THREAD;

  ACE_hthread_t thr_handle;
  ACE_Thread::self (thr_handle);
  int prio;

  if (ACE_Thread::getprio (thr_handle, prio) == -1)
    ACE_ERROR_RETURN ((LM_ERROR, "%p\n", "getprio failed"), -1);

  ACE_DEBUG ((LM_DEBUG, "(%t) prio = %d, priority_ = %d\n", 
	      prio, this->priority_));
  ACE_ASSERT (this->priority_ == prio);
  return 0;
}

#endif /* ACE_HAS_THREADS */

int 
main (int, char *[])
{
  ACE_START_TEST ("Priority_Task_Test");

#if defined (ACE_HAS_THREADS)

  Priority_Task tasks[ACE_MAX_ITERATIONS];

  int i;

  // Spawn off ACE_MAX_ITERATIONS of tasks, passing each one their
  // iteration number as their priority.

  // NOTE:  on Solaris, for example, this requests the min FIFO
  // priority.  But, this test doesn't use the Realtime scheduling
  // class.  The FIFO priorities are used because they're all nonnegative.
  int priority = ACE_Sched_Params::priority_min (ACE_SCHED_FIFO,
                                                 ACE_SCOPE_THREAD);

  for (i = 0; i < ACE_MAX_ITERATIONS; i++)
    {
      tasks[i].open ((void *) &priority);
      priority = ACE_Sched_Params::next_priority (ACE_SCHED_FIFO,
                                                  priority,
                                                  ACE_SCOPE_THREAD);
    }

  ACE_DEBUG ((LM_DEBUG, "(%t) %d tasks spawned, wait for them to exit . . .\n",
                        ACE_MAX_ITERATIONS));

  // Wait for all tasks to exit.
  ACE_Service_Config::thr_mgr ()->wait ();

#else
  ACE_ERROR ((LM_ERROR, "threads not supported on this platform\n"));
#endif /* ACE_HAS_THREADS */
  ACE_END_TEST;
  return 0;
}
