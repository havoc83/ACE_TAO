// $Id$
//
// ============================================================================
//
// = LIBRARY
//    TAO
//
// = FILENAME
//    Service_Callbacks.h
//
// = DESCRIPTION
//   This is a generic interface that would be used to override many
//   of the default functionalities that the ORB provides by the
//   services if they have been loaded in to the ORB_Core
//
// = AUTHOR
//   Bala Natarajan <bala@cs.wustl.edu>
// ============================================================================
#ifndef TAO_SERVICE_CALLBACK_H
#define TAO_SERVICE_CALLBACK_H
#include "ace/pre.h"

#include "tao/IOPC.h"


#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

class TAO_Profile;
class TAO_MProfile;
class TAO_GIOP_Invocation;
class TAO_Server_Request;
class TAO_Message_State_Factory;

class TAO_Export TAO_Service_Callbacks
{
  // = TITLE
  //   An Abstract Base class for the hooks in the ORB.
  //
  // = DESCRIPTION
  //   This class (would) define all the hooks that may be needed by
  //   the ORB to override some of its default behaviour. The methods
  //   can be potentially used to call service level specific
  //   processing that may be required.

public:

  virtual ~TAO_Service_Callbacks (void);
  // Dtor

  virtual CORBA::Boolean select_profile (TAO_MProfile *mprofile,
                                         TAO_Profile *&pfile);
  // Select the profile from MProfile as the needs of the services
  // may be. Return the profile in <pfile>

  virtual CORBA::Boolean reselect_profile (TAO_Stub *stub,
                                           TAO_Profile *&pfile);
  // Select the profile from MProfile as the needs of the services
  // may be. Return the profile in <pfile>

  virtual void reset_profile_flags (void);
  // Reset the profile flags that the services could have

  virtual CORBA::Boolean object_is_nil (CORBA::Object_ptr obj);
  // Check whether <obj> is nil or not.


  virtual void service_context_list (TAO_Stub *&stub,
                                     IOP::ServiceContextList &service_list,
                                     CORBA::Boolean restart,
                                     CORBA::Environment &ACE_TRY_ENV);
  // Allow the services to add service specific service contexr
  // information.

  virtual int raise_comm_failure (TAO_GIOP_Invocation *invoke,
                                  TAO_Profile *profile,
                                  CORBA::Environment &ACE_TRY_ENV);
  // Allow the service layer to decide whether the COMM_FAILURE
  // exception should be thrown or a reinvocation is needed

  virtual int raise_transient_failure (TAO_GIOP_Invocation *invoke,
                                       TAO_Profile *profile,
                                       CORBA::Environment &ACE_TRY_ENV);
  // Allow the service layer to decide whether the TRANSIENT
  // exception should be thrown or a reinvocation is needed


  virtual void service_log_msg_rcv (TAO_Message_State_Factory &state);
  // Send the message state to the FT service for logging. This hook
  // sends the message state after the server receives the
  // message. The message at this point has been verified that it is a
  // GIOP message.

  virtual void service_log_msg_pre_upcall (TAO_ServerRequest &req);
  // Send the message state to the FT service for logging. This hook
  // sends the message state after the POA receives upcall but just
  // before the call has been dispatched to the servant

  virtual void service_log_msg_post_upcall (TAO_ServerRequest &req);
  // Send the message state to the FT service for logging. This hook
  // sends the message state just before the reply is ready to be
  // dispatched.
};


#if defined (__ACE_INLINE__)
# include "tao/Service_Callbacks.i"
#endif /* __ACE_INLINE__ */

#include "ace/post.h"
#endif /*TAO_SERVICE_CALLBACK_H*/
