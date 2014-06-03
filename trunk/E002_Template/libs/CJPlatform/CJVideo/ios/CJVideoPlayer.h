

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayer.h>
#import "CJVideoController.h"


typedef enum CJVideoType
{
    CJVideoTypeNoneInrective = 0,                         // no button type
    CJVideoTypeSkip,
    CJVideoTypeNativeVideo,
    CJVideoTypeNativeVideo2,
    CJVideoTypeCJVideo,
    CJVideoTypeFrameVideo,
} CJVideoType;

@interface CJVideoPlayer : UIViewController <cjVideoControllerDelegate>
{
    MPMoviePlayerController *_mpMoviePlayer;
    NSNotification* didBecomeActiveNotification;
}

@property (nonatomic, retain) CJVideoController *cjController;
@property (nonatomic, retain) MPMoviePlayerController *mpMoviePlayer;
@property (nonatomic, retain) NSURL *contentURL;
@property (nonatomic, assign) CJVideoType videoType;
@property (nonatomic, retain) NSTimer *timer;

+ (CJVideoPlayer*) getInstance;
+ (void) releaseInstance;

- (id) initWithPath:(NSURL*)contentURL frame:(CGRect)frame type:(CJVideoType)type;
- (void) setMoviePlayerType:(CJVideoType)type;

- (void) makeCJController;
- (void) releaseCJController;

- (void) addNotificationObserver;
- (void) notificationReceiver:(NSNotification*)notification;
- (void) addActiveNotification;
- (void) removeActiveNotification;

- (MPMoviePlayerController*) getMPMoviePlayer;  /* cjVideoControllerDelegate method */
- (void) play;                                  /* cjVideoControllerDelegate method */
- (void) pause;                                 /* cjVideoControllerDelegate method */
- (void) stop;                                  /* cjVideoControllerDelegate method */
- (void) resume;


- (void) addVideoMask: (NSString*)imagePath;
- (void) addVideoBtn: (const char*) btnPath posX:(float) x posY: (float) y iTag: (int) tag;
- (void) customButtonTouched:(id)sender;


- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;

- (void)onTimerForTouch;
- (void)timerInvalidate;



@end
