

#include "E002_C030_P110.h"
#include "E002_C030_P000_Index.h"
#include "E002_C030_P130.h"
//#include "E002_C030_P110_Guide.h"

enum
{
    kTagLeftWall = 200,
    kTagRightWall,
    kTagLeftWall2,
    kTagRightWall2,
    
    kTagExample001 = 250,
    kTagExample002,
    kTagExample003,
    kTagExample004,
    
    kTagCouple000,
    kTagCouple001,
    
};

E002_C030_P110::E002_C030_P110()
{
    mExamples = new std::vector<std::vector<E002_Base_ExampleItem*>*>();
    mSeqImgs = new std::vector<std::vector<std::vector<std::string>*>*>();
    mSelectTag = new std::vector<int>();
    mCompleteTag = new std::vector<int>();
    
    m_touchingExampleSp = NULL;
    mSndManager = new E002_C030_SoundManager();
}

E002_C030_P110::~E002_C030_P110()
{
    CC_SAFE_DELETE(mExamples);
}

#pragma mark - init

bool E002_C030_P110::init()
{
    if (!E002_Base_Question::init()) {
        return false;
    }
    
    m_nMaxStageCount = 6;
    m_nCurrentStageIndex = 1;
    mSelectedCount = 0;
    mSuccessCount = 0;
    mCompleteQuestion = false;
    mPlayingGuideNarration = false;
    
    return true;
}

void E002_C030_P110::onEnter()
{
    E002_Base_Question::onEnter();
    
    const char* exampleImgName[6][4] =
    {
        {
            "e002_c030_p110_q00_00_n",
            "e002_c030_p110_q00_01_n",
            "e002_c030_p110_q00_02_n",
            "e002_c030_p110_q00_03_n"
        },
        {
            "e002_c030_p110_q01_00_n",
            "e002_c030_p110_q01_01_n",
            "e002_c030_p110_q01_02_n",
            "e002_c030_p110_q01_03_n"
        },
        {
            "e002_c030_p110_q02_00_n",
            "e002_c030_p110_q02_01_n",
            "e002_c030_p110_q02_02_n",
            "e002_c030_p110_q02_03_n"
        },
        {
            "e002_c030_p110_q03_00_n",
            "e002_c030_p110_q03_01_n",
            "e002_c030_p110_q03_02_n",
            "e002_c030_p110_q03_03_n"
        },
        {
            "e002_c030_p110_q04_00_n",
            "e002_c030_p110_q04_01_n",
            "e002_c030_p110_q04_02_n",
            "e002_c030_p110_q04_03_n"
        },
        {
            "e002_c030_p110_q05_00_n",
            "e002_c030_p110_q05_01_n",
            "e002_c030_p110_q05_02_n",
            "e002_c030_p110_q05_03_n"
        },
    };
    
    const char* exampleSelectImgName[6][4] =
    {
        {
            "e002_c030_p110_q00_00_s",
            "e002_c030_p110_q00_01_s",
            "e002_c030_p110_q00_02_s",
            "e002_c030_p110_q00_03_s"
        },
        {
            "e002_c030_p110_q01_00_s",
            "e002_c030_p110_q01_01_s",
            "e002_c030_p110_q01_02_s",
            "e002_c030_p110_q01_03_s"
        },
        {
            "e002_c030_p110_q02_00_s",
            "e002_c030_p110_q02_01_s",
            "e002_c030_p110_q02_02_s",
            "e002_c030_p110_q02_03_s"
        },
        {
            "e002_c030_p110_q03_00_s",
            "e002_c030_p110_q03_01_s",
            "e002_c030_p110_q03_02_s",
            "e002_c030_p110_q03_03_s"
        },
        {
            "e002_c030_p110_q04_00_s",
            "e002_c030_p110_q04_01_s",
            "e002_c030_p110_q04_02_s",
            "e002_c030_p110_q04_03_s"
        },
        {
            "e002_c030_p110_q05_00_s",
            "e002_c030_p110_q05_01_s",
            "e002_c030_p110_q05_02_s",
            "e002_c030_p110_q05_03_s"
        }
    };
    
    const char* exampleSeqImgName[6][4][2] =
    {
        {
            {
                "e002_c030_p110_q00_00_seq00.png",
                "e002_c030_p110_q00_00_seq01.png",
            },
            {
                "e002_c030_p110_q00_01_seq00.png",
                "e002_c030_p110_q00_01_seq01.png",
            },
            {
                "e002_c030_p110_q00_02_seq00.png",
                "e002_c030_p110_q00_02_seq01.png",
            },
            {
                "e002_c030_p110_q00_03_seq00.png",
                "e002_c030_p110_q00_03_seq01.png"
            }
        },
        {
            {
                "e002_c030_p110_q01_00_seq00.png",
                "e002_c030_p110_q01_00_seq01.png",
            },
            {
                "e002_c030_p110_q01_01_seq00.png",
                "e002_c030_p110_q01_01_seq01.png",
            },
            {
                "e002_c030_p110_q01_02_seq00.png",
                "e002_c030_p110_q01_02_seq01.png",
            },
            {
                "e002_c030_p110_q01_03_seq00.png",
                "e002_c030_p110_q01_03_seq01.png"
            }
        },
        {
            {
                "e002_c030_p110_q02_00_seq00.png",
                "e002_c030_p110_q02_00_seq01.png",
            },
            {
                "e002_c030_p110_q02_01_seq00.png",
                "e002_c030_p110_q02_01_seq01.png",
            },
            {
                "e002_c030_p110_q02_02_seq00.png",
                "e002_c030_p110_q02_02_seq01.png",
            },
            {
                "e002_c030_p110_q02_03_seq00.png",
                "e002_c030_p110_q02_03_seq01.png"
            }
        },
        {
            {
                "e002_c030_p110_q03_00_seq00.png",
                "e002_c030_p110_q03_00_seq01.png",
            },
            {
                "e002_c030_p110_q03_01_seq00.png",
                "e002_c030_p110_q03_01_seq01.png",
            },
            {
                "e002_c030_p110_q03_02_seq00.png",
                "e002_c030_p110_q03_02_seq01.png",
            },
            {
                "e002_c030_p110_q03_03_seq00.png",
                "e002_c030_p110_q03_03_seq01.png"
            }
        },
        {
            {
                "e002_c030_p110_q04_00_seq00.png",
                "e002_c030_p110_q04_00_seq01.png",
            },
            {
                "e002_c030_p110_q04_01_seq00.png",
                "e002_c030_p110_q04_01_seq01.png",
            },
            {
                "e002_c030_p110_q04_02_seq00.png",
                "e002_c030_p110_q04_02_seq01.png",
            },
            {
                "e002_c030_p110_q04_03_seq00.png",
                "e002_c030_p110_q04_03_seq01.png"
            }
        },
        {
            {
                "e002_c030_p110_q05_00_seq00.png",
                "e002_c030_p110_q05_00_seq01.png",
            },
            {
                "e002_c030_p110_q05_01_seq00.png",
                "e002_c030_p110_q05_01_seq01.png",
            },
            {
                "e002_c030_p110_q05_02_seq00.png",
                "e002_c030_p110_q05_02_seq01.png",
            },
            {
                "e002_c030_p110_q05_03_seq00.png",
                "e002_c030_p110_q05_03_seq01.png"
            }
        },
    };
    
    int correntTags[6][4] =
    {
        {
            kTagCouple000,
            kTagCouple001,
            kTagCouple000,
            kTagCouple001
        },
        {
            kTagCouple000,
            kTagCouple000,
            kTagCouple001,
            kTagCouple001
        },
        {
            kTagCouple000,
            kTagCouple001,
            kTagCouple000,
            kTagCouple001
        },
        {
            kTagCouple000,
            kTagCouple001,
            kTagCouple000,
            kTagCouple001
        },
        {
            kTagCouple000,
            kTagCouple001,
            kTagCouple001,
            kTagCouple000
        },
        {
            kTagCouple000,
            kTagCouple001,
            kTagCouple001,
            kTagCouple000
        },
    };
    
    const char* exampleSndName[6][4] =
    {
        {
            "e002_c030_p000_snd_black_n.mp3",
            "e002_c030_p000_snd_block_n.mp3",
            "e002_c030_p000_snd_black_n.mp3",
            "e002_c030_p000_snd_block_n.mp3"
        },
        {
            "e002_c030_p000_snd_clam_n.mp3",
            "e002_c030_p000_snd_clam_n.mp3",
            "e002_c030_p000_snd_clap_n.mp3",
            "e002_c030_p000_snd_clap_n.mp3"
        },
        {
            "e002_c030_p000_snd_flap_n.mp3",
            "e002_c030_p000_snd_flag_n.mp3",
            "e002_c030_p000_snd_flap_n.mp3",
            "e002_c030_p000_snd_flag_n.mp3"
        },
        {
            "e002_c030_p000_snd_slide_n.mp3",
            "e002_c030_p000_snd_sled_n.mp3",
            "e002_c030_p000_snd_slide_n.mp3",
            "e002_c030_p000_snd_sled_n.mp3"
        },
        {
            "e002_c030_p000_snd_glad_n.mp3",
            "e002_c030_p000_snd_glass_n.mp3",
            "e002_c030_p000_snd_glass_n.mp3",
            "e002_c030_p000_snd_glad_n.mp3"
        },
        {
            "e002_c030_p000_snd_plane_n.mp3",
            "e002_c030_p000_snd_plate_n.mp3",
            "e002_c030_p000_snd_plate_n.mp3",
            "e002_c030_p000_snd_plane_n.mp3"
        },
    };
    
    for (int i = 0; i < 6; i++)
    {
        std::vector<E002_Base_ExampleItem*> *question = new std::vector<E002_Base_ExampleItem*>();
        
        for (int j = 0; j < 4; j++)
        {
            question->push_back(new E002_Base_ExampleItem(i, exampleImgName[i][j], exampleSelectImgName[i][j],  exampleSndName[i][j], kTagExample001 + j, correntTags[i][j]));
        }
        
        mExamples->push_back(question);
    }
    
    for (int i = 0; i < 6; i++)
    {
        std::vector<std::vector<std::string>*> *seqImgs = new std::vector<std::vector<std::string>*>();
        
        for (int j = 0; j < 4; j++)
        {
            std::vector<std::string> *seqImg = new std::vector<std::string>();
            
            for (int k = 0; k < 2; k++)
            {
                std::string img = exampleSeqImgName[i][j][k];
                seqImg->push_back(img);
            }
            
            seqImgs->push_back(seqImg);
        }
        
        mSeqImgs->push_back(seqImgs);
    }
    
    //memset(exampleName, 0, sizeof(exampleName));
    
    
    
    onViewLoad();
}

void E002_C030_P110::onExit()
{
    E002_Base_Question::onExit();
}


void E002_C030_P110::onViewLoad()
{
    E002_Base_Question::onViewLoad();
     
    CJPsdParser::parseToPsdJSON("e002_c030_p110.json", &m_psdDictionary);
    
    CJSprite *bg = CJPsdParser::getPsdSprite("e002_c030_p110_bg00_00", m_psdDictionary);
    addChild(bg, kDepth0_backImage+5);

    showFire();
    
    setAnimationFile("e002_c030_p110_flash_cat_sheets.json", "e002_c030_p110_flash_cat_animations.json", "MEERKAT");
    setAnimationFile("e002_c030_p110_flash_sun_sheets.json", "e002_c030_p110_flash_sun_animations.json", "ANISON");
 
    mMeerKat = new CJAnimationCharacter(this, "MEERKAT");
    mMeerKat->setLooping("e002_c030_p110_flash_n_cat_loop");
    mMeerKat->setSuccess("e002_c030_p110_flash_s01_cat_action", NULL);
    mMeerKat->setFails("e002_c030_p110_flash_f01_cat_action", "e002_c030_p110_flash_f02_cat_action", NULL);
  
    mAnison = new CJAnimationCharacter(this, "ANISON");;
    mAnison->setLooping("e002_c030_p110_flash_n_sun_loop");
    mAnison->setSuccess("e002_c030_p110_flash_s01_sun_loop", "e002_c030_p110_flash_s02_sun_loop", NULL);
    mAnison->setFails("e002_c030_p110_flash_f01_sun_loop", "e002_c030_p110_flash_f02_sun_loop", NULL);
    
    addAnimationCharacter(mMeerKat, mAnison, NULL);
    
    createWall();
    
    if(m_bIsGuide)
    {
        createGuideDim(kDepth2_questions-1);
    }
    
    animationManagerParseStart();

}

void E002_C030_P110::onViewLoaded()
{
    E002_Base_Question::onViewLoaded();
    
    CJMultimedia::getInstance()->playBGM(getFilePath("snd","e002_c030_snd_bgm_play01.mp3"), true);
    
    animationManagerParseComplete();
}

void E002_C030_P110::startFlashAnimation()
{
    createAllAnimations();
    
    mAnison->showLooping();
    mMeerKat->showLooping();
    
    feedbackCharacter = mAnison->getSprite("e002_c030_p110_flash_n_sun_face");
    
    if(m_bIsGuide)
    {
        CJUtils::performSelector(this, callfunc_selector(E002_Base_Question::removeTouchDelegateForGuide), 0.5);
        CJUtils::performSelector(this, callfunc_selector(E002_C030_P110::setQuestions),0.3);
    }
    else
    {
        onFirstNarration();
    }
}

void E002_C030_P110::onFirstNarration()
{
    E002_Base_Question::onFirstNarration();
    removeAllAnimationsInDataPool("MEERKAT");
    
    mFirstNarration = mSndManager->playLetsPlay1Narration(0);
    playAnimation("MEERKAT", "e002_c030_p110_flash_t_cat_action", -1, kDepth1_flash);
    mPlayingGuideNarration = true;
}

void E002_C030_P110::onFirstNarrationEnd()
{
    E002_Base_Question::onFirstNarrationEnd();
    
    showGuideCharacterLooping();
    
    if (getUserDefaultFirstGuide(eGuidePageP110) == false)
    {
        mShowFirstGuide = true;
        setUserDefaultFirstGuide(eGuidePageP110);
        showGuide();
    }
    else
    {
        CJUtils::performSelector(this, callfunc_selector(E002_C030_P110::setQuestions),0.3);
    }
}

void E002_C030_P110::showGuideCharacterLooping()
{
    if (mPlayingGuideNarration)
    {
        removeAllAnimationsInDataPool("MEERKAT");
        mMeerKat->showLooping();
        guideCharacter = mMeerKat->getSprite("e002_c030_p110_flash_n_cat_body");
        
        mPlayingGuideNarration = false;
    }
    
}

void E002_C030_P110::onNarrationFinishedCallback(std::string fileName)
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
    
    for (int i = 0; i < mExamples->at(m_nCurrentStageIndex)->size(); i++)
    {
        if(fileName == mExamples->at(m_nCurrentStageIndex)->at(i)->getSoundPath() && mCompleteQuestion && mSuccessCount > 1)
        {
            CJUtils::performSelector(this, callfuncND_selector(E002_C030_P110::showSuccessCharacterMotion),(void*)0, 1.0f);

            break;
        }
    }
}

void E002_C030_P110::completeToGetRewardItem()
{
    E002_Base_Question::completeToGetRewardItem();
}

#pragma mark - touch

bool E002_C030_P110::onTouchBegan(CCPoint tp)
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
        
        mSndManager->playAnisonTouchNarr();
        return false;
    }
    
    for (int i = kTagExample001; i <= kTagExample004; i++)
    {
        if(getChildByTag(i) != NULL && CJUtils::hitTestPoint(getChildByTag(i), tp, false))
        {
            if(mExamples->at(m_nCurrentStageIndex)->at(i-kTagExample001)->getItemTag() == i)
            {
                for (int j = 0; j < mCompleteTag->size(); j++)
                {
                    if(mCompleteTag->at(j) == i)
                    {
                        return false;
                    }
                }
                
                showGuideCharacterLooping();
                
                speakNarration(NULL, mExamples->at(m_nCurrentStageIndex)->at(i-kTagExample001)->getSoundPath().c_str());
                
                mSelectTag->push_back(mExamples->at(m_nCurrentStageIndex)->at(i-kTagExample001)->getItemTag());
                
                mSndManager->playLetsPlay1Effect(2);
                
                ((CJSprite*)getChildByTag(i))->setTexture(CCTextureCache::sharedTextureCache()
                        ->addImage(getFilePath("img", mExamples->at(m_nCurrentStageIndex)->at(i-kTagExample001)->getSelectImgPath().append(".png")).c_str()));
                
                ((CJSprite*)getChildByTag(i))->runAction(CCSequence::create(CCScaleTo::create(0.1, 1.2),
                                                                            CCScaleTo::create(0.1, 1.0f),
                                                                            NULL));
                mSelectedCount++;
                
                if(mSelectedCount == 2)
                {
                    if(mSelectedTag == mExamples->at(m_nCurrentStageIndex)->at(i-kTagExample001)->getItemTag())
                    {
                        mSelectedCount--;
                        return false;
                    }
                    
                    setTouchDisalbeBaseLayer();
                    
                    if(mCorrectedTag == mExamples->at(m_nCurrentStageIndex)->at(i-kTagExample001)->getCorrectTag())
                    {
                        runAction(CCSequence::create(CCDelayTime::create(1.0f),
                                                     CCCallFuncND::create(this, callfuncND_selector(E002_C030_P110::onSuccesses), (void*)mCorrectedTag),
                                                     NULL));
                        
                    }
                    else
                    {
                        runAction(CCSequence::create(CCDelayTime::create(1.0f),
                                                     CCCallFuncND::create(this, callfuncND_selector(E002_C030_P110::onFails), (void*)mCorrectedTag),
                                                     NULL));
                    }
                    
                    return false;
                }
                
                mCorrectedTag = mExamples->at(m_nCurrentStageIndex)->at(i-kTagExample001)->getCorrectTag();
                mSelectedTag = mExamples->at(m_nCurrentStageIndex)->at(i-kTagExample001)->getItemTag();

            }
        }
        
        if(m_bIsGuide)
        {
            if (m_currentGuideIndex == 0)
            {
                showHand(NULL, 1);
            }
            else if (m_currentGuideIndex == 3)
            {
                showHand(NULL, 4);
            }
        }
    }

    return false;
}

void E002_C030_P110::onTouchMoved(CCPoint tp)
{
}

void E002_C030_P110::onTouchEnded(CCPoint tp)
{
   
}

#pragma mark - feedback event

void E002_C030_P110::onExamplesTouched(int index)
{
    E002_Base_Question::onExamplesTouched(index);
}


void E002_C030_P110::onSuccesses(CCNode *node, int tag)
{
    mSuccessCount++;
    
    mCompleteQuestion = true;
    
    mSndManager->playSuccessSfxSnd(11);
    
    int index = 0;
    
    for (int i = 0; i<mExamples->at(m_nCurrentStageIndex)->size(); i++)
    {
        if(mExamples->at(m_nCurrentStageIndex)->at(i)->getCorrectTag() == tag)
        {
            mCompleteTag->push_back(mExamples->at(m_nCurrentStageIndex)->at(i)->getItemTag());
            
            index = i;
            
            ((CJSprite*)getChildByTag(mExamples->at(m_nCurrentStageIndex)->at(i)->getItemTag()))
            ->runAction(CCSequence::create(CCDelayTime::create(0.3),
                                           CCScaleTo::create(0.3, 1.1),
                                           CCScaleTo::create(0.2, 1.0),
                                            CCDelayTime::create(0.7),
                                           CCCallFunc::create(this, callfunc_selector(E002_C030_P110::playExampleSuccessEffectSnd)),
                                           CJUtils::getSeqAction(1, 0.1, getFilePath("img",mSeqImgs->at(m_nCurrentStageIndex)->at(i)->at(0)).c_str(),
                                                                         getFilePath("img", mSeqImgs->at(m_nCurrentStageIndex)->at(i)->at(1)).c_str(),
                                                                         NULL),
                                           NULL));
            
        }
    }

    runAction(CCSequence::create(CCDelayTime::create(0.3),
                                   CCCallFuncND::create(this, callfuncND_selector(E002_C030_P110::speakNarration),
                                                       (void*)mExamples->at(m_nCurrentStageIndex)->at(index)->getSoundPath().c_str()),
                                   NULL));
    
    setTouchEnableBaseLayer(true);
    
    mCorrectedTag = 0;
    mSelectedCount = 0;
}

void E002_C030_P110::playExampleSuccessEffectSnd()
{
    mSndManager->playLetsPlay1Effect(1);

}

void E002_C030_P110::onFails(CCNode *node, int tag)
{
    mFailCount++;
    mSndManager->playWrongSfxSnd(11);
    
    runAction(CCSequence::create(CCDelayTime::create(0.3f),
                                 CCCallFuncND::create(this, callfuncND_selector(E002_C030_P110::showWrongCharacterMotion), (void*)0),
                                 NULL));
    
    float delay = 0;
    
    for (int i = 0; i < mSelectTag->size() ; i++)
    {
        CCRepeat *repeat = CCRepeat::create(CCSequence::create(CCMoveBy::create(0.1, ccp(-20, 0)),
                                                               CCMoveBy::create(0.1, ccp(20, 0)),
                                                               NULL), 3);
        
        if(i == mSelectTag->size() - 1)
        {
            getChildByTag(mSelectTag->at(i))->runAction(CCSequence::create(CCDelayTime::create(delay),
                                                                           repeat,
                                                                           CCCallFunc::create(this, callfunc_selector(E002_C030_P110::resetExamples)),
                                                                           NULL));
        }
        else
        {
            getChildByTag(mSelectTag->at(i))->runAction(CCSequence::create(CCDelayTime::create(delay),
                                                                           repeat,
                                                                           NULL));
        }
        
        delay += 0.05;
        
    }
    
    mSelectTag->clear();
    
}

void E002_C030_P110::resetExamples()
{
    setTouchEnableBaseLayer();
    
    for (int i = kTagExample001; i <= kTagExample004 ; i++)
    {
        removeChildByTag(i);
    }
    
    for (int i = 0; i<4; i++)
    {
        E002_Base_ExampleItem *item = mExamples->at(m_nCurrentStageIndex)->at(i);
        
        CJSprite *example = CJPsdParser::getPsdSprite(item->getImgPath(), m_psdDictionary);
        addChild(example, kDepth3_examples, kTagExample001 + i);
        
    }

    mCorrectedTag = 0;
    mSelectedCount = 0;
}

void E002_C030_P110::onComplete()
{
    E002_Base_Question::onComplete();

}

#pragma mark - user function

void E002_C030_P110::setQuestions()
{
    setTouchDisalbeBaseLayer();
    
    resetValue();
    
    for (int i = 0; i<4; i++)
    {
        float delay = 1.0f;

        E002_Base_ExampleItem *item = mExamples->at(m_nCurrentStageIndex)->at(i);
        
        CJSprite *example = CJPsdParser::getPsdSprite(item->getImgPath(), m_psdDictionary);
        example->setScale(0);
        addChild(example, kDepth3_examples, kTagExample001 + i);
        
        delay *= i;
        
        if( i == 3)
        {
            example->runAction(CCSequence::create(CCDelayTime::create(delay),
                                                  CCCallFuncND::create(this, callfuncND_selector(E002_C030_P110::playAppearanceExamplesSound), (void*)i),
                                                  CCEaseElasticOut::create(CCScaleTo::create(1.0, 1.0), 0.4),
                                                  CCCallFuncND::create(this, callfuncND_selector(E002_C030_P110::setReadyQuestion), (void*)true),
                                                  NULL));
        }
        else
        {
            example->runAction(CCSequence::create(CCDelayTime::create(delay),
                                                  CCCallFuncND::create(this, callfuncND_selector(E002_C030_P110::playAppearanceExamplesSound), (void*)i),
                                                  CCEaseElasticOut::create(CCScaleTo::create(1.0, 1.0), 0.4),
                                                  NULL));
        }
    }
}

void E002_C030_P110::setReadyQuestion(CCNode* node, bool isReady)
{
    
    if(isReady)
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

void E002_C030_P110::showShakeFullScreen(CCNode *node, int count)
{
    CCRepeat *repeat = CCRepeat::create(CCSequence::create(CCMoveBy::create(0.1f, ccp(0, 10)),
                                                           CCMoveBy::create(0.1f, ccp(0, -10)),
                                                           CCMoveBy::create(0.1f, ccp(0, 5)),
                                                           CCMoveBy::create(0.1f, ccp(0, -5)),
                                                           NULL), count);
    runAction(repeat);
}

void E002_C030_P110::nextQuestion()
{
    for (int i=0; i<4; i++)
    {
        getChildByTag(mExamples->at(m_nCurrentStageIndex)->at(i)->getItemTag())->setZOrder(kDepth0_background+1);
        
        if(i == 0 || i == 2)
        {
            getChildByTag(mExamples->at(m_nCurrentStageIndex)->at(i)->getItemTag())->runAction(CCSequence::create(CCMoveBy::create(1.8f, ccp(-100, 0)),
                                                                                                                  CCEaseSineIn::create(CCMoveBy::create(0.8f, ccp(-400, 0))),
                                                                                                                  CCCallFuncN::create(this, callfuncN_selector(CJLayer::removeChild)),
                                                                                                                  NULL));
            
        }
        else
        {
            getChildByTag(mExamples->at(m_nCurrentStageIndex)->at(i)->getItemTag())->runAction(CCSequence::create(CCMoveBy::create(1.8f, ccp(100, 0)),
                                                                                                                  CCEaseSineIn::create(CCMoveBy::create(0.8f, ccp(400, 0))),
                                                                                                                  CCCallFuncN::create(this, callfuncN_selector(CJLayer::removeChild)),
                                                                                                                  NULL));
        }
    }
   
    
    if(m_nCurrentStageIndex%2 == 1)
    {
        mSndManager->playLetsPlay1Effect(3);

        CJSprite *rock = CJPsdParser::getPsdSprite("e002_c030_p110_img_rock01_seq_00", m_psdDictionary);
        addChild(rock, kDepth0_background);
        
        rock->runAction(CCSequence::create(CJUtils::getSeqAction(1,
                                                                 0.3,
                                                                 getFilePath("img", "e002_c030_p110_img_rock01_seq_01.png").c_str(),
                                                                 getFilePath("img", "e002_c030_p110_img_rock01_seq_02.png").c_str(),
                                                                 getFilePath("img", "e002_c030_p110_img_rock01_seq_03.png").c_str(),
                                                                 getFilePath("img", "e002_c030_p110_img_rock01_seq_04.png").c_str(),
                                                                 NULL),
                                           CCCallFuncN::create(this, callfuncN_selector(CJLayer::removeChild)),
                                           NULL));
    }
    else
    {
        mSndManager->playLetsPlay1Effect(3);
        
        CJSprite *rock = CJPsdParser::getPsdSprite("e002_c030_p110_img_rock00_seq_00", m_psdDictionary);
        addChild(rock, kDepth0_background);
        
        rock->runAction(CCSequence::create(CJUtils::getSeqAction(1,
                                                                 0.3,
                                                                 getFilePath("img", "e002_c030_p110_img_rock00_seq_01.png").c_str(),
                                                                 getFilePath("img", "e002_c030_p110_img_rock00_seq_02.png").c_str(),
                                                                 getFilePath("img", "e002_c030_p110_img_rock00_seq_03.png").c_str(),
                                                                 getFilePath("img", "e002_c030_p110_img_rock00_seq_04.png").c_str(),
                                                                 NULL),
                                           CCCallFuncN::create(this, callfuncN_selector(CJLayer::removeChild)),
                                           NULL));
    }
    
    getChildByTag(kTagLeftWall)->runAction(CCSequence::create(CCMoveBy::create(1.8f, ccp(-100, 0)),
                                                               CCEaseSineIn::create(CCMoveBy::create(0.8f, ccp(-400, 0))),
                                                               CCCallFuncN::create(this, callfuncN_selector(CJLayer::removeChild)),
                                                               NULL));
    
    getChildByTag(kTagRightWall)->runAction(CCSequence::create(CCMoveBy::create(1.8f, ccp(100, 0)),
                                                                CCEaseSineIn::create(CCMoveBy::create(0.8f, ccp(400, 0))),
                                                               CCDelayTime::create(0.5f),
                                                               //CCCallFunc::create(this, callfunc_selector(E002_C030_P110::onTouchedNavigationButtonAtNext)),
                                                                CCCallFuncN::create(this, callfuncN_selector(CJLayer::removeChild)),
                                                                NULL));
    
        
    
}

void E002_C030_P110::resetValue()
{
    if (m_nCurrentStageIndex > 1)
    {
        E002_Base_Navigation::setVisibleButton(true, eNavigationButton_Prev);
    }
    else if(m_nCurrentStageIndex == 1)
    {
        E002_Base_Navigation::setVisibleButton(false, eNavigationButton_Prev);
    }
    
    showGuideCharacterLooping();
    
    mSelectTag->clear();
    mCompleteTag->clear();
    
    mFailCount = 0;
    mCorrectedTag = 0;
    mSelectedCount = 0;
    mSuccessCount = 0;
    mCompleteQuestion = false;
    setReadyQuestion(NULL, false);
    
    for (int i = kTagExample001; i <= kTagExample004; i++)
    {
        if(getChildByTag(i) != NULL)
            removeChildByTag(i);
    }
    
    createWall();
    
}

#pragma mark - sound & narration
void E002_C030_P110::playAppearanceExamplesSound(CCNode* sender, void* index)
{
    mSndManager->playLetsPlay1Effect(1);
    
    if(!mCompleteQuestion)
        speakNarration(NULL, mExamples->at(m_nCurrentStageIndex)->at((int)index)->getSoundPath().c_str());
}

  
#pragma mark - user function

void E002_C030_P110::speakNarration(CCNode *node, const char* fileName)
{
    stopAllNarration();
    playNarration(fileName); 
}

#pragma mark - navigation delegate

void E002_C030_P110::onTouchedNavigationButtonAtIndex()
{
    E002_Base_Question::onTouchedNavigationButtonAtIndex();
    
    E002_C030_P000_Index* _indexClass = E002_C030_P000_Index::create();
    _indexClass->init();
    _indexClass->setIndexDelegate(this);
    _indexClass->showIndex(this, _indexClass);
    addChild(_indexClass, kDepth11_Index);
}

void E002_C030_P110::onTouchedNavigationButtonAtInfo()
{
    E002_Base_Question::onTouchedNavigationButtonAtInfo();
    
    showGuide();
}

void E002_C030_P110::onTouchedNavigationButtonAtPrev()
{
    E002_Base_Question::onTouchedNavigationButtonAtPrev();
    if (m_nCurrentStageIndex > 0) {
        m_nCurrentStageIndex--;
        setQuestions();
    }
}

void E002_C030_P110::onTouchedNavigationButtonAtNext()
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
        completeLetsPlay1();
        
        //replayceScene
        replaceSceneTransitionFadeOut(E002_C030_P130);
    }
    
}

void E002_C030_P110::onTouchedNavigationButtonAtReward()
{
    showLetPlay1RewardPopup(NULL, m_nCurrentStageIndex - 1);
}

void E002_C030_P110::OnLastFrame(CJAnimation* pAnimation)
{
    E002_Base_Question::OnLastFrame(pAnimation);
    
    for (int i = 0; i < mAnison->getSuccessKeys()->size(); i++)
    {
        if(pAnimation->getName() == mAnison->getSuccessKeys()->at(i))
        {
            if(m_bIsGuide)
            {
                ((E002_Base_Question*)getParent())->removeGuide();
                return;
            }
            
//            CJUtils::performSelector(this, callfuncND_selector(E002_C030_P110::playEffect),(void*)7, 1.5f);
            
            int index = m_nCurrentStageIndex - 1;
            CJUtils::performSelector(this, callfuncND_selector(E002_C030_P110::showLetPlay1RewardItem),(void*) index, 1.5f);

            runAction(CCSequence::create(CCCallFuncND::create(this, callfuncND_selector(E002_C030_P110::showWallParticle), (void*)0),
                                         CCDelayTime::create(0.5f),
                                         CCCallFuncND::create(this, callfuncND_selector(E002_C030_P110::showWallParticle), (void*)1),
                                         CCCallFuncND::create(this, callfuncND_selector(E002_C030_P110::showShakeFullScreen), (void*)6),
                                         CCDelayTime::create(0.5),
                                         CCCallFunc::create(this, callfunc_selector(E002_C030_P110::nextQuestion)),
                                         CCDelayTime::create(3.0),
                                         CCCallFunc::create(this, callfunc_selector(E002_C030_P110::onTouchedNavigationButtonAtNext)),
                                         NULL));
        }
    }
}

void E002_C030_P110::onTouchedNavigationButtonAtClose()
{
    E002_Base_Question::onTouchedNavigationButtonAtClose();
    
}

#pragma mark - sprite create

void E002_C030_P110::createWall()
{
    
    if(m_nCurrentStageIndex%2 == 1)
    {
        if(m_nCurrentStageIndex == m_nMaxStageCount - 1)
        {
            CJSprite *stair = CJPsdParser::getPsdSprite("e002_c030_p110_img_stairs", m_psdDictionary);
            addChild(stair, kDepth0_background-1);
        }
        
        for (int i = kTagLeftWall; i <= kTagRightWall2; i++)
        {
            if(getChildByTag(i) != NULL)
            {
                removeChildByTag(i);
            }
        }
        
        
        CJSprite *leftWall = CJPsdParser::getPsdSprite("e002_c030_p110_bg01_00", m_psdDictionary);
        addChild(leftWall, kDepth0_background, kTagLeftWall);
            
        CJSprite *rightWall = CJPsdParser::getPsdSprite("e002_c030_p110_bg01_01", m_psdDictionary);
        addChild(rightWall, kDepth0_background, kTagRightWall);
        
        CJSprite *leftWall2 = CJPsdParser::getPsdSprite("e002_c030_p110_bg02_00", m_psdDictionary);
        addChild(leftWall2, kDepth0_background-2, kTagLeftWall2);
        
        CJSprite *rightWall2 = CJPsdParser::getPsdSprite("e002_c030_p110_bg02_01", m_psdDictionary);
        addChild(rightWall2, kDepth0_background-2, kTagRightWall2);
        
    }
    else
    {
        for (int i = kTagLeftWall; i <= kTagRightWall2; i++)
        {
            if(getChildByTag(i) != NULL)
            {
                removeChildByTag(i);
            }
        }
        
        
        CJSprite *leftWall = CJPsdParser::getPsdSprite("e002_c030_p110_bg02_00", m_psdDictionary);
        addChild(leftWall, kDepth0_background, kTagLeftWall);
        
        CJSprite *rightWall = CJPsdParser::getPsdSprite("e002_c030_p110_bg02_01", m_psdDictionary);
        addChild(rightWall, kDepth0_background, kTagRightWall);
        
        CJSprite *leftWall2 = CJPsdParser::getPsdSprite("e002_c030_p110_bg01_00", m_psdDictionary);
        addChild(leftWall2, kDepth0_background-2, kTagLeftWall2);
        
        CJSprite *rightWall2 = CJPsdParser::getPsdSprite("e002_c030_p110_bg01_01", m_psdDictionary);
        addChild(rightWall2, kDepth0_background-2, kTagRightWall2);
    }
}

void E002_C030_P110::showFire()
{
    CJSprite *leftFire = CJPsdParser::getPsdSprite("e002_c030_p110_img_fire_on00@0", m_psdDictionary);
    addChild(leftFire, kDepth1_flash);
    
    leftFire->runAction(CJUtils::getSeqAction(-1, 0.2f,
                                              getFilePath("img","e002_c030_p110_img_fire_on01.png").c_str(),
                                              getFilePath("img","e002_c030_p110_img_fire_on02.png").c_str(),
                                              getFilePath("img","e002_c030_p110_img_fire_on03.png").c_str(),
                                              getFilePath("img","e002_c030_p110_img_fire_on04.png").c_str(),
                                              NULL));
    
    CJSprite *rightFire = CJPsdParser::getPsdSprite("e002_c030_p110_img_fire_on00@1", m_psdDictionary);
    addChild(rightFire, kDepth1_flash);
    
    rightFire->runAction(CJUtils::getSeqAction(-1, 0.2f,
                                              getFilePath("img","e002_c030_p110_img_fire_on01.png").c_str(),
                                              getFilePath("img","e002_c030_p110_img_fire_on02.png").c_str(),
                                              getFilePath("img","e002_c030_p110_img_fire_on03.png").c_str(),
                                              getFilePath("img","e002_c030_p110_img_fire_on04.png").c_str(),
                                              NULL));
}


void E002_C030_P110::showSuccessCharacterMotion(CCNode *node, int index)
{
    if(index == 0)
    {
        if (m_nCurrentStageIndex%2 == 0)
        {
             mSuccessNarrationSnd = mSndManager->playMeercatSuccessNarr(1);
        }
        else
        {
             mSuccessNarrationSnd = mSndManager->playMeercatSuccessNarr(2);
        }

        CJAnimation* meerKat = mMeerKat->showSuccess();
        addEffectOnFlashFrame(meerKat, 1, getFilePath("snd", mSndManager->playLetsPlay1Effect(4, true)).c_str());
    
        CJAnimation* anison = mAnison->showSuccess();
        addEffectOnFlashFrame(anison, 1, getFilePath("snd", mSndManager->playLetsPlay1Effect(5, true)).c_str());
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

void E002_C030_P110::showWrongCharacterMotion(CCNode *node, int index)
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
        
        CJAnimation *ani =  mAnison->showFails();
        
        if(ani->getName() == "e002_c030_p110_flash_f02_sun_loop")
        {
            addEffectOnFlashFrame(ani, 1, getFilePath("snd", mSndManager->playLetsPlay1Effect(6, true)).c_str());
        }
    }
    else
    {
        if (m_nCurrentStageIndex%2 == 0)
        {
            if(mFailCount%2 == 0)
            {  mSndManager->playAnisonWrongNarr(9);
            
            }
            else
            {
                mSndManager->playAnisonWrongNarr(12);

            }
        }
        else
        {
            if(mFailCount%2 == 0)
            {
                mSndManager->playAnisonWrongNarr(12);
            }
            else
            {
                mSndManager->playAnisonWrongNarr(9);
            }
        }
    }
}

void E002_C030_P110::showWallParticle(CCNode *node, int index)
{
    std::string resource;
    
    if(m_nCurrentStageIndex%2 == 1)
    {
        if (index == 0)
        {
            resource = "e002_c030_p110_wall_open02.plist";
        }
        else
        {
            resource = "e002_c030_p110_wall_open04.plist";
        }
        
    }
    else
    {
        if (index == 0)
        {
            resource = "e002_c030_p110_wall_open01.plist";
        }
        else
        {
            resource = "e002_c030_p110_wall_open03.plist";
        }
    }
    

    CCParticleSystemQuad * particle = CCParticleSystemQuad::create(getFilePath("img", resource).c_str());
    
    if(index == 0)
    {
        addChild(particle, kDepth0_backImage+4);
    }
    else
    {
        addChild(particle, kDepth0_background-1);
    }
        
    
    particle->setAutoRemoveOnFinish(true);
}

void E002_C030_P110::playEffect(CCNode *node, int index)
{
    mSndManager->playLetsPlay1Effect(index);
}

void E002_C030_P110::showGuide()
{
    E002_Base_Question::showGuide();
        
    m_Guide = E002_C030_P110::create();
    m_Guide->init();
    m_Guide->setGuide(true);
    addChild(m_Guide, kDepth10_guide);
    
    std::vector<CCPoint> *guideHandPosition = new std::vector<CCPoint>();
    
    guideHandPosition->push_back(CJPsdParser::getPsdPosition("e002_common_img_guide_hand@00", m_psdDictionary));
    guideHandPosition->push_back(CJPsdParser::getPsdPosition("e002_common_img_guide_hand@01", m_psdDictionary));
    guideHandPosition->push_back(ccp(500, -200));
    guideHandPosition->push_back(CJPsdParser::getPsdPosition("e002_common_img_guide_hand@02", m_psdDictionary));
    guideHandPosition->push_back(CJPsdParser::getPsdPosition("e002_common_img_guide_hand@03", m_psdDictionary));
    
    m_Guide->setGuideHandPosition(guideHandPosition);
}

void E002_C030_P110::removeGuide()
{
    E002_Base_Question::removeGuide();
    removeChild(m_Guide);
    
}

void E002_C030_P110::completeToMoveHand(CCNode *node, int index)
{
    switch (index) {
        case 0:
            onTouchBegan(getChildByTag(kTagExample001)->getPosition());
            break;
        case 1:
            onTouchBegan(getChildByTag(kTagExample003)->getPosition());
            showHand(NULL, 2);
            break;
        case 2:
            CJUtils::performSelector(this, callfuncND_selector(E002_Base_Question::showHand), (void*)3, 1.0f);
            break;
        case 3:
            onTouchBegan(getChildByTag(kTagExample002)->getPosition());
            break;
        case 4:
            onTouchBegan(getChildByTag(kTagExample004)->getPosition());
            break;
        default:
            break;
    }
}

void E002_C030_P110::completeFirstGuide()
{
    CJUtils::performSelector(this, callfunc_selector(E002_C030_P110::setQuestions),0.3);
}