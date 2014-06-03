

#include "E002_C030_P210.h"
#include "E002_C030_P000_Index.h"
#include "E002_C030_P230.h"
//#include "E002_C030_P210_Guide.h"

#define GET_EXAMPLES mExamples->at(m_nCurrentStageIndex)
#define GET_SELECTED_ITEM mExamples->at(m_nCurrentStageIndex)->at(mExampleSelectIndex)

enum
{
    kTagWall = 200,
    
    kTagExample001 = 250,
    kTagExample002,
    kTagExample003,
    
    kTagSuccess000,
    kTagSuccess001,
    kTagSuccess002,
    kTagSuccess003,
    
    kTagCouple000,
    kTagCouple001,
    
    kTagQuestion,
    
    kTagLeftFireBottom,
    kTagRightFireBottom,
    kTagLeftFireTop,
    kTagRightFireTop,
    
    kTagLeftFire,
    kTagRightFire,
    
    kTagLeftFireBlur,
    kTagRightFireBlur,
    
    kTagPharaoh,
    kTagLight,
    kTagLight2,

    
};

E002_C030_P210::E002_C030_P210()
{
    mExamples = new std::vector<std::vector<E002_Base_ExampleItem*>*>();
    mQuestions = new std::vector<std::vector<std::string>*>();
    mQuestionSounds = new std::vector<std::vector<std::string>*>();
    
    m_touchingExampleSp = NULL;
    mExampleSelectIndex = 0;
    
    mSndManager = new E002_C030_SoundManager();
}

E002_C030_P210::~E002_C030_P210()
{
//    for (int i=0; i < mExamples->size(); i++)
//    {
//        for (int j = 0; mExamples->at(i)->size(); j++)
//        {
//            delete mExamples->at(i)->at(j);
//        }
//    }
    
    CC_SAFE_DELETE(mExamples);
}

#pragma mark - init

bool E002_C030_P210::init()
{
    if (!E002_Base_Question::init()) {
        return false;
    }
    
    m_nMaxStageCount = 8;
    m_nCurrentStageIndex = 1;
    mSelectedCount = 0;
    mSuccessCount = 0;
    mPlayingGuideNarration = false;
    
    return true;
}

void E002_C030_P210::onEnter()
{
    E002_Base_Question::onEnter();
    
    const char* exampleImgName[8][3] =
    {
        {
            "e002_c030_p210_a00_00",
            "e002_c030_p210_a00_01",
            "e002_c030_p210_a00_02"
        },
        {
            "e002_c030_p210_a01_00",
            "e002_c030_p210_a01_01",
            "e002_c030_p210_a01_02"
        },
        {
            "e002_c030_p210_a02_00",
            "e002_c030_p210_a02_01",
            "e002_c030_p210_a02_02"
        },
        {
            "e002_c030_p210_a03_00",
            "e002_c030_p210_a03_01",
            "e002_c030_p210_a03_02",
        },
        {
            "e002_c030_p210_a04_00",
            "e002_c030_p210_a04_01",
            "e002_c030_p210_a04_02",
        },
        {
            "e002_c030_p210_a05_00",
            "e002_c030_p210_a05_01",
            "e002_c030_p210_a05_02",
        },
        {
            "e002_c030_p210_a06_00",
            "e002_c030_p210_a06_01",
            "e002_c030_p210_a06_02",
        },
        {
            "e002_c030_p210_a07_00",
            "e002_c030_p210_a07_01",
            "e002_c030_p210_a07_02",
        },
    };
    
    const char* questionsImgName[8][5] =
    {
        {
            "e002_c030_p210_q00",
            "e002_c030_p210_q00_success_img",
            "e002_c030_p210_q00_success_01",
            "e002_c030_p210_q00_success_02",
            "e002_c030_p210_q00_success_03",
        },
        {
            "e002_c030_p210_q01",
            "e002_c030_p210_q01_success_img",
            "e002_c030_p210_q01_success_01",
            "e002_c030_p210_q01_success_02",
            "e002_c030_p210_q01_success_03",
        },
        {
            "e002_c030_p210_q02",
            "e002_c030_p210_q02_success_img",
            "e002_c030_p210_q02_success_01",
            "e002_c030_p210_q02_success_02",
            "e002_c030_p210_q02_success_03",
        },
        {
            "e002_c030_p210_q03",
            "e002_c030_p210_q03_success_img",
            "e002_c030_p210_q03_success_01",
            "e002_c030_p210_q03_success_02",
            "e002_c030_p210_q03_success_03",
        },
        {
            "e002_c030_p210_q04",
            "e002_c030_p210_q04_success_img",
            "e002_c030_p210_q04_success_01",
            "e002_c030_p210_q04_success_02",
            "e002_c030_p210_q04_success_03",
        },
        {
            "e002_c030_p210_q05",
            "e002_c030_p210_q05_success_img",
            "e002_c030_p210_q05_success_01",
            "e002_c030_p210_q05_success_02",
            "e002_c030_p210_q05_success_03",
        },
        {
            "e002_c030_p210_q06",
            "e002_c030_p210_q06_success_img",
            "e002_c030_p210_q06_success_01",
            "e002_c030_p210_q06_success_02",
            "e002_c030_p210_q06_success_03",
        },
        {
            "e002_c030_p210_q07",
            "e002_c030_p210_q07_success_img",
            "e002_c030_p210_q07_success_01",
            "e002_c030_p210_q07_success_02",
            "e002_c030_p210_q07_success_03",
        }
    };
    
    const char* exampleSndName[8][3] =
    {
        {
            "e002_c030_p000_snd_clam_n.mp3",
            "e002_c030_p000_snd_flag_n.mp3",
            "e002_c030_p000_snd_plant_n.mp3",
        },
        {
            "e002_c030_p000_snd_blue_n.mp3",
            "e002_c030_p000_snd_gloves_n.mp3",
            "e002_c030_p000_snd_clock_n.mp3",
        },
        {
            "e002_c030_p000_snd_flute_n.mp3",
            "e002_c030_p000_snd_glass_n.mp3",
            "e002_c030_p000_snd_sled_n.mp3",
        },
        {
            "e002_c030_p000_snd_clap_n.mp3",
            "e002_c030_p000_snd_black_n.mp3",
            "e002_c030_p000_snd_slide_n.mp3",
        },
        {
            "e002_c030_p000_snd_fl_n.mp3",
            "e002_c030_p000_snd_cl_n.mp3",
            "e002_c030_p000_snd_bl_n.mp3",
        },
        {
            "e002_c030_p000_snd_sl_n.mp3",
            "e002_c030_p000_snd_pl_n.mp3",
            "e002_c030_p000_snd_cl_n.mp3",
        },
        {
            "e002_c030_p000_snd_bl_n.mp3",
            "e002_c030_p000_snd_gl_n.mp3",
            "e002_c030_p000_snd_fl_n.mp3",
        },
        {
            "e002_c030_p000_snd_pl_n.mp3",
            "e002_c030_p000_snd_cl_n.mp3",
            "e002_c030_p000_snd_gl_n.mp3",
        },
    };
    
    const char* questionsSndName[8][2] =
    {
        {
            "e002_c030_p000_snd_pl_n.mp3",
            "e002_c030_p000_snd_pl_plant_n.mp3"
        },
        {
            "e002_c030_p000_snd_gl_n.mp3",
            "e002_c030_p000_snd_gl_gloves_n.mp3"
        },
        {
            "e002_c030_p000_snd_fl_n.mp3",
            "e002_c030_p000_snd_fl_flute_n.mp3"
        },
        {
            "e002_c030_p000_snd_sl_n.mp3",
            "e002_c030_p000_snd_sl_slide_n.mp3"
        },
        {
            "e002_c030_p000_snd_blue_n.mp3",
            "e002_c030_p000_snd_bl_blue_n.mp3"
        },
        {
            "e002_c030_p000_snd_clock_n.mp3",
            "e002_c030_p000_snd_cl_clock_n.mp3"
        },
        {
            "e002_c030_p000_snd_flag_n.mp3",
            "e002_c030_p000_snd_fl_flag_n.mp3"
        },
        {
            "e002_c030_p000_snd_plane_n.mp3",
            "e002_c030_p000_snd_pl_plane_n.mp3"
        }
    };
    
    int correntTags[8] =
    {
        kTagExample003, kTagExample002, kTagExample001, kTagExample003,
        kTagExample003, kTagExample003, kTagExample003, kTagExample001
    };
    
    
    for (int i = 0; i < 8; i++)
    {
        std::vector<E002_Base_ExampleItem*> *examples = new std::vector<E002_Base_ExampleItem*>();
        
        for (int j = 0; j < 3; j++)
        {
            examples->push_back(new E002_Base_ExampleItem(i, exampleImgName[i][j], "", exampleSndName[i][j], kTagExample001 + j, correntTags[i]));
        }
        
        mExamples->push_back(examples);
    }
    
    for (int i = 0; i < 8; i++)
    {
        std::vector<std::string> *question = new std::vector<std::string>();
        
        for (int j = 0; j < 5; j++)
        {
            question->push_back(questionsImgName[i][j]);
        }
        
        mQuestions->push_back(question);
    }
    
    for (int i = 0; i < 8; i++)
    {
        std::vector<std::string> *questionSnd = new std::vector<std::string>();
        
        for (int j = 0; j < 2; j++)
        {
            questionSnd->push_back(questionsSndName[i][j]);
        }
        
        mQuestionSounds->push_back(questionSnd);
    }
    
    //memset(exampleName, 0, sizeof(exampleName));
  
    onViewLoad();
}

void E002_C030_P210::onExit()
{
    E002_Base_Question::onExit();
}


void E002_C030_P210::onViewLoad()
{
    E002_Base_Question::onViewLoad();
     
    CJPsdParser::parseToPsdJSON("e002_c030_p210.json", &m_psdDictionary);
    
    setBackground("e002_c030_p210_bg00_00.jpg");
    
    CJSprite *pharaoh = CJPsdParser::getPsdSprite("e002_c030_p210_img_00", m_psdDictionary);
    addChild(pharaoh, kDepth2_questions-1, kTagPharaoh);
    
    CJSprite *leftDais = CJPsdParser::getPsdSprite("e002_c030_p210_bg00_01@00", m_psdDictionary);
    addChild(leftDais, kDepth2_questions-1);

    CJSprite *rightDais = CJPsdParser::getPsdSprite("e002_c030_p210_bg00_01@01", m_psdDictionary);
    addChild(rightDais, kDepth2_questions-1);

    mMeerKat = new CJAnimationCharacter(this, "MEERKAT");
    mMeerKat->setLooping("e002_c030_p210_flash_n_cat02_loop");
    mMeerKat->setSuccess("e002_c030_p210_flash_s01_cat02_action", "e002_c030_p210_flash_s02_cat02_action", NULL);
    mMeerKat->setFails("e002_c030_p210_flash_f01_cat02_action", "e002_c030_p210_flash_f02_cat02_action", NULL);
    
    mBoomBoom = new CJAnimationCharacter(this, "BOOMBOOM");;
    mBoomBoom->setLooping("e002_c030_p210_flash_boom_n01_loop");
    mBoomBoom->setSuccess("e002_c030_p210_flash_boom_s01_action", "e002_c030_p210_flash_boom_s02_action", NULL);
    mBoomBoom->setFails("e002_c030_p210_flash_boom_f01_action", "e002_c030_p210_flash_boom_f02_action", NULL);
    
    mRobot = new CJAnimationCharacter(this, "ROBOT");;
    mRobot->setLooping("e002_c030_p220_flash_robot_n01_loop");
    mRobot->setSuccess("e002_c030_p220_flash_robot_s01_action", "e002_c030_p220_flash_robot_s02_action", NULL);
    mRobot->setFails("e002_c030_p220_flash_robot_f01_action", "e002_c030_p220_flash_robot_f02_action", NULL);

    addAnimationCharacter(mMeerKat, mBoomBoom, mRobot, NULL);
    
    mTargetPoint = CJPsdParser::getPsdPosition("e002_c030_p210_a00_success_position", m_psdDictionary);
 
    createFire();
    
    if(m_bIsGuide)
    {
        createGuideDim(kDepth2_questions-2);
    }
    
    setAnimationFile("e002_c030_p210_flash_cat02_sheets.json", "e002_c030_p210_flash_cat02_animations.json", "MEERKAT");
    setAnimationFile("e002_c030_p210_flash_boomboom_sheets.json", "e002_c030_p210_flash_boomboom_animations.json", "BOOMBOOM");
    setAnimationFile("e002_c030_p220_flash_robot_sheets.json", "e002_c030_p220_flash_robot_animations.json", "ROBOT");
    
    animationManagerParseStart();

}

void E002_C030_P210::onViewLoaded()
{
    E002_Base_Question::onViewLoaded();
    
    if (m_nCurrentStageIndex == 1) {
        E002_Base_Navigation::setVisibleButton(false, eNavigationButton_Prev);
    }
 
    CJMultimedia::getInstance()->playBGM(getFilePath("snd","e002_c030_snd_bgm_play02.mp3"), true);
    
    animationManagerParseComplete();
}

void E002_C030_P210::startFlashAnimation()
{
    createAllAnimations();
    mBoomBoom->showLooping();
    mMeerKat->showLooping();
    
    mCurrentFlashCharacter = "BOOMBOOM";
    feedbackCharacter = mBoomBoom->getSprite("e002_c030_p120_flash_boom_n01_body");
    
    if(m_bIsGuide)
    {
        CJUtils::performSelector(this, callfunc_selector(E002_Base_Question::removeTouchDelegateForGuide), 0.5);
        CJUtils::performSelector(this, callfunc_selector(E002_C030_P210::setQuestions),0.3);
    }
    else
    {
        onFirstNarration();
    }

}

void E002_C030_P210::onFirstNarration()
{
    E002_Base_Question::onFirstNarration();
    removeAllAnimationsInDataPool("MEERKAT");

    mFirstNarration = mSndManager->playLetsPlay2Narration(0);
    playAnimation("MEERKAT", "e002_c030_p210_flash_talk_cat02_loop", -1, kDepth1_flash);
    mPlayingGuideNarration = true;
}

void E002_C030_P210::onFirstNarrationEnd()
{
    E002_Base_Question::onFirstNarrationEnd();
    
    showGuideCharacterLooping();
    
    if (getUserDefaultFirstGuide(eGuidePageP210) == false)
    {
        mShowFirstGuide = true;
        setUserDefaultFirstGuide(eGuidePageP210);
        showGuide();
    }
    else
    {
        CJUtils::performSelector(this, callfunc_selector(E002_C030_P210::setQuestions),0.3);
    }
}


void E002_C030_P210::showGuideCharacterLooping()
{
    if(mPlayingGuideNarration)
    {
        removeAllAnimationsInDataPool("MEERKAT");
        mMeerKat->showLooping();
        
        guideCharacter = mMeerKat->getSprite("e002_c030_p120_flash_sun_n01_cat02_body");

        mPlayingGuideNarration = false;
    }
}


void E002_C030_P210::onNarrationFinishedCallback(std::string fileName)
{
    if (fileName == mFirstNarration && !isFirstSkiped())
    {
        onFirstNarrationEnd();
    }
    else if (fileName == mFirstNarration && isFirstSkiped())
    {
        removeAllAnimationsInDataPool("MEERKAT");
        mMeerKat->showLooping();
    }
    else if(fileName == mSuccessNarrationSnd)
    {
        showSuccessCharacterMotion(NULL, 1);
    }
    else if(fileName == mWrongNarrationSnd)
    {
        showWrongCharacterMotion(NULL, 1);
    }
    
    else if(!mReadyQuestion && fileName == mQuestionSounds->at(m_nCurrentStageIndex)->at(0))
    {
        runAction(CCSequence::create(CCDelayTime::create(0.5),
                                     CCCallFunc::create(this, callfunc_selector(E002_C030_P210::showExamples)),
                                     NULL));

    }
    else if( fileName == mQuestionSounds->at(m_nCurrentStageIndex)->at(1))
    {
        runAction(CCSequence::create(CCDelayTime::create(0.3f),
                                     CCCallFuncND::create(this, callfuncND_selector(E002_C030_P210::showSuccessCharacterMotion), (void*)0),
                                    NULL));
        
    }
}

#pragma mark - touch

bool E002_C030_P210::onTouchBegan(CCPoint tp)
{
    if(mReadyQuestion && guideCharacter != NULL && CJUtils::hitTestPoint(guideCharacter, tp, false))
    {
        mPlayingGuideNarration = true;
        stopAllNarration();
        onFirstNarration();
        return false;
    }
    else if (mReadyQuestion && feedbackCharacter != NULL && CJUtils::hitTestPoint(feedbackCharacter, tp, false))
    {
        stopAllNarration();
        showGuideCharacterLooping();
        
        if(mCurrentFlashCharacter == "BOOMBOOM")
            mSndManager->playBoomBoomTouchNarr();
        else
            mSndManager->playRobotTouchNarr();
        return false;
    }
    else if (mReadyQuestion && getChildByTag(kTagQuestion) != NULL && CJUtils::hitTestPoint(getChildByTag(kTagQuestion), tp, false))
    {
        m_touchingExampleSp = NULL;
        
        if(m_nCurrentStageIndex < 4)
        {
            playExampleNarrationRepeat(mQuestionSounds->at(m_nCurrentStageIndex)->at(0));

        }
        else
        {
            playQuestionSound(NULL, 0);
        }
        
        return true;
    }
    
    for (int i = kTagExample001; i <= kTagExample003; i++)
    {
        CJSprite* sp = (CJSprite*)getChildByTag(i);
        
        if(getChildByTag(i) != NULL && CJUtils::hitTestPoint(getChildByTag(i) , tp, false))
        {
            showLight();
            
            showGuideCharacterLooping();
            
            mExampleSelectIndex = i - kTagExample001;
            
            if(m_nCurrentStageIndex < 4)
            {
                speakNarration(NULL, mExamples->at(m_nCurrentStageIndex)->at(i-kTagExample001)->getSoundPath().c_str());
            }
            else
            {
                playExampleNarrationRepeat(mExamples->at(m_nCurrentStageIndex)->at(i-kTagExample001)->getSoundPath());
            }
            
            m_touchingExampleSp = GET_SELECTED_ITEM->getItemSprite();
            m_touchingExampleSp->setScale(1.2f);
            m_touchingExampleSp->setZOrder(kDepth6_dimmed);
                
            mTouchedPointGab = ccpSub(sp->getPosition(), tp);
            
            if(m_bIsGuide)
            {
                showHand(NULL, 1);
                m_touchingExampleSp->runAction(CCMoveTo::create(0.7f, mTargetPoint));
            }
            
            return true;
        }
    }
    
    return false;
}

void E002_C030_P210::onTouchMoved(CCPoint tp)
{
    if (m_touchingExampleSp !=  NULL)
    {
        m_touchingExampleSp->setPosition(ccp(tp.x + mTouchedPointGab.x, tp.y + mTouchedPointGab.y));
    }
}

void E002_C030_P210::onTouchEnded(CCPoint tp)
{
    stopExampleNarrationRepeat();
    hideLight();
    
    if(m_touchingExampleSp == NULL)
        return;
    
    if (CJUtils::hitTestPoint(m_touchingExampleSp, mTargetPoint, false))
    {
        intoTarget(m_touchingExampleSp, mTargetPoint);
    }
    else
    {
        mSndManager->playLetsPlay2Effect(2);
        m_touchingExampleSp->runAction(CCSpawn::create(CCEaseBackOut::create(CCMoveTo::create(0.1, GET_SELECTED_ITEM->getOriginalPosition())),
                                                       CCScaleTo::create(0.1, 1.0),
                                                       NULL));
    }
}

void E002_C030_P210::intoTarget(CJSprite* sp, CCPoint pt)
{
    setTouchDisalbeBaseLayer();
    mReadyQuestion = false;
    
    mSndManager->playLetsPlay2Effect(3);
    sp->runAction(CCSequence::create(CCEaseSineInOut::create(CCMoveTo::create(0.2, mTargetPoint)),
                                     CCSpawn::create(CCEaseSineIn::create(CCMoveTo::create(0.2, mTargetPoint)),
                                                     CCEaseSineIn::create(CCScaleTo::create(0.2, 0)),
                                                     NULL),
                                     CCDelayTime::create(0.5f),
                                     CCCallFuncN::create(this, callfuncN_selector(E002_C030_P210::checkAnswer)),
                                     NULL));
}

void E002_C030_P210::checkAnswer(CCNode *node)
{
    if(GET_SELECTED_ITEM->getItemTag() ==  GET_SELECTED_ITEM->getCorrectTag())
    {
        mSndManager->playSuccessSfxSnd(12);
        
        runAction(CCSequence::create(CCDelayTime::create(1.0),
                                     CCCallFuncN::create(this, callfuncN_selector(E002_C030_P210::onSuccesses)),
                                     NULL));
    }
    else
    {
        node->runAction(CCSequence::create(CCDelayTime::create(0.5f),
                                           CCCallFuncN::create(this, callfuncN_selector(E002_C030_P210::onFails)),
                                           NULL));
        return;
    }
}

#pragma mark - feedback event

void E002_C030_P210::onExamplesTouched(int index)
{
    E002_Base_Question::onExamplesTouched(index);
}


void E002_C030_P210::onSuccesses(CCNode *node, int tag)
{
    CCLog("onSuccess");
    
    for (int i = 0; i < GET_EXAMPLES->size(); i++)
    {
        if(GET_EXAMPLES->at(i)->getItemTag() != node->getTag() )
        {
            GET_EXAMPLES->at(i)->getItemSprite()->runAction(CCSequence::create(CCMoveBy::create(0.3f, ccp(0, -200)),
                                                                               CCCallFuncN::create(this, callfuncN_selector(CJLayer::removeChild)),
                                                                               NULL));
        }
    }
    
    ((CJSprite*)getChildByTag(kTagQuestion))->setTexture(CCTextureCache::sharedTextureCache()
                                                        ->addImage(getFilePath("img", "e002_c030_p210_q00_00_seq00.png").c_str()));
    
    getChildByTag(kTagQuestion)->runAction(CCSequence::create(CCDelayTime::create(0.5f),
                                                              CCCallFuncND::create(this, callfuncND_selector(E002_C030_P210::playEffect), (void*)1),
                                                               CJUtils::getSeqAction(1, 0.05f,
                                                                 getFilePath("img","e002_c030_p210_q00_00_seq01.png").c_str(),
                                                                 getFilePath("img","e002_c030_p210_q00_00_seq02.png").c_str(),
                                                                 getFilePath("img","e002_c030_p210_q00_00_seq03.png").c_str(),
                                                                 getFilePath("img","e002_c030_p210_q00_00_seq04.png").c_str(),
                                                                 NULL),
                                                              CCCallFunc::create(this,callfunc_selector(E002_C030_P210::showSuccessText)),
                                                              CCDelayTime::create(0.3f),
                                                              CCCallFuncND::create(this, callfuncND_selector(E002_C030_P210::playQuestionSound),(void*)1),
                                                              NULL));
    
    
}

void E002_C030_P210::showSuccessText()
{
    for (int i = 1; i < mQuestions->at(m_nCurrentStageIndex)->size(); i++)
    {
        CJSprite *text = CJPsdParser::getPsdSprite(mQuestions->at(m_nCurrentStageIndex)->at(i), m_psdDictionary);
        addChild(text, kDepth3_examples, i + kTagSuccess000 - 1);
    }
    
    float delay = 0.3f;
    
    for (int i = kTagSuccess001; i <= kTagSuccess003; i++)
    {
        getChildByTag(i)->runAction(CCSequence::create(CCDelayTime::create(delay),
                                                       CCScaleTo::create(0.2, 1.2),
                                                       CCScaleTo::create(0.2, 1.0),
                                                       NULL));
        delay += 0.6f;
    }
}

void E002_C030_P210::onFails(CCNode *node, int tag)
{
    mFailCount++;
    mReadyQuestion = true;
    mSndManager->playWrongSfxSnd(12);
    setTouchEnableBaseLayer();
    
    runAction(CCSequence::create(CCDelayTime::create(0.3f),
                                 CCCallFuncND::create(this, callfuncND_selector(E002_C030_P210::showWrongCharacterMotion), (void*)0),
                                 NULL));
    
    node->runAction(CCSequence::create(CCDelayTime::create(0.1f),
                                       CCEaseSineOut::create(CCScaleTo::create(0.2, 0.7)),
                                       CCMoveBy::create(0.1f, ccp(10, 0)),
                                       CCMoveBy::create(0.1f, ccp(-20, 0)),
                                       CCMoveBy::create(0.1f, ccp(5, 0)),
                                       CCMoveBy::create(0.1f, ccp(-5, 0)),
                                       CCScaleTo::create(0.1f, 1.0f),
                                       CCEaseBackOut::create(CCMoveTo::create(0.2, GET_SELECTED_ITEM->getOriginalPosition())),
                                       NULL));
}

void E002_C030_P210::onComplete()
{
    E002_Base_Question::onComplete();

}

#pragma mark - user function

void E002_C030_P210::setQuestions()
{
    resetValue();
    stopAllActions();
    
    if(m_nCurrentStageIndex < 4)
    {
        CJSprite *question = CJPsdParser::getPsdSprite("e002_c030_p210_q00_00_seq00", m_psdDictionary);
        
        addChild(question, kDepth2_questions, kTagQuestion);
        
        std::string que = mQuestions->at(m_nCurrentStageIndex)->at(0);
        
        question->runAction(CCSequence::create(CCCallFuncND::create(this, callfuncND_selector(E002_C030_P210::playEffect), (void*)1),
                                               CJUtils::getSeqAction(1, 0.1f,
                                                                     getFilePath("img","e002_c030_p210_q00_00_seq01.png").c_str(),
                                                                     getFilePath("img","e002_c030_p210_q00_00_seq02.png").c_str(),
                                                                     getFilePath("img", que.append(".png")).c_str(),
                                                                     NULL),
                                               CCDelayTime::create(0.5f),
                                               CCCallFuncND::create(this, callfuncND_selector(E002_C030_P210::playQuestionSound),(void*)0),
                                               NULL));
        
    }
    else
    {
        CJSprite *question = CJPsdParser::getPsdSprite("e002_c030_p210_q00_01_seq00", m_psdDictionary);
        
        addChild(question, kDepth2_questions, kTagQuestion);
        
        std::string que = mQuestions->at(m_nCurrentStageIndex)->at(0);
        
        question->runAction(CCSequence::create(CCCallFuncND::create(this, callfuncND_selector(E002_C030_P210::playEffect), (void*)1),
                                               CJUtils::getSeqAction(1, 0.1f,
                                                                     getFilePath("img","e002_c030_p210_q00_01_seq01.png").c_str(),
                                                                     getFilePath("img","e002_c030_p210_q00_01_seq02.png").c_str(),
                                                                     getFilePath("img", que.append(".png")).c_str(),
                                                                     NULL),
                                               CCDelayTime::create(0.5f),
                                               CCCallFuncND::create(this, callfuncND_selector(E002_C030_P210::playQuestionSound),(void*)0),
                                               NULL));
    }

}

void E002_C030_P210::setReadyQuestion(CCNode* node, bool isReady)
{
    if (isReady)
    {
        if (m_bIsGuide)
        {
            showHand(NULL, 0);
            return;
        }
        
        setTouchEnableBaseLayer();
    }
    
    mReadyQuestion = isReady;
}


void E002_C030_P210::showExamples()
{
    for (int i = 0; i < 3; i++)
    {
        float delay = 1.0f;
        
        E002_Base_ExampleItem *item = GET_EXAMPLES->at(i);
        item->setOriginalPosition(CJPsdParser::getPsdPosition(item->getImgPath(), m_psdDictionary));
        
        item->setItemSprite(CJPsdParser::getPsdSprite(item->getImgPath(), m_psdDictionary));
        
        item->getItemSprite()->setPositionY(-160);
        addChild(item->getItemSprite(), kDepth3_examples, kTagExample001 + i);
        
        delay *= i;
        
        if ( i == 2)
        {
            item->getItemSprite()->runAction(CCSequence::create(CCDelayTime::create(delay),
                                                                CCCallFuncND::create(this, callfuncND_selector(E002_C030_P210::playAppearanceExamplesSound), (void*)i),
                                                                CCEaseBackOut::create(CCMoveTo::create(0.3f, item->getOriginalPosition())),
                                                                CCCallFuncND::create(this, callfuncND_selector(E002_C030_P210::setReadyQuestion), (void*)true),
                                                                NULL));
        }
        else
        {
            item->getItemSprite()->runAction(CCSequence::create(CCDelayTime::create(delay),
                                                                CCCallFuncND::create(this, callfuncND_selector(E002_C030_P210::playAppearanceExamplesSound), (void*)i),
                                                                CCEaseBackOut::create(CCMoveTo::create(0.3f, item->getOriginalPosition())),
                                                                NULL));
        }
       
    }
}

void E002_C030_P210::resetValue()
{
    setTouchDisalbeBaseLayer();
    
    if (m_nCurrentStageIndex > 1)
    {
        E002_Base_Navigation::setVisibleButton(true, eNavigationButton_Prev);
    }
    else if(m_nCurrentStageIndex == 1)
    {
        E002_Base_Navigation::setVisibleButton(false, eNavigationButton_Prev);
    }
    
    showGuideCharacterLooping();
    
    removeChildByTag(kTagQuestion);
    removeChild(m_touchingExampleSp);
    setReadyQuestion(NULL, false);
    mFailCount = 0;
    
    for (int i = kTagExample001; i <= kTagSuccess003; i++)
    {
        if(getChildByTag(i) != NULL)
            removeChildByTag(i);
    }
    
    if(m_nCurrentStageIndex > 3)
    {
        if (mCurrentFlashCharacter == "BOOMBOOM")
        {
            removeAllAnimationsInDataPool("BOOMBOOM");
            mRobot->showLooping();
            
            feedbackCharacter = mRobot->getSprite("e002_c030_p120_flash_robot_n01_body");
            mCurrentFlashCharacter = "ROBOT";
            
        }
        
        ((CJSprite*)getChildByTag(kTagPharaoh))->setTexture(CCTextureCache::sharedTextureCache()
                                                            ->addImage(getFilePath("img", "e002_c030_p210_img_01.png").c_str()));

    }
    else
    {
        if (mCurrentFlashCharacter == "ROBOT")
        {
            removeAllAnimationsInDataPool("ROBOT");
            mBoomBoom->showLooping();
            
            feedbackCharacter = mBoomBoom->getSprite("e002_c030_p120_flash_boom_n01_body");
            mCurrentFlashCharacter = "BOOMBOOM";
        }
        
        ((CJSprite*)getChildByTag(kTagPharaoh))->setTexture(CCTextureCache::sharedTextureCache()
                                                            ->addImage(getFilePath("img", "e002_c030_p210_img_00.png").c_str()));

    }
}

#pragma mark - sound & narration
void E002_C030_P210::playQuestionSound(CCNode* node, void* index)
{
    speakNarration(NULL, mQuestionSounds->at(m_nCurrentStageIndex)->at((int)index).c_str());
}

void E002_C030_P210::playAppearanceExamplesSound(CCNode* sender, void* index)
{
    mSndManager->playLetsPlay2Effect(0);
    speakNarration(NULL, mExamples->at(m_nCurrentStageIndex)->at((int)index)->getSoundPath().c_str());
}

  
#pragma mark - user function

void E002_C030_P210::speakNarration(CCNode *node, const char* fileName)
{
    stopAllNarration();
    playNarration(fileName); 
}


#pragma mark - navigation delegate

void E002_C030_P210::onTouchedNavigationButtonAtIndex()
{
    E002_Base_Question::onTouchedNavigationButtonAtIndex();
    
    E002_C030_P000_Index* _indexClass = E002_C030_P000_Index::create();
    _indexClass->init();
    _indexClass->setIndexDelegate(this);
    _indexClass->showIndex(this, _indexClass);
    addChild(_indexClass, kDepth11_Index);
}

void E002_C030_P210::onTouchedNavigationButtonAtInfo()
{
    E002_Base_Question::onTouchedNavigationButtonAtInfo();
     
    showGuide();
}

void E002_C030_P210::onTouchedNavigationButtonAtPrev()
{
    E002_Base_Question::onTouchedNavigationButtonAtPrev();
    if (m_nCurrentStageIndex > 0) {
        m_nCurrentStageIndex--;
        setQuestions();
    }
}

void E002_C030_P210::onTouchedNavigationButtonAtNext()
{
    E002_Base_Question::onTouchedNavigationButtonAtNext();
    
    if (m_nCurrentStageIndex < m_nMaxStageCount-1)
    {
        m_nCurrentStageIndex++;
        setQuestions();
    }
    else
    {
        //If you complete "Let's play1", call this function.
        completeLetsPlay2();
        
        //replayceScene
        replaceSceneTransitionFadeOut(E002_C030_P230);
    }
    
}

void E002_C030_P210::onTouchedNavigationButtonAtReward()
{
    showLetPlay2RewardPopup(NULL, m_nCurrentStageIndex - 1);
}


void E002_C030_P210::onTouchedNavigationButtonAtClose()
{
    E002_Base_Question::onTouchedNavigationButtonAtClose();
    
}


void E002_C030_P210::OnLastFrame(CJAnimation* pAnimation)
{
    E002_Base_Question::OnLastFrame(pAnimation);
    
    for (int i = 0; i < mBoomBoom->getSuccessKeys()->size(); i++)
    {
        if(pAnimation->getName() == mBoomBoom->getSuccessKeys()->at(i) || pAnimation->getName() == mRobot->getSuccessKeys()->at(i))
        {
            if(m_bIsGuide)
            {
                ((E002_Base_Question*)getParent())->removeGuide();
                return;
            }
            
            //CJUtils::performSelector(this, callfuncND_selector(E002_C030_P210::playEffect),(void*)5, 0.3f);
            
            int index = m_nCurrentStageIndex - 1;
            CJUtils::performSelector(this, callfuncND_selector(E002_C030_P210::showLetPlay2RewardItem),(void*) index, 0.3f);
        }
    }
}

void E002_C030_P210::completeToGetRewardItem()
{
    E002_Base_Question::completeToGetRewardItem();
    
    if( m_nCurrentStageIndex == 3)
    {
        runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(E002_C030_P210::resetValue)),
                                     CCDelayTime::create(0.5f),
                                     CCCallFunc::create(this, callfunc_selector(E002_C030_P210::switchScene)),
                                     NULL));
    }
    else
    {
        CJUtils::performSelector(this, callfunc_selector(E002_C030_P210::onTouchedNavigationButtonAtNext), 0.5f);
    }
}

#pragma mark - sprite create

void E002_C030_P210::createFire()
{
    if(getChildByTag(kTagLeftFireBlur) == NULL)
    {
        CJSprite *leftFireBlur = CJPsdParser::getPsdSprite("e002_c030_p210_img_fire_blur@00", m_psdDictionary);
        addChild(leftFireBlur, kDepth1_flash-1, kTagLeftFireBlur);
        
        CJSprite *rightFireBlur = CJPsdParser::getPsdSprite("e002_c030_p210_img_fire_blur@01", m_psdDictionary);
        addChild(rightFireBlur, kDepth1_flash-1, kTagRightFireBlur);

    }
    
    CJSprite *leftFire = CJPsdParser::getPsdSprite("e002_c030_p210_img_fire_on00@0", m_psdDictionary);
    addChild(leftFire, kDepth1_flash, kTagLeftFire);
    
    leftFire->runAction(CJUtils::getSeqAction(-1, 0.2f,
                                              getFilePath("img","e002_c030_p210_img_fire_on01.png").c_str(),
                                              getFilePath("img","e002_c030_p210_img_fire_on02.png").c_str(),
                                              getFilePath("img","e002_c030_p210_img_fire_on03.png").c_str(),
                                              getFilePath("img","e002_c030_p210_img_fire_on04.png").c_str(),
                                              NULL));
    
    CJSprite *rightFire = CJPsdParser::getPsdSprite("e002_c030_p210_img_fire_on00@1", m_psdDictionary);
    addChild(rightFire, kDepth1_flash, kTagRightFire);
    
    rightFire->runAction(CJUtils::getSeqAction(-1, 0.2f,
                                              getFilePath("img","e002_c030_p210_img_fire_on01.png").c_str(),
                                              getFilePath("img","e002_c030_p210_img_fire_on02.png").c_str(),
                                              getFilePath("img","e002_c030_p210_img_fire_on03.png").c_str(),
                                              getFilePath("img","e002_c030_p210_img_fire_on04.png").c_str(),
                                              NULL));
    
}

void E002_C030_P210::switchScene()
{
    CJSprite *leftFire = (CJSprite*)getChildByTag(kTagLeftFire);
    
    leftFire->stopAllActions();
    leftFire->runAction(CJUtils::getSeqAction(1, 0.2f,
                                              getFilePath("img","e002_c030_p210_img_fire_off00.png").c_str(),
                                              getFilePath("img","e002_c030_p210_img_fire_off01.png").c_str(),
                                              getFilePath("img","e002_c030_p210_img_fire_off00.png").c_str(),
                                              getFilePath("img","e002_c030_p210_img_fire_off01.png").c_str(),
                                              getFilePath("img","e002_c030_p210_img_fire_off02.png").c_str(),
                                              getFilePath("img","e002_c030_p210_img_fire_off03.png").c_str(),
                                              NULL));
    
    
    CJSprite *rightFire = (CJSprite*)getChildByTag(kTagRightFire);
    
    rightFire->stopAllActions();
    rightFire->runAction(CCSequence::create(CJUtils::getSeqAction(1, 0.2f,
                                               getFilePath("img","e002_c030_p210_img_fire_off00.png").c_str(),
                                               getFilePath("img","e002_c030_p210_img_fire_off01.png").c_str(),
                                               getFilePath("img","e002_c030_p210_img_fire_off00.png").c_str(),
                                               getFilePath("img","e002_c030_p210_img_fire_off01.png").c_str(),
                                               getFilePath("img","e002_c030_p210_img_fire_off02.png").c_str(),
                                               getFilePath("img","e002_c030_p210_img_fire_off03.png").c_str(),
                                               NULL),
                                            CCCallFunc::create(this, callfunc_selector(E002_C030_P210::showDarkScreen)),
                                            CCCallFunc::create(this, callfunc_selector(E002_C030_P210::lightCandle)),
                                            NULL));
    
    showDarkScreen();
    
    getChildByTag(kTagLeftFireBlur)->runAction(CCFadeOut::create(0.8f));
    getChildByTag(kTagRightFireBlur)->runAction(CCFadeOut::create(0.8f));

}

void E002_C030_P210::showDarkScreen()
{
    removeAllAnimationsInDataPool("BOOMBOOM");
    mRobot->showLooping();
    
    CJSprite *darkBG = CJSprite::create();
    darkBG->init();
    darkBG->setContentSize(winSize);
    darkBG->setTextureRect(CCRectMake(0, 0, winSize.width, winSize.height));
    darkBG->setColor(ccBLACK);
    darkBG->setPosition(winCenter);
    darkBG->setOpacity(0);
    
    addChild(darkBG, kDepth6_dimmed);
    
    CJSprite *darkPharaoh = CJPsdParser::getPsdSprite("e002_c030_p210_img_black", m_psdDictionary);
    addChild(darkPharaoh, kDepth5_particle);
    darkPharaoh->setOpacity(100);
    
    darkPharaoh->runAction(CCSequence::create(CCFadeTo::create(1.0f, 255),
                                              CCDelayTime::create(0.2f),
                                              CCCallFunc::create(this, callfunc_selector(E002_C030_P210::changePharaoh)),
                                              CCFadeTo::create(1.0f, 0),
                                              NULL));
    
    darkBG->runAction(CCSequence::create(CCFadeTo::create(1.0f, 100),
                                         CCCallFunc::create(this, callfunc_selector(E002_C030_P210::lightCandle)),
                                         CCFadeTo::create(3.0f, 0),
                                         CCDelayTime::create(0.5f),
                                         CCCallFunc::create(this, callfunc_selector(E002_C030_P210::onTouchedNavigationButtonAtNext)),
                                         NULL));
    
}

void E002_C030_P210::changePharaoh()
{
    ((CJSprite*)getChildByTag(kTagPharaoh))->setTexture(CCTextureCache::sharedTextureCache()
                                                        ->addImage(getFilePath("img", "e002_c030_p210_img_01.png").c_str()));

}

void E002_C030_P210::lightCandle()
{
    removeChildByTag(kTagRightFire);
    removeChildByTag(kTagLeftFire);
    
    CJSprite *leftFireBottom = CJPsdParser::getPsdSprite("e002_c030_p210_img_fire_bottom@0", m_psdDictionary);
    addChild(leftFireBottom, kDepth1_flash, kTagLeftFireBottom);
     
    CJSprite *leftFireTop = CJPsdParser::getPsdSprite("e002_c030_p210_img_fire_top@0", m_psdDictionary);
    leftFireTop->setScale(0);
    leftFireTop->setAnchorPointWithoutPosition(ccp(0.5, 0));
    addChild(leftFireTop, kDepth1_flash, kTagLeftFireTop);
     
    CJSprite *rightFireBottom = CJPsdParser::getPsdSprite("e002_c030_p210_img_fire_bottom@1", m_psdDictionary);
    addChild(rightFireBottom, kDepth1_flash, kTagRightFireBottom);
     
    CJSprite *rightFireTop = CJPsdParser::getPsdSprite("e002_c030_p210_img_fire_top@1", m_psdDictionary);
    rightFireTop->setScale(0);
    rightFireTop->setAnchorPointWithoutPosition(ccp(0.5, 0));
    addChild(rightFireTop, kDepth1_flash, kTagRightFireTop);
    
    leftFireTop->runAction(CCSequence::create(CCDelayTime::create(0.5),
                                              CCScaleTo::create(2.0, 1),
                                              CCCallFunc::create(this, callfunc_selector(E002_C030_P210::createFire)),
                                              CCCallFuncN::create(this, callfuncN_selector(CJLayer::removeChild)),
                                              NULL));
    
    rightFireTop->runAction(CCSequence::create(CCDelayTime::create(0.5),
                                              CCScaleTo::create(2.0, 1),
                                            CCCallFuncN::create(this, callfuncN_selector(CJLayer::removeChild)),
                                              NULL));
    
    getChildByTag(kTagRightFireBlur)->runAction(CCFadeIn::create(2.5));
    getChildByTag(kTagLeftFireBlur)->runAction(CCFadeIn::create(2.5));
    
}

void E002_C030_P210::showSuccessCharacterMotion(CCNode *node, int index)
{
    if(index == 0)
    {
        if (m_nCurrentStageIndex%2 == 0)
        {
            mSuccessNarrationSnd = mSndManager->playMeercatSuccessNarr(16);
        }
        else
        {
            mSuccessNarrationSnd = mSndManager->playMeercatSuccessNarr(19);
        }

        mMeerKat->showSuccess();
        
        if(mCurrentFlashCharacter == "BOOMBOOM")
        {
             mBoomBoom->showSuccess();
        }
        else
        {
             mRobot->showSuccess();
        }
    }
    else
    {
        if(mCurrentFlashCharacter == "BOOMBOOM")
        {
            if (m_nCurrentStageIndex%2 == 0)
            {
                mSndManager->playBoomBoomSuccessNarr(5);
            }
            else
            {
                mSndManager->playBoomBoomSuccessNarr(6);
            }
        }
        else
        {
            if (m_nCurrentStageIndex%2 == 0)
            {
                mSndManager->playRobotSuccessNarr(24);
            }
            else
            {
                mSndManager->playRobotSuccessNarr(25);
            }
        }
    }
}

void E002_C030_P210::showWrongCharacterMotion(CCNode *node, int index)
{
    if(index == 0)
    {
        if (m_nCurrentStageIndex%2 == 0)
        {
            if(mFailCount%2 == 0)
            {
                mWrongNarrationSnd = mSndManager->playMeercatWrongNarr(8);
            }
            else
            {
                mWrongNarrationSnd = mSndManager->playMeercatWrongNarr(11);
            }
        }
        else
        {
            if(mFailCount%2 == 0)
            {
                mWrongNarrationSnd = mSndManager->playMeercatWrongNarr(11);
            }
            else
            {
                mWrongNarrationSnd = mSndManager->playMeercatWrongNarr(8);
            }
        }
        
        mMeerKat->showFails();
        
        if(mCurrentFlashCharacter == "BOOMBOOM")
        {
            mBoomBoom->showFails();
        }
        else
        {
            mRobot->showFails();
        }
    }
    else
    {
        if (m_nCurrentStageIndex%2 == 0)
        {
            if(mCurrentFlashCharacter == "BOOMBOOM")
            {
                if(mFailCount%2 == 0)
                {
                    mSndManager->playBoomBoomWrongNarr(12);
                }
                else
                {
                    mSndManager->playBoomBoomWrongNarr(15);
                    
                }
            }
            else
            {
                if(mFailCount%2 == 0)
                {
                    mSndManager->playRobotWrongNarr(3);
                }
                else
                {
                    mSndManager->playRobotWrongNarr(4);
                    
                }
            }
            
        }
        else
        {
            if(mCurrentFlashCharacter == "BOOMBOOM")
            {
                if(mFailCount%2 == 0)
                {
                    mSndManager->playBoomBoomWrongNarr(15);
                }
                else
                {
                    mSndManager->playBoomBoomWrongNarr(12);
                    
                }
            }
            else
            {
                if(mFailCount%2 == 0)
                {
                    mSndManager->playRobotWrongNarr(4);
                }
                else
                {
                    mSndManager->playRobotWrongNarr(3);
                    
                }
            }
        }
    }
}

void E002_C030_P210::playEffect(CCNode *node, int index)
{
    mSndManager->playLetsPlay2Effect(index);
}

void E002_C030_P210::showLight()
{
    CJSprite *light = CJPsdParser::getPsdSprite("e002_c030_p210_img_effect", m_psdDictionary);
    addChild(light, kDepth4_title, kTagLight);
    
    light->setOpacity(120);
    
    CCRepeat *repeat = CCRepeat::create(CCSequence::create(CCFadeTo::create(0.5, 120),
                                                           CCFadeTo::create(0.5, 255),
                                                           NULL), -1);
    
    light->runAction(CCSequence::create(CCFadeIn::create(0.4),
                                        repeat,
                                        NULL));
    
    CJSprite *light2 = CJPsdParser::getPsdSprite("e002_c030_p210_img_effect_02", m_psdDictionary);
    addChild(light2, kDepth4_title-1, kTagLight2);
    
    light2->setOpacity(70);
    
    CCRepeat *repeat2 = CCRepeat::create(CCSequence::create(CCSpawn::create(CCFadeTo::create(0.5, 70),
                                                                            CCScaleTo::create(0.5, 0.9),
                                                                            NULL),
                                                            CCSpawn::create(CCFadeTo::create(0.5, 255),
                                                                            CCScaleTo::create(0.5, 1.2),
                                                                            NULL),
                                                           NULL), -1);
    
    light2->runAction(CCSequence::create(CCFadeIn::create(0.4),
                                        repeat2,
                                        NULL));

}

void E002_C030_P210::hideLight()
{
    removeChildByTag(kTagLight);
    removeChildByTag(kTagLight2);
}

void E002_C030_P210::showGuide()
{
    E002_Base_Question::showGuide();
    
    m_Guide = E002_C030_P210::create();
    m_Guide->init();
    m_Guide->setGuide(true);
    addChild(m_Guide, kDepth10_guide);
    
    std::vector<CCPoint> *guideHandPosition = new std::vector<CCPoint>();
    
    guideHandPosition->push_back(CJPsdParser::getPsdPosition("e002_common_img_guide_hand@00", m_psdDictionary));
    guideHandPosition->push_back(CJPsdParser::getPsdPosition("e002_common_img_guide_hand@01", m_psdDictionary));
    
    m_Guide->setGuideHandPosition(guideHandPosition);
}

void E002_C030_P210::removeGuide()
{
    E002_Base_Question::removeGuide();
    removeChild(m_Guide);
    
}

void E002_C030_P210::completeToMoveHand(CCNode *node, int index)
{
    switch (index) {
        case 0:
            onTouchBegan(getChildByTag(kTagExample003)->getPosition());
            break;
        case 1:
            onTouchEnded(mTargetPoint);
            break;
        default:
            break;
    }
}

void E002_C030_P210::completeFirstGuide()
{
    CJUtils::performSelector(this, callfunc_selector(E002_C030_P210::setQuestions),0.3);
}