//
//  CJ_RecorderIos.h
//  S001-C130
//
//  Created by SangSeong Lee on 6/17/13.
//  Copyright (c) 2013 CJ Educations. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <AVFoundation/AVAudioPlayer.h>

@interface CJ_RecorderIos : NSObject <AVAudioPlayerDelegate>
{
    AVAudioRecorder *recorder;
    NSURL *inUrl;
    
    AVAudioPlayer *player;
    
    NSError *error;
    
    NSString *m_strPlayFileName;
    
    __block BOOL bEnableRECSession;
}


-(void) setRecSession;
-(BOOL) getRecSession;
-(void) readyRec:(const char*) file;
-(void) startRec;
-(void) pauseRec;
-(void) stopRec;
-(float) playRecordFile:(const char*) file;
-(void) pauseRecordFile;
-(void) resumeRecordFile;
-(void) stopRecordFile;
@end
