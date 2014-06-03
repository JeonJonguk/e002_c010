

#include "E002_C010_P330.h"
#include "E002_C010_BaseUtil.h"
#include "E002_C010_P000_Index.h"
#include "E002_C010_P310.h"
#include "E002_C010_CompletePopup.h"

#define LAYER_DISTANCE          1536 *2

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

    _kBalloon,
    _kShadow,
    _kBody,
    _kEye_l,
    _kEye_r,
    _kEyebrow,
    _kMouse,
    _kPupil_l,
    _kPupil_r,
    
    
    _kItem_0,
    _kItem_1,
    _kItem_2,
    _kItem_3,
    _kItem_4,
    _kItem_5,
    
    _kItem_wear_0,
    _kItem_wear_1,
    _kItem_wear_2,
    _kItem_wear_3,
    _kItem_wear_4,
    _kItem_wear_5,
    _kItem_wear_3_2,
    
    _kCloud_0,
    _kCloud_1,
    _kCloud_2,
    _kCloud_3,
    _kCloud_4,
    _kCloud_5,
    
    //step2
    _kBodyDown,
    _kFreedom,
//    _kBird1,
//    _kBird2,
};

enum depth{
    _kDepthBackground = kDepth0_background,
    _kDepthBackImage = kDepth0_backImage,
    
};


E002_C010_P330::E002_C010_P330()
{
    
    m_touchingExampleSp = NULL;
    mSndManager = new E002_C010_SoundManager;
}

E002_C010_P330::~E002_C010_P330()
{
    CC_SAFE_DELETE(mSndManager);
}

#pragma mark - init

bool E002_C010_P330::init()
{
    if (!E002_Base_Reward::init()) {
        return false;
    }
    
    m_nMaxStageCount = 6;
    m_nCurrentStageIndex = 0;
    bIsStep2 = false;
    return true;
}

void E002_C010_P330::onEnter()
{
    E002_Base_Reward::onEnter();
    setTouchDisalbeBaseLayer();
    onViewLoad();
}

void E002_C010_P330::onExit()
{
    
    E002_Base_Reward::onExit();
}


void E002_C010_P330::onViewLoad()
{
    E002_Base_Reward::onViewLoad();
    
    
    CJPsdParser::parseToPsdJSON("e002_c010_p330.json", &m_psdDictionary);
    
    CJSprite* bg = CJSprite::createWithFullPath("e002_c010_p320_img_bg_00.jpg");
    bg->setAnchorPoint(CCPointZero);
    bg->setPosition(ccp(0,  -(bg->getContentSize().height - winSize.height)));
    addChild(bg, kDepth0_background, _kTagBg1);
    //step 1
    CJSprite* balloon = createSprite("e002_c010_p330_img_balloon_00");
    CJSprite* shadow = createSprite("e002_c010_p330_img_cha00_shadow");
    addChild(balloon, kDepth0_backImage, _kBalloon);
    addChild(shadow, kDepth0_backImage, _kShadow);
    
    mBody = createSprite("e002_c010_p330_img_cha00_body");
    CJSprite* eye_l = createSprite("e002_c010_p330_img_cha00_eye_l");
    CJSprite* eye_r = createSprite("e002_c010_p330_img_cha00_eye_r");
    CJSprite* eyebrow = createSprite("e002_c010_p330_img_cha00_eyebrow");
    CJSprite* mouse = createSprite("e002_c010_p330_img_cha00_mouse");
    CJSprite* pupil_l = createSprite("e002_c010_p330_img_cha00_pupil_l");
    CJSprite* pupil_r = createSprite("e002_c010_p330_img_cha00_pupil_r");
//    pupil_l->setPosition(ccp(481, 368));
//    pupil_r->setPosition(ccp(545, 368));
    
    addChild(mBody, kDepth0_backImage, _kBody);
    mBody->addChildIgnoreParent(eye_l, kDepth0_backImage, _kEye_l);
    mBody->addChildIgnoreParent(eye_r, kDepth0_backImage, _kEye_r);
    mBody->addChildIgnoreParent(eyebrow, kDepth0_backImage, _kEyebrow);
    mBody->addChildIgnoreParent(mouse, kDepth0_backImage, _kMouse);
    mBody->addChildIgnoreParent(pupil_l, kDepth0_backImage, _kPupil_l);
    mBody->addChildIgnoreParent(pupil_r, kDepth0_backImage, _kPupil_r);
    eyebrow->m_originPosition = eyebrow->getPosition();
    pupil_l->m_originPosition = pupil_l->getPosition();
    pupil_r->m_originPosition = pupil_r->getPosition();
    pupil_l->m_secondPosition = mBody->convertToNodeSpace(ccp(481, 368));
    pupil_r->m_secondPosition = mBody->convertToNodeSpace(ccp(545, 368));
    

    for (int i = 0; i < 6; i++) {
        std::string wearName = CJUtils::getStringFormatInteger("e002_c010_p330_img_reward0%d_01", i);
        CJSprite* wearItem = createSprite(wearName);
        mBody->addChildIgnoreParent(wearItem, kDepth1_actors, _kItem_wear_0+i);
        wearItem->setVisible(false);
        
        std::string name = CJUtils::getStringFormatInteger("e002_c010_p330_img_reward0%d_00", i);
        CJSprite* item = createSprite(name);
        addChild(item, kDepth1_actors, _kItem_0+i);
        item->setScale(0);
    }
    
    CJSprite* wearItem3_2 = createSprite("e002_c010_p330_img_reward03_02");
    mBody->addChildIgnoreParent(wearItem3_2, -01, _kItem_wear_3_2);
    wearItem3_2->setVisible(false);

    //cloud
    
    for (int i = 0; i < 6; i++) {
        std::string name = CJUtils::getStringFormatInteger("e002_c010_p330_img_cloud_0%d", i);
        CJSprite* cloud = createSprite(name);
        addChild(cloud, kDepth0_backImage-1, _kCloud_0+i);
        
        int temp = i < 4 ? 1 : -1;
        cloudHorizontal(cloud, temp);
    

    }
    
    
    //step2
    CJSprite* downBody = createSprite("e002_c010_p330_img_cha01_00");
    addChild(downBody, kDepth1_actors, _kBodyDown);
    downBody->setVisible(false);
    
    CJSprite* freedom = createSprite("e002_c010_p330_img_statue");
    freedom->setAnchorPointWithoutPosition(ccp(1, 0));
    addChild(freedom, kDepth0_backImage, _kFreedom);
    
//    CJSprite* bird1 = createSprite("e002_c010_p330_img_bird_00_00");
//    CJSprite* bird2 = createSprite("e002_c010_p330_img_bird_01_00");
//    addChild(bird1, kDepth0_backImage, _kBird1);
//    addChild(bird2, kDepth0_backImage, _kBird2);
//    bird1->setVisible(false);
//    bird2->setVisible(false);
//    bird1->runAction(CJUtils::getSeqAction(-1, 0.15,
//                                           getImageFilePath("e002_c010_p330_img_bird_00_00.png").c_str(),
//                                           getImageFilePath("e002_c010_p330_img_bird_00_01.png").c_str(),
//                                           NULL));
//    
//    bird2->runAction(CJUtils::getSeqAction(-1, 0.18,
//                                           getImageFilePath("e002_c010_p330_img_bird_01_00.png").c_str(),
//                                           getImageFilePath("e002_c010_p330_img_bird_01_01.png").c_str(),
//                                           NULL));
    
    

}


void E002_C010_P330::onViewLoaded()
{
    E002_Base_Reward::onViewLoaded();
    
    
    CJUtils::performSelector(this, callfunc_selector(E002_C010_P330::onFirstNarration),0.5);


}

void E002_C010_P330::onFirstNarration()
{
//    E002_Base_Reward::onFirstNarration();
    mFirstNarration = "e002_c010_p330_snd_01_as.mp3";
    playNarration(mFirstNarration);
    _mouseAnimation();
    _eyebrowAnimation();
}

void E002_C010_P330::onFirstNarrationEnd()
{
    E002_Base_Reward::onFirstNarrationEnd();
//    setTouchDisalbeBaseLayer();
    
    _mouseStop();
    
    
    if (getUserDefaultFirstGuide(eGuidePageP330) == false)
    {
    mShowFirstGuide = true;
    
    setUserDefaultFirstGuide(eGuidePageP330);
    onTouchedNavigationButtonAtInfo();
    }else{
    start();
    }

    
}

void E002_C010_P330::onNarrationFinishedCallback(std::string fileName)
{
    if (fileName == mFirstNarration)
    {
        onFirstNarrationEnd();
    }
}

#pragma mark - touch

bool E002_C010_P330::onTouchBegan(CCPoint tp)
{
    for (int i = 0; i < 6 ; i++) {
        CJSprite* item = (CJSprite*)getChildByTag(i + _kItem_0);
        if (item && CJUtils::hitTestPoint(item, tp, false)) {
            m_nExamplesTouchedIndex = i;
            m_touchingExampleSp = item;
            mTouchedPointGab = ccpSub(m_touchingExampleSp->getPosition(), tp);
            _eyesAnimation(tp, true);
            
            CJSprite* brow = (CJSprite*)mBody->getChildByTag(_kEyebrow);
            brow->stopAllActions();
            _eyebrowAnimation();
            return true;
        }
    }
    
    
    
    if (mBody && bIsStep2 && CJUtils::hitTestPoint(mBody, tp, false)) {
        
        setTouchDisalbeBaseLayer();
        openParachute();
    }
    
    return false;
}

void E002_C010_P330::onTouchMoved(CCPoint tp)
{
    m_touchingExampleSp->setPosition(ccp(tp.x + mTouchedPointGab.x, tp.y + mTouchedPointGab.y));
    _eyesAnimation(tp);
    
}

void E002_C010_P330::onTouchEnded(CCPoint tp)
{
    if (CJUtils::hitTestObjects(m_touchingExampleSp, getChildByTag(_kBody))) {
        int tempIdx = m_nExamplesTouchedIndex;
        CCPoint targetPt = mBody->convertToWorldSpace(mBody->getChildByTag(_kItem_wear_0+m_nExamplesTouchedIndex)->getPosition());
        m_touchingExampleSp->runAction(CCSequence::create(CCSpawn::create(CCEaseBackOut::create(CCMoveTo::create(0.2, targetPt)),
                                                                          CCFadeOut::create(0.2),
                                                                          CCCallFuncND::create(this, callfuncND_selector(E002_C010_P330::intoTarget), (void*)tempIdx),
                                                                          NULL),
                                                          
                                                          CCCallFunc::create(m_touchingExampleSp, callfunc_selector(CJSprite::removeFromParent)),
                                                          NULL));
    }else{
        m_touchingExampleSp->runAction(
                                       CCEaseBackOut::create(CCMoveTo::create(0.4, m_touchingExampleSp->m_originPosition)));
    }
    
    
    _eyesStop();
}

#pragma mark - check 

void E002_C010_P330::intoTarget(CJSprite* sp, int tag)
{
//    setTouchDisalbeBaseLayer();
    playEffect("e002_c010_p000_sfx_06.mp3");
    CJSprite* wearItem = (CJSprite*)mBody->getChildByTag(_kItem_wear_0+tag);
    
    wearItem->setOpacity(0);
    wearItem->setScale(1.6);
    wearItem->setVisible(true);
    wearItem->runAction(CCSequence::create(CCSpawn::create(CCEaseSineIn::create(CCFadeIn::create(0.3)),
                                                           CCEaseSineIn::create(CCScaleTo::create(0.3, 1.0)),
                                                           NULL),
                                           CCEaseSineOut::create(CCScaleTo::create(0.1, 1.05)),
                                           CCEaseSineIn::create(CCScaleTo::create(0.1, 1.0)),
                                           CCCallFuncND::create(this, callfuncND_selector(E002_C010_P330::onSuccesses), (void*)tag),
                                           NULL));
    
    CCParticleSystemQuad* particle1 =  E002_C010_BaseUtil::addParticle("e002_c010_p330_star_00.plist");
    addChild(particle1, kDepth5_particle);


    if (tag == 3) {
        CJSprite* wearItem = (CJSprite*)mBody->getChildByTag(_kItem_wear_3_2);
        wearItem->setOpacity(0);
        wearItem->setScale(1.6);
        wearItem->setVisible(true);
        wearItem->runAction(CCSequence::create(CCSpawn::create(CCEaseSineIn::create(CCFadeIn::create(0.3)),
                                                               CCEaseSineIn::create(CCScaleTo::create(0.3, 1.0)),
                                                               NULL),
                                               CCEaseSineOut::create(CCScaleTo::create(0.1, 1.05)),
                                               CCEaseSineIn::create(CCScaleTo::create(0.1, 1.0)),
                                               NULL));

    }
    
}
#pragma mark - feedback event

void E002_C010_P330::onSuccesses(CCNode *node, int tag)
{
    if (m_nCurrentStageIndex < 5) {
        m_nCurrentStageIndex++;
        
    }else{
        
        playEffect("e002_c010_p330_sfx_complete.mp3");
        setTouchDisalbeBaseLayer();
        mBody->setAnchorPointWithoutPosition(ccp(0.5, 0));
        
        //jump
        mBody->runAction(CCSequence::create(CCEaseSineInOut::create(CCScaleTo::create(0.5, 1.0,0.8)),
                                            CJMultimedia::getInstance()->playEffectWithDelayCallfuncND(this, getFilePath("snd","e002_c010_p330_sfx_jump_as.mp3")),
                                            CCSpawn::create(CCScaleTo::create(0.1, 1.1),
                                                            CCMoveTo::create(0.1, ccp(mBody->getPositionX(), winSize.height + 100)),
                                                            NULL),
                                            CCCallFunc::create(mBody, callfunc_selector(CJSprite::removeFromParent)),
                                            NULL));
        
        CJSprite* shadow = (CJSprite*)getChildByTag(_kShadow);
        shadow->runAction(CCSequence::create(CCEaseSineInOut::create(CCScaleTo::create(0.5, 1.1)),
                                             CCScaleTo::create(0.1, 0),
                                             NULL));
        
        CJSprite* balloon = (CJSprite*)getChildByTag(_kBalloon);
        balloon->runAction(CCSequence::create(CCDelayTime::create(0.8),
                                              CCEaseSineIn::create(CCMoveBy::create(0.4, ccp(0, -250))),
                                              
                                              NULL));
        
        for (int i = 0; i < 6; i++) {
            CJSprite* cloud = (CJSprite*)getChildByTag(_kCloud_0+i);
            cloud->stopAllActions();
            cloud->runAction(CCSequence::create(CCDelayTime::create(1.0),
                                                CCEaseSineIn::create( CCMoveBy::create(0.5, ccp(0, -768))),
                                                NULL));
        }
        
        CJUtils::performSelector(this, callfunc_selector(E002_C010_P330::step2), 1.6);


    }
}

void E002_C010_P330::onComplete()
{
    E002_Base_Reward::onComplete();
    onEnd();

    
}


void E002_C010_P330::onEnd()
{
    replaceSceneTransitionFadeOut(E002_C010_P330);
//    showCompletePopup();
}

#pragma mark - set questions, set examples
void E002_C010_P330::start()
{
    setQuestions();
}

void E002_C010_P330::setQuestions()
{
    float delay = 0.0f;
    for (int i = 0; i < 6; i++) {
        CJSprite* item = (CJSprite*)getChildByTag(_kItem_0 + i);
        item->runAction(CCSequence::create(CCDelayTime::create(delay),
                                           CJMultimedia::getInstance()->playEffectWithDelayCallfuncND(this, getFilePath("snd","e002_c010_p000_sfx_02.mp3")),
                                           CCEaseElasticOut::create(CCScaleTo::create(0.5, 1.0)),
                                           CCCallFuncN::create(this, callfuncN_selector(E002_C010_P330::_doongDoong)),
                                           NULL));
        delay += 0.3;
    }
    CJUtils::performSelector(this, callfunc_selector(E002_C010_P330::setTouchEnableBaseLayer),delay);

}

void E002_C010_P330::showQuestions()
{
}

void E002_C010_P330::showExamples()
{    
}

void E002_C010_P330::resetValue()
{
}

void E002_C010_P330::OnLastFrame(CJAnimation* pAnimation)
{
    E002_C010_BaseUtil::OnLastFrame(pAnimation);

}



void E002_C010_P330::step2()
{
    bIsStep2 = true;
    
    //cloud set
    for (int i = 0; i < 6; i++) {
        CJSprite* cloud = (CJSprite*)getChildByTag(_kCloud_0+i);
        cloud->setPosition(ccpAdd(cloud->m_originPosition,ccp(0, -768)));
        cloud->m_secondPosition = cloud->getPosition();
        cloud->runAction(CCSequence::create(CCDelayTime::create(0.5),
                                            CCEaseSineIn::create( CCMoveBy::create(1.0, ccp(0, -768))),
                                            CCCallFuncND::create(this, callfuncND_selector(E002_C010_P330::cloudVertical),(void*)1000),
                                            NULL));
    }
    
    
    //bird
//    CJSprite* bird1 = (CJSprite*)getChildByTag(_kBird1);
//    CJSprite* bird2 = (CJSprite*)getChildByTag(_kBird2);
//    bird1->setPosition(ccpAdd(bird1->m_originPosition,ccp(0, -768)));
//    bird1->m_secondPosition = bird1->getPosition();
//    bird2->setPosition(ccpAdd(bird2->m_originPosition,ccp(0, -768)));
//    bird2->m_secondPosition = bird2->getPosition();
//    bird1->setVisible(true);
//    bird2->setVisible(true);
//    birdVertical(bird1, 1000);
//    birdVertical(bird2, 1000);
//    
//    bird1->runAction(CCRepeatForever::create(CCSequence::create(CCMoveTo::create(7.0, ccp(-200, bird1->getPositionY())),
//                                                                CCMoveTo::create(0, ccp(winSize.width+ 200, bird1->getPositionY())),
//                                                                NULL)));
//    bird2->runAction(CCRepeatForever::create(CCSequence::create(CCMoveTo::create(8.0, ccp(-200, bird2->getPositionY())),
//                                                                CCMoveTo::create(0, ccp(winSize.width+ 200, bird2->getPositionY())),
//                                                                NULL)));

    
    mBody = (CJSprite*)getChildByTag(_kBodyDown);
    mBody->setPosition(ccpAdd(mBody->m_originPosition, ccp(0,winSize.height)));
    mBody->setVisible(true);
    
    mBody->runAction(CCSequence::create(CCDelayTime::create(0.5),
                                        CCEaseSineInOut::create(CCMoveTo::create(1.0, mBody->m_originPosition)),
                                        CCCallFunc::create(this, callfunc_selector(E002_C010_P330::setTouchEnableBaseLayer)),
                                        CCCallFunc::create(this, callfunc_selector(E002_C010_P330::_bodyDownAnimation)),
                                        NULL));
    
    mBody->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.04, ccp(0,4)),
                                                                CCMoveBy::create(0.04, ccp(0,-4)),
                                                                NULL)));
    
    
    CJSprite* copy = CJSprite::createWithFullPath("e002_c010_p330_img_cha01_00_white.png");
    mBody->addChild(copy, 1, 0);
    copy->setPosition(CCPointZero);
    copy->setAnchorPoint(ccp(0, 0));
    copy->setOpacity(0);
    copy->runAction(CCSequence::create(CCDelayTime::create(4.5),
                                       CCCallFunc::create(this, callfunc_selector(E002_C010_P330::_whiteningAnimation)),
                                       NULL));
//    copy->runAction(CCSequence::create(CCDelayTime::create(0.5),
//                                        CCEaseSineInOut::create(CCMoveTo::create(1.0, mBody->m_originPosition)),
//                                        NULL));
    
    CJMultimedia::getInstance()->playNarration(getFilePath("snd","e002_c010_p330_sfx_down_as.mp3"), true);
}


void E002_C010_P330::openParachute()
{
    stopNarration("e002_c010_p330_sfx_down_as.mp3");
    playEffect("e002_c010_p330_sfx_parachute.mp3");
    
    mBody->removeAllChildren();
    
    mBody->stopAllActions();
    mBody->changeTextureWithFullPath("e002_c010_p330_img_cha01_01.png");
    mBody->runAction(CCSequence::create(CCEaseSineOut::create(CCMoveBy::create(0.8, ccp(0, 90))),
                                        CCDelayTime::create(0.2),
                                        CCCallFunc::create(this, callfunc_selector(E002_C010_P330::bodyAfterOpenParachuteAnimation)),
                                        CCMoveBy::create(2.5, ccp(120, -90)),
                                        CCDelayTime::create(2.5),
                                        CJUtils::getSeqAction(1, 0.1,
                                                              getImageFilePath("e002_c010_p330_img_cha01_02.png").c_str(),NULL),
                                        NULL));
    
    for (int i = 0; i < 6; i++) {
        CJSprite* cloud = (CJSprite*)getChildByTag(_kCloud_0+i);
        cloud->stopAllActions();
        cloudVertical(cloud, 300);
    }
    
//    CJSprite* bird1 = (CJSprite*)getChildByTag(_kBird1);
//    bird1->stopActionByTag(0);
//    birdVertical(bird1, 300);
//    
//    
//    CJSprite* bird2 = (CJSprite*)getChildByTag(_kBird2);
//    bird2->stopActionByTag(0);
//    birdVertical(bird2, 300);
    
    CCParticleSystemQuad* particle =  E002_C010_BaseUtil::addParticle("e002_c010_p330_star_01.plist");
    addChild(particle, kDepth5_particle);

    
    
    CJSprite* freedom = (CJSprite*)getChildByTag(_kFreedom);
    freedom->runAction(CCSequence::create(CCDelayTime::create(3.0),
                                          CCMoveTo::create(4.0, ccp(winSize.width, 0)),
//                                          CCCallFunc::create(this, callfunc_selector(E002_C010_P330::onComplete)),
                                          NULL));
    
    this->runAction(CCSequence::create(CCDelayTime::create(6.5),
                                       CCCallFunc::create(this, callfunc_selector(E002_C010_P330::onComplete)),
                                       NULL));
}


void E002_C010_P330::bodyAfterOpenParachuteAnimation()
{
    //483 × 532
    //237 , 423
    mBody->setAnchorPointWithoutPosition(ccp(237.f/483.f, 423.f/532.f));
    mBody->runAction(CCRepeatForever::create(CCSequence::create(CCEaseSineInOut::create(CCRotateTo::create(1.2, 10)),
                                                                CCEaseSineInOut::create(CCRotateBy::create(1.2, -13)),
                                                                NULL)));
}

#pragma mark - animations

void E002_C010_P330::_doongDoong(CJSprite* balloon)
{
    balloon->runAction(CCRepeatForever::create(CCSequence::create(CCEaseSineInOut::create(CCMoveBy::create(0.7, ccp(0, 10))),
                                                                  CCEaseSineInOut::create(CCMoveBy::create(0.7, ccp(0, -10))),
                                                                  NULL)));
    
}


void E002_C010_P330::_eyesAnimation(CCPoint tp, bool bWithAction )
{
    
    //eyes
    CJSprite* eye_l = (CJSprite*)mBody->getChildByTag(_kPupil_l);
    CJSprite* eye_r = (CJSprite*)mBody->getChildByTag(_kPupil_r);
    eye_l->stopAllActions();
    eye_r->stopAllActions();
    
    CCPoint vector = ccpSub(tp, mBody->convertToWorldSpace(eye_l->m_secondPosition));
    CCPoint normalVector = ccpNormalize(vector);
//    CJLog("normalVector = %f %f", normalVector.x, normalVector.y);
    
    
    float angleRads = ccpToAngle(normalVector);
    int angleDegs = (int)CC_RADIANS_TO_DEGREES(angleRads) % 360;
    float length = ccpLength(vector);
    
    while (angleDegs < 0)
        angleDegs += 360;
    
    if (length > 360)
    {
        length = 360;
    }
    
    if (angleDegs > 360)
    {
        normalVector = ccpForAngle(CC_DEGREES_TO_RADIANS(360));
        
    }
    else if (angleDegs < 0)
    {
        normalVector = ccpForAngle(CC_DEGREES_TO_RADIANS(0));
        
    }
    
    float length2;
    
    if (length < 15) {
        
        length2 = length;
    }
    
    else {
        length2 = 15;
    }
    
    if (bWithAction) {
        
        eye_l->runAction(CCEaseSineInOut::create(CCMoveTo::create(0.1, ccpAdd(eye_l->m_secondPosition, ccpMult(normalVector, length2)))));
        eye_r->runAction(CCEaseSineInOut::create(CCMoveTo::create(0.1, ccpAdd(eye_r->m_secondPosition, ccpMult(normalVector, length2)))));
        
    }else{
        eye_l->setPosition(ccpAdd(eye_l->m_secondPosition, ccpMult(normalVector, length2)));
        eye_r->setPosition(ccpAdd(eye_r->m_secondPosition, ccpMult(normalVector, length2)));

    }
    
}

void E002_C010_P330::_eyesStop()
{
    CJSprite* eye_l = (CJSprite*)mBody->getChildByTag(_kPupil_l);
    CJSprite* eye_r = (CJSprite*)mBody->getChildByTag(_kPupil_r);
    eye_l->stopAllActions();
    eye_r->stopAllActions();
    eye_l->runAction(CCEaseSineInOut::create(CCMoveTo::create(0.1, eye_l->m_originPosition)));
    eye_r->runAction(CCEaseSineInOut::create(CCMoveTo::create(0.1, eye_r->m_originPosition)));
}

void E002_C010_P330::_mouseAnimation()
{
    
    CJSprite* mouse = (CJSprite*)mBody->getChildByTag(_kMouse);
    mouse->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(0),
                                                                CCDelayTime::create(0.1),
                                                                CCFadeIn::create(0),
                                                                CCDelayTime::create(0.1),
                                                                NULL)));
}

void E002_C010_P330::_mouseStop()
{
    CJSprite* mouse = (CJSprite*)mBody->getChildByTag(_kMouse);
    mouse->stopAllActions();
    mouse->setVisible(true);
}

void E002_C010_P330::_eyebrowAnimation()
{
    CJSprite* brow = (CJSprite*)mBody->getChildByTag(_kEyebrow);
    brow->setPosition(brow->m_originPosition);
    brow->runAction(CCRepeatForever::create(CCSequence::create(CCJumpBy::create(0.4, CCPointZero, 9, 1),
                                                               CCDelayTime::create(1.5),
                                                               CCJumpBy::create(0.8, CCPointZero, 9, 2),
                                                               CCDelayTime::create(3.5),
                                                               NULL)));
}

void E002_C010_P330::_bodyDownAnimation()
{
    mBody->runAction(CCRepeatForever::create(CCSequence::create(CCEaseSineInOut::create(CCMoveBy::create(1.0, ccp(0, 80))),
                                                                CCEaseSineInOut::create(CCMoveBy::create(1.0, ccp(0, -80))),
                                                                NULL)));
}

void E002_C010_P330::_whiteningAnimation()
{
    CJSprite* white = (CJSprite*)mBody->getChildByTag(0);
    white->runAction(CCRepeatForever::create(CCSequence::create(
                                                                CCFadeTo::create(0.1, 190),
                                                                CCFadeTo::create(0.4, 0),
                                                                CCDelayTime::create(0.5),
                                                                NULL)));
}


void E002_C010_P330::cloudHorizontal(CJSprite* pCloud, int pVec)
{
    CJSprite* cloud = pCloud;
    float posx = pVec > 0 ? winSize.width + 200 : -200 ;
    float dur = fabsf(posx - cloud->getPositionX() )/50.f;
//    CJLog("dur = %f", dur);
    
    cloud->runAction(CCSequence::create(CCMoveTo::create(dur, ccp(posx,cloud->getPositionY())),
                                        CCCallFuncND::create(this, callfuncND_selector(E002_C010_P330::cloudHorizontal),(void*)(pVec * -1)),                                                                NULL));
}

void E002_C010_P330::cloudVertical(CJSprite* pCloud, int duration)
{
    CJSprite* cloud = pCloud;
    float posY = winSize.height + 150 ;
    float dur = fabsf(posY - cloud->getPositionY() )/(float)duration;
//    CJLog("dur = %f", dur);
    
    cloud->runAction(CCSequence::create(CCMoveTo::create(dur, ccp(cloud->getPositionX(),posY)),
                                        CCMoveTo::create(0, cloud->m_secondPosition),
                                        CCCallFuncND::create(this, callfuncND_selector(E002_C010_P330::cloudVertical),(void*)duration),                                                                NULL));
}

//void E002_C010_P330::birdHorizontal(CJSprite* sp, int duration)
//{
//    float posx =  -200 ;
//    float dur = fabsf(posx - sp->getPositionX() )/(float)duration;
//    //    CJLog("dur = %f", dur);
//    
//    sp->runAction(CCSequence::create(CCMoveTo::create(dur, ccp(posx,sp->getPositionY())),
//                                     CCMoveTo::create(0, ccp(winSize.width + 100, sp->getPositionY())),
//                                     CCCallFuncND::create(this, callfuncND_selector(E002_C010_P330::birdHorizontal),(void*)duration),
//                                     NULL));
//}


void E002_C010_P330::birdVertical(CJSprite* sp, int duration)
{
    float posY = winSize.height + 150 ;
    float dur = fabsf(posY - sp->getPositionY() )/(float)duration;
    //    CJLog("dur = %f", dur);
    
    CCFiniteTimeAction* action = CCSequence::create(CCDelayTime::create(4.0),
                                                    CCMoveTo::create(dur, ccp(sp->getPositionX(),posY)),
                                                    CCMoveTo::create(0, ccp(sp->getPositionX(), sp->m_secondPosition.y)),
                                                    CCCallFuncND::create(this, callfuncND_selector(E002_C010_P330::birdVertical),(void*)duration),
                                                    NULL);
    action->setTag(0);
    sp->runAction(action);
    
}


void E002_C010_P330::completeFirstGuide()
{
    CJUtils::performSelector(this, callfunc_selector(E002_C010_P330::start),0.0);
    setTouchDisalbeBaseLayer();
}

void E002_C010_P330::showCompletePopup()
{
    E002_C010_CompletePopup *cPopup = new E002_C010_CompletePopup();
    cPopup->init(P300);
    addChild(cPopup, kDepth10_guide);
    
    cPopup->showPopup(this);
    cPopup->showCompletePopup();
}


#pragma mark - navigation delegate

void E002_C010_P330::onTouchedNavigationButtonAtIndex()
{
    E002_Base_Reward::onTouchedNavigationButtonAtIndex();
    E002_C010_P000_Index* _indexClass = E002_C010_P000_Index::create();
    _indexClass->init();
    _indexClass->setIndexDelegate(this);
    _indexClass->showIndex(this, _indexClass);
    addChild(_indexClass, kDepth11_Index);
    
}

void E002_C010_P330::onTouchedNavigationButtonAtInfo()
{
    E002_Base_Reward::onTouchedNavigationButtonAtInfo();
    std::vector<E002_Base_ImageGuide_Item*> *items = new std::vector<E002_Base_ImageGuide_Item*>();
    
    items->push_back(new E002_Base_ImageGuide_Item("e002_c010_p330_guide_00.jpg",
                                                   CJPsdParser::getPsdPosition("e002_common_img_guide_hand@00", m_psdDictionary),
                                                   CJPsdParser::getPsdPosition("e002_common_img_guide_hand@01", m_psdDictionary)
                                                   ));
    
    items->push_back(new E002_Base_ImageGuide_Item("e002_c010_p330_guide_01.jpg",
                                                   CJPsdParser::getPsdPosition("e002_common_img_guide_hand@03", m_psdDictionary),
                                                   CJPsdParser::getPsdPosition("e002_common_img_guide_hand@03", m_psdDictionary)
                                                   ));
    showGuide(items);

}

void E002_C010_P330::onTouchedNavigationButtonAtPrev()
{
    E002_Base_Reward::onTouchedNavigationButtonAtPrev();
    replaceSceneTransitionFadeOut(E002_C010_P310);
}

void E002_C010_P330::onTouchedNavigationButtonAtNext()
{
    E002_Base_Reward::onTouchedNavigationButtonAtNext();

    
}



#pragma mark - my util

CJSprite* E002_C010_P330::createSprite(std::string pStr)
{
    return CJPsdParser::getPsdSprite(pStr, m_psdDictionary);
}

void E002_C010_P330::_setPositionOutParent(CCNode* child, CCNode* newParent)
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

void E002_C010_P330::_safeRemoveFromParents(CCNode* pChild)
{
    if (pChild && pChild->getParent()) {
        pChild->removeFromParent();
    }
}

