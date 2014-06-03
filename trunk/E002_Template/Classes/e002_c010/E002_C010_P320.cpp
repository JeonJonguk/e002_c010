

#include "E002_C010_P320.h"
#include "E002_C010_BaseUtil.h"
#include "E002_C010_P000_Index.h"
#include <math.h>   // abs() fabs()
#include "E002_C010_P330.h"
#include "E002_C010_P310.h"


enum
{
    kTagExample001,
    kTagExample002,
    
    _kTagBasketCover,
    _kTagBasketShadow_l,
    _kTagBasketShadow_r,
    
    _kTagCloud,
    _kTagBird1,
    _kTagBird2,
    
};

enum depth{
    _kDepthBackground = kDepth0_background,
    _kDepthBackImage = kDepth0_backImage,
    _kDepthLayer1,
    _kDepthLayer2,
    _kDepthLayer3,
    _kDepthLayer4,

};


E002_C010_P320::E002_C010_P320()
{
    
    m_touchingExampleSp = NULL;
    mSndManager = new E002_C010_SoundManager;
    arrBalloons = new CCArray();
    arrBalloons->init();
    
    _leftSuccessCount = 0;
    _rightSuccessCount = 0;
    _nTempQuestionIndex = 0;
    _nTempExampleIndex = 0;

}

E002_C010_P320::~E002_C010_P320()
{
    CC_SAFE_DELETE(mSndManager);
    CC_SAFE_DELETE(arrBalloons);
}

#pragma mark - init

bool E002_C010_P320::init()
{
    if (!E002_Base_Question::init()) {
        return false;
    }
    
    m_nMaxStageCount = 4;
    m_nCurrentStageIndex = 1;
    _selectedExampleIndex = 0;
    _selectedQuestionIndex = 0;
    _oldCurrentStageIndex = m_nCurrentStageIndex;
    return true;
}

void E002_C010_P320::onEnter()
{
    E002_Base_Question::onEnter();
    setTouchDisalbeBaseLayer();
    onViewLoad();
}

void E002_C010_P320::onExit()
{
    
    for (int i = 0; i < mQuestions.size(); i++) {
        std::vector<SSQuestionItem*> vec = mQuestions[i];
        for (int j = 0; j < vec.size(); j++) {
            CC_SAFE_RELEASE_NULL(vec[j]);
        }
    }
    
    for (int i = 0; i < mExamples.size(); i++) {
        std::vector<SSExampleItem*> vec = mExamples[i];
        for (int j = 0; j < vec.size(); j++) {
            CC_SAFE_RELEASE_NULL(vec[j]);
        }
    }
    
    E002_Base_Question::onExit();
}


void E002_C010_P320::onViewLoad()
{
    E002_Base_Question::onViewLoad();
    
    std::string questionsTxtName[4][2] =
    {
        {"e002_c010_p320_img_que00_00","e002_c010_p320_img_que00_01"}, //guide
        {"e002_c010_p320_img_que01_00","e002_c010_p320_img_que01_01"},
        {"e002_c010_p320_img_que02_00","e002_c010_p320_img_que02_01"},
        {"e002_c010_p320_img_que03_00","e002_c010_p320_img_que03_01"},
    };

    
    std::string questionsSndName[4][2] =
    {
        {wordSoundFileNames[67],wordSoundFileNames[68]},  //guide
        {wordSoundFileNames[72],wordSoundFileNames[71]},
        {wordSoundFileNames[69],wordSoundFileNames[70]},
        {wordSoundFileNames[74],wordSoundFileNames[73]}
    };
    
    
    for (int i = 0; i < m_nMaxStageCount; i++)
    {
        
        std::vector<SSQuestionItem*> questions;
        for (int j = 0; j < 2; j++)
        {
            SSQuestionItem* item = SSQuestionItem::create("",
                                                          questionsTxtName[i][j],
                                                          "",
                                                          "",
                                                          questionsSndName[i][j],
                                                          "",
                                                          "");
            item->retain();
            questions.push_back(item);
        }
        mQuestions.push_back(questions);
        
    }
    
    
    
    // example setting =================
    
    std::string exampleImgName[4][4] =
    {
        {
            "e002_c010_p320_img_ans00_00",
            "e002_c010_p320_img_ans00_01",
            "e002_c010_p320_img_ans00_02",
            "e002_c010_p320_img_ans00_03"
        },
        
        {
            "e002_c010_p320_img_ans01_00",
            "e002_c010_p320_img_ans01_01",
            "e002_c010_p320_img_ans01_02",
            "e002_c010_p320_img_ans01_03"

        },
        {
            "e002_c010_p320_img_ans02_00",
            "e002_c010_p320_img_ans02_01",
            "e002_c010_p320_img_ans02_02",
            "e002_c010_p320_img_ans02_03"
        },
        {
            "e002_c010_p320_img_ans03_00",
            "e002_c010_p320_img_ans03_01",
            "e002_c010_p320_img_ans03_02",
            "e002_c010_p320_img_ans03_03",
        }
    };
    
    std::string exampleSndName[4][4] =
    {
        {wordSoundFileNames[4], wordSoundFileNames[10], wordSoundFileNames[5], wordSoundFileNames[11]    }, //guide
        {wordSoundFileNames[14], wordSoundFileNames[13], wordSoundFileNames[12], wordSoundFileNames[15]    },
        {wordSoundFileNames[6], wordSoundFileNames[8], wordSoundFileNames[7], wordSoundFileNames[9]    },
        {wordSoundFileNames[17], wordSoundFileNames[16], wordSoundFileNames[18], wordSoundFileNames[19]    },
    };
    
    int correctTags[4][4] =
    {
        {0, 1, 0, 1},
        {1, 0, 0, 1},
        {0, 1, 0, 1},
        {1, 1, 0, 0},
    };
    
    
    
    for (int i = 0; i < m_nMaxStageCount; i++)
    {
        std::vector<SSExampleItem*> examples;
        for (int j = 0; j < 4; j++)
        {
            SSExampleItem* item = SSExampleItem::create(i,
                                                        exampleImgName[i][j],
                                                        "",
                                                        exampleSndName[i][j],
                                                        kTagExample001 + j,
                                                        correctTags[i][j]);
            item->retain();
            examples.push_back(item);
        }
        mExamples.push_back(examples);
    }
    
    CJPsdParser::parseToPsdJSON("e002_c010_p320.json", &m_psdDictionary);
//    setBackground("e002_c010_p320_img_bg_00.jpg");
    
    
    
    
    //layer 1 ============================================================================ // sky
    layer1 = createSprite("e002_c010_p320_img_bg_00");
    layer1->setAnchorPoint(CCPointZero);
    layer1->setPosition(CCPointZero);
    
    //layer 2 ============================================================================ // bridge
    layer2 = createSprite("e002_c010_p320_img_bg_01");
    layer2->setAnchorPoint(CCPointZero);
    layer2->setPosition(CCPointZero);
    
    //layer 3 ============================================================================ // ground
    layer3 = createSprite("e002_c010_p320_img_bg_02_00");
    layer3->setAnchorPoint(CCPointZero);
    layer3->setPosition(CCPointZero);
    
    CJSprite* freedom = createSprite("e002_c010_p320_img_bg_02_02");
    layer3->addChildIgnoreParent(freedom);
   
    CJSprite* leaf = createSprite("e002_c010_p320_img_bg_02_01");
    layer3->addChildIgnoreParent(leaf);

    
    //layer 4 ============================================================================ // flash
    layer4 = CJSprite::create();
    layer4->setContentSize(winSize);
    layer4->setAnchorPoint(CCPointZero);
    layer4->setPosition(CCPointZero);
    

    parallaxLayer = CCParallaxNode::create();
    parallaxLayer->addChild(layer1, _kDepthLayer1, ccp(1, 1), ccp(0, 0));
    parallaxLayer->addChild(layer2, _kDepthLayer2, ccp(1, 1.3), ccp(0.5, 0.5));
    parallaxLayer->addChild(layer3, _kDepthLayer3, ccp(1, 1.6), ccp(0.5, 0.5));
    addChild(parallaxLayer, _kDepthLayer1, 10);
    parallaxLayer->setPosition(CCPointZero);
    

    //this
    basket_l = createSprite("e002_c010_p320_img_basket_l_00");
    addChild(basket_l, kDepth2_questions);

    CJSprite* basket_l_cover = createSprite("e002_c010_p320_img_basket_l_01");
    basket_l->addChildIgnoreParent(basket_l_cover, kDepth2_questions, _kTagBasketCover);
    
    CJSprite* basket_l_shadow = createSprite("e002_c010_p320_img_basket_l_shadow");
    layer3->addChild(basket_l_shadow, basket_l->getZOrder()-1, _kTagBasketShadow_l);
    
    
    basket_r = createSprite("e002_c010_p320_img_basket_r_00");
    addChild(basket_r, kDepth2_questions);

    CJSprite* basket_r_cover = createSprite("e002_c010_p320_img_basket_r_01");
    basket_r->addChildIgnoreParent(basket_r_cover, kDepth2_questions, _kTagBasketCover);
    
    CJSprite* basket_r_shadow = createSprite("e002_c010_p320_img_basket_r_shadow");
    layer3->addChild(basket_r_shadow, basket_r->getZOrder()-1, _kTagBasketShadow_r);

    
    //balloons
    for (int i = 0; i < 6 ; i++) {
        std::string str_l = CJUtils::getStringFormatInteger("e002_c010_p320_img_balloon_l_0%d", i);
        std::string str_r = CJUtils::getStringFormatInteger("e002_c010_p320_img_balloon_r_0%d", i);
        
        CJSprite* balloon_l_1 = createSprite(str_l);
        CJSprite* balloon_r_1 = createSprite(str_r);
        
        basket_l->addChildIgnoreParent(balloon_l_1, -1);
        basket_r->addChildIgnoreParent(balloon_r_1, -1);
        
        balloon_l_1->m_originPosition = balloon_l_1->getPosition();
        balloon_r_1->m_originPosition = balloon_r_1->getPosition();
        
        balloon_l_1->setPosition(ccpAdd(balloon_l_1->getPosition(), ccp(0,-15)));
        balloon_r_1->setPosition(ccpAdd(balloon_r_1->getPosition(), ccp(0,-15)));
        
        balloon_l_1->m_secondPosition = balloon_l_1->getPosition();
        balloon_r_1->m_secondPosition = balloon_r_1->getPosition();
        
        arrBalloons->addObject(balloon_l_1);
        arrBalloons->addObject(balloon_r_1);
        
        
        balloon_l_1->setVisible(false);
        balloon_r_1->setVisible(false);
    }
    

    
    //cloud
    CJSprite* cloud1 = createSprite("e002_c010_p320_img_cloud_00");
    CJSprite* cloud2 = createSprite("e002_c010_p320_img_cloud_02");
    CJSprite* cloud3 = createSprite("e002_c010_p320_img_cloud_01");
    
    layer1->addChildIgnoreParent(cloud1,0,_kTagCloud);
    layer2->addChildIgnoreParent(cloud2,0,_kTagCloud);
    layer3->addChildIgnoreParent(cloud3,0,_kTagCloud);
    
    //bird
    CJSprite* bird1 = createSprite("e002_c010_p320_img_bird_00_00");
    layer1->addChildIgnoreParent(bird1, 2, _kTagBird1);
    bird1->runAction(CJUtils::getSeqAction(-1,
                                           0.2,
                                           getImageFilePath("e002_c010_p320_img_bird_00_00.png").c_str(),
                                           getImageFilePath("e002_c010_p320_img_bird_00_01.png").c_str(),
                                           NULL));
    
    CJSprite* bird2 = createSprite("e002_c010_p320_img_bird_01_00");
    layer1->addChildIgnoreParent(bird2, 1, _kTagBird2);
    bird2->runAction(CJUtils::getSeqAction(-1,
                                           0.15,
                                           getImageFilePath("e002_c010_p320_img_bird_01_00.png").c_str(),
                                           getImageFilePath("e002_c010_p320_img_bird_01_01.png").c_str(),
                                           NULL));
    
    

    schedule(schedule_selector(E002_C010_P320::checkSchedule), 1/60.f);
    
    
    if(m_bIsGuide)
    {
        createGuideDim(kDepth2_questions-2);
    }
    
    // FLASH
    setAnimationFile("e002_c010_p320_flash_as_sheets.json", "e002_c010_p320_flash_as_animations.json", FLASH_ANISON);
    setAnimationFile("e002_c010_p320_flash_ch_sheets.json", "e002_c010_p320_flash_ch_animations.json", FLASH_CHU);
    animationManagerParseStart();
    

//    parallaxLayer->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(5.0, ccp(0,-(1563-768))),
//                                                         CCMoveBy::create(5.0, ccp(0,+(1563-768))),
//                                                         NULL)));
    
}

void E002_C010_P320::onViewLoaded()
{
    E002_Base_Question::onViewLoaded();

    
    if (!m_bIsGuide)
    {
        E002_Base_Navigation::setVisibleButton(true, eNavigationButton_Prev);
        mSndManager->playBgm(E002_C010_SoundManager::p320);
    }
    
    



}

void E002_C010_P320::startFlashAnimation()
{
    //anison
    //    e002_c010_p320_flash_as_f01_action
    //    e002_c010_p320_flash_as_n01_loop
    //    e002_c010_p320_flash_as_n02_speak
    //    e002_c010_p320_flash_as_s01_action
    createAnimationAndSetKey(FLASH_ANISON, "e002_c010_p320_flash_as_n01_loop", FLASH_KEY_LOOPING);
    createAnimationAndSetKey(FLASH_ANISON, "e002_c010_p320_flash_as_s01_action", FLASH_KEY_SUCCESS);
    createAnimationAndSetKey(FLASH_ANISON, "e002_c010_p320_flash_as_f01_action", FLASH_KEY_FAIL);
    createAnimationAndSetKey(FLASH_ANISON, "e002_c010_p320_flash_as_n02_speak", FLASH_KEY_SPEAK);
    
    
    
    //chu
    //    e002_c010_p320_flash_ch_f01_action
    //    e002_c010_p320_flash_ch_n01_action
    //    e002_c010_p320_flash_ch_n01_loop
    //    e002_c010_p320_flash_ch_no2_loop
    //    e002_c010_p320_flash_ch_s01_action
    createAnimationAndSetKey(FLASH_CHU, "e002_c010_p320_flash_ch_n01_action", FLASH_KEY_ACTION1);
    createAnimationAndSetKey(FLASH_CHU, "e002_c010_p320_flash_ch_no2_loop", FLASH_KEY_LOOPING);
    createAnimationAndSetKey(FLASH_CHU, "e002_c010_p320_flash_ch_s01_action", FLASH_KEY_SUCCESS);
    createAnimationAndSetKey(FLASH_CHU, "e002_c010_p320_flash_ch_f01_action", FLASH_KEY_FAIL);
    createAnimationAndSetKey(FLASH_CHU, "e002_c010_p320_flash_ch_n01_loop", FLASH_KEY_LOOPING2);
    
    
    _playAnimationAnison(FLASH_KEY_LOOPING);
    _playAnimationChu(FLASH_KEY_LOOPING2);
    
    //    playAnimation(FLASH_CHU, "e002_c010_p320_flash_ch_n01_action", -1, 1000);
    

//    CJUtils::performSelector(this, callfunc_selector(E002_C010_P320::onFirstNarration),1.5);
    if(m_bIsGuide)
    {
        CJUtils::performSelector(this, callfunc_selector(E002_Base_Question::removeTouchDelegateForGuide), 0.5);
        CJUtils::performSelector(this, callfunc_selector(E002_C010_P320::start),0.3);
    }
    else
    {
        CJUtils::performSelector(this, callfunc_selector(E002_C010_P320::onFirstNarration),1.5);
    }
}

void E002_C010_P320::onFirstNarration()
{
    E002_Base_Question::onFirstNarration();

    mFirstNarration = "e002_c010_p320_snd_01_as.mp3";
    playNarration(mFirstNarration);
    _playAnimationAnison(FLASH_KEY_SPEAK);
    
}

void E002_C010_P320::onFirstNarrationEnd()
{
    E002_Base_Question::onFirstNarrationEnd();
    setTouchDisalbeBaseLayer();
    
//    if (getUserDefaultFirstGuide(eGuidePageP320) == false)
//    {
        mShowFirstGuide = true;
        setUserDefaultFirstGuide(eGuidePageP320);
        showGuide();
//    }else{
//        
//        start();
//    }
}

void E002_C010_P320::onNarrationFinishedCallback(std::string fileName)
{
    if (fileName == mFirstNarration && !isFirstSkiped())
    {
        onFirstNarrationEnd();
    }
    else if (fileName == mFirstNarration)
    {
        removeAllAnimationsInDataPool(FLASH_ANISON, true);
        _playAnimationAnison(FLASH_KEY_LOOPING);
//        _playAnimationChu(FLASH_KEY_LOOPING);
    }

}

#pragma mark - touch

bool E002_C010_P320::onTouchBegan(CCPoint tp)
{

    
    if (CJUtils::hitTestPoint(getAnimationByKey(FLASH_ANISON, FLASH_KEY_LOOPING),tp, false)) {
        
        playNarration(mFirstNarration);
        _playAnimationAnison(FLASH_KEY_SPEAK);
        return false;
    }
    
    if (CJUtils::hitTestPoint(getAnimationByKey(FLASH_CHU, FLASH_KEY_LOOPING),tp, false)) {
        
        stopSpeakingAndLooping();
        mSndManager->playChuTouchNarr();
        return false;
    }
    
    
    for (int i = 0; i < 4; i++) {
        CJSprite* example =  mExamples[m_nCurrentStageIndex][i]->sprite;
        
        if (!example->isComplete() && CJUtils::hitTestPoint(example, tp, false))
        {
            stopSpeakingAndLooping();
            
            m_touchingExampleSp = example;
            _selectedExampleIndex = i;
            _touchedExampleItem = mExamples[m_nCurrentStageIndex][i];
            _touchedExampleItem->playEffect();
            
            reorderChild(m_touchingExampleSp, m_touchingExampleSp->getZOrder());
            m_touchingExampleSp->onTouchActionEvent();
            m_touchingExampleSp->m_secondPosition =  m_touchingExampleSp->getPosition();
            
            
            if(m_bIsGuide)
            {
                
                showHand(NULL, ++m_currentGuideIndex);
                
                CCPoint targetPt = mExamples[m_nCurrentStageIndex][i]->correctTag == 0 ? basket_l->getPosition() : basket_r->getPosition();
                example->runAction(CCEaseSineOut::create(CCMoveTo::create(0.7f, targetPt)));
            }
            
            return true;
            
        }
        
        else if(example->isComplete() && CJUtils::hitTestPoint(example, tp, false))
        {
            _touchedExampleItem = mExamples[m_nCurrentStageIndex][i];
            _touchedExampleItem->playEffect();
            return false;

        }
        
        
    }
    
    for (int i = 0; i < 2; i++) {
        CJSprite* que = mQuestions[m_nCurrentStageIndex][i]->txtSprite;
        if (CJUtils::hitTestPoint(que, tp, false)) {
            stopSpeakingAndLooping();
            mQuestions[m_nCurrentStageIndex][i]->playEffect();
            mQuestions[m_nCurrentStageIndex][i]->playAction(que);
            return false;
        }
    }
    

    
    return false;
}

void E002_C010_P320::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint tp = pTouch->getLocation();
    CCPoint preTp = pTouch->getPreviousLocation();

    CCPoint pos = ccpAdd(m_touchingExampleSp->getPosition(), ccpSub(tp, preTp));
    m_touchingExampleSp->setPosition(pos);
    
    
}

void E002_C010_P320::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
//    CCPoint tp = pTouch->getLocation();
    m_touchingExampleSp->onTouchEndActionEvent();
    
    CCPoint pt = CCPointZero;
    int temp = 0;
    if (CJUtils::hitTestObjects(m_touchingExampleSp, basket_l))
    {
        _selectedQuestionIndex = 0;
        temp = _leftSuccessCount + 1;
        
        if (_leftSuccessCount == 2) {
            temp = 2;
        }

    }
    else if(CJUtils::hitTestObjects(m_touchingExampleSp, basket_r))
    {
        _selectedQuestionIndex = 1;
        temp = _rightSuccessCount + 3;
        
        if (_rightSuccessCount == 2) {
            temp = 4;
        }
    
    }
    else
    {
        _doongDoong(m_touchingExampleSp);
        m_touchingExampleSp = NULL;
        return;
    }
    

    
    
    std::string strTargetPos = CJUtils::getStringFormatInteger("e002_c010_p320_img_ans@%d", temp);
    CJLog("strTargetPos = %s",strTargetPos.c_str());
    pt = CJPsdParser::getPsdPosition(strTargetPos, m_psdDictionary);
    intoTarget(m_touchingExampleSp, pt);
    

    
}

#pragma mark - check 

void E002_C010_P320::intoTarget(CJSprite* sp, CCPoint tp)
{
    playEffect("e002_c010_p000_sfx_04.mp3");
    setTouchDisalbeBaseLayer();

    CJSprite* queSp = _selectedQuestionIndex == 0 ? basket_l : basket_r;
    sp->setScale(1);
    sp->retain();
    sp->removeFromParentAndCleanup(false);
    queSp->addChildIgnoreParent(sp,-1);
    sp->release();
    tp = queSp->convertToNodeSpace(tp);

    sp->setAnchorPointWithoutPosition(ccp(0.5, 0));
    sp->runAction(CCSequence::create(CCCallFuncND::create(this, callfuncND_selector(E002_C010_P320::checkAnswer), (int*)_selectedQuestionIndex),
                                     CCEaseBackOut::create(CCMoveTo::create(0.6, tp)),
                                     NULL));
}



void E002_C010_P320::checkAnswer(CCNode *node, int tag)
{
    CJLog("tag = %d", tag);
    if (_touchedExampleItem->correctTag ==  tag) {
        mSndManager->playSuccessSfxSnd(3);
        
        if (_selectedQuestionIndex == 0) {
            CJLog("left success");
            _leftSuccessCount++;
        }else{
            CJLog("right success");
            _rightSuccessCount++;
        }
        
        if (_rightSuccessCount == 2 && _leftSuccessCount == 2) {
            CJUtils::performSelector(this, callfuncND_selector(E002_C010_P320::onSuccesses),NULL, 0.6);
            return;
        }
        
        setTouchEnableBaseLayer();
        ((CJSprite*)node)->setComplete(true);
        
        
    }else{
        mSndManager->playWrongSfxSnd(2);
        node->runAction(CCSequence::create(
                                           CCDelayTime::create(0.5),
                                           CCCallFuncND::create(this,callfuncND_selector(E002_C010_P320::onFails),NULL),
                                           NULL));
        
        
    }
    
}

void E002_C010_P320::reorderBalloon(CJSprite* balloon)
{
    
}


#pragma mark - feedback event


void E002_C010_P320::onSuccesses(CCNode *node, int tag)
{
    CCLog("onSuccess");

    
    mSndManager->playCorrectNarrationAnison(E002_C010_SoundManager::p320);
    mSndManager->playCorrectNarrationOtherOne(E002_C010_SoundManager::p320);

    playEffect("e002_c010_p110_sfx_jump_as.mp3");
    playEffect("e002_c010_p110_sfx_jump_gb.mp3");
    
    _playAnimationAnison(FLASH_KEY_SUCCESS,1);
    _playAnimationChu(FLASH_KEY_SUCCESS,1);
    
    CJLog(" arrBalloons->count() = %d ", arrBalloons->count());
    for (int i = 0; i < arrBalloons->count(); i++) {
        CJSprite* balloon = (CJSprite*)arrBalloons->objectAtIndex(i);
        if (i < (m_nCurrentStageIndex) * 4) {
            balloon->setVisible(true);
            CJLog("o visible true index = %d",i);
        }else{
            balloon->setVisible(false);
            CJLog("x visible false index = %d",i);
        }
    }
    
    
    
   
    
    CCParticleSystemQuad* particle1 =  E002_C010_BaseUtil::addParticle("e002_c010_p320_star_00.plist");
    addChild(particle1, kDepth5_particle);
    
    CCParticleSystemQuad* particle2 =  E002_C010_BaseUtil::addParticle("e002_c010_p320_star_01.plist");
    addChild(particle2, kDepth5_particle);
    
    //example
    for (int i = 0; i < 4; i++) {
        mExamples[m_nCurrentStageIndex][i]->sprite->removeFromParent();
        mExamples[m_nCurrentStageIndex][i]->sprite = NULL;
    }
    
    //question
    for (int i = 0; i < 2; i++) {
        CJSprite* question = mQuestions[m_nCurrentStageIndex][i]->txtSprite;
        question->retain();
        question->runAction(CCSequence::create(CCFadeOut::create(0.4),
                                               CCCallFunc::create(question, callfunc_selector(CJSprite::removeFromParent)),
                                                                   NULL));
        
    }
}


void E002_C010_P320::onFails(CCNode *node, int tag)
{
    CJLog("onFail");
    
    
    playEffect("e002_c010_p320_sfx_wrong_as.mp3");
    playEffect("e002_c010_p320_sfx_wrong_ch.mp3");
    CJSprite* example = (CJSprite*)node;
    
    mSndManager->playWrongNarrationAnison(E002_C010_SoundManager::p320);
    mSndManager->playWrongNarrationOtherOne(E002_C010_SoundManager::p320);
    
    CCPoint pt = example->getParent()->convertToWorldSpace(example->getPosition());
    example->retain();
    example->removeFromParentAndCleanup(false);
    addChild(example, kDepth3_examples);
    example->setPosition(pt);
    example->release();
    
    example->setAnchorPointWithoutPosition(ccp(0.5, 0.5));
    example->runAction(CCSequence::create(CCEaseBackOut::create(CCMoveTo::create(0.8,  example->m_secondPosition)),
                                          NULL));
    example->runAction(_doongDoong());
    
    _playAnimationAnison(FLASH_KEY_FAIL,1);
    _playAnimationChu(FLASH_KEY_FAIL,1);
    
}

void E002_C010_P320::flashSuccessFinishCallback(CJAnimation* pAnimation)
{
    _playAnimationAnison(FLASH_KEY_LOOPING);
    _playAnimationChu(FLASH_KEY_LOOPING);

    showLetPlay3RewardItem(NULL, m_nCurrentStageIndex-1 +3);
    
    if (m_bIsGuide) {
        ((E002_Base_Question*)getParent())->removeGuide();
    }else{
        CJUtils::performSelector(this, callfunc_selector(E002_C010_P320::disappearAnimation), 1.5f);
        
    }
//    CJUtils::performSelector(this, callfunc_selector(E002_C010_P320::disappearAnimation), 1.5f);
}

void E002_C010_P320::flashFailFinishCallback(CJAnimation* pAnimation)
{
    setTouchEnableBaseLayer();
    _playAnimationAnison(FLASH_KEY_LOOPING);
    _playAnimationChu(FLASH_KEY_LOOPING);
}

void E002_C010_P320::onComplete()
{
    E002_Base_Question::onComplete();
    
    if (m_nCurrentStageIndex < m_nMaxStageCount-1) {
        resetValue();
        m_nCurrentStageIndex++;
        setQuestions();
        setExamles();
        showQuestions();
    }else{
        CJLog("end");
        onEnd();

    }
    
    

}

void E002_C010_P320::onEnd()
{
    completeLetsPlay3();
    replaceSceneTransitionFadeOut(E002_C010_P330);
}

#pragma mark - set questions, set examples
void E002_C010_P320::start()
{
    _playAnimationAnison(FLASH_KEY_LOOPING);
    _playAnimationChu(FLASH_KEY_ACTION1,1);
    
    setQuestions();
    setExamles();
    showQuestions();
}

void E002_C010_P320::setQuestions()
{

//    if (m_nCurrentStageIndex == 1) {
//        E002_Base_Navigation::setVisibleButton(false, eNavigationButton_Prev);
//    }else if(m_nCurrentStageIndex > 1){
//        E002_Base_Navigation::setVisibleButton(true, eNavigationButton_Prev);
//    }
    
    
    if(m_nCurrentStageIndex > 1)
    {
        
        basket_l->runAction(CCRepeatForever::create(CCSequence::create(CCEaseSineInOut::create(CCMoveBy::create(0.9, ccp(0, 20))),
                                                                       CCEaseSineInOut::create(CCMoveBy::create(0.9, ccp(0, -20))),
                                                                       NULL)));
        basket_r->runAction(CCRepeatForever::create(CCSequence::create(CCEaseSineInOut::create(CCMoveBy::create(1.0, ccp(0, 20))),
                                                                       CCEaseSineInOut::create(CCMoveBy::create(1.0, ccp(0, -20))),
                                                                       NULL)));
    }
    
    _oldCurrentStageIndex = m_nCurrentStageIndex;
    
    mQuestions[m_nCurrentStageIndex][0]->createTxtSprite(m_psdDictionary);
    mQuestions[m_nCurrentStageIndex][1]->createTxtSprite(m_psdDictionary);
    
    basket_l->addChildIgnoreParent(mQuestions[m_nCurrentStageIndex][0]->txtSprite,kDepth2_questions);
    basket_r->addChildIgnoreParent(mQuestions[m_nCurrentStageIndex][1]->txtSprite,kDepth2_questions);
    
    mQuestions[m_nCurrentStageIndex][0]->txtSprite->setScale(0);
    mQuestions[m_nCurrentStageIndex][1]->txtSprite->setScale(0);
    
    
}

void E002_C010_P320::showQuestions()
{
    
    if (_nTempQuestionIndex < 2) {
        mQuestions[m_nCurrentStageIndex][_nTempQuestionIndex]->playEffect();
        mQuestions[m_nCurrentStageIndex][_nTempQuestionIndex]->playAction(mQuestions[m_nCurrentStageIndex][_nTempQuestionIndex]->txtSprite);
        
        _nTempQuestionIndex++;
        CJUtils::performSelector(this, callfunc_selector(E002_C010_P320::showQuestions), 0.8);
    }else{
        _nTempQuestionIndex = 0;
        showExamples();
    }
}


void E002_C010_P320::setExamles()
{
    for (int i = 0; i < 4; i++) {
        mExamples[m_nCurrentStageIndex][i]->createImgSprite(m_psdDictionary);
        addChild(mExamples[m_nCurrentStageIndex][i]->sprite, kDepth3_examples);
        mExamples[m_nCurrentStageIndex][i]->sprite->setTouchEnable(true);
        mExamples[m_nCurrentStageIndex][i]->sprite->setPosition(ccp(mExamples[m_nCurrentStageIndex][i]->sprite->getPositionX(),
                                                                    winSize.height + mExamples[m_nCurrentStageIndex][i]->sprite->getContentSize().height/2));
        mExamples[m_nCurrentStageIndex][i]->sprite->m_secondPosition = mExamples[m_nCurrentStageIndex][i]->sprite->getPosition();
    }
}

void E002_C010_P320::showExamples()
{
    if (_nTempExampleIndex < 4) {
        playEffect("e002_c010_p000_sfx_03.mp3");
        SSExampleItem* example = mExamples[m_nCurrentStageIndex][_nTempExampleIndex];
        example->playEffect();
        example->sprite->runAction(CCEaseBackOut::create(CCMoveTo::create(0.5, example->sprite->m_originPosition)));
        example->sprite->m_secondPosition = example->getPosition();
        _doongDoong(example->sprite);
        
        _nTempExampleIndex++;
        CJUtils::performSelector(this, callfunc_selector(E002_C010_P320::showExamples), 0.8);
        
    }else{
        _nTempExampleIndex = 0;
        setTouchEnableBaseLayer();
        
        if (m_bIsGuide) {
            showHand(NULL, 0);
        }
    }

}


void E002_C010_P320::resetValue()
{
    setTouchDisalbeBaseLayer();
    stopAllActions();
    stopAllNarration();
    
    _leftSuccessCount = 0;
    _rightSuccessCount = 0;
    
    _nTempQuestionIndex = 0;
    _nTempExampleIndex = 0;

    basket_l->stopAllActions();
    basket_r->stopAllActions();
    basket_l->setPosition(basket_l->m_originPosition);
    basket_r->setPosition(basket_r->m_originPosition);
    
    CJSprite* basket_l_shadow = (CJSprite*)layer3->getChildByTag(_kTagBasketShadow_l);
    basket_l_shadow->setScale(1.0);
    CJSprite* basket_r_shadow = (CJSprite*)layer3->getChildByTag(_kTagBasketShadow_r);
    basket_r_shadow->setScale(1.0);
   


    
    if (mQuestions[_oldCurrentStageIndex][0]->txtSprite && mQuestions[_oldCurrentStageIndex][0]->txtSprite->getParent()) {
        mQuestions[_oldCurrentStageIndex][0]->txtSprite->removeFromParent();
        if (mQuestions[_oldCurrentStageIndex][0]->txtSprite->retainCount() != 0)
            mQuestions[_oldCurrentStageIndex][0]->txtSprite->release();

        mQuestions[_oldCurrentStageIndex][0]->txtSprite = NULL;
    }
    if (mQuestions[_oldCurrentStageIndex][1]->txtSprite && mQuestions[_oldCurrentStageIndex][1]->txtSprite->getParent()) {
        mQuestions[_oldCurrentStageIndex][1]->txtSprite->removeFromParent();
        if (mQuestions[_oldCurrentStageIndex][1]->txtSprite->retainCount() != 0)
            mQuestions[_oldCurrentStageIndex][1]->txtSprite->release();

        mQuestions[_oldCurrentStageIndex][1]->txtSprite = NULL;
    }
    
    
    for (int i = 0; i < 4; i++) {
        if (mExamples[_oldCurrentStageIndex][i]->sprite) {
            mExamples[_oldCurrentStageIndex][i]->sprite->removeFromParent();
            mExamples[_oldCurrentStageIndex][i]->sprite= NULL;
        }
    }
    
}


void E002_C010_P320::setNextQuestions()
{
    E002_C010_BaseUtil::stopAllAnimationsWithOutTags(this,_kTagBird1,_kTagBird2,-1);
    resetValue();
    
    for (int i = 0; i < arrBalloons->count(); i++) {
        CJSprite* balloon = (CJSprite*)arrBalloons->objectAtIndex(i);
        if (i < (m_nCurrentStageIndex-1) * 4) {
            balloon->setVisible(true);
        }else{
            balloon->setVisible(false);
        }
    }
    
    CJLog("setNextQuestions : m_nCurrentStageIndex = %d",m_nCurrentStageIndex);
    float height = (layer1->getContentSize().height - winSize.height)/2 * (m_nCurrentStageIndex-1);
    parallaxLayer->setPositionY(-height);
    
    start();
    
}


#pragma mark - appear, disappear

void E002_C010_P320::disappearAnimation()
{
  
    
    if (m_nCurrentStageIndex < m_nMaxStageCount-1) {
        for (int i = 0; i < arrBalloons->count(); i++) {
            CJSprite* balloon = (CJSprite*)arrBalloons->objectAtIndex(i);
            balloon->runAction(CCSequence::create(CCEaseSineIn::create(CCMoveTo::create(0.5, balloon->m_originPosition)),
                                                  CCJumpTo::create(0.5, balloon->m_originPosition, -7, 1),
                                                  NULL));
        }
        
        playEffectWithDelay("e002_c010_p320_sfx_up.mp3",1.0);
        
        float height = (layer1->getContentSize().height - winSize.height)/2 * m_nCurrentStageIndex;
        parallaxLayer->runAction(CCSequence::create(CCDelayTime::create(1.0),
                                                    CCCallFunc::create(this, callfunc_selector(E002_C010_P320::onUpParticle)),
                                                    CCEaseSineInOut::create(CCMoveTo::create(3.0, ccp(0,-height))),
                                                    CCCallFunc::create(this, callfunc_selector(E002_C010_P320::onComplete)),
                                                    NULL));
        
        
        CJSprite* basket_l_shadow = (CJSprite*)layer3->getChildByTag(_kTagBasketShadow_l);
        basket_l_shadow->setScale(1.0);
        basket_l_shadow->runAction(CCSequence::create(CCDelayTime::create(1.0),
                                                      CCEaseSineInOut::create(CCScaleTo::create(2.0, 0.5)),
                                                      NULL));
        
        CJSprite* basket_r_shadow = (CJSprite*)layer3->getChildByTag(_kTagBasketShadow_r);
        basket_r_shadow->setScale(1.0);
        basket_r_shadow->runAction(CCSequence::create(CCDelayTime::create(1.0),
                                                      CCEaseSineInOut::create(CCScaleTo::create(2.0, 0.5)),
                                                      NULL));
    }else{
     
        
//        playEffect("e002_c010_p320_sfx_up.mp3");
        playEffectWithDelay("e002_c010_p320_sfx_up.mp3",0.1);
        basket_l->runAction(CCSequence::create(CCEaseSineIn::create(CCMoveTo::create(2.1, ccp(basket_l->getPositionX(), winSize.height+basket_l->getContentSize().height))),NULL));
        basket_r->runAction(CCSequence::create(CCDelayTime::create(0.1),
                                               CCCallFunc::create(this, callfunc_selector(E002_C010_P320::onUpParticle)),
                                               CCEaseSineIn::create(CCMoveTo::create(2.3, ccp(basket_r->getPositionX(), winSize.height+basket_r->getContentSize().height))),
                                               CCCallFunc::create(this, callfunc_selector(E002_C010_P320::onComplete)),
                                               NULL));
        
        
    }
}

void E002_C010_P320::checkSchedule()
{
//    layer1->addChildIgnoreParent(cloud2,0,_kTagCloud);
//    layer2->addChildIgnoreParent(cloud3,0,_kTagCloud);
//    layer3->addChildIgnoreParent(cloud1,0,_kTagCloud);
    CJSprite* cloud1 = (CJSprite*)layer1->getChildByTag(_kTagCloud);
    CJSprite* cloud2 = (CJSprite*)layer2->getChildByTag(_kTagCloud);
    CJSprite* cloud3 = (CJSprite*)layer3->getChildByTag(_kTagCloud);
    
   
    static int vec1 = 1;
    static int vec2 = 1;
    static int vec3 = 1;
    
    float x1 = 1 * vec1;
    float x2 = 1.5 * vec2;
    float x3 = 2 * vec3;
    
    cloud1->setPositionX(cloud1->getPositionX()+x1);
    cloud2->setPositionX(cloud2->getPositionX()+x2);
    cloud3->setPositionX(cloud3->getPositionX()+x3);
    
    if (cloud1->getPositionX() > winSize.width + 200) {
        vec1 = -1;
    }
    if (cloud2->getPositionX() > winSize.width + 200) {
        vec2 = -1;
    }
    if (cloud3->getPositionX() > winSize.width + 200) {
        vec3 = -1;
    }
    
    
    if (cloud1->getPositionX() < - 200) {
        vec1 = 1;
    }
    if (cloud2->getPositionX() < - 200) {
        vec2 = 1;
    }
    if (cloud3->getPositionX() < - 200) {
        vec3 = 1;
    }
    
    

    //bird
    CJSprite* bird1 = (CJSprite*)layer1->getChildByTag(_kTagBird1);
    CJSprite* bird2 = (CJSprite*)layer1->getChildByTag(_kTagBird2);
    bird1->setPositionX(bird1->getPositionX()+ 9);
    bird2->setPositionX(bird2->getPositionX()+ 6.5);
    if (bird1->getPositionX() > winSize.width + 200) {
        bird1->setPositionX(-300);
    }
    if (bird2->getPositionX() > winSize.width + 200) {
        bird2->setPositionX(-200);
    }
    
}

void E002_C010_P320::OnLastFrame(CJAnimation* pAnimation)
{
//    E002_C010_BaseUtil::OnLastFrame(pAnimation);
    
    if (pAnimation->getKey() == FLASH_KEY_ACTION1) {
        _playAnimationChu(FLASH_KEY_LOOPING);
    }
    

    static int cnt = 0;
    if (pAnimation->getKey() == FLASH_KEY_SUCCESS) {
        cnt++;
        if (cnt == 2) {
            cnt = 0;
            flashSuccessFinishCallback(pAnimation);
        }
    }
    
    if (pAnimation->getKey() == FLASH_KEY_FAIL) {
        cnt++;
        if (cnt == 2) {
            cnt = 0;
            flashFailFinishCallback(pAnimation);
        }
    }
    
    if (pAnimation->getKey() == FLASH_KEY_SPEAK) {

        playAnimationByKey(pAnimation->getDataPool()->getKey(), FLASH_KEY_LOOPING, -1, pAnimation->getZOrder());
        removeAnimation(pAnimation, true);
    }
    
}



#pragma mark - animation 

CJAnimation* E002_C010_P320::_playAnimationAnison(std::string pAniKey, int count)
{
    removeAllAnimationsInDataPool(FLASH_ANISON, true);
    CJAnimation* ani = playAnimationByKey(FLASH_ANISON,pAniKey.c_str(), count, 0, basket_r);
//    CJUtils::setPositionForParent(basket_r, ani);
//    ani->setPosition(ccp(1308/2, 768 - 1088/2));
    ani->setAnchorPoint(ccp(0.5, 0));
    ani->setPosition(ccp(basket_r->getContentSize().width/2, 60));
    
    return ani;
}

CJAnimation* E002_C010_P320::_playAnimationChu(std::string pAniKey, int count)
{
    removeAllAnimationsInDataPool(FLASH_CHU, true);
    CJAnimation* ani = playAnimationByKey(FLASH_CHU,pAniKey.c_str(), count, 0, basket_l);
    CJUtils::setPositionForParent(basket_l, ani);
//    ani->setAnchorPoint(ccp(0.5, 0));
//    ani->setPosition(ccp(basket_l->getContentSize().width/2, 60));

    
    return ani;
}

void E002_C010_P320::stopSpeakingAndLooping()
{
    stopAllNarration();
    if (getAnimationByKey(FLASH_ANISON, FLASH_KEY_SPEAK)->isPlay()) {
        _playAnimationAnison(FLASH_KEY_LOOPING);
    }
    
}

void E002_C010_P320::_doongDoong(CJSprite* balloon)
{
    balloon->runAction(CCRepeatForever::create(CCSequence::create(CCEaseSineInOut::create(CCMoveBy::create(0.7, ccp(0, 10))),
                                                                  CCEaseSineInOut::create(CCMoveBy::create(0.7, ccp(0, -10))),
                                                                  NULL)));

}

CCAction* E002_C010_P320::_doongDoong()
{
    return CCRepeatForever::create(CCSequence::create(CCEaseSineInOut::create(CCMoveBy::create(0.7, ccp(0, 10))),
                                                      CCEaseSineInOut::create(CCMoveBy::create(0.7, ccp(0, -10))),
                                                      NULL));
}

void E002_C010_P320::onUpParticle()
{
    CCParticleSystemQuad* particle1 =  E002_C010_BaseUtil::addParticle("e002_c010_p320_light_00.plist");
    basket_l->addChildIgnoreParent(particle1, kDepth5_particle);
    
    CCParticleSystemQuad* particle2 =  E002_C010_BaseUtil::addParticle("e002_c010_p320_light_01.plist");
    basket_r->addChildIgnoreParent(particle2, kDepth5_particle);
}

#pragma mark - Guide

void E002_C010_P320::showGuide()
{
    E002_Base_Question::showGuide();
    
    m_Guide = E002_C010_P320::create();
    m_Guide->init();
    m_Guide->setGuide(true);
    addChild(m_Guide, kDepth10_guide);
    
    std::vector<CCPoint> *guideHandPosition = new std::vector<CCPoint>();
//    "e002_c010_p320_img_ans00_00",
//    "e002_c010_p320_img_ans00_01",
//    "e002_c010_p320_img_ans00_02",
//    "e002_c010_p320_img_ans00_03"
    
    guideHandPosition->push_back(ccpAdd(CJPsdParser::getPsdPosition("e002_c010_p320_img_ans00_00",m_psdDictionary), ccp(60, -60)));
    guideHandPosition->push_back(ccpAdd(basket_l->getPosition() , ccp(60, -60)));

    guideHandPosition->push_back(ccpAdd(CJPsdParser::getPsdPosition("e002_c010_p320_img_ans00_01",m_psdDictionary), ccp(60, -60)));
    guideHandPosition->push_back(ccpAdd(basket_r->getPosition() , ccp(60, -60)));

    guideHandPosition->push_back(ccpAdd(CJPsdParser::getPsdPosition("e002_c010_p320_img_ans00_02",m_psdDictionary), ccp(60, -60)));
    guideHandPosition->push_back(ccpAdd(basket_l->getPosition() , ccp(60, -60)));

    guideHandPosition->push_back(ccpAdd(CJPsdParser::getPsdPosition("e002_c010_p320_img_ans00_03",m_psdDictionary), ccp(60, -60)));
    guideHandPosition->push_back(ccpAdd(basket_r->getPosition() , ccp(60, -60)));

    
    m_Guide->setGuideHandPosition(guideHandPosition);
    
}


void E002_C010_P320::removeGuide()
{
    E002_Base_Question::removeGuide();
    removeChild(m_Guide);
    
}

void E002_C010_P320::completeToMoveHand(CCNode *node, int index)
{
    switch (index%2) {
        case 0:
            onTouchBegan(ccpAdd(node->getPosition(),ccp(-60, 60)));
            break;
        case 1:
        {
            CCPoint convertUI = CCDirector::sharedDirector()->convertToUI(ccpAdd(node->getPosition(),ccp(-60, 60)));
            CCTouch* ctouch = new CCTouch();
            ctouch->setTouchInfo(0, convertUI.x, convertUI.y);
            
            ccTouchEnded(ctouch,NULL);
            if (m_currentGuideIndex < 7) {
                showHand(NULL, ++m_currentGuideIndex);
            }
        }
            break;
        default:
            break;
    }
}

void E002_C010_P320::completeFirstGuide()
{
    CJUtils::performSelector(this, callfunc_selector(E002_C010_P320::start),0.3);
    setTouchDisalbeBaseLayer();
}


#pragma mark - navigation delegate

void E002_C010_P320::onTouchedNavigationButtonAtIndex()
{
    E002_Base_Question::onTouchedNavigationButtonAtIndex();
    E002_C010_P000_Index* _indexClass = E002_C010_P000_Index::create();
    _indexClass->init();
    _indexClass->setIndexDelegate(this);
    _indexClass->showIndex(this, _indexClass);
    addChild(_indexClass, kDepth11_Index);
    
}

void E002_C010_P320::onTouchedNavigationButtonAtInfo()
{
    E002_Base_Question::onTouchedNavigationButtonAtInfo();
    showGuide();
}

void E002_C010_P320::onTouchedNavigationButtonAtPrev()
{
    E002_Base_Question::onTouchedNavigationButtonAtPrev();
    if (m_nCurrentStageIndex > 1) {
        m_nCurrentStageIndex--;
        setNextQuestions();
    }else{
        replaceSceneTransitionFadeOut(E002_C010_P310);
    }
}

void E002_C010_P320::onTouchedNavigationButtonAtNext()
{
    E002_Base_Question::onTouchedNavigationButtonAtNext();
    
    if (m_nCurrentStageIndex < m_nMaxStageCount-1)
    {
        m_nCurrentStageIndex++;
        setNextQuestions();
    }
    else
    {
        onEnd();
    }
    
}

void E002_C010_P320::onTouchedNavigationButtonAtReward()
{
    showLetPlay3RewardPopup(NULL, m_nCurrentStageIndex - 1 +3);
}

#pragma mark - my util

CJSprite* E002_C010_P320::createSprite(std::string pStr)
{
    return CJPsdParser::getPsdSprite(pStr, m_psdDictionary);
}


void E002_C010_P320::_setPositionOutParent(CCNode* child, CCNode* newParent)
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

void E002_C010_P320::_safeRemoveFromParents(CCNode* pChild)
{
    if (pChild && pChild->getParent()) {
        pChild->removeFromParent();
    }
}

