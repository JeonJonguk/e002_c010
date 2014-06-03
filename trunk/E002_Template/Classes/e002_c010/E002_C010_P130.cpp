

#include "E002_C010_P130.h"
#include "E002_C010_BaseUtil.h"
#include "E002_C010_P000_Index.h"
#include "E002_C010_P200_Intro.h"
#include "E002_C010_P110.h"
#include "E002_C010_CompletePopup.h"

#define FLASH_KEY_ACTION1_2     "action1_2"
#define FLASH_KEY_ACTION2_2     "action2_2"
#define FLASH_FIRE              "FIRE"
#define FLASH_KEY_FIRE0         "fire0"
#define FLASH_KEY_FIRE1         "fire1"
#define FLASH_KEY_FIRE2         "fire2"
#define FLASH_KEY_FIRE3         "fire3"
#define FLASH_KEY_FIRE4         "fire4"
#define FLASH_KEY_FIRE5         "fire5"

enum
{
    kTagExample001,
    kTagExample002,
    
    _kTagBg1,
    _kTagBg2,
    _kTagBg3,
    _kTagHighlight,
    
    _kTagBall1,
    _kTagBall2,
    _kTagBall3,
    _kTagBall4,
    _kTagBall5,
    _kTagBall6,
    
    _kTagBall1_back,
    _kTagBall2_back,
    _kTagBall3_back,
    _kTagBall4_back,
    _kTagBall5_back,
    _kTagBall6_back,


};

enum depth{
    _kDepthBackground = kDepth0_background,
    _kDepthBackImage = kDepth0_backImage,
    _kDepthLayer1,
    _kDepthLayer2,
    _kDepthLayer3,
    _kDepthLayer4,

    
};


E002_C010_P130::E002_C010_P130()
{
    
    m_touchingExampleSp = NULL;
    mSndManager = new E002_C010_SoundManager;
    arrMasks = CCArray::create();
    arrMasks->retain();
}

E002_C010_P130::~E002_C010_P130()
{
    CC_SAFE_DELETE(mSndManager);
    arrMasks->release();
}

#pragma mark - init

bool E002_C010_P130::init()
{
    if (!E002_Base_Reward::init()) {
        return false;
    }
    
    m_nMaxStageCount = 6;
    m_nCurrentStageIndex = 0;
    
    return true;
}

void E002_C010_P130::onEnter()
{
    E002_Base_Reward::onEnter();
    setTouchDisalbeBaseLayer();
    onViewLoad();
}

void E002_C010_P130::onExit()
{
    
    E002_Base_Reward::onExit();
}


void E002_C010_P130::onViewLoad()
{
    E002_Base_Reward::onViewLoad();

    
    CJPsdParser::parseToPsdJSON("e002_c010_p130.json", &m_psdDictionary);
    
    CJSprite* bg1 = createSprite("e002_c010_p130_img_bg_00");
    CJSprite* bg2 = createSprite("e002_c010_p130_img_bg_01");
    CJSprite* bg3 = createSprite("e002_c010_p130_img_bg_02");
    addChild(bg1, kDepth0_background+1);
    addChild(bg2, kDepth0_backImage);
    addChild(bg3, kDepth0_backImage+5);
    
    
    CJSprite* building0 = createSprite("e002_c010_p130_img_building00_bg");
    CJSprite* building1 = createSprite("e002_c010_p130_img_building01_bg");
    CJSprite* building2 = createSprite("e002_c010_p130_img_building02_bg");
    CJSprite* building3 = createSprite("e002_c010_p130_img_building03_bg");
    CJSprite* building4 = createSprite("e002_c010_p130_img_building04_bg");
    CJSprite* statue = createSprite("e002_c010_p130_img_statue_00");
    
    addChild(statue, kDepth0_backImage-1);
    addChild(building2, kDepth0_backImage-1);
    addChild(building1, kDepth0_backImage);
    addChild(building0, kDepth0_backImage);
    addChild(building3, kDepth0_backImage);
    addChild(building4, kDepth0_backImage);
    

    
    //make buildinds
    runSequence(building0, "e002_c010_p130_img_building00_00", 0.2);
    runSequence(building0, "e002_c010_p130_img_building00_01", 0.2);
    
    runSequence(building1, "e002_c010_p130_img_building01_00", 0.2);
    runSequence(building1, "e002_c010_p130_img_building01_01", 0.2);
    
    runSequence(building2, "e002_c010_p130_img_building02", 0.2);
    
    runSequence(building3, "e002_c010_p130_img_building03_00", 0.2);
//    runSequence(building3, "e002_c010_p130_img_building03_01", 0.2);
    runSequence(building3, "e002_c010_p130_img_building03_02", 0.2);
    runSequence(building3, "e002_c010_p130_img_building03_03", 0.2);
    
    runSequence(building4, "e002_c010_p130_img_building04_00", 0.2);
    runSequence(building4, "e002_c010_p130_img_building04_01", 0.2);
    
    
    runSequence(statue, "e002_c010_p130_img_statue", 0.1);

    
    //make balls
    for (int i = 0; i < 6; i++) {
        std::string str = CJUtils::getStringFormatInteger("e002_c010_p130_img_reward0%d", i);
        std::string str1 = CJUtils::getStringMerge(str, "_00");
        std::string str2 = CJUtils::getStringMerge(str, "_01");
        CJSprite* back = createSprite(str1);
        addChild(back, kDepth6_dimmed+1, _kTagBall1_back+i);
        
        CJSprite* ball = createSprite(str2);
        addChild(ball, kDepth6_dimmed+1, _kTagBall1+i);
        
        
        ball->setScale(0);
        back->setScale(0);
        
    }

    mDimm = createSprite("e002_c010_p130_img_dim");
//    setTouchEnableBaseLayer();
    
    setBrush();
    
    // FLASH
    setAnimationFile("e002_c010_p130_flash_as_sheets.json", "e002_c010_p130_flash_as_animations.json", FLASH_ANISON);
    setAnimationFile("e002_c010_p130_flash_firework_sheets.json", "e002_c010_p130_flash_firework_animations.json", FLASH_FIRE);
    setAnimationFile("e002_c010_p130_flash_ending_sheets.json", "e002_c010_p130_flash_ending_animations.json", "ENDING");

//    animationManagerParseStart();
    parseThreadStartCallback();

}


void E002_C010_P130::onViewLoaded()
{
    E002_Base_Reward::onViewLoaded();
    
    
//    mSndManager->playBgm(E002_C010_SoundManager::p110);
    
    animationManagerParseComplete();


}

void E002_C010_P130::startFlashAnimation()
{
    createAnimationAndSetKey(FLASH_ANISON, "e002_c010_p130_flash_as_action", FLASH_KEY_SPEAK);
    
    createAnimationAndSetKey(FLASH_FIRE, "e002_c010_p130_flash_firework_00", FLASH_KEY_FIRE0);
    createAnimationAndSetKey(FLASH_FIRE, "e002_c010_p130_flash_firework_01", FLASH_KEY_FIRE1);
    createAnimationAndSetKey(FLASH_FIRE, "e002_c010_p130_flash_firework_02", FLASH_KEY_FIRE2);
    createAnimationAndSetKey(FLASH_FIRE, "e002_c010_p130_flash_firework_03", FLASH_KEY_FIRE3);
    createAnimationAndSetKey(FLASH_FIRE, "e002_c010_p130_flash_firework_04", FLASH_KEY_FIRE4);
    createAnimationAndSetKey(FLASH_FIRE, "e002_c010_p130_flash_firework_05", FLASH_KEY_FIRE5);
    
    createAnimationAndSetKey("ENDING", "e002_c010_p130_flash_as_action", FLASH_KEY_SUCCESS);
    
    CJUtils::performSelector(this, callfunc_selector(E002_C010_P130::onFirstNarration),0.5);
    _playAnimationAnison(FLASH_KEY_SPEAK, 1);
}

void E002_C010_P130::onFirstNarration()
{
//    E002_Base_Reward::onFirstNarration();

    mFirstNarration = "e002_c010_p120_snd_01_as_backup.mp3";
    playNarration(mFirstNarration);
}

void E002_C010_P130::onFirstNarrationEnd()
{
    E002_Base_Reward::onFirstNarrationEnd();
//    setTouchDisalbeBaseLayer();

    //guide in onLastFrame();
}

void E002_C010_P130::onNarrationFinishedCallback(std::string fileName)
{
    if (fileName == mFirstNarration)
    {
        onFirstNarrationEnd();
    }
}

#pragma mark - touch

bool E002_C010_P130::onTouchBegan(CCPoint tp)
{
    
    for (int i = _kTagBall1; i <= _kTagBall6 ; i ++) {
        CJSprite* ball = (CJSprite*)getChildByTag(i);
        if(ball && CJUtils::hitTestPoint(ball, tp, false))
        {
            playEffect("e002_c010_p130_sfx_select.mp3");
            onSuccesses(ball, i);
        }
        
    }
    
    
    return false;
}

void E002_C010_P130::onTouchMoved(CCPoint tp)
{
}

void E002_C010_P130::onTouchEnded(CCPoint tp)
{
}

#pragma mark - check 

void E002_C010_P130::intoTarget(CJSprite* sp, CCPoint pt)
{
    setTouchDisalbeBaseLayer();
    
}
#pragma mark - feedback event

void E002_C010_P130::onSuccesses(CCNode *node, int tag)
{
    CCLog("onSuccess");
    CJSprite* ball = (CJSprite*)node;
    CJSprite* ballBack = (CJSprite*)getChildByTag(tag+ (_kTagBall1_back-_kTagBall1));
    
    ball->runAction(CCSequence::create(CCSpawn::create(CCFadeOut::create(0.5),
                                                       CCScaleTo::create(0.5, 1.5),
                                                       NULL),
                                       CCCallFunc::create(ball, callfunc_selector(CJSprite::removeFromParent)),
                                       NULL));
    
    ballBack->runAction(CCSequence::create(CCSpawn::create(CCFadeOut::create(0.5),
                                                           CCScaleTo::create(0.5, 1.5),
                                                           NULL),
                                           CCCallFunc::create(ballBack, callfunc_selector(CJSprite::removeFromParent)),
                                           NULL));
    
    
    std::string name = CJUtils::getStringFormatInteger("e002_c010_p130_img_mask_0%d", tag - _kTagBall1);
    CJSprite* sp = createSprite(name);
    completeMasking(sp);
    _playFirework(ball->getPosition(), tag - _kTagBall1);
    
    
    std::string sndName = CJUtils::getStringFormatInteger("e002_c010_p120_snd_good_0%d.mp3", m_nCurrentStageIndex%4);
    playNarration(sndName);
    
    m_nCurrentStageIndex++;
   
    if (m_nCurrentStageIndex >= m_nMaxStageCount) {
        CJLog("complete");
        setTouchDisalbeBaseLayer();
        CJUtils::performSelector(this, callfunc_selector(E002_C010_P130::onComplete), 1.0);
    }
    
}


void E002_C010_P130::onComplete()
{
    E002_Base_Reward::onComplete();
    
    playEffect("e002_c010_p130_sfx_04.mp3");
    
    CCSprite* m_targetSp = (m_target->getSprite());
    m_targetSp->runAction(CCSequence::create(CCFadeOut::create(0.5),
                                             CCCallFunc::create(m_targetSp, callfunc_selector(CCSprite::removeFromParent)),
                                             NULL));
    
    //1122,1140
    //1250, 1298
    CJAnimation* fire1 = _playFirework(ccp(561, 570), 0);
    fire1->setScale(0.3);
    CJUtils::performSelector(this, callfunc_selector(E002_C010_P130::completeFirework), 0.5);
    
}

void E002_C010_P130::completeFirework()
{

    CJAnimation* fire2 = _playFirework(ccp(625, 649), 1);
    fire2->setScale(0.3);
    
    CJAnimation*ani = playAnimationByKey("ENDING", FLASH_KEY_SUCCESS, 1, kDepth6_dimmed);
    addNarrationOnFlashFrame(ani, 1, getFilePath("snd","e002_c010_p120_snd_03_as.mp3").c_str());
    addNarrationOnFlashFrame(ani, 158, getFilePath("snd","e002_c010_p120_snd_04_ar.mp3").c_str());
    addNarrationOnFlashFrame(ani, 271, getFilePath("snd","e002_c010_p120_snd_05_as.mp3").c_str());
    
}

void E002_C010_P130::onEnd()
{
//    replaceSceneTransitionFadeOut(E002_C010_P200_Intro);
    showCompletePopup();
}

#pragma mark - set questions, set examples
void E002_C010_P130::start()
{
    setQuestions();
}

void E002_C010_P130::setQuestions()
{
    float delay = 0.f;
    for (int i = _kTagBall1; i <= _kTagBall6; i++) {
        CJSprite* ball = (CJSprite*)getChildByTag(i);
        CJSprite* back = (CJSprite*)getChildByTag(i+ (_kTagBall1_back-_kTagBall1));
        
        CCAction* scaleup = CCEaseSineOut::create(CCSpawn::create(CCScaleTo::create(0.3, 1.0),
                                                                  CCRotateBy::create(0.3, 360 * 2),
                                                                  NULL));

        ball->runAction(CCSequence::create(CCDelayTime::create(delay),
                                           CJMultimedia::getInstance()->playEffectWithDelayCallfuncND(this, getSoundFilePath("e002_c010_p130_sfx_01.mp3")),
                                           scaleup,
                                           CCCallFuncN::create(this, callfuncN_selector(E002_C010_P130::ballAnimation)),
                                           NULL));

        
        if (i != _kTagBall6) {
            
            back->runAction(CCSequence::create(CCDelayTime::create(delay),
                                               scaleup->copy()->autorelease(),
                                               CCEaseSineOut::create(CCSpawn::create(CCScaleTo::create(1.5, 1.5),
//                                                                                     CCFadeTo::create(1.5, 100),
                                                                                     NULL)),
                                               CCCallFuncN::create(this, callfuncN_selector(E002_C010_P130::ballBackAnimation)),
                                               NULL));

        }else{
            back->runAction(CCSequence::create(CCDelayTime::create(delay),
                                               scaleup->copy()->autorelease(),
                                               CCEaseSineOut::create(CCSpawn::create(CCScaleTo::create(1.5, 1.5),
//                                                                                     CCFadeTo::create(1.5, 100),
                                                                                     NULL)),
                                               CCCallFuncN::create(this, callfuncN_selector(E002_C010_P130::ballBackAnimation)),
                                               CCCallFunc::create(this, callfunc_selector(E002_C010_P130::setTouchEnableBaseLayer)),
                                               NULL));

        }
        
        delay += 0.3f;
        
        
    }
}


void E002_C010_P130::showQuestions()
{
}

void E002_C010_P130::showExamples()
{
    
}

void E002_C010_P130::resetValue()
{
}

void E002_C010_P130::ballBackAnimation(CCNode* sender)
{
    
    CJSprite* sp = (CJSprite*)sender;
    sp->setScale(1.0);
    sp->setOpacity(255);
    sp->runAction(CCRepeatForever::create(CCSequence::create(CCFadeTo::create(0.0, 255.0),
                                                             CCScaleTo::create(0.0, 1.0),
                                                             CCEaseSineOut::create(CCSpawn::create(CCScaleTo::create(1.5, 1.8),
//                                                                                                   CCFadeTo::create(2.0, 100.0),
                                                                                                   NULL)),
                                                             CCEaseSineOut::create(CCSpawn::create(CCScaleTo::create(1.5, 1.0),
//                                                                                                   CCFadeTo::create(1.5, 255.0),
                                                                                                   NULL)),
                                                             CCDelayTime::create(0.5),
                                                             NULL)));
}

void E002_C010_P130::ballAnimation(CCNode* sender)
{
    float rand = CJUtils::randomFloat(4.5, 9.0);
    int randV = CJUtils::randomInteger(0, 1) == 0 ? -1 : 1;
    sender->runAction(CCRepeatForever::create(CCRotateBy::create(rand, 360*randV)));
}

void E002_C010_P130::runSequence(CJSprite* parent, std::string str, float delay)
{
    std::string str1 = CJUtils::getStringMerge(str, "_00");
    std::string str2 = CJUtils::getStringMerge(str, "_01");
    CJSprite* sp = createSprite(str1);
    parent->addChildIgnoreParent(sp);
    sp->runAction(CJUtils::getSeqAction(-1,
                                        delay,
                                        getImageFilePath(str1).append(".png").c_str(),
                                        getImageFilePath(str2).append(".png").c_str(),
                                        NULL));
}



#pragma mark - appear, disappear



void E002_C010_P130::disappearAnimation()
{
    
}

void E002_C010_P130::OnLastFrame(CJAnimation* pAnimation)
{
//    E002_C010_BaseUtil::OnLastFrame(pAnimation);
    
    if (pAnimation->getKey() == FLASH_KEY_SPEAK) {
        
//    if (getUserDefaultFirstGuide(eGuidePageP130) == false)
//    {
        mShowFirstGuide = true;
        
        setUserDefaultFirstGuide(eGuidePageP130);
        onTouchedNavigationButtonAtInfo();
//    }else{
//    start();
//}
    }
    
    if (pAnimation->getKey() == FLASH_KEY_SUCCESS) {
        onEnd();
    }
}

#pragma mark - mask

void E002_C010_P130::setBrush()
{
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    m_target = CCRenderTexture::create(s.width, s.height);
    
	if (NULL == m_target) {return;}
	
    m_target->setPosition(ccp(s.width/2, s.height/2));
    addChild(m_target,kDepth6_dimmed);
    

//    (m_target->getSprite())->setBlendFunc((ccBlendFunc){GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA});
//    CJLog("m_target->getSprite() = %p",m_target->getSprite());
    
//    
//    CCSprite* maskingLayer = new CCSprite();
//    maskingLayer = new CCSprite();
//    maskingLayer->init();
//    maskingLayer->setContentSize(CCSizeMake(1024, 768));
//    maskingLayer->setTextureRect(CCRectMake(0, 0, 1024, 768));
//    maskingLayer->setColor(ccBLACK);
//    maskingLayer->setAnchorPoint(CCPointZero);
//    maskingLayer->setPosition(CCPointZero);
//    maskingLayer->setOpacity(255.0f * 0.90);
    //    maskingLayer->setTag(kTagMaskingLayer);
    
    m_target->begin();
    mDimm->visit();
    m_target->end();
    
}


void E002_C010_P130::completeMasking(CJSprite* sp)
{
    mask = sp;
    arrMasks->addObject(sp);
    for (int i = 0 ; i < arrMasks->count(); i++) {
        if (arrMasks->objectAtIndex(i) != sp) {
            sp->setOpacity(255);
        }
    }
    
    sp->setBlendFunc((ccBlendFunc){GL_ZERO, GL_ONE_MINUS_SRC_ALPHA});
    sp->setOpacity(0);
    addChild(sp);

    schedule(schedule_selector(E002_C010_P130::showMaskRenderingSchedule), 1/60.f);
    sp->runAction(CCSequence::create(CCFadeIn::create(0.5),
                                     CCCallFuncN::create(this, callfuncN_selector(E002_C010_P130::endMaskRenderingSchedule)),
                                     NULL));
    
    
    
}


void E002_C010_P130::showMaskRenderingSchedule(float dt)
{
    CCLog("visit");
    m_target->begin();
    for (int i = 0; i < arrMasks->count(); i++) {
        ((CJSprite*)arrMasks->objectAtIndex(i))->visit();
    }
//    mask->visit();
    m_target->end();
}

void E002_C010_P130::endMaskRenderingSchedule(CCNode* sender)
{
    CCLog("unscheduled.");
    unschedule(schedule_selector(E002_C010_P130::showMaskRenderingSchedule));
    arrMasks->removeObject(sender);
    
}

void E002_C010_P130::completeFirstGuide()
{
    CJUtils::performSelector(this, callfunc_selector(E002_C010_P130::start),0.0);
    setTouchDisalbeBaseLayer();
}

void E002_C010_P130::showCompletePopup()
{
    E002_C010_CompletePopup *cPopup = new E002_C010_CompletePopup();
    cPopup->init(P100);
    addChild(cPopup, kDepth10_guide);
    
    cPopup->showPopup(this);
    cPopup->showCompletePopup();
}

#pragma mark - animation 

CJAnimation* E002_C010_P130::_playAnimationAnison(std::string pAniKey, int count)
{
    removeAllAnimationsInDataPool(FLASH_ANISON);
    return playAnimationByKey(FLASH_ANISON,pAniKey.c_str(), count, kDepth7_popup, this);
}


CJAnimation* E002_C010_P130::_playFirework(CCPoint pos, int tag)
{
    std::string key = CJUtils::getStringFormatInteger("fire%d", tag);
    CJAnimation* ani = playAnimationByKey(FLASH_FIRE, key, 1, kDepth6_dimmed+1, this);
    ani->setPosition(pos);
    playEffect("e002_c010_p130_sfx_lighting.mp3");
    return ani;
}




#pragma mark - navigation delegate

void E002_C010_P130::onTouchedNavigationButtonAtIndex()
{
    E002_Base_Reward::onTouchedNavigationButtonAtIndex();
    E002_C010_P000_Index* _indexClass = E002_C010_P000_Index::create();
    _indexClass->init();
    _indexClass->setIndexDelegate(this);
    _indexClass->showIndex(this, _indexClass);
    addChild(_indexClass, kDepth11_Index);
    
}

void E002_C010_P130::onTouchedNavigationButtonAtInfo()
{
    E002_Base_Reward::onTouchedNavigationButtonAtInfo();
    
    showGuide(new E002_Base_ImageGuide_Item("e002_c010_p130_guide.jpg",
                                            CJPsdParser::getPsdPosition("e002_common_img_guide_hand", m_psdDictionary),
                                            CJPsdParser::getPsdPosition("e002_common_img_guide_hand", m_psdDictionary)
//                                            ccpAdd(CJPsdParser::getPsdPosition("e002_c010_p130_img_reward05_01", m_psdDictionary),ccp(60, -60)),
//                                            ccpAdd(CJPsdParser::getPsdPosition("e002_c010_p130_img_reward05_01", m_psdDictionary),ccp(60, -60))
                                            ));

}

void E002_C010_P130::onTouchedNavigationButtonAtPrev()
{
    E002_Base_Reward::onTouchedNavigationButtonAtPrev();
    replaceSceneTransitionFadeOut(E002_C010_P110);
}

void E002_C010_P130::onTouchedNavigationButtonAtNext()
{
    E002_Base_Reward::onTouchedNavigationButtonAtNext();
//    onEnd();
    replaceSceneTransitionFadeOut(E002_C010_P200_Intro);
}



#pragma mark - my util

CJSprite* E002_C010_P130::createSprite(std::string pStr)
{
    return CJPsdParser::getPsdSprite(pStr, m_psdDictionary);
}


void E002_C010_P130::_setPositionOutParent(CCNode* child, CCNode* newParent)
{
    CCNode* parent = (CCNode*)child->getParent();
    if (parent && child) {
    
        child->retain();
        
        CCSize parentSize = parent->getContentSize();
        CCPoint parentAnchor = parent->getAnchorPoint();
        
        float posX =  parent->getPositionX() - parentSize.width*parentAnchor.x + child->getPositionX();
        float posY =  parent->getPositionY() - parentSize.height*parentAnchor.y + child->getPositionY();
    
        child->removeFromParentAndCleanup(false);
        child->setPosition(ccp(posX, posY));
        this->addChild(child);
        
        child->release();
    }
    
}

void E002_C010_P130::_safeRemoveFromParents(CCNode* pChild)
{
    if (pChild && pChild->getParent()) {
        pChild->removeFromParent();
    }
}

