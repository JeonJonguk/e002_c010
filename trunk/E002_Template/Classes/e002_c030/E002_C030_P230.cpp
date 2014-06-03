
#include "E002_C030_P210.h"
#include "E002_C030_P230.h"
#include "E002_C030_P000_Index.h"
#include "E002_C030_P300_Intro.h"
#include "E002_C030_CompletePopup.h"

enum
{
    kTagPieceBlank001 = 200,
    kTagPieceBlank002,
    kTagPieceBlank003,
    kTagPieceBlank004,
    kTagPieceBlank005,
    kTagPieceBlank006,
    kTagPieceBlank007,
    
    kTagPieceNormal001,
    kTagPieceNormal002,
    kTagPieceNormal003,
    kTagPieceNormal004,
    kTagPieceNormal005,
    kTagPieceNormal006,
    kTagPieceNormal007,
    
    kTagPieceSelect001,
    kTagPieceSelect002,
    kTagPieceSelect003,
    kTagPieceSelect004,
    kTagPieceSelect005,
    kTagPieceSelect006,
    kTagPieceSelect007,
    
    kTagBox = 255,
    kTagDoor,
    kTagDoorShadow,
};

E002_C030_P230::E002_C030_P230()
{
    mExamples = new std::vector<E002_Base_ExampleItem*>();
    mQuestions = new std::vector<std::string>();
    mCompleteTargetTags = new std::vector<int>();
    
    m_touchingExampleSp = NULL;
    mSndManager = new E002_C030_SoundManager();
}

E002_C030_P230::~E002_C030_P230()
{
    CC_SAFE_DELETE(mExamples);
}

#pragma mark - init

bool E002_C030_P230::init()
{
    if (!E002_Base_Reward::init()) {
        return false;
    }
    
    mSuccessCount = 0;
    
    return true;
}

void E002_C030_P230::onEnter()
{
    E002_Base_Reward::onEnter();
    
    const char* questionImgName[7] =
    {
        "e002_c030_p230_piece00_s",
        "e002_c030_p230_piece01_s",
        "e002_c030_p230_piece02_s",
        "e002_c030_p230_piece03_s",
        "e002_c030_p230_piece04_s",
        "e002_c030_p230_piece05_s",
        "e002_c030_p230_piece06_s",
    };
    
    const char* exampleImgName[7][2] =
    {
        {
            "e002_c030_p230_piece00_n",
            "e002_c030_p230_piece00_s"
        },
        {
            "e002_c030_p230_piece01_n",
            "e002_c030_p230_piece01_s"
        },
        {
            "e002_c030_p230_piece02_n",
            "e002_c030_p230_piece02_s"
        },
        {
            "e002_c030_p230_piece03_n",
            "e002_c030_p230_piece03_s"
        },
        {
            "e002_c030_p230_piece04_n",
            "e002_c030_p230_piece04_s"
        },
        {
            "e002_c030_p230_piece05_n",
            "e002_c030_p230_piece05_s"
        },
        {
            "e002_c030_p230_piece06_n",
            "e002_c030_p230_piece06_s"
        }
    };
    
    for (int i = 0; i < 7; i++)
    {
        mExamples->push_back(new E002_Base_ExampleItem(i, exampleImgName[i][0], exampleImgName[i][1], "", kTagPieceNormal001 + i, kTagPieceBlank001+ i));
        mQuestions->push_back(questionImgName[i]);
    }
    
    onViewLoad();
}

void E002_C030_P230::onExit()
{
    E002_Base_Reward::onExit();
}


void E002_C030_P230::onViewLoad()
{
    E002_Base_Reward::onViewLoad();
    
    CJPsdParser::parseToPsdJSON("e002_c030_p230.json", &m_psdDictionary);
    
    
    CJSprite *bg = CJPsdParser::getPsdSprite("e002_c030_p230_bg00_00", m_psdDictionary);
    addChild(bg, kDepth0_backImage);

    CJSprite *door = CJPsdParser::getPsdSprite("e002_c030_p230_door_n", m_psdDictionary);
    addChild(door, kDepth0_backImage, kTagDoor);
    
    CJSprite *doorShadow = CJPsdParser::getPsdSprite("e002_c030_p230_door_shadow", m_psdDictionary);
    addChild(doorShadow, kDepth0_backImage, kTagDoorShadow);
    
    CJSprite *doorUp = CJPsdParser::getPsdSprite("e002_c030_p230_door_up", m_psdDictionary);
    addChild(doorUp, kDepth5_particle);
    
    setAnimationFile("e002_c030_p230_flash_reward_sheets.json", "e002_c030_p230_flash_reward_animations.json", "MEERKAT");
    
    animationManagerParseStart();
    
    setTouchDisalbeBaseLayer();
}

void E002_C030_P230::onViewLoaded()
{
    E002_Base_Reward::onViewLoaded();
    
    CJMultimedia::getInstance()->playBGM(getFilePath("snd","e002_c030_snd_bgm_play02.mp3"), true);

    createBlankPiece();
    
    animationManagerParseComplete();
}

void E002_C030_P230::startFlashAnimation()
{
    createAllAnimations();
    
    CJAnimation *ani = playAnimation("MEERKAT", "e002_c030_p230_flash_reward_mk_action", 1, kDepth6_dimmed);
    
    addNarrationOnFlashFrame(ani, 20, getFilePath("snd","e002_c030_p230_snd_01_mk.mp3").c_str());
    addEffectOnFlashFrame(ani, 0, getFilePath("snd","e002_c030_p130_sfx_appear_mk.mp3").c_str());
    addEffectOnFlashFrame(ani, 120, getFilePath("snd","e002_c030_p130_sfx_appear_mk.mp3").c_str());

}

void E002_C030_P230::onFirstNarration()
{
    E002_Base_Reward::onFirstNarration();
    
}

void E002_C030_P230::onFirstNarrationEnd()
{
    E002_Base_Reward::onFirstNarrationEnd();
}


void E002_C030_P230::onNarrationFinishedCallback(std::string fileName)
{

}

#pragma mark - touch

bool E002_C030_P230::onTouchBegan(CCPoint tp)
{
    for (int i = kTagPieceNormal001; i <= kTagPieceNormal007; i++)
    {
        CJSprite* sp = (CJSprite*)getChildByTag(i);
        
        if(getChildByTag(i) != NULL && CJUtils::hitTestPoint(sp , tp, false))
        {
            mTouchedItem = mExamples->at(i - kTagPieceNormal001);
            
            m_touchingExampleSp = sp;
            m_touchingExampleSp->setScale(1.3f);
            m_touchingExampleSp->setZOrder(kDepth6_dimmed);
            
            mTouchedPointGab = ccpSub(sp->getPosition(), tp);
            return true;
            
        }
    }
    
    return false;
}

void E002_C030_P230::onTouchMoved(CCPoint tp)
{
    m_touchingExampleSp->setPosition(ccp(tp.x + mTouchedPointGab.x, tp.y + mTouchedPointGab.y));
}

void E002_C030_P230::onTouchEnded(CCPoint tp)
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

void E002_C030_P230::intoTarget(CJSprite* sp, CJSprite *target)
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
        playEffect(NULL, 8);
    }
    
    sp->runAction(CCSequence::create(CCSpawn::create(CCEaseSineInOut::create(CCMoveTo::create(0.2, target->getPosition())),
                                                     CCScaleTo::create(0.1, 1.2),
                                                     NULL),
                                     CCDelayTime::create(0.5f),
                                     CCCallFuncND::create(this, callfuncND_selector(E002_C030_P230::checkAnswer), (void*)target->getTag()),
                                     NULL));
}

void E002_C030_P230::checkAnswer(CCNode *node, int targetTag)
{
    if(mTouchedItem->getCorrectTag() == targetTag)
    {
        mCompleteTargetTags->push_back(targetTag);
        
        onSuccesses(node);
    }
    else
    {
        onFails(node);
    }
}

#pragma mark - feedback event
void E002_C030_P230::onSuccesses(CCNode *node)
{
    setTouchEnableBaseLayer();
    
    mSuccessCount++;

    if(mSuccessCount > 6)
    {
        CJUtils::performSelector(this, callfunc_selector(E002_C030_P230::onComplete), 1.0);
    }
    
}

void E002_C030_P230::onComplete()
{
    playEffect(NULL, 10);
    hideBox();
    
    CJSprite *sucSeq = CJPsdParser::getPsdSprite("e002_c030_p230_door_success_seq00", m_psdDictionary);
    addChild(sucSeq, kDepth4_title);
    
    
    
    sucSeq->runAction(CCSequence::create(CJUtils::getSeqAction(1, 0.3, getFilePath("img","e002_c030_p230_door_success_seq01.png").c_str(),
                                                                       getFilePath("img","e002_c030_p230_door_success_seq02.png").c_str(),
                                                                       getFilePath("img","e002_c030_p230_door_success_seq03.png").c_str(),
                                                               NULL),
                                         CCCallFunc::create(this, callfunc_selector(E002_C030_P230::removeDoor)),
                                         CCMoveBy::create(1.0, ccp(0, 500)),
                                         CCCallFunc::create(this, callfunc_selector(E002_C030_P230::playSuccessFlash)),
                                         NULL));
    
}

void E002_C030_P230::playSuccessFlash()
{
    CJAnimation *ani = playAnimation("MEERKAT", "e002_c030_p230_flash_reward_action", 1, kDepth6_dimmed);
    
    addNarrationOnFlashFrame(ani, 130 - 130, getFilePath("snd","e002_c030_p230_snd_04_as.mp3").c_str());
    addNarrationOnFlashFrame(ani, 138 - 130, getFilePath("snd","e002_c030_p000_snd_s_07_01_ar.mp3").c_str());
    
    addEffectOnFlashFrame(ani, 193-130, getFilePath("snd","e002_c030_p230_sfx_jump_ar.mp3").c_str());
    addEffectOnFlashFrame(ani, 130-130, getFilePath("snd","e002_c030_p230_sfx_jump_as.mp3").c_str());

}

void E002_C030_P230::removeDoor()
{
    for (int i = kTagPieceNormal001; i <= kTagPieceNormal007; i++)
    {
        removeChildByTag(i);
    }
    
    removeChildByTag(kTagDoor);
}

void E002_C030_P230::onFails(CCNode *node)
{
    setTouchEnableBaseLayer();

    playEffect(NULL, 9);
    m_touchingExampleSp->runAction(CCSpawn::create(CCEaseBackOut::create(CCMoveTo::create(0.1, mTouchedItem->getOriginalPosition())),
                                                   CCScaleTo::create(0.1, 1.0),
                                                   NULL));
}

#pragma mark - user function

void E002_C030_P230::setQuestions()
{
    float delay = 0.0f;
    
    for (int i = kTagPieceNormal001; i <= kTagPieceNormal007; i++)
    {
        E002_Base_ExampleItem *item = mExamples->at(i - kTagPieceNormal001);
        item->setOriginalPosition(CJPsdParser::getPsdPosition(item->getImgPath(), m_psdDictionary));

        CJSprite *example = CJPsdParser::getPsdSprite(item->getImgPath(), m_psdDictionary);
        addChild(example, kDepth3_examples, i);
        
        example->setScale(0);
        
        if(i == kTagPieceNormal007)
        {
            example->runAction(CCSequence::create(CCDelayTime::create(delay),
                                                  CCCallFuncND::create(this, callfuncND_selector(E002_C030_P230::playEffect), (void*)7),
                                                  CCEaseElasticOut::create(CCScaleTo::create(1, 1.0)),
                                                  CCCallFunc::create(this, callfunc_selector(E002_C030_P230::completeShowExamples)),
                                                  NULL));
        }
        else
        {
            example->runAction(CCSequence::create(CCDelayTime::create(delay),
                                                  CCCallFuncND::create(this, callfuncND_selector(E002_C030_P230::playEffect), (void*)7),
                                                  CCEaseElasticOut::create(CCScaleTo::create(1, 1.0)),
                                                  NULL));
        }
        
        delay += 0.4f;
        
    }
}

void E002_C030_P230::playEffect(CCNode* node, int index)
{
    mSndManager->playLetsPlay2Effect(index);
}

void E002_C030_P230::completeShowExamples()
{
    setTouchEnableBaseLayer();
}

#pragma mark - sound & narration


#pragma mark - navigation delegate

void E002_C030_P230::onTouchedNavigationButtonAtIndex()
{
    E002_Base_Reward::onTouchedNavigationButtonAtIndex();
    
    E002_C030_P000_Index* _indexClass = E002_C030_P000_Index::create();
    _indexClass->init();
    _indexClass->setIndexDelegate(this);
    _indexClass->showIndex(this, _indexClass);
    addChild(_indexClass, kDepth11_Index);
}

void E002_C030_P230::onTouchedNavigationButtonAtInfo()
{
    E002_Base_Reward::onTouchedNavigationButtonAtInfo();
    
    showGuide(new E002_Base_ImageGuide_Item("e002_c030_p230_guide.jpg",
                                            CJPsdParser::getPsdPosition("e002_common_img_guide_hand@00", m_psdDictionary),
                                            CJPsdParser::getPsdPosition("e002_common_img_guide_hand@01", m_psdDictionary)
                                            ));
}

void E002_C030_P230::onTouchedNavigationButtonAtPrev()
{
    E002_Base_Reward::onTouchedNavigationButtonAtPrev();
    
    replaceSceneTransitionFadeOut(E002_C030_P210);
}

void E002_C030_P230::onTouchedNavigationButtonAtNext()
{
    E002_Base_Reward::onTouchedNavigationButtonAtNext();
    
    replaceSceneTransitionFadeOut(E002_C030_P300_Intro);
    
}

void E002_C030_P230::OnLastFrame(CJAnimation* pAnimation)
{
    E002_Base_Reward::OnLastFrame(pAnimation);
    
    if(pAnimation->getName() == "e002_c030_p230_flash_reward_mk_action")
    {
        if (getUserDefaultFirstGuide(eGuidePageP230) == false)
        {
            mShowFirstGuide = true;
            setUserDefaultFirstGuide(eGuidePageP230);
            
            showGuide(new E002_Base_ImageGuide_Item("e002_c030_p230_guide.jpg",
                                                    CJPsdParser::getPsdPosition("e002_common_img_guide_hand@00", m_psdDictionary),
                                                    CJPsdParser::getPsdPosition("e002_common_img_guide_hand@01", m_psdDictionary)
                                                    ));
        }
        else
        {
            showBox();
            CJUtils::performSelector(this, callfunc_selector(E002_C030_P230::setQuestions),1.0f);
        }
    }
    else if(pAnimation->getName() == "e002_c030_p230_flash_reward_action")
    {
        CJUtils::performSelector(this, callfunc_selector(E002_C030_P230::showCompletePopup), 1.0f);
    }
}

void E002_C030_P230::showCompletePopup()
{
    E002_C030_CompletePopup *cPopup = new E002_C030_CompletePopup();
    cPopup->init(P200);
    addChild(cPopup, kDepth10_guide);
    
    cPopup->showPopup(this);
    cPopup->showCompletePopup();
}

void E002_C030_P230::completeFirstGuide()
{
    showBox();
    CJUtils::performSelector(this, callfunc_selector(E002_C030_P230::setQuestions),1.0f);
}

#pragma mark - sprite create
void E002_C030_P230::createBlankPiece()
{
    for (int i = kTagPieceBlank001; i <= kTagPieceBlank007; i++)
    {
        CJSprite *blank = CJPsdParser::getPsdSprite(mQuestions->at(i - kTagPieceBlank001), m_psdDictionary);
        addChild(blank, kDepth2_questions, i);
        blank->setVisible(false);
    }
}

void E002_C030_P230::showBox()
{
    CJSprite *box = CJPsdParser::getPsdSprite("e002_c030_p230_box", m_psdDictionary);
    addChild(box, kDepth1_actors, kTagBox);
    
    box->setPositionY(box->getPositionY()-300);
    
    box->runAction(CCMoveBy::create(0.5f, ccp(0, 300)));
    
}

void E002_C030_P230::hideBox()
{
    CJSprite *box = (CJSprite*)getChildByTag(kTagBox);
    
    if(box == NULL)
        return;
    
    box->runAction(CCSequence::create(CCMoveBy::create(0.5f, ccp(0, -300)),
                                      CCCallFuncN::create(this, callfuncN_selector(CJLayer::removeChild)),
                                      NULL));
}


