//
//  MoviePlayer.m
//  CameraEngine
//
//  Created by KyuJin on 13. 7. 5..
//
//
#import "CJVideoPlayer.h"

#import "CJVideoInterface.h"
#import "AppController.h"

@implementation CJVideoPlayer

@synthesize cjController;
@synthesize mpMoviePlayer = _mpMoviePlayer;
static CJVideoPlayer *sharedInstance;

+ (CJVideoPlayer*) getInstance
{
    @synchronized(self)
    {
        if (!sharedInstance)
        {
            sharedInstance = [[CJVideoPlayer alloc] init];
        }
        return sharedInstance;
    }

}

+ (void) releaseInstance
{
    [sharedInstance release];
    sharedInstance = nil;
    
}

- (id) initWithPath:(NSURL*)contentURL frame:(CGRect)frame type:(CJVideoType)type{
    
    cjController = nil;
    self.timer = nil;
    
    self.videoType = type;
    self.contentURL = contentURL;
    
    [self.view setFrame:frame];
    [self.view setBackgroundColor:[UIColor clearColor]];
    [self.view setUserInteractionEnabled:false];
    
    
    self.mpMoviePlayer = [[MPMoviePlayerController alloc] initWithContentURL:self.contentURL];
    [self.mpMoviePlayer.view setFrame:CGRectMake(self.view.bounds.origin.x, self.view.bounds.origin.y, self.view.bounds.size.width, self.view.bounds.size.height)];
    [self.mpMoviePlayer.view setBackgroundColor:[UIColor clearColor]];
    self.mpMoviePlayer.controlStyle = MPMovieControlStyleEmbedded;
    
    [self.view addSubview:self.mpMoviePlayer.view];
    [self.view setBackgroundColor:[UIColor clearColor]];
    [self setMoviePlayerType:self.videoType];
    
    
    UIWindow *window = [[UIApplication sharedApplication] keyWindow];
    [[[window subviews] objectAtIndex:0] addSubview:self.view];

    
    [self addNotificationObserver];
    [self addActiveNotification];
    

    return self;
}



- (void) setMoviePlayerType:(CJVideoType)type
{

    switch (self.videoType) {
        case CJVideoTypeNoneInrective:
            self.mpMoviePlayer.controlStyle =  MPMovieControlStyleNone;
            break;
            
        case CJVideoTypeSkip:
            self.mpMoviePlayer.controlStyle =  MPMovieControlStyleNone;
            self.view.userInteractionEnabled = true;
            break;
            
        case CJVideoTypeNativeVideo:
        {
            self.mpMoviePlayer.controlStyle = MPMovieControlStyleFullscreen;
            self.view.userInteractionEnabled = false;
            [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(MPMoviePlayerDidExitFullscreen:)
                                                         name:MPMoviePlayerDidExitFullscreenNotification object:self.mpMoviePlayer];
        }
            break;
            
        case CJVideoTypeNativeVideo2:
            self.mpMoviePlayer.controlStyle = MPMovieControlStyleEmbedded;
            break;
            
        case CJVideoTypeCJVideo:
            self.mpMoviePlayer.controlStyle = MPMovieControlStyleNone;
            self.view.userInteractionEnabled = true;
            [self makeCJController];
            break;
            
        case CJVideoTypeFrameVideo:
            self.mpMoviePlayer.controlStyle =  MPMovieControlStyleNone;
            self.view.userInteractionEnabled = false;
            
            break;
            
        default:
            self.view.userInteractionEnabled = true;
            break;
    }

}

- (void) makeCJController
{
    self.cjController = [[CJVideoController alloc] initWithFrame:self.view.bounds];
    self.cjController.delegate = self;
    [self.view addSubview:self.cjController];

}

- (void) releaseCJController
{
    if (self.cjController) {
        [self.cjController.timer invalidate];
        self.cjController.timer = nil;
        
        [self.cjController.customSlider release];

        self.cjController.delegate = nil;
        [self.cjController removeFromSuperview];
        [self.cjController release];
        self.cjController = nil;
    }


}

#pragma mark - Touch Evnet
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{

    if (self.videoType == CJVideoTypeSkip) {
        CJVideoInterface::getInstance()->stopVideo();
        return;
    }else if(self.videoType == CJVideoTypeCJVideo){
        
        [self.cjController setHidden:!self.cjController.hidden];
        
        if (self.cjController.hidden == NO) {
            [self onTimerForTouch];
        }
    }

    
}

#pragma mark - timer

- (void)onTimerForTouch{
    if (self.timer != nil) {
        [self.timer invalidate];
        self.timer = nil;
    }
    self.timer = [NSTimer scheduledTimerWithTimeInterval:3
                                                  target:self
                                                selector:@selector(timerEnd)
                                                userInfo:nil
                                                 repeats:NO];

}

- (void)timerEnd{
    [self.cjController setHidden:YES];
    [self.timer invalidate];
    self.timer = nil;
}


- (void)timerInvalidate
{
    if (self.timer!= nil) {
        [self.timer invalidate];
        self.timer = nil;
    }

}


#pragma mark - Notificatoin Control
- (void) addNotificationObserver
{
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(notificationReceiver:)
                                                 name:MPMoviePlayerPlaybackDidFinishNotification
                                               object:self.mpMoviePlayer];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(notificationReceiver:)
                                                 name:MPMoviePlayerLoadStateDidChangeNotification
                                               object:nil];
    
}


- (void) notificationReceiver:(NSNotification*)notification
{
    NSString *noti = notification.name;
    NSDictionary *userInfo = notification.userInfo;
    NSLog(@"__noti name = %@", [notification name]);
    NSLog(@"__userInfo = %@", userInfo);
    
    // change state Notification
    if([noti isEqualToString:MPMoviePlayerLoadStateDidChangeNotification])
    {
        if(self.mpMoviePlayer.loadState == MPMovieLoadStatePlaythroughOK)
        {
            if (self.videoType == CJVideoTypeCJVideo) {
                [self.cjController setTotalProgress:self.mpMoviePlayer.duration];
            }
        }
    }
    
    // Finished Notification
    if([noti isEqualToString:MPMoviePlayerPlaybackDidFinishNotification])
    {
        [[NSNotificationCenter defaultCenter] removeObserver:self];
        [self removeActiveNotification];
        
        [self releaseCJController];
        
        if (self.videoType == CJVideoTypeFrameVideo) {
            CJVideoInterface::getInstance()->removeFrameVideo();
            CCNotificationCenter::sharedNotificationCenter()->postNotification(CJNOTIFICATION_FRAME_VIDEOVIEW_FINISHCALL);

        }else{
            CJVideoInterface::getInstance()->stopVideo();
            CCNotificationCenter::sharedNotificationCenter()->postNotification(CJNOTIFICATION_VIDEO_FINISHCALL);
        }
        
        
    }
    
}

- (void) addActiveNotification
{
    //on BecomeActive noti
    didBecomeActiveNotification = [[NSNotificationCenter defaultCenter] addObserverForName:UIApplicationDidBecomeActiveNotification
                                                                                    object:[UIApplication sharedApplication]
                                                                                     queue:[NSOperationQueue mainQueue]
                                                                                usingBlock:^(NSNotification *note)
                                   {
                                       // here
                                       [self.cjController setHidden:NO];
                                       [self.cjController setPlayButtonState];
                                   }];
    
}

- (void) removeActiveNotification
{
    [[NSNotificationCenter defaultCenter] removeObserver:didBecomeActiveNotification];
    
}


#pragma mark - Player Control <cjVideoControllerDelegate>

-(MPMoviePlayerController*) getMPMoviePlayer
{
    return self.mpMoviePlayer;
}


- (void) play
{
    if(!self.mpMoviePlayer)
    {
        return;
    }
    [self.mpMoviePlayer play];
}

- (void) pause
{
    if(!self.mpMoviePlayer)
    {
        NSLog(@"error : Movie Player Not Initialized");
        return;
    }

    [self.mpMoviePlayer pause];
}

- (void) stop
{
    if(!self.mpMoviePlayer)
    {
        NSLog(@"error : Movie Player Not Initialized");
        return;
    }
    
    [self.mpMoviePlayer stop];
    
}

- (void) resume
{
    
    if(!self.mpMoviePlayer)
    {
        NSLog(@"error : Movie Player Not Initialized");
        return;
    }
    [self.mpMoviePlayer play];
}

#pragma mark - button custom


- (void) addVideoMask: (NSString*)imagePath;
{
    NSString* path = [[NSBundle mainBundle] pathForResource: imagePath ofType: nil inDirectory:nil];
    
    if ([[NSFileManager defaultManager] fileExistsAtPath:path])
    {
        UIImage *tempImage = [UIImage imageNamed:imagePath];
        UIImageView *tempImageView = [[[UIImageView alloc] initWithImage:tempImage] autorelease];
        
        //resizing
        tempImage = [AppController resizingWithImageForScaleFactor:tempImage];
        [tempImageView setImage:tempImage];
        [tempImageView setFrame:[self.view bounds]];
        
        [self.view addSubview:tempImageView];
        [self.view bringSubviewToFront:tempImageView];
        
    }
}


-(void) addVideoBtn: (const char*) btnPath posX:(float) x posY: (float) y iTag: (int) tag
{
    float customScale = 1;
    if ( [[[UIDevice currentDevice] model] isEqualToString:@"iPhone"] )
    {
        customScale = 1.5;
    }
    
    
    NSString *filePath = [NSString stringWithUTF8String:btnPath];
    NSString* path = [[NSBundle mainBundle] pathForResource: filePath ofType: nil inDirectory:nil];
    NSData *imageData = [NSData dataWithContentsOfFile:path];
    
    if ([[NSFileManager defaultManager] fileExistsAtPath:path])
    {
        UIButton *tempBtn = [UIButton buttonWithType:UIButtonTypeCustom];
        UIImage *tempImage = [UIImage imageWithData:imageData];
        
        float tempImageWidth = tempImage.size.width/2;
        x = x+tempImageWidth;
        
        tempImage = [AppController resizingWithImageForScaleFactor:tempImage customScale:customScale];
        x = x * ([[UIScreen mainScreen] bounds].size.height / 1024) - (tempImage.size.width/2);
        y = y * [AppController getScaleValue];
        
        
        [tempBtn setBackgroundImage:tempImage  forState:UIControlStateNormal];
        [tempBtn setFrame:CGRectMake(x,y, tempImage.size.width, tempImage.size.height)];
        [tempBtn addTarget:self action:@selector(customButtonTouched:) forControlEvents:UIControlEventTouchUpInside];
        [tempBtn setTag:tag];
        
        if(self.videoType == CJVideoTypeCJVideo)
        {
            [self.cjController addSubview:tempBtn];
            [self.cjController bringSubviewToFront:tempBtn];
            [self.cjController setHidden:TRUE];
        }
        else
        {
            [self.view addSubview:tempBtn];
            [self.view bringSubviewToFront:tempBtn];
        }
        
        
    }
}

- (void) customButtonTouched:(id)sender
{
    CJVideoInterface::getInstance()->onButtonTouch(((UIButton*)sender).tag);
}







- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
}
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskLandscape;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)dealloc {
    NSLog(@"CJVideoPlaer dealloc");
    
    [self.mpMoviePlayer release];
    self.mpMoviePlayer = nil;
    self.contentURL = nil;

    [self.timer invalidate];
    self.timer = nil;
    
    [super dealloc];
}


@end
