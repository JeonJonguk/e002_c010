//
//  SoundPhonics_TemplateAppController.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 5. 3..
//  Copyright __MyCompanyName__ 2013년. All rights reserved.
//


@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate, UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;

+ (float)getScaleFactor;
+ (float)getScaleValue;
+ (float)getLetterBoxPositionX;
+ (UIImage *)resizingWithImageForScaleFactor:(UIImage *)image;
+ (UIImage *)resizingWithImageForScaleFactor:(UIImage *)image customScale:(float)fCustomScale;


@end

