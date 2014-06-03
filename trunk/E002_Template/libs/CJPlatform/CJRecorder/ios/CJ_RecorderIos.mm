//
//  CJ_RecorderIos.m
//  S001-C130
//
//  Created by SangSeong Lee on 6/17/13.
//  Copyright (c) 2013 CJ Educations. All rights reserved.
//

#import "CJ_RecorderIos.h"
#import "CJVoiceRecorderInterface.h"

@implementation CJ_RecorderIos


-(id)init
{
    self = [super init];
    if(self)
    {
        bEnableRECSession = NO;
    }
    return  self;
}
-(void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag
{
    CJVoiceRecorderInterface::getInstance()->stopRecordPlayCallBack();
}

-(BOOL) getRecSession
{
    return bEnableRECSession;
}

-(void) setRecSession
{
    [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayAndRecord error:nil];

    // if iOS7 availeable.
    if ([[AVAudioSession sharedInstance] respondsToSelector:@selector(requestRecordPermission:)])
    {
        [[AVAudioSession sharedInstance] performSelector:@selector(requestRecordPermission:) withObject:^(BOOL granted) {
            bEnableRECSession = granted;
        }];
    }
    // if iOS6 Under.
    else
    {
        bEnableRECSession = YES;
    }
    
    [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryAmbient error:nil];
}

-(void) readyRec:(const char*) file
{
    [self setRecSession];
    [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayAndRecord error:nil];

    if(YES == [self getRecSession])
    {
        NSMutableDictionary* recordSetting = [[NSMutableDictionary alloc] init];
        [recordSetting setValue :[NSNumber numberWithInt:kAudioFormatAppleIMA4] forKey:AVFormatIDKey];
        [recordSetting setValue:[NSNumber numberWithFloat:44100.0] forKey:AVSampleRateKey];
        [recordSetting setValue:[NSNumber numberWithInt: 1] forKey:AVNumberOfChannelsKey];
        
        NSArray* documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
        NSString* fullFilePath = [[documentPaths objectAtIndex:0] stringByAppendingPathComponent: [NSString stringWithUTF8String:file]];
        inUrl = [NSURL fileURLWithPath:fullFilePath];
        
        recorder = [[ AVAudioRecorder alloc] initWithURL: inUrl settings:recordSetting error:&error];
        [recorder prepareToRecord];
    }
}

-(float) playRecordFile:(const char* )file
{
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();


    NSArray* documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString* fullFilePath = [[documentPaths objectAtIndex:0] stringByAppendingPathComponent: [NSString stringWithUTF8String:file]];
    NSURL* fileUrl = [NSURL fileURLWithPath:fullFilePath];
    m_strPlayFileName = fullFilePath;
    player = [[AVAudioPlayer alloc] initWithContentsOfURL: fileUrl error:&error];
    [player prepareToPlay];
    [player setVolume:8];
    [player play];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(stopRecordFile)
                                                 name:AVPlayerItemDidPlayToEndTimeNotification
                                               object:nil];
    player.delegate = self;
    
    return (float)[player duration];
    

    
}
-(void) resumeRecordFile
{
    if(![player isPlaying])
    {
        [player play];
    }
}
-(void) pauseRecordFile
{
    if([player isPlaying])
    {
        [player pause];
    }
}
-(void) stopRecordFile
{

    [player stop];
    [player release];
     player  = nil;

    
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

-(void) stopRec
{
    [recorder stop];
    [recorder release];
    recorder = nil;
    [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryAmbient error:nil];
    
}

-(void) pauseRec
{

    [recorder pause];

    
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

-(void) startRec
{
    if(YES == [self getRecSession])
    {
        if (!recorder.recording)
        {
            [recorder record];
        }
    }
}
@end
