//
//  CJLayer.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 5. 31..
//
//

#ifndef SoundPhonics_Template_CJLayer_h
#define SoundPhonics_Template_CJLayer_h


#include "cocos2d.h"
#include "CJSprite.h"
#include "CJUtils.h"
#include "CJMultimedia.h"
#include "CJMacros.h"
#include "CJPsdParser.h"

using namespace cocos2d;


typedef enum{
    kDepth0_background      = 0,
    kDepth0_backImage       = 5,
    kDepth1_actors          = 10,
    kDepth1_flash           = 15,
    kDepth2_questions       = 20,
    kDepth3_examples        = 30,
    kDepth4_title           = 40,
    kDepth5_particle        = 50,
    kDepth6_dimmed          = 60,
    kDepth8_menu            = 80,
    kDepth9_navigations     = 90,
    kDepth7_popup           = 95,
    kDepth10_guide          = 100,
    kDepth11_Index          = 110,
    
}eCJLayerDepth;

typedef enum{
    kActionTag00            = 0,
    kActionTag01            = 10,
    kActionTag02            = 20,
    kActionTag03            = 30,
    kActionTag04            = 40,
}eCJActionTag;


class CJLayer : public CCLayerColor {
    
public:
    
    CCSize      winSize;
    CCSize      winHalfSize;
	CCPoint     winCenter;

protected:
    bool                            m_bIsCompleteTransition;
    bool                            m_bIsCompleteFlashParsing;
    
private:
    // scheduler time
    int                           _currentTime;
    
public:
    ~CJLayer();
    CJLayer();
    
    static CJLayer* create(const ccColor4B& color);
    static CJLayer * create(const ccColor4B& color, GLfloat width, GLfloat height);
    
    virtual bool init();
    virtual bool initWithColor(const ccColor4B& color);
    virtual bool initWithColor(const ccColor4B& color, GLfloat w, GLfloat h);
    
    virtual void onEnter();
    void         onEnterTransitionDidFinish();
    virtual void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

    virtual void onViewLoad();
    virtual void onViewLoaded();
    
    virtual void addChild(CCNode *child, int zOrder, int tag);
    virtual void addChild(CCNode *child, int zOrder);
    virtual void addChild(CCNode *child);
    
    CREATE_FUNC(CJLayer);
    
    void setBackgroundColor(const ccColor4B& color);

#pragma mark - getPath
protected:
    std::string getFilePath(std::string path);
    std::string getFilePath(string strFolderName, std::string strFileName);
    
    std::string getCommonFilePath(std::string path);
    std::string getCommonFilePath(string strFolderName, std::string strFileName);

    std::string getSoundFilePath(std::string path);
    std::string getImageFilePath(std::string path);
    
#pragma mark - sound
protected:
    void playNarration(std::string fileName, bool bLoop = false);
    void playCommonNarration(std::string fileName, bool bLoop = false);
    void playNarrationWithDelay(std::string fileName, float delay);
    void playCommonNarrationWithDelay(std::string fileName, float delay);

    
    unsigned int playEffect(std::string fileName, bool bLoop = false);
    unsigned int playCommonEffect(std::string fileName, bool bLoop = false);
    void playEffectWithDelay(std::string fileName, float delay);
    void playCommonEffectWithDelay(std::string fileName, float delay);
    
    void stopNarration(std::string fileName);
    void stopAllNarration();
    void removeAllNarration();
    void stopEffect(int soundId);
    void stopAllEffect();
    
    void addSoundObserver();
    void removeSoundObserver();
    virtual void onNarrationFinishedCallback(std::string fileName);
private:
    void _onNarrationFinishedCallback(CCString *fileName);
    void _onNarrationFinishedCallbackTransformThread(CCNode *sender, const char *fileName);
    
    
#pragma mark - video
protected:
    void addVideoObserver();
    void removeVideoObserver(); 
    virtual void onVideoFinishedCallback();
    virtual void onVideoIndexBtnTouchCallback(CCObject* tag);
    virtual void onVideoBtnTouchCallback(CCObject* tag);
    virtual void onVideoFrameFinishedCallback();
#pragma mark - recording
protected:
    void addRecordingObserver();
    void removeRecordingObserver();
    virtual void onVoiceRecordedPlayFinishedCallback();
    
private:
    void _onVoiceRecordedPlayFinishedCallbackTransformThread();
    
#pragma mark - timer
protected:
    void onTimer();
    void stopTimer();
    float getCurrentTime();
private:
    void _tick();

    
#pragma mark - touch controll
public:
    void setTouchEnableCJLayer(CCNode* sender, bool bDispatchEvents);
    void setTouchEnableCJSprite(CCNode* sender, bool bDispatchEvents);
    std::vector<CJSprite*>  _vTouchEnableCJSprites;
    
#pragma mark - background
private:
    CCSprite                                            *_imgBackground;
    void _setBackground(CCSprite *pSprite);
    
protected:
    /**
     * @author      Lee.YJ
     * @brief       set background sprite image.
     * @version     1.0
     * @param       CCSprite *pSprite : background sprite
     * @return      void
     * @exception
     * @date        2013.02.07
     * @since       2013.02.07
     */
    void setBackground(CCSprite *pSprite);
    void setBackground(std::string strImageName, bool bIsLanguage = false);
    void setBackgroundPosition(CCPoint aPoint);
    void setBackgroundScale(float fScale);
    CCSprite* getBackgroundSprite();

#pragma mark - utils
      
    void removeAllpointArray(CCPointArray* pointArray);
    const char* stringFromRect(CCNode* node);
    
    //test
public:
    virtual void cjMenuTouchBegan(CCTouch *touch, CCEvent* event);
    
protected:
    virtual void setViewLoadedToTransition(bool completeTransition){m_bIsCompleteTransition = completeTransition;};
    virtual void setViewLoadedToParsing(bool completeFlashParsing){m_bIsCompleteFlashParsing = completeFlashParsing;};
};


#endif
