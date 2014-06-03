/*
 * CCVideoPlayer
 *
 * cocos2d-extensions
 * https://github.com/cocos2d/cocos2d-iphone-extensions
 *
 * Copyright (c) 2010-2011 Stepan Generalov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED
#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayer.h>


@protocol cjVideoControllerDelegate <NSObject>
@required
-(MPMoviePlayerController*) getMPMoviePlayer;
-(void) pause;
-(void) play;
@optional
-(void) stop;
-(void) onTimerForTouch;
-(void) timerInvalidate;
@end



@class CJCustomSlider;
@interface CJVideoController : UIView  {
//    CJCustomSlider* customSlider;
}
@property(nonatomic, retain) UIButton* playBtn;
@property(nonatomic, retain) NSTimer *timer;
@property(nonatomic, assign) id<cjVideoControllerDelegate> delegate;
@property(nonatomic, retain) CJCustomSlider* customSlider;

- (void) setPlayButtonState;
- (void) onPlayButtonTouched:(id)sender;
- (void) setTotalProgress:(float)totalTime;
- (void) customControllerSliderPause;
- (void) customControllerSliderStart;
- (void) updateSliderValue:(id)sender;
@end


//==============================================================

@interface CJCustomSlider : UISlider
{
    MPMoviePlaybackState playerState;
}
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;

@property(nonatomic , retain)CJVideoController *videoController;
@end

#endif