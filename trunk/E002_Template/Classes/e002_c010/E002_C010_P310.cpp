

#include "E002_C010_P310.h"
#include "E002_C010_BaseUtil.h"
#include "E002_C010_P000_Index.h"
#include "E002_C010_P320.h"
#include <math.h>   // abs() fabs()



enum
{
    kTagExample001,
    kTagExample002,
    
    _kTagBgCover,
    _kTagShip,
    _kTagQueBg,
    _kTagQueBand,
    _kTagHighlight,
    _kTagCroc_l,
    _kTagCroc_r,
    _kTagCroc_close_l,
    _kTagCroc_close_r,
    _kTagCroc_open_l,
    _kTagCroc_open_r,
    _kTagCroc_shadow_1,
    _kTagCroc_shadow_2,
    _kTagCroc_Tail,
    
    _kTagWave1,
    _kTagWave2,
    
    _kTagEfx,
    
    _kTagFish1,
    _kTagFish2,
    _kTagFish3,
    _kTagFish4,
    _kTagFish5,
    _kTagFish6,
};

enum depth{
    _kDepthBackground = kDepth0_background,
    _kDepthBackImage = kDepth0_backImage,
   
    
};


E002_C010_P310::E002_C010_P310()
{
    
    m_touchingExampleSp = NULL;
    candy = NULL;
    copyCandy = NULL;
    mSndManager = new E002_C010_SoundManager;
}

E002_C010_P310::~E002_C010_P310()
{
    CC_SAFE_DELETE(mSndManager);
}

#pragma mark - init

bool E002_C010_P310::init()
{
    if (!E002_Base_Question::init()) {
        return false;
    }
    
    m_nMaxStageCount = 4;
    m_nCurrentStageIndex = 1;
    _oldCurrentStageIndex = m_nCurrentStageIndex;
    _selectedIndex = 0;
    
    return true;
}

void E002_C010_P310::onEnter()
{
    E002_Base_Question::onEnter();
    setTouchDisalbeBaseLayer();
    onViewLoad();
}

void E002_C010_P310::onExit()
{
    
    for (int i = 0; i < mQuestions.size(); i++) {
        CC_SAFE_RELEASE_NULL(mQuestions[i]);
    }
    
    for (int i = 0; i < mExamples.size(); i++) {
        std::vector<SSExampleItem*> vec = mExamples[i];
        for (int j = 0; j < vec.size(); j++) {
            CC_SAFE_RELEASE_NULL(vec[j]);
        }
    }
    
    E002_Base_Question::onExit();
}


void E002_C010_P310::onViewLoad()
{
    E002_Base_Question::onViewLoad();
    
    std::string questionsTxtName[4] =
    {
        "e002_c010_p310_img_que_00", //guide
        "e002_c010_p310_img_que_01",
        "e002_c010_p310_img_que_02",
        "e002_c010_p310_img_que_03",
    };

    
    std::string questionsSndName[4] =
    {
        wordSoundFileNames[19],  //guide
        wordSoundFileNames[6],
        wordSoundFileNames[11],
        wordSoundFileNames[13],
    };
    
    
    for (int i = 0; i < m_nMaxStageCount; i++)
    {
        SSQuestionItem* item = SSQuestionItem::create("",
                                                      questionsTxtName[i],
                                                      "",
                                                      "",
                                                      questionsSndName[i],
                                                      "",
                                                      "");
        item->retain();
        mQuestions.push_back(item);
    }
    
    
    
    // example setting =================
    
    std::string exampleImgName[4][2] =
    {
        {
            "e002_c010_p310_img_ans00_00",
            "e002_c010_p310_img_ans00_01"
        },
        
        {
            "e002_c010_p310_img_ans01_00",
            "e002_c010_p310_img_ans01_01"
        },
        {
            "e002_c010_p310_img_ans02_00",
            "e002_c010_p310_img_ans02_01"
        },
        {
            "e002_c010_p310_img_ans03_00",
            "e002_c010_p310_img_ans03_01"
        }
    };
    
    std::string exampleSndName[4][2] =
    {
        {wordSoundFileNames[18], wordSoundFileNames[8]}, //guide
        {wordSoundFileNames[13], wordSoundFileNames[07]},
        {wordSoundFileNames[10], wordSoundFileNames[16]},
        {wordSoundFileNames[6], wordSoundFileNames[12]},
        
    };
    
    int correctTags[4] =
    {
        kTagExample001,
        kTagExample002,
        kTagExample001,
        kTagExample002,
    };
    
    
    
    for (int i = 0; i < m_nMaxStageCount; i++)
    {
        std::vector<SSExampleItem*> examples;
        for (int j = 0; j < 2; j++)
        {
            SSExampleItem* item = SSExampleItem::create(i,
                                                        exampleImgName[i][j],
                                                        "",
                                                        exampleSndName[i][j],
                                                        kTagExample001 + j,
                                                        correctTags[i]);
            item->retain();
            examples.push_back(item);
        }
        mExamples.push_back(examples);
    }
    
    
    
    CJPsdParser::parseToPsdJSON("e002_c010_p310.json", &m_psdDictionary);
    
    setBackground("e002_c010_p310_img_bg_00.jpg");
    std::string coverName = m_bIsGuide ? "e002_c010_p310_img_bg_02" : "e002_c010_p310_img_bg_01";
    CJSprite* bgCover = createSprite(coverName);
    addChild(bgCover, kDepth2_questions+1, _kTagBgCover);
    bgCover->setPosition(ccpAdd( bgCover->getPosition(),ccp(0, 2)));
    bgCover->setVisible(false);
    
    
    mShip = createSprite("e002_c010_p310_img_ship");
    addChild(mShip, kDepth3_examples, _kTagShip);
    mShip->runAction(CCRepeatForever::create(CCSequence::create(CCEaseSineInOut::create(CCMoveBy::create(1.5, ccp(0, -10))),
                                                                CCEaseSineInOut::create(CCMoveBy::create(1.5, ccp(0, 10))),
                                                                NULL)));
    mShip->runAction(CCRepeatForever::create(CCSequence::create(CCEaseSineInOut::create(CCRotateTo::create(3.5, -1)),
                                                                CCEaseSineInOut::create(CCRotateTo::create(3.5,  1)),
                                                                NULL)));
    
    CJSprite* queBg1 = createSprite("e002_c010_p310_img_que_bg_00");
    addChild(queBg1, mShip->getZOrder()+1);
    
    queBand_l = createSprite("e002_c010_p310_img_band@2" );
    queBand_l->setAnchorPoint(ccp(0, 0.5));
    queBg1->addChildIgnoreParent(queBand_l, 0, _kTagQueBand);
    
    queBand_r = createSprite("e002_c010_p310_img_band@4");
    queBand_r->setAnchorPoint(ccp(1, 0.5));
    queBg1->addChildIgnoreParent(queBand_r, 0);
   
    mQueBg = createSprite("e002_c010_p310_img_que_bg_01");
    addChild(mQueBg, kDepth4_title, _kTagQueBg);
    
    
    pStick_l = CJPsdParser::getPsdPosition("e002_c010_p310_img_band@2", m_psdDictionary);//왼쪽 나무
    pStick_r = CJPsdParser::getPsdPosition("e002_c010_p310_img_band@4", m_psdDictionary);//오른쪽 나무
    
    CCPoint pHole_l = CJPsdParser::getPsdPosition("e002_c010_p310_img_band@1", m_psdDictionary);//왼쪽 구멍
    CCPoint pHole_r = CJPsdParser::getPsdPosition("e002_c010_p310_img_band@3", m_psdDictionary);//오른쪽 구멍
    pHole_l = ccpSub(mQueBg->getPosition(), ccp(mQueBg->getContentSize().width/2-16, mQueBg->getContentSize().height/2-54));        //16,54
    pHole_r = ccpAdd(mQueBg->getPosition(), ccp(176 - mQueBg->getContentSize().width/2, 54-mQueBg->getContentSize().height/2));   //176,54
    
    fOriginDist_l=queBand_l->getContentSize().width;
    float delAngle1 = CC_RADIANS_TO_DEGREES(-ccpToAngle(ccpSub(pHole_l, pStick_l)));
    queBand_l->setRotation(delAngle1);
    
    fOriginDist_r = queBand_r->getContentSize().width;
    float delAngle2 = CC_RADIANS_TO_DEGREES(-ccpToAngle(ccpSub(pStick_r, pHole_r)));
    queBand_r->setRotation(delAngle2);

    
    //wave
    CJSprite* wave1 = createSprite("e002_c010_p310_img_wave_b_00");
    addChild(wave1, kDepth2_questions+2, _kTagWave1);
    CJSprite* wave2 = createSprite("e002_c010_p310_img_wave_b_01");
    addChild(wave2, kDepth2_questions+2, _kTagWave2);
   
    wave1->runAction(CCRepeatForever::create(CCSequence::create(CCEaseInOut::create(CCMoveTo::create(3.5, ccp(512+100, wave1->m_originPosition.y)) , 2.0),
                                                                CCEaseInOut::create(CCMoveTo::create(3.5, ccp(512-100, wave1->m_originPosition.y)) , 2.0),
                                                                NULL)));
    wave2->runAction(CCRepeatForever::create(CCSequence::create(CCEaseInOut::create(CCMoveTo::create(3.5, ccp(512-100, wave2->m_originPosition.y)) , 2.0),
                                                                CCEaseInOut::create(CCMoveTo::create(3.5, ccp(512+100, wave2->m_originPosition.y)) , 2.0),
                                                                NULL)));
    
    wave1->runAction(CCRepeatForever::create(CCSequence::create(CCEaseSineInOut::create(CCMoveBy::create(1.5, ccp(0, -10))),
                                                                CCEaseSineInOut::create(CCMoveBy::create(1.5, ccp(0, 10))),
                                                                NULL)));
    wave2->runAction(CCRepeatForever::create(CCSequence::create(CCEaseSineInOut::create(CCMoveBy::create(1.5, ccp(0, -10))),
                                                                CCEaseSineInOut::create(CCMoveBy::create(1.5, ccp(0, 10))),
                                                                NULL)));
    
    
    //fish
//    for (int i = 0; i < 6; i++) {
//        std::string str = CJUtils::getStringFormatInteger("e002_c010_p310_img_fish_0%d", i);
//        CJSprite* fish = createSprite(str);
//        addChild(fish, kDepth2_questions, _kTagFish1+i);
//        
//        if (i > 2) {
//            reorderChild(fish, kDepth1_actors-1);
//        }
//        
//    }
    
    
    // crocodiles
    CJSprite* crocodile_l = createSprite("e002_c010_p310_img_ans_start_l");
    addChild(crocodile_l, kDepth3_examples, _kTagCroc_l);
    crocodile_l->setPositionX(- crocodile_l->getContentSize().width);
    crocodile_l->m_secondPosition = crocodile_l->getPosition();
    
    CJSprite* crocodile_r = createSprite("e002_c010_p310_img_ans_start_r");
    addChild(crocodile_r, kDepth3_examples, _kTagCroc_r);
    crocodile_r->setPositionX(winSize.width + crocodile_r->getContentSize().width);
    crocodile_r->m_secondPosition = crocodile_r->getPosition();
    
    CJSprite* crocodile_close_l = createSprite("e002_c010_p310_img_ans_close_l_01");
    addChild(crocodile_close_l, kDepth3_examples, _kTagCroc_close_l);
    CJSprite* crocodile_tail_l = createSprite("e002_c010_p310_img_ans_close_l_00");
    crocodile_close_l->addChildIgnoreParent(createSprite("e002_c010_p310_img_ans_close_l_shadow_01"),-1,_kTagCroc_shadow_1);
    crocodile_close_l->addChildIgnoreParent(createSprite("e002_c010_p310_img_ans_close_l_shadow_00"),-1,_kTagCroc_shadow_2);
    crocodile_close_l->addChildIgnoreParent(crocodile_tail_l,-1,_kTagCroc_Tail);
    crocodile_close_l->setVisible(false);
    

    CJSprite* crocodile_close_r = createSprite("e002_c010_p310_img_ans_close_r_01");
    addChild(crocodile_close_r, kDepth3_examples, _kTagCroc_close_r);
    CJSprite* crocodile_tail_r = createSprite("e002_c010_p310_img_ans_close_r_00");
    crocodile_close_r->addChildIgnoreParent(createSprite("e002_c010_p310_img_ans_close_r_shadow_01"),-1,_kTagCroc_shadow_1);
    crocodile_close_r->addChildIgnoreParent(createSprite("e002_c010_p310_img_ans_close_r_shadow_00"),-1,_kTagCroc_shadow_2);
    crocodile_close_r->addChildIgnoreParent(crocodile_tail_r,-1,_kTagCroc_Tail);
    crocodile_close_r->setVisible(false);

    
    
    CJSprite* crocodile_open_l = createSprite("e002_c010_p310_img_ans_open_l_00");
    addChild(crocodile_open_l, kDepth3_examples, _kTagCroc_open_l);
    crocodile_open_l->addChildIgnoreParent(createSprite("e002_c010_p310_img_ans_open_l_shadow"),-1,_kTagCroc_shadow_1);
    crocodile_open_l->setVisible(false);
    
    CJSprite* crocodile_open_r = createSprite("e002_c010_p310_img_ans_open_r_00");
    addChild(crocodile_open_r, kDepth3_examples, _kTagCroc_open_r);
    crocodile_open_r->addChildIgnoreParent(createSprite("e002_c010_p310_img_ans_open_r_shadow"),-1,_kTagCroc_shadow_1);
    crocodile_open_r->setVisible(false);

    
    CJSprite* smallWave1 = createSprite("e002_c010_p310_img_wave_s_00");
    CJSprite* smallWave2 = createSprite("e002_c010_p310_img_wave_s_01");
    CJSprite* smallWave3 = createSprite("e002_c010_p310_img_wave_s_02");
    addChild(smallWave1, kDepth0_backImage);
    addChild(smallWave2, kDepth0_backImage);
    addChild(smallWave3, kDepth2_questions+2);
    


    
    _currentQuestionItem = mQuestions[m_nCurrentStageIndex];
    
    
    if(m_bIsGuide)
    {
        createGuideDim(kDepth2_questions-2);
    }
    
    // FLASH
    setAnimationFile("e002_c010_p310_flash_as_sheets.json", "e002_c010_p310_flash_as_animations.json", FLASH_ANISON);
    setAnimationFile("e002_c010_p310_flash_ch_sheets.json", "e002_c010_p310_flash_ch_animations.json", FLASH_CHU);
    setAnimationFile("e002_c010_p310_flash_sub_sheets.json", "e002_c010_p310_flash_sub_animations.json", FLASH_OTHERONE);
    animationManagerParseStart();
}

void E002_C010_P310::onViewLoaded()
{
    E002_Base_Question::onViewLoaded();
    
    if (m_nCurrentStageIndex == 1) {
        E002_Base_Navigation::setVisibleButton(false, eNavigationButton_Prev);
    }
    
//    mSndManager->playBgm(E002_C010_SoundManager::p310);
    
    

    
    
    

    


}

void E002_C010_P310::startFlashAnimation()
{
    //anison
    //e002_c010_p310_flash_as_f01
    //e002_c010_p310_flash_as_n01_action
    //e002_c010_p310_flash_as_n01_loop
    //e002_c010_p310_flash_as_n02_speak
    //e002_c010_p310_flash_as_s01
    createAnimationAndSetKey(FLASH_ANISON, "e002_c010_p310_flash_as_n01_loop", FLASH_KEY_LOOPING);
    createAnimationAndSetKey(FLASH_ANISON, "e002_c010_p310_flash_as_s01", FLASH_KEY_SUCCESS);
    createAnimationAndSetKey(FLASH_ANISON, "e002_c010_p310_flash_as_f01", FLASH_KEY_FAIL);
    createAnimationAndSetKey(FLASH_ANISON, "e002_c010_p310_flash_as_n01_action", FLASH_KEY_ACTION1);
    createAnimationAndSetKey(FLASH_ANISON, "e002_c010_p310_flash_as_n02_speak", FLASH_KEY_SPEAK);
    //    "e002_c010_p310_flash_sun_n01_action"
    
    //chu
    //e002_c010_p310_flash_ch_f01
    //e002_c010_p310_flash_ch_n01_action
    //e002_c010_p310_flash_ch_n01_loop
    //e002_c010_p310_flash_ch_s01
    createAnimationAndSetKey(FLASH_CHU, "e002_c010_p310_flash_ch_n01_loop", FLASH_KEY_LOOPING);
    createAnimationAndSetKey(FLASH_CHU, "e002_c010_p310_flash_ch_s01", FLASH_KEY_SUCCESS);
    createAnimationAndSetKey(FLASH_CHU, "e002_c010_p310_flash_ch_f01", FLASH_KEY_FAIL);
    createAnimationAndSetKey(FLASH_CHU, "e002_c010_p310_flash_ch_n01_action", FLASH_KEY_ACTION1);
    
    
    
    createAnimationAndSetKey(FLASH_OTHERONE, "e002_c010_p310_flash_sub_s01_action_1", FLASH_KEY_ACTION1);
    createAnimationAndSetKey(FLASH_OTHERONE, "e002_c010_p310_flash_sub_s01_action_2", FLASH_KEY_ACTION2);
    
    _playAnimationAnison(FLASH_KEY_LOOPING);
    _playAnimationChu(FLASH_KEY_LOOPING);
    
//    CJUtils::performSelector(this, callfunc_selector(E002_C010_P310::onFirstNarration),1.5);
    if(m_bIsGuide)
    {
        CJUtils::performSelector(this, callfunc_selector(E002_Base_Question::removeTouchDelegateForGuide), 0.5);
        CJUtils::performSelector(this, callfunc_selector(E002_C010_P310::start),0.3);
    }
    else
    {
        CJUtils::performSelector(this, callfunc_selector(E002_C010_P310::onFirstNarration),1.5);
    }
}

void E002_C010_P310::onFirstNarration()
{
    E002_Base_Question::onFirstNarration();

    mFirstNarration = "e002_c010_p310_snd_01_as.mp3";
    playNarration(mFirstNarration);
    _playAnimationAnison(FLASH_KEY_SPEAK);
}

void E002_C010_P310::onFirstNarrationEnd()
{
    E002_Base_Question::onFirstNarrationEnd();
    setTouchDisalbeBaseLayer();
//    if (getUserDefaultFirstGuide(eGuidePageP310) == false)
//    {
        mShowFirstGuide = true;
        setUserDefaultFirstGuide(eGuidePageP310);
        showGuide();
//    }else{
//        
//        start();
//    }
}

void E002_C010_P310::onNarrationFinishedCallback(std::string fileName)
{
    if (fileName == mFirstNarration && !isFirstSkiped())
    {
        onFirstNarrationEnd();
    }
    else if (fileName == mFirstNarration)
    {
        removeAllAnimationsInDataPool(FLASH_ANISON);
        _playAnimationAnison(FLASH_KEY_LOOPING);
//        _playAnimationChu(FLASH_KEY_LOOPING);
    }

}

#pragma mark - touch

bool E002_C010_P310::onTouchBegan(CCPoint tp)
{

    if (CJUtils::hitTestPoint(mQueBg, tp, false)) {
        
        m_bIsQueBgTouched = true;
        candy->setScale(1);
        
        CJSprite* queImg = mQuestions[m_nCurrentStageIndex]->txtSprite;
        mQuestions[m_nCurrentStageIndex]->playEffect();
        mQuestions[m_nCurrentStageIndex]->playAction(queImg);
        
        _touchGab = ccpSub(mQueBg->getPosition(), tp);
        _touchGabCandy = ccpSub(candy->getPosition(), tp);
        
        copyCandy->setVisible(true);
        
        if(m_bIsGuide)
        {
            
            schedule(schedule_selector(E002_C010_P310::guideScheduler), 1/60.f);
            showHand(NULL, 1);
            mQueBg->runAction(CCEaseSineOut::create(CCMoveTo::create(0.7f, ccpAdd(mQueBg->getPosition(), ccp(100, -100)))));
        }
        
        return true;
    }
    
    
    for (int i = 0; i < 2; i++) {
        CJSprite* example =  mExamples[m_nCurrentStageIndex][i]->sprite;
        if (CJUtils::hitTestPoint(example, tp, false)) {
            stopSpeakingAndLooping();
            mExamples[m_nCurrentStageIndex][i]->playEffect();
            mExamples[m_nCurrentStageIndex][i]->playAction();
            return false;
        }
    }
    

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

    
    return false;
}

void E002_C010_P310::onTouchMoved(CCPoint tp)
{
//    CJLog("-------- touch moved ------------");
//    CJLog("getLocation          = %.2f, %.2f",pTouch->getLocation().x, pTouch->getLocation().y);
//    CJLog("getPreviousLocation  = %.2f, %.2f",pTouch->getPreviousLocation().x, pTouch->getPreviousLocation().y);
//    CJLog("--------     end     ------------");
    
    
    if (m_bIsQueBgTouched) {
        
        float minX = mQueBg->m_originPosition.x - 200;
        float maxX = mQueBg->m_originPosition.x + 200;
        float minY = mQueBg->m_originPosition.y - 300;
        float maxY = mQueBg->m_originPosition.y;
        
        
        tp.x = MAX(tp.x, minX);
        tp.x = MIN(tp.x, maxX);
        tp.y = MAX(tp.y, minY);
        tp.y = MIN(tp.y, maxY);
        
//        preTp.x = MAX(preTp.x, minX);
//        preTp.x = MIN(preTp.x, maxX);
//        preTp.y = MAX(preTp.y, minY);
//        preTp.y = MIN(preTp.y, maxY);
        
        
        CCPoint bgPos = ccpAdd(tp, _touchGab);
        mQueBg->setPosition(bgPos);
        
        
        CCPoint pHole_l = ccpSub(mQueBg->getPosition(), ccp(mQueBg->getContentSize().width/2-16, mQueBg->getContentSize().height/2-54));        //16,54
        CCPoint pHole_r = ccpAdd(mQueBg->getPosition(), ccp(176 - mQueBg->getContentSize().width/2, 54-mQueBg->getContentSize().height/2));   //176,54
        
        float delAngle1 = CC_RADIANS_TO_DEGREES(-ccpToAngle(ccpSub(pHole_l, pStick_l)));
        queBand_l->setRotation(delAngle1);
        
        float delAngle2 = CC_RADIANS_TO_DEGREES(-ccpToAngle(ccpSub(pStick_r, pHole_r)));
        queBand_r->setRotation(delAngle2);
        
        
        float distance1 = ccpDistance(pHole_l, pStick_l);
        float distance2 = ccpDistance(pHole_r, pStick_r);
        
        float scaleFactor_l = distance1 / fOriginDist_l;
        queBand_l->setScaleX(scaleFactor_l);
        float scaleFactor_r = distance2 / fOriginDist_r;
        queBand_r->setScaleX(scaleFactor_r);
        
        
        

        candy->setPosition(ccpAdd(tp, _touchGabCandy));
        
        
        //        CCLog("ccpDistance = %.2f",ccpDistance(mQueBg->getPosition(), mQueBg->m_originPosition));
        
        static bool bCandyScale = false;
        if (ccpDistance(mQueBg->getPosition(), mQueBg->m_originPosition) > 60 && (fabs(mQueBg->getPositionX() - winCenter.x) > 40))
//        if(ccpDistance(mQueBg->getPosition(), mQueBg->m_originPosition) > 60  && (candy->m_originPosition.y - mQueBg->getPositionY()) > 10) // 던진다
        {
            if(!bCandyScale){
                candy->runAction(CCEaseElasticOut::create(CCScaleTo::create(0.3, 1.2)));
                bCandyScale = true;
                CCPoint targetPoint = CCPointZero;
                
                
                CJSprite* crocodile_current = NULL;
                CJSprite* crocodile_else = NULL;
                if (mQueBg->getPositionX() - winCenter.x > 0) { //left
                    crocodile_current = (CJSprite*)getChildByTag(_kTagCroc_open_l);
                    crocodile_else = (CJSprite*)getChildByTag(_kTagCroc_open_r);
                    
                    targetPoint = CJPsdParser::getPsdPosition("e002_c010_p310_img_candy_00@2_40%", m_psdDictionary);

                    
                }else{ //right
                    crocodile_current = (CJSprite*)getChildByTag(_kTagCroc_open_r);
                    crocodile_else = (CJSprite*)getChildByTag(_kTagCroc_open_l);
                    
                    targetPoint = CJPsdParser::getPsdPosition("e002_c010_p310_img_candy_00@3_40%", m_psdDictionary);
                }
                
                _copyCandyTargetPoint = targetPoint;
                runCopyCandy(targetPoint);
//                targetPoint = ccp(targetPoint.x - candy->m_originPosition.x, targetPoint.y - candy->m_originPosition.y);
//                copyCandy->runAction(CCRepeatForever::create(CCSequence::create(//CCMoveTo::create(0, ccp(521.00, 231.00)),
//                                                                                CCFadeTo::create(0, 190),
//                                                                                CCScaleTo::create(0, 1),
//                                                                                
//                                                                                CCSpawn::create(CCFadeTo::create(0.5, 0),
//                                                                                                CCScaleTo::create(0.5, 0.4),
//                                                                                                CCJumpBy::create(0.5, targetPoint, 400, 1),
//                                                                                                NULL),
//                                                                                
//                                                                                CCDelayTime::create(0.5),
//                                                                                CCCallFunc::create(this, callfunc_selector(E002_C010_P310::test)),
//                                                                                NULL)));
                
                
                crocodile_current->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(0.2, 1.1),
                                                                                        CCScaleTo::create(0.2, 1.0),
                                                                                        NULL)));
                crocodile_else->stopAllActions();
                crocodile_else->setScale(1.0);
            };
        }else{ // 안던져
            if (bCandyScale == true) {
                candy->runAction(CCEaseElasticOut::create(CCScaleTo::create(0.3, 1.0)));
                bCandyScale = false;
                
                CJSprite* crocodile_open_l = (CJSprite*)getChildByTag(_kTagCroc_open_l);
                CJSprite* crocodile_open_r = (CJSprite*)getChildByTag(_kTagCroc_open_r);
                crocodile_open_l->stopAllActions();
                crocodile_open_l->setScale(1.0);
                crocodile_open_r->stopAllActions();
                crocodile_open_r->setScale(1.0);
                
                
                copyCandy->stopAllActions();
                copyCandy->setPosition(copyCandy->m_originPosition);
                copyCandy->setOpacity(0);
            }
        }
    }
}

void E002_C010_P310::runCopyCandy(CCPoint pt)
{
//    pt = ccp(pt.x - candy->m_originPosition.x, pt.y - candy->m_originPosition.y);
    copyCandy->runAction(CCSequence::create(//CCMoveTo::create(0, ccp(521.00, 231.00)),
                                            CCFadeTo::create(0, 190),
                                            CCScaleTo::create(0, 1),
                                            
                                            CCSpawn::create(//CCFadeTo::create(0.8, 0),
                                                            CCScaleTo::create(0.8, 0.4),
                                                            CCJumpTo::create(0.8, _copyCandyTargetPoint, 400, 1),
                                                            NULL),
                                            CCFadeTo::create(0, 0),
                                            CCDelayTime::create(0.3),
                                            CCCallFunc::create(this, callfunc_selector(E002_C010_P310::test)),
                                            NULL));

}

void E002_C010_P310::test()
{
    copyCandy->setPosition(candy->getPosition());
    runCopyCandy(_copyCandyTargetPoint);
}

//void E002_C010_P310::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
//{
//    CCPoint tp = pTouch->getLocation();
//    CCPoint preTp = pTouch->getPreviousLocation();
//    
//    
//    
//    //touch test
////    CJLog("getLocationInView = %.2f, %.2f",pTouch->getLocationInView().x, pTouch->getLocationInView().y);
//   
//}

void E002_C010_P310::onTouchEnded(CCPoint tp)
{
   

    if (m_bIsQueBgTouched) {
        copyCandy->stopAllActions();
        copyCandy->setVisible(false);
        
        CJSprite* crocodile_open_l = (CJSprite*)getChildByTag(_kTagCroc_open_l);
        CJSprite* crocodile_open_r = (CJSprite*)getChildByTag(_kTagCroc_open_r);
        crocodile_open_l->stopAllActions();
        crocodile_open_l->setScale(1.0);
        crocodile_open_r->stopAllActions();
        crocodile_open_r->setScale(1.0);
        
        schedule(schedule_selector(E002_C010_P310::checkSchedule), 1/60.f);
        float dur = 0.7;
        float period = 0.3;
        
        
        if (ccpDistance(mQueBg->getPosition(), mQueBg->m_originPosition) > 60 && (fabs(mQueBg->getPositionX() - winCenter.x) > 40)) {
//        if (ccpDistance(mQueBg->getPosition(), mQueBg->m_originPosition) > 60 && (candy->m_originPosition.y - mQueBg->getPositionY()) > 10) {
            CJLog("==== in");
            
            
            CCPoint targetPoint = CCPointZero;
            if (tp.x > winCenter.x ) {
                targetPoint = CJPsdParser::getPsdPosition("e002_c010_p310_img_candy_00@2_40%", m_psdDictionary);
                _selectedIndex = 0;
            }
            
            else if(tp.x < winCenter.x ){
                targetPoint = CJPsdParser::getPsdPosition("e002_c010_p310_img_candy_00@3_40%", m_psdDictionary);
                _selectedIndex = 1;
            }
            _touchedExampleItem = mExamples[m_nCurrentStageIndex][_selectedIndex];
            intoTarget(candy, targetPoint);
            mQueBg->runAction(CCSequence::create(CCEaseElasticOut::create(CCMoveTo::create(dur, mQueBg->m_originPosition), period),
                                                 NULL));
            
        }else{
            _touchedExampleItem = NULL;
            mQueBg->runAction(CCSequence::create(CCEaseBackOut::create(CCMoveTo::create(dur, mQueBg->m_originPosition)),
                                                 NULL));
            candy->runAction(CCSequence::create(CCEaseBackOut::create(CCMoveTo::create(dur, candy->m_originPosition)),
                                                NULL));
        }
        
        if (m_bIsGuide) {
            unschedule(schedule_selector(E002_C010_P310::guideScheduler));

        }
    }
     m_bIsQueBgTouched = false;
    
    
}

#pragma mark - check 

void E002_C010_P310::intoTarget(CJSprite* sp, CCPoint tp)
{
    setTouchDisalbeBaseLayer();
    

    sp->runAction(CCSequence::create(CCSpawn::create(CCScaleTo::create(0.5, 0.4),
                                                     CCJumpTo::create(0.5, tp, 400, 1),
                                                     NULL),
                                     CCCallFuncN::create(this, callfuncN_selector(E002_C010_P310::checkAnswer)),
                                     NULL));
}



void E002_C010_P310::checkAnswer(CCNode *node)
{
    unschedule(schedule_selector(E002_C010_P310::checkSchedule));

    
    
    int closeTag = _kTagCroc_close_l + _touchedExampleItem->itemTag;
    int openTag = _kTagCroc_open_l + _touchedExampleItem->itemTag;
    
    CJSprite* crocodile_close = (CJSprite*)getChildByTag(closeTag);
    CJSprite* crocodile_open = (CJSprite*)getChildByTag(openTag);
    
    crocodile_open->setVisible(false);
    crocodile_close->setVisible(true);
    


    
    
    if (_touchedExampleItem->correctTag == _touchedExampleItem->itemTag) { //success
        //먹어
        
        playEffect("e002_c010_p310_snd_correct_04_ab.mp3");
        candy->removeFromParent();
        candy = NULL;
        
        CJSprite* bgCover = (CJSprite*)getChildByTag(_kTagBgCover);
        bgCover->setVisible(true);
        
        reorderChild(crocodile_close, kDepth2_questions);
        crocodile_close->runAction(CCEaseSineIn::create(CCSequence::create(CCDelayTime::create(0.8),
                                                                           CCMoveBy::create(0.2, ccp(0, -500)),
                                                                           CCDelayTime::create(0.4),
                                                                           CCCallFunc::create(this, callfunc_selector(E002_C010_P310::beforeSuccess)),
                                                                           NULL)));
        
        
        int idx = _touchedExampleItem->itemTag == 0 ? 1 : 0 ;
        int negOpenTag = _kTagCroc_open_l + idx;

        CJSprite* crocodile_open = (CJSprite*)getChildByTag(negOpenTag);
        CCPoint pMoveTarget = idx < 0.5 ? ccp(-200 ,crocodile_open->getPositionY()) : ccp(winSize.width + 200 ,crocodile_open->getPositionY());
        crocodile_open->runAction(CCMoveTo::create(0.5, pMoveTarget));
        

        mQuestions[m_nCurrentStageIndex]->txtSprite->runAction(CCScaleTo::create(0.2, 0));
        
        
        CCParticleSystemQuad* particle =  E002_C010_BaseUtil::addParticle("e002_c010_p310_heart_00.plist");
        particle->setPosition(crocodile_close->getPosition());
        addChild(particle, kDepth5_particle);
        
    }else{ //fail
        //먹지마
        playEffect("e002_c010_p310_snd_wrong_04_ab.mp3");
        playEffect("e002_c010_p000_sfx_09.mp3");
        
        crocodile_close->runAction(CCJumpBy::create(0.3, CCPointZero, 20, 1));
        crocodile_close->getChildByTag(_kTagCroc_Tail)->runAction(CCJumpBy::create(0.3, CCPointZero, -20, 1));
        crocodile_close->getChildByTag(_kTagCroc_shadow_1)->runAction(CCJumpBy::create(0.3, CCPointZero, -20, 1));
        crocodile_close->getChildByTag(_kTagCroc_shadow_2)->runAction(CCJumpBy::create(0.3, CCPointZero, -20, 1));
        
        reorderChild(candy, kDepth2_questions);
        candy->runAction(CCSequence::create(CCSpawn::create(CCScaleTo::create(0.5, 1.0),
                                                            CCJumpTo::create(0.5, ccp(winCenter.x, 100), 400, 1),
                                                            NULL),
                                            CCFadeOut::create(0),
                                            CCDelayTime::create(0.1),
                                            CCCallFuncND::create(this, callfuncND_selector(E002_C010_P310::onFails), NULL),
                                            NULL));
    
        //
        std::string fileName = _selectedIndex == 0 ? "e002_c010_p310_img_fail_efx_l" : "e002_c010_p310_img_fail_efx_r";
        CJSprite* efx = createSprite(fileName);
        efx->setOpacity(200);
        addChild(efx, crocodile_close->getZOrder(), _kTagEfx);
        efx->runAction(CCSequence::create(CCScaleTo::create(0.2, 1.3),
                                          CCScaleTo::create(0.2, 1),
                                          CCCallFunc::create(efx, callfunc_selector(CJSprite::removeFromParent)),
                                          NULL));
    }
//    mQuestions[m_nCurrentStageIndex]->playAction();
//    mQuestions[m_nCurrentStageIndex]->playSuccessSound();
//    CJUtils::performSelector(this, callfuncND_selector(E002_C010_P310::onSuccesses),NULL, 1.5);
}

#pragma mark - feedback event


void E002_C010_P310::beforeSuccess()
{
    mSndManager->playSuccessSfxSnd(1);
    
    std::string keyName = _selectedIndex == 0 ? FLASH_KEY_ACTION2 : FLASH_KEY_ACTION1 ;
    int tempDepth = m_bIsGuide ? kDepth2_questions : kDepth1_actors;
    CJAnimation* ani = playAnimationByKey(FLASH_OTHERONE, keyName, 1, tempDepth, this);
    
    CCSprite* text_l = getSpriteFromFlash(ani, "e002_c010_p310_flash_sub_text_l");
    CCSprite* text_r = getSpriteFromFlash(ani, "e002_c010_p310_flash_sub_text_r");
    
    
    std::string fileName_l = CJUtils::getStringFormatInteger("e002_c010_p310_img_success_0%d_01.png", m_nCurrentStageIndex);
    std::string fileName_r = CJUtils::getStringFormatInteger("e002_c010_p310_img_success_0%d_00.png", m_nCurrentStageIndex);
    
    text_l->setTexture(CCTextureCache::sharedTextureCache()->addImage(getFilePath("img",fileName_l).c_str()));
    text_r->setTexture(CCTextureCache::sharedTextureCache()->addImage(getFilePath("img",fileName_r).c_str()));
    
    
    playEffectWithDelay(mQuestions[m_nCurrentStageIndex]->snd , 0.8);
    playEffectWithDelay(mExamples[m_nCurrentStageIndex][_selectedIndex]->snd , 1.8);
    
    
    CCParticleSystemQuad* particle =  E002_C010_BaseUtil::addParticle("e002_c010_p310_fish_00.plist");
    addChild(particle, tempDepth-1);
    CJUtils::performSelector(this, callfunc_selector(E002_C010_P310::onFishParticle),0.4);
 
    playEffect("e002_c010_p300_sfx_river2.mp3");
}

void E002_C010_P310::onFishParticle()
{
    CCParticleSystemQuad* particle =  E002_C010_BaseUtil::addParticle("e002_c010_p310_fish_01.plist");
    addChild(particle, kDepth1_actors-1);
    CJUtils::performSelector(this, callfunc_selector(E002_C010_P310::onFishParticle2),0.4);
}

void E002_C010_P310::onFishParticle2()
{
    CCParticleSystemQuad* particle =  E002_C010_BaseUtil::addParticle("e002_c010_p310_fish_00.plist");
    addChild(particle, kDepth1_actors-1);
}



void E002_C010_P310::onSuccesses(CCNode *node, int tag)
{
    CCLog("onSuccess");

    
    mSndManager->playCorrectNarrationAnison(E002_C010_SoundManager::p310);
    mSndManager->playCorrectNarrationOtherOne(E002_C010_SoundManager::p310);
    
    playEffect("e002_c010_p110_sfx_jump_as.mp3");
    playEffect("e002_c010_p000_sfx_08.mp3");
    
    _playAnimationAnison(FLASH_KEY_SUCCESS,1);
    _playAnimationChu(FLASH_KEY_SUCCESS,1);
    
    
}


void E002_C010_P310::onFails(CCNode *node, int tag)
{
    CJLog("onFail");
    playEffect("e002_c010_p310_sfx_wrong_river.mp3");
    
    mSndManager->playWrongNarrationAnison(E002_C010_SoundManager::p310);
    mSndManager->playWrongNarrationOtherOne(E002_C010_SoundManager::p310);
    
    _playAnimationAnison(FLASH_KEY_FAIL,1);
    _playAnimationChu(FLASH_KEY_FAIL,1);
    
}

void E002_C010_P310::flashSuccessFinishCallback(CJAnimation* pAnimation)
{
    
}

void E002_C010_P310::flashFailFinishCallback(CJAnimation* pAnimation)
{
    
}

void E002_C010_P310::onComplete()
{
    E002_Base_Question::onComplete();
    
    if (m_nCurrentStageIndex < m_nMaxStageCount-1) {
        resetValue();
        m_nCurrentStageIndex++;
        setQuestions();
        setExamples();
    }else{
        CJLog("end");
        onEnd();
    }
    

}

void E002_C010_P310::onEnd()
{
    replaceSceneTransitionFadeOut(E002_C010_P320);
}

#pragma mark - set questions, set examples
void E002_C010_P310::start()
{
    _playAnimationAnison(FLASH_KEY_LOOPING);
    _playAnimationChu(FLASH_KEY_LOOPING);
    
    setQuestions();
    setExamples();
}

void E002_C010_P310::setQuestions()
{
    if (m_nCurrentStageIndex == 1) {
        E002_Base_Navigation::setVisibleButton(false, eNavigationButton_Prev);
    }else if(m_nCurrentStageIndex > 1){
        E002_Base_Navigation::setVisibleButton(true, eNavigationButton_Prev);
    }
    
    _oldCurrentStageIndex = m_nCurrentStageIndex;
    _currentQuestionItem = mQuestions[m_nCurrentStageIndex];
    
    _currentQuestionItem->createTxtSprite(m_psdDictionary);
    if (_currentQuestionItem->txtSprite->getParent() == NULL) {
        mQueBg->addChildIgnoreParent(_currentQuestionItem->txtSprite, kDepth3_examples);
    }
    _currentQuestionItem->txtSprite->setScale(0);
    
    candy = createSprite(CJUtils::getStringFormatInteger("e002_c010_p310_img_candy_0%d", (int)m_nCurrentStageIndex/2));
    addChild(candy, mQueBg->getZOrder()-2);
    candy->setScale(0);
    candy->runAction(CCEaseElasticOut::create(CCScaleTo::create(0.5, 1.0), 0.3));
    

    copyCandy = E002_C010_BaseUtil::copyCJSprite(candy);
    copyCandy->setVisible(false);
    copyCandy->setOpacity(0);
    addChild(copyCandy, candy->getZOrder()-1);
    copyCandy->m_originPosition = candy->m_originPosition;
    copyCandy->setPosition(copyCandy->m_originPosition);
    CJLog("copyCandy->m_originPosition = %.2f, %.2f", copyCandy->m_originPosition.x, copyCandy->m_originPosition.y);
    
    
//    _currentQuestionItem->playEffect();
//    _currentQuestionItem->playAction();


}

void E002_C010_P310::showQuestions()
{
    _currentQuestionItem->playEffect();
    _currentQuestionItem->playAction(_currentQuestionItem->txtSprite);
}

void E002_C010_P310::setExamples()
{
    CJSprite* crocodile_r = (CJSprite*)getChildByTag(_kTagCroc_r);
    CJSprite* crocodile_l = (CJSprite*)getChildByTag(_kTagCroc_l);
    
    float dist_l = crocodile_l->m_originPosition.x - crocodile_l->getPositionX();
    float dist_r = crocodile_r->m_originPosition.x - crocodile_r->getPositionX();
    
    playEffect("e002_c010_p300_sfx_river.mp3");
    crocodile_l->stopAllActions();
    crocodile_l->setPosition(crocodile_l->m_secondPosition);
    crocodile_l->runAction(CCSequence::create(CCEaseSineInOut::create(CCMoveBy::create(0.7, ccp(dist_l/3, 0))),
                                              CCEaseSineInOut::create(CCMoveBy::create(0.7, ccp(dist_l/3, 0))),
                                              CCEaseSineInOut::create(CCMoveTo::create(0.7, crocodile_l->m_originPosition)),
                                              NULL));
    crocodile_r->stopAllActions();
    crocodile_r->setPosition(crocodile_r->m_secondPosition);
    crocodile_r->runAction(CCSequence::create(CCEaseSineInOut::create(CCMoveBy::create(0.7, ccp(dist_r/3, 0))),
                                              CCEaseSineInOut::create(CCMoveBy::create(0.7, ccp(dist_r/3, 0))),
                                              CCEaseSineInOut::create(CCMoveTo::create(0.7, crocodile_r->m_originPosition)),
                                              CCCallFunc::create(this, callfunc_selector(E002_C010_P310::showExamples)),
                                              NULL));
    
    
    CJSprite* crocodile_open_l = (CJSprite*)getChildByTag(_kTagCroc_open_l);
    CJSprite* crocodile_open_r = (CJSprite*)getChildByTag(_kTagCroc_open_r);
    mExamples[m_nCurrentStageIndex][0]->createImgSprite(m_psdDictionary);
    mExamples[m_nCurrentStageIndex][0]->sprite->setScale(0);
    crocodile_open_l->addChildIgnoreParent(mExamples[m_nCurrentStageIndex][0]->sprite, kDepth3_examples);
    
    mExamples[m_nCurrentStageIndex][1]->createImgSprite(m_psdDictionary);
    mExamples[m_nCurrentStageIndex][1]->sprite->setScale(0);
    crocodile_open_r->addChildIgnoreParent(mExamples[m_nCurrentStageIndex][1]->sprite, kDepth3_examples);
}

void E002_C010_P310::showExamples()
{
    CJSprite* crocodile_r = (CJSprite*)getChildByTag(_kTagCroc_r);
    CJSprite* crocodile_l = (CJSprite*)getChildByTag(_kTagCroc_l);
    crocodile_l->setVisible(false);
    crocodile_r->setVisible(false);
    
    CJSprite* crocodile_close_l = (CJSprite*)getChildByTag(_kTagCroc_close_l);
    CJSprite* crocodile_close_r = (CJSprite*)getChildByTag(_kTagCroc_close_r);
    crocodile_close_l->setVisible(true);
    crocodile_close_r->setVisible(true);

    
    CJUtils::performSelector(this, callfunc_selector(E002_C010_P310::showQuestions), 0.5);
    CJUtils::performSelector(this, callfunc_selector(E002_C010_P310::showExamplesCallfunc_left), 1.5);
    CJUtils::performSelector(this, callfunc_selector(E002_C010_P310::showExamplesCallfunc_right), 2.5);
}

void E002_C010_P310::showExamplesCallfunc_left()
{
//    playEffect("e002_c010_p300_sfx_03.mp3");
    
    CJSprite* crocodile_close_l = (CJSprite*)getChildByTag(_kTagCroc_close_l);
    crocodile_close_l->setVisible(false);
    
    CJSprite* crocodile_open_l = (CJSprite*)getChildByTag(_kTagCroc_open_l);
    crocodile_open_l->setVisible(true);
    
    mExamples[m_nCurrentStageIndex][0]->sprite->runAction(CCSequence::create(mExamples[m_nCurrentStageIndex][0]->playEffectCallfunc(),
                                                                             CCEaseSineOut::create(CCScaleTo::create(0.15, 1.2)),
                                                                             CCDelayTime::create(0.2),
                                                                             CCEaseSineOut::create(CCScaleTo::create(0.15, 1.0)),
                                                                             NULL));
}

void E002_C010_P310::showExamplesCallfunc_right()
{
    
//    playEffect("e002_c010_p300_sfx_03.mp3");
    
    CJSprite* crocodile_close_r = (CJSprite*)getChildByTag(_kTagCroc_close_r);
    crocodile_close_r->setVisible(false);
    
    CJSprite* crocodile_open_r = (CJSprite*)getChildByTag(_kTagCroc_open_r);
    crocodile_open_r->setVisible(true);
    
    mExamples[m_nCurrentStageIndex][1]->sprite->runAction(CCSequence::create(
                                                                             mExamples[m_nCurrentStageIndex][1]->playEffectCallfunc(),
                                                                             CCEaseSineOut::create(CCScaleTo::create(0.15, 1.2)),
                                                                             CCDelayTime::create(0.2),
                                                                             CCEaseSineOut::create(CCScaleTo::create(0.15, 1.0)),
                                                                             CCCallFunc::create(this, callfunc_selector(E002_C010_P310::setTouchEnableBaseLayer)),
                                                                             NULL));
    
    if (m_bIsGuide)
    {
        this->runAction(CCSequence::create(CCDelayTime::create(0.7),
                                           CCCallFuncND::create(this, callfuncND_selector(E002_C010_P310::showHand), (void*)0),
                                           NULL));
        return;
    }
}


void E002_C010_P310::resetValue()
{
    setTouchDisalbeBaseLayer();
    stopAllActions();
    stopAllEffect();

    
    CJSprite* bgCover = (CJSprite*)getChildByTag(_kTagBgCover);
    bgCover->setVisible(false);
    
//    mShip->stopAllActions();
//    mShip->setPosition(mShip->m_originPosition);
//    mShip->runAction(CCRepeatForever::create(CCSequence::create(CCEaseSineInOut::create(CCMoveBy::create(1.5, ccp(0, -10))),
//                                                                CCEaseSineInOut::create(CCMoveBy::create(1.5, ccp(0, 10))),
//                                                                NULL)));
//    mShip->runAction(CCRepeatForever::create(CCSequence::create(CCEaseSineInOut::create(CCRotateTo::create(3.5, -1)),
//                                                                CCEaseSineInOut::create(CCRotateTo::create(3.5,  1)),
//                                                                NULL)));
    
    if (candy && candy->getParent()) {
        candy->removeFromParent();
        candy = NULL;
    }
    
    if (copyCandy && copyCandy->getParent()) {
        copyCandy->removeAllChildren();
        copyCandy = NULL;
    }

    CJSprite* eff = (CJSprite*)getChildByTag(_kTagEfx);
    if (eff && eff->getParent()) {
        eff->removeFromParent();
        eff = NULL;
    }

//    CJSprite* wave1 = (CJSprite*)getChildByTag(_kTagWave1);
//    CJSprite* wave2 = (CJSprite*)getChildByTag(_kTagWave2);
//    wave1->runAction(CCRepeatForever::create(CCSequence::create(CCEaseInOut::create(CCMoveTo::create(3.5, ccp(512+100, wave1->m_originPosition.y)) , 2.0),
//                                                                CCEaseInOut::create(CCMoveTo::create(3.5, ccp(512-100, wave1->m_originPosition.y)) , 2.0),
//                                                                NULL)));
//    wave2->runAction(CCRepeatForever::create(CCSequence::create(CCEaseInOut::create(CCMoveTo::create(3.5, ccp(512-100, wave2->m_originPosition.y)) , 2.0),
//                                                                CCEaseInOut::create(CCMoveTo::create(3.5, ccp(512+100, wave2->m_originPosition.y)) , 2.0),
//                                                                NULL)));
//    
//    wave1->runAction(CCRepeatForever::create(CCSequence::create(CCEaseSineInOut::create(CCMoveBy::create(1.5, ccp(0, -10))),
//                                                                CCEaseSineInOut::create(CCMoveBy::create(1.5, ccp(0, 10))),
//                                                                NULL)));
//    wave2->runAction(CCRepeatForever::create(CCSequence::create(CCEaseSineInOut::create(CCMoveBy::create(1.5, ccp(0, -10))),
//                                                                CCEaseSineInOut::create(CCMoveBy::create(1.5, ccp(0, 10))),
//                                                                NULL)));
    
    CJSprite* crocodile_l = (CJSprite*)getChildByTag(_kTagCroc_l);
    crocodile_l->setPosition(crocodile_l->m_secondPosition);
    crocodile_l->setVisible(true);
    crocodile_l->setScale(1.0);
    
    CJSprite* crocodile_r = (CJSprite*)getChildByTag(_kTagCroc_r);
    crocodile_r->setPosition(crocodile_r->m_secondPosition);
    crocodile_r->setVisible(true);
    crocodile_r->setScale(1.0);
    
    CJSprite* crocodile_close_l = (CJSprite*)getChildByTag(_kTagCroc_close_l);
    crocodile_close_l->setPosition(crocodile_close_l->m_originPosition);
    crocodile_close_l->setVisible(false);
    reorderChild(crocodile_close_l, kDepth3_examples);
    
    CJSprite* crocodile_close_r = (CJSprite*)getChildByTag(_kTagCroc_close_r);
    crocodile_close_r->setPosition(crocodile_close_r->m_originPosition);
    crocodile_close_r->setVisible(false);
    reorderChild(crocodile_close_r, kDepth3_examples);
    
    CJSprite* crocodile_open_l = (CJSprite*)getChildByTag(_kTagCroc_open_l);
    crocodile_open_l->setPosition(crocodile_open_l->m_originPosition);
    crocodile_open_l->setVisible(false);
    
    CJSprite* crocodile_open_r = (CJSprite*)getChildByTag(_kTagCroc_open_r);
    crocodile_open_r->setPosition(crocodile_open_r->m_originPosition);
    crocodile_open_r->setVisible(false);
    
    if (_currentQuestionItem->txtSprite) {
        _currentQuestionItem->txtSprite->removeFromParent();
        _currentQuestionItem->txtSprite = NULL;
    }
    if (mExamples[_oldCurrentStageIndex][0]->sprite) {
        mExamples[_oldCurrentStageIndex][0]->sprite->removeFromParent();
        mExamples[_oldCurrentStageIndex][0]->sprite = NULL;
    }
    if (mExamples[_oldCurrentStageIndex][1]->sprite) {
        mExamples[_oldCurrentStageIndex][1]->sprite->removeFromParent();
        mExamples[_oldCurrentStageIndex][1]->sprite = NULL;
    }
    
}


void E002_C010_P310::setNextQuestions()
{
    setTouchDisalbeBaseLayer();
    E002_C010_BaseUtil::stopAllAnimationsWithOutTags(this,_kTagWave1,_kTagWave2,_kTagShip,-1);
    resetValue();
    removeAllAnimationsInDataPool(FLASH_OTHERONE);
    start();
    
}

#pragma mark - appear, disappear



void E002_C010_P310::questionAppearStep1()
{

}
void E002_C010_P310::disappearAnimation()
{
    
    
    std::string keyName = _selectedIndex == 0 ? FLASH_KEY_ACTION1 : FLASH_KEY_ACTION2 ;
    CJAnimation* ani = getAnimationByKey(FLASH_OTHERONE, keyName);
    ani->stopAnimation(true);
    
    
//    CJSprite* crocodile = (CJSprite*)getChildByTag(_kTagCroc_l + _selectedIndex);
//    crocodile->setVisible(true);
//    crocodile->setScaleX(-1);
//    float dist_l = crocodile->m_secondPosition.x - crocodile->getPositionX();
//    crocodile->runAction(CCSequence::create(CCEaseSineInOut::create(CCMoveBy::create(0.7, ccp(dist_l/3, 0))),
//                                              CCEaseSineInOut::create(CCMoveBy::create(0.7, ccp(dist_l/3, 0))),
//                                              CCEaseSineInOut::create(CCMoveTo::create(0.7, crocodile->m_secondPosition)),
//                                            CCCallFunc::create(this, callfunc_selector(E002_C010_P310::onComplete)),
//                                              NULL));
//    
//
//    mQuestions[m_nCurrentStageIndex]->txtSprite->runAction(CCScaleTo::create(0.3, 0));
    
    if (m_bIsGuide) {
        ((E002_Base_Question*)getParent())->removeGuide();
    }else{
        showLetPlay3RewardItem(NULL, m_nCurrentStageIndex-1);
        CJUtils::performSelector(this, callfunc_selector(E002_C010_P320::onComplete),0.7 + 2.0); //0.7
        
    }
}

void E002_C010_P310::checkSchedule()
{
    CCPoint pHole_l = ccpSub(mQueBg->getPosition(), ccp(mQueBg->getContentSize().width/2-16, mQueBg->getContentSize().height/2-54));        //16,54
    CCPoint pHole_r = ccpAdd(mQueBg->getPosition(), ccp(176 - mQueBg->getContentSize().width/2, 54-mQueBg->getContentSize().height/2));   //176,54
    
    float delAngle1 = CC_RADIANS_TO_DEGREES(-ccpToAngle(ccpSub(pHole_l, pStick_l)));
    queBand_l->setRotation(delAngle1);
    
    float delAngle2 = CC_RADIANS_TO_DEGREES(-ccpToAngle(ccpSub(pStick_r, pHole_r)));
    queBand_r->setRotation(delAngle2);
    
    
    float distance1 = ccpDistance(pHole_l, pStick_l);
    float distance2 = ccpDistance(pHole_r, pStick_r);
    
    float scaleFactor_l = distance1 / fOriginDist_l;
    queBand_l->setScaleX(scaleFactor_l);
    float scaleFactor_r = distance2 / fOriginDist_r;
    queBand_r->setScaleX(scaleFactor_r);
}

void E002_C010_P310::OnLastFrame(CJAnimation* pAnimation)
{
    E002_C010_BaseUtil::OnLastFrame(pAnimation);
    

    static int cnt = 0;
    if (pAnimation->getKey() == FLASH_KEY_SUCCESS) {
        cnt++;
        if (cnt == 2) {
            cnt = 0;
            disappearAnimation();
        }
    }
    
    if (pAnimation->getKey() == FLASH_KEY_FAIL) {
        cnt++;
        if (cnt == 2) {
            cnt = 0;
            
            
            candy->setPosition(candy->m_originPosition);
            reorderChild(candy, mQueBg->getZOrder()-1);
            candy->setVisible(true);
            candy->setOpacity(255);
            candy->setScale(0);
            candy->runAction(CCEaseElasticOut::create(CCScaleTo::create(0.5, 1.0), 0.3));
            setTouchEnableBaseLayer();
            
            int closeTag = _kTagCroc_close_l + _touchedExampleItem->itemTag;
            int openTag = _kTagCroc_open_l + _touchedExampleItem->itemTag;
            CJSprite* crocodile_close = (CJSprite*)getChildByTag(closeTag);
            CJSprite* crocodile_open = (CJSprite*)getChildByTag(openTag);
            crocodile_open->setVisible(true);
            crocodile_close->setVisible(false);
        }
    }
    
    
    if (pAnimation->getKey() == FLASH_KEY_SPEAK) {
        pAnimation->stopAnimation(false);
        playAnimationByKey(pAnimation->getDataPool()->getKey(), FLASH_KEY_LOOPING, -1, pAnimation->getZOrder());
    }
    
    
    if (pAnimation->getDataPool()->getKey() == FLASH_OTHERONE) {
        removeAnimation(pAnimation);
        onSuccesses(NULL);
    }
}



#pragma mark - animation 

CJAnimation* E002_C010_P310::_playAnimationAnison(std::string pAniKey, int count)
{
    removeAllAnimationsInDataPool(FLASH_ANISON);
    return playAnimationByKey(FLASH_ANISON,pAniKey.c_str(), count, kDepth1_flash, mShip);
}

CJAnimation* E002_C010_P310::_playAnimationChu(std::string pAniKey, int count)
{
    removeAllAnimationsInDataPool(FLASH_CHU);
    return playAnimationByKey(FLASH_CHU,pAniKey.c_str(), count, kDepth1_flash, mShip);
}

void E002_C010_P310::stopSpeakingAndLooping()
{
    stopAllNarration();
    if (getAnimationByKey(FLASH_ANISON, FLASH_KEY_SPEAK)->isPlay()) {
        _playAnimationAnison(FLASH_KEY_LOOPING);
    }
    
}



#pragma mark - Guide

void E002_C010_P310::showGuide()
{
    E002_Base_Question::showGuide();
    
    m_Guide = E002_C010_P310::create();
    m_Guide->init();
    m_Guide->setGuide(true);
    addChild(m_Guide, kDepth10_guide);
    
    std::vector<CCPoint> *guideHandPosition = new std::vector<CCPoint>();
    
    guideHandPosition->push_back(ccpAdd(mQueBg->getPosition(), ccp(60, -60)));
    guideHandPosition->push_back(ccpAdd(ccpAdd(mQueBg->getPosition(), ccp(100, -100)), ccp(60, -60)));
    
    
    m_Guide->setGuideHandPosition(guideHandPosition);
}


void E002_C010_P310::removeGuide()
{
    E002_Base_Question::removeGuide();
    removeChild(m_Guide);
    
}

void E002_C010_P310::completeToMoveHand(CCNode *node, int index)
{
    switch (index) {
        case 0:
            onTouchBegan(ccpAdd(node->getPosition(),ccp(-60, 60)));
            break;
        case 1:
            onTouchEnded(ccpAdd(node->getPosition(),ccp(-60, 60)));
            //            onTouchBegan(node->getPosition());
            //            showHand(NULL, 2);
            //            break;
        default:
            break;
    }
}

void E002_C010_P310::completeFirstGuide()
{
    CJUtils::performSelector(this, callfunc_selector(E002_C010_P310::start),0.2);
    setTouchDisalbeBaseLayer();
}

void E002_C010_P310::guideScheduler()
{
    onTouchMoved(mQueBg->getPosition());
}

#pragma mark - navigation delegate

void E002_C010_P310::onTouchedNavigationButtonAtIndex()
{
    E002_Base_Question::onTouchedNavigationButtonAtIndex();
    E002_C010_P000_Index* _indexClass = E002_C010_P000_Index::create();
    _indexClass->init();
    _indexClass->setIndexDelegate(this);
    _indexClass->showIndex(this, _indexClass);
    addChild(_indexClass, kDepth11_Index);
    
}

void E002_C010_P310::onTouchedNavigationButtonAtInfo()
{
    E002_Base_Question::onTouchedNavigationButtonAtInfo();
    showGuide();
}

void E002_C010_P310::onTouchedNavigationButtonAtPrev()
{
    E002_Base_Question::onTouchedNavigationButtonAtPrev();

    if (m_nCurrentStageIndex > 1) {
        m_nCurrentStageIndex--;
        setNextQuestions();
    }else{
        replaceSceneTransitionFadeOut(E002_C010_P310);
    }
}

void E002_C010_P310::onTouchedNavigationButtonAtNext()
{
    E002_Base_Question::onTouchedNavigationButtonAtNext();
    if (m_nCurrentStageIndex < m_nMaxStageCount-1)
    {
        m_nCurrentStageIndex++;
        setNextQuestions();
    }
    else
    {
        replaceSceneTransitionFadeOut(E002_C010_P320);
    }
    
}

void E002_C010_P310::onTouchedNavigationButtonAtReward()
{
    showLetPlay3RewardPopup(NULL, m_nCurrentStageIndex - 1);
}

#pragma mark - my util

CJSprite* E002_C010_P310::createSprite(std::string pStr)
{
    return CJPsdParser::getPsdSprite(pStr, m_psdDictionary);
}


void E002_C010_P310::_setPositionOutParent(CCNode* child, CCNode* newParent)
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

void E002_C010_P310::_safeRemoveFromParents(CCNode* pChild)
{
    if (pChild && pChild->getParent()) {
        pChild->removeFromParent();
    }
}

