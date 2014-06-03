

#include "E002_C010_P210.h"
#include "E002_C010_P000_Index.h"
#include <math.h>
#include "E002_C010_BaseUtil.h"
#include "SSExampleItem.h"
#include "E002_C010_P310.h"
#include "E002_C010_P230.h"


#define TOP_LIMITE              631
#define LEFT_LIMITE             300//:40 //252:90
#define RIGHT_LIMITE            1024-LEFT_LIMITE //772

#define SIDE_ANGLE              61.75f
#define SIDE_SPEED              5
#define SIDE_DISTANCE_FACTOR    1.5
#define QEUSTION_FIRST_DIST     200


#define FLASH_NAME_ANISON_TALK  "e002_c010_p210_flash_as_n01_speak"
#define FLASH_NAME_ANISON_RUN   "e002_c010_p210_flash_as_s02_run"

#define FLASH_NAME_BOOM_RUN1    "e002_c010_p210_flash_bb_s02_run_1"
#define FLASH_NAME_BOOM_RUN2    "e002_c010_p210_flash_bb_s02_run_2"
#define FLASH_NAME_BOOM_ACTION0 "e002_c010_p210_flash_bb_n01_action_1"
#define FLASH_NAME_BOOM_ACTION1 "e002_c010_p210_flash_bb_n01_action_2"

enum
{
    kTagExample001,
    kTagExample002,
    
    _kTagBg,
    _kTagBar_left,
    _kTagBar_right,
    _kTagButte_left,
    _kTagButte_right,
    _kTagObjShadow,
    _kTagQueBg,
    _kTagQueBgHighlight,
    _kTagQueBgShadow,
    _kTagQueBackBoard,
    _kTagQueBackBoard2,
    _kTagQueBlank,
    _kTagExmStick_head_l,
    _kTagExmStick_head_r,
    
};

E002_C010_P210::E002_C010_P210()
{
    
    m_touchingExampleSp = NULL;
    
    
    _arrSideObjects_l = new CCArray();
    _arrSideObjects_r = new CCArray();
    mSndManager = new E002_C010_SoundManager;
    e = NULL;
    exampleDummy = NULL;
    _targetPoint = CCPointZero;
}

E002_C010_P210::~E002_C010_P210()
{
    _arrSideObjects_l->release();
    _arrSideObjects_r->release();
    
    CC_SAFE_DELETE(mSndManager);
}

#pragma mark - init

bool E002_C010_P210::init()
{
    if (!E002_Base_Question::init()) {
        return false;
    }
    
    m_nMaxStageCount = 7;
    m_nCurrentStageIndex = 1;
    _oldCurrentStageIndex = m_nCurrentStageIndex;
    _successCount = 0;
    
    return true;
}

void E002_C010_P210::onEnter()
{
    E002_Base_Question::onEnter();
    setTouchDisalbeBaseLayer();
    onViewLoad();
}

void E002_C010_P210::onExit()
{
    
    
    for (int i = 0; i < mExamples.size(); i++) {
        std::vector<SSExampleItem*> vec = mExamples[i];
        for (int j = 0; j < vec.size(); j++) {
            CC_SAFE_RELEASE_NULL(vec[j]);
        }
    }
    
    for (int i = 0; i < mQuestions.size(); i++) {
        std::vector<SSQuestionItem*> vec = mQuestions[i];
        for (int j = 0; j < vec.size(); j++) {
            CC_SAFE_RELEASE_NULL(vec[j]);
            
        }
    }
    
    E002_Base_Question::onExit();
}


void E002_C010_P210::onViewLoad()
{
    E002_Base_Question::onViewLoad();
    
    
    std::string questionsImgName[7][2] =
    {
        {"e002_c010_p210_img_que00_00"},
        {"e002_c010_p210_img_que00_01"},
        {"e002_c010_p210_img_que00_02"},
        {"e002_c010_p210_img_que00_03"},
        {"e002_c010_p210_img_que00_04","e002_c010_p210_img_que00_05"},
        {"e002_c010_p210_img_que00_06","e002_c010_p210_img_que00_07"},
        {"e002_c010_p210_img_que00_08","e002_c010_p210_img_que00_09"}
    };
    
    std::string questionsTxtName[7] =
    {
        "e002_c010_p210_img_que01_name",
        "e002_c010_p210_img_que01_kite",
        "e002_c010_p210_img_que01_bake",
        "e002_c010_p210_img_que01_five",
        "e002_c010_p210_img_que01_ape",
        "e002_c010_p210_img_que01_ine",
        "e002_c010_p210_img_que01_ide",
    };
    
    std::string questionsSuccessImgName[7][2] =
    {
        {"e002_c010_p210_img_success_00"},
        {"e002_c010_p210_img_success_01"},
        {"e002_c010_p210_img_success_02"},
        {"e002_c010_p210_img_success_03"},
        {"e002_c010_p210_img_success_04","e002_c010_p210_img_success_05"},
        {"e002_c010_p210_img_success_06","e002_c010_p210_img_success_07"},
        {"e002_c010_p210_img_success_08","e002_c010_p210_img_success_09"}
    };
    
    std::string questionsSndName[7][2] =
    {
        {wordSoundFileNames[11]},
        {wordSoundFileNames[12]},
        {wordSoundFileNames[9]},
        {wordSoundFileNames[18]},
        
        {wordSoundFileNames[5],wordSoundFileNames[4]},
        {wordSoundFileNames[16],wordSoundFileNames[17]},
        {wordSoundFileNames[15],wordSoundFileNames[14]},
    };
    
    std::string questionsSuccessSndName[7][2] =
    {
        {wordSoundFileNames[11]},
        {wordSoundFileNames[12]},
        {wordSoundFileNames[9]},
        {wordSoundFileNames[18]},
        
        {wordSoundFileNames[46],wordSoundFileNames[50]},
        {wordSoundFileNames[54],wordSoundFileNames[58]},
        {wordSoundFileNames[61],wordSoundFileNames[65]},
    };
    
    
    std::string questionsFailSndName[7][2] =
    {
        {wordSoundFileNames[36]},
        {wordSoundFileNames[42]},
        {wordSoundFileNames[38]},
        {wordSoundFileNames[43]},
        
        {wordSoundFileNames[47],wordSoundFileNames[51]},
        {wordSoundFileNames[55],wordSoundFileNames[59]},
        {wordSoundFileNames[62],wordSoundFileNames[66]},
    };
    
    
    std::string exampleImgName[7][4] =
    {
        {
            "e002_c010_p210_img_ans_a",
            "e002_c010_p210_img_ans_i"
        },
        
        {
            "e002_c010_p210_img_ans_i",
            "e002_c010_p210_img_ans_a"
        },
        {
            "e002_c010_p210_img_ans_i",
            "e002_c010_p210_img_ans_a"
        },
        {
            "e002_c010_p210_img_ans_a",
            "e002_c010_p210_img_ans_i"
        },
        {
            "e002_c010_p210_img_ans_n",
            "e002_c010_p210_img_ans_t",
            "e002_c010_p210_img_ans_c",
            "e002_c010_p210_img_ans_g"
            
        },
        {
            "e002_c010_p210_img_ans_l",
            "e002_c010_p210_img_ans_m",
            "e002_c010_p210_img_ans_p",
            "e002_c010_p210_img_ans_v"
        },
        {
            "e002_c010_p210_img_ans_h",
            "e002_c010_p210_img_ans_t",
            "e002_c010_p210_img_ans_w",
            "e002_c010_p210_img_ans_r"
        }
        
    };
    
    std::string exampleSndName[7][4] =
    {
        {wordSoundFileNames[2], wordSoundFileNames[3]}, //guide
        {wordSoundFileNames[3], wordSoundFileNames[2]},
        {wordSoundFileNames[3], wordSoundFileNames[2]},
        {wordSoundFileNames[2], wordSoundFileNames[3]},
        
        {wordSoundFileNames[45], wordSoundFileNames[44] ,wordSoundFileNames[48], wordSoundFileNames[49] },
        {wordSoundFileNames[52], wordSoundFileNames[53] ,wordSoundFileNames[57], wordSoundFileNames[56] },
        {wordSoundFileNames[60], wordSoundFileNames[44], wordSoundFileNames[64], wordSoundFileNames[63] },
        
    };
    
    
    int correntTags[7][2] =
    {
        {kTagExample001},
        {kTagExample001},
        {kTagExample002},
        {kTagExample002},
        
        {kTagExample002,2+kTagExample001},
        {kTagExample001,2+kTagExample002},
        {kTagExample001,2+kTagExample002}
    };
    
    
    
    int secondStage = (m_nMaxStageCount+1)/2;
    for (int i = 0; i < m_nMaxStageCount; i++)
    {
        int temp = i < secondStage ? 1 : 2;
        std::vector<SSQuestionItem*> questions;
        
        for (int j = 0; j < temp; j++) {
            
            SSQuestionItem* item = SSQuestionItem::create(questionsImgName[i][j],
                                                          questionsTxtName[i],
                                                          questionsSuccessImgName[i][j],
                                                          "",
                                                          questionsSndName[i][j],
                                                          questionsSuccessSndName[i][j],
                                                          questionsFailSndName[i][j]);
            item->retain();
            questions.push_back(item);
        }
        
        mQuestions.push_back(questions);
    }
    
    
    
    for (int i = 0; i < m_nMaxStageCount; i++)
    {
        
        int temp = i < secondStage ? 2 : 4;
        
        std::vector<SSExampleItem*> examples;
        for (int j = 0; j < temp; j++)
        {
            SSExampleItem* item = SSExampleItem::create(i,
                                                        exampleImgName[i][j],
                                                        "",
                                                        exampleSndName[i][j],
                                                        kTagExample001 + j,
                                                        correntTags[i][j/2]);
            item->retain();
            examples.push_back(item);
        }
        mExamples.push_back(examples);
    }
    
    
    
    mFirstNarration = "e002_c010_p210_snd_01_as.mp3";
    mFirstNarration2 = "e002_c010_p210_snd_02_as_backup.mp3";
    
    
    CJPsdParser::parseToPsdJSON("e002_c010_p210.json", &m_psdDictionary);
    
    CJSprite* bg2 = createSprite("e002_c010_p210_img_bg_00");
    addChild(bg2, kDepth0_background-2);
    CJSprite* bg = createSprite("e002_c010_p210_bg_01");
    addChild(bg, kDepth0_background, _kTagBg);
    
    
    CJSprite* leftBar = createSprite("e002_c010_p210_img_fence_l_00");
    addChild(leftBar, kDepth0_backImage+6, _kTagBar_left);
    CJSprite* rightBar = createSprite("e002_c010_p210_img_fence_r_00");
    addChild(rightBar, kDepth0_backImage+6, _kTagBar_right);
    
    
    CJSprite* butte_l = createSprite("e002_c010_p210_img_butte_l");
    addChild(butte_l, kDepth0_background-1, _kTagButte_left);
    butte_l->setAnchorPointWithoutPosition(ccp(0.2, 0));
    butte_l->m_originPosition = butte_l->getPosition();
    butte_l->setScale(0.6);
    
    CJSprite* butte_r = createSprite("e002_c010_p210_img_butte_r");
    addChild(butte_r, kDepth0_background-1, _kTagButte_right);
    butte_r->setAnchorPointWithoutPosition(ccp(0.8, 0));
    butte_r->m_originPosition = butte_r->getPosition();
    butte_r->setScale(0.6);
    
    _targetPoint = CJPsdParser::getPsdPosition("e002_c010_p210_img_blank_00", m_psdDictionary);
    
    
    makeSideObjects();
    sideObjectScheduler();
    _currentQuestionItem = mQuestions[m_nCurrentStageIndex][_successCount];
    
    
    mAnison = new CJAnimationCharacter(this, FLASH_ANISON);
    mAnison->setLooping("e002_c010_p210_flash_as_n01_loop");
    mAnison->setSuccess("e002_c010_p210_flash_as_s01_action", NULL);
    mAnison->setFails("e001_c010_p210_flash_as_f01_action",NULL);
    if (!m_bIsGuide) {
        mAnison->setZorder(kDepth0_backImage);
    }
    
    mBoomBoom = new CJAnimationCharacter(this, FLASH_BOOM);
    mBoomBoom->setLooping("e002_c010_p210_flash_bb_n01_loop");
    mBoomBoom->setSuccess("e002_c010_p210_flash_bb_s01_action", NULL);
    mBoomBoom->setFails("e002_c010_p210_flash_bb_f01_action",NULL);
    
    
    addAnimationCharacter(mAnison, mBoomBoom, NULL);
    
    
    
    if(m_bIsGuide)
    {
        createGuideDim(kDepth2_questions-2);
    }
    
    setAnimationFile("e002_c010_p210_flash_as_sheets.json", "e002_c010_p210_flash_as_animations.json", "ANISON");
    setAnimationFile("e002_c010_p210_flash_bb_sheets.json", "e002_c010_p210_flash_bb_animations.json", "BOOM");
//    animationManagerParseStart();
    parseStart();
}

void E002_C010_P210::onViewLoaded()
{
    CCLOG("aaa = onViewLoaded");
    
    
    E002_Base_Question::onViewLoaded();
    
    if (m_nCurrentStageIndex == 1) {
        E002_Base_Navigation::setVisibleButton(false, eNavigationButton_Prev);
    }
    //    mSndManager->playBgm(E002_C010_SoundManager::p210);
    
    setExamples();
    setQuestions();
    startFlashAnimation();
    
}

void E002_C010_P210::startFlashAnimation()
{
    CCLOG("aaa = startFlashAnimation");
    createAllAnimations();
    
    
    if(m_bIsGuide)
    {
        CJUtils::performSelector(this, callfunc_selector(E002_Base_Question::removeTouchDelegateForGuide), 0.5);
        showGuideQuestions();
        //        CJUtils::performSelector(this, callfunc_selector(E002_C010_P210::showGuideQuestions),0.3);
    }
    else
    {
        mAnison->showLooping();
        mBoomBoom->showLooping();
        CJUtils::performSelector(this, callfunc_selector(E002_C010_P210::onFirstNarration),1.0);
    }
}

void E002_C010_P210::onFirstNarration()
{
    E002_Base_Question::onFirstNarration();
    
    
    playNarration(mFirstNarration);
    removeAllAnimationsInDataPool(FLASH_ANISON);
    playAnimation(FLASH_ANISON, FLASH_NAME_ANISON_TALK, -1, kDepth0_backImage);
}

void E002_C010_P210::onFirstNarrationEnd()
{
    E002_Base_Question::onFirstNarrationEnd();
    setTouchDisalbeBaseLayer();
    
    
//    if (getUserDefaultFirstGuide(eGuidePageP210) == false)
//    {
        mShowFirstGuide = true;
        setUserDefaultFirstGuide(eGuidePageP210);
        showGuide();
//    }else{
//        
//        start();
//    }

    
}

void E002_C010_P210::onNarrationFinishedCallback(std::string fileName)
{
    if (fileName == mFirstNarration)
    {
        playNarration(mFirstNarration2);
    }
    else if (fileName == mFirstNarration2 && !isFirstSkiped())
    {
        onFirstNarrationEnd();
    }
    else if (fileName == mFirstNarration2)
    {
        removeAllAnimationsInDataPool(FLASH_ANISON);
        mAnison->showLooping();
    }
    
    
    
    
}

#pragma mark - touch

bool E002_C010_P210::onTouchBegan(CCPoint tp)
{
    
    
    CJSprite* questionBg = (CJSprite*)getChildByTag(_kTagQueBg);
    
    for (int i = 0; i < 2; i++)
    {
        CJSprite* example = mExamples[m_nCurrentStageIndex][(_successCount*2)+i]->sprite;
        if (example && CJUtils::hitTestPoint(example, tp, false)) {
            stopSpeakingAndLooping();
            
            
            _touchedExampleItem = mExamples[m_nCurrentStageIndex][(_successCount*2)+i];
            m_touchingExampleSp = example;
            
            
            CJSprite* stick_head = (CJSprite*)example->getParent();
            exampleDummy = (CJSprite*)E002_C010_BaseUtil::copyCJSprite(stick_head);
            exampleDummy->setPosition(stick_head->getParent()->convertToWorldSpace(stick_head->getPosition()));
            exampleDummy->setOpacity(150);
            addChild(exampleDummy, 100);
            mTouchedPointGab = ccpSub(exampleDummy->getPosition(), tp);
            
            
            playExampleNarrationRepeat(_touchedExampleItem->snd);
            
            
            example->runAction(CCSequence::create(CCEaseSineOut::create(CCScaleTo::create(0.15, 1.2)),
                                                  CCDelayTime::create(0.2),
                                                  CCEaseSineOut::create(CCScaleTo::create(0.15, 1.0)),
                                                  NULL));
            if (m_nCurrentStageIndex < 4) {
                e->runAction(CCRepeatForever::create(CCSequence::create(CCEaseSineOut::create(CCScaleTo::create(0.15, 1.2)),
                                                                        CCDelayTime::create(0.2),
                                                                        CCEaseSineOut::create(CCScaleTo::create(0.15, 1.0)),
                                                                        CCDelayTime::create(0.3),
                                                                        NULL)));
            }
            
            
            // for guide
            if(m_bIsGuide)
            {
                CJSprite* blank = (CJSprite*)questionBg->getChildByTag(_kTagQueBlank);
                showHand(NULL, 1);
                exampleDummy->runAction(CCEaseSineOut::create(CCMoveTo::create(0.7f, questionBg->convertToWorldSpace(blank->getPosition()))));
            }
            
            return true;
            
        }
    }
    
    
    if (questionBg && CJUtils::hitTestPoint(questionBg, tp, false)) {
        mQuestions[m_nCurrentStageIndex][_successCount]->playEffect();
        
        CJSprite* questionBgHighlight = (CJSprite*)questionBg->getChildByTag(_kTagQueBgHighlight);
        questionBgHighlight->runAction(CCSequence::create(CCFadeIn::create(0),
                                                          CCDelayTime::create(0.6),
                                                          CCFadeOut::create(0),
                                                          NULL));
        stopSpeakingAndLooping();
        return false;
    }
    
    
    
    
    
    if (CJUtils::hitTestPoint(getAnimationByName(FLASH_ANISON, FLASH_NAME_ANISON_TALK),tp, false)) {
        
        removeAllAnimationsInDataPool(FLASH_ANISON);
        stopAllNarration();
        playNarration(mFirstNarration2);
        playAnimation(FLASH_ANISON, FLASH_NAME_ANISON_TALK, -1, kDepth0_backImage);
        
    }
    
    if (CJUtils::hitTestPoint(mBoomBoom->getCurrentAnimationCharacter(),tp, false)) {
        
        stopSpeakingAndLooping();
        mSndManager->playBoomBoomTouchNarr();
    }
    
    
    
    
    return false;
}

void E002_C010_P210::onTouchMoved(CCPoint tp)
{
    exampleDummy->setPosition(ccpAdd(tp, mTouchedPointGab));
}

void E002_C010_P210::onTouchEnded(CCPoint tp)
{
    stopExampleNarrationRepeat();
    
    CJSprite* questionBg = (CJSprite*)getChildByTag(_kTagQueBg);
    CJSprite* blank = (CJSprite*)questionBg->getChildByTag(_kTagQueBlank);
    
    if (CJUtils::hitTestObjects(exampleDummy, blank)) {
        intoTarget(m_touchingExampleSp, CCPointZero);
    }
    exampleDummy->removeFromParent();
    exampleDummy = NULL;
    
    if (!m_bIsTapped) {
        playEffect("e002_c010_p000_sfx_01.mp3");
    }
    
    
    if (m_nCurrentStageIndex < 4) {
        e->stopAllActions();
        e->setScale(1.0);
    }

}

void E002_C010_P210::intoTarget(CJSprite* sp, CCPoint pt)
{
    setTouchDisalbeBaseLayer();
    
    CJUtils::performSelector(this, callfunc_selector(E002_C010_P210::_throwLope),0.5);
    //    bool isSuccess = ((SSExampleItem*)sp)->correctTag == ((SSExampleItem*)sp)->itemTag ? true : false;
}


void E002_C010_P210::_throwLope()
{
    std::string aniName = _touchedExampleItem->itemTag%2 == 0 ? FLASH_NAME_BOOM_ACTION1 : FLASH_NAME_BOOM_ACTION0 ;
    std::string textureName = "e002_c010_p210_flash_bb_n02_action_box_l";
    //  std::string textureName = _touchedExampleItem->itemTag == 0 ? "e002_c010_p210_flash_bb_n02_action_box_l" : "e002_c010_p210_flash_bb_n02_action_box_l";
    
    removeAllAnimationsInDataPool(FLASH_BOOM);
    CJAnimation* ani = playAnimation(FLASH_BOOM, aniName, 1, kDepth4_title);
    
    CCSprite* sp = getSpriteFromFlash(ani, textureName.c_str());
    CJSprite* head = (CJSprite*)_touchedExampleItem->sprite->getParent();
    head->retain();
    head->removeFromParentAndCleanup(false);
    head->setPosition(ccp(head->getContentSize().width/2, head->getContentSize().height/2));
    sp->addChild(head);
    head->release();
    
    ani->addCustomFrameCallback(this, callfuncND_selector(E002_C010_P210::_chagneDummy), 23, NULL);
    
    playEffectWithDelay("e002_c010_p210_sfx_rope.mp3", 0.5);
}

void E002_C010_P210::_chagneDummy(CCNode *seder, void* data)
{
    
    CJSprite* head = (CJSprite*)_touchedExampleItem->sprite->getParent();
    head->retain();
    head->removeFromParentAndCleanup(false);
    head->setPosition(_targetPoint);
    addChild(head);
    head->release();
}

void E002_C010_P210::checkAnswer(CCNode *node)
{
    
    SSExampleItem* item = (SSExampleItem*)node;
    if (item->correctTag == item->itemTag) {
        CJLog(" success !!! ");
        
        playNarration(_currentQuestionItem->successSnd);
        
        if (m_nCurrentStageIndex < 4) {
            showSuccessText();
        }
        else
        {
            //example 커지고,
            _touchedExampleItem->playAction();
            //question 커지고
            _currentQuestionItem->txtSprite->runAction(CCSequence::create(CCDelayTime::create(0.6),
                                                                          CCEaseSineOut::create(CCScaleTo::create(0.15, 1.2)),
                                                                          CCDelayTime::create(0.2),
                                                                          CCEaseSineOut::create(CCScaleTo::create(0.15, 1.0)),
                                                                          NULL));
            
            this->runAction(CCSequence::create(CCDelayTime::create(0.6 *2),
                                               CCCallFunc::create(this, callfunc_selector(E002_C010_P210::showSuccessText)),
                                               NULL));
            
        }
        
        
    }else{
        CJLog(" fail !!! ");
        playNarration(_currentQuestionItem->failSnd);
        
        if (m_nCurrentStageIndex < 4) {
            float delay = CJMultimedia::getInstance()->getNarrationTime(getFilePath("snd",_currentQuestionItem->failSnd));
            CJUtils::performSelector(this, callfuncND_selector(E002_C010_P210::onFails), 0 , delay+0.2);
            
        }else{
            //example 커지고,
            _touchedExampleItem->playAction();
            //question 커지고
            _currentQuestionItem->txtSprite->runAction(CCSequence::create(CCDelayTime::create(0.6),
                                                                          CCEaseSineOut::create(CCScaleTo::create(0.15, 1.2)),
                                                                          CCDelayTime::create(0.2),
                                                                          CCEaseSineOut::create(CCScaleTo::create(0.15, 1.0)),
                                                                          NULL));
            
            this->runAction(CCSequence::create(CCDelayTime::create(0.6 *2),
                                               CCCallFunc::create(this, callfunc_selector(E002_C010_P210::showFailText)),
                                               NULL));
        }
        
        
    }
    
}



void E002_C010_P210::showSuccessText()
{
    // blank remove
    CJSprite* questionBg = (CJSprite*)getChildByTag(_kTagQueBg);
    CJSprite* blank = (CJSprite*)questionBg->getChildByTag(_kTagQueBlank);
    blank->removeFromParent();
    
    CJSprite* head = (CJSprite*)_touchedExampleItem->sprite->getParent();
    head->removeFromParent();
    
    
    //기존 txt remove.
    _currentQuestionItem->txtSprite->runAction(CCFadeOut::create(0));
    if (m_nCurrentStageIndex < 4) {
        e->setOpacity(0);
    }
    
    //정답 txt sprite add.
    CJSprite* questionBack = (CJSprite*)questionBg->getChildByTag(_kTagQueBackBoard+_successCount);
    CJSprite* successTxt = createSprite(_currentQuestionItem->sucTxt);
    questionBack->addChild(successTxt,10);
    successTxt->setPositionForRootParent(this);
    successTxt->runAction(CCSequence::create(CCEaseSineOut::create(CCScaleTo::create(0.15, 1.2)),
                                             CCDelayTime::create(0.2),
                                             CCEaseSineOut::create(CCScaleTo::create(0.15, 1.0)),
                                             NULL));
    
    // bg 교체
    std::string bgTextureName = CJUtils::getStringFormatInteger("e002_c010_p210_img_success_bg_0%d.png",(m_nCurrentStageIndex/4));
    questionBack->changeTextureWithFullPath(bgTextureName);
    
    // 깜빡 깜빡
    CJSprite* questionBgHighlight = (CJSprite*)questionBg->getChildByTag(_kTagQueBgHighlight);
    questionBgHighlight->runAction(CCSequence::create(CCFadeIn::create(0),
                                                      CCDelayTime::create(0.2),
                                                      CCFadeOut::create(0),
                                                      CCDelayTime::create(0.2),
                                                      CCFadeIn::create(0),
                                                      CCDelayTime::create(0.2),
                                                      CCFadeOut::create(0),
                                                      CCDelayTime::create(0.2),
                                                      CCFadeIn::create(0),
                                                      CCDelayTime::create(0.2),
                                                      CCFadeOut::create(0),
                                                      CCDelayTime::create(0.2),
                                                      CCFadeIn::create(0),
                                                      NULL));
    
    
    float delay = CJMultimedia::getInstance()->getNarrationTime(getFilePath("snd",_currentQuestionItem->successSnd));
    if (m_nCurrentStageIndex < 4) {
        
        CJUtils::performSelector(this, callfuncND_selector(E002_C010_P210::onSuccesses), 0 , delay+0.2);
        
    }else{
        if ( _successCount >= 1) {
            CJUtils::performSelector(this, callfuncND_selector(E002_C010_P210::onSuccesses), 0 , 0.8);
        }else{
            CJUtils::performSelector(this, callfuncND_selector(E002_C010_P210::onHalfSuccess), 0 , 0.8);
        }
        _successCount++;
        
    }
    
    
    CCParticleSystemQuad* particle =  E002_C010_BaseUtil::addParticle("e002_c010_p210_smoke.plist");
    addChild(particle, kDepth5_particle);
    CCParticleSystemQuad* particle2 =  E002_C010_BaseUtil::addParticle("e002_c010_p210_star.plist");
    addChild(particle2, kDepth5_particle);
    
}


void E002_C010_P210::showFailText()
{
    
    _touchedExampleItem->playAction();
    _currentQuestionItem->txtSprite->runAction(CCSequence::create(CCEaseSineOut::create(CCScaleTo::create(0.15, 1.2)),
                                                                  CCDelayTime::create(0.2),
                                                                  CCEaseSineOut::create(CCScaleTo::create(0.15, 1.0)),
                                                                  NULL));
    CJUtils::performSelector(this, callfuncND_selector(E002_C010_P210::onFails), 0 , 0.8);
    
    
}


#pragma mark - feedback event

void E002_C010_P210::onExamplesTouched(int index)
{
    E002_Base_Question::onExamplesTouched(index);
}


void E002_C010_P210::onSuccesses(CCNode *node, int tag)
{
    CCLog("onSuccess");
    
    _successCount = 0;
    
    
    
    
    //    CJUtils::performSelector(this, callfunc_selector(E002_C010_P210::onSuccesses_callfunc),0.1);
    playCommonEffect("e002_common_sfx_correct_05.mp3");
    
    
    mSndManager->playCorrectNarrationAnison(E002_C010_SoundManager::p210);
    mAnison->showSuccess();
}

void E002_C010_P210::onSuccesses_callfunc()
{
    stick_l->removeFromParent();
    stick_r->removeFromParent();
    stick_l = NULL;
    stick_r = NULL;
    
    CJSprite* stick_head_l = (CJSprite*)getChildByTag(_kTagExmStick_head_l);
    CJSprite* stick_head_r = (CJSprite*)getChildByTag(_kTagExmStick_head_r);
    _safeRemoveFromParents(stick_head_l);
    _safeRemoveFromParents(stick_head_r);
    
    disappearAnimation();
    
    mSndManager->playCorrectNarrationOtherOne(E002_C010_SoundManager::p210);
    mBoomBoom->showSuccess();
    
    playEffectWithDelay("e002_c010_p210_sfx_jump_horse.mp3", 0.3);
}

void E002_C010_P210::onHalfSuccess(CCNode *node, int tag)
{
    //    stick_l->removeFromParent();
    //    stick_r->removeFromParent();
    
    CJSprite* stick_head_l = (CJSprite*)getChildByTag(_kTagExmStick_head_l);
    CJSprite* stick_head_r = (CJSprite*)getChildByTag(_kTagExmStick_head_r);
    _safeRemoveFromParents(stick_head_l);
    _safeRemoveFromParents(stick_head_r);
    
    
    CJSprite* questionBg = (CJSprite*)getChildByTag(_kTagQueBg);
    questionBg->runAction(CCSequence::create(CCJumpBy::create(0.4, CCPointZero, 0, 1),
                                             NULL));
    
    
    CJSprite* questionBack = (CJSprite*)questionBg->getChildByTag(_kTagQueBackBoard);
    CJSprite* questionBgHighlight = (CJSprite*)questionBg->getChildByTag(_kTagQueBgHighlight);
    questionBgHighlight->setOpacity(0);
    
    //    questionBg->reorderChild(questionBack, -1);
    //    questionBack->runAction(CCSpawn::create(CCScaleTo::create(0.2, 0.9),
    //                                            CCSequence::create(CCEaseSineOut::create(CCMoveBy::create(0.1, ccp(0, 10))),
    //                                                               CCEaseSineIn::create(CCMoveBy::create(0.2, ccp(0,-50))),
    //                                                               CCCallFunc::create(this, callfunc_selector(E002_C010_P210::showHalfQuestions)),
    //                                                               NULL),NULL));
    
    //    questionBack->setAnchorPointWithoutPosition(ccp(1, 0));
    questionBack->runAction(CCEaseOut::create( CCSpawn::create(CCRotateBy::create(1.0, 360 * 4),
                                                               CCJumpBy::create(1.0, ccp(712, 200), 250, 1),
                                                               CCSequence::create(CCDelayTime::create(1.0),
                                                                                  CCCallFunc::create(this, callfunc_selector(E002_C010_P210::showHalfQuestions)),
                                                                                  CCCallFunc::create(questionBack, callfunc_selector(CJSprite::removeFromParent)),
                                                                                  NULL),
                                                               NULL),2.0));
    
    playEffect("e002_c010_p000_sfx_06.mp3");
    
}



void E002_C010_P210::onFails(CCNode *node, int tag)
{
    CJLog("onFail");
    
    
    CJSprite*head =(CJSprite*)_touchedExampleItem->sprite->getParent();
    head->runAction(CCSequence::create(CCDelayTime::create(0.2),CCEaseElasticOut::create(CCMoveTo::create(0.4, head->m_secondPosition)),NULL));
    
    
    mSndManager->playWrongNarrationAnison(E002_C010_SoundManager::p210);
    mSndManager->playWrongNarrationOtherOne(E002_C010_SoundManager::p210);
    
    
    mAnison->showFails();
    mBoomBoom->showFails();
    
    playEffect("e002_c010_p210_sfx_wrong_horse.mp3");
    playCommonEffect("e002_common_sfx_wrong_01.mp3");
    
    
    //    m_touchingExampleSp->setVisible(true);
    //    m_touchingExampleSp->setPosition(_targetPoint);
    //    m_touchingExampleSp->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.2, m_touchingExampleSp->m_originPosition)));
}


void E002_C010_P210::flashFailFinishCallback(CJAnimation* pAnimation)
{
    setTouchEnableBaseLayer();
    
}

void E002_C010_P210::onComplete()
{
    E002_Base_Question::onComplete();
    if (m_nCurrentStageIndex < m_nMaxStageCount-1) {
        resetValue();
        m_nCurrentStageIndex++;
        setQuestions();
        setExamples();
        
        questionAppearStep1();
        exampleAppearStep1();
    }else{
        CJUtils::performSelector(this, callfunc_selector(E002_C010_P210::onEnd),3.0);
    }
    
}

void E002_C010_P210::onEnd()
{
     completeLetsPlay2();
    replaceSceneTransitionFadeOut(E002_C010_P230);
}

#pragma mark - user function
void E002_C010_P210::start()
{
    
    runSchedule();
    exampleAppearStep1();
    questionAppearStep1();
    playAnimationRun();
}



void E002_C010_P210::setQuestions()
{
    
    if (m_nCurrentStageIndex == 1) {
        E002_Base_Navigation::setVisibleButton(false, eNavigationButton_Prev);
    }else if(m_nCurrentStageIndex > 1){
        E002_Base_Navigation::setVisibleButton(true, eNavigationButton_Prev);
    }
    
    _oldCurrentStageIndex = m_nCurrentStageIndex;
    _currentQuestionItem = mQuestions[m_nCurrentStageIndex][_successCount];
    
    
    //qeustions
    CJSprite* questionBg = CJSprite::createWithFullPath("e002_c010_p210_img_que_bg_n.png");
    questionBg->setPosition(CJPsdParser::getPsdPosition("e002_c010_p210_img_que_bg_n", m_psdDictionary));
    addChild(questionBg, kDepth0_background-1, _kTagQueBg);
    
    CJSprite* questionBg_shadow = createSprite("e002_c010_p210_img_que_shadow");
    questionBg->addChildIgnoreParent(questionBg_shadow, -1, _kTagQueBgShadow);
    CJSprite* questionBgHighlight = createSprite("e002_c010_p210_img_que_bg_s");
    questionBgHighlight->setOpacity(0);
    questionBg->addChildIgnoreParent(questionBgHighlight, 0, _kTagQueBgHighlight);
    
    
    
    CJSprite* questionBack = createSprite(CJUtils::getStringFormatInteger("e002_c010_p210_img_que01_bg_0%d",(m_nCurrentStageIndex/4)));
    questionBg->addChildIgnoreParent(questionBack, kDepth2_questions+1, _kTagQueBackBoard);
    
    questionBg->setAnchorPointWithoutPosition(ccp(0.5,0));
    questionBg->m_originPosition = questionBg->getPosition();
    
    CCPoint firstPos = ccpSub(ccp(winCenter.x, TOP_LIMITE), ccp(0, QEUSTION_FIRST_DIST));
    questionBg->setPosition(firstPos);
    questionBg->setScale(0.0);
    questionBg->m_secondPosition = firstPos;
    
    
    _targetPoint = CJPsdParser::getPsdPosition(CJUtils::getStringFormatInteger("e002_c010_p210_img_blank_0%d",(m_nCurrentStageIndex/4)).c_str(),
                                               m_psdDictionary);
    
    
}

void E002_C010_P210::showQuestions()
{
    CJSprite* questionBg = (CJSprite*)getChildByTag(_kTagQueBg);
    CJSprite* questionBack = (CJSprite*)questionBg->getChildByTag(_kTagQueBackBoard);
    //    _setPositionOutParent(questionBack, this);
    
    
    
    CJLog("_currentQuestionItem[%d][%d]",m_nCurrentStageIndex, _successCount);
    
    CJSprite* questionImg = _currentQuestionItem->createImgSprite(m_psdDictionary);
    questionBg->addChild(questionImg, kDepth2_questions+1);
    questionImg->setPositionForRootParent(this);
    
    
    CJSprite* questionTxt = _currentQuestionItem->createTxtSprite(m_psdDictionary);
    CJLog("_currentQuestionItem->txt = %s",_currentQuestionItem->txt.c_str());
    CJLog("_currentQuestionItem->createTxtSprite = %p",_currentQuestionItem->txtSprite);
    CJLog("getParents = %p",questionTxt->getParent());
    questionBack->addChild(questionTxt, kDepth2_questions+1);
    questionTxt->setPositionForRootParent(this);
    
    
    
    CJSprite* blank = createSprite(CJUtils::getStringFormatInteger("e002_c010_p210_img_blank_0%d",(m_nCurrentStageIndex/4)));
    questionBg->addChildIgnoreParent(blank, 10,_kTagQueBlank);
    
    
    
    questionImg->setScale(0);
    questionTxt->setOpacity(0);
    
    questionImg->runAction(CCEaseBackOut::create(CCScaleTo::create(0.4, 1.0)));
    questionTxt->runAction(CCSpawn::create(CCFadeIn::create(0.2),
                                           CCJumpBy::create(0.4, CCPointZero, 5, 1),
                                           NULL));
    
    if (m_nCurrentStageIndex < 4) {
        e = createSprite(CJUtils::getStringMerge(_currentQuestionItem->txt,"_e"));
        questionBack->addChild(e, kDepth2_questions+1);
        e->setPositionForRootParent(this);
        e->runAction(CCSpawn::create(CCFadeIn::create(0.2),
                                     CCJumpBy::create(0.4, CCPointZero, 5, 1),
                                     NULL));
        
    }
    
    
    playNarration(_currentQuestionItem->snd);
}

void E002_C010_P210::showHalfQuestions()
{
    //remove old object
    _currentQuestionItem->imgSprite->runAction(CCSequence::create(CCFadeOut::create(0.2),
                                                                  CCCallFunc::create(_currentQuestionItem->imgSprite, callfunc_selector(CJSprite::removeFromParent)),
                                                                  NULL));
    
    
    //qeustions
    CJSprite* questionBg = (CJSprite*)getChildByTag(_kTagQueBg);
    CJSprite* questionBack = createSprite(CJUtils::getStringFormatInteger("e002_c010_p210_img_que01_bg_0%d",(m_nCurrentStageIndex/4)));
    questionBg->addChildIgnoreParent(questionBack, kDepth2_questions+1, _kTagQueBackBoard2);
    questionBg->setAnchorPointWithoutPosition(ccp(0.5,0));
    questionBg->m_originPosition = questionBg->getPosition();
    
    
    
    
    
    _currentQuestionItem = mQuestions[m_nCurrentStageIndex][_successCount];
    
    CJSprite* questionImg = _currentQuestionItem->createImgSprite(m_psdDictionary);
    questionBg->addChild(questionImg, kDepth2_questions+1);
    questionImg->setPositionForRootParent(this);
    
    
    CJSprite* questionTxt = _currentQuestionItem->createTxtSprite(m_psdDictionary);
    questionBack->addChild(questionTxt, kDepth2_questions+1);
    questionTxt->setPositionForRootParent(this);
    
    
    CJSprite* blank = createSprite(CJUtils::getStringFormatInteger("e002_c010_p210_img_blank_0%d",(m_nCurrentStageIndex/4)));
    questionBg->addChildIgnoreParent(blank, 10,_kTagQueBlank);
    
    
    
    questionImg->setScale(0);
    questionTxt->setOpacity(0);
    
    questionImg->runAction(CCEaseBackOut::create(CCScaleTo::create(0.4, 1.0)));
    questionTxt->runAction(CCSpawn::create(CCFadeIn::create(0.2),
                                           CCJumpBy::create(0.4, CCPointZero, 5, 1),
                                           NULL));
    playNarration(_currentQuestionItem->snd);
    
    
    //example
    
    CJSprite* stick_head_l = createSprite("e002_c010_p210_img_ans_bg_00_01");
    addChild(stick_head_l, kDepth2_questions, _kTagExmStick_head_l);
    stick_head_l->m_secondPosition = stick_head_l->getPosition();
    
    CJSprite* stick_head_r = createSprite("e002_c010_p210_img_ans_bg_01_01");
    addChild(stick_head_r, kDepth2_questions, _kTagExmStick_head_r);
    stick_head_r->m_secondPosition = stick_head_r->getPosition();
    
    
    int tempIndex = _successCount*2;
    CJSprite* txt_l = mExamples[m_nCurrentStageIndex][tempIndex]->createImgSprite(m_psdDictionary);
    stick_head_l->addChild(txt_l, kDepth2_questions+10);
    txt_l->setPosition(ccp(txt_l->getContentSize().width/2, txt_l->getContentSize().height/2));
    
    
    
    CJSprite* txt_r = mExamples[m_nCurrentStageIndex][tempIndex+1]->createImgSprite(m_psdDictionary);
    stick_head_r->addChild(txt_r, kDepth2_questions+100);
    txt_r->setPosition(ccp(txt_r->getContentSize().width/2, txt_r->getContentSize().height/2));
    
    
    txt_l->setScale(0);
    txt_r->setScale(0);
    
    
    txt_l->runAction(CCSequence::create(CCDelayTime::create(1.0),
                                        mExamples[m_nCurrentStageIndex][tempIndex]->playEffectCallfunc(),
                                        CCEaseBackOut::create(CCScaleTo::create(0.4, 1.0)),
                                        NULL));
    
    txt_r->runAction(CCSequence::create(CCDelayTime::create(2.0),
                                        mExamples[m_nCurrentStageIndex][tempIndex+1]->playEffectCallfunc(),
                                        CCEaseBackOut::create(CCScaleTo::create(0.4, 1.0)),
                                        CCCallFunc::create(this, callfunc_selector(E002_C010_P210::setTouchEnableBaseLayer)),
                                        NULL));
    
    
}

void E002_C010_P210::setExamples()
{
    
    //examples
    stick_l = createSprite("e002_c010_p210_img_ans_bg_00_00");
    addChild(stick_l, kDepth2_questions-1);
    CJSprite* stick_head_l = createSprite("e002_c010_p210_img_ans_bg_00_01");
    stick_l->addChildIgnoreParent(stick_head_l, kDepth2_questions-1, _kTagExmStick_head_l);
    CJSprite* stick_l_shadow = createSprite("e002_c010_p210_img_ans_shadow_00");
    stick_l->addChildIgnoreParent(stick_l_shadow, kDepth2_questions-2);
    
    stick_l->setAnchorPointWithoutPosition(ccp(0.5, 0));
    stick_l->m_originPosition = stick_l->getPosition();
    
    
    
    stick_r = createSprite("e002_c010_p210_img_ans_bg_01_00");
    addChild(stick_r, kDepth2_questions-1);
    CJSprite* stick_head_r = createSprite("e002_c010_p210_img_ans_bg_01_01");
    stick_r->addChildIgnoreParent(stick_head_r, kDepth2_questions-1, _kTagExmStick_head_r);
    CJSprite* stick_r_shadow = createSprite("e002_c010_p210_img_ans_shadow_01");
    stick_r->addChildIgnoreParent(stick_r_shadow, kDepth2_questions-2);
    
    stick_r->setAnchorPointWithoutPosition(ccp(0.5, 0));
    stick_r->m_originPosition = stick_r->getPosition();
    
    
    CCPoint firstPos_l = ccpSub(ccp(stick_l->m_originPosition.x, TOP_LIMITE), ccp(-10, QEUSTION_FIRST_DIST + 306));
    stick_l->setPosition(firstPos_l);
    stick_l->setScale(0.1);
    stick_l->m_secondPosition = firstPos_l;
    stick_l->setZOrder(kDepth0_background-1);
    
    CCPoint firstPos_r = ccpSub(ccp(stick_r->m_originPosition.x, TOP_LIMITE), ccp(10, QEUSTION_FIRST_DIST + 306));
    stick_r->setPosition(firstPos_r);
    stick_r->setScale(0.1);
    stick_r->m_secondPosition = firstPos_r;
    stick_r->setZOrder(kDepth0_background-1);
    
    
    
}

void E002_C010_P210::showExamples()
{
    //replace stick
    CJSprite* stick_head_l = (CJSprite*)stick_l->getChildByTag(_kTagExmStick_head_l);
    _setPositionOutParent(stick_head_l, this);
    stick_head_l->setZOrder(kDepth2_questions);
    stick_head_l->m_secondPosition = stick_head_l->getPosition();
    
    
    CJSprite* stick_head_r = (CJSprite*)stick_r->getChildByTag(_kTagExmStick_head_r);
    _setPositionOutParent(stick_head_r, this);
    stick_head_r->setZOrder(kDepth2_questions);
    stick_head_r->m_secondPosition = stick_head_r->getPosition();
    
    
    
    int tempIndex = _successCount*2;
    CJSprite* txt_l = mExamples[m_nCurrentStageIndex][tempIndex]->createImgSprite(m_psdDictionary);
    stick_head_l->addChild(txt_l, kDepth2_questions+10);
    txt_l->setPosition(ccp(txt_l->getContentSize().width/2, txt_l->getContentSize().height/2));
    
    
    
    CJSprite* txt_r = mExamples[m_nCurrentStageIndex][tempIndex+1]->createImgSprite(m_psdDictionary);
    stick_head_r->addChild(txt_r, kDepth2_questions+100);
    txt_r->setPosition(ccp(txt_r->getContentSize().width/2, txt_r->getContentSize().height/2));
    
    
    txt_l->setScale(0);
    txt_r->setScale(0);
    
    
    txt_l->runAction(CCSequence::create(CCDelayTime::create(1.0),
                                        mExamples[m_nCurrentStageIndex][tempIndex]->playEffectCallfunc(),
                                        CCEaseBackOut::create(CCScaleTo::create(0.4, 1.0)),
                                        NULL));
    
    txt_r->runAction(CCSequence::create(CCDelayTime::create(2.0),
                                        mExamples[m_nCurrentStageIndex][tempIndex+1]->playEffectCallfunc(),
                                        CCEaseBackOut::create(CCScaleTo::create(0.4, 1.0)),
                                        CCCallFunc::create(this, callfunc_selector(E002_C010_P210::setTouchEnableBaseLayer)),
                                        NULL));
    
    
    
    if (m_nCurrentStageIndex < 4) {
        e->setAnchorPointWithoutPosition(ccp(0, 0.5));
        
        e->runAction(CCSequence::create(CCDelayTime::create(1.0),
                                        CCEaseSineOut::create(CCScaleTo::create(0.15, 1.2)),
                                        CCDelayTime::create(0.2),
                                        CCEaseSineOut::create(CCScaleTo::create(0.15, 1.0)),
                                        NULL));
        
        e->runAction(CCSequence::create(CCDelayTime::create(2.0),
                                        CCEaseSineOut::create(CCScaleTo::create(0.15, 1.2)),
                                        CCDelayTime::create(0.2),
                                        CCEaseSineOut::create(CCScaleTo::create(0.15, 1.0)),
                                        NULL));
    }
    
    
    if (m_bIsGuide)
    {
        this->runAction(CCSequence::create(CCDelayTime::create(2.5),
                                           CCCallFuncND::create(this, callfuncND_selector(E002_C010_P210::showHand), (void*)0),
                                           NULL));
        return;
    }
}



void E002_C010_P210::showGuideQuestions()
{
    CJSprite* questionBg = (CJSprite*)getChildByTag(_kTagQueBg);
    questionBg->setScale(1.0);
    questionBg->setPosition(questionBg->m_originPosition);
    reorderChild(questionBg, kDepth2_questions);
    
    stick_l->setScale(1.0);
    stick_l->setPosition(stick_l->m_originPosition);
    stick_l->setZOrder(kDepth2_questions-1);
    
    stick_r->setScale(1.0);
    stick_r->setPosition(stick_r->m_originPosition);
    stick_r->setZOrder(kDepth2_questions-1);
    
    CJUtils::performSelector(this, callfunc_selector(E002_C010_P210::showQuestions), 0.5);
    CJUtils::performSelector(this, callfunc_selector(E002_C010_P210::showExamples), 0.7);
    
    mAnison->showLooping();
    mBoomBoom->showLooping();
    
}


void E002_C010_P210::resetValue()
{
    
    //remove question
    
    
    //remove question bg
    CJSprite* questionBg = (CJSprite*)getChildByTag(_kTagQueBg);
    questionBg->stopAllActions();
    CJUtils::removeAllchildren(questionBg);
    questionBg->removeFromParent();
    
    mQuestions[_oldCurrentStageIndex][_successCount]->imgSprite = NULL;
    mQuestions[_oldCurrentStageIndex][_successCount]->txtSprite = NULL;
    
    
    //    if (mQuestions[m_nCurrentStageIndex][_successCount]->imgSprite) {
    //        _safeRemoveFromParents(mQuestions[m_nCurrentStageIndex][_successCount]->imgSprite);
    //    }
    
    //    if (mQuestions[m_nCurrentStageIndex][_successCount]->txtSprite) {
    //        _safeRemoveFromParents(mQuestions[m_nCurrentStageIndex][_successCount]->txtSprite);
    //    }
    
    
    
    //remove examples
    if(stick_l)
    {
        stick_l->stopAllActions();
        stick_l->removeFromParent();
        stick_l = NULL;
    }
    if (stick_r) {
        stick_r->stopAllActions();
        stick_r->removeFromParent();
        stick_r = NULL;
    }
    
    CJSprite* stick_head_l = (CJSprite*)getChildByTag(_kTagExmStick_head_l);
    CJSprite* stick_head_r = (CJSprite*)getChildByTag(_kTagExmStick_head_r);
    _safeRemoveFromParents(stick_head_l);
    _safeRemoveFromParents(stick_head_r);
    
    _successCount = 0;
    setTouchDisalbeBaseLayer();
    
    
    
}

void E002_C010_P210::setNextQuestions()
{
    unschedule(schedule_selector(E002_C010_P210::sideObjectScheduler));
    
    stopAllActions();
    resetValue();
    stopAllNarration();
    setQuestions();
    setExamples();
    
    
    //flash
    mAnison->showLooping();
    mBoomBoom->showLooping();
    
    //question
    CJSprite* questionBg = (CJSprite*)getChildByTag(_kTagQueBg);
    questionBg->setScale(1.0);
    questionBg->setPosition(questionBg->m_originPosition);
    reorderChild(questionBg, kDepth2_questions);
    
    
    //example
    stick_l->setScale(1.0);
    stick_l->setPosition(stick_l->m_originPosition);
    stick_l->setZOrder(kDepth2_questions-1);
    
    stick_r->setScale(1.0);
    stick_r->setPosition(stick_r->m_originPosition);
    stick_r->setZOrder(kDepth2_questions-1);
    
    showQuestions();
    CJUtils::performSelector(this, callfunc_selector(E002_C010_P210::showExamples), 0.5);
    
    
    //stop Sequence
    stopSchedule();
    
    CJSprite* butte_l = (CJSprite*)getChildByTag(_kTagButte_left);
    CJSprite* butte_r = (CJSprite*)getChildByTag(_kTagButte_right);
    
    float value = (1.2f / 7.0f) * (float)m_nCurrentStageIndex;
    butte_l->setScale(0.6 + value);
    butte_r->setScale(0.6 + value);
    
    
}

#pragma mark - sound & narration
void E002_C010_P210::playQuestionSound(CCNode* node, void* index)
{
}

void E002_C010_P210::playAppearanceExamplesSound(CCNode* sender, void* index)
{
}


#pragma mark - user function

void E002_C010_P210::speakNarration(CCNode *node, std::string fileName)
{
    stopAllNarration();
    playNarration(fileName);
}



void E002_C010_P210::OnLastFrame(CJAnimation* pAnimation)
{
    //    E002_Base_Question::OnLastFrame(pAnimation);
    
    if (pAnimation->getName() == FLASH_NAME_BOOM_ACTION0 || pAnimation->getName() == FLASH_NAME_BOOM_ACTION1) {
        checkAnswer(_touchedExampleItem);
        mAnison->showLooping();
        mBoomBoom->showLooping();
    }
    
    
    //fail
    if (pAnimation->getName() == "e002_c010_p210_flash_bb_f01_action") {
        mBoomBoom->showLooping();
        flashFailFinishCallback(pAnimation);
    }
    if (pAnimation->getName() == "e001_c010_p210_flash_as_f01_action") {
        mAnison->showLooping();
    }
    
    
    //success
    if (pAnimation->getName() == "e002_c010_p210_flash_as_s01_action") {
        removeAllAnimationsInDataPool(FLASH_ANISON);
        playAnimation(FLASH_ANISON, FLASH_NAME_ANISON_RUN, -1, kDepth0_backImage);
        onSuccesses_callfunc();
    }
    if (pAnimation->getName() == "e002_c010_p210_flash_bb_s01_action") {
        playAnimationRun();
        
    }
    
}

#pragma mark - sprite create


void E002_C010_P210::showSuccessCharacterMotion(CCNode *node, int index)
{
    
}

void E002_C010_P210::showWrongCharacterMotion(CCNode *node, int index)
{
}



void E002_C010_P210::makeSideObjects()
{
    float distance_l = 0;
    float distance_r = 0;
    float x_gab = 40;
    
    for (int i = 0; i <= 5; i++) {
        
        //left =====================================================================
        
        std::string str_l = CJUtils::getStringFormatInteger("e002_c010_p210_img_object_l_0%d.png", i);
        MoveObject* object_l = MoveObject::createWithFullPath(str_l.c_str());
        object_l->setAnchorPoint(ccp(0.5,0));
        _arrSideObjects_l->addObject(object_l);
        
        std::string str_shadow_l = CJUtils::getStringFormatInteger("e002_c010_p210_img_object_l_shadow_0%d.png", i);
        CJSprite *shadow_l = CJSprite::createWithFullPath(str_shadow_l.c_str());
        object_l->addChild(shadow_l, -1, _kTagObjShadow);
        shadow_l->setPosition(ccp( object_l->getContentSize().width/2,0));
        object_l->shadow = shadow_l;
        object_l->zorder = 5-i;
        
        {
            
            float angle = SIDE_ANGLE;
            distance_l = distance_l + (210.0 - (20*(i*SIDE_DISTANCE_FACTOR)));
            CJLog("distance %d = %.2f ",i, distance_l);
            
            float xx = cosf(angle) * distance_l;
            float yy = -sinf(angle) * distance_l;
            
            object_l->setPosition(ccp(xx - x_gab, yy));
            addChild(object_l, kDepth0_backImage + object_l->zorder);
            
            
            if (object_l->getPositionY() > TOP_LIMITE)
            {
                object_l->bIsUpVec = true;
                object_l->setPosition(ccp(object_l->getPositionX(), TOP_LIMITE - (object_l->getPositionY() - TOP_LIMITE)));
                reorderChild(object_l, kDepth0_background - 1);
            }
        }
        
        
        
        //right =====================================================================
        std::string str_r = CJUtils::getStringFormatInteger("e002_c010_p210_img_object_r_0%d.png", i);
        MoveObject* object_r = MoveObject::createWithFullPath(str_r.c_str());
        object_r->setAnchorPoint(ccp(0.5,0));
        _arrSideObjects_r->addObject(object_r);
        
        std::string str_shadow_r = CJUtils::getStringFormatInteger("e002_c010_p210_img_object_r_shadow_0%d.png", i);
        CJSprite *shadow_r = CJSprite::createWithFullPath(str_shadow_r.c_str());
        object_r->addChild(shadow_r, -1, _kTagObjShadow);
        shadow_r->setPosition(ccp( object_r->getContentSize().width/2,0));
        object_r->shadow = shadow_r;
        object_r->zorder = 5-i;
        
        {
            float angle = -SIDE_ANGLE;
            distance_r = distance_r + (210.0 - (20*(i*SIDE_DISTANCE_FACTOR)));
            
            float xx = cosf(angle) * distance_r;
            float yy = sinf(angle) * distance_r;
            
            object_r->setPosition(ccp((winSize.width + x_gab) - xx, yy));
            addChild(object_r, kDepth0_backImage + object_l->zorder);
            
            if (object_r->getPositionY() > TOP_LIMITE)
            {
                object_r->bIsUpVec = true;
                object_r->setPosition(ccp(object_r->getPositionX(), TOP_LIMITE - (object_r->getPositionY() - TOP_LIMITE)));
                reorderChild(object_r, kDepth0_background-1);
            }
        }
        
        if (i == 5)
        {
            _lastPosition_l = object_l->getPosition();
            _lastPosition_r = object_r->getPosition();
        }
    }
}


void E002_C010_P210::runSchedule()
{
    schedule(schedule_selector(E002_C010_P210::sideObjectScheduler), 1/60.f);
    
    
    CJSprite* bg = (CJSprite*)getChildByTag(_kTagBg);
    bg->runAction(CJUtils::getSeqAction(-1,
                                        0.2,
                                        getImageFilePath("e002_c010_p210_bg_01.png").c_str(),
                                        getImageFilePath("e002_c010_p210_bg_02.png").c_str(),
                                        NULL));
    
    
    CJSprite* leftBar = (CJSprite*)getChildByTag(_kTagBar_left);
    CJSprite* rightBar = (CJSprite*)getChildByTag(_kTagBar_right);
    
    
    leftBar->runAction(CJUtils::getSeqAction(-1,
                                             0.2,
                                             getImageFilePath("e002_c010_p210_img_fence_l_00.png").c_str(),
                                             getImageFilePath("e002_c010_p210_img_fence_l_01.png").c_str(),
                                             NULL));
    
    rightBar->runAction(CJUtils::getSeqAction(-1,
                                              0.2,
                                              getImageFilePath("e002_c010_p210_img_fence_r_00.png").c_str(),
                                              getImageFilePath("e002_c010_p210_img_fence_r_01.png").c_str(),
                                              NULL));
    
    
    
    
    
    
    CJSprite* butte_l = (CJSprite*)getChildByTag(_kTagButte_left);
    butte_l->stopAllActions();
    butte_l->runAction(CCRepeatForever::create(CCSequence::create(
                                                                  CCEaseOut::create(CCMoveTo::create(0.3, ccpAdd(butte_l->m_originPosition, ccp(0,7))),1.5),
                                                                  CCEaseIn::create(CCMoveTo::create(0.3, butte_l->m_originPosition),1.5),
                                                                  NULL)));
    
    CJSprite* butte_r = (CJSprite*)getChildByTag(_kTagButte_right);
    butte_r->stopAllActions();
    butte_r->runAction(CCRepeatForever::create(CCSequence::create(
                                                                  CCEaseOut::create(CCMoveTo::create(0.3, ccpAdd(butte_r->m_originPosition, ccp(0,7))),1.5),
                                                                  CCEaseIn::create(CCMoveTo::create(0.3, butte_r->m_originPosition),1.5),
                                                                  NULL)));
    
    float value = (1.2f / 7.0f) * (float)m_nCurrentStageIndex;
    CJLog("value = %f",value);
    butte_l->runAction(CCScaleTo::create(4.5, 0.6 + value));
    butte_r->runAction(CCScaleTo::create(4.5, 0.6 + value));
}


void E002_C010_P210::stopSchedule(){
    unschedule(schedule_selector(E002_C010_P210::sideObjectScheduler));
    
    CJSprite* bg = (CJSprite*)getChildByTag(_kTagBg);
    bg->stopAllActions();
    
    CJSprite* leftBar = (CJSprite*)getChildByTag(_kTagBar_left);
    CJSprite* rightBar = (CJSprite*)getChildByTag(_kTagBar_right);
    leftBar->stopAllActions();
    rightBar->stopAllActions();
    
    CJSprite* butte_l = (CJSprite*)getChildByTag(_kTagButte_left);
    CJSprite* butte_r = (CJSprite*)getChildByTag(_kTagButte_right);
    butte_l->stopAllActions();
    butte_r->stopAllActions();
}

#pragma mark - scheduler
void E002_C010_P210::sideObjectScheduler()
{
    
    float speedFactor = 15;
    
    for (int i = 0; i < _arrSideObjects_l->count(); i++) {
        MoveObject* object_l = (MoveObject*)_arrSideObjects_l->objectAtIndex(i);
        
        
        // 가속도
        float speed = speedFactor - (object_l->getPositionX() * speedFactor / _lastPosition_l.x ) + SIDE_SPEED; /* 0 ~ temp */
        
        //방향 설정
        if ((int)object_l->getPositionX() < LEFT_LIMITE )
        {
            if (object_l->bIsUpVec == true) {
                object_l->bIsUpVec = false;
                reorderChild(object_l, kDepth0_backImage + object_l->zorder);
                
            }
            object_l->pVec = getVectorLeftDown(speed);
            
        }else{
            object_l->pVec = getVectorLeftUp(speed);
            
        }
        
        
        
        
        
        
        if (object_l->getPositionY() < -220) {
            object_l->setScale(0.5);
            object_l->setPosition(_lastPosition_l);
            object_l->bIsUpVec = true;
            object_l->pVec = getVectorLeftUp(speed);
            reorderChild(object_l, kDepth0_background-1);
        }
        
        object_l->setPosition(ccpAdd(object_l->getPosition(), object_l->pVec));
        float fScale = (object_l->getPositionX() / 190) * 0.7;
        object_l->setScale(1.5 - fScale);
    }
    
    
    
    
    for (int i = 0; i < _arrSideObjects_r->count(); i++)
    {
        MoveObject* object_r = (MoveObject*)_arrSideObjects_r->objectAtIndex(i);
        
        
        // 가속도
        float speed = ((object_r->getPositionX()-_lastPosition_r.x) * speedFactor / (winSize.width - _lastPosition_r.x) ) + SIDE_SPEED; /* 0 ~ 50 */
        
        
        
        if ((int)object_r->getPositionX() > RIGHT_LIMITE )
        {
            if (object_r->bIsUpVec == true) {
                object_r->bIsUpVec = false;
                reorderChild(object_r, kDepth0_backImage + object_r->zorder);
            }
            object_r->pVec = getVectorRightDown(speed);
            
        }else{
            object_r->pVec = getVectorRightUp(speed);
        }
        
        
        if (object_r->getPositionY() < -220) {
            object_r->setScale(0.5);
            object_r->setPosition(_lastPosition_r);
            object_r->bIsUpVec = true;
            object_r->pVec = getVectorRightUp(speed);
            reorderChild(object_r, kDepth0_background-1);
        }
        
        
        object_r->setPosition(ccpAdd(object_r->getPosition(), object_r->pVec));
        float fScale = ((winSize.width - object_r->getPositionX()) / 190) * 0.7;
        object_r->setScale(1.5 - fScale);
    }
}


void E002_C010_P210::questionAppearStep1()
{
    CJSprite* questionBg = (CJSprite*)getChildByTag(_kTagQueBg);
    questionBg->setScale(0.1);
    questionBg->setPosition(questionBg->m_secondPosition);
    reorderChild(questionBg, kDepth0_background-1);
    
    
    questionBg->runAction( CCSequence::create(CCEaseOut::create(CCSpawn::create(CCMoveTo::create(1.5, ccp(winCenter.x, TOP_LIMITE)),
                                                                                CCScaleTo::create(1.5, 0.5),
                                                                                NULL),1.0),
                                              
                                              CCCallFunc::create(this, callfunc_selector(E002_C010_P210::questionAppearStep2)),
                                              
                                              CCEaseIn::create(CCSpawn::create(CCMoveTo::create(1.5, questionBg->m_originPosition),
                                                                               CCScaleTo::create(1.5, 1.0),
                                                                               NULL),1.0),
                                              NULL));
    
    
}


void E002_C010_P210::questionAppearStep2()
{
    CJSprite* questionBg = (CJSprite*)getChildByTag(_kTagQueBg);
    reorderChild(questionBg, kDepth2_questions);
    //    reord kDepth2_questions
}


void E002_C010_P210::exampleAppearStep1()
{
    
    stick_l->setScale(0.1);
    stick_l->setPosition(stick_l->m_secondPosition);
    stick_l->setZOrder(kDepth0_background-1);
    
    
    
    stick_l->runAction(CCSequence::create(CCEaseOut::create(CCSpawn::create(CCMoveTo::create(2.7, ccp(stick_l->m_secondPosition.x+2, TOP_LIMITE)),
                                                                            CCScaleTo::create(2.7, 0.8),
                                                                            NULL),1.0),
                                          
                                          CCCallFuncN::create(this, callfuncN_selector(E002_C010_P210::exampleAppearStep2)),
                                          
                                          CCEaseIn::create(CCSpawn::create(CCMoveTo::create(0.3, stick_l->m_originPosition),
                                                                           CCScaleTo::create(0.3, 1.0),
                                                                           NULL),1.0),
                                          CCCallFunc::create(this, callfunc_selector(E002_C010_P210::exampleAppearEnd)),
                                          NULL));
    
    
    
    stick_r->setScale(0.1);
    stick_r->setPosition(stick_r->m_secondPosition);
    stick_r->setZOrder(kDepth0_background-1);
    
    
    
    stick_r->runAction(CCSequence::create(CCEaseOut::create(CCSpawn::create(CCMoveTo::create(2.7, ccp(stick_r->m_secondPosition.x-2, TOP_LIMITE)),
                                                                            CCScaleTo::create(2.7, 0.8),
                                                                            NULL),1.0),
                                          
                                          CCCallFuncN::create(this, callfuncN_selector(E002_C010_P210::exampleAppearStep2)),
                                          
                                          CCEaseIn::create(CCSpawn::create(CCMoveTo::create(0.3, stick_r->m_originPosition),
                                                                           CCScaleTo::create(0.3, 1.0),
                                                                           NULL),1.0),
                                          NULL));
    
}

void E002_C010_P210::exampleAppearStep2(CCNode* sender)
{
    CJSprite* stick = (CJSprite*)sender;
    stick->setZOrder(kDepth2_questions-1);
}

void E002_C010_P210::exampleAppearEnd()
{
    stopSchedule();
    CJUtils::performSelector(this, callfunc_selector(E002_C010_P210::showQuestions), 0.5);
    CJUtils::performSelector(this, callfunc_selector(E002_C010_P210::showExamples), 0.7);
    
    mAnison->showLooping();
    mBoomBoom->showLooping();
    stopAllNarration();
}

void E002_C010_P210::disappearAnimation()
{
    runSchedule();
    //remove question
    CJSprite* questionBg = (CJSprite*)getChildByTag(_kTagQueBg);
    
    if (m_bIsGuide) {
        questionBg->runAction(CCSequence::create(CCEaseOut::create(CCSpawn::create(CCMoveTo::create(1.5, ccp(winCenter.x, -400)),
                                                                                   CCScaleTo::create(1.5, 1.5),
                                                                                   NULL),1.0),
                                                 CCCallFunc::create(((E002_Base_Question*)getParent()), callfunc_selector(E002_C010_P210::removeGuide)),
                                                 NULL));
        
        
    }else{
        questionBg->runAction(CCSequence::create(CCEaseOut::create(CCSpawn::create(CCMoveTo::create(1.5, ccp(winCenter.x, -400)),
                                                                                   CCScaleTo::create(1.5, 1.5),
                                                                                   NULL),1.0),
                                                 CCCallFunc::create(this, callfunc_selector(E002_C010_P210::onComplete)),
                                                 NULL));
        CJUtils::performSelector(this, callfunc_selector(E002_C010_P210::showReward),1.0);
        
    }
    
}


void E002_C010_P210::showReward()
{
    showLetPlay2RewardItem(NULL, m_nCurrentStageIndex-1);
}


#pragma mark - flash animation
void E002_C010_P210::playAnimationRun()
{
    removeAllAnimations();
    playAnimation(FLASH_ANISON, FLASH_NAME_ANISON_RUN, -1, kDepth0_backImage);
    playAnimation(FLASH_BOOM, FLASH_NAME_BOOM_RUN2, -1, kDepth4_title);
    
    playNarration("e002_c010_p210_sfx_horse_slow_run.mp3", true);
}

void E002_C010_P210::stopSpeakingAndLooping()
{
    stopAllNarration();
    if (getAnimationByName(FLASH_ANISON, FLASH_NAME_ANISON_TALK)->isPlay()) {
        removeAllAnimationsInDataPool(FLASH_ANISON);
        mAnison->showLooping();
    }
    
}

#pragma mark - this util

CCPoint E002_C010_P210::getVectorLeftDown(float speed)
{
    CCPoint pt = ccp(-cos(SIDE_ANGLE  * M_PI/180.0) * speed, -sin(SIDE_ANGLE  * M_PI/180.0) * speed);
    return pt;
}

CCPoint E002_C010_P210::getVectorLeftUp(float speed)
{
    CCPoint pt = ccp(getVectorLeftDown(speed).x, -1 * getVectorLeftDown(speed).y);
    return pt;
}
CCPoint E002_C010_P210::getVectorRightDown(float speed)
{
    CCPoint pt = ccp(cos(-SIDE_ANGLE  * M_PI/180.0) * speed, sin(-SIDE_ANGLE  * M_PI/180.0) * speed);
    return pt;
    
}
CCPoint E002_C010_P210::getVectorRightUp(float speed)
{
    CCPoint pt = ccp(getVectorRightDown(speed).x, -1 * getVectorRightDown(speed).y);
    return pt;
    
}


#pragma mark - Guide

void E002_C010_P210::showGuide()
{
    E002_Base_Question::showGuide();
    
    m_Guide = E002_C010_P210::create();
    m_Guide->init();
    m_Guide->setGuide(true);
    addChild(m_Guide, kDepth10_guide);
    
    std::vector<CCPoint> *guideHandPosition = new std::vector<CCPoint>();
    
    guideHandPosition->push_back(ccpAdd(CJPsdParser::getPsdPosition("e002_c010_p210_img_ans_bg_00_01", m_psdDictionary), ccp(60, -60)));
    guideHandPosition->push_back(ccpAdd(_targetPoint, ccp(60, -60)));
    
    
    m_Guide->setGuideHandPosition(guideHandPosition);
}


void E002_C010_P210::removeGuide()
{
    removeChild(m_Guide);
    E002_Base_Question::removeGuide();
    
}

void E002_C010_P210::completeToMoveHand(CCNode *node, int index)
{
    switch (index) {
        case 0:
            onTouchBegan(ccpAdd(node->getPosition(),ccp(-60, 60)));
            break;
        case 1:
            onTouchEnded(ccpAdd(node->getPosition(),ccp(-60, 60)));
            //            onTouchBegan(node->getPosition());
            //            showHand(NULL, 2);
            break;
        default:
            break;
    }
}

void E002_C010_P210::completeFirstGuide()
{
    start();
    setTouchDisalbeBaseLayer();
}

#pragma mark - navigation delegate

void E002_C010_P210::onTouchedNavigationButtonAtIndex()
{
    E002_Base_Question::onTouchedNavigationButtonAtIndex();
    
    E002_C010_P000_Index* _indexClass = E002_C010_P000_Index::create();
    _indexClass->setIndexDelegate(this);
    _indexClass->showIndex(this, _indexClass);
    addChild(_indexClass, kDepth11_Index);
}

void E002_C010_P210::onTouchedNavigationButtonAtInfo()
{
    E002_Base_Question::onTouchedNavigationButtonAtInfo();
    showGuide();
}

void E002_C010_P210::onTouchedNavigationButtonAtPrev()
{
    E002_Base_Question::onTouchedNavigationButtonAtPrev();
    if (m_nCurrentStageIndex > 1) {
        m_nCurrentStageIndex--;
        setNextQuestions();
    }else{
        CJLog("m_nCurrentStageIndex = 0");
    }
}

void E002_C010_P210::onTouchedNavigationButtonAtNext()
{
    E002_Base_Question::onTouchedNavigationButtonAtNext();
    
    if (m_nCurrentStageIndex < m_nMaxStageCount-1)
    {
        m_nCurrentStageIndex++;
        setNextQuestions();
    }
    else
    {
        //If you complete "Let's play1", call this function.
        onEnd();
    }
    
}

void E002_C010_P210::onTouchedNavigationButtonAtReward()
{
    showLetPlay2RewardPopup(NULL, m_nCurrentStageIndex - 1);
}

#pragma mark - my util
CJSprite* E002_C010_P210::createSprite(std::string pStr)
{
    return CJPsdParser::getPsdSprite(pStr, m_psdDictionary);
}


void E002_C010_P210::_setPositionOutParent(CCNode* child, CCNode* newParent)
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

void E002_C010_P210::_safeRemoveFromParents(CCNode* pChild)
{
    if (pChild && (CJSprite*)pChild->getParent()) {
        pChild->removeFromParent();
    }
}
