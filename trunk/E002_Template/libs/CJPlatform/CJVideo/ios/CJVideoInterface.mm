//
//  CJVideoInterface.cpp
//  CJTemplate
//
//  Created by Dongjin Park on 13. 1. 2..
//
//

#include "CJVideoInterface.h"
#include "CJDefines.h"
#include "CJVideoPlayer.h"
#include "AppController.h"


static CJVideoInterface *s_pCJVideoInterface;
//static CJVideoPlayer *moviePlayer = NULL;

CJVideoInterface::CJVideoInterface()
{
}

CJVideoInterface::~CJVideoInterface()
{
    
}

CJVideoInterface* CJVideoInterface::getInstance()
{
    if (! s_pCJVideoInterface)
    {
        s_pCJVideoInterface = new CJVideoInterface();
    }
    
    return s_pCJVideoInterface;
}


#pragma mark - defualt video play

void CJVideoInterface::playVideo(std::string filePath , bool isController)
{
    CJVideoType _type = isController ? CJVideoTypeCJVideo : CJVideoTypeSkip;
    
    CGSize s;
    if (UIInterfaceOrientationIsLandscape(UIApplication.sharedApplication.statusBarOrientation)) {
        s = CGSizeMake(std::max<float>(UIScreen.mainScreen.bounds.size.width, UIScreen.mainScreen.bounds.size.height),
                       std::min<float>(UIScreen.mainScreen.bounds.size.width, UIScreen.mainScreen.bounds.size.height));
    } else {
        s = CGSizeMake(std::min<float>(UIScreen.mainScreen.bounds.size.width, UIScreen.mainScreen.bounds.size.height),
                       std::max<float>(UIScreen.mainScreen.bounds.size.width, UIScreen.mainScreen.bounds.size.height));
    }
    
    
    NSString *pathForTheFile = [NSString stringWithUTF8String:fullPathFromRelativePath(filePath).c_str()];
    if ([[NSFileManager defaultManager] fileExistsAtPath:pathForTheFile])
    {
        NSURL *fileURL = [NSURL fileURLWithPath:pathForTheFile];
        [[CJVideoPlayer getInstance] initWithPath:fileURL frame:CGRectMake(0, 0, s.width, s.height) type:_type];
    }else{
        NSLog(@"__video file no exist!");
    }

    [[CJVideoPlayer getInstance] play];
    
}


void CJVideoInterface::pauseVideo()
{
    [[CJVideoPlayer getInstance] pause];
}
void CJVideoInterface::resumeVideo()
{
     [[CJVideoPlayer getInstance] resume];
}

void CJVideoInterface::stopVideo()
{
    [[CJVideoPlayer getInstance] stop];
    [[CJVideoPlayer getInstance].view removeFromSuperview];
    [CJVideoPlayer releaseInstance];

}


#pragma mark - frame video play
void CJVideoInterface::playFrameVideo(std::string frameImgPath, std::string contentPath, int x,int y,int width,int height)
{
    //multi resolution
    x = x * [AppController getScaleValue] + [AppController getLetterBoxPositionX];
    y = y * [AppController getScaleValue];
    width = width * [AppController getScaleValue];
    height = height * [AppController getScaleValue];
    
    
    NSString *pathForTheFile = [NSString stringWithUTF8String:fullPathFromRelativePath(contentPath).c_str()];
    if ([[NSFileManager defaultManager] fileExistsAtPath:pathForTheFile])
    {
        NSURL *fileURL = [NSURL fileURLWithPath:pathForTheFile];
        [[CJVideoPlayer getInstance] initWithPath:fileURL frame:CGRectMake(x, y, width, height) type:CJVideoTypeFrameVideo];
    }else{
        NSLog(@"__video file no exist!");
    }
    [[CJVideoPlayer getInstance] addVideoMask:[NSString stringWithUTF8String:frameImgPath.c_str()]];
    [[CJVideoPlayer getInstance] play];
    
}

void CJVideoInterface::removeFrameVideo()
{
    stopVideo();
}



void CJVideoInterface::addVideoBtn(std::string btnPath, float x, float y, int tag)
{
    [[CJVideoPlayer getInstance] addVideoBtn:btnPath.c_str() posX:x posY:y iTag:tag];
}

void CJVideoInterface::onButtonTouch(int tag)
{
    CCNotificationCenter::sharedNotificationCenter()->postNotification(CJNOTIFICATION_VIDEO_BUTTONCALL, (CCObject*)tag);
    
}


#pragma only ios



std::string CJVideoInterface::fullPathFromRelativePath(std::string relativePath)
{
    NSString *pathForTheFile;
    
    if(relativePath.find("/")==-1)
    {
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,
                                                             NSUserDomainMask, YES);
        NSString *documentsDirectory = [paths objectAtIndex:0];
        pathForTheFile= [documentsDirectory stringByAppendingPathComponent:[NSString stringWithUTF8String:relativePath.c_str()]];
    }
    else
    {
        pathForTheFile = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:relativePath.c_str()] ofType:nil];
        
    }

    return [pathForTheFile UTF8String];
}
