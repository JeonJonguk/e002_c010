

#pragma once

#include "cocos2d.h"  

namespace CameraTestTag
{
    enum {
        TagBG = 100,
        TagCameraBtn = 101,
        TagVideoBtn = 102,
        TagStartBtn = 103,
    };
}

USING_NS_CC;

const int CAMERA_MODE = 0;
const int VIDEO_MODE = 1;

class CameraTest : public CCLayer
{
public:
    cocos2d::CCSize winSize;
 
	virtual bool init();
     
	static cocos2d::CCScene* scene();
    
    CCDictionary *readPointXml;
    CCDictionary *readPopupXml;

    virtual void onEnter();
    virtual void onExit();

    void makeBtn();
    
    bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	void ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
 
    CREATE_FUNC(CameraTest);
    
    void onCameraFinished(CCString* fileName);
    void onVideoRecordingFinished(CCString* fileName);
    void onFrameVideoFinished();
    void onBtnTouch(CCObject* tag);
    
private:

    int currentMode;
    bool isRecording;
    bool isCompleteRecording;
    std::string recordedVideoFile;
    
    void showCamera();
    void takePicture();
    void startRecording();
    void stopRecording();
    void playFrameVideoview();
};

 
