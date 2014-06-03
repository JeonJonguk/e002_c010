

#include "E002_C010_P230.h"
#include "E002_C010_BaseUtil.h"
#include "E002_C010_P000_Index.h"
#include "E002_C010_P210.h"
#include "E002_C010_P300_Intro.h"
#include "E002_C010_CompletePopup.h"

#define HURDLE_GAB          1536

enum
{
    kTagExample001,
    kTagExample002,
    
    _kTagStar,
    _kTagBg1,
    _kTagBg2,
    _kTagTrees,
    _kTagHighlight,
    
    _kTagHurdle0,
    _kTagHurdle1,
    _kTagHurdle2,
    _kTagHurdle3,
    _kTagHurdle4,
    _kTagHurdle5,
    
    _kTagHurdle_fail0,
    _kTagHurdle_fail1,
    _kTagHurdle_fail2,
    _kTagHurdle_fail3,
    _kTagHurdle_fail4,
    _kTagHurdle_fail5,
    
    _kTagFood0,
    _kTagFood1,
    _kTagFood2,
    _kTagFood3,
    _kTagFood4,
    _kTagFood5,
    
    _kTagReady,
    _kTagSet,
    _kTagGo,
};

enum depth{
    _kDepthBackground = kDepth0_background,
    _kDepthBackImage = kDepth0_backImage,
    _kDepthLayer1,
    _kDepthLayer2,
    _kDepthLayer3,
    _kDepthLayer4,

    
};


E002_C010_P230::E002_C010_P230()
{
    
    m_touchingExampleSp = NULL;
    mSndManager = new E002_C010_SoundManager;
    _arrBuildings = new CCArray();
}

E002_C010_P230::~E002_C010_P230()
{
    CC_SAFE_DELETE(mSndManager);
}

#pragma mark - init

bool E002_C010_P230::init()
{
    if (!E002_Base_Reward::init()) {
        return false;
    }
    
    m_nMaxStageCount = 6;
    m_nCurrentStageIndex = 0;
    bIsJumping = false;
    bIsKoong = false;
    
    nForLayer1Position = 0;
    nForLayer2Position = 0;
    nForLayer4Position = 0;
    
    return true;
}

void E002_C010_P230::onEnter()
{
    E002_Base_Reward::onEnter();
    setTouchDisalbeBaseLayer();
    onViewLoad();
}

void E002_C010_P230::onExit()
{
    
    for (int i = 0; i < mQuestions.size(); i++) {
        CC_SAFE_RELEASE_NULL(mQuestions[i]);
    }
    
    unschedule(schedule_selector(E002_C010_P230::checkSchedule));
    unschedule(schedule_selector(E002_C010_P230::checkStageSchedule));

    
    E002_Base_Reward::onExit();
}


void E002_C010_P230::onViewLoad()
{
    E002_Base_Reward::onViewLoad();
    
    std::string questionsImgName[8] =
    {
        "e002_c010_p230_img_que00_txt_00", //guide
        "e002_c010_p230_img_que01_txt_00", //guide
        "e002_c010_p230_img_que00_txt_02",
        "e002_c010_p230_img_que01_txt_02",
        "e002_c010_p230_img_que02_txt_00",
        "e002_c010_p230_img_que03_txt_00",
        "e002_c010_p230_img_que04_txt_00",
        "e002_c010_p230_img_que05_txt_00",
    };

    
    for (int i = 0; i < m_nMaxStageCount; i++)
    {
        
        SSQuestionItem* item = SSQuestionItem::create(questionsImgName[i],
                                                          "",
                                                          "",
                                                          "",
                                                          "",
                                                          "",
                                                          "");
        item->retain();
        mQuestions.push_back(item);
    }
    
    
    CJPsdParser::parseToPsdJSON("e002_c010_p230.json", &m_psdDictionary);
    
   
    //layer 1 ============================================================================ // sky
    layer1 = CJSprite::create();
    layer1->setContentSize(winSize);
    layer1->setAnchorPoint(CCPointZero);
    layer1->setPosition(CCPointZero);
    
    CJSprite* bg1 = createSprite("e002_c010_p230_img_bg_00");
    CJSprite* bg1_2 = createSprite("e002_c010_p230_img_bg_00");
    bg1->setAnchorPoint(CCPointZero);
    bg1->setPosition(ccp(0, 547-221));
    bg1_2->setAnchorPoint(CCPointZero);
    bg1_2->setPosition(ccp(bg1->getContentSize().width, 0));
    bg1->addChild(bg1_2);
    layer1->addChild(bg1, _kDepthLayer1, _kTagBg1);
    
    
    //layer 2 ============================================================================ // ground, reword
    layer2 = CJSprite::create();
    layer2->setContentSize(winSize);
    layer2->setAnchorPoint(CCPointZero);
    layer2->setPosition(CCPointZero);
    
    CJSprite* bg2 = createSprite("e002_c010_p230_img_bg_01");
    CJSprite* bg2_2 = createSprite("e002_c010_p230_img_bg_01");
    bg2->setAnchorPoint(CCPointZero);
    bg2->setPosition(CCPointZero);
    bg2_2->setAnchorPoint(CCPointZero);
    bg2_2->setPosition(ccp(bg2->getContentSize().width, 0));
    bg2->addChild(bg2_2);
    layer2->addChild(bg2, 0, _kTagBg2);


    
    float posX = 0.0f;
    float firstPosx = 572.f;
    
    for (int i = 0; i < 6; i++) {
        std::string str = CJUtils::getStringFormatInteger("e002_c010_p230_img_reward0%d_00", i);
        CJSprite* hurdle = createSprite(str);
        hurdle->setAnchorPointWithoutPosition(CCPointZero);
        posX = hurdle->getPositionX() + (i*HURDLE_GAB) + 300;
        hurdle->setPositionX(posX);
        layer2->addChild(hurdle, 1, _kTagHurdle0+i);
        
        std::string failStr = CJUtils::getStringFormatInteger("e002_c010_p230_img_reward0%d_01", i);
        CJSprite* failHurdle = createSprite(failStr);
        failHurdle->setAnchorPointWithoutPosition(CCPointZero);
        failHurdle->setPositionX(posX);
        failHurdle->setVisible(false);
        layer2->addChild(failHurdle, 0, _kTagHurdle_fail0+i);
        
        
        std::string foodStr = CJUtils::getStringFormatInteger("e002_c010_p230_img_food_0%d", i);
        CJSprite* food = createSprite(foodStr);
        CJSprite* cloud = CJSprite::createWithFullPath("e002_c010_p230_img_food_bg.png");
        cloud->setPosition(ccp(food->getContentSize().width/2, food->getContentSize().height/2));
        food->addChild(cloud,-1);
        food->setPositionX(food->getPositionX() + i*HURDLE_GAB + 300);
        layer2->addChild(food, 0, _kTagFood0+i);
        
        food->runAction(CCRepeatForever::create(CCSequence::create(CCEaseSineInOut::create(CCMoveBy::create(0.5, ccp(0, 20))),
                                                                   CCEaseSineInOut::create(CCMoveBy::create(0.5, ccp(0, -20))),
                                                                   NULL)));

    }
    posX = (posX + HURDLE_GAB + 700);
    CJSprite* finish = createSprite("e002_c010_p230_img_finsh");
    finish->setAnchorPointWithoutPosition(CCPointZero);
    finish->setPositionX(posX+150);
    layer2->addChild(finish);
    
    totalDist = posX - firstPosx;
    mBoomParent = layer2;
    
    
    
    //layer 3 ============================================================================
    layer3 = CJSprite::create();
    layer3->setContentSize(winSize);
    layer3->setAnchorPoint(CCPointZero);
    layer3->setPosition(CCPointZero);
    
    
    
    //layer 4 ============================================================================ //foward object
    layer4 = CJSprite::create();
    layer4->setContentSize(winSize);
    layer4->setAnchorPoint(CCPointZero);
    layer4->setPosition(CCPointZero);
    
    
    //particle
    cloudParticle = E002_C010_BaseUtil::addParticle("e002_c010_p230_cloud.plist",false);
    starParticle =  E002_C010_BaseUtil::addParticle("e002_c010_p230_star.plist",false);
    addChild(cloudParticle, kDepth5_particle);
    addChild(starParticle, kDepth5_particle);
    cloudParticle->stopSystem();
    starParticle ->stopSystem();

    
    
        //trees
    CJSprite* trees = CJSprite::create();
    trees->setContentSize(CCSizeMake(1536, 105));
    trees->setAnchorPoint(CCPointZero);
    trees->setPosition(CCPointZero);
    
    CJSprite* treeObject1 = createSprite("e002_c010_p230_img_object_00");
    CJSprite* treeObject2 = createSprite("e002_c010_p230_img_object_01");
    CJSprite* treeObject3 = createSprite("e002_c010_p230_img_object_02");
    CJSprite* treeObject4 = createSprite("e002_c010_p230_img_object_03");
    treeObject1->setPositionX(treeObject1->getPositionX());
    treeObject2->setPositionX(treeObject2->getPositionX());
    treeObject3->setPositionX(treeObject3->getPositionX());
    treeObject4->setPositionX(treeObject4->getPositionX());
    
    trees->addChild(treeObject1);
    trees->addChild(treeObject2);
    trees->addChild(treeObject3);
    trees->addChild(treeObject4);
    layer4->addChild(trees, 0, _kTagTrees);
    
    CJSprite* treeCopy = (CJSprite*)E002_C010_BaseUtil::copyCJSprite(trees);
    treeCopy->setAnchorPoint(CCPointZero);
    treeCopy->setPosition(ccp(trees->getContentSize().width, 0));
    trees->addChild(treeCopy);

    ratio1 = 0.3;
    ratio2 = 1.0;
    ratio3 = 0.0;
    ratio4 = 1.7;
    
    parallaxLayer = CCParallaxNode::create();
    parallaxLayer->addChild(layer1, _kDepthLayer1, ccp(ratio1, 0), CCPointZero);
    parallaxLayer->addChild(layer2, _kDepthLayer2, ccp(ratio2, 0), CCPointZero);
    parallaxLayer->addChild(layer3, _kDepthLayer3, ccp(ratio3, 0), CCPointZero);
    parallaxLayer->addChild(layer4, _kDepthLayer4, ccp(ratio4, 0), CCPointZero);
    addChild(parallaxLayer, _kDepthLayer1, 10);
    
    
    
//    float dist = 0;
//    dist = ((CJSprite*)_arrBuildings->objectAtIndex(m_nCurrentStageIndex))->getPositionX() - ((CJSprite*)_arrBuildings->objectAtIndex(0))->getPositionX();
//    parallaxLayer->setPositionX(parallaxLayer->getPositionX()-dist);

//    parallaxLayer->runAction(CCMoveBy::create(15.0, ccp(-totalDist, 0)));
    parallaxLayer->runAction(CCMoveTo::create(0, ccp(-totalDist, 0)));
//    checkSchedule();
    schedule(schedule_selector(E002_C010_P230::checkSchedule), 1/60.f);
    
    
    
    // FLASH
    setAnimationFile("e002_c010_p110_flash_as_sheets.json", "e002_c010_p110_flash_as_animations.json", FLASH_ANISON);
    setAnimationFile("e002_c010_p230_flash_bb_sheets.json", "e002_c010_p230_flash_bb_animations.json", FLASH_BOOM);
    setAnimationFile("e002_c010_p230_flash_al_sheets.json", "e002_c010_p230_flash_al_animations.json", FLASH_ROBOT);
    
    

    animationManagerParseStart();
    



}

void E002_C010_P230::onViewLoaded()
{
    E002_Base_Reward::onViewLoaded();
    
    
    createAnimationAndSetKey(FLASH_ANISON, "e002_c010_p110_flash_sun_n01_loop", FLASH_KEY_LOOPING);
    createAnimationAndSetKey(FLASH_ANISON, "e002_c010_p110_flash_sun_s01_action", FLASH_KEY_SUCCESS);
    createAnimationAndSetKey(FLASH_ANISON, "e002_c010_p110_flash_sun_s02_run", FLASH_KEY_RUN);
    createAnimationAndSetKey(FLASH_ANISON, "e002_c010_p110_flash_sun_n02_speak", FLASH_KEY_SPEAK);
    
    createAnimationAndSetKey(FLASH_BOOM, "e002_c010_p320_flash_as_n01_loop", FLASH_KEY_LOOPING);
    createAnimationAndSetKey(FLASH_BOOM, "e002_c010_p320_flash_as_n02_loop", FLASH_KEY_LOOPING2);
    createAnimationAndSetKey(FLASH_BOOM, "e002_c010_p320_flash_as_s01_action", FLASH_KEY_ACTION1);
    createAnimationAndSetKey(FLASH_BOOM, "e002_c010_p320_flash_as_f01_action", FLASH_KEY_FAIL);
    
    
    createAnimationAndSetKey(FLASH_ROBOT, "e002_c010_p230_flash_al_n01", FLASH_KEY_LOOPING);
    createAnimationAndSetKey(FLASH_ROBOT, "e002_c010_p230_flash_al_n02", FLASH_KEY_LOOPING2);
    createAnimationAndSetKey(FLASH_ROBOT, "e002_c010_p230_flash_al_s01_action", FLASH_KEY_SUCCESS);
    
    
    
    mAnison = _playAnimationAnison(FLASH_KEY_LOOPING);
    mAnison->setPosition(ccp(totalDist+700, 300));
    
    mRobot = _playAnimationRobot(FLASH_KEY_LOOPING);
    mRobot ->setPositionX(totalDist+mRobot->getPositionX());
    
    mBoom = _playAnimationBoomBoom(FLASH_KEY_LOOPING);
    

    
    CJUtils::performSelector(this, callfunc_selector(E002_C010_P230::onFirstNarration),1.0);


}

void E002_C010_P230::startFlashAnimation()
{
    
}

void E002_C010_P230::onFirstNarration()
{
//    E002_Base_Reward::onFirstNarration();
    mFirstNarration = "e002_c010_p230_snd_02_as.mp3";
    
    mAnison = _playAnimationAnison(FLASH_KEY_SPEAK);
    mAnison->setPosition(ccp(totalDist+700, 300));
    playNarration(mFirstNarration);
}

void E002_C010_P230::onFirstNarrationEnd()
{
    E002_Base_Reward::onFirstNarrationEnd();
    setTouchDisalbeBaseLayer();
    removeAllAnimationsInDataPool(FLASH_ANISON);
    _playAnimationAnison(FLASH_KEY_LOOPING);
    
    
    //    if (getUserDefaultFirstGuide(eGuidePageP130) == false)
    //    {
    mShowFirstGuide = true;
    
    setUserDefaultFirstGuide(eGuidePageP230);
    onTouchedNavigationButtonAtInfo();
    //    }else{
    //    start();
    //}

}

void E002_C010_P230::onNarrationFinishedCallback(std::string fileName)
{
    if (fileName == mFirstNarration)
    {
        onFirstNarrationEnd();
//        removeAllAnimationsInDataPool(FLASH_ANISON);
    }
    
    if (fileName == "e002_c010_p230_snd_03_ar.mp3") {
        runStart();
    }
    
    
    if (fileName == "e002_c010_p230_snd_05_as.mp3") {
        _playAnimationAnison(FLASH_KEY_LOOPING);
        CJUtils::performSelector(this, callfunc_selector(E002_C010_P230::onEnd), 0.5);
    }

}

#pragma mark - touch

bool E002_C010_P230::onTouchBegan(CCPoint tp)
{

//    CJSprite* queImg = mQuestions[m_nCurrentStageIndex]->imgSprite;
//    if (queImg && CJUtils::hitTestPoint(queImg, tp, false)) {
//        mQuestions[m_nCurrentStageIndex]->playEffect();
//        mQuestions[m_nCurrentStageIndex]->playAction(mQuestions[m_nCurrentStageIndex]->imgSprite);
//        return false;
//    }
    
    if (bIsJumping == false && bIsKoong == false) {
        bIsJumping = true;
        _playAnimationBoomBoom(FLASH_KEY_ACTION1,1);
        playEffect("e002_c010_p000_sfx_08.mp3");
    }
    return false;
}

void E002_C010_P230::onTouchMoved(CCPoint tp)
{
}

void E002_C010_P230::onTouchEnded(CCPoint tp)
{
}


#pragma mark - feedback event

void E002_C010_P230::onSuccesses(CCNode *node, int tag)
{
    CCLog("onSuccess");
    setTouchDisalbeBaseLayer();
    stopNarration("e002_c010_p210_sfx_horse_fast_run.mp3");
    
    
    _playAnimationBoomBoom(FLASH_KEY_LOOPING);

    mRobot = _playAnimationRobot(FLASH_KEY_SUCCESS, 2);
    mRobot ->setPositionX(totalDist+mRobot->getPositionX());

    
    mAnison = _playAnimationAnison(FLASH_KEY_SUCCESS, 2);
    mAnison->setPosition(ccp(totalDist+700, 300));
    
    mSndManager->playCorrectNarrationAnison(E002_C010_SoundManager::p210);
    playEffect("e002_c010_p200_intro_sfx_people.mp3");
    
}

void E002_C010_P230::onFails(CCNode *node, int tag)
{
    CJLog("onFail");
}


void E002_C010_P230::onComplete()
{
    E002_Base_Reward::onComplete();
    _playAnimationAnison(FLASH_KEY_SPEAK);
    playNarration("e002_c010_p230_snd_05_as.mp3"); //end: onEnd();
  
    
}

void E002_C010_P230::onEnd()
{
//    replaceSceneTransitionFadeOut(E002_C010_P300_Intro);
    showCompletePopup();
}

#pragma mark - set questions, set examples
void E002_C010_P230::start()
{
//    _playAnimationBoomBoom(FLASH_KEY_LOOPING);
    parallaxLayer->runAction(CCSequence::create(CCEaseSineOut::create( CCMoveTo::create(6, ccp(0, 0)) ),
                                                CCCallFunc::create(this, callfunc_selector(E002_C010_P230::setQuestions)),
                                                NULL));

}



void E002_C010_P230::setQuestions()
{
    CJSprite* _ready = CJSprite::createWithFullPath("e002_c010_p230_img_txt_00.png");
    CJSprite* _set = CJSprite::createWithFullPath("e002_c010_p230_img_txt_01.png");
    CJSprite* _go = CJSprite::createWithFullPath("e002_c010_p230_img_txt_02.png");
    
    addChild(_ready, kDepth4_title, _kTagReady);
    addChild(_set, kDepth4_title, _kTagSet);
    addChild(_go, kDepth4_title, _kTagGo);
    
    _ready->setPosition(winCenter);
    _set->setPosition(winCenter);
    _go->setPosition(winCenter);
    
    _ready->setScale(0);
    _set->setScale(0);
    _go->setScale(0);

    
    float delay = 0.0;
    for (int i = 0; i < 3; i++) {
        CJSprite* sp = (CJSprite*)getChildByTag(_kTagReady+i);
        sp->setPosition(winCenter);
        
//        if (i < 2) {
            sp->runAction(CCSequence::create(CCDelayTime::create(delay),
                                             CCEaseSineOut::create(CCScaleTo::create(0.5, 1.0)),
                                             CCEaseSineIn::create(CCSpawn::create(CCScaleTo::create(0.5, 1.3),
                                                                                  CCFadeOut::create(0.5),
                                                                                  NULL)),
                                             NULL));
//        }else{
//            sp->runAction(CCSequence::create(CCDelayTime::create(delay),
//                                             CCEaseSineOut::create(CCScaleTo::create(0.5, 1.0)),
//                                             CCCallFunc::create(this, callfunc_selector(E001_Base_P530_Drums::playMusic)),
//                                             CCEaseSineIn::create(CCSpawn::create(CCScaleTo::create(0.5, 1.3),
//                                                                                  CCFadeOut::create(0.5),
//                                                                                  NULL)),
//                                             
//                                             NULL));
//        }
        
        
        
        delay += 1.0;
    }

    
    playNarrationWithDelay("e002_c010_p230_snd_03_ar.mp3",0.5); // end:runStart();
    
//    e002_c010_p230_img_txt_00.png
//    e002_c010_p230_img_txt_01.png
//    e002_c010_p230_img_txt_02.png
    

}

void E002_C010_P230::runStart()
{
    setTouchEnableBaseLayer();
    mBoomParent = layer3;
    parallaxLayer->runAction(CCSequence::create(CCMoveTo::create(12.0, ccp(-totalDist, 0)),
                                                CCCallFuncN::create(this, callfuncN_selector(E002_C010_P230::onSuccesses)),
                                                NULL));
    _playAnimationBoomBoom(FLASH_KEY_LOOPING2);
    schedule(schedule_selector(E002_C010_P230::checkStageSchedule), 1/60.f);
    
    playNarration("e002_c010_p210_sfx_horse_fast_run.mp3", true);
    
    
}

void E002_C010_P230::resetValue()
{
    _successCount = 0;
    setTouchDisalbeBaseLayer();
}

void E002_C010_P230::checkStageSchedule()
{
    //check stage indexx
    for (int i = _kTagHurdle0; i <= _kTagHurdle5 ; i++) {
        CJSprite* hurdle = (CJSprite*)layer2->getChildByTag(i);
        if (mBoom &&
            layer2->convertToWorldSpace(hurdle->getPosition()).x > mBoom->getPosition().x - 200)
        {
            m_nCurrentStageIndex = (i - _kTagHurdle0) ;
            break;
        }
    }
    

    CJSprite* hurdle = (CJSprite*)layer2->getChildByTag(_kTagHurdle0+ m_nCurrentStageIndex);
    
    if (mBoom->boundingBox().containsPoint(ccp(layer2->convertToWorldSpace(hurdle->getPosition()).x+70,layer2->convertToWorldSpace(hurdle->getPosition()).y+100))) {
        if (bIsJumping) {
            
            CJSprite* food = (CJSprite*)layer2->getChildByTag(_kTagFood0+m_nCurrentStageIndex);
            if (!food->isComplete()) {
                food->setComplete(true);
                food->runAction(CCSequence::create(CCEaseSineOut::create(CCSpawn::create(CCScaleTo::create(0.2, 1.2),
                                                                                         CCFadeOut::create(0.2),
                                                                                         NULL)),
                                                   NULL));
                CJSprite* cloud = (CJSprite*)food->getChildren()->objectAtIndex(0);
                cloud->runAction(CCSequence::create(CCEaseSineOut::create(CCFadeOut::create(0.15)),NULL));
                
                playEffect("e002_c010_p000_sfx_06.mp3");
                

                cloudParticle->resetSystem();
                starParticle->resetSystem();

                
                playEffect("e002_c010_p230_snd_04_bb.mp3");
            }
            


            
        }else{
            if (hurdle->isVisible()) {
                
                CJLog("KOONG!!");
                bIsKoong = true;
                _playAnimationBoomBoom(FLASH_KEY_FAIL,1);
                bIsJumping = false;
                
                hurdle->setVisible(false);
                CJSprite* fail = (CJSprite*)layer2->getChildByTag(_kTagHurdle_fail0+m_nCurrentStageIndex);
                fail->setVisible(true);
                
                playEffect("e002_c010_p230_sfx_block.mp3");
                playCommonEffect("e002_common_snd_wrong_12_bb.mp3");
            }
        }

    }
    
}

void E002_C010_P230::checkSchedule()
{
    
    CJSprite* bg1 =(CJSprite*)layer1->getChildByTag(_kTagBg1);
    if (parallaxLayer->getPositionX()*ratio1 < -bg1->getContentSize().width*(nForLayer1Position+1)) {
        nForLayer1Position++;
        bg1->setPositionX(bg1->getContentSize().width * nForLayer1Position);
    }
    if (parallaxLayer->getPositionX()*ratio1 > -bg1->getContentSize().width*(nForLayer1Position)) {
        nForLayer1Position--;
        bg1->setPositionX(bg1->getContentSize().width * nForLayer1Position);
    }
    
    
    CJSprite* bg2 =(CJSprite*)layer2->getChildByTag(_kTagBg2);
    if (parallaxLayer->getPositionX()*ratio2 < -bg2->getContentSize().width*(nForLayer2Position+1)) {
        nForLayer2Position++;
        bg2->setPositionX(bg2->getContentSize().width * nForLayer2Position);
    }
    if (parallaxLayer->getPositionX()*ratio2 > -bg2->getContentSize().width*(nForLayer2Position)) {
        nForLayer2Position--;
        bg2->setPositionX(bg2->getContentSize().width * nForLayer2Position);
    }


    CJSprite* trees =(CJSprite*)layer4->getChildByTag(_kTagTrees);
    if (parallaxLayer->getPositionX()*ratio4 < -trees->getContentSize().width*(nForLayer4Position+1)) {
        nForLayer4Position++;
        trees->setPositionX(trees->getContentSize().width * nForLayer4Position);
    }
    if (parallaxLayer->getPositionX()*ratio4 > -trees->getContentSize().width*(nForLayer4Position)) {
        nForLayer4Position--;
        trees->setPositionX(trees->getContentSize().width * nForLayer4Position);
    }

    
  
}

#pragma mark - appear, disappear

void E002_C010_P230::OnLastFrame(CJAnimation* pAnimation)
{
    if (pAnimation->getDataPool()->getKey() == FLASH_ANISON) {
        if (pAnimation->getKey() == FLASH_KEY_SPEAK) {
            removeAnimation(pAnimation);
            playAnimationByKey(pAnimation->getDataPool()->getKey(), FLASH_KEY_LOOPING, -1, pAnimation->getZOrder());
            return;
        }
        
        if (pAnimation->getKey() == FLASH_KEY_SUCCESS) {
            removeAnimation(pAnimation);
            playAnimationByKey(pAnimation->getDataPool()->getKey(), FLASH_KEY_LOOPING, -1, pAnimation->getZOrder());
            onComplete();
            return;
        }
    }
    
    if (pAnimation->getDataPool()->getKey() == FLASH_ROBOT) {

        if (pAnimation->getKey() == FLASH_KEY_SUCCESS) {
            mRobot= _playAnimationRobot(FLASH_KEY_LOOPING2);
            mRobot ->setPositionX(totalDist+mRobot->getPositionX());

            return;
        }
    }

    
    if (pAnimation->getDataPool()->getKey() == FLASH_BOOM )
    {
        if (pAnimation->getKey() == FLASH_KEY_ACTION1) {
            bIsJumping = false;
            removeAnimation(pAnimation);
            _playAnimationBoomBoom(FLASH_KEY_LOOPING2);
        }
        
        if (pAnimation->getKey() == FLASH_KEY_FAIL) {
            bIsKoong = false;
            removeAnimation(pAnimation);
            _playAnimationBoomBoom(FLASH_KEY_LOOPING2);
        }
        
    }

}

void E002_C010_P230::completeFirstGuide()
{
    CJUtils::performSelector(this, callfunc_selector(E002_C010_P230::start),0.0);
    setTouchDisalbeBaseLayer();
}

void E002_C010_P230::showCompletePopup()
{
    E002_C010_CompletePopup *cPopup = new E002_C010_CompletePopup();
    cPopup->init(P200);
    addChild(cPopup, kDepth10_guide);
    
    cPopup->showPopup(this);
    cPopup->showCompletePopup();
}

#pragma mark - animation 

CJAnimation* E002_C010_P230::_playAnimationAnison(std::string pAniKey, int count)
{
    removeAllAnimationsInDataPool(FLASH_ANISON);
    return playAnimationByKey(FLASH_ANISON,pAniKey.c_str(), count, 0, layer2);
}

CJAnimation* E002_C010_P230::_playAnimationBoomBoom(std::string pAniKey, int count)
{
    removeAllAnimationsInDataPool(FLASH_BOOM);
    return playAnimationByKey(FLASH_BOOM,pAniKey.c_str(), count, 0, mBoomParent);
}

CJAnimation* E002_C010_P230::_playAnimationRobot(std::string pAniKey, int count)
{
    removeAllAnimationsInDataPool(FLASH_ROBOT);
    return playAnimationByKey(FLASH_ROBOT,pAniKey.c_str(), count, 0, layer2);
}


#pragma mark - navigation delegate

void E002_C010_P230::onTouchedNavigationButtonAtIndex()
{
    E002_Base_Reward::onTouchedNavigationButtonAtIndex();
    E002_C010_P000_Index* _indexClass = E002_C010_P000_Index::create();
    _indexClass->init();
    _indexClass->setIndexDelegate(this);
    _indexClass->showIndex(this, _indexClass);
    addChild(_indexClass, kDepth11_Index);
    
}

void E002_C010_P230::onTouchedNavigationButtonAtInfo()
{
    E002_Base_Reward::onTouchedNavigationButtonAtInfo();
    showGuide(new E002_Base_ImageGuide_Item("e002_c010_p230_guide.jpg",
                                            CJPsdParser::getPsdPosition("e002_common_img_guide_hand", m_psdDictionary),
                                            CJPsdParser::getPsdPosition("e002_common_img_guide_hand", m_psdDictionary)
                                            ));
    
}

void E002_C010_P230::onTouchedNavigationButtonAtPrev()
{
    E002_Base_Reward::onTouchedNavigationButtonAtPrev();
    replaceSceneTransitionFadeOut(E002_C010_P210);
}

void E002_C010_P230::onTouchedNavigationButtonAtNext()
{
    E002_Base_Reward::onTouchedNavigationButtonAtNext();
    
//    if (m_nCurrentStageIndex < m_nMaxStageCount-1)
//    {
//        m_nCurrentStageIndex++;
//    }
//    else
//    {
//        completeLetsPlay1();
//        onEnd();
//    }
    replaceSceneTransitionFadeOut(E002_C010_P300_Intro);
    
    
    
}



#pragma mark - my util

CJSprite* E002_C010_P230::createSprite(std::string pStr)
{
    return CJPsdParser::getPsdSprite(pStr, m_psdDictionary);
}


void E002_C010_P230::_setPositionOutParent(CCNode* child, CCNode* newParent)
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

void E002_C010_P230::_safeRemoveFromParents(CCNode* pChild)
{
    if (pChild && pChild->getParent()) {
        pChild->removeFromParent();
    }
}


