//
//  SoundPhonics_TemplateAppController.mm
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 5. 3..
//  Copyright __MyCompanyName__ 2013년. All rights reserved.
//
#import <UIKit/UIKit.h>
#import "AppController.h"
#import "cocos2d.h"
#import "EAGLView.h"
#import "AppDelegate.h"

#import "RootViewController.h"




@implementation AppController

@synthesize window;
@synthesize viewController;



#pragma mark - utils for Resolution

+ (float)getScaleFactor
{
    float height = [[UIScreen mainScreen] bounds].size.width * [[UIScreen mainScreen] scale]; //320 * 2
    float scaleFactor = height / 768;
    // (320 * 2) / 768 = 0.8333
    return scaleFactor;
}

+ (float)getScaleValue
{
    //0.8333 / 2.0
    return [self getScaleFactor] / [[UIScreen mainScreen] scale];
}

+ (float)getLetterBoxPositionX
{
    return ([[UIScreen mainScreen] bounds].size.height  - (1024 * [AppController getScaleValue]))/2;
}

+ (UIImage *)resizingWithImageForScaleFactor:(UIImage *)image{
    
    CGSize newSize = CGSizeMake(image.size.width * [AppController getScaleValue], image.size.height * [AppController getScaleValue]);
    UIGraphicsBeginImageContextWithOptions(newSize, NO, 0.0);
    [image drawInRect:CGRectMake(0, 0, newSize.width, newSize.height)];
    UIImage *newImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return newImage;
}

+ (UIImage *)resizingWithImageForScaleFactor:(UIImage *)image customScale:(float)fCustomScale
{
    CGSize newSize = CGSizeMake(image.size.width * [AppController getScaleValue] * fCustomScale, image.size.height * [AppController getScaleValue] * fCustomScale);
    UIGraphicsBeginImageContextWithOptions(newSize, NO, 0.0);
    [image drawInRect:CGRectMake(0, 0, newSize.width, newSize.height)];
    UIImage *newImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return newImage;
}


#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

    // Override point for customization after application launch.

    // Add the view controller's view to the window and display.
//    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
//    EAGLView *__glView = [EAGLView viewWithFrame: [window bounds]
//                                     pixelFormat: kEAGLColorFormatRGBA8
//                                     depthFormat: GL_DEPTH_COMPONENT16
//                              preserveBackbuffer: NO
//                                      sharegroup: nil
//                                   multiSampling: NO
//                                 numberOfSamples:0 ];

    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    
    EAGLView *__glView = [EAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGBA8
                                     depthFormat: GL_DEPTH24_STENCIL8_OES
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples:0 ];

    
    // Use RootViewController manage EAGLView
    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
//    viewController.wantsFullScreenLayout = YES;
    viewController.view = __glView;

    
    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:viewController];
    }
    
    [window makeKeyAndVisible];

    [[UIApplication sharedApplication] setStatusBarHidden: YES];
    [[UIApplication sharedApplication] setIdleTimerDisabled:YES];
    
    
    
    // set push notifications.
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSInteger tmpint7 = [defaults integerForKey:@"SettingPush"];
    
    if (tmpint7 == 0)
    {
        [application registerForRemoteNotificationTypes:(UIRemoteNotificationTypeBadge |
                                                         UIRemoteNotificationTypeSound |
														 UIRemoteNotificationTypeAlert)];
        
        [defaults setInteger:1 forKey:@"SettingPush"];
        [defaults synchronize];
        
    }
    
	//Badge 개수 설정
	application.applicationIconBadgeNumber = 0;

    
    cocos2d::CCApplication::sharedApplication()->run();
    
    
    UIImage* leftImage = [UIImage imageNamed:@"left.jpg"];
    UIImageView* lefImgView = [[[UIImageView alloc] initWithImage:leftImage] autorelease];
    [lefImgView setFrame:CGRectMake([AppController getLetterBoxPositionX] - leftImage.size.width, 0, leftImage.size.width, leftImage.size.height)];
    [viewController.view addSubview:lefImgView];
    
    
    
    UIImage* rightImage = [UIImage imageNamed:@"right.jpg"];
    UIImageView* rightImgView = [[[UIImageView alloc] initWithImage:rightImage] autorelease];
    [rightImgView setFrame:CGRectMake([window bounds].size.height - ceil([AppController getLetterBoxPositionX]), 0, rightImage.size.width, rightImage.size.height)];
    [viewController.view addSubview:rightImgView];

    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
    
    cocos2d::CCDirector::sharedDirector()->pause();
//    cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
    cocos2d::CCDirector::sharedDirector()->resume();
//    cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();
    
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
	application.applicationIconBadgeNumber = 0;
    cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}

- (void)beginReceivingRemoteControlEvents
{
    
}

- (void)endReceivingRemoteControlEvents
{
    
}




#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
     cocos2d::CCDirector::sharedDirector()->purgeCachedData();
}


- (void)dealloc {
    [super dealloc];
}


@end

