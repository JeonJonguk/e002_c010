

#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED

#import "CJVideoController.h"
#import "AppController.h"
#import "UIImage+Brightness.h"

#define CUSTOM_SCALE_VALUE 1.3

@implementation CJVideoController
@synthesize delegate;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        [self setPlayButton];
        [self setSlider];
    }
    return self;
}

- (void)setPlayButton
{
    self.playBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    
    float customScale = 1;
    if ( [[[UIDevice currentDevice] model] isEqualToString:@"iPhone"] )
    {
        customScale = CUSTOM_SCALE_VALUE;
    }
    UIImage* playImg = [UIImage imageNamed:@"cjplatform_video_btn_play.png"];
    UIImage* pauseImg = [UIImage imageNamed:@"cjplatform_video_btn_pause.png"];
    playImg = [AppController resizingWithImageForScaleFactor:playImg customScale:customScale];
    pauseImg = [AppController resizingWithImageForScaleFactor:pauseImg customScale:customScale];
    
    [AppController resizingWithImageForScaleFactor:playImg];
    
    [self.playBtn setBackgroundImage:playImg forState:UIControlStateNormal];
    [self.playBtn setBackgroundImage:pauseImg forState:UIControlStateSelected];
    [self.playBtn setFrame:CGRectMake(self.bounds.size.width/2 - playImg.size.width/2 ,
                                      self.bounds.size.height/2 - playImg.size.height/2 ,
                                      playImg.size.width,
                                      playImg.size.height)];
    [self.playBtn setBackgroundImage:[pauseImg imageWithBrightness:-0.5]  forState:UIControlStateSelected|UIControlStateHighlighted];
    [self.playBtn setSelected:YES];
    [self addSubview:self.playBtn];
    [self.playBtn addTarget:self action:@selector(onPlayButtonTouched:) forControlEvents:UIControlEventTouchUpInside];
    [self.playBtn addTarget:self.delegate action:@selector(timerInvalidate) forControlEvents:UIControlEventTouchDown];
}

- (void) onPlayButtonTouched:(id)sender
{
    
    if ([self.delegate getMPMoviePlayer].playbackState == MPMoviePlaybackStatePlaying)
    {
        [self.delegate pause];
    }else{
        [self.delegate play];
    }
    
    [self setPlayButtonState];
    //timer
    [self.delegate onTimerForTouch];
}


- (void) setPlayButtonState
{
    if ([self.delegate getMPMoviePlayer].playbackState == MPMoviePlaybackStatePlaying)
    {
        self.playBtn.selected = YES;    //to pause icon
    }else{
        self.playBtn.selected = NO;     //to play icon
    }
    
}

- (void)setSlider
{
    float customScale = 1;
    if ( [[[UIDevice currentDevice] model] isEqualToString:@"iPhone"] )
    {
        customScale = CUSTOM_SCALE_VALUE;
    }
    
    
    UIImage *bgImage = [UIImage imageNamed:@"cjplatform_video_seekbar_bg.png"];
    bgImage = [AppController resizingWithImageForScaleFactor:bgImage customScale:customScale];
    
    UIImageView *_imgProgressBg = [[[UIImageView alloc]initWithImage:bgImage] autorelease];
    [_imgProgressBg setFrame:CGRectMake(self.bounds.size.width/2 - bgImage.size.width/2,
                                        self.bounds.size.height - (bgImage.size.height *1.5),
                                        bgImage.size.width,
                                        bgImage.size.height)];
    [_imgProgressBg setUserInteractionEnabled:true];
    
    
    
    //set progress
    UIImage *progressImg =[UIImage imageNamed:@"cjplatform_video_seekbar_progress_bg.png"];
    progressImg = [AppController resizingWithImageForScaleFactor:progressImg customScale:customScale];

    CGRect sliderFrame = CGRectMake(_imgProgressBg.bounds.size.width/2 - (progressImg.size.width/2),
                             _imgProgressBg.bounds.size.height/2 - (progressImg.size.height/2) ,
                             progressImg.size.width,
                             progressImg.size.height);
    
    self.customSlider = [[CJCustomSlider alloc]initWithFrame:sliderFrame];
    self.customSlider.videoController = self;
    
    
    //seek controller
    UIImage *ninePatch = [UIImage imageNamed:@"cjplatform_video_seekbar_progress.png"];
    ninePatch = [AppController resizingWithImageForScaleFactor:ninePatch customScale:customScale];
    [self.customSlider setMinimumTrackImage:[ninePatch
                                        resizableImageWithCapInsets:UIEdgeInsetsMake(ninePatch.size.height/2,
                                                                                     ninePatch.size.width/2,
                                                                                     ninePatch.size.height/2,
                                                                                     ninePatch.size.width/2)] forState:UIControlStateNormal];
    
    [self.customSlider setMaximumTrackImage:progressImg forState:UIControlStateNormal];
    
    
    
    
    UIImage* thumbImg = [UIImage imageNamed:@"cjplatform_video_seekbar_thumb.png"];
    thumbImg = [AppController resizingWithImageForScaleFactor:thumbImg customScale:customScale];
    [self.customSlider setThumbImage:thumbImg forState:UIControlStateNormal];
    [self.customSlider setUserInteractionEnabled:true];
    [self.customSlider addTarget:self.customSlider action:@selector(SliderTouchDownEventDelegate) forControlEvents:UIControlEventTouchDown];
    [self.customSlider addTarget:self.customSlider action:@selector(SliderTouchMoveEventDelegate) forControlEvents:UIControlEventTouchDragInside];
    [self.customSlider addTarget:self.customSlider action:@selector(SliderTouchUpEventDelegate) forControlEvents:UIControlEventTouchDragOutside];
    [self.customSlider addTarget:self.customSlider action:@selector(SliderTouchUpEventDelegate) forControlEvents:UIControlEventTouchUpOutside];

    
    [self addSubview:_imgProgressBg];
    [_imgProgressBg addSubview:self.customSlider];

   
}

-  (void)setTotalProgress:(float)totalTime
{
    [self.customSlider setMinimumValue:0.0f];
    [self.customSlider setMaximumValue:totalTime];
    [self customControllerSliderStart];
}

- (void) customControllerSliderPause
{
    if (self.timer != nil) {
        [self.timer invalidate];
        self.timer = nil;
    }
}

- (void) customControllerSliderStart
{
    if (self.timer == nil) {
        self.timer = [NSTimer scheduledTimerWithTimeInterval:1
                                                      target:self
                                                    selector:@selector(updateSliderValue:)
                                                    userInfo:nil
                                                     repeats:YES];
    }
}

- (void) updateSliderValue:(id)sender
{
    [self.customSlider setValue:[self.delegate getMPMoviePlayer].currentPlaybackTime];
    NSLog(@" currentPlaybackTime = %f", [self.delegate getMPMoviePlayer].currentPlaybackTime);
}


@end


#pragma mark - CJCustomSlider

@implementation CJCustomSlider

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    
    UITouch *touch = [[event allTouches] anyObject];
    CGPoint touchPoint = [touch locationInView:self];
    
    playerState = [self.videoController.delegate getMPMoviePlayer].playbackState;
    
    float value = (touchPoint.x * self.maximumValue) / self.frame.size.width;
    [self setValue:value];
    [self.videoController.delegate pause];
    [[self.videoController.delegate getMPMoviePlayer] setCurrentPlaybackTime:value];
    [self.videoController customControllerSliderPause];
    
    //timer
    [self.videoController.delegate timerInvalidate];
    
}
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    
    UITouch *touch = [[event allTouches]anyObject];
    CGPoint touchPoint = [touch locationInView:self];
    float value = (touchPoint.x * self.maximumValue) / self.frame.size.width;
    [self setValue:value];
    
    [[self.videoController.delegate getMPMoviePlayer] setCurrentPlaybackTime:(NSTimeInterval)value];
    


    
}
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    if (playerState == MPMoviePlaybackStatePlaying) {
        [self.videoController.delegate play];
    }
    [self.videoController customControllerSliderStart];
    
    //timer
    [self.videoController.delegate onTimerForTouch];
}

@end

#endif