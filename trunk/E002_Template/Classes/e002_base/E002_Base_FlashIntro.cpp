//
//  E002_Base_FlashIntro.cpp
//  E002_Template
//
//  Created by Jeong.YJ on 2014. 2. 24..
//
//

#include "E002_Base_FlashIntro.h"
#include "E002_Base_Define.h"

enum {
    kTagPlayBtn = 999,
};


E002_Base_FlashIntro::E002_Base_FlashIntro()
{
    mAnimationNames = new std::vector<const char*>();
    mNarrationNames = new std::vector<E002_Base_FlashIntro_Sound_Item*>();
    mEffectNames = new std::vector<E002_Base_FlashIntro_Sound_Item*>();
    
    mCurrentCut = 0;
    mIsTouch = false;
}

E002_Base_FlashIntro::~E002_Base_FlashIntro()
{
    SAFE_DELETE(mAnimationNames);
    SAFE_DELETE(mNarrationNames);
}


#pragma mark - init()

bool E002_Base_FlashIntro::init()
{
    if (!CJLayer::init()){
        return false;
    }
    
    return true;
}

void E002_Base_FlashIntro::onEnter()
{
    CJLayer::onEnter();
}

void E002_Base_FlashIntro::onExit()
{
    removeSoundObserver();
    stopTimer();
   //CJMultimedia::getInstance()->stopBGM();
    CJLayer::onExit();
}

#pragma mark - view load

void E002_Base_FlashIntro::onViewLoad()
{
    CJLayer::onViewLoad();
    
    setAnimationParent(this);
    createBtns();
}

void E002_Base_FlashIntro::onViewLoaded()
{
    CJLayer::onViewLoaded();
    
    E002_Base_Navigation::initWithNavigationType(this, "",
                                                 eNavigationType_Intro);
    E002_Base_Navigation::showNavigation();
    addSoundObserver();
}

#pragma mark - touch
bool E002_Base_FlashIntro::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint tp = pTouch->getLocation();
    
    CJSprite *sp = (CJSprite*)getChildByTag(kTagPlayBtn);
    
    if(CJUtils::hitTestPoint(sp, tp, false))
    {
        if(mIsTouch)
        {
            return false;
        }
        
        mIsTouch = true;
        mCurrentCut++;
        
        if(mCurrentCut == mAnimationNames->size())
        {
            setTouchEnabled(false);
            onFlashIntroCompletedCallback();
            
            return false;
        }
        
        startAnimation();
    }
    
    return false;
}

void E002_Base_FlashIntro::setCutAnimationName(const char* animation, ...)
{
    va_list args;
    va_start(args,animation);
    
    while (animation != NULL) {
        
        CCLog("animation = %s", animation);
        mAnimationNames->push_back(animation);
        
        animation = va_arg(args, const char*);
    }
    
    va_end(args);
}

void E002_Base_FlashIntro::setEnableTouch()
{
    mIsTouch = false;
}

void E002_Base_FlashIntro::startAnimation()
{
    runAction(CCSequence::create(CCDelayTime::create(2.0f),
                                 CCCallFunc::create(this, callfunc_selector(E002_Base_FlashIntro::setEnableTouch)),
                                 NULL));
    stopAllNarration();
    removeAllAnimations();
    mPlayBtn->stopAllActions();
    mPlayBtn->setOpacity(255);
    
    mCurrentAnimation = playAnimation(FLASH_INTRO_DATEPOOL_KEY, mAnimationNames->at(mCurrentCut), 1, kDepth1_flash);

    for (int i = 0; i < mNarrationNames->size(); i++)
    {
        if(mCurrentAnimation->getName() == mNarrationNames->at(i)->getAniName())
        {
            addNarrationOnFlashFrame(mCurrentAnimation, mNarrationNames->at(i)->getFrame(), getFilePath("snd", mNarrationNames->at(i)->getSndName()).c_str());
        }
    }
    
    for (int i = 0; i < mEffectNames->size(); i++)
    {
        if(mCurrentAnimation->getName() == mEffectNames->at(i)->getAniName())
        {
            addEffectOnFlashFrame(mCurrentAnimation, mEffectNames->at(i)->getFrame(), getFilePath("snd", mEffectNames->at(i)->getSndName()).c_str());
        }
    }
}

void E002_Base_FlashIntro::animationManagerParseComplete()
{
    createAllAnimations();
//    startAnimation();
    CJUtils::performSelector(this, callfunc_selector(E002_Base_FlashIntro::startAnimation), 0.5f);
}

void E002_Base_FlashIntro::OnLastFrame(CJFlash::CJAnimation *pAnimation)
{
    mPlayBtn->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.4f),
                                                                   CCFadeOut::create(0.4f),
                                                                   NULL)));
}

void E002_Base_FlashIntro::createBtns()
{
    mPlayBtn = CJSprite::create(getCommonFilePath("img","e002_common_intro_flash_btn.png").c_str());;
    mPlayBtn->setPosition(ccp(winSize.width - 100, 100));
    addChild(mPlayBtn, kDepth4_title, kTagPlayBtn);
}

void E002_Base_FlashIntro::setNarrationOnFrame(std::string aniName, int frame, std::string sndPath)
{
    mNarrationNames->push_back(new E002_Base_FlashIntro_Sound_Item(aniName, frame, sndPath));
}

void E002_Base_FlashIntro::setEffectOnFrame(std::string aniName, int frame, std::string sndPath)
{
    mEffectNames->push_back(new E002_Base_FlashIntro_Sound_Item(aniName, frame, sndPath));
}
