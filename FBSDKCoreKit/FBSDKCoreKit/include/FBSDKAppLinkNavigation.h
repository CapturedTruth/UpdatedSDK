/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#if !TARGET_OS_TV

#import <Foundation/Foundation.h>

#import <FBSDKCoreKit/FBSDKAppLinkNavigationBlock.h>
#import <FBSDKCoreKit/FBSDKAppLinkNavigationType.h>
#import <FBSDKCoreKit/FBSDKAppLinkResolving.h>

@class FBSDKAppLink;
@protocol FBSDKInternalURLOpener;
@protocol FBSDKSettings;

NS_ASSUME_NONNULL_BEGIN

/**
 Represents a pending request to navigate to an App Link. Most developers will
 simply use navigateToURLInBackground: to open a URL, but developers can build
 custom requests with additional navigation and app data attached to them by
 creating FBSDKAppLinkNavigations themselves.
 */
NS_EXTENSION_UNAVAILABLE_IOS("Not available in app extension")
NS_SWIFT_NAME(AppLinkNavigation)
@interface FBSDKAppLinkNavigation : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 The default resolver to be used for App Link resolution. If the developer has not set one explicitly,
 a basic, built-in FBSDKWebViewAppLinkResolver will be used.
 */
@property (class, nonatomic, strong) id<FBSDKAppLinkResolving> defaultResolver
NS_SWIFT_NAME(default);

/**
 The extras for the AppLinkNavigation. This will generally contain application-specific
 data that should be passed along with the request, such as advertiser or affiliate IDs or
 other such metadata relevant on this device.
 */
@property (nonatomic, readonly, copy) NSDictionary<NSString *, id> *extras;

/**
 The al_applink_data for the AppLinkNavigation. This will generally contain data common to
 navigation attempts such as back-links, user agents, and other information that may be used
 in routing and handling an App Link request.
 */
@property (nonatomic, readonly, copy) NSDictionary<NSString *, id> *appLinkData;

/// The AppLink to navigate to
@property (nonatomic, readonly, strong) FBSDKAppLink *appLink;

/**
 Return navigation type for current instance.
 No-side-effect version of navigate:
 */
@property (nonatomic, readonly) FBSDKAppLinkNavigationType navigationType;

// UNCRUSTIFY_FORMAT_OFF
/// Creates an AppLinkNavigation with the given link, extras, and App Link data
+ (instancetype)navigationWithAppLink:(FBSDKAppLink *)appLink
                               extras:(NSDictionary<NSString *, id> *)extras
                          appLinkData:(NSDictionary<NSString *, id> *)appLinkData
                             settings:(id<FBSDKSettings>)settings
NS_SWIFT_NAME(init(appLink:extras:appLinkData:settings:));

/**
 Creates an NSDictionary<NSString *, id> with the correct format for iOS callback URLs,
 to be used as 'appLinkData' argument in the call to navigationWithAppLink:extras:appLinkData:
 */
+ (NSDictionary<NSString *, NSDictionary<NSString *, NSString *> *> *)callbackAppLinkDataForAppWithName:(NSString *)appName
                                                                                                    url:(NSString *)url
NS_SWIFT_NAME(callbackAppLinkData(forApp:url:));
// UNCRUSTIFY_FORMAT_ON

/// Performs the navigation
- (FBSDKAppLinkNavigationType)navigate:(NSError **)error
  __attribute__((swift_error(nonnull_error)));

/// Returns a FBSDKAppLink for the given URL
+ (void)resolveAppLink:(NSURL *)destination handler:(FBSDKAppLinkBlock)handler;

/// Returns a FBSDKAppLink for the given URL using the given App Link resolution strategy
+ (void)resolveAppLink:(NSURL *)destination
              resolver:(id<FBSDKAppLinkResolving>)resolver
               handler:(FBSDKAppLinkBlock)handler;

/// Navigates to a FBSDKAppLink and returns whether it opened in-app or in-browser
+ (FBSDKAppLinkNavigationType)navigateToAppLink:(FBSDKAppLink *)link error:(NSError **)error
  __attribute__((swift_error(nonnull_error)));

/**
 Returns a FBSDKAppLinkNavigationType based on a FBSDKAppLink.
 It's essentially a no-side-effect version of navigateToAppLink:error:,
 allowing apps to determine flow based on the link type (e.g. open an
 internal web view instead of going straight to the browser for regular links.)
 */
+ (FBSDKAppLinkNavigationType)navigationTypeForLink:(FBSDKAppLink *)link;

/// Navigates to a URL (an asynchronous action) and returns a FBSDKNavigationType
+ (void)navigateToURL:(NSURL *)destination handler:(FBSDKAppLinkNavigationBlock)handler;

/**
 Navigates to a URL (an asynchronous action) using the given App Link resolution
 strategy and returns a FBSDKNavigationType
 */
+ (void)navigateToURL:(NSURL *)destination
             resolver:(id<FBSDKAppLinkResolving>)resolver
              handler:(FBSDKAppLinkNavigationBlock)handler;

/**
 Internal method exposed to facilitate transition to Swift.
 API Subject to change or removal without warning. Do not use.

 @warning INTERNAL - DO NOT USE
 */
+ (void)configureWithSettings:(id<FBSDKSettings>)settings
                    urlOpener:(id<FBSDKInternalURLOpener>)urlOpener
           appLinkEventPoster:(id<FBSDKAppLinkEventPosting>)appLinkEventPoster
              appLinkResolver:(id<FBSDKAppLinkResolving>)appLinkResolver
NS_SWIFT_NAME(configure(settings:urlOpener:appLinkEventPoster:appLinkResolver:));

@end

NS_ASSUME_NONNULL_END

#endif
