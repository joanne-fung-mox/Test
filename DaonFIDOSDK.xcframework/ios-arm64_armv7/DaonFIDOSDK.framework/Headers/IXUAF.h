/*!
 @header IXUAF
 Simplified FIDO interface.
 @copyright Daon. All rights reserved.
 @updated 2019-01-10
 */

#import <Foundation/Foundation.h>
#import "DaonFIDO.h"
#import "IXUAFServiceDelegate.h"

static NSString * _Nonnull const kIXUAFServiceParameterUsername      = @"username";
static NSString * _Nonnull const kIXUAFServiceParameterApplication   = @"application";
static NSString * _Nonnull const kIXUAFServiceParameterDescription   = @"description";
static NSString * _Nonnull const kIXUAFServiceParameterIdentifier    = @"id";
static NSString * _Nonnull const kIXUAFServiceParameterProvider      = @"provider";
static NSString * _Nonnull const kIXUAFServiceParameterServer        = @"device.gateway.url";
static NSString * _Nonnull const kIXUAFServiceParameterType          = @"push.type";


static NSString * _Nonnull const kIXUAFAAIDPasscode = @"D409#2301";
static NSString * _Nonnull const kIXUAFAAIDFace     = @"D409#2205";
static NSString * _Nonnull const kIXUAFAAIDTouchID  = @"D409#2101";


static NSString * _Nonnull const kIXUAFApplicationSchemeDefault = @"default";  // iOS bundle id
static NSString * _Nonnull const kIXUAFApplicationSchemeUser    = @"user";     // User set
static NSString * _Nonnull const kIXUAFApplicationSchemeURL     = @"url";      // E.g. Published Locally


@interface IXUAF : NSObject <IXUAFDelegate>

/*!
@brief The configuration delegate.
*/
@property(nonatomic, weak) id<IXUAFDelegate> _Nullable delegate;

/*!
@brief True if the SDK is initialized.
*/
@property (nonatomic, readonly) BOOL initialized;

/*!
@brief The FIDO application id.
*/
@property (nonatomic, strong)   NSString *_Nullable application;

/*!
@brief Enable or disable logging. Default is disabled.
*/
@property (nonatomic, assign)   BOOL logging;

/*!
@brief Enable or disable ADoS support. Default is disabled.
*/
@property (nonatomic, assign)   BOOL ados;

/*!
 @brief Set token received when registering for push notifications
 @param token The Apple Push Notifications token.
 */
+ (void) setPushNotificationServiceToken:(NSData*_Nonnull)token NS_SWIFT_NAME(setPushNotificationService(token:));

- (instancetype _Nonnull) initWithService:(id<IXUAFServiceDelegate>_Nullable)service;

/*!
 @brief Initialise the SDK. This must be called before the SDK is used.
 @param parameters The SDK exensions and other parameters.
 @param completion The completion handler.
 */
- (void) initializeWithParameters:(NSDictionary *_Nullable)parameters completion:(void (^_Nonnull)(IXUAFErrorCode code))completion;

/*!
@brief Set parameter/extension
@param param The SDK exensions and other parameters.
@param value The value.
*/
- (IXUAFErrorCode) setParameter:(NSString*_Nonnull)param value:(NSString*_Nonnull)value;

/*!
@brief Get application scheme
*/
- (NSString*_Nonnull) applicationScheme;

/*!
 @brief Discover available UAF authenticators.
 @param handler The handler returns the list of authenticators or an error.
 */
- (void) discoverWithCompletionHandler:(void (^_Nonnull)(IXUAFDiscoveryData *_Nullable response, NSError *_Nullable error))handler;

/*!
 @brief Perform UAF register operation.
 @param handler The handler returns the response or an error.
 */
- (void) registerWithCompletionHandler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler;

/*!
 @brief Perform UAF register operation.
 @param username The username.
 @param handler The handler returns the response or an error.
 */
- (void) registerWithUsername:(NSString*_Nullable)username handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler;

/*!
 @brief Perform UAF authenticate operation.
 @param handler The handler returns the response or an error.
 */
- (void) authenticateWithCompletionHandler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler;

/*!
 @brief Perform UAF step-up authenticate operation.
 @param username The username.
 @param description A short description
 @param handler The handler returns the response or an error.
 */
- (void) authenticateWithUsername:(NSString*_Nullable)username description:(NSString*_Nullable)description handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler;

/*!
 @brief Perform UAF step-up authenticate operation.
 @param username The username.
 @param description A short description
 @param parameters Additional parameters passed during authentication
 @param handler The handler returns the response or an error.
 */
- (void) authenticateWithUsername:(NSString*_Nullable)username description:(NSString*_Nullable)description params:(NSDictionary*_Nullable)parameters handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler;

/*!
 @brief Perform UAF authenticate operation in response to a push notification.
 @param notification The push notification dictionary.
 @param username The username.
 @param handler The handler returns the response or an error.
 */
- (void) authenticateWithNotification:(NSDictionary*_Nonnull)notification username:(NSString*_Nullable)username handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler;

/*!
 @brief Perform UAF deregister operation.
 @param aaid The AAID.
 @param username The username if available
 @param handler The handler returns nil if the operation was a success.
 */
- (void) deregisterWithAaid:(NSString*_Nonnull)aaid username:(NSString*_Nullable)username handler:(void (^_Nonnull)(NSError *_Nullable))handler;

/*!
 @brief Perform UAF deregister operation.
 @param message The FIDO deregistration message.
 @param handler The handler returns nil if the operation was a success.
 */
- (void) deregisterWithMessage:(NSString*_Nonnull)message handler:(void (^_Nonnull)(NSError *_Nullable))handler;

/*!
 @brief Perform UAF deregister operation.
 @discussion The handler is called for each deregistered authenticator with an AAID and/or error. The call is complete when the AAID is nil.
 @param username The username
 @param handler The handler is called with an AAID and/or error. The call is complete when the AAID is nil.
 */
- (void) deregisterWithUsername:(NSString*_Nonnull)username handler:(void (^_Nonnull)(NSString *_Nullable, NSError *_Nullable))handler;

/*!
 @brief Check for registered authenticators.
 @discussion Get a list of authenticators which match the given registration policy and lists those which
 are registered for the given user and app ID.
 @param username The username.
 @param handler The handler returns the list of authenticators or an error.
 */
- (void) checkRegistrationsWithUsername:(NSString*_Nonnull)username handler:(void (^_Nonnull)(NSArray<IXUAFAuthenticator *> * _Nullable authenticators, NSError * _Nullable error)) handler;

/*!
 @brief Check that a UAF message can be processed by at least one of the available UAF authenticators.
 @param message The FIDO message.
 @param handler The handler returns nil if the operation was a success.
 */
- (void) checkMessage:(NSString *_Nonnull)message handler:(void (^_Nonnull)(NSError *_Nullable error))handler;

/*!
 @brief Check that a UAF message can be processed by at least one of the available UAF authenticators.
 @param message The FIDO message.
 @param username The username
 @param handler The handler returns nil if the operation was a success.
 */
- (void) checkMessage:(NSString *_Nonnull)message username:(NSString*_Nullable)username handler:(void (^_Nonnull)(NSError *_Nullable error))handler;

/*!
 @brief Generate a One Time Password (OTP).
 @param mode The mode IXUAFOfflineOTPModeIdentify or IXUAFOfflineOTPModeSign.
 @param handler The handler returns the response or an error.
 */
- (void) oneTimePasswordWithMode:(IXUAFOfflineOTPMode)mode handler:(void (^_Nonnull)(NSDictionary<NSString*, NSString*> *_Nullable response, NSError *_Nullable error))handler;

/*!
 @brief Check if authenticator is registered
 @param aaid The aaid
 @param username The username
 */
- (BOOL) registeredWithAuthenticator:(NSString*_Nonnull)aaid username:(NSString*_Nullable)username;
    
// Single Shot

/*!
 @brief Register with FIDO message, e.g. can be used for single-shot registration.
 @param message The FIDO message.
 @param handler The handler returns the response or an error.
 */
- (void) registerWithMessage:(NSString*_Nonnull)message handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler;

/*!
 @brief Authenticate with FIDO message, e.g. can be used for single-shot authentication.
 @param message The FIDO message.
 @param handler The handler returns the response or an error.
 */
- (void) authenticateWithMessage:(NSString*_Nonnull)message handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler;

// Headless

- (BOOL) isRegisteredAaid:(NSString*_Nonnull)aaid username:(NSString*_Nullable)username;

- (void) registerWithAaid:(NSString*_Nonnull)aaid
                 username:(NSString*_Nullable)username
                     data:(id _Nullable)data
                  handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler;

- (void) registerWithAaid:(NSString*_Nonnull)aaid
                 username:(NSString*_Nullable)username
                  handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler;

- (void) authenticateWithAaid:(NSString*_Nonnull)aaid
                     username:(NSString*_Nullable)username
                  description:(NSString*_Nullable)description
                       params:(NSDictionary*_Nullable)parameters
                      handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler;

- (void) authenticateWithAaid:(NSString*_Nonnull)aaid
                     username:(NSString*_Nullable)username
                         data:(id _Nullable)data
                  description:(NSString*_Nullable)description
                       params:(NSDictionary*_Nullable)parameters
                      handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler;
@end

