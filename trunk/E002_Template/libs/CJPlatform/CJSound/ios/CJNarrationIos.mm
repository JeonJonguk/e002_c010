//
//  CJNarrationIos.m
//  SoundPhonics_Template
//
//  Created by SangSeong Lee on 6/20/13.
//
//

#import "CJNarrationIos.h"
#import "CJNarrationSound.h"

@implementation CJNarrationIos
@synthesize strCurrentFileName = _strCurrentFileName;
@synthesize player = _player;

-(id)init
{
    self = [super init];
    
    if(self)
    {
         self.strCurrentFileName = @"";
    }
    
    return self;
}

-(void) dealloc
{
    NSLog(@" CJNarration ios dealloc");
//    self.strCurrentFileName = nil;
    if (self.player) {
        [self.player release];
        self.player = nil;
    }
    [super dealloc];
}

- (NSString *)fullPathFromRelativePath:(NSString*)relativePath
{
    if(([relativePath length] > 0) && ([relativePath characterAtIndex:0] == '/'))
    {
        return relativePath;
    }
    
    NSMutableArray *imagePathComponents = [NSMutableArray arrayWithArray:[relativePath pathComponents]];
    NSString *file = [imagePathComponents lastObject];
    
    [imagePathComponents removeLastObject];
    NSString *imageDirectory = [NSString pathWithComponents:imagePathComponents];
    
    NSString *fullpath = [[NSBundle mainBundle] pathForResource:file ofType:nil inDirectory:imageDirectory];
    if (fullpath == nil)
    {
        fullpath = relativePath;
    }
    
    return fullpath;
}



- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag;
{
    
//	NSLog(@"be audio player did finish");
	if(self.strCurrentFileName )
	{
//        NSLog(@"audio player did finish = %@",self.strCurrentFileName);
        CJNarrationSound::getInstance()->onVoiceCallBack([self.strCurrentFileName UTF8String] );
    }
}

-(void)preloadNarration:(std::string)fileName
{
    self.strCurrentFileName = [NSString stringWithUTF8String:fileName.c_str()] ;
    
//    NSString* path = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:fileName] ofType:nil];
    NSString *path = [self fullPathFromRelativePath:[NSString stringWithUTF8String:fileName.c_str()]];

    if ([[NSFileManager defaultManager] fileExistsAtPath:path])
    {
        NSURL* url = [NSURL fileURLWithPath:path];
        NSError *error;
        self.player = [[CJNarrationPlayer alloc] initWithContentsOfURL:url error:&error];
        if (error) {
            NSLog(@"preload narration error = %@",error);
        }
        [self.player prepareToPlay];
    }
}

-(void)playNarration:(std::string)fileName
{
    self.strCurrentFileName = [NSString stringWithUTF8String:fileName.c_str()];

//    NSString* path = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:fileName] ofType:nil];
    NSString *path = [self fullPathFromRelativePath:[NSString stringWithUTF8String:fileName.c_str()]];
    
    if ([[NSFileManager defaultManager] fileExistsAtPath:path])
    {
        NSURL* url = [NSURL fileURLWithPath:path];
        NSError *error;

        if(!self.player)
        {
            self.player = [[CJNarrationPlayer alloc] initWithContentsOfURL:url error:&error];
            self.player.delegate = self;
            if (error) {
                NSLog(@"play narration error = %@",error);
            }
            [self.player prepareToPlay];
        }
        
        [self.player play];
    }
}

-(void)playNarration:(std::string)fileName isLooping:(bool)bValue
{
    self.strCurrentFileName = [NSString stringWithUTF8String:fileName.c_str()];
    
//    NSString* path = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:fileName] ofType:nil];
    NSString *path = [self fullPathFromRelativePath:[NSString stringWithUTF8String:fileName.c_str()]];

    if ([[NSFileManager defaultManager] fileExistsAtPath:path])
    {
        NSURL* url = [NSURL fileURLWithPath:path];
        NSError *error;
        
        if(!self.player)
        {
            self.player = [[CJNarrationPlayer alloc] initWithContentsOfURL:url error:&error];
            if (error) {
                NSLog(@"play narration error = %@",error);
            }
            self.player.delegate = self;
            [self.player setNumberOfLoops:bValue*-1];
            [self.player prepareToPlay];
            if (error) {
                NSLog(@"play narration error = %@",error);
            }
        }
        
        [self.player play];
    }
}

-(void)pauseNarration:(std::string)fileName
{
    if(self.player != nil && [self.player isPlaying])
    {
        [self.player pause];
    }
}

-(void)resumeNarration:(std::string)fileName
{
    if(self.player != nil)
        [self.player play];
}

-(void)stopNarration:(std::string)fileName
{
    if(self.player != nil)
        [self.player stop];
}

-(bool)isNarrationPlaying
{
    return [self.player isPlaying];
}

-(float)getNarrationCurrentPosition:(std::string) filePath;
{
    float duration = 0.0;
    duration = [self.player currentTime];
    return duration;
}

-(float)getNarrationTime:(std::string) filePath;
{
    float time = 0.0;
    time = [self.player duration];
    return time;
}


#pragma mark - AudioPlayer Custom Callback
- (void) audioPlayerDidPlay:(CJNarrationPlayer*)audioPlayer
{
    CJNarrationSound::getInstance()->audioPlayerCallbackPlay(audioPlayer);
}

- (void) audioPlayerDidPause:(CJNarrationPlayer*)audioPlayer
{
    CJNarrationSound::getInstance()->audioPlayerCallbackPause(audioPlayer);
}

- (void) audioPlayerDidStop:(CJNarrationPlayer*)audioPlayer
{
    CJNarrationSound::getInstance()->audioPlayerCallbackStop(audioPlayer);
}

#pragma -
#pragma mark - Volume
-(float)getNarrationVolume
{
    return [self.player volume];
}

-(void)setNarrationVolume:(float)fvolume    
{
    [self.player setVolume:fvolume];
}

#pragma mark - UnloadPlayer
-(void)unloadPlayer
{
    if (self.player) {
        [self.player stop];
        self.player.delegate = nil;
        [self.player release];
        self.player = nil;
    }
//    [self release];
}

-(std::string)getFileName
{
    return [self.strCurrentFileName UTF8String];
}

@end

@implementation  CJNarrationPlayer
@synthesize callback = _callback;
- (BOOL)prepareToPlay
{
    [super prepareToPlay];

    return true;
}

- (BOOL)play
{

    [super play];
    [self.callback audioPlayerDidPlay:self];
    return true;
}

- (void)pause
{
    if([self isPlaying])
    [super pause];
    
    [self.callback audioPlayerDidPause:self];
}

- (void)stop
{
    [super stop];
    [self.callback audioPlayerDidStop:self];
}

- (void)resume
{
    if(![self isPlaying])
    {
        [super play];
    }
}

@end
