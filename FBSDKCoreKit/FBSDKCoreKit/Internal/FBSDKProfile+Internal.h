/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#if !TARGET_OS_TV

#import <FBSDKCoreKit/FBSDKAccessTokenProviding.h>
#import <FBSDKCoreKit/FBSDKGraphRequest.h>
#import <FBSDKCoreKit/FBSDKProfile.h>
#import <FBSDKCoreKit_Basics/FBSDKCoreKit_Basics.h>

NS_ASSUME_NONNULL_BEGIN

@protocol _FBSDKNotificationPosting;
@protocol FBSDKNotificationDelivering;
@protocol FBSDKSettings;
@protocol FBSDKURLHosting;

typedef void (^FBSDKParseProfileBlock)(id result, FBSDKProfile *_Nonnull *_Nullable profileRef);

@interface FBSDKProfile (Internal)

+ (void)cacheProfile:(nullable FBSDKProfile *)profile;
+ (nullable FBSDKProfile *)fetchCachedProfile NS_SWIFT_NAME(fetchCachedProfile());

+ (void)loadProfileWithToken:(FBSDKAccessToken *)token
                graphRequest:(id<FBSDKGraphRequest>)request
                  completion:(FBSDKProfileBlock)completion
                  parseBlock:(FBSDKParseProfileBlock)parseBlock;

+ (void)loadProfileWithToken:(FBSDKAccessToken *)token completion:(_Nullable FBSDKProfileBlock)completion;

+ (void)observeChangeAccessTokenChange:(NSNotification *)notification;

@end

NS_ASSUME_NONNULL_END

#endif
