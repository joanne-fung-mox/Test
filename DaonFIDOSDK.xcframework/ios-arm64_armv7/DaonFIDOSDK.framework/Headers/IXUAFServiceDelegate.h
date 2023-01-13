/*!
 @header IXUAFServiceDelegate
 SDK delegate for for handling FIDO related communication with a Relying Party.
 @copyright Daon. All rights reserved.
 @updated 2019-01-20
 */

#ifndef IXUAFServiceDelegate_h
#define IXUAFServiceDelegate_h

#import <Foundation/Foundation.h>

@protocol IXUAFServiceDelegate <NSObject>

/*!
 @brief Get a FIDO registration message, e.g. from a server.
 @discussion The registration call, registerWithCompletionHandler, will call this method when a registration message is needed.
 @param username An optional user name. 
 @param handler The handler should return the FIDO message and/or any errors.
 */
- (void) serviceRequestRegistrationWithUsername:(NSString*_Nullable)username handler:(nonnull void (^)(NSString* _Nullable message, NSError* _Nullable error))handler;

/*!
 @brief Send FIDO registration message to the server.
 @discussion The registration call, registerWithCompletionHandler, will call this method when the user has registered an authenticator and a registration message has been created.
 @param uafMessage The FIDO registration message
 @param request The optional FIDO request. May not be required depending on implementation.
 @param handler The handler should return the FIDO response message and/or any errors.
 */
- (void) serviceRegisterWithMessage:(NSString* _Nonnull)uafMessage request:(NSString*_Nonnull)request handler:(nonnull void (^)(NSString* _Nullable response, NSError* _Nullable error))handler;

/*!
 @brief Get a FIDO authentication message, e.g. from a server.
 @discussion The authentication API will call this method when an authentication message is needed.
 @param params The request parameters, e.g. username.
 @param handler The handler should return the FIDO message and/or any errors.
 */
- (void) serviceRequestAuthenticationWithParameters:(NSDictionary<NSString*, id>* _Nullable)params handler:(nonnull void (^)(NSString* _Nullable message, NSError* _Nullable error))handler;

/*!
 @brief Send FIDO authentication message to the server.
 @discussion The authentication API will call this method when the user has authenticated and an authentication message has been created.
 @param uafMessage The FIDO authentication message
 @param request The optional FIDO request. May not be required depending on implementation.
 @param username The optional user name. May be provided in case of a step-up authentication.
 @param handler The handler should return the FIDO response message and/or any errors.
 */
- (void) serviceAuthenticateWithMessage:(NSString* _Nonnull)uafMessage request:(NSString*_Nonnull)request username:(NSString*_Nullable)username handler:(nonnull void (^)(NSString* _Nullable response, NSError* _Nullable error))handler;

/*!
 @brief Send FIDO message to the server.
 @discussion The API will call this method to submit ADOS data to the server.
 @param uafMessage The FIDO registration/authentication message
 @param username The optional user name. May be provided in case of a step-up authentication.
 @param handler The handler should return the FIDO response message and/or any errors.
 */
- (void) serviceUpdateWithMessage:(NSString* _Nonnull)uafMessage username:(NSString*_Nullable)username handler:(nonnull void (^)(NSString* _Nullable response, NSError* _Nullable error))handler;

/*!
 @brief Get a FIDO de-registration message, e.g. from a server.
 @discussion The de-registration calls will call this method when a de-registration message is needed.
 @param aaid The AAID to deregister.
 @param username The optional user name.
 @param application The FIDO application ID
 @param handler The handler should return the FIDO message and/or any errors.
 */
- (void) serviceRequestDeregistrationWithAaid:(NSString* _Nonnull)aaid username:(NSString*_Nullable)username application:(NSString*_Nullable)application handler:(nonnull void (^)(NSString* _Nullable response, NSError* _Nullable error))handler;

/*!
 @brief Get the FIDO registration policy, e.g. from a server.
 @discussion The checkRegistrations call will call this method when needed.
 @param handler The handler should return the FIDO policy and/or any errors.
 */
- (void) serviceRequestRegistrationPolicyWithHandler:(nonnull void (^)(NSString* _Nullable policy, NSError* _Nullable error))handler;

/*!
 @brief Send authentication attempt data to the server.
 @discussion The API will call this method after a failed attempt. This is not called for an ADOS authenticator, since the server already have the necessary information.
 @param info The attempt information provided by the SDK.
 @param handler The handler should return the FIDO response message and/or any errors.
 */
- (void) serviceUpdateWithAttempt:(NSDictionary<NSString*, id>* _Nonnull)info handler:(nonnull void (^)(NSString* _Nullable response, NSError* _Nullable error))handler;


@optional

- (void) serviceInitializeWithParameters:(NSDictionary<NSString*, NSString*>* _Nullable)params handler:(nonnull void (^)(NSError* _Nullable error))handler;

@end


#endif /* IXUAFServiceDelegate_h */
