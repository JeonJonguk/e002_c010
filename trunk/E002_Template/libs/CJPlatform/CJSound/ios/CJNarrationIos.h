//
//  CJNarrationIos.h
//  SoundPhonics_Template
//
//  Created by SangSeong Lee on 6/20/13.
//
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <AVFoundation/AVAudioPlayer.h>
//#include "cocos2d.h"
#import <iostream>

@class CJNarrationPlayer;

@protocol CustomAVAudioPlayerDelegate <NSObject>
@required
- (void) audioPlayerDidPlay:(CJNarrationPlayer*)audioPlayer;
- (void) audioPlayerDidPause:(CJNarrationPlayer*)audioPlayer;
- (void) audioPlayerDidStop:(CJNarrationPlayer*)audioPlayer;

@end

@interface CJNarrationIos : NSObject <AVAudioPlayerDelegate, CustomAVAudioPlayerDelegate>
{
    CJNarrationPlayer *_player;
    NSString *_strCurrentFileName;
}

@property (nonatomic, retain) CJNarrationPlayer *player;
@property (nonatomic, retain) NSString *strCurrentFileName;

-(id)init;
-(void)preloadNarration:(std::string)fileName;
-(void)playNarration:(std::string)fileName;
-(void)playNarration:(std::string)fileName isLooping:(bool)bValue;
-(void)pauseNarration:(std::string)fileName;
-(void)resumeNarration:(std::string)fileName;
-(void)stopNarration:(std::string)fileName;
-(bool)isNarrationPlaying;
-(std::string) getFileName;
-(float)getNarrationVolume;
-(void)setNarrationVolume:(float)fvolume ;
-(void)unloadPlayer;
- (void)dealloc;


-(float)getNarrationCurrentPosition:(std::string) filePath;
-(float)getNarrationTime:(std::string) filePath;

@end

@interface CJNarrationPlayer : AVAudioPlayer
{
    id<CustomAVAudioPlayerDelegate> _callback;
}
- (BOOL)prepareToPlay;
- (BOOL)play;
- (void)pause;
- (void)stop;
@property (nonatomic, assign) id<CustomAVAudioPlayerDelegate> callback;
@end






