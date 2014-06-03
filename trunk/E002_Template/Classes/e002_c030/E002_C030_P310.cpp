

#include "E002_C030_P310.h"
#include "E002_C030_P000_Index.h"
//#include "E001_C110_P120_Q2.h"
//#include "E002_C030_P210_Guide.h"
#include "E002_C030_P320.h"

#define GET_EXAMPLES mExamples->at(m_nCurrentStageIndex)
#define GET_SELECTED_ITEM mExamples->at(m_nCurrentStageIndex)->at(mExampleSelectIndex)

#define INDEX_QUESTION        0
#define INDEX_LIGHT           1
#define INDEX_QUE_TEXT        2
#define INDEX_ANS_TEXT        3
#define INDEX_TARGET          4
#define INDEX_QUE_SHADOW      5
#define INDEX_ANS_SHADOW      6
#define INDEX_QUE_BG          7
#define INDEX_ANS_BG          8
#define INDEX_QUE_BLANK       9
#define INDEX_SUC_TEXT        10
#define INDEX_QUE_SOUND       11
#define INDEX_QUE_SUCCESS_SND 12


enum
{
    kTagWall = 200,
    
    kTagFront,
    kTagBack,
    
    kTagExample001 = 250,
    kTagExample002,
    kTagExample003,
    
    kTagQuestion001,
    kTagQuestion002,
    kTagQuestion003,

    kTagTarget001,
    kTagTarget002,
    kTagTarget003,
    
    kTagBlank001,
    kTagBlank002,
    kTagBlank003,
    
    kTagQueBG001,
    kTagQueBG002,
    kTagQueBG003,

    kTagQueText001,
    kTagQueText002,
    kTagQueText003,
    
    kTagAnswerText001,
    kTagAnswerText002,
    kTagAnswerText003,
    
    kTagLight001,
    kTagLight002,
    kTagLight003,
    
    kTagAnswerBG001,
    kTagAnswerBG002,
    kTagAnswerBG003,
    
    kTagAnsShadow001,
    kTagAnsShadow002,
    kTagAnsShadow003,

    kTagQueShadow001,
    kTagQueShadow002,
    kTagQueShadow003,
    
    kTagSuccessText001,
    kTagSuccessText002,
    kTagSuccessText003,

};

E002_C030_P310::E002_C030_P310()
{
    mExamples = new std::vector<std::vector<E002_Base_ExampleItem*>*>();
    mQuestions = new std::vector<std::vector<std::vector<std::string>*>*>();
    
    m_touchingExampleSp = NULL;
    mExampleSelectIndex = 0;
    
    mSndManager = new E002_C030_SoundManager();
}

E002_C030_P310::~E002_C030_P310()
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

bool E002_C030_P310::init()
{
    if (!E002_Base_Question::init()) {
        return false;
    }
    
    m_nMaxStageCount = 4;
    m_nCurrentStageIndex = 1;
    mSelectedCount = 0;
    mSuccessCount = 0;
    mPlayingGuideNarration = false;
    
    mCurrentQuestionTheme = ONE_QUETION_THEME;
    
    return true;
}

void E002_C030_P310::onEnter()
{
    E002_Base_Question::onEnter();
    
    const char* exampleImgName[4][3] =
    {
        {
            "e002_c030_p310_ans_sl@00",
            "e002_c030_p310_ans_cl@0",
            "e002_c030_p310_ans_bl@00"
        },
        {
            "e002_c030_p310_ans_fl",
            "e002_c030_p310_ans_gl@0",
            "e002_c030_p310_ans_cl@1"
        },
        {
            "e002_c030_p310_ans_pl@00",
            "e002_c030_p310_ans_gl@1",
            ""
        },
        {
            "e002_c030_p310_ans_sl@02",
            "e002_c030_p310_ans_gl@03",
            "e002_c030_p310_ans_bl@01",
        }
        
    };
    
    const char* exampleSndName[4][3] =
    {
        {
            "e002_c030_p000_snd_sl_n.mp3",
            "e002_c030_p000_snd_cl_n.mp3",
            "e002_c030_p000_snd_bl_n.mp3"
        },
        {
            "e002_c030_p000_snd_fl_n.mp3",
            "e002_c030_p000_snd_gl_n.mp3",
            "e002_c030_p000_snd_cl_n.mp3"
        },
        {
            "e002_c030_p000_snd_pl_n.mp3",
            "e002_c030_p000_snd_gl_n.mp3",
            ""
        },
        {
            "e002_c030_p000_snd_sl_n.mp3",
            "e002_c030_p000_snd_gl_n.mp3",
            "e002_c030_p000_snd_bl_n.mp3",
        }
        
    };
    
    const char* questionsImgName[13][4][3] =
    {
        {
            {
                "e002_c030_p310_img_sled",
                "",
                ""
            },
            {
                "e002_c030_p310_img_clap",
                "",
                ""
            },
            {
                "e002_c030_p310_img_glad",
                "e002_c030_p310_img_plane",
                ""
            },
            {
                "e002_c030_p310_img_glass",
                "e002_c030_p310_img_slide",
                "e002_c030_p310_img_blue"
            }
        },
        {
            {
                "e002_c030_p310_light_sled",
                "",
                ""
            },
            {
                "e002_c030_p310_light_clap",
                "",
                ""
            },
            {
                "e002_c030_p310_light_glad",
                "e002_c030_p310_light_plane",
                ""
            },
            {
                "e002_c030_p310_light_glass",
                "e002_c030_p310_light_slide",
                "e002_c030_p310_light_blue"
            }
        },
        {
            {
                "e002_c030_p310_que_sled_text",
                "",
                ""
            },
            {
                "e002_c030_p310_que_clap_text",
                "",
                ""
            },
            {
                "e002_c030_p310_que_glad_text",
                "e002_c030_p310_que_plane_text",
                ""
            },
            {
                "e002_c030_p310_que_glass_text",
                "e002_c030_p310_que_slide_text",
                "e002_c030_p310_que_blue_text"
            }
        },
        {
            {
                "e002_c030_p310_ans_sl_text@00",
                "",
                ""
            },
            {
                "e002_c030_p310_ans_cl_text",
                "",
                ""
            },
            {
                "e002_c030_p310_ans_gl_text@00",
                "e002_c030_p310_ans_pl_text",
                ""
            },
            {
                "e002_c030_p310_ans_gl_text@01",
                "e002_c030_p310_ans_sl_text@01",
                "e002_c030_p310_ans_bl_text"
            }
        },
        {
            {
                "e002_c030_p310_ans_sl@01",
                "",
                ""
            },
            {
                "e002_c030_p310_ans_cl@2",
                "",
                ""
            },
            {
                "e002_c030_p310_ans_gl@02",
                "e002_c030_p310_ans_pl@01",
                ""
            },
            {
                "e002_c030_p310_ans_gl@04",
                "e002_c030_p310_ans_sl@03",
                "e002_c030_p310_ans_bl@02",
            }
        },
        {
            {
                "e002_c030_p310_que_bg_shadow@00",
                "",
                ""
            },
            {
                "e002_c030_p310_que_bg_shadow@01",
                "",
                ""
            },
            {
                "e002_c030_p310_que_bg_shadow@02",
                "e002_c030_p310_que_bg_shadow@03",
                ""
            },
            {
                "e002_c030_p310_que_bg_shadow@04",
                "e002_c030_p310_que_bg_shadow@05",
                "e002_c030_p310_que_bg_shadow@06",
            }
        },
        {
            {
                "e002_c030_p310_ans_bg_shadow@00",
                "",
                ""
            },
            {
                "e002_c030_p310_ans_bg_shadow@01",
                "",
                ""
            },
            {
                "e002_c030_p310_ans_bg_shadow@02",
                "e002_c030_p310_ans_bg_shadow@03",
                ""
            },
            {
                "e002_c030_p310_ans_bg_shadow@04",
                "e002_c030_p310_ans_bg_shadow@05",
                "e002_c030_p310_ans_bg_shadow@06",
            }
        },
        {
            {
                "e002_c030_p310_que_bg_00@00",
                "",
                ""
            },
            {
                "e002_c030_p310_que_bg_00@01",
                "",
                ""
            },
            {
                "e002_c030_p310_que_bg_00@02",
                "e002_c030_p310_que_bg_00@03",
                ""
            },
            {
                "e002_c030_p310_que_bg_00@04",
                "e002_c030_p310_que_bg_00@05",
                "e002_c030_p310_que_bg_00@06",
            }
        },
        {
            {
                "e002_c030_p310_ans_bg_00@00",
                "",
                ""
            },
            {
                "e002_c030_p310_ans_bg_00@01",
                "",
                ""
            },
            {
                "e002_c030_p310_ans_bg_00@02",
                "e002_c030_p310_ans_bg_00@03",
                ""
            },
            {
                "e002_c030_p310_ans_bg_00@04",
                "e002_c030_p310_ans_bg_00@05",
                "e002_c030_p310_ans_bg_00@06",
            }
        },
        {
            {
                "e002_c030_p310_que_blank@00",
                "",
                ""
            },
            {
                "e002_c030_p310_que_blank@01",
                "",
                ""
            },
            {
                "e002_c030_p310_que_blank@02",
                "e002_c030_p310_que_blank@03",
                ""
            },
            {
                "e002_c030_p310_que_blank@04",
                "e002_c030_p310_que_blank@05",
                "e002_c030_p310_que_blank@06",
            }
        },
        {
            {
                "e002_c030_p310_success_sled",
                "",
                ""
            },
            {
                "e002_c030_p310_success_clap",
                "",
                ""
            },
            {
                "e002_c030_p310_success_glad",
                "e002_c030_p310_success_plane",
                ""
            },
            {
                "e002_c030_p310_success_glass",
                "e002_c030_p310_success_slide",
                "e002_c030_p310_success_blue",
            }
        },
        {
            {
                "e002_c030_p000_snd_sled_n.mp3",
                "",
                ""
            },
            {
                "e002_c030_p000_snd_clap_n.mp3",
                "",
                ""
            },
            {
                "e002_c030_p000_snd_glad_n.mp3",
                "e002_c030_p000_snd_plane_n.mp3",
                ""
            },
            {
                "e002_c030_p000_snd_glass_n.mp3",
                "e002_c030_p000_snd_slide_n.mp3",
                "e002_c030_p000_snd_blue_n.mp3"
            }
        },
        {
            {
                "e002_c030_p000_snd_sl_ed_n.mp3",
                "",
                ""
            },
            {
                "e002_c030_p000_snd_cl_ap_n.mp3",
                "",
                ""
            },
            {
                "e002_c030_p000_snd_gl_ad_n.mp3",
                "e002_c030_p000_snd_pl_ane_n.mp3",
                ""
            },
            {
                "e002_c030_p000_snd_gl_ass_n.mp3",
                "e002_c030_p000_snd_sl_ide_n.mp3",
                "e002_c030_p000_snd_bl_ue_n.mp3"
            }
        },
    };
    
    int correntTags[4][3] =
    {
        {kTagTarget001, 0, 0},
        {0, 0, kTagTarget001},
        {kTagTarget002, kTagTarget001, 0},
        {kTagTarget002, kTagTarget001, kTagTarget003}
    };
    
    
    for (int i = 0; i < 4; i++)
    {
        std::vector<E002_Base_ExampleItem*> *examples = new std::vector<E002_Base_ExampleItem*>();
        
        for (int j = 0; j < 3; j++)
        {
            examples->push_back(new E002_Base_ExampleItem(i, exampleImgName[i][j], "", exampleSndName[i][j], kTagExample001 + j, correntTags[i][j]));
        }
        
        mExamples->push_back(examples);
    }
    
    for (int i = 0; i < 13; i++)
    {
        std::vector<std::vector<std::string>*> *questions = new std::vector<std::vector<std::string>*>();
        
        for (int j = 0; j < 4; j++)
        {
            std::vector<std::string> *question = new std::vector<std::string>();
            
            for (int k = 0; k < 3; k++)
            {
                question->push_back(questionsImgName[i][j][k]);
            }
            
            questions->push_back(question);
        }
        
        mQuestions->push_back(questions);
    }
    
    //memset(exampleName, 0, sizeof(exampleName));
  
    onViewLoad();
}

void E002_C030_P310::onExit()
{
    E002_Base_Question::onExit();
}


void E002_C030_P310::onViewLoad()
{
    E002_Base_Question::onViewLoad();
     
    CJPsdParser::parseToPsdJSON("e002_c030_p310.json", &m_psdDictionary);
    
    setBackground("e002_c030_p310_bg00_00.jpg");
    
    setAnimationFile("e002_c030_p310_flash_cat02_sheets.json", "e002_c030_p310_flash_cat02_animations.json", "MEERKAT");
    setAnimationFile("e002_c030_p310_flash_sun_sheets.json", "e002_c030_p310_flash_sun_animations.json", "ANISON");
    
    mMeerKat = new CJAnimationCharacter(this, "MEERKAT");
    mMeerKat->setLooping("e002_c030_p310_flash_n_cat02_loop");
    mMeerKat->setSuccess("e002_c030_p310_flash_s01_cat02_action", "e002_c030_p310_flash_s02_cat02_action", NULL);
    mMeerKat->setFails("e002_c030_p310_flash_f01_cat02_action", "e002_c030_p310_flash_f02_cat02_action", NULL);
    
    mAnison = new CJAnimationCharacter(this, "ANISON");;
    mAnison->setLooping("e002_c030_p310_flash_n_sun_loop");
    mAnison->setSuccess("e002_c030_p310_flash_s01_sun_loop", "e002_c030_p310_flash_s02_sun_loop", NULL);
    mAnison->setFails("e002_c030_p310_flash_f01_sun_loop", "e002_c030_p310_flash_f02_sun_loop", NULL);
    
    addAnimationCharacter(mMeerKat, mAnison, NULL);
    
    createQuestionBG();
    
    if(m_bIsGuide)
    {
        createGuideDim(kDepth2_questions-2);
    }
    
    animationManagerParseStart();

}

void E002_C030_P310::onViewLoaded()
{
    E002_Base_Question::onViewLoaded();
    
    if (m_nCurrentStageIndex == 1) {
        E002_Base_Navigation::setVisibleButton(false, eNavigationButton_Prev);
    }
 
    CJMultimedia::getInstance()->playBGM(getFilePath("snd","e002_c030_snd_bgm_play03.mp3"), true);

    animationManagerParseComplete();
}

void E002_C030_P310::startFlashAnimation()
{
    createAllAnimations();
    
    mAnison->showLooping();
    mMeerKat->showLooping();
    
    feedbackCharacter = mAnison->getSprite("e002_c030_p110_flash_n_sun_face");
    
    if(m_bIsGuide)
    {
        CJUtils::performSelector(this, callfunc_selector(E002_Base_Question::removeTouchDelegateForGuide), 0.5);
        
        CJUtils::performSelector(this, callfunc_selector(E002_C030_P310::setQuestions),0.3);
    }
    else
    {
        onFirstNarration();
    }
}

void E002_C030_P310::onFirstNarration()
{
    E002_Base_Question::onFirstNarration();
    removeAllAnimationsInDataPool("MEERKAT");

    mFirstNarration = mSndManager->playLetsPlay3Narration(0);
    playAnimation("MEERKAT", "e002_c030_p310_flash_talk_cat02_loop", -1, kDepth5_particle);
    mPlayingGuideNarration = true;
}

void E002_C030_P310::onFirstNarrationEnd()
{
    E002_Base_Question::onFirstNarrationEnd();
    
    showGuideCharacterLooping();
    
    if (getUserDefaultFirstGuide(eGuidePageP310) == false)
    {
        mShowFirstGuide = true;
        setUserDefaultFirstGuide(eGuidePageP310);
        showGuide();
    }
    else
    {
        CJUtils::performSelector(this, callfunc_selector(E002_C030_P310::setQuestions),0.3);
    }
}

void E002_C030_P310::showGuideCharacterLooping()
{
    if(mPlayingGuideNarration)
    {
        removeAllAnimationsInDataPool("MEERKAT");
        mMeerKat->showLooping();
        guideCharacter = mMeerKat->getSprite("e002_c030_p120_flash_sun_n01_cat02_body");
        
        mPlayingGuideNarration = false;
    }
}

void E002_C030_P310::onNarrationFinishedCallback(std::string fileName)
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
    else if(!mReadyQuestion && fileName == mQuestions->at(INDEX_QUE_SOUND)->at(m_nCurrentStageIndex)->at(mCurrentQuestionTheme - 1))
    {
        CJUtils::performSelector(this, callfunc_selector(E002_C030_P310::showExamples), 0.7f);
    }
    else if(fileName == mWrongSound)
    {
        mSndManager->playWrongSfxSnd(13);
        
        runAction(CCSequence::create(CCDelayTime::create(0.5f),
                                     CCCallFuncND::create(this, callfuncND_selector(E002_C030_P310::showWrongCharacterMotion), (void*)0),
                                     NULL));
        
        setTouchEnableBaseLayer(true);
    }
    
    for (int i = 0; i < mQuestions->at(INDEX_QUE_SUCCESS_SND)->at(m_nCurrentStageIndex)->size(); i++)
    {
        if( fileName == mQuestions->at(INDEX_QUE_SUCCESS_SND)->at(m_nCurrentStageIndex)->at(i) && mSuccessCount == mCurrentQuestionTheme)
        {
            runAction(CCSequence::create(CCDelayTime::create(0.3f),
                                         CCCallFuncND::create(this, callfuncND_selector(E002_C030_P310::showSuccessCharacterMotion), (void*)0),
                                         NULL));
            
        }
    }
}

#pragma mark - touch

bool E002_C030_P310::onTouchBegan(CCPoint tp)
{
    if(mReadyQuestion && guideCharacter != NULL && CJUtils::hitTestPoint(guideCharacter, tp, false))
    {
        stopAllNarration();
        onFirstNarration();
        return false;
    }
    else if (mReadyQuestion && feedbackCharacter != NULL && CJUtils::hitTestPoint(feedbackCharacter, tp, false))
    {
        stopAllNarration();
        showGuideCharacterLooping();
        
        mSndManager->playAnisonTouchNarr();
        return false;
    }
    
    if(mReadyQuestion)
    {
        for (int i = kTagQuestion001; i <= kTagQuestion003; i++)
        {
            if(getChildByTag(i) != NULL && CJUtils::hitTestPoint(getChildByTag(i), tp, false))
            {
                showGuideCharacterLooping();
                
                int index = i - kTagQuestion001;
                playQuestionSound(NULL, (void*)index);
                
                getChildByTag(i)->runAction(CCSequence::create(CCScaleBy::create(0.1, 1.2),
                                                               CCScaleBy::create(0.1, 0.8),
                                                               NULL));
                
                if (getChildByTag(i+12) != NULL) {
                    getChildByTag(i+12)->runAction(CCSequence::create(CCScaleBy::create(0.1, 1.2),
                                                                      CCScaleBy::create(0.1, 0.8),
                                                                      NULL));
                }
            }
        }
        
        for (int i = kTagQueText001; i <= kTagQueText003; i++)
        {
            if(getChildByTag(i) != NULL && CJUtils::hitTestPoint(getChildByTag(i), tp, false))
            {
                showGuideCharacterLooping();
                
                int index = i - kTagQueText001;
                playQuestionSound(NULL, (void*)index);
                getChildByTag(i)->runAction(CCSequence::create(CCScaleBy::create(0.1, 1.2),
                                                               CCScaleBy::create(0.1, 0.8),
                                                               NULL));
                
                if (getChildByTag(i-12) != NULL)
                {
                    getChildByTag(i-12)->runAction(CCSequence::create(CCScaleBy::create(0.1, 1.2),
                                                                      CCScaleBy::create(0.1, 0.8),
                                                                      NULL));
                }
            }
        }
        
        for (int i = kTagBlank001; i <= kTagBlank003; i++)
        {
            if(getChildByTag(i) != NULL && CJUtils::hitTestPoint(getChildByTag(i), tp, false))
            {
                showGuideCharacterLooping();
                
                int index = i - kTagBlank001;
                playQuestionSound(NULL, (void*)index);
                
                if (getChildByTag(i+6) != NULL)
                {
                    getChildByTag(i+6)->runAction(CCSequence::create(CCScaleBy::create(0.1, 1.2),
                                                                     CCScaleBy::create(0.1, 0.8),
                                                                     NULL));
                }
                
                if (getChildByTag(i-6) != NULL)
                {
                    getChildByTag(i-6)->runAction(CCSequence::create(CCScaleBy::create(0.1, 1.2),
                                                                     CCScaleBy::create(0.1, 0.8),
                                                                     NULL));
                }
            }
        }
        
        for (int i = kTagExample001; i <= kTagExample003; i++)
        {
            CJSprite* sp = (CJSprite*)getChildByTag(i);

            if(getChildByTag(i) != NULL && CJUtils::hitTestPoint(sp , tp, false))
            {

                showGuideCharacterLooping();
                
                playExampleNarrationRepeat(mExamples->at(m_nCurrentStageIndex)->at(i-kTagExample001)->getSoundPath());
                
                mExampleSelectIndex = i - kTagExample001;
                
                m_touchingExampleSp = GET_SELECTED_ITEM->getItemSprite();
                m_touchingExampleSp->setScale(1.2f);
                m_touchingExampleSp->setZOrder(kDepth6_dimmed);
                
                mTouchedPointGab = ccpSub(sp->getPosition(), tp);
                
                if(m_bIsGuide)
                {
                    showHand(NULL, 1);
                    m_touchingExampleSp->runAction(CCMoveTo::create(0.7f, getChildByTag(kTagBlank001)->getPosition()));
                }
                
                return true;
            }
        }
    }
    
    return false;
}

void E002_C030_P310::onTouchMoved(CCPoint tp)
{
    if(m_touchingExampleSp != NULL)
    {
        m_touchingExampleSp->setPosition(ccp(tp.x + mTouchedPointGab.x, tp.y + mTouchedPointGab.y));
    }
}

void E002_C030_P310::onTouchEnded(CCPoint tp)
{
    stopExampleNarrationRepeat();

    for (int i = 0; i < mTargets->size(); i++)
    {
        if (mTargets->at(i) != NULL && CJUtils::hitTestPoint(m_touchingExampleSp, mTargets->at(i)->getPosition(), false))
        {
            setTouchDisalbeBaseLayer();
            intoTarget(m_touchingExampleSp, mTargets->at(i));
            return;
        }
    }
    
    m_touchingExampleSp->runAction(CCSpawn::create(CCEaseBackOut::create(CCMoveTo::create(0.1, GET_SELECTED_ITEM->getOriginalPosition())),
                                                   CCScaleTo::create(0.1, 1.0),
                                                   NULL));
    

}

void E002_C030_P310::intoTarget(CJSprite* sp, CCNode *target)
{
    for (int i = 0 ; i < mCompleteTargetTags->size(); i++)
    {
        if(mCompleteTargetTags->at(i) == target->getTag())
        {
            m_touchingExampleSp->runAction(CCSpawn::create(CCEaseBackOut::create(CCMoveTo::create(0.1, GET_SELECTED_ITEM->getOriginalPosition())),
                                                           CCScaleTo::create(0.1, 1.0),
                                                           NULL));
            return;
        }
    }
     
    sp->runAction(CCSequence::create(CCSpawn::create(CCEaseSineInOut::create(CCMoveTo::create(0.2, target->getPosition())),
                                                     CCScaleTo::create(0.2, 1.0f),
                                                     NULL),
                                     CCDelayTime::create(0.5f),
                                     CCCallFuncND::create(this, callfuncND_selector(E002_C030_P310::checkAnswer),(void*)target->getTag()),
                                     NULL));
}

void E002_C030_P310::checkAnswer(CCNode *node, int targetTag)
{
    //setTouchEnableBaseLayer();
    CCLog("targetTag %d", targetTag);
    CCLog("GET_SELECTED_ITEM->getCorrectTag() %d", GET_SELECTED_ITEM->getCorrectTag() );
    
    if(targetTag ==  GET_SELECTED_ITEM->getCorrectTag())
    {
        mCompleteTargetTags->push_back(targetTag);
        
        mSuccessCount++;
        onSuccesses(node, targetTag);
    }
    else
    {
        node->runAction(CCSequence::create(CCDelayTime::create(0.1f),
                                           CCCallFuncND::create(this, callfuncND_selector(E002_C030_P310::onFails), (void*)targetTag),
                                           NULL));
    }
}

#pragma mark - feedback event

void E002_C030_P310::onExamplesTouched(int index)
{
    E002_Base_Question::onExamplesTouched(index);
}


void E002_C030_P310::onSuccesses(CCNode *node, int tag)
{
    CCLog("onSuccess");
    
    mSndManager->playSuccessSfxSnd(13);
    
    if(mCurrentQuestionTheme == ONE_QUETION_THEME)
    {
        for (int i = 0; i < GET_EXAMPLES->size(); i++)
        {
            if(GET_EXAMPLES->at(i)->getItemTag() != node->getTag() )
            {
                GET_EXAMPLES->at(i)->getItemSprite()->runAction(CCSequence::create(CCMoveBy::create(0.3f, ccp(0, -200)),
                                                                                   CCCallFuncN::create(this, callfuncN_selector(CJLayer::removeChild)),
                                                                                   NULL));
            }
        }
    }

    node->runAction(CCSequence::create(CCDelayTime::create(0.5f),
                                       CCCallFuncND::create(this, callfuncND_selector(E002_C030_P310::showSuccessTexture), (void*)tag),
                                       NULL));
}

void E002_C030_P310::showSuccessTexture(CCNode *node, int tag)
{
    CCLog("showSuccessTexture");
    removeTexture(node->getTag());
    
    int index;
    
    if(mCurrentQuestionTheme < TWO_QUETION_THEME)
    {
        index = 0;
    }
    else
    {
        index = tag - kTagTarget001;
    }
    
    CCLog("tag kTagTarget001 = %d, %d", tag, kTagTarget001);
    
    speakNarration(NULL, mQuestions->at(INDEX_QUE_SUCCESS_SND)->at(m_nCurrentStageIndex)->at(index).c_str());
    
    CJSprite *ansShadow = CJPsdParser::getPsdSprite(mQuestions->at(INDEX_ANS_SHADOW)->at(m_nCurrentStageIndex)->at(index), m_psdDictionary);
    addChild(ansShadow, kDepth3_examples, kTagAnsShadow001+index);
        
    CJSprite *ansBG = CJPsdParser::getPsdSprite(mQuestions->at(INDEX_ANS_BG)->at(m_nCurrentStageIndex)->at(index), m_psdDictionary);
    addChild(ansBG, kDepth3_examples, kTagAnswerBG001+index);
        
    CJSprite *ansText = CJPsdParser::getPsdSprite(mQuestions->at(INDEX_ANS_TEXT)->at(m_nCurrentStageIndex)->at(index), m_psdDictionary);
    addChild(ansText, kDepth3_examples, kTagAnswerText001+index);
        
    ansText->runAction(CCSequence::create(CCScaleTo::create(0.3f, 1.2),
                                          CCScaleTo::create(0.3f, 1.0f),
                                          CCDelayTime::create(0.6),
                                          CCCallFuncN::create(this, callfuncN_selector(CJLayer::removeChild)),
                                          NULL));
        
    getChildByTag(kTagQueText001+index)->runAction(CCSequence::create(CCDelayTime::create(0.6f),
                                                                      CCScaleTo::create(0.3f, 1.2),
                                                                      CCScaleTo::create(0.3f, 1.0f),
                                                                      CCCallFuncN::create(this, callfuncN_selector(CJLayer::removeChild)),
                                                                      NULL));
    runAction(CCSequence::create(CCDelayTime::create(0.6f),
                                 CCCallFuncND::create(this, callfuncND_selector(E002_C030_P310::showSuccessText),(void*)index),
                                 NULL));

}

void E002_C030_P310::removeTexture(int tag)
{
    for (int i = 0 ; i < mTargets->size(); i++)
    {
        for (int j = 0; j < mCompleteTargetTags->size(); j++)
        {
            if(mTargets->at(i) != NULL && mTargets->at(i)->getTag() == mCompleteTargetTags->at(j))
            {
                removeChildByTag(mTargets->at(i)->getTag()+3);
                removeChild(mTargets->at(i));
                mTargets->at(i) = NULL;
            }
        }
    }
    
    for (int i = 0; i < GET_EXAMPLES->size(); i++)
    {
        if(GET_EXAMPLES->at(i)->getItemTag() == tag )
        {
            removeChild(GET_EXAMPLES->at(i)->getItemSprite());
        }
    }
}

void E002_C030_P310::playWheel()
{ 
    mSndManager->playLetsPlay3Effect(1);
    
    for (int i = kTagAnsShadow001; i <= kTagAnsShadow003; i++)
    {
        if(getChildByTag(i) != NULL)
        {
            getChildByTag(i)->runAction(CCRepeatForever::create(CCRotateTo::create(2.0f, 960)));
        }
    }
    

    for (int i = kTagAnswerBG001; i <= kTagAnswerBG003; i++)
    {
        if(getChildByTag(i) != NULL)
        {
            getChildByTag(i)->runAction(CCRepeatForever::create(CCRotateTo::create(2.0f, 960)));
        }
    }
    
    for (int i = kTagQueShadow001; i <= kTagQueShadow003; i++)
    {
        if(getChildByTag(i) != NULL)
        {
            getChildByTag(i)->runAction(CCRepeatForever::create(CCRotateTo::create(2.0f, -960)));
        }
    }
    
    for (int i = kTagQueBG001; i <= kTagQueBG003; i++)
    {
        if(getChildByTag(i) != NULL)
        {
            getChildByTag(i)->runAction(CCRepeatForever::create(CCRotateTo::create(2.0f, -960)));
        }
    }
    
}

void E002_C030_P310::showSuccessText(CCNode *node, int index)
{

    CJSprite *successText = CJPsdParser::getPsdSprite(mQuestions->at(INDEX_SUC_TEXT)->at(m_nCurrentStageIndex)->at(index), m_psdDictionary);
    successText->setPosition(ccp(successText->getPositionX(), successText->getPositionY()-200));
    
    addChild(successText, kDepth2_questions+4, kTagSuccessText001+index);
    
    CCRepeat *repeat = CCRepeat::create(CCSequence::create(CCMoveBy::create(0.5f, ccp(0, 10)),
                                                           CCMoveBy::create(0.5f, ccp(0, -10)),
                                                           NULL),
                                        -1);
    
    successText->runAction(CCSequence::create(CCDelayTime::create(0.3),
                                              CCEaseBackOut::create(CCMoveBy::create(1.0f, ccp(0, 200))),
                                              repeat,
                                              NULL));
    
    getChildByTag(kTagQuestion001+index)->runAction(CCSequence::create(CCDelayTime::create(0.3f),
                                                                       CCMoveBy::create(0.5f, ccp(0, successText->getContentSize().height)),
                                                                       NULL));
    
    if((m_nCurrentStageIndex == 2 && mSuccessCount < 2) || (m_nCurrentStageIndex == 3 && mSuccessCount < 3))
    {
        setTouchEnableBaseLayer(true);
    }
    else
    {
        CJUtils::performSelector(this, callfunc_selector(E002_C030_P310::playWheel), 1.0f);
    }
}

void E002_C030_P310::onFails(CCNode *node, int tag)
{
    mFailCount++;
    
    playWrongSound(tag);
    
    node->runAction(CCSequence::create(CCDelayTime::create(0.5f),
                                       CCEaseSineOut::create(CCScaleTo::create(0.2, 1.0)),
                                       CCEaseBackOut::create(CCMoveTo::create(0.2, GET_SELECTED_ITEM->getOriginalPosition())),
                                       NULL));

}

void E002_C030_P310::playWrongSound(int tag)
{
    if (m_nCurrentStageIndex == 1)
    {
        if (m_touchingExampleSp->getTag() == kTagExample001)
        {
            mWrongSound = "e002_c030_p000_snd_flap_n.mp3";
        }
        else
        {
             mWrongSound = "e002_c030_p000_snd_glap_n.mp3";
        }
    }
    else if(m_nCurrentStageIndex == 2)
    {
        switch (tag) {
            case kTagTarget001:
                mWrongSound = "e002_c030_p000_snd_plad_n.mp3";
                break;
            case kTagTarget002:
                mWrongSound = "e002_c030_p000_snd_glane_n.mp3";
                break;
            default:
                break;
        }
    }
    else if(m_nCurrentStageIndex == 3)
    {
        if (m_touchingExampleSp->getTag() == kTagExample001)
        {
            switch (tag) {
                case kTagTarget001:
                    mWrongSound = "e002_c030_p000_snd_slass.mp3";
                    break;
                case kTagTarget003:
                    mWrongSound = "e002_c030_p000_snd_slue_n.mp3";
                    break;
                default:
                    break;
            }
        }
        else if (m_touchingExampleSp->getTag() == kTagExample002)
        {
            switch (tag) {
                case kTagTarget002:
                    mWrongSound = "e002_c030_p000_snd_glide_n.mp3";
                    break;
                case kTagTarget003:
                    mWrongSound = "e002_c030_p000_snd_glue_n.mp3";
                    break;
                default:
                    break;
            }
        }
        else if (m_touchingExampleSp->getTag() == kTagExample003)
        {
            switch (tag) {
                case kTagTarget001:
                    mWrongSound = "e002_c030_p000_snd_blass_n.mp3";
                    break;
                case kTagTarget002:
                    mWrongSound = "e002_c030_p000_snd_blide_n.mp3";
                    break;
                default:
                    break;
            }
        }
    }
    
    playNarration(mWrongSound);
}

void E002_C030_P310::onComplete()
{
    E002_Base_Question::onComplete();

}

#pragma mark - user function

void E002_C030_P310::setQuestions()
{
    CCLog("setQuestion");
    //if(mCompleteTargetTags != NULL)
    //    delete mCompleteTargetTags;
    
    if(m_nCurrentStageIndex == 1)
    {
        mCurrentQuestionTheme = ONE_QUETION_THEME;
    }
    else if(m_nCurrentStageIndex == 2)
    {
        mCurrentQuestionTheme = TWO_QUETION_THEME;
    }
    else if(m_nCurrentStageIndex == 3)
    {
        mCurrentQuestionTheme = THREE_QUETION_THEME;
    }
    
    resetValue();
    stopAllActions();
    showGuideCharacterLooping();
 
    mCompleteTargetTags = new std::vector<int>();
    
    float delay = 0.f;
    
    for (int i = 0; i < mCurrentQuestionTheme; i++)
    {
        CJSprite *question = CJPsdParser::getPsdSprite(mQuestions->at(INDEX_QUESTION)->at(m_nCurrentStageIndex)->at(i), m_psdDictionary);
        question->setPosition(ccp(question->getPositionX(), question->getPositionY()-200));
        
        addChild(question, kDepth2_questions+3, kTagQuestion001 + i);
        
        CJSprite *light = CJPsdParser::getPsdSprite(mQuestions->at(INDEX_LIGHT)->at(m_nCurrentStageIndex)->at(i), m_psdDictionary);
        light->setScale(0);
        light->setAnchorPointWithoutPosition(ccp(0.5, 0));
        addChild(light, kDepth2_questions+2, kTagLight001 + i);
        
        CJSprite *queText = CJPsdParser::getPsdSprite(mQuestions->at(INDEX_QUE_TEXT)->at(m_nCurrentStageIndex)->at(i), m_psdDictionary);
        queText->setScale(0);
        addChild(queText, kDepth2_questions+7, kTagQueText001 + i);
            
        showQuestion(i, queText, light, question, delay);
        
        delay += 1.5f;
    }
    
    createTarget();
    
}

void E002_C030_P310::setReadyQuestion(CCNode* node, bool isReady)
{
    if (isReady)
    {
        if (m_bIsGuide)
        {
            mReadyQuestion = isReady;
            showHand(NULL, 0);
            return;
        }
        
        setTouchEnableBaseLayer();
    }
    
    mReadyQuestion = isReady;
}

void E002_C030_P310::showQuestion(int index, CJSprite *queText, CJSprite *light, CJSprite *question, float delay)
{
    queText->runAction(CCSequence::create(CCDelayTime::create(delay),
                                          CCCallFuncND::create(this, callfuncND_selector(E002_C030_P310::playQuestionSound), (void*)index),
                                          CCEaseBackOut::create(CCScaleTo::create(1.0f, 1.0)),
                                          NULL));
    
    light->runAction(CCSequence::create(CCDelayTime::create(delay),
                                        CCScaleTo::create(0.5f, 1.0),
                                        NULL));
    
    CCRepeat *repeat = CCRepeat::create(CCSequence::create(CCMoveBy::create(0.5f, ccp(0, 10)),
                                                           CCMoveBy::create(0.5f, ccp(0, -10)),
                                                           NULL),
                                        -1);
    
    question->runAction(CCSequence::create(CCDelayTime::create(delay),
                                           CCEaseBackOut::create(CCMoveBy::create(1.0f, ccp(0, 200))),
                                           repeat,
                                           NULL));
}

void E002_C030_P310::showExamples()
{
    for (int i = 0; i<3; i++)
    {
        float delay = 1.0f;
        
        E002_Base_ExampleItem *item = GET_EXAMPLES->at(i);
        
        if(item->getImgPath() != "")
        {
            item->setOriginalPosition(CJPsdParser::getPsdPosition(item->getImgPath(), m_psdDictionary));
            
            item->setItemSprite(CJPsdParser::getPsdSprite(item->getImgPath(), m_psdDictionary));
            
            item->getItemSprite()->setPositionY(-160);
            addChild(item->getItemSprite(), kDepth3_examples, kTagExample001 + i);
            
            delay *= i;
            
            if (i == 2)
            {
                item->getItemSprite()->runAction(CCSequence::create(CCDelayTime::create(delay),
                                                                    CCCallFuncND::create(this, callfuncND_selector(E002_C030_P310::playAppearanceExamplesSound), (void*)i),
                                                                    CCEaseBackOut::create(CCMoveTo::create(0.3f, item->getOriginalPosition())),
                                                                    CCCallFuncND::create(this, callfuncND_selector(E002_C030_P310::setReadyQuestion), (void*)true),
                                                                    NULL));
            }
            else
            {
                item->getItemSprite()->runAction(CCSequence::create(CCDelayTime::create(delay),
                                                                    CCCallFuncND::create(this, callfuncND_selector(E002_C030_P310::playAppearanceExamplesSound), (void*)i),
                                                                    CCEaseBackOut::create(CCMoveTo::create(0.3f, item->getOriginalPosition())),
                                                                    NULL));
            }
        }
        else
        {
            runAction(CCSequence::create(CCDelayTime::create(delay),
                                         CCCallFuncND::create(this, callfuncND_selector(E002_C030_P310::setReadyQuestion), (void*)true),
                                         NULL));
        }
    }
}

void E002_C030_P310::resetValue()
{
    if (m_nCurrentStageIndex > 1)
    {
        E002_Base_Navigation::setVisibleButton(true, eNavigationButton_Prev);
    }
    else if(m_nCurrentStageIndex == 1)
    {
        E002_Base_Navigation::setVisibleButton(false, eNavigationButton_Prev);
    }
    
    mSuccessCount = 0;
    mFailCount = 0;
    
    showGuideCharacterLooping();
    removeChild(m_touchingExampleSp);
    setReadyQuestion(NULL, false);
    
    for (int i = kTagQuestion001; i <= kTagSuccessText003; i++)
    {
        if(getChildByTag(i) != NULL)
        {
            removeChildByTag(i);
        }
    }
    
    for (int i = kTagExample001; i <= kTagExample003; i++)
    {
        if(getChildByTag(i) != NULL)
            removeChildByTag(i);
    }
    
    createQuestionBG();
}

#pragma mark - sound & narration
void E002_C030_P310::playQuestionSound(CCNode* node, void* index)
{
    CCLog("playQuestionSound %s", mQuestions->at(INDEX_QUE_SOUND)->at(m_nCurrentStageIndex)->at((int)index).c_str());
    speakNarration(NULL, mQuestions->at(INDEX_QUE_SOUND)->at(m_nCurrentStageIndex)->at((int)index).c_str());
}

void E002_C030_P310::playAppearanceExamplesSound(CCNode* sender, void* index)
{
    mSndManager->playLetsPlay3Effect(0);
    speakNarration(NULL, mExamples->at(m_nCurrentStageIndex)->at((int)index)->getSoundPath().c_str());
}

#pragma mark - user function

void E002_C030_P310::speakNarration(CCNode* node, const char* fileName)
{
    stopAllNarration();
    playNarration(fileName); 
}


#pragma mark - navigation delegate

void E002_C030_P310::onTouchedNavigationButtonAtIndex()
{
    E002_Base_Question::onTouchedNavigationButtonAtIndex();
    
    E002_C030_P000_Index* _indexClass = E002_C030_P000_Index::create();
    _indexClass->init();
    _indexClass->setIndexDelegate(this);
    _indexClass->showIndex(this, _indexClass);
    addChild(_indexClass, kDepth11_Index);
}

void E002_C030_P310::onTouchedNavigationButtonAtInfo()
{
    E002_Base_Question::onTouchedNavigationButtonAtInfo();
     
    showGuide();
}

void E002_C030_P310::onTouchedNavigationButtonAtPrev()
{
    E002_Base_Question::onTouchedNavigationButtonAtPrev();
    if (m_nCurrentStageIndex > 0) {
        m_nCurrentStageIndex--;
        setQuestions();
    }
}

void E002_C030_P310::onTouchedNavigationButtonAtNext()
{
    E002_Base_Question::onTouchedNavigationButtonAtNext();
    
    if (m_nCurrentStageIndex < m_nMaxStageCount-1)
    {
        m_nCurrentStageIndex++;
        setQuestions();
    }
    else
    {
        //replayceScene
        replaceSceneTransitionFadeOut(E002_C030_P320);
    }
    
}

void E002_C030_P310::onTouchedNavigationButtonAtReward()
{
    showLetPlay3RewardPopup(NULL, m_nCurrentStageIndex - 1);
}

void E002_C030_P310::onTouchedNavigationButtonAtClose()
{
    E002_Base_Question::onTouchedNavigationButtonAtClose();
    
}

void E002_C030_P310::OnLastFrame(CJAnimation* pAnimation)
{
    E002_Base_Question::OnLastFrame(pAnimation);
    
    for (int i = 0; i < mMeerKat->getSuccessKeys()->size(); i++)
    {
        if(pAnimation->getName() == mMeerKat->getSuccessKeys()->at(i))
        {
            if(m_bIsGuide)
            {
                ((E002_Base_Question*)getParent())->removeGuide();
                return;
            }
            
            //CJUtils::performSelector(this, callfuncND_selector(E002_C030_P310::playEffect), (void*)3, 0.5f);
            
            int index = m_nCurrentStageIndex - 1;
            CJUtils::performSelector(this, callfuncND_selector(E002_C030_P310::showLetPlay3RewardItem),(void*) index, 0.5f);
        }
    }
}

void E002_C030_P310::completeToGetRewardItem()
{
    E002_Base_Question::completeToGetRewardItem();

    CJUtils::performSelector(this, callfunc_selector(E002_C030_P310::onTouchedNavigationButtonAtNext), 0.5f);
    
}

#pragma mark - sprite create

void E002_C030_P310::createQuestionBG()
{
    CCLog("createQuestionBG :: mCurrentQuestion theme =  %d", mCurrentQuestionTheme);
    
    if(getChildByTag(kTagBack) != NULL)
    {
        removeChildByTag(kTagBack);
        removeChildByTag(kTagFront);
    }
    
    if(mCurrentQuestionTheme == ONE_QUETION_THEME)
    {
        CJSprite *back = CJPsdParser::getPsdSprite("e002_c030_p310_que00_back", m_psdDictionary);
        addChild(back, kDepth0_backImage, kTagBack);
        
        CJSprite *front = CJPsdParser::getPsdSprite("e002_c030_p310_que00_front", m_psdDictionary);
        addChild(front, kDepth2_questions+5, kTagFront);
    }
    else if(mCurrentQuestionTheme == TWO_QUETION_THEME)
    {
        CJSprite *back = CJPsdParser::getPsdSprite("e002_c030_p310_que02_back", m_psdDictionary);
        addChild(back, kDepth0_backImage, kTagBack);
        
        CJSprite *front = CJPsdParser::getPsdSprite("e002_c030_p310_que02_front", m_psdDictionary);
        addChild(front, kDepth2_questions+5, kTagFront);
    }
    else
    {
        CJSprite *back = CJPsdParser::getPsdSprite("e002_c030_p310_que03_back", m_psdDictionary);
        addChild(back, kDepth0_backImage, kTagBack);
        
        CJSprite *front = CJPsdParser::getPsdSprite("e002_c030_p310_que03_front", m_psdDictionary);
        addChild(front, kDepth2_questions+5, kTagFront);
    }
    
    for (int i = 0; i < mCurrentQuestionTheme; i++)
    {
        CJSprite *queBlank = CJPsdParser::getPsdSprite(mQuestions->at(INDEX_QUE_BLANK)->at(m_nCurrentStageIndex)->at(i), m_psdDictionary);
        addChild(queBlank, kDepth2_questions+6, kTagBlank001+i);
        
        CJSprite *queShadow = CJPsdParser::getPsdSprite(mQuestions->at(INDEX_QUE_SHADOW)->at(m_nCurrentStageIndex)->at(i), m_psdDictionary);
        addChild(queShadow, kDepth2_questions+6, kTagQueShadow001+i);
        
        CJSprite *queBG = CJPsdParser::getPsdSprite(mQuestions->at(INDEX_QUE_BG)->at(m_nCurrentStageIndex)->at(i), m_psdDictionary);
        addChild(queBG, kDepth2_questions+6, kTagQueBG001+i);
    }
}

void E002_C030_P310::createTarget()
{
    mTargets = new std::vector<CJSprite*>();
    
    for (int i = 0; i < 3; i++)
    {
        if (mQuestions->at(INDEX_TARGET)->at(m_nCurrentStageIndex)->at(i) != "")
        {
            CJSprite *targetSprite =CJPsdParser::getPsdSprite(mQuestions->at(INDEX_TARGET)->at(m_nCurrentStageIndex)->at(i), m_psdDictionary);
            targetSprite->setVisible(false);
            addChild(targetSprite, kDepth3_examples, kTagTarget001 + i);
            
            mTargets->push_back(targetSprite);
        }
    }
}

void E002_C030_P310::showSuccessCharacterMotion(CCNode *node, int index)
{
    if(index == 0)
    {
        if (m_nCurrentStageIndex%2 == 0)
        {
            mSuccessNarrationSnd = mSndManager->playMeercatSuccessNarr(3);
        }
        else
        {
            mSuccessNarrationSnd = mSndManager->playMeercatSuccessNarr(16);
        }
        
        mAnison->showSuccess();
        mMeerKat->showSuccess();
    }
    else
    {
        if (m_nCurrentStageIndex%2 == 0)
        {
            mSndManager->playAnisonSuccessNarr(24);
        }
        else
        {
            mSndManager->playAnisonSuccessNarr(25);
        }
    }
}

void E002_C030_P310::showWrongCharacterMotion(CCNode *node, int index)
{
    if(index == 0)
    {
        if (m_nCurrentStageIndex%2 == 0)
        {
            if(mFailCount%2 == 0)
            {
                mWrongNarrationSnd = mSndManager->playMeercatWrongNarr(6);
            }
            else
            {
                mWrongNarrationSnd = mSndManager->playMeercatWrongNarr(9);
            }
        }
        else
        {
            if(mFailCount%2 == 0)
            {
                mWrongNarrationSnd = mSndManager->playMeercatWrongNarr(9);
            }
            else
            {
                mWrongNarrationSnd = mSndManager->playMeercatWrongNarr(6);
            }
        }
        
        mMeerKat->showFails();
        mAnison->showFails();
    }
    else
    {
        if (m_nCurrentStageIndex%2 == 0)
        {
            if(mFailCount%2 == 0)
            {
                mSndManager->playAnisonWrongNarr(3);
            }
            else
            {
                mSndManager->playAnisonWrongNarr(4);
            }
        }
        else
        {
            if(mFailCount%2 == 0)
            {
                mSndManager->playAnisonWrongNarr(4);
            }
            else
            {
                mSndManager->playAnisonWrongNarr(3);
            }
        }
    }
}

void E002_C030_P310::playEffect(CCNode *node, int index)
{
    mSndManager->playLetsPlay3Effect(index);
}

void E002_C030_P310::showGuide()
{
    E002_Base_Question::showGuide();
    
    m_Guide = E002_C030_P310::create();
    m_Guide->init();
    m_Guide->setGuide(true);
    addChild(m_Guide, kDepth10_guide);
    
    std::vector<CCPoint> *guideHandPosition = new std::vector<CCPoint>();
    
    guideHandPosition->push_back(CJPsdParser::getPsdPosition("e002_common_img_guide_hand@00", m_psdDictionary));
    guideHandPosition->push_back(CJPsdParser::getPsdPosition("e002_common_img_guide_hand@01", m_psdDictionary));
    
    m_Guide->setGuideHandPosition(guideHandPosition);
}

void E002_C030_P310::removeGuide()
{
    E002_Base_Question::removeGuide();
    removeChild(m_Guide);
    
}

void E002_C030_P310::completeToMoveHand(CCNode *node, int index)
{
    switch (index) {
        case 0:
            onTouchBegan(getChildByTag(kTagExample001)->getPosition());
            break;
        case 1:
            onTouchEnded(getChildByTag(kTagBlank001)->getPosition());
            break;
        default:
            break;
    }
}

void E002_C030_P310::completeFirstGuide()
{
    CJUtils::performSelector(this, callfunc_selector(E002_C030_P310::setQuestions),0.3);
}