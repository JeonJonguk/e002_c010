//
//  E002_Base_P520_Recording.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 5. 31..
//
//

#ifndef SoundPhonics_Template_E002_Base_P520_Recording_h
#define SoundPhonics_Template_E002_Base_P520_Recording_h


#include "cocos2d.h"
#include "CJLayer.h"
#include "CJAnimationManager.h"

using namespace cocos2d;


class E002_Base_P520_Recording : public CJLayer, public CJAnimationManager {
    
protected:
    CCDictionary*                   m_psdDictionary;                // psd를 파싱할 딕셔너리
    
    std::vector<string>             m_vSubtitlesFileName;
    std::vector<float>              m_vSubtitlesDelays;
    
    CCMenu*                         menu;
    CJSprite*                       m_subtitle;
    
    //camera
    std::string                     mCameraFrameImg;
    float                           mCameraPositionX;
    float                           mCameraPositionY;
    float                           mCameraWidth;
    float                           mCameraHeight;
    std::string                     m_recordedVideoFile;
    
    std::string                     m_musicFileName;
    
private:
    int                             _nSubtitlesIndex;
    bool                            _bIsRecordingStarted;
    float                           _hideCameraXposition;
    
public:
    ~E002_Base_P520_Recording();
    E002_Base_P520_Recording();

    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual void onViewLoad();
    virtual void onViewLoaded();
    
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual bool onTouchBegan(CCPoint tp){return false;};
    virtual void onTouchMoved(CCPoint tp){};
	virtual void onTouchEnded(CCPoint tp){};
    
    virtual void onNarrationFinishedCallback(std::string fileName);
    virtual void onVideoFrameFinishedCallback();
    
    CREATE_FUNC(E002_Base_P520_Recording);

    void setMenuNavigation();
    virtual void onTouchedMenuAtSongMenu();
    virtual void startMusic(std::string pMusicFileName);
    virtual void startRecordedVideo();
    
    void setCameraSetting(std::string frameImg, int x, int y,  int width, int height);
    void removeVideoView();
    
    void startRecordingVideo();
    void stopRecordingVideo();
    void onVideoRecordingFinished(CCString* fileName);
    void onPauseVideoRecording();
    void playFrameVideoview();
    
    void playSubtitles();
    void addSubtitles();
    virtual void completeSubtitles();
    
    virtual void onComplete();
    
    void setSingUserDefaultValue(int pValue);
    
    
    void speakerAnimation(CCNode* node);
    void lightingColorAnimation(CCNode* node);
    void lightRotateAnimation(CCNode* node, float r1, float r2);
};


#endif
