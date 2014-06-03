

#include "E002_C030_P110.h"
#include "E002_C030_P130.h"
#include "E002_C030_P000_Index.h"
#include "E002_C030_P200_Intro.h"
#include "E002_C030_CompletePopup.h"

enum
{
    kTagPieceBlank001 = 200,
    kTagPieceBlank002,
    kTagPieceBlank003,
    kTagPieceBlank004,
    kTagPieceBlank005,
    
    kTagPieceNormal001,
    kTagPieceNormal002,
    kTagPieceNormal003,
    kTagPieceNormal004,
    kTagPieceNormal005,
    
    kTagPieceSelect001,
    kTagPieceSelect002,
    kTagPieceSelect003,
    kTagPieceSelect004,
    kTagPieceSelect005,
    

    
};

E002_C030_P130::E002_C030_P130()
{
    mExamples = new std::vector<E002_Base_ExampleItem*>();
    mQuestions = new std::vector<std::string>();
    mCompleteTargetTags = new std::vector<int>();
    
    m_touchingExampleSp = NULL;
    mSndManager = new E002_C030_SoundManager();
}

E002_C030_P130::~E002_C030_P130()
{
    CC_SAFE_DELETE(mExamples);
}

#pragma mark - init

bool E002_C030_P130::init()
{
    if (!E002_Base_Reward::init()) {
        return false;
    }
    
    mSuccessCount = 0;
    
    return true;
}

void E002_C030_P130::onEnter()
{
    E002_Base_Reward::onEnter();
    
    const char* questionImgName[5] =
    {
        "e002_c030_p130_piece00_blank",
        "e002_c030_p130_piece01_blank",
        "e002_c030_p130_piece02_blank",
        "e002_c030_p130_piece03_blank",
        "e002_c030_p130_piece04_blank",
  
    };
    
    const char* exampleImgName[5][2] =
    {
        {
            "e002_c030_p130_piece00_n",
            "e002_c030_p130_piece00_s"
        },
        {
            "e002_c030_p130_piece01_n",
            "e002_c030_p130_piece01_s"
        },
        {
            "e002_c030_p130_piece02_n",
            "e002_c030_p130_piece02_s"
        },
        {
            "e002_c030_p130_piece03_n",
            "e002_c030_p130_piece03_s"
        },
        {
            "e002_c030_p130_piece04_n",
            "e002_c030_p130_piece04_s"
        }
    };
    
    for (int i = 0; i < 5; i++)
    {
        mExamples->push_back(new E002_Base_ExampleItem(i, exampleImgName[i][0], exampleImgName[i][1], "", kTagPieceNormal001 + i, kTagPieceBlank001+ i));
        mQuestions->push_back(questionImgName[i]);
    }
    
    onViewLoad();
}

void E002_C030_P130::onExit()
{
    E002_Base_Reward::onExit();
}


void E002_C030_P130::onViewLoad()
{
    E002_Base_Reward::onViewLoad();
     
    CJPsdParser::parseToPsdJSON("e002_c030_p130.json", &m_psdDictionary);
    
    CJSprite *bg = CJPsdParser::getPsdSprite("e002_c030_p130_bg00_00", m_psdDictionary);
    addChild(bg, kDepth0_backImage+5);

    CJSprite *bg2 = CJPsdParser::getPsdSprite("e002_c030_p130_bg00_02", m_psdDictionary);
    addChild(bg2, kDepth4_title);

    createBlankPiece();
    showFire();
    
    setAnimationFile("e002_c030_p130_flash_reward_sheets.json", "e002_c030_p130_flash_reward_animations.json", "MEERKAT");
    
    animationManagerParseStart();
    
    setTouchDisalbeBaseLayer();
}

void E002_C030_P130::onViewLoaded()
{
    E002_Base_Reward::onViewLoaded();
    
    CJMultimedia::getInstance()->playBGM(getFilePath("snd","e002_c030_snd_bgm_play01.mp3"), true);
    
    animationManagerParseComplete();
}

void E002_C030_P130::startFlashAnimation()
{
    createAllAnimations();
    
    CJAnimation *ani = playAnimation("MEERKAT", "e002_c030_p130_flash_reward_mk_action", 1, kDepth6_dimmed);
    
    addNarrationOnFlashFrame(ani, 20, getFilePath("snd","e002_c030_p230_snd_01_mk.mp3").c_str());
    addEffectOnFlashFrame(ani, 0, getFilePath("snd","e002_c030_p130_sfx_appear_mk.mp3").c_str());
    addEffectOnFlashFrame(ani, 169, getFilePath("snd","e002_c030_p130_sfx_appear_mk.mp3").c_str());

}

void E002_C030_P130::onFirstNarration()
{
    E002_Base_Reward::onFirstNarration();
    
}

void E002_C030_P130::onFirstNarrationEnd()
{
    E002_Base_Reward::onFirstNarrationEnd();
}


void E002_C030_P130::onNarrationFinishedCallback(std::string fileName)
{
    /*if (fileName == mFirstNarration && !isFirstSkiped())
    {
        onFirstNarrationEnd();
    }
*/
}

#pragma mark - touch

bool E002_C030_P130::onTouchBegan(CCPoint tp)
{
    for (int i = kTagPieceNormal001; i <= kTagPieceNormal005; i++)
    {
        CJSprite* sp = (CJSprite*)getChildByTag(i);
        
        if(getChildByTag(i) != NULL && CJUtils::hitTestPoint(sp , tp, false))
        {
            mTouchedItem = mExamples->at(i - kTagPieceNormal001);
            
            m_touchingExampleSp = sp;
            m_touchingExampleSp->setScale(1.3f);
            m_touchingExampleSp->setZOrder(kDepth2_questions+1);
            
            mTouchedPointGab = ccpSub(sp->getPosition(), tp);
            return true;
            
        }
    }
    
    return false;
}

void E002_C030_P130::onTouchMoved(CCPoint tp)
{
    m_touchingExampleSp->setPosition(ccp(tp.x + mTouchedPointGab.x, tp.y + mTouchedPointGab.y));
}

void E002_C030_P130::onTouchEnded(CCPoint tp)
{
    for (int i = 0; i < mQuestions->size(); i++)
    {
        CJSprite *blank = (CJSprite*)getChildByTag(kTagPieceBlank001 + i);

        if (CJUtils::hitTestPoint(m_touchingExampleSp, blank->getPosition(), false))
        {
            intoTarget(m_touchingExampleSp, blank);
            return;
        }
    }
    
    setTouchEnableBaseLayer();
    
    m_touchingExampleSp->runAction(CCSpawn::create(CCEaseBackOut::create(CCMoveTo::create(0.1, mTouchedItem->getOriginalPosition())),
                                                   CCScaleTo::create(0.1, 1.0),
                                                   NULL));
    
}

void E002_C030_P130::intoTarget(CJSprite* sp, CJSprite *target)
{
    setTouchDisalbeBaseLayer();
    
    for (int i = 0 ; i < mCompleteTargetTags->size(); i++)
    {
        if(mCompleteTargetTags->at(i) == target->getTag())
        {
            setTouchEnableBaseLayer();
            
            m_touchingExampleSp->runAction(CCSpawn::create(CCEaseBackOut::create(CCMoveTo::create(0.1, mTouchedItem->getOriginalPosition())),
                                                           CCScaleTo::create(0.1, 1.0),
                                                           NULL));
            return;
        }
    }
    
    if(mTouchedItem->getCorrectTag() == target->getTag())
    {
        playEffect(NULL, 11);
    }
    
    sp->runAction(CCSequence::create(CCSpawn::create(CCEaseSineInOut::create(CCMoveTo::create(0.2, ccp(target->getPositionX()+2, target->getPositionY()-3 ))),
                                                     CCScaleTo::create(0.1, 1.2),
                                                     NULL),
                                     //CCDelayTime::create(0.5f),
                                     CCCallFuncND::create(this, callfuncND_selector(E002_C030_P130::checkAnswer), (void*)target->getTag()),
                                     NULL));
}

void E002_C030_P130::checkAnswer(CCNode *node, int targetTag)
{
    if(mTouchedItem->getCorrectTag() == targetTag)
    {
        mCompleteTargetTags->push_back(targetTag);
        
        CJSprite *sel = CJPsdParser::getPsdSprite(mTouchedItem->getSelectImgPath(), m_psdDictionary);
        addChild(sel, mTouchedItem->getItemSprite()->getZOrder());
        
        getChildByTag(mTouchedItem->getItemSprite()->getTag() - 5)->setVisible(false);
        removeChild(mTouchedItem->getItemSprite());
        
        onSuccesses(node);
    }
    else
    {
        onFails(node);
    }
}

#pragma mark - feedback event
void E002_C030_P130::onSuccesses(CCNode *node)
{
    setTouchEnableBaseLayer();
    
    mSuccessCount++;

    if(mSuccessCount > 4)
    {
        onComplete();
    }
    
}

void E002_C030_P130::onComplete()
{
    playEffect(NULL, 13);
    CJAnimation *ani = playAnimation("MEERKAT", "e002_c030_p130_flash_reward_action", 1, kDepth4_title-1);
    
    addNarrationOnFlashFrame(ani, 203 - 179, getFilePath("snd","e002_c030_p000_snd_s_07_01_ar.mp3").c_str());
    addNarrationOnFlashFrame(ani, 203 - 179, getFilePath("snd","e002_c030_p000_snd_s_07_01_as.mp3").c_str());
    addNarrationOnFlashFrame(ani, 203 - 179, getFilePath("snd","e002_c030_p000_snd_s_07_01_bb.mp3").c_str());
    
    addEffectOnFlashFrame(ani, 179-179, getFilePath("snd","e002_c030_p130_sfx_run_all.mp3").c_str());

    //addEffectOnFlashFrame(ani, 228-179, getFilePath("snd","e002_c030_p130_sfx_run01.mp3").c_str());
    //addEffectOnFlashFrame(ani, 305-179, getFilePath("snd","e002_c030_p130_sfx_plane_ar.mp3").c_str());

}

void E002_C030_P130::onFails(CCNode *node)
{
    setTouchEnableBaseLayer();
    
    playEffect(NULL, 12);
    m_touchingExampleSp->runAction(CCSpawn::create(CCEaseBackOut::create(CCMoveTo::create(0.1, mTouchedItem->getOriginalPosition())),
                                                   CCScaleTo::create(0.1, 1.0),
                                                   NULL));
}

#pragma mark - user function

void E002_C030_P130::setQuestions()
{
    float delay = 0.0f;
    
    for (int i = kTagPieceNormal001; i <= kTagPieceNormal005; i++)
    {
        E002_Base_ExampleItem *item = mExamples->at(i - kTagPieceNormal001);
        item->setOriginalPosition(CJPsdParser::getPsdPosition(item->getImgPath(), m_psdDictionary));

        CJSprite *example = CJPsdParser::getPsdSprite(item->getImgPath(), m_psdDictionary);
        addChild(example, kDepth3_examples, i);
        
        item->setItemSprite(example);
        example->setScale(0);
        
        if(i == kTagPieceNormal005)
        {
            example->runAction(CCSequence::create(CCDelayTime::create(delay),
                                                  CCCallFuncND::create(this, callfuncND_selector(E002_C030_P130::playEffect), (void*)10),
                                                  CCEaseElasticOut::create(CCScaleTo::create(1, 1.0)),
                                                  CCCallFunc::create(this, callfunc_selector(E002_C030_P130::setTouchEnableBaseLayer)),
                                                  NULL));
        }
        else
        {
            example->runAction(CCSequence::create(CCDelayTime::create(delay),
                                                  CCCallFuncND::create(this, callfuncND_selector(E002_C030_P130::playEffect), (void*)10),
                                                  CCEaseElasticOut::create(CCScaleTo::create(1, 1.0)),
                                                  NULL));
        }
        
        delay += 0.5f;
        
    }
}

void E002_C030_P130::playEffect(CCNode* node, int index)
{
    mSndManager->playLetsPlay1Effect(index);
}

void E002_C030_P130::completeShowExamples()
{
    CJSprite *exampleBG = CJPsdParser::getPsdSprite("e002_c030_p130_bg00_01", m_psdDictionary);
    addChild(exampleBG, kDepth1_flash);
    
    setTouchEnableBaseLayer();
}

#pragma mark - sound & narration


#pragma mark - navigation delegate

void E002_C030_P130::onTouchedNavigationButtonAtIndex()
{
    E002_Base_Reward::onTouchedNavigationButtonAtIndex();
    
    E002_C030_P000_Index* _indexClass = E002_C030_P000_Index::create();
    _indexClass->init();
    _indexClass->setIndexDelegate(this);
    _indexClass->showIndex(this, _indexClass);
    addChild(_indexClass, kDepth11_Index);
}

void E002_C030_P130::onTouchedNavigationButtonAtInfo()
{
    E002_Base_Reward::onTouchedNavigationButtonAtInfo();
    
    /* If you use two page for image guide, must use this coding text.
     
    std::vector<E002_Base_ImageGuide_Item*> *items = new std::vector<E002_Base_ImageGuide_Item*>();
     
    items->push_back(new E002_Base_ImageGuide_Item("e002_c030_p130_guide.jpg",
                                                   CJPsdParser::getPsdPosition("e002_common_img_guide_hand@00", m_psdDictionary),
                                                   CJPsdParser::getPsdPosition("e002_common_img_guide_hand@01", m_psdDictionary)
                                                   ));
    items->push_back(new E002_Base_ImageGuide_Item("e002_c030_p130_guide.jpg",
                                                   CJPsdParser::getPsdPosition("e002_common_img_guide_hand@00", m_psdDictionary),
                                                   CJPsdParser::getPsdPosition("e002_common_img_guide_hand@01", m_psdDictionary)
                                                   ));
    showGuide(items);
    */
    
    // One page guide
    showGuide(new E002_Base_ImageGuide_Item("e002_c030_p130_guide.jpg",
                                            CJPsdParser::getPsdPosition("e002_common_img_guide_hand@00", m_psdDictionary),
                                            CJPsdParser::getPsdPosition("e002_common_img_guide_hand@01", m_psdDictionary)
                                            ));
     
     
}

void E002_C030_P130::onTouchedNavigationButtonAtPrev()
{
    E002_Base_Reward::onTouchedNavigationButtonAtPrev();
    
    replaceSceneTransitionFadeOut(E002_C030_P110);

}

void E002_C030_P130::onTouchedNavigationButtonAtNext()
{
    E002_Base_Reward::onTouchedNavigationButtonAtNext();
    
    replaceSceneTransitionFadeOut(E002_C030_P200_Intro);
    
}

void E002_C030_P130::OnLastFrame(CJAnimation* pAnimation)
{
    E002_Base_Reward::OnLastFrame(pAnimation);
    
    if(pAnimation->getName() == "e002_c030_p130_flash_reward_mk_action")
    {
        if (getUserDefaultFirstGuide(eGuidePageP130) == false)
        {
            mShowFirstGuide = true;
            
            setUserDefaultFirstGuide(eGuidePageP130);
            
            showGuide(new E002_Base_ImageGuide_Item("e002_c030_p130_guide.jpg",
                                                    CJPsdParser::getPsdPosition("e002_common_img_guide_hand@00", m_psdDictionary),
                                                    CJPsdParser::getPsdPosition("e002_common_img_guide_hand@01", m_psdDictionary)
                                                    ));
        }
        else
        {
            CJUtils::performSelector(this, callfunc_selector(E002_C030_P130::setQuestions),0.0);
        }
    }
    else if(pAnimation->getName() == "e002_c030_p130_flash_reward_action")
    {
        CJUtils::performSelector(this, callfunc_selector(E002_C030_P130::showCompletePopup), 1.0f);
    }
}

void E002_C030_P130::showCompletePopup()
{
    E002_C030_CompletePopup *cPopup = new E002_C030_CompletePopup();
    cPopup->init(P100);
    addChild(cPopup, kDepth10_guide);
    
    cPopup->showPopup(this);
    cPopup->showCompletePopup();
}

#pragma mark - sprite create
void E002_C030_P130::createBlankPiece()
{
    for (int i = kTagPieceBlank001; i <= kTagPieceBlank005; i++)
    {
        CJSprite *blank = CJPsdParser::getPsdSprite(mQuestions->at(i - kTagPieceBlank001), m_psdDictionary);
        addChild(blank, kDepth2_questions, i);
    }
}

void E002_C030_P130::showFire()
{
    CJSprite *leftFire = CJPsdParser::getPsdSprite("e002_c030_p130_img_fire_on00@0", m_psdDictionary);
    addChild(leftFire, kDepth1_flash);
    
    leftFire->runAction(CJUtils::getSeqAction(-1, 0.2f,
                                              getFilePath("img","e002_c030_p130_img_fire_on01.png").c_str(),
                                              getFilePath("img","e002_c030_p130_img_fire_on02.png").c_str(),
                                              getFilePath("img","e002_c030_p130_img_fire_on03.png").c_str(),
                                              getFilePath("img","e002_c030_p130_img_fire_on04.png").c_str(),
                                              NULL));
    
    CJSprite *rightFire = CJPsdParser::getPsdSprite("e002_c030_p130_img_fire_on00@1", m_psdDictionary);
    addChild(rightFire, kDepth1_flash);
    
    rightFire->runAction(CJUtils::getSeqAction(-1, 0.2f,
                                               getFilePath("img","e002_c030_p130_img_fire_on01.png").c_str(),
                                               getFilePath("img","e002_c030_p130_img_fire_on02.png").c_str(),
                                               getFilePath("img","e002_c030_p130_img_fire_on03.png").c_str(),
                                               getFilePath("img","e002_c030_p130_img_fire_on04.png").c_str(),
                                               NULL));
}

void E002_C030_P130::completeFirstGuide()
{
    CJUtils::performSelector(this, callfunc_selector(E002_C030_P130::setQuestions),0.0);
}
