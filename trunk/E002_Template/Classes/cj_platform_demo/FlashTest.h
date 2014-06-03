

#include "cocos2d.h" 
#include "SimpleAudioEngine.h"

#include "../../libs/CJPlatform/CJAnimationLibrary/CJFlashAnimation/CJAnimationManager.h"


namespace FlashTestTag
{
    enum {
        TagBG = 100,
        
    };
}

USING_NS_CC;     
using namespace CocosDenshion;

class FlashTest : public CCLayer, public CJAnimationManager
{
public:
    cocos2d::CCSize winSize;
    
    CJAnimationDataPool* datapool;
    
    CCLayerColor* layer;
    
    CCSprite *mBtn;
    int stagecount;
    
	virtual bool init();
     
	static cocos2d::CCScene* scene();


    virtual void onEnter();
    virtual void onExit();

    
    bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	void ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
 
    CREATE_FUNC(FlashTest);
    
    virtual void OnPlay(CJAnimation* pAnimation);
    virtual void OnStop(CJAnimation* pAnimation);
    virtual void OnLastFrame(CJAnimation* pAnimation);
    virtual void OnPause(CJAnimation* pAnimation);
    virtual void OnUpdate(CJAnimation* pAnimation);
    
    
    void loadingCallback();
    void play();

    void play1();
    void play1btn();
    void play2();
    void play2btn();
    void play3();
    void play3btn();
    void play4();
    void play4btn();
    
    
public:
    virtual void animationManagerParseComplete();
    
};

 
