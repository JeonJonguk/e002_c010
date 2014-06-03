

#include "E002_C030_P320.h"
#include "E002_C030_P330.h"
#include "E002_C030_P000_Index.h"
#include "E002_C030_P310.h"

#define GET_EXAMPLES mExamples->at(m_nCurrentStageIndex)
#define GET_SELECTED_ITEM mExamples->at(m_nCurrentStageIndex)->at(mExampleSelectIndex)

enum
{
    kTagWall = 200,
    
    kTagExample001 = 250,
    kTagExample002,
    kTagExample003,
    
    kTagTarget001,
    kTagTarget002,
    kTagTarget003,
    
    kTagCouple001,
    
    kTagQuestion,
    kTagSuccess,
    
    kTagDragTargetBg,
};

E002_C030_P320::E002_C030_P320()
{
    mExamples = new std::vector<std::vector<E002_Base_ExampleItem*>*>();
    mQuestions = new std::vector<std::vector<std::string>*>();
    mTargets = new std::vector<CJSprite*>();
    mQuestions = new std::vector<std::vector<std::string>*>();
    mQuestionSounds = new std::vector<std::vector<std::string>*>();

    m_touchingExampleSp = NULL;
    mExampleSelectIndex = 0;
    mPlayingGuideNarration = false;
    
    mSndManager = new E002_C030_SoundManager();
    mGuideMoveCnt = 0;
}

E002_C030_P320::~E002_C030_P320()
{
//    for (int i=0; i < mExamples->size(); i++)
//    {
//        for (int j = 0; mExamples->at(i)->size(); j++)
//        {
//            delete mExamples->at(i)->at(j);
//        }
//    }
    
    CC_SAFE_DELETE(mExamples);
    CC_SAFE_DELETE(mQuestions);
    CC_SAFE_DELETE(mTargets);
    CC_SAFE_DELETE(mQuestions);
    CC_SAFE_DELETE(mQuestionSounds);
}

#pragma mark - init

bool E002_C030_P320::init()
{
    if (!E002_Base_Question::init()) {
        return false;
    }
    
    m_nMaxStageCount = 4;
    m_nCurrentStageIndex = 1;
    mSelectedCount = 0;
    mSuccessCount = 0;
    
    
    return true;
}

void E002_C030_P320::onEnter()
{
    E002_Base_Question::onEnter();
    
    const char* exampleImgName[4][3] =
    {
        {
            "e002_c030_p320_a00_o_n",
            "e002_c030_p320_a00_ck_n",
            "e002_c030_p320_a00_cl_n"
        },
        {
            "e002_c030_p320_a01_m_n",
            "e002_c030_p320_a01_a_n",
            "e002_c030_p320_a01_cl_n"
        },
        {
            "e002_c030_p320_a02_e_n",
            "e002_c030_p320_a02_d_n",
            "e002_c030_p320_a02_sl_n"
        },
        {
            "e002_c030_p320_a03_g_n",
            "e002_c030_p320_a03_fl_n",
            "e002_c030_p320_a03_a_n"
        }
    };
    
    const char* exampleSelectImgName[4][3] =
    {
        {
            "e002_c030_p320_a00_o_s",
            "e002_c030_p320_a00_ck_s",
            "e002_c030_p320_a00_cl_s"
        },
        {
            "e002_c030_p320_a01_m_s",
            "e002_c030_p320_a01_a_s",
            "e002_c030_p320_a01_cl_s"
        },
        {
            "e002_c030_p320_a02_e_s",
            "e002_c030_p320_a02_d_s",
            "e002_c030_p320_a02_sl_s"
        },
        {
            "e002_c030_p320_a03_g_s",
            "e002_c030_p320_a03_fl_s",
            "e002_c030_p320_a03_a_s"
        }
    };
    
    const char* exampleSndName[4][3] =
    {
        {
            "e002_c030_p000_snd_o_n.mp3",
            "e002_c030_p000_snd_ck_n.mp3",
            "e002_c030_p000_snd_cl_n.mp3"
        },
        {
            "e002_c030_p000_snd_m_n.mp3",
            "e002_c030_p000_snd_a_n.mp3",
            "e002_c030_p000_snd_cl_n.mp3"
        },
        {
            "e002_c030_p000_snd_e_n.mp3",
            "e002_c030_p000_snd_d_n.mp3",
            "e002_c030_p000_snd_sl_n.mp3"
        },
        {
            "e002_c030_p000_snd_g_n.mp3",
            "e002_c030_p000_snd_fl_n.mp3",
            "e002_c030_p000_snd_a_n.mp3"
        }
    };
    
    const char* questionsImgName[4][2] =
    {
        {
            "e002_c030_p320_a00_img",
            "e002_c030_p320_a00_success"
        },
        {
            "e002_c030_p320_a01_img",
            "e002_c030_p320_a01_success"
        },
        {
            "e002_c030_p320_a02_img",
            "e002_c030_p320_a02_success"
        },
        {
            "e002_c030_p320_a03_img",
            "e002_c030_p320_a03_success"
        }
    };
    
    const char* questionsSndName[4][2] =
    {
        {
            "e002_c030_p000_snd_clock_n.mp3",
            "e002_c030_p000_snd_cl_o_ck_n.mp3"
        },
        {
            "e002_c030_p000_snd_clam_n.mp3",
            "e002_c030_p000_snd_cl_a_m_n.mp3"
        },
        {
            "e002_c030_p000_snd_sled_n.mp3",
            "e002_c030_p000_snd_sl_e_d_n.mp3"
        },
        {
            "e002_c030_p000_snd_flag_n.mp3",
            "e002_c030_p000_snd_fl_a_g_n.mp3"
        }
    };
    
    int correntTags[4][3] =
    {
        {
            kTagTarget002,
            kTagTarget003,
            kTagTarget001
        },
        {
            kTagTarget003,
            kTagTarget002,
            kTagTarget001
        },
        {
            kTagTarget002,
            kTagTarget003,
            kTagTarget001
        },
        {
            kTagTarget003,
            kTagTarget001,
            kTagTarget002
        }
    };
    
    
    for (int i = 0; i < 4; i++)
    {
        std::vector<E002_Base_ExampleItem*> *examples = new std::vector<E002_Base_ExampleItem*>();
        
        for (int j = 0; j < 3; j++)
        {
            examples->push_back(new E002_Base_ExampleItem(i, exampleImgName[i][j], exampleSelectImgName[i][j], exampleSndName[i][j], kTagExample001 + j, correntTags[i][j]));
        }
        
        mExamples->push_back(examples);
    }
    
    for (int i = 0; i < 4; i++)
    {
        std::vector<std::string> *question = new std::vector<std::string>();
        std::vector<std::string> *queSnd = new std::vector<std::string>();
        
        for (int j = 0; j < 2; j++)
        {
            question->push_back(questionsImgName[i][j]);
            queSnd->push_back(questionsSndName[i][j]);
        }
        
        mQuestions->push_back(question);
        mQuestionSounds->push_back(queSnd);
    }
    
    //memset(exampleName, 0, sizeof(exampleName));
  
    onViewLoad();
}

void E002_C030_P320::onExit()
{
    E002_Base_Question::onExit();
}


void E002_C030_P320::onViewLoad()
{
    E002_Base_Question::onViewLoad();
     
    CJPsdParser::parseToPsdJSON("e002_c030_p320.json", &m_psdDictionary);
    
    setBackground("e002_c030_p320_bg00_00.jpg");
    
    CJSprite *bridge = CJPsdParser::getPsdSprite("e002_c030_p320_bg00_01", m_psdDictionary);
    addChild(bridge, kDepth2_questions-1);
    
    CJSprite *dragTargetBg = CJPsdParser::getPsdSprite("e002_c030_p320_a00_success_bg", m_psdDictionary);
    addChild(dragTargetBg, kDepth0_backImage, kTagDragTargetBg);
    dragTargetBg->setVisible(false);
    
    setAnimationFile("e002_c030_p320_flash_cat02_boom_sheets.json", "e002_c030_p320_flash_cat02_boom_animations.json", "CHARACTERS");
    
    mCharacters = new CJAnimationCharacter(this, "CHARACTERS");
    mCharacters->setLooping("e002_c030_p320_flash_n_cat02_boom_loop");
    mCharacters->setSuccess("e002_c030_p320_flash_s_cat02_boom_action", NULL);
    mCharacters->setFails("e002_c030_p320_flash_f01_cat02_boom_action", "e002_c030_p320_flash_f02_cat02_boom_action", NULL);    

    addAnimationCharacter(mCharacters, NULL);

    if(m_bIsGuide)
    {
        createGuideDim(kDepth2_questions-2);
    }
    
    animationManagerParseStart();

}

void E002_C030_P320::onViewLoaded()
{
    E002_Base_Question::onViewLoaded();
    
    CJMultimedia::getInstance()->playBGM(getFilePath("snd","e002_c030_snd_bgm_play03_2.mp3"), true);
    
    animationManagerParseComplete();
}

void E002_C030_P320::startFlashAnimation()
{
    createAllAnimations();
    mCharacters->showLooping();
    
    if(m_bIsGuide)
    {
        CJUtils::performSelector(this, callfunc_selector(E002_Base_Question::removeTouchDelegateForGuide), 0.5);
        
        CJUtils::performSelector(this, callfunc_selector(E002_C030_P320::setQuestions),0.3);
    }
    else
    {
        onFirstNarration();
    }
}

void E002_C030_P320::onFirstNarration()
{
    E002_Base_Question::onFirstNarration();
    
    removeAllAnimationsInDataPool("CHARACTERS");
    mFirstNarration = mSndManager->playLetsPlay1Narration(0);
    playAnimation("CHARACTERS", "e002_c030_p320_flash_talk_cat02_boom_loop", -1, kDepth1_flash);
    mPlayingGuideNarration = true;
}

void E002_C030_P320::onFirstNarrationEnd()
{
    E002_Base_Question::onFirstNarrationEnd();
    
    showGuideCharacterLooping();
    
    if (getUserDefaultFirstGuide(eGuidePageP320) == false)
    {
        mShowFirstGuide = true;
        setUserDefaultFirstGuide(eGuidePageP320);
        showGuide();
    }
    else
    {
        CJUtils::performSelector(this, callfunc_selector(E002_C030_P320::setQuestions),0.3);
    }
}

void E002_C030_P320::showGuideCharacterLooping()
{
    if(mPlayingGuideNarration)
    {
        removeAllAnimationsInDataPool("CHARACTERS");
        mCharacters->showLooping();
        guideCharacter = mCharacters->getSprite("e002_c030_p120_flash_sun_n01_cat02_body");
        feedbackCharacter = mCharacters->getSprite("e002_c030_p120_flash_boom_n01_body");

        mPlayingGuideNarration = false;
    }
}

void E002_C030_P320::onNarrationFinishedCallback(std::string fileName)
{
    if (fileName == mFirstNarration && !isFirstSkiped())
    {
        onFirstNarrationEnd();
    }
    else if (fileName == mFirstNarration && isFirstSkiped())
    {
        showGuideCharacterLooping();
    }
    else if(fileName == mSuccessNarrationSnd)
    {
        showSuccessCharacterMotion(NULL, 1);
    }
    else if(fileName == mWrongNarrationSnd)
    {
        showWrongCharacterMotion(NULL, 1);
    }
    else if( !mReadyQuestion && fileName == mQuestionSounds->at(m_nCurrentStageIndex)->at(0))
    {
        showExamples();
    }
    else if( fileName == mQuestionSounds->at(m_nCurrentStageIndex)->at(1))
    {
        runAction(CCSequence::create(CCDelayTime::create(0.5f),
                                     CCCallFunc::create(this, callfunc_selector(E002_C030_P320::removeSuccessTexture)),
                                     CCCallFuncND::create(this, callfuncND_selector(E002_C030_P320::showSuccessCharacterMotion), (void*)0),
                                     NULL));
    }
}

#pragma mark - touch

bool E002_C030_P320::onTouchBegan(CCPoint tp)
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
        mSndManager->playBoomBoomTouchNarr();
        return false;
    }
    else if(mReadyQuestion && getChildByTag(kTagQuestion) != NULL && CJUtils::hitTestPoint(getChildByTag(kTagQuestion), tp, false))
    {
        showGuideCharacterLooping();
        playQuestionSound(NULL, 0);
        
        getChildByTag(kTagQuestion)->runAction(CCSequence::create(CCScaleTo::create(0.1, 1.2),
                                                                  CCScaleTo::create(0.1, 1.0),
                                                                  NULL));
    }
    
    for (int i = kTagExample001; i <= kTagExample003; i++)
    {
         CJSprite* sp = (CJSprite*)getChildByTag(i);
        
        if(getChildByTag(i) != NULL && CJUtils::hitTestPoint(sp , tp, false))
        {
            for (int j = 0; j < mCompleteTargetTags->size(); j++)
            {
                if(mExamples->at(m_nCurrentStageIndex)->at(i-kTagExample001)->getCorrectTag() == mCompleteTargetTags->at(j))
                {
                    return false;
                }
            }
            
            showGuideCharacterLooping();
            
            playExampleNarrationRepeat(mExamples->at(m_nCurrentStageIndex)->at(i-kTagExample001)->getSoundPath());

            mExampleSelectIndex = i - kTagExample001;
            
            m_touchingExampleSp = GET_SELECTED_ITEM->getItemSprite();
            m_touchingExampleSp->setScale(1.2f);
            m_touchingExampleSp->setZOrder(kDepth6_dimmed);
                
            mTouchedPointGab = ccpSub(sp->getPosition(), tp);
            
            if(m_bIsGuide)
            {
                int target;
                
                switch (mGuideMoveCnt) {
                    case 0:
                        showHand(NULL, 1);
                        target = kTagTarget001;
                        break;
                    case 1:
                        showHand(NULL, 4);
                        target = kTagTarget002;
                        break;
                    case 2:
                        showHand(NULL, 7);
                        target = kTagTarget003;
                        break;
                    default:
                        break;
                }
                
                m_touchingExampleSp->runAction(CCMoveTo::create(0.7f, getChildByTag(target)->getPosition()));
                
                mGuideMoveCnt++;
            }
            
            return true;
        }
    }

    return false;
}

void E002_C030_P320::onTouchMoved(CCPoint tp)
{
    m_touchingExampleSp->setPosition(ccp(tp.x + mTouchedPointGab.x, tp.y + mTouchedPointGab.y));
}

void E002_C030_P320::onTouchEnded(CCPoint tp)
{
    stopExampleNarrationRepeat();
    
    for (int i = 0; i < mTargets->size(); i++)
    {
        if (CJUtils::hitTestPoint(m_touchingExampleSp, mTargets->at(i)->getPosition(), false))
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

void E002_C030_P320::intoTarget(CJSprite* sp, CCNode *target)
{
    for (int i = 0 ; i < mCompleteTargetTags->size(); i++)
    {
        if(mCompleteTargetTags->at(i) == target->getTag())
        {
            m_touchingExampleSp->runAction(CCSpawn::create(CCEaseBackOut::create(CCMoveTo::create(0.1, GET_SELECTED_ITEM->getOriginalPosition())),
                                                           CCScaleTo::create(0.1, 1.0),
                                                           NULL));
            setTouchEnableBaseLayer();
            return;
        }
    }
    
    sp->runAction(CCSequence::create(CCSpawn::create(CCEaseSineInOut::create(CCMoveTo::create(0.2, target->getPosition())),
                                                     CCScaleTo::create(0.1, 1),
                                                     NULL),
                                     CCDelayTime::create(0.5f),
                                     CCCallFuncND::create(this, callfuncND_selector(E002_C030_P320::checkAnswer), (void*)target->getTag()),
                                     NULL));
}

CCNode* E002_C030_P320::changeTexture(CCNode *node)
{
    CJSprite *sNode = CJPsdParser::getPsdSprite(GET_SELECTED_ITEM->getSelectImgPath(), m_psdDictionary);
    addChild(sNode, node->getZOrder(), node->getTag());
    sNode->setOpacity(0);
    
    node->runAction(CCSequence::create(CCFadeOut::create(0.2f),
                                       CCCallFuncN::create(this, callfuncN_selector(CJLayer::removeChild)),
                                       NULL));
    
    sNode->runAction(CCFadeIn::create(0.2f));
    
    for (int i = 0; i < GET_EXAMPLES->size(); i++)
    {
        if(GET_SELECTED_ITEM->getCorrectTag() == mTargets->at(i)->getTag())
        {
            mTargets->at(i)->setVisible(false);
            
            if (i == 0) {
                sNode->setZOrder(kDepth3_examples+1);
            }
            else if(i == 2)
            {
                sNode->setZOrder(kDepth3_examples-1);
            }
        }
    }
    
    return sNode;
}

void E002_C030_P320::checkAnswer(CCNode *node, int targetTag)
{
    if(targetTag ==  GET_SELECTED_ITEM->getCorrectTag())
    {
        if(!m_bIsGuide)
            setTouchEnableBaseLayer();
        
        mCompleteTargetTags->push_back(targetTag);
        CCNode *cNode = changeTexture(node);

        mSuccessCount++;
        
        if (mSuccessCount == 3)
        {
            cNode->runAction(CCSequence::create(CCDelayTime::create(0.3f),
                                               CCCallFuncN::create(this, callfuncN_selector(E002_C030_P320::onSuccesses)),
                                               NULL));
            //onSuccesses(node);
        }
    }
    else
    {
        node->runAction(CCSequence::create(CCDelayTime::create(0.1f),
                                           CCCallFuncN::create(this, callfuncN_selector(E002_C030_P320::onFails)),
                                           NULL));
    }
}

#pragma mark - feedback event

void E002_C030_P320::onExamplesTouched(int index)
{
    E002_Base_Question::onExamplesTouched(index);
}


void E002_C030_P320::onSuccesses(CCNode *node, int tag)
{
    setTouchDisalbeBaseLayer();
    
    mSndManager->playSuccessSfxSnd(13);
    
    CJUtils::performSelector(this, callfuncND_selector(E002_C030_P320::playQuestionSound),(void*)1, 0.5);
    
    float delay = 0.5;
    int showCount = 0;
    int startSprite = kTagTarget001;
    int i = 0;
    
    while (true)
    {
        if(showCount == 3)
        {
            break;
        }
        
        if(startSprite == GET_EXAMPLES->at(i)->getCorrectTag())
        {
            if(showCount == 2)
            {
                getChildByTag(GET_EXAMPLES->at(i)->getItemTag())->runAction(CCSequence::create(CCDelayTime::create(delay),
                                                                                   CCScaleTo::create(0.2, 1.2),
                                                                                   CCScaleTo::create(0.2, 1.0f),
                                                                                   CCDelayTime::create(0.2f),
                                                                                   CCCallFunc::create(this, callfunc_selector(E002_C030_P320::showSuccessTexture)),
                                                                                   NULL));
            }
            else
            {
                getChildByTag(GET_EXAMPLES->at(i)->getItemTag())->runAction(CCSequence::create(CCDelayTime::create(delay),
                                                                                   CCScaleTo::create(0.2, 1.2),
                                                                                   CCScaleTo::create(0.2, 1.0f),
                                                                                   NULL));
            }
            
            delay += 0.6f;
            showCount++;
            startSprite++;
         
            i = 0;
            
            continue;
        }
        
        i++;
    }
}

void E002_C030_P320::showSuccessTexture()
{
    getChildByTag(kTagDragTargetBg)->setVisible(true);
    
    for (int i = 0; i < GET_EXAMPLES->size(); i++)
    {
        removeChild(mTargets->at(i));
        removeChildByTag(GET_EXAMPLES->at(i)->getItemTag());
    }
    
    CJSprite *success = CJPsdParser::getPsdSprite(mQuestions->at(m_nCurrentStageIndex)->at(1), m_psdDictionary);
    addChild(success, kDepth2_questions, kTagSuccess);
    
    success->runAction(CCSequence::create(//CCDelayTime::create(0.5f),
                                          CCScaleTo::create(0.2f, 1.2),
                                          CCScaleTo::create(0.2f, 1.0f),
                                          CCDelayTime::create(1.0),
                                          NULL));
    
    getChildByTag(kTagQuestion)->runAction(CCSequence::create(//CCDelayTime::create(0.5f),
                                                              CCScaleTo::create(0.2f, 1.2),
                                                              CCScaleTo::create(0.2f, 1.0f),
                                                              NULL));
    
   
}

void E002_C030_P320::removeSuccessTexture()
{
    removeChildByTag(kTagQuestion);
    removeChildByTag(kTagSuccess);
}

void E002_C030_P320::onFails(CCNode *node, int tag)
{
    mFailCount++;
    
    mSndManager->playWrongSfxSnd(13);
    
    runAction(CCSequence::create(CCDelayTime::create(0.3f),
                                 CCCallFuncND::create(this, callfuncND_selector(E002_C030_P320::showWrongCharacterMotion), (void*)0),
                                 NULL));
    
    node->runAction(CCSequence::create(CCDelayTime::create(0.2f),
                                       CCEaseSineOut::create(CCScaleTo::create(0.2, 1.0)),
                                       CCEaseBackOut::create(CCMoveTo::create(0.2, GET_SELECTED_ITEM->getOriginalPosition())),
                                       NULL));
    
    setTouchEnableBaseLayer();
}

void E002_C030_P320::onComplete()
{
    E002_Base_Question::onComplete();

}

#pragma mark - user function

void E002_C030_P320::setQuestions()
{
    //if(mCompleteTargetTags != NULL)
    //    delete mCompleteTargetTags;
    
    resetValue();
    
    mCompleteTargetTags = new std::vector<int>();
    
    createTarget();
    
    CJSprite *question = CJPsdParser::getPsdSprite(mQuestions->at(m_nCurrentStageIndex)->at(0), m_psdDictionary);
    addChild(question, kDepth2_questions, kTagQuestion);
    
    CCRepeat *repeat = CCRepeat::create(CCSequence::create(CCMoveBy::create(0.5f, ccp(0, 10)),
                                                           CCMoveBy::create(0.5f, ccp(0, -10)),
                                                           NULL),
                                        -1);
    
    question->setScale(0);
    question->runAction(CCSequence::create(CCCallFuncND::create(this, callfuncND_selector(E002_C030_P320::playQuestionSound),(void*)0),
                                           CCEaseElasticOut::create(CCScaleTo::create(1, 1.0)),
                                           repeat,
                                           NULL));
    
}

void E002_C030_P320::showExamples()
{
    for (int i = 0; i<3; i++)
    {
        float delay = 1.0f;
        
        E002_Base_ExampleItem *item = GET_EXAMPLES->at(i);
        item->setOriginalPosition(CJPsdParser::getPsdPosition(item->getImgPath(), m_psdDictionary));
        
        item->setItemSprite(CJPsdParser::getPsdSprite(item->getImgPath(), m_psdDictionary));
        
        item->getItemSprite()->setPositionY(-160);
        addChild(item->getItemSprite(), kDepth3_examples, kTagExample001 + i);
        
        delay *= i;
        
        if( i == 2)
        {
            item->getItemSprite()->runAction(CCSequence::create(CCDelayTime::create(delay),
                                                                CCCallFuncND::create(this, callfuncND_selector(E002_C030_P320::playAppearanceExamplesSound), (void*)i),
                                                                CCEaseBackOut::create(CCMoveTo::create(0.3f, item->getOriginalPosition())),
                                                                CCCallFuncND::create(this, callfuncND_selector(E002_C030_P320::setReadyQuestion), (void*)true),
                                                                NULL));
        }
        else
        {
            item->getItemSprite()->runAction(CCSequence::create(CCDelayTime::create(delay),
                                                                CCCallFuncND::create(this, callfuncND_selector(E002_C030_P320::playAppearanceExamplesSound), (void*)i),
                                                                CCEaseBackOut::create(CCMoveTo::create(0.3f, item->getOriginalPosition())),
                                                                NULL));
        }
    }
}

void E002_C030_P320::setReadyQuestion(CCNode* node, bool isReady)
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

void E002_C030_P320::resetValue()
{
    
    mSuccessCount = 0;
    mFailCount = 0;
    
    removeChildByTag(kTagQuestion);
    removeChildByTag(kTagSuccess);
    removeChild(m_touchingExampleSp);
    
    showGuideCharacterLooping();
    
    getChildByTag(kTagDragTargetBg)->setVisible(false);
    
    setReadyQuestion(NULL, false);

    stopAllActions();
    
    for (int i = kTagExample001; i <= kTagTarget003; i++)
    {
        if (getChildByTag(i) != NULL)
        {
            removeChildByTag(i);
        }
    }
}

#pragma mark - sound & narration
void E002_C030_P320::playQuestionSound(CCNode* node, void* index)
{
    CCLog("playQuestionSound %s", mQuestionSounds->at(m_nCurrentStageIndex)->at((int)index).c_str());
    speakNarration(NULL, mQuestionSounds->at(m_nCurrentStageIndex)->at((int)index).c_str());
}

void E002_C030_P320::playAppearanceExamplesSound(CCNode* sender, void* index)
{
    speakNarration(NULL, mExamples->at(m_nCurrentStageIndex)->at((int)index)->getSoundPath().c_str());
}

  
#pragma mark - user function

void E002_C030_P320::speakNarration(CCNode* node, const char* fileName)
{
    stopAllNarration();
    playNarration(fileName); 
}


#pragma mark - navigation delegate

void E002_C030_P320::onTouchedNavigationButtonAtIndex()
{
    E002_Base_Question::onTouchedNavigationButtonAtIndex();
    
    E002_C030_P000_Index* _indexClass = E002_C030_P000_Index::create();
    _indexClass->init();
    _indexClass->setIndexDelegate(this);
    _indexClass->showIndex(this, _indexClass);
    addChild(_indexClass, kDepth11_Index);
}

void E002_C030_P320::onTouchedNavigationButtonAtInfo()
{
    E002_Base_Question::onTouchedNavigationButtonAtInfo();
     
    showGuide();
}

void E002_C030_P320::onTouchedNavigationButtonAtPrev()
{
    E002_Base_Question::onTouchedNavigationButtonAtPrev();
    if (m_nCurrentStageIndex > 0)
    {
        if(m_nCurrentStageIndex == 1)
        {
            replaceSceneTransitionFadeOut(E002_C030_P310);
            return;
        }
        
        m_nCurrentStageIndex--;
        setQuestions();
    }
}

void E002_C030_P320::onTouchedNavigationButtonAtNext()
{
    E002_Base_Question::onTouchedNavigationButtonAtNext();
    
    if (m_nCurrentStageIndex < m_nMaxStageCount - 1)
    {
        m_nCurrentStageIndex++;
        setQuestions();
    }
    else
    {
        //If you complete "Let's play3", call this function.
        completeLetsPlay3();
        
        //replayceScene
        replaceSceneTransitionFadeOut(E002_C030_P330);
    }
    
}

void E002_C030_P320::onTouchedNavigationButtonAtReward()
{
    showLetPlay3RewardPopup(NULL, m_nCurrentStageIndex + 3 - 1);
}

void E002_C030_P320::onTouchedNavigationButtonAtClose()
{
    E002_Base_Question::onTouchedNavigationButtonAtClose();
    
}

void E002_C030_P320::OnLastFrame(CJAnimation* pAnimation)
{
    E002_Base_Question::OnLastFrame(pAnimation);
     
    if(pAnimation->getName() == "e002_c030_p320_flash_s_cat02_boom_action")
    {
        if(m_bIsGuide)
        {
            ((E002_Base_Question*)getParent())->removeGuide();
            return;
        }
        
        removeAllAnimationsInDataPool("CHARACTERS");
        
        mPlayingGuideNarration = true;
        playAnimation("CHARACTERS", "e002_c030_p320_flash_walk_cat02_boom_action", 1,  kDepth3_examples);
        
        CJUtils::performSelector(this, callfuncND_selector(E002_C030_P320::playEffect), (void*)3, 0.5f);
        
        int index = m_nCurrentStageIndex - 1 + 3;
        CJUtils::performSelector(this, callfuncND_selector(E002_C030_P320::showLetPlay3RewardItem),(void*) index, 1.0f);
        
        if (m_nCurrentStageIndex == m_nMaxStageCount - 1)
        {
            //CJUtils::performSelector(this, callfunc_selector(E002_C030_P320::onTouchedNavigationButtonAtNext), 2.5f);
        }
    }
    else if (pAnimation->getName() == "e002_c030_p320_flash_walk_cat02_boom_action")
    {
        showGuideCharacterLooping();
        
        if (m_nCurrentStageIndex == m_nMaxStageCount - 1)
        {
            return;
        }
        
        CJUtils::performSelector(this, callfunc_selector(E002_C030_P320::onTouchedNavigationButtonAtNext), 0.5f);
    }
}

void E002_C030_P320::completeToGetRewardItem()
{
    E002_Base_Question::completeToGetRewardItem();
    
    CJUtils::performSelector(this, callfunc_selector(E002_C030_P320::onTouchedNavigationButtonAtNext), 0.0f);
}

#pragma mark - sprite create

void E002_C030_P320::createTarget()
{
    mTargets = new std::vector<CJSprite*>();
    
    CJSprite *targetSprite001 = CJSprite::create(getFilePath("img", "e002_c030_p320_guide_00.png").c_str());
    targetSprite001->setPosition(CJPsdParser::getPsdPosition("e002_c030_p320_guide_00", m_psdDictionary));
    addChild(targetSprite001, kDepth2_questions, kTagTarget001);
    
    CJSprite *targetSprite002 = CJSprite::create(getFilePath("img", "e002_c030_p320_guide_00.png").c_str());
    targetSprite002->setPosition(CJPsdParser::getPsdPosition("e002_c030_p320_guide_01", m_psdDictionary));
    addChild(targetSprite002, kDepth2_questions, kTagTarget002);
    
    CJSprite *targetSprite003 = CJSprite::create(getFilePath("img", "e002_c030_p320_guide_00.png").c_str());
    targetSprite003->setPosition(CJPsdParser::getPsdPosition("e002_c030_p320_guide_02", m_psdDictionary));
    addChild(targetSprite003, kDepth2_questions, kTagTarget003);
    
    mTargets->push_back(targetSprite001);
    mTargets->push_back(targetSprite002);
    mTargets->push_back(targetSprite003);
}

void E002_C030_P320::showSuccessCharacterMotion(CCNode *node, int index)
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
        
        mCharacters->showSuccess();
    }
    else
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
}

void E002_C030_P320::showWrongCharacterMotion(CCNode *node, int index)
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
        
        mCharacters->showFails();
    }
    else
    {
        if (m_nCurrentStageIndex%2 == 0)
        {
            if(mFailCount%2 == 0)
            {
                mSndManager->playBoomBoomWrongNarr(4);
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
                mSndManager->playBoomBoomWrongNarr(12);
            }
            else
            {
                mSndManager->playBoomBoomWrongNarr(4);
            }
        }
    }
}

void E002_C030_P320::playEffect(CCNode *node, int index)
{
    mSndManager->playLetsPlay3Effect(index);
}

void E002_C030_P320::showGuide()
{
    E002_Base_Question::showGuide();
    
    m_Guide = E002_C030_P320::create();
    m_Guide->init();
    m_Guide->setGuide(true);
    addChild(m_Guide, kDepth10_guide);
    
    std::vector<CCPoint> *guideHandPosition = new std::vector<CCPoint>();
    
    guideHandPosition->push_back(CJPsdParser::getPsdPosition("e002_common_img_guide_hand@00", m_psdDictionary));
    guideHandPosition->push_back(CJPsdParser::getPsdPosition("e002_common_img_guide_hand@01", m_psdDictionary));
    guideHandPosition->push_back(ccp(500, -200));
    guideHandPosition->push_back(CJPsdParser::getPsdPosition("e002_common_img_guide_hand@02", m_psdDictionary));
    guideHandPosition->push_back(CJPsdParser::getPsdPosition("e002_common_img_guide_hand@03", m_psdDictionary));
    guideHandPosition->push_back(ccp(500, -200));
    guideHandPosition->push_back(CJPsdParser::getPsdPosition("e002_common_img_guide_hand@04", m_psdDictionary));
    guideHandPosition->push_back(CJPsdParser::getPsdPosition("e002_common_img_guide_hand@05", m_psdDictionary));

    m_Guide->setGuideHandPosition(guideHandPosition);
}

void E002_C030_P320::removeGuide()
{
    E002_Base_Question::removeGuide();
    removeChild(m_Guide);
    
}

void E002_C030_P320::completeToMoveHand(CCNode *node, int index)
{
    switch (index) {
        case 0:
            onTouchBegan(getChildByTag(kTagExample003)->getPosition());
            break;
        case 1:
            onTouchEnded(getChildByTag(kTagTarget001)->getPosition());
            showHand(NULL, 2);
            break;
        case 2:
            CJUtils::performSelector(this, callfuncND_selector(E002_Base_Question::showHand), (void*)3, 0.3f);
            break;
        case 3:
            onTouchBegan(getChildByTag(kTagExample001)->getPosition());
            break;
        case 4:
            onTouchEnded(getChildByTag(kTagTarget002)->getPosition());
            showHand(NULL, 5);
            break;
        case 5:
            CJUtils::performSelector(this, callfuncND_selector(E002_Base_Question::showHand), (void*)6, 0.3f);
            break;
        case 6:
            onTouchBegan(getChildByTag(kTagExample002)->getPosition());
            break;
        case 7:
            onTouchEnded(getChildByTag(kTagTarget003)->getPosition());
            break;
        default:
            break;
    }
}

void E002_C030_P320::completeFirstGuide()
{
    CJUtils::performSelector(this, callfunc_selector(E002_C030_P320::setQuestions),0.3);
}