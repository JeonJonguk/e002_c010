

#include "E002_C010_P110.h"
#include "E002_C010_BaseUtil.h"
#include "E002_C010_P000_Index.h"
#include "E002_C010_P130.h"


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
    
    _kTagStar,
    _kTagBg1,
    _kTagBg2,
    _kTagHighlight,
    
    _kTagParticleRun0,
    _kTagParticleRun1,
};

enum depth{
    _kDepthBackground = kDepth0_background,
    _kDepthBackImage = kDepth0_backImage,
    _kDepthLayer1 = 10,
    _kDepthLayer2 = 20,
    _kDepthLayer3 = 30,
    _kDepthLayer4 = 40,
    
    
};


E002_C010_P110::E002_C010_P110()
{
    
    mSndManager = new E002_C010_SoundManager;
    _arrBuildings = new CCArray();
    
    m_touchingExampleSp = NULL;
    _lastFireworkAni = NULL;
}

E002_C010_P110::~E002_C010_P110()
{
    CC_SAFE_DELETE(mSndManager);
}

#pragma mark - init

bool E002_C010_P110::init()
{
    if (!E002_Base_Question::init()) {
        return false;
    }
    
    m_nMaxStageCount = 8;
    m_nCurrentStageIndex = 2;
    
    return true;
}

void E002_C010_P110::onEnter()
{
    E002_Base_Question::onEnter();
    setTouchDisalbeBaseLayer();
    onViewLoad();
}

void E002_C010_P110::onExit()
{
    
    for (int i = 0; i < mQuestions.size(); i++) {
        CC_SAFE_RELEASE_NULL(mQuestions[i]);
    }
    
    unschedule(schedule_selector(E002_C010_P110::checkSchedule));
    
    
    E002_Base_Question::onExit();
}


void E002_C010_P110::onViewLoad()
{
    E002_Base_Question::onViewLoad();
    
    std::string questionsTxtName[8] =
    {
        "e002_c010_p110_img_que00_txt_00", //guide
        "e002_c010_p110_img_que01_txt_00", //guide
        "e002_c010_p110_img_que00_txt_02",
        "e002_c010_p110_img_que01_txt_02",
        "e002_c010_p110_img_que02_txt_00",
        "e002_c010_p110_img_que03_txt_00",
        "e002_c010_p110_img_que04_txt_00",
        "e002_c010_p110_img_que05_txt_00",
    };
    
    std::string questionsSuccessTxtName[8] =
    {
        "e002_c010_p110_img_que00_txt_01",  //guide
        "e002_c010_p110_img_que01_txt_01",  //guide
        "e002_c010_p110_img_que00_txt_03",
        "e002_c010_p110_img_que01_txt_03",
        "e002_c010_p110_img_que02_txt_01",
        "e002_c010_p110_img_que03_txt_01",
        "e002_c010_p110_img_que04_txt_01",
        "e002_c010_p110_img_que05_txt_01",
    };
    
    std::string questionsSuccessImgName[8] =
    {
        "e002_c010_p110_img_que00_txt_04",  //guide
        "e002_c010_p110_img_que01_txt_04",  //guide
        "e002_c010_p110_img_que00_txt_05",
        "e002_c010_p110_img_que01_txt_05",
        "e002_c010_p110_img_que02_txt_02",
        "e002_c010_p110_img_que03_txt_02",
        "e002_c010_p110_img_que04_txt_02",
        "e002_c010_p110_img_que05_txt_02",
    };
    
    
    std::string questionsSndName[8] =
    {
        wordSoundFileNames[20],  //guide
        wordSoundFileNames[21],  //guide
        wordSoundFileNames[22],
        wordSoundFileNames[23],
        wordSoundFileNames[28],
        wordSoundFileNames[29],
        wordSoundFileNames[30],
        wordSoundFileNames[31],
    };
    
    std::string questionsSucSndName[8] =
    {
        wordSoundFileNames[4], //guide
        wordSoundFileNames[5], //guide
        wordSoundFileNames[8],
        wordSoundFileNames[9],
        wordSoundFileNames[12],
        wordSoundFileNames[13],
        wordSoundFileNames[18],
        wordSoundFileNames[19],
    };
    
    
    for (int i = 0; i < m_nMaxStageCount; i++)
    {
        
        SSQuestionItem* item = SSQuestionItem::create(questionsSuccessImgName[i],
                                                      questionsTxtName[i],
                                                      questionsSuccessTxtName[i],
                                                      "",
                                                      questionsSndName[i],
                                                      questionsSucSndName[i],
                                                      "");
        item->retain();
        mQuestions.push_back(item);
    }
    
    
    CJPsdParser::parseToPsdJSON("e002_c010_p110.json", &m_psdDictionary);
    
    setBackground("e002_c010_p110_img_bg_00.jpg");
    CJSprite* star = createSprite("e002_c010_p110_img_star");
    star->setAnchorPoint(ccp(0, 1));
    star->setPosition(ccp(0,winSize.height));
    
    //layer 1 ============================================================================ // small buildings
    layer1 = CJSprite::create();
    layer1->setContentSize(winSize);
    layer1->setAnchorPoint(CCPointZero);
    layer1->setPosition(CCPointZero);
    
    CJSprite* bg1 = createSprite("e002_c010_p110_img_bg_01");
    CJSprite* bg1_2 = createSprite("e002_c010_p110_img_bg_01");
    bg1->setAnchorPoint(CCPointZero);
    bg1->setPosition(ccp(0, 175));
    bg1_2->setAnchorPoint(CCPointZero);
    bg1_2->setPosition(ccp(bg1->getContentSize().width, 0));
    bg1->addChild(bg1_2);
    layer1->addChild(bg1, _kDepthLayer1, _kTagBg1);
    
    
    //layer 2 ============================================================================ // buildings (main layer)
    layer2 = CJSprite::create();
    layer2->setContentSize(winSize);
    layer2->setAnchorPoint(CCPointZero);
    layer2->setPosition(CCPointZero);
    
    CJSprite* bg2 = createSprite("e002_c010_p110_img_bg_02");
    CJSprite* bg2_2 = createSprite("e002_c010_p110_img_bg_02");
    bg2->setAnchorPoint(CCPointZero);
    bg2->setPosition(CCPointZero);
    bg2_2->setAnchorPoint(CCPointZero);
    bg2_2->setPosition(ccp(bg2->getContentSize().width, 0));
    bg2->addChild(bg2_2);
    layer2->addChild(bg2, 0, _kTagBg2);
    
    //set buildings
    for (int i = 0; i < m_nMaxStageCount; i++) {
        int temp = 0;
        if (i < 2) {
            temp = i;
        }else{
            temp = i - 2;
        }
        CJSprite* building = createSprite(CJUtils::getStringFormatInteger("e002_c010_p110_img_que0%d_bg",temp));
        CJSprite* highlight = createSprite(CJUtils::getStringFormatInteger("e002_c010_p110_img_que0%d_00",temp));
        building->addChildIgnoreParent(highlight);
        highlight->setTag(_kTagHighlight);
        highlight->setOpacity(0);
        
        _arrBuildings->addObject(building);
        float addX = LAYER_DISTANCE * (i/2);
        building->setPositionX(building->getPositionX()+addX);
        layer2->addChildIgnoreParent(building);
    }
    
    //set buiding side
    for (int i = 0; i < m_nMaxStageCount-1; i++) {
        for (int j = 0; j < 3; j++) {
            CJSprite* object = createSprite(CJUtils::getStringFormatInteger("e002_c010_p110_img_que_object_0%d",j));
            layer2->addChild(object,kDepth0_backImage);
            
            float addX = (LAYER_DISTANCE/2) * i;
            object->setPositionX(object->getPositionX()+addX);
        }
    }
    
    
    
    //layer 3 ============================================================================
    layer3 = CJSprite::create();
    layer3->setContentSize(winSize);
    layer3->setAnchorPoint(CCPointZero);
    layer3->setPosition(CCPointZero);
    
    
    //layer 4 ============================================================================
    layer4 = CJSprite::create();
    layer4->setContentSize(winSize);
    layer4->setAnchorPoint(CCPointZero);
    layer4->setPosition(CCPointZero);
    
    // top trees
    for (int i = 0; i < m_nMaxStageCount+2; i++) {
        float addX = (LAYER_DISTANCE/2) * i;
        CJSprite* treeObject1 = createSprite("e002_c010_p110_img_object_00_00");
        //        CJSprite* treeObject2 = createSprite("e002_c010_p110_img_object_00_01");
        CJSprite* treeObject3 = createSprite("e002_c010_p110_img_object_01_00");
        CJSprite* treeObject4 = createSprite("e002_c010_p110_img_object_01_01");
        treeObject1->setPositionX(treeObject1->getPositionX() + addX);
        //        treeObject2->setPositionX(treeObject2->getPositionX() + addX);
        treeObject3->setPositionX(treeObject3->getPositionX() + addX);
        treeObject4->setPositionX(treeObject4->getPositionX() + addX);
        
        layer4->addChild(treeObject1);
        //        layer4->addChild(treeObject2);
        layer4->addChild(treeObject3);
        layer4->addChild(treeObject4);
    }
    
    
    mDimm = CJSprite::createWithFullPath("e002_c010_p110_img_bg_dim.png");
    mDimm->setAnchorPoint(CCPointZero);
    mDimm->setPosition(CCPointZero);
    
    
    parallaxLayer = CCParallaxNode::create();
    float temp = star->getContentSize().width / (LAYER_DISTANCE * 4.5);
    CJLog("temp value = %f",temp);
    parallaxLayer->addChild(star, _kDepthLayer1+1, ccp(0.05, 0),star->getPosition());
    parallaxLayer->addChild(layer1, _kDepthLayer1, ccp(0.5, 0), CCPointZero);
    parallaxLayer->addChild(layer2, _kDepthLayer2, ccp(1.0, 0), CCPointZero);
    parallaxLayer->addChild(layer3, _kDepthLayer3, ccp(0, 0), CCPointZero);
    parallaxLayer->addChild(layer4, _kDepthLayer4, ccp(1.5, 0), CCPointZero);
    parallaxLayer->addChild(mDimm, _kDepthLayer1+1,ccp(0, 0), CCPointZero);
    addChild(parallaxLayer, _kDepthLayer1, 10);
    
    
    
    
    float dist = ((CJSprite*)_arrBuildings->objectAtIndex(m_nCurrentStageIndex))->getPositionX() - ((CJSprite*)_arrBuildings->objectAtIndex(0))->getPositionX();
    parallaxLayer->setPositionX(parallaxLayer->getPositionX()-dist);
    checkSchedule();
    
    
    
    
    if(m_bIsGuide)
    {
        CCSprite* dim = CCSprite::create();
        dim->setTextureRect(CCRectMake(0, 0, winSize.width, winSize.height));
        dim->setColor(ccBLACK);
        dim->setContentSize(CCSizeMake(winSize.width, winSize.height));
        dim->setPosition(CCPointZero);
        dim->setAnchorPoint(CCPointZero);
        dim->setOpacity(190);
        dim->setZOrder(_kDepthLayer1);
        parallaxLayer->addChild(dim,_kDepthLayer1, ccp(0, 0),CCPointZero);
    }
    
    // FLASH
    setAnimationFile("e002_c010_p110_flash_as_sheets.json", "e002_c010_p110_flash_as_animations.json", FLASH_ANISON);
    setAnimationFile("e002_c010_p110_flash_gb_sheets.json", "e002_c010_p110_flash_gb_animations.json", FLASH_GRUM);
    setAnimationFile("e002_c010_p130_flash_firework_sheets.json", "e002_c010_p130_flash_firework_animations.json", FLASH_FIRE);
    animationManagerParseStart();
    
}

void E002_C010_P110::onViewLoaded()
{
    E002_Base_Question::onViewLoaded();
    
    
    
    
}

void E002_C010_P110::startFlashAnimation()
{
    createAnimationAndSetKey(FLASH_ANISON, "e002_c010_p110_flash_sun_n01_loop", FLASH_KEY_LOOPING);
    createAnimationAndSetKey(FLASH_ANISON, "e002_c010_p110_flash_sun_s01_action", FLASH_KEY_SUCCESS);
    createAnimationAndSetKey(FLASH_ANISON, "e002_c010_p110_flash_sun_s02_run", FLASH_KEY_RUN);
    createAnimationAndSetKey(FLASH_ANISON, "e002_c010_p110_flash_sun_n02_speak", FLASH_KEY_SPEAK);
    
    
    createAnimationAndSetKey(FLASH_GRUM, "e002_c010_p110_flash_gb_n01_loop", FLASH_KEY_SPEAK);
    createAnimationAndSetKey(FLASH_GRUM, "e002_c010_p110_flash_gb_n02_loop", FLASH_KEY_LOOPING);
    createAnimationAndSetKey(FLASH_GRUM, "e002_c010_p110_flash_gb_n02_action", FLASH_KEY_LOOPING2);
    createAnimationAndSetKey(FLASH_GRUM, "e002_c010_p110_flash_gb_s01_action", FLASH_KEY_SUCCESS);
    createAnimationAndSetKey(FLASH_GRUM, "e002_c010_p110_flash_gb_s02_loop", FLASH_KEY_RUN);
    createAnimationAndSetKey(FLASH_GRUM, "e002_c010_p110_flash_gb_n02_action_2", FLASH_KEY_ACTION1);
    createAnimationAndSetKey(FLASH_GRUM, "e002_c010_p110_flash_gb_n02_action_2_1", FLASH_KEY_ACTION1_2);
    createAnimationAndSetKey(FLASH_GRUM, "e002_c010_p110_flash_gb_n02_action_1", FLASH_KEY_ACTION2);
    createAnimationAndSetKey(FLASH_GRUM, "e002_c010_p110_flash_gb_n02_action_1_1", FLASH_KEY_ACTION2_2);
    
    
    
    _playAnimationAnison(FLASH_KEY_LOOPING);
    _playAnimationGrumbie(FLASH_KEY_SPEAK);
    
    
    
    createAnimationAndSetKey(FLASH_FIRE, "e002_c010_p130_flash_firework_00", FLASH_KEY_FIRE0);
    createAnimationAndSetKey(FLASH_FIRE, "e002_c010_p130_flash_firework_01", FLASH_KEY_FIRE1);
    createAnimationAndSetKey(FLASH_FIRE, "e002_c010_p130_flash_firework_02", FLASH_KEY_FIRE2);
    createAnimationAndSetKey(FLASH_FIRE, "e002_c010_p130_flash_firework_03", FLASH_KEY_FIRE3);
    createAnimationAndSetKey(FLASH_FIRE, "e002_c010_p130_flash_firework_04", FLASH_KEY_FIRE4);
    createAnimationAndSetKey(FLASH_FIRE, "e002_c010_p130_flash_firework_05", FLASH_KEY_FIRE5);
    
    if(m_bIsGuide)
    {
        CJUtils::performSelector(this, callfunc_selector(E002_Base_Question::removeTouchDelegateForGuide), 0.5);
        CJUtils::performSelector(this, callfunc_selector(E002_C010_P110::start),0.3);
    }
    else
    {
        CJUtils::performSelector(this, callfunc_selector(E002_C010_P110::onFirstNarration),1.5);
    }
}

void E002_C010_P110::onFirstNarration()
{
    E002_Base_Question::onFirstNarration();
    
    mFirstNarration = "e002_c010_p110_snd_01_as.mp3";
    playNarration(mFirstNarration);
    _playAnimationAnison(FLASH_KEY_SPEAK);
}

void E002_C010_P110::onFirstNarrationEnd()
{
    E002_Base_Question::onFirstNarrationEnd();
    setTouchDisalbeBaseLayer();
    
    
    //    if (getUserDefaultFirstGuide(eGuidePageP110) == false)
    //    {
    mShowFirstGuide = true;
    setUserDefaultFirstGuide(eGuidePageP110);
    showGuide();
    //    }
    //    else
    //    {
    //        start();
    //    }
    
}

void E002_C010_P110::onNarrationFinishedCallback(std::string fileName)
{
    if (fileName == mFirstNarration && !isFirstSkiped())
    {
        onFirstNarrationEnd();
    }
    else if (fileName == mFirstNarration)
    {
        removeAllAnimationsInDataPool(FLASH_ANISON);
        _playAnimationAnison(FLASH_KEY_LOOPING);
        //        _playAnimationGrumbie(FLASH_KEY_LOOPING);
    }
    
}

#pragma mark - touch

bool E002_C010_P110::onTouchBegan(CCPoint tp)
{
    
    CJSprite* queImg = mQuestions[m_nCurrentStageIndex]->txtSprite;
    if (queImg && CJUtils::hitTestPoint(queImg, tp, false)) {
        stopSpeakingAndLooping();
        mQuestions[m_nCurrentStageIndex]->playEffect();
        mQuestions[m_nCurrentStageIndex]->playAction(mQuestions[m_nCurrentStageIndex]->txtSprite);
        return false;
    }
    
    if (m_nCurrentStageIndex%2==0) {
        CJSprite* nextQueImg = mQuestions[m_nCurrentStageIndex+1]->txtSprite;
        if (nextQueImg && CJUtils::hitTestPoint(nextQueImg, tp, false)) {
            stopSpeakingAndLooping();
            mQuestions[m_nCurrentStageIndex+1]->playEffect();
            mQuestions[m_nCurrentStageIndex+1]->playAction(mQuestions[m_nCurrentStageIndex+1]->txtSprite);
            return false;
        }
    }else{
        CJSprite* prevQueImg = mQuestions[m_nCurrentStageIndex-1]->txtSprite;
        if (prevQueImg && CJUtils::hitTestPoint(prevQueImg, tp, false)) {
            stopSpeakingAndLooping();
            mQuestions[m_nCurrentStageIndex-1]->playSuccessSound();
            mQuestions[m_nCurrentStageIndex-1]->playAction(mQuestions[m_nCurrentStageIndex-1]->txtSprite);
            return false;
        }
        
    }
    
    
    
    
    if (CJUtils::hitTestPoint(getAnimationByKey(FLASH_GRUM, FLASH_KEY_LOOPING),tp, false)) {
        
        stopSpeakingAndLooping();
        intoTarget(NULL, tp);
    }
    
    if (CJUtils::hitTestPoint(getAnimationByKey(FLASH_ANISON, FLASH_KEY_SPEAK),tp, false)) {
        
        playNarration(mFirstNarration);
        _playAnimationAnison(FLASH_KEY_SPEAK);
        
    }
    
    if(m_bIsGuide)
    {
        if (m_currentGuideIndex == 0)
        {
            //            showHand(NULL, 1);
        }
    }
    
    
    return false;
}

void E002_C010_P110::onTouchMoved(CCPoint tp)
{
}

void E002_C010_P110::onTouchEnded(CCPoint tp)
{
}

#pragma mark - check

void E002_C010_P110::intoTarget(CJSprite* sp, CCPoint pt)
{
    setTouchDisalbeBaseLayer();
    
    CJAnimation* ani = getAnimationByKey(FLASH_GRUM, FLASH_KEY_LOOPING);
    CCSprite* gun = getSpriteFromFlash(ani,"e002_c010_p110_flash_g3_n02_action_gun");
    CJSprite* e = (CJSprite*)gun->getChildByTag(0);
    if (e) {
        e->removeFromParent();
    }
    //    e->runAction(CCSequence::create(CCScaleTo::create(0.05, 1.1),
    //                                    CCScaleTo::create(0.05, 1.00),
    //                                    CCScaleTo::create(0.05, 1.1),
    //                                    CCScaleTo::create(0.05, 1.00),
    //                                    CCScaleTo::create(0.05, 1.1),
    //                                    CCScaleTo::create(0.05, 1.00),
    //                                    CCScaleTo::create(0.05, 1.1) ,
    //                                    CCEaseSineOut::create(CCScaleTo::create(0.05, 0.0)),
    //                                    CCCallFunc::create(e, callfunc_selector(CJSprite::removeFromParent)),
    //                                    NULL));
    
    
    
    CJAnimation* shoot = NULL;
    if ( _currentQuestionItem->txtSprite->getParent()->convertToWorldSpace(_currentQuestionItem->txtSprite->getPosition()).y > 460) {
        shoot = _playAnimationGrumbie(FLASH_KEY_ACTION1, 1);
    }else{
        shoot = _playAnimationGrumbie(FLASH_KEY_ACTION2, 1);
    }
    
    playEffectWithDelay(wordSoundFileNames[1], 0.3);
    CJUtils::performSelector(this, callfunc_selector(E002_C010_P110::shootTheGun),1.2);
    
    addChild(E002_C010_BaseUtil::addParticle("e002_c010_p110_gun.plist"),kDepth5_particle);
    
}

void E002_C010_P110::shootTheGun()
{
    CJAnimation* shoot = NULL;
    if ( _currentQuestionItem->txtSprite->getParent()->convertToWorldSpace(_currentQuestionItem->txtSprite->getPosition()).y > 460) {
        shoot = _playAnimationGrumbie(FLASH_KEY_ACTION1_2, 1);
    }else{
        shoot = _playAnimationGrumbie(FLASH_KEY_ACTION2_2, 1);
    }
    
    playEffect("e002_c010_p110_sfx_shooting.mp3");
    shoot->addCustomFrameCallback(this, callfuncND_selector(E002_C010_P110::changeQuestionText), 5, shoot);
    
}

void E002_C010_P110::changeQuestionText(CCNode* sender, void* pData)
{
    CJAnimation* shoot = (CJAnimation*)pData;
    //    shoot->removeParticularAllFrame();
    shoot->removeParticularFrameCallback(5);
    
    mQuestions[m_nCurrentStageIndex]->txtSprite->runAction(CCSequence::create(CCMoveBy::create(0.1, ccp(5,0)),
                                                                              CCMoveBy::create(0.1, ccp(-5,0)),
                                                                              NULL));
    mQuestions[m_nCurrentStageIndex]->txtSprite->changeTextureWithFullPath(mQuestions[m_nCurrentStageIndex]->sucTxt+".png");
    
    playFirework();
    playEffect("e002_c010_p110_sfx_sum.mp3");
}


void E002_C010_P110::checkAnswer(CCNode *node)
{
    mQuestions[m_nCurrentStageIndex]->txtSprite->setOpacity(0);
    
    CJSprite* img = mQuestions[m_nCurrentStageIndex]->imgSprite;
    img->setOpacity(255);
    mQuestions[m_nCurrentStageIndex]->playAction(img);
    mQuestions[m_nCurrentStageIndex]->playSuccessSound();
    CJUtils::performSelector(this, callfuncND_selector(E002_C010_P110::onSuccesses),NULL, 1.5);
}

#pragma mark - feedback event

void E002_C010_P110::onSuccesses(CCNode *node, int tag)
{
    CCLog("onSuccess");
    _playAnimationAnison(FLASH_KEY_SUCCESS, 1);
    _playAnimationGrumbie(FLASH_KEY_SUCCESS, 1);
    
    playEffect("e002_c010_p110_sfx_jump_as.mp3");
    playEffect("e002_c010_p110_sfx_jump_gb.mp3");
    
    mSndManager->playCorrectNarrationAnison(E002_C010_SoundManager::p110);
    mSndManager->playCorrectNarrationOtherOne(E002_C010_SoundManager::p110);
    
    CJSprite* building = (CJSprite*)_arrBuildings->objectAtIndex(m_nCurrentStageIndex);
    CJSprite* highlight = (CJSprite*) building->getChildByTag(_kTagHighlight);
    
    int temp = m_nCurrentStageIndex < 2 ? m_nCurrentStageIndex : m_nCurrentStageIndex - 2;
    std::string fileName1 = CJUtils::getStringFormatInteger("e002_c010_p110_img_que0%d_00.png",temp);
    std::string fileName2 = CJUtils::getStringFormatInteger("e002_c010_p110_img_que0%d_01.png",temp);
    highlight->setOpacity(255);
    highlight->runAction(CJUtils::getSeqAction(-1,
                                               0.1,
                                               getImageFilePath(fileName1).c_str(),
                                               getImageFilePath(fileName2).c_str(),
                                               NULL));
    
    mDimm->runAction(CCFadeTo::create(0.5,  mDimm->getOpacity()-120.f));
    
    //    lightingColorAnimation(highlight);
    
    
}


void E002_C010_P110::onHalfSuccess(CCNode *node, int tag)
{
    
}

void E002_C010_P110::onFails(CCNode *node, int tag)
{
    CJLog("onFail");
}

void E002_C010_P110::flashSuccessFinishCallback(CJAnimation* pAnimation)
{
    
}

//void E002_C010_P110::flashFailFinishCallback(CJAnimation* pAnimation)
//{
//    setTouchEnableBaseLayer();
//
//}

void E002_C010_P110::onComplete()
{
    E002_Base_Question::onComplete();
    
    CJSprite* building = (CJSprite*)_arrBuildings->objectAtIndex(m_nCurrentStageIndex);
    CJSprite* highlight = (CJSprite*) building->getChildByTag(_kTagHighlight);
    highlight->stopAllActions();
    
    if (m_nCurrentStageIndex < m_nMaxStageCount-1) {

        m_nCurrentStageIndex++;
        questionAppearStep1();
    }else{
        CJAnimation* ani1 = _playAnimationGrumbie(FLASH_KEY_RUN);
        CJAnimation* ani2 = _playAnimationAnison(FLASH_KEY_RUN);
        ani1->runAction(CCSequence::create(CCEaseSineIn::create(CCMoveBy::create(1.0, ccp(1000,0))),
                                           NULL));
        
        ani2->runAction(CCSequence::create(CCEaseSineIn::create(CCMoveBy::create(1.0, ccp(1000,0))),
                                           CCDelayTime::create(0.5),
                                           CCCallFunc::create(this, callfunc_selector(E002_C010_P110::onEnd)),
                                           NULL));
        
        
        parallaxLayer->runAction(CCSequence::create(CCEaseSineIn::create(CCMoveBy::create(1.0, ccp(-200, 0))),
                                                    NULL));
        
        
    }
    
}

void E002_C010_P110::onEnd()
{
    completeLetsPlay1();
    replaceSceneTransitionFadeOut(E002_C010_P130);
}

#pragma mark - set questions, set examples
void E002_C010_P110::start()
{
    _playAnimationAnison(FLASH_KEY_LOOPING);
    _playAnimationGrumbie(FLASH_KEY_LOOPING, 3);
    
    setQuestions();
}

void E002_C010_P110::setQuestions()
{
    
    if (m_nCurrentStageIndex == 3) {
        E002_Base_Navigation::setVisibleButton(false, eNavigationButton_Prev);
    }else if(m_nCurrentStageIndex > 3){
        E002_Base_Navigation::setVisibleButton(true, eNavigationButton_Prev);
    }
    
    _currentQuestionItem = mQuestions[m_nCurrentStageIndex];
    CJSprite* currentBuilding = (CJSprite*) _arrBuildings->objectAtIndex(m_nCurrentStageIndex);
    
    if (m_nCurrentStageIndex%2 == 0) {
        
        //set next question
        CJSprite* nextBuilding = (CJSprite*) _arrBuildings->objectAtIndex(m_nCurrentStageIndex+1);
        CJSprite* sideQuestion = mQuestions[m_nCurrentStageIndex+1]->txtSprite;
        if (!sideQuestion) {
            sideQuestion = mQuestions[m_nCurrentStageIndex+1]->createTxtSprite(m_psdDictionary);
            nextBuilding->addChildIgnoreParent(sideQuestion, 100);
        }
        sideQuestion->setPositionX(nextBuilding->getContentSize().width/2);
        sideQuestion->setOpacity(0);
        
        
        CJSprite* nextImg = mQuestions[m_nCurrentStageIndex+1]->imgSprite;
        if (!nextImg) {
            nextImg = mQuestions[m_nCurrentStageIndex+1]->createImgSprite(m_psdDictionary);
            nextImg->setPosition(sideQuestion->getPosition());
            nextBuilding->addChild(nextImg, 100);
            //            (mQuestions[m_nCurrentStageIndex+1]->txtSprite->getParent())-> addChild(nextImg, mQuestions[m_nCurrentStageIndex+1]->txtSprite->getZOrder());
        }
        nextImg->setOpacity(0);
        
        
        
        //set current question
        CJSprite* question = _currentQuestionItem->txtSprite;
        if (!question) {
            question = _currentQuestionItem->createTxtSprite(m_psdDictionary);
            currentBuilding->addChildIgnoreParent(question, 100);
        }
        
        question->setPositionX(currentBuilding->getContentSize().width/2);
        question->setOpacity(0);
        question->runAction(CCSpawn::create(CCFadeIn::create(0.5),
                                            CCSequence::create(CCFadeTo::create(0, 255),
                                                               CCDelayTime::create(0.2),
                                                               CCFadeTo::create(0, 0),
                                                               
                                                               CCDelayTime::create(0.1),
                                                               CCFadeTo::create(0, 255),
                                                               CCDelayTime::create(0.1),
                                                               CCFadeTo::create(0, 0),
                                                               
                                                               CCDelayTime::create(0.04),
                                                               CCFadeTo::create(0, 255),
                                                               CCDelayTime::create(0.04),
                                                               CCFadeTo::create(0, 0),
                                                               
                                                               CCDelayTime::create(0.04),
                                                               CCFadeTo::create(0, 255),
                                                               CCDelayTime::create(0.04),
                                                               CCFadeTo::create(0, 0),
                                                               
                                                               CCDelayTime::create(0.1),
                                                               CCFadeTo::create(0, 255),
                                                               CCCallFunc::create(this, callfunc_selector(E002_C010_P110::setSideQuestion)),
                                                               NULL),
                                            NULL));
        
        //create img sprite
        CJSprite* img = mQuestions[m_nCurrentStageIndex]->imgSprite;
        if (!img) {
            img = mQuestions[m_nCurrentStageIndex]->createImgSprite(m_psdDictionary);
            img->setPosition(question->getPosition());
            currentBuilding->addChild(img, 100);
            //            (mQuestions[m_nCurrentStageIndex]->txtSprite->getParent())-> addChild(img, mQuestions[m_nCurrentStageIndex]->txtSprite->getZOrder());
        }
        img->setOpacity(0);
        
    }
    else
    {
        showQuestions();
    }
}

void E002_C010_P110::setSideQuestion()
{
    CJSprite* question =  mQuestions[m_nCurrentStageIndex+1]->txtSprite;
    question->runAction(CCSpawn::create(CCFadeIn::create(0.5),
                                        CCSequence::create(CCFadeTo::create(0, 255),
                                                           CCDelayTime::create(0.2),
                                                           CCFadeTo::create(0, 0),
                                                           
                                                           CCDelayTime::create(0.1),
                                                           CCFadeTo::create(0, 255),
                                                           CCDelayTime::create(0.1),
                                                           CCFadeTo::create(0, 0),
                                                           
                                                           CCDelayTime::create(0.04),
                                                           CCFadeTo::create(0, 255),
                                                           CCDelayTime::create(0.04),
                                                           CCFadeTo::create(0, 0),
                                                           
                                                           CCDelayTime::create(0.04),
                                                           CCFadeTo::create(0, 255),
                                                           CCDelayTime::create(0.04),
                                                           CCFadeTo::create(0, 0),
                                                           
                                                           CCDelayTime::create(0.1),
                                                           CCFadeTo::create(0, 255),
                                                           CCDelayTime::create(0.2),
                                                           CCCallFunc::create(this, callfunc_selector(E002_C010_P110::showQuestions)),
                                                           NULL),
                                        NULL));
}

void E002_C010_P110::showQuestions()
{
    _currentQuestionItem->txtSprite->setOpacity(255);
    _currentQuestionItem->playEffect();
    _currentQuestionItem->playAction(mQuestions[m_nCurrentStageIndex]->txtSprite);
    CJUtils::performSelector(this, callfunc_selector(E002_C010_P110::showExamples),1.0);
}

void E002_C010_P110::showExamples()
{
    playEffect(wordSoundFileNames[1]);
    CJUtils::performSelector(this, callfunc_selector(E002_C010_P110::setTouchEnableBaseLayer),0.5);
    CJAnimation* ani = getAnimationByKey(FLASH_GRUM, FLASH_KEY_LOOPING);
    CCSprite* sp = getSpriteFromFlash(ani,"e002_c010_p110_flash_g3_n02_action_gun");
    CJSprite* e = CJSprite::createWithFullPath("e002_c010_p110_flash_gb_n02_e.png");
    e->setPosition(ccp(43, 66));
    e->setRotation(-sp->getRotation());
    sp->addChild(e,0,0);
    e->setScale(0);
    e->runAction(CCSequence::create(CCScaleTo::create(0.1, 1.1),
                                    CCDelayTime::create(0.2),
                                    CCScaleTo::create(0.1, 1.0),
                                    NULL));
    
    if (m_bIsGuide)
    {
        this->runAction(CCSequence::create(CCDelayTime::create(1.5),
                                           CCCallFuncND::create(this, callfuncND_selector(E002_C010_P110::showHand), (void*)0),
                                           NULL)); //showHand(NULL, 0);
        return;
    }
    
    
}

void E002_C010_P110::resetValue()
{
    _successCount = 0;
    setTouchDisalbeBaseLayer();
    stopAllNarration();
    stopAllEffect();
    CJUtils::stopAllAnimations(this);
    removeAllAnimations();
    
    //dimmed
    mDimm->setOpacity(255);
    
    //layer position
    int tempIndex = m_nCurrentStageIndex >= m_nMaxStageCount ? m_nMaxStageCount-1 : m_nCurrentStageIndex;
    float dist = ((CJSprite*)_arrBuildings->objectAtIndex(tempIndex))->getPositionX() - winCenter.x;
    parallaxLayer->setPositionX(-dist);;
    
    CJSprite* bg1 =(CJSprite*)layer1->getChildByTag(_kTagBg1);
    CJSprite* bg2 =(CJSprite*)layer2->getChildByTag(_kTagBg2);
    bg1->setPositionX(dist*0.5);
    bg2->setPositionX(dist);
    
    
    // flash sprite'e'
    CJAnimation* ani = getAnimationByKey(FLASH_GRUM, FLASH_KEY_LOOPING);
    CCSprite* gun = getSpriteFromFlash(ani,"e002_c010_p110_flash_g3_n02_action_gun");
    CJSprite* e = (CJSprite*)gun->getChildByTag(0);
    if (e) {
        e->removeFromParent();
    }

    
    if (mQuestions[m_nCurrentStageIndex]->txtSprite) {
        mQuestions[m_nCurrentStageIndex]->txtSprite->changeTextureWithFullPath(mQuestions[m_nCurrentStageIndex]->txt+".png");
        mQuestions[m_nCurrentStageIndex+1]->txtSprite->changeTextureWithFullPath(mQuestions[m_nCurrentStageIndex+1]->txt+".png");

    }
    
    
}

void E002_C010_P110::checkSchedule()
{
    
    CJSprite* bg2 =(CJSprite*)layer2->getChildByTag(_kTagBg2);
    int nForLayer2Position = (int)(bg2->getPositionX() / bg2->getContentSize().width);
    
    if (parallaxLayer->getPositionX() < -bg2->getContentSize().width * (nForLayer2Position+1)) {
        nForLayer2Position++;
        CJLog("+nForLayer2Position = %d" ,nForLayer2Position);
        bg2->setPositionX(bg2->getContentSize().width * nForLayer2Position);
    }
    if (parallaxLayer->getPositionX() > -bg2->getContentSize().width*(nForLayer2Position)) {
        nForLayer2Position--;
        CJLog("-nForLayer2Position = %d" ,nForLayer2Position);
        bg2->setPositionX(bg2->getContentSize().width * nForLayer2Position);
    }
    
    
    CJSprite* bg1 =(CJSprite*)layer1->getChildByTag(_kTagBg1);
    int nForLayer1Position = (int)(bg1->getPositionX() / bg1->getContentSize().width);
    
    if (parallaxLayer->getPositionX()*0.5 < -bg1->getContentSize().width*(nForLayer1Position+1)) {
        nForLayer1Position++;
        bg1->setPositionX(bg1->getContentSize().width * nForLayer1Position);
        CJLog("+nForLayer1Position = %d" ,nForLayer1Position);
    }
    if (parallaxLayer->getPositionX()*0.5 > -bg1->getContentSize().width*(nForLayer1Position)) {
        nForLayer1Position--;
        bg1->setPositionX(bg1->getContentSize().width * nForLayer1Position);
        CJLog("-nForLayer1Position = %d" ,nForLayer1Position);
    }
    
    
}

#pragma mark - appear, disappear



void E002_C010_P110::questionAppearStep1()
{
    _playAnimationGrumbie(FLASH_KEY_RUN);
    _playAnimationAnison(FLASH_KEY_RUN);
    
    
    float dist = 0;
    dist = ((CJSprite*)_arrBuildings->objectAtIndex(m_nCurrentStageIndex-1))->getPositionX() - ((CJSprite*)_arrBuildings->objectAtIndex(m_nCurrentStageIndex))->getPositionX();
    CJLog("dist = %.2f",dist);
    float duration = -dist < 1000 ? 1.5 : 3.5 ;
    parallaxLayer->runAction(CCSequence::create(CCEaseSineInOut::create(CCMoveBy::create(duration, ccp(dist, 0))),
                                                CCCallFunc::create(this, callfunc_selector(E002_C010_P110::questionAppearStep2)),
                                                NULL));
    schedule(schedule_selector(E002_C010_P110::checkSchedule), 1/60.f);
    
    std::string snd = -dist < 1000 ? "e002_c010_p000_sfx_run.mp3" : "e002_c010_p000_sfx_run02.mp3" ;
    playEffect(snd);
    
    
    if (m_nCurrentStageIndex%2 == 0) {
        mDimm->runAction(CCEaseSineInOut::create(CCFadeIn::create(duration)));
    }
    
    
    
    addChild(E002_C010_BaseUtil::addParticle("e002_c010_p110_run_00.plist"),kDepth5_particle, _kTagParticleRun0);
    addChild(E002_C010_BaseUtil::addParticle("e002_c010_p110_run_01.plist"),kDepth5_particle, _kTagParticleRun1);
    
    
    
}

void E002_C010_P110::questionAppearStep2()
{
    unschedule(schedule_selector(E002_C010_P110::checkSchedule));
    
    CCParticleSystemQuad* run0 = (CCParticleSystemQuad*)getChildByTag(_kTagParticleRun0);
    CCParticleSystemQuad* run1 = (CCParticleSystemQuad*)getChildByTag(_kTagParticleRun1);
    run0->stopSystem();
    run1->stopSystem();
    
    start();
}
void E002_C010_P110::disappearAnimation()
{
    
}

void E002_C010_P110::OnLastFrame(CJAnimation* pAnimation)
{
    E002_C010_BaseUtil::OnLastFrame(pAnimation);
    
    if (pAnimation == _lastFireworkAni) {
        checkAnswer(NULL);
    }
    
    if (pAnimation->getKey() == FLASH_KEY_SUCCESS) {
        static int cnt = 0;
        cnt++;
        if (cnt == 2) {
            cnt = 0;
            
            
            if(m_bIsGuide)
            {
                ((E002_Base_Question*)getParent())->removeGuide();
                return;
            }else{
                showLetPlay1RewardItem(NULL, m_nCurrentStageIndex-2);
                CJUtils::performSelector(this, callfunc_selector(E002_C010_P110::onComplete), 1.5f);
            }
        }
    }
    
    if (pAnimation->getKey() == FLASH_KEY_SPEAK) {
        pAnimation->stopAnimation(false);
        playAnimationByKey(pAnimation->getDataPool()->getKey(), FLASH_KEY_LOOPING, -1, pAnimation->getZOrder());
        return;
    }
    
    if (pAnimation->getDataPool()->getKey() == FLASH_GRUM ) {
        
        if (pAnimation->getKey() == FLASH_KEY_LOOPING) {
            pAnimation->stopAnimation(false);
            _playAnimationGrumbie(FLASH_KEY_LOOPING2,1);
            return;
        }
        
        if (pAnimation->getKey() == FLASH_KEY_LOOPING2) {
            pAnimation->stopAnimation(false);
            _playAnimationGrumbie(FLASH_KEY_LOOPING,3);
            return;
        }
    }
    
    
}



#pragma mark - animation

CJAnimation* E002_C010_P110::_playAnimationAnison(std::string pAniKey, int count)
{
    removeAllAnimationsInDataPool(FLASH_ANISON);
    return playAnimationByKey(FLASH_ANISON,pAniKey.c_str(), count, 0, layer3);
}

CJAnimation* E002_C010_P110::_playAnimationGrumbie(std::string pAniKey, int count)
{
    removeAllAnimationsInDataPool(FLASH_GRUM);
    return playAnimationByKey(FLASH_GRUM,pAniKey.c_str(), count, 0, layer3);
}

void E002_C010_P110::stopSpeakingAndLooping()
{
    stopAllNarration();
    if (getAnimationByKey(FLASH_ANISON, FLASH_KEY_SPEAK)->isPlay()) {
        _playAnimationAnison(FLASH_KEY_LOOPING);
    }
    
}

void E002_C010_P110::playFirework()
{
    
    runAction(CCSequence::create(
                                 CCCallFunc::create(this, callfunc_selector(E002_C010_P110::_playFirework1)),
                                 CCDelayTime::create(0.7),
                                 CCCallFunc::create(this, callfunc_selector(E002_C010_P110::_playFirework2)),
                                 NULL));
}

CJAnimation* E002_C010_P110::_playFirework1()
{
    int temp = m_nCurrentStageIndex%3;
    std::string key = CJUtils::getStringFormatInteger("fire%d", temp);
    
    CJSprite* que = (CJSprite*)_arrBuildings->objectAtIndex(m_nCurrentStageIndex);
    CCPoint convertPt = que->getParent()->convertToWorldSpace(que->getPosition());
    CJAnimation* ani = playAnimationByKey(FLASH_FIRE, key, 1, 0, layer3);
    ani->setPosition(ccpAdd(convertPt, ccp(-60, 40)));
    
    playEffect("e002_c010_p110_sfx_firecracker.mp3");
    
    CCParticleSystemQuad* particle =  E002_C010_BaseUtil::addParticle("e002_c010_p110_boom.plist");
    particle->setPosition(ani->getPosition());
    addChild(particle,kDepth5_particle);
    
    return ani;
}
CJAnimation* E002_C010_P110::_playFirework2()
{
    int temp = m_nCurrentStageIndex%3+3 ;
    std::string key = CJUtils::getStringFormatInteger("fire%d", temp);
    
    CJSprite* que = (CJSprite*)_arrBuildings->objectAtIndex(m_nCurrentStageIndex);
    CCPoint convertPt = que->getParent()->convertToWorldSpace(que->getPosition());
    
    _lastFireworkAni = playAnimationByKey(FLASH_FIRE, key, 1, 0, layer3);
    _lastFireworkAni->setPosition(ccpAdd(convertPt, ccp(60, -40)));
    
    playEffect("e002_c010_p110_sfx_firecracker.mp3");
    
    CCParticleSystemQuad* particle =  E002_C010_BaseUtil::addParticle("e002_c010_p110_boom.plist");
    particle->setPosition(_lastFireworkAni->getPosition());
    addChild(particle,kDepth5_particle);
    
    return _lastFireworkAni;
}

void E002_C010_P110::lightingColorAnimation(CCNode* node)
{
    CCActionInterval* tintA1 = CCTintTo::create(0.2f, 255, 216, 0);
    CCActionInterval* tintE1 = CCEaseSineInOut::create(tintA1);
    
    CCActionInterval* tintA2 = CCTintTo::create(0.2f, 246, 115, 120);
    CCActionInterval* tintE2 = CCEaseSineInOut::create(tintA2);
    
    CCActionInterval* tintA3 = CCTintTo::create(0.2f, 13, 184, 150);
    CCActionInterval* tintE3 = CCEaseSineInOut::create(tintA3);
    
    CCActionInterval* tintA4 = CCTintTo::create(0.2f, 188, 143, 202);
    CCActionInterval* tintE4 = CCEaseSineInOut::create(tintA4);
    
    
    CCActionInterval* seq = CCSequence::create(
                                               tintE1,
                                               tintE2,
                                               tintE3,
                                               tintE4,
                                               NULL);
    
    
    
    CCRepeatForever *repeatForever = CCRepeatForever::create( seq );
    
    node->runAction(repeatForever);
}


#pragma mark - Guide

void E002_C010_P110::showGuide()
{
    E002_Base_Question::showGuide();

    m_Guide = E002_C010_P110::create();
    m_Guide->init();
    m_Guide->setGuide(true);
    addChild(m_Guide, kDepth10_guide);
    
    std::vector<CCPoint> *guideHandPosition = new std::vector<CCPoint>();
    
    guideHandPosition->push_back(ccpAdd(ccp(390/2, 510/2), ccp(60, -60)));
    
    m_Guide->setGuideHandPosition(guideHandPosition);
}

void E002_C010_P110::removeGuide()
{
    E002_Base_Question::removeGuide();
    removeChild(m_Guide);
    
}

void E002_C010_P110::completeToMoveHand(CCNode *node, int index)
{
    switch (index) {
        case 0:
            onTouchBegan(node->getPosition());
            break;
        case 1:
            //            onTouchBegan(node->getPosition());
            //            showHand(NULL, 2);
            //            break;
        default:
            break;
    }
}

void E002_C010_P110::completeFirstGuide()
{
    //    CJUtils::performSelector(this, callfunc_selector(E002_C010_P110::setQuestions),0.3);
    start();
    setTouchDisalbeBaseLayer();
}


#pragma mark - navigation delegate

void E002_C010_P110::onTouchedNavigationButtonAtIndex()
{
    E002_Base_Question::onTouchedNavigationButtonAtIndex();
    E002_C010_P000_Index* _indexClass = E002_C010_P000_Index::create();
    _indexClass->init();
    _indexClass->setIndexDelegate(this);
    _indexClass->showIndex(this, _indexClass);
    addChild(_indexClass, kDepth11_Index);
    
}

void E002_C010_P110::onTouchedNavigationButtonAtInfo()
{
    E002_Base_Question::onTouchedNavigationButtonAtInfo();
    showGuide();
}

void E002_C010_P110::onTouchedNavigationButtonAtPrev()
{
    E002_Base_Question::onTouchedNavigationButtonAtPrev();
    //    replaceSceneTransitionFadeOut(E002_C010_P110);
    if (m_nCurrentStageIndex > 0) {
        
        if (m_nCurrentStageIndex%2 == 0) {
            m_nCurrentStageIndex -= 2;
        }else{
            m_nCurrentStageIndex -= 1;
        }
        
        resetValue();
        start();
    }
}

void E002_C010_P110::onTouchedNavigationButtonAtNext()
{
    E002_Base_Question::onTouchedNavigationButtonAtNext();
    
    if (m_nCurrentStageIndex < m_nMaxStageCount-2)
    {
        if (m_nCurrentStageIndex%2 == 0) {
            m_nCurrentStageIndex += 2;
        }else{
            m_nCurrentStageIndex += 1;
        }
        
        resetValue();
        start();
    }
    else
    {
        
        onEnd();
    }
    
}

void E002_C010_P110::onTouchedNavigationButtonAtReward()
{
    showLetPlay1RewardPopup(NULL, m_nCurrentStageIndex - 2);
}



#pragma mark - my util

CJSprite* E002_C010_P110::createSprite(std::string pStr)
{
    return CJPsdParser::getPsdSprite(pStr, m_psdDictionary);
}


void E002_C010_P110::_setPositionOutParent(CCNode* child, CCNode* newParent)
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

void E002_C010_P110::_safeRemoveFromParents(CCNode* pChild)
{
    if (pChild && pChild->getParent()) {
        pChild->removeFromParent();
    }
}

