// ******  Code generated by the The ACE ORB (TAO) IDL Compiler *******
// TAO ORB and the TAO IDL Compiler have been developed by Washington 
// University Computer Science's Distributed Object Computing Group.
//
// Information on TAO is available at
//                 http://www.cs.wustl.edu/~schmidt/TAO.html

#if !defined (_TAO_IDL_RTECEVENTCOMMC_H_)
#define _TAO_IDL_RTECEVENTCOMMC_H_

#include "tao/corba.h"

class RtecEventComm{
public:
  
#if !defined (_RTECEVENTCOMM_DISCONNECTED___PTR_CH_)
#define _RTECEVENTCOMM_DISCONNECTED___PTR_CH_

  class Disconnected;
  typedef Disconnected *Disconnected_ptr;
  
#endif // end #if !defined


#if !defined (_RTECEVENTCOMM_DISCONNECTED_CH_)
#define _RTECEVENTCOMM_DISCONNECTED_CH_

  class Disconnected : public virtual CORBA::UserException
  {
  public:
      Disconnected (void);
  };
  
  
#endif // end #if !defined

static CORBA::TypeCode_ptr _tc_Disconnected;

  struct EventData
  {
    CORBA::Long x;

    CORBA::Long y;

  };

  class EventData_var
  {
  public:
    EventData_var (void); // default constructor
    EventData_var (EventData *);
    EventData_var (const EventData_var &); // copy constructor
    ~EventData_var (void); // destructor
    
    EventData_var &operator= (EventData *);
    EventData_var &operator= (const EventData_var &);
    EventData *operator-> (void);
    const EventData *operator-> (void) const;
    
    operator const EventData &() const;
    operator EventData &();
    operator EventData &() const;
    // in, inout, out, _retn 
    const EventData &in (void) const;
    EventData &inout (void);
    EventData &out (void);
    EventData _retn (void);
    EventData *ptr(void) const;

  private:
    EventData *ptr_;
  };

  typedef EventData &EventData_out;

  static CORBA::TypeCode_ptr _tc_EventData;

  typedef CORBA::Long EventSourceID;typedef CORBA::Long_out EventSourceID_out;

  static CORBA::TypeCode_ptr _tc_EventSourceID;

  typedef CORBA::Long Time;typedef CORBA::Long_out Time_out;

  static CORBA::TypeCode_ptr _tc_Time;

  typedef CORBA::Long EventType;typedef CORBA::Long_out EventType_out;

  static CORBA::TypeCode_ptr _tc_EventType;

  struct Event
  {
    ACE_NESTED_CLASS (RtecEventComm,EventSourceID) source_;

    ACE_NESTED_CLASS (RtecEventComm,EventType) type_;

    ACE_NESTED_CLASS (RtecEventComm,Time) time_;

    ACE_NESTED_CLASS (RtecEventComm,EventData) data_;

  };

  class Event_var
  {
  public:
    Event_var (void); // default constructor
    Event_var (Event *);
    Event_var (const Event_var &); // copy constructor
    ~Event_var (void); // destructor
    
    Event_var &operator= (Event *);
    Event_var &operator= (const Event_var &);
    Event *operator-> (void);
    const Event *operator-> (void) const;
    
    operator const Event &() const;
    operator Event &();
    operator Event &() const;
    // in, inout, out, _retn 
    const Event &in (void) const;
    Event &inout (void);
    Event &out (void);
    Event _retn (void);
    Event *ptr(void) const;

  private:
    Event *ptr_;
  };

  typedef Event &Event_out;

  static CORBA::TypeCode_ptr _tc_Event;


#if !defined (_RTECEVENTCOMM__TAO__SEQ_EVENTSET_CH_)
#define _RTECEVENTCOMM__TAO__SEQ_EVENTSET_CH_

  // *************************************************************
  // class _tao__seq_EventSet
  // *************************************************************
  
  class _tao__seq_EventSet
  {
  public:
    _tao__seq_EventSet (void); // default constructor
    _tao__seq_EventSet (CORBA::ULong max);
    _tao__seq_EventSet (CORBA::ULong max, CORBA::ULong length, 
    	ACE_NESTED_CLASS (RtecEventComm,Event) *value, CORBA::Boolean release=CORBA::B_FALSE);
    _tao__seq_EventSet(const _tao__seq_EventSet &); // copy constructor
    ~_tao__seq_EventSet (void);
    _tao__seq_EventSet &operator= (const _tao__seq_EventSet &);
    CORBA::ULong maximum (void) const;
    void length (CORBA::ULong);
    CORBA::ULong length (void) const;
    ACE_NESTED_CLASS (RtecEventComm,Event) &operator[] (CORBA::ULong index);
    const ACE_NESTED_CLASS (RtecEventComm,Event) &operator[] (CORBA::ULong index) const;
    static ACE_NESTED_CLASS (RtecEventComm,Event) *allocbuf (CORBA::ULong nelems);
    static void freebuf (ACE_NESTED_CLASS (RtecEventComm,Event) *);
  private:
    CORBA::ULong maximum_;
    CORBA::ULong length_;
    ACE_NESTED_CLASS (RtecEventComm,Event) *buffer_;
    CORBA::Boolean release_;
  };
  typedef _tao__seq_EventSet* _tao__seq_EventSet_ptr;
  static CORBA::TypeCode_ptr _tc__tao__seq_EventSet;


#endif // end #if !defined


#if !defined (_RTECEVENTCOMM__TAO__SEQ_EVENTSET___VAR_CH_)
#define _RTECEVENTCOMM__TAO__SEQ_EVENTSET___VAR_CH_

// *************************************************************
  // class RtecEventComm::_tao__seq_EventSet_var
  // *************************************************************

  class _tao__seq_EventSet_var
  {
  public:
    _tao__seq_EventSet_var (void); // default constructor
    _tao__seq_EventSet_var (_tao__seq_EventSet *);
    _tao__seq_EventSet_var (const _tao__seq_EventSet_var &); // copy constructor
    ~_tao__seq_EventSet_var (void); // destructor
    
    _tao__seq_EventSet_var &operator= (_tao__seq_EventSet *);
    _tao__seq_EventSet_var &operator= (const _tao__seq_EventSet_var &);
    _tao__seq_EventSet *operator-> (void);
    const _tao__seq_EventSet *operator-> (void) const;
    
    operator const _tao__seq_EventSet &() const;
    operator _tao__seq_EventSet &();
    operator _tao__seq_EventSet &() const;
    ACE_NESTED_CLASS (RtecEventComm,Event) &operator[] (CORBA::ULong index);
    // in, inout, out, _retn 
    const _tao__seq_EventSet &in (void) const;
    _tao__seq_EventSet &inout (void);
    _tao__seq_EventSet *&out (void);
    _tao__seq_EventSet *_retn (void);
    _tao__seq_EventSet *ptr (void) const;

  private:
    _tao__seq_EventSet *ptr_;
  };


#endif // end #if !defined


#if !defined (_RTECEVENTCOMM__TAO__SEQ_EVENTSET___OUT_CH_)
#define _RTECEVENTCOMM__TAO__SEQ_EVENTSET___OUT_CH_

  class _tao__seq_EventSet_out
  {
  public:
    _tao__seq_EventSet_out (_tao__seq_EventSet *&);
    _tao__seq_EventSet_out (_tao__seq_EventSet_var &);
    _tao__seq_EventSet_out (_tao__seq_EventSet_out &);
    _tao__seq_EventSet_out &operator= (_tao__seq_EventSet_out &);
    _tao__seq_EventSet_out &operator= (_tao__seq_EventSet *);
    operator _tao__seq_EventSet *&();
    _tao__seq_EventSet *&ptr (void);
    _tao__seq_EventSet *operator-> (void);
    ACE_NESTED_CLASS (RtecEventComm,Event) &operator[] (CORBA::ULong index);
    
  private:
    _tao__seq_EventSet *&ptr_;
    // assignment from T_var not allowed
    void operator= (const _tao__seq_EventSet_var &);
  };


#endif // end #if !defined

  typedef ACE_NESTED_CLASS (RtecEventComm,_tao__seq_EventSet) EventSet;
  typedef ACE_NESTED_CLASS (RtecEventComm,_tao__seq_EventSet_var) EventSet_var;
  typedef ACE_NESTED_CLASS (RtecEventComm,_tao__seq_EventSet_out) EventSet_out;

  static CORBA::TypeCode_ptr _tc_EventSet;

  
#if !defined (_RTECEVENTCOMM_PUSHCONSUMER___PTR_CH_)
#define _RTECEVENTCOMM_PUSHCONSUMER___PTR_CH_

class PushConsumer;
  typedef PushConsumer *PushConsumer_ptr;
  
#endif // end #if !defined


#if !defined (_RTECEVENTCOMM_PUSHCONSUMER_CH_)
#define _RTECEVENTCOMM_PUSHCONSUMER_CH_

class PushConsumer: public virtual ACE_CORBA_1 (Object)
  {
  public:
    // the static operations
    static PushConsumer_ptr _duplicate (PushConsumer_ptr obj);
    static PushConsumer_ptr _narrow (CORBA::Object_ptr obj, CORBA::Environment &env);
    static PushConsumer_ptr _nil (void);
    static PushConsumer_ptr _bind (const char *host, CORBA::UShort port, const char *key, CORBA::Environment &env);

    virtual void push (const ACE_NESTED_CLASS (RtecEventComm,EventSet) &data, CORBA::Environment &env);
    virtual void disconnect_push_consumer (CORBA::Environment &env);
  protected:
    PushConsumer (void); // default constructor
    PushConsumer (STUB_Object *objref);
    virtual ~PushConsumer (void);
  private:
    PushConsumer (const PushConsumer&);
    void operator= (const PushConsumer&);
  };


#endif // end #if !defined


#if !defined (_RTECEVENTCOMM_PUSHCONSUMER___VAR_CH_)
#define _RTECEVENTCOMM_PUSHCONSUMER___VAR_CH_

  class PushConsumer_var
  {
  public:
    PushConsumer_var (void); // default constructor
    PushConsumer_var (PushConsumer_ptr);
    PushConsumer_var (const PushConsumer_var &); // copy constructor
    ~PushConsumer_var (void); // destructor
    
    PushConsumer_var &operator= (PushConsumer_ptr);
    PushConsumer_var &operator= (const PushConsumer_var &);
    PushConsumer_ptr operator-> (void) const;
    
    operator const PushConsumer_ptr &() const;
    operator PushConsumer_ptr &();
    // in, inout, out, _retn 
    PushConsumer_ptr in (void) const;
    PushConsumer_ptr &inout (void);
    PushConsumer_ptr &out (void);
    PushConsumer_ptr _retn (void);
    PushConsumer_ptr ptr (void) const;

  private:
    PushConsumer_ptr ptr_;
  };


#endif // end #if !defined


#if !defined (_RTECEVENTCOMM_PUSHCONSUMER___OUT_CH_)
#define _RTECEVENTCOMM_PUSHCONSUMER___OUT_CH_

  class PushConsumer_out
  {
  public:
    PushConsumer_out (PushConsumer_ptr &);
    PushConsumer_out (PushConsumer_var &);
    PushConsumer_out (PushConsumer_out &);
    PushConsumer_out &operator= (PushConsumer_out &);
    PushConsumer_out &operator= (const PushConsumer_var &);
    PushConsumer_out &operator= (PushConsumer_ptr);
    operator PushConsumer_ptr &();
    PushConsumer_ptr &ptr (void);
    PushConsumer_ptr operator-> (void);
    
  private:
    PushConsumer_ptr &ptr_;
  };


#endif // end #if !defined

  static CORBA::TypeCode_ptr _tc_PushConsumer;

  
#if !defined (_RTECEVENTCOMM_PUSHSUPPLIER___PTR_CH_)
#define _RTECEVENTCOMM_PUSHSUPPLIER___PTR_CH_

class PushSupplier;
  typedef PushSupplier *PushSupplier_ptr;
  
#endif // end #if !defined


#if !defined (_RTECEVENTCOMM_PUSHSUPPLIER_CH_)
#define _RTECEVENTCOMM_PUSHSUPPLIER_CH_

class PushSupplier: public virtual ACE_CORBA_1 (Object)
  {
  public:
    // the static operations
    static PushSupplier_ptr _duplicate (PushSupplier_ptr obj);
    static PushSupplier_ptr _narrow (CORBA::Object_ptr obj, CORBA::Environment &env);
    static PushSupplier_ptr _nil (void);
    static PushSupplier_ptr _bind (const char *host, CORBA::UShort port, const char *key, CORBA::Environment &env);

    virtual void disconnect_push_supplier (CORBA::Environment &env);
  protected:
    PushSupplier (void); // default constructor
    PushSupplier (STUB_Object *objref);
    virtual ~PushSupplier (void);
  private:
    PushSupplier (const PushSupplier&);
    void operator= (const PushSupplier&);
  };


#endif // end #if !defined


#if !defined (_RTECEVENTCOMM_PUSHSUPPLIER___VAR_CH_)
#define _RTECEVENTCOMM_PUSHSUPPLIER___VAR_CH_

  class PushSupplier_var
  {
  public:
    PushSupplier_var (void); // default constructor
    PushSupplier_var (PushSupplier_ptr);
    PushSupplier_var (const PushSupplier_var &); // copy constructor
    ~PushSupplier_var (void); // destructor
    
    PushSupplier_var &operator= (PushSupplier_ptr);
    PushSupplier_var &operator= (const PushSupplier_var &);
    PushSupplier_ptr operator-> (void) const;
    
    operator const PushSupplier_ptr &() const;
    operator PushSupplier_ptr &();
    // in, inout, out, _retn 
    PushSupplier_ptr in (void) const;
    PushSupplier_ptr &inout (void);
    PushSupplier_ptr &out (void);
    PushSupplier_ptr _retn (void);
    PushSupplier_ptr ptr (void) const;

  private:
    PushSupplier_ptr ptr_;
  };


#endif // end #if !defined


#if !defined (_RTECEVENTCOMM_PUSHSUPPLIER___OUT_CH_)
#define _RTECEVENTCOMM_PUSHSUPPLIER___OUT_CH_

  class PushSupplier_out
  {
  public:
    PushSupplier_out (PushSupplier_ptr &);
    PushSupplier_out (PushSupplier_var &);
    PushSupplier_out (PushSupplier_out &);
    PushSupplier_out &operator= (PushSupplier_out &);
    PushSupplier_out &operator= (const PushSupplier_var &);
    PushSupplier_out &operator= (PushSupplier_ptr);
    operator PushSupplier_ptr &();
    PushSupplier_ptr &ptr (void);
    PushSupplier_ptr operator-> (void);
    
  private:
    PushSupplier_ptr &ptr_;
  };


#endif // end #if !defined

  static CORBA::TypeCode_ptr _tc_PushSupplier;

};


#if defined (__ACE_INLINE__)
#include "RtecEventCommC.i"
#endif // defined INLINE


#endif // if !defined
