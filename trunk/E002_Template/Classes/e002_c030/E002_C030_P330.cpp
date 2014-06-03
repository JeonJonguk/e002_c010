

#include "E002_C030_P320.h"
#include "E002_C030_P330.h"
#include "E002_C030_P000_Index.h"
#include "E002_C030_P200_Intro.h"
#include "E002_C030_CompletePopup.h"
#include "E002_C030_P300_Ending.h"

enum
{
    kTagPieceBlank001 = 200,
    kTagPieceBlank002,
    kTagPieceBlank003,
    kTagPieceBlank004,
    kTagPieceBlank005,
    kTagPieceBlank006,

    
    kTagPieceNormal001,
    kTagPieceNormal002,
    kTagPieceNormal003,
    kTagPieceNormal004,
    kTagPieceNormal005,
    kTagPieceNormal006,

    
    kTagPieceSelect001,
    kTagPieceSelect002,
    kTagPieceSelect003,
    kTagPieceSelect004,
    kTagPieceSelect005,
    kTagPieceSelect006,

    kTagPiecePoint001,
    kTagPiecePoint002,
    kTagPiecePoint003,
    kTagPiecePoint004,
    kTagPiecePoint005,
    kTagPiecePoint006,
    
    kTagBlank,
    kTagLine,
};

E002_C030_P330::E002_C030_P330()
{
    mExamples = new std::vector<E002_Base_ExampleItem*>();
    mQuestions = new std::vector<std::string>();
    mTargets = new std::vector<CCPoint>();
    mPoints = new std::vector<std::string>();
    
    mCompleteTargetTags = new std::vector<int>();
    
    m_touchingExampleSp = NULL;
    mSndManager = new E002_C030_SoundManager();
}

E002_C030_P330::~E002_C030_P330()
{
    CC_SAFE_DELETE(mExamples);
}

#pragma mark - init

bool E002_C030_P330::init()
{
    if (!E002_Base_Reward::init()) {
        return false;
    }
    
    mSuccessCount = 0;
    
    return true;
}

void E002_C030_P330::onEnter()
{
    E002_Base_Reward::onEnter();
    
    const char* targetName[6] =
    {
        "e002_c030_p330_piece00_n_target",
        "e002_c030_p330_piece01_n_target",
        "e002_c030_p330_piece02_n_target",
        "e002_c030_p330_piece03_n_target",
        "e002_c030_p330_piece04_n_target",
        "e002_c030_p330_piece05_n_target",
    };
    
    const char* piecePoint[6] =
    {
        "e002_c030_p330_img_point@00",
        "e002_c030_p330_img_point@01",
        "e002_c030_p330_img_point@02",
        "e002_c030_p330_img_point@03",
        "e002_c030_p330_img_point@04",
        "e002_c030_p330_img_point@05",
    };
    
 
    const char* exampleImgName[6][2] =
    {
        {
            "e002_c030_p330_piece00_n",
            "e002_c030_p330_piece00_s"
        },
        {
            "e002_c030_p330_piece01_n",
            "e002_c030_p330_piece01_s"
        },
        {
            "e002_c030_p330_piece02_n",
            "e002_c030_p330_piece02_s"
        },
        {
            "e002_c030_p330_piece03_n",
            "e002_c030_p330_piece03_s"
        },
        {
            "e002_c030_p330_piece04_n",
            "e002_c030_p330_piece04_s"
        },
        {
            "e002_c030_p330_piece05_n",
            "e002_c030_p330_piece05_s"
        },
    };
    
    for (int i = 0; i < 6; i++)
    {
        mExamples->push_back(new E002_Base_ExampleItem(i, exampleImgName[i][0], exampleImgName[i][1], "", kTagPieceNormal001 + i, kTagPieceBlank001+ i));
        mQuestions->push_back(targetName[i]);
        mPoints->push_back(piecePoint[i]);
    }
    
    onViewLoad();
}

void E002_C030_P330::onExit()
{
    E002_Base_Reward::onExit();
}


void E002_C030_P330::onViewLoad()
{
    E002_Base_Reward::onViewLoad();

    CJPsdParser::parseToPsdJSON("e002_c030_p330.json", &m_psdDictionary);
    
    
    CJSprite *bg = CJPsdParser::getPsdSprite("e002_c030_p330_bg00_00", m_psdDictionary);
    addChild(bg, kDepth0_backImage);

    CJSprite *blank = CJPsdParser::getPsdSprite("e002_c030_p330_pyramid_blank", m_psdDictionary);
    addChild(blank, kDepth0_backImage, kTagBlank);
    
    CJSprite *line = CJPsdParser::getPsdSprite("e002_c030_p330_pyramid_line", m_psdDictionary);
    addChild(line, kDepth6_dimmed, kTagLine);
    
    setAnimationFile("e002_c030_p330_flash_reward_sheets.json", "e002_c030_p330_flash_reward_animations.json", "MEERKAT");
    
    animationManagerParseStart();
}

void E002_C030_P330::onViewLoaded()
{
    E002_Base_Reward::onViewLoaded();
    
    setTouchDisalbeBaseLayer();
    
    CJMultimedia::getInstance()->playBGM(getFilePath("snd","e002_c030_snd_bgm_play02.mp3"), true);
    
    createBlankPiece();
    animationManagerParseComplete();
}

void E002_C030_P330::startFlashAnimation()
{
    createAllAnimations();
    
    CJAnimation *ani = playAnimation("MEERKAT", "e002_c030_p330_flash_reward_mk_action", 1, kDepth6_dimmed);
    
    addNarrationOnFlashFrame(ani, 20, getFilePath("snd","e002_c030_p330_snd_01_mk.mp3").c_str());
    addEffectOnFlashFrame(ani, 0, getFilePath("snd","e002_c030_p130_sfx_appear_mk.mp3").c_str());
    addEffectOnFlashFrame(ani, 209, getFilePath("snd","e002_c030_p130_sfx_appear_mk.mp3").c_str());
    
}

void E002_C030_P330::onFirstNarration()
{
    E002_Base_Reward::onFirstNarration();
    
}

void E002_C030_P330::onFirstNarrationEnd()
{
    E002_Base_Reward::onFirstNarrationEnd();
}


void E002_C030_P330::onNarrationFinishedCallback(std::string fileName)
{
}

#pragma mark - touch

bool E002_C030_P330::onTouchBegan(CCPoint tp)
{
    for (int i = kTagPieceNormal001; i <= kTagPieceNormal006; i++)
    {
        CJSprite* sp = (CJSprite*)getChildByTag(i);
        
        if(getChildByTag(i) != NULL && CJUtils::hitTestPoint(sp , tp, false))
        {
            mTouchedItem = mExamples->at(i - kTagPieceNormal001);
            
            m_touchingExampleSp = sp;
            m_touchingExampleSp->runAction(CCScaleTo::create(0, 1.3));
            m_touchingExampleSp->setZOrder(kDepth6_dimmed);
            
            mTouchedPointGab = ccpSub(sp->getPosition(), tp);
            return true;
            
        }
    }
    
    return false;
}

void E002_C030_P330::onTouchMoved(CCPoint tp)
{
    m_touchingExampleSp->setPosition(ccp(tp.x + mTouchedPointGab.x, tp.y + mTouchedPointGab.y));
}

void E002_C030_P330::onTouchEnded(CCPoint tp)
{
    for (int i = 0; i < mExamples->size(); i++)
    {
        if (CJUtils::hitTestPoint(m_touchingExampleSp->getChildByTag(m_touchingExampleSp->getTag()+ 12), mTargets->at(i), false))
        {
            intoTarget(m_touchingExampleSp, (CJSprite*)getChildByTag(i + kTagPieceBlank001));
            return;
        }
    }
    
    setTouchEnableBaseLayer();
    
    m_touchingExampleSp->runAction(CCSpawn::create(CCEaseBackOut::create(CCMoveTo::create(0.1, mTouchedItem->getOriginalPosition())),
                                                   CCScaleTo::create(0.1, 1.0),
                                                   NULL));
    
}

void E002_C030_P330::intoTarget(CJSprite* sp, CJSprite *target)
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
    
    sp->runAction(CCSequence::create(CCSpawn::create(CCEaseSineInOut::create(CCMoveTo::create(0.1, ccp(target->getPositionX()+1, target->getPositionY()-4 ))),
                                                     CCScaleTo::create(0.1, 1.18),
                                                     NULL),
                                     CCCallFuncND::create(this, callfuncND_selector(E002_C030_P330::setExampleZorder), (void*)kDepth3_examples),
                                     CCDelayTime::create(0.5f),
                                     CCCallFuncND::create(this, callfuncND_selector(E002_C030_P330::checkAnswer), (void*)target->getTag()),
                                     NULL));
}

void E002_C030_P330::checkAnswer(CCNode *node, int targetTag)
{
    if(mTouchedItem->getCorrectTag() == targetTag)
    {
        mCompleteTargetTags->push_back(targetTag);
        
        CJSprite *sel = CJPsdParser::getPsdSprite(mTouchedItem->getSelectImgPath(), m_psdDictionary);
        addChild(sel, mTouchedItem->getItemSprite()->getZOrder(), mTouchedItem->getItemSprite()->getTag()+6);

        removeChild(mTouchedItem->getItemSprite());

        
        onSuccesses(node);
    }
    else
    {
        onFails(node);
    }
}

#pragma mark - feedback event
void E002_C030_P330::onSuccesses(CCNode *node)
{
    setTouchEnableBaseLayer();
    
    mSuccessCount++;

    if(mSuccessCount > 5)
    {
        onComplete();
    }
    
}

void E002_C030_P330::onComplete()
{
    for (int i = kTagPieceSelect001; i <= kTagPieceSelect006; i++)
    {
        removeChildByTag(i);
    }
    
    playEffect(NULL, 13);
    
    CJSprite *sucSeq = CJPsdParser::getPsdSprite("e002_c030_p330_pyramid_success_seq00", m_psdDictionary);
    addChild(sucSeq, kDepth4_title);
    
    
    
    sucSeq->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(E002_C030_P330::removeObject)),
                                         CJUtils::getSeqAction(1, 0.2, getFilePath("img","e002_c030_p330_pyramid_success_seq01.png").c_str(),
                                                                       getFilePath("img","e002_c030_p330_pyramid_success_seq02.png").c_str(),
                                                                       getFilePath("img","e002_c030_p330_pyramid_success_seq03.png").c_str(),
                                                                       getFilePath("img","e002_c030_p330_pyramid_success_seq04.png").c_str(),
                                                                       getFilePath("img","e002_c030_p330_pyramid_success_seq05.png").c_str(),
                                                                       getFilePath("img","e002_c030_p330_pyramid_success_seq06.png").c_str(),
                                                                       getFilePath("img","e002_c030_p330_pyramid_success_seq07.png").c_str(),
                                                                       getFilePath("img","e002_c030_p330_pyramid_success_seq08.png").c_str(),
                                                                       NULL),
                                         CCDelayTime::create(2.0),
                                         CCCallFunc::create(this, callfunc_selector(E002_C030_P330::onTouchedNavigationButtonAtNext)),
                                         NULL));
    
}

void E002_C030_P330::removeObject()
{
    for (int i = kTagPieceNormal001; i <= kTagPieceNormal006; i++)
    {
        removeChildByTag(i);
    }
    
    removeChildByTag(kTagBlank);
    removeChildByTag(kTagLine);
}

void E002_C030_P330::onFails(CCNode *node)
{
    setTouchEnableBaseLayer();
    
    playEffect(NULL, 12);
    m_touchingExampleSp->runAction(CCSpawn::create(CCEaseBackOut::create(CCMoveTo::create(0.1, mTouchedItem->getOriginalPosition())),
                                                   CCScaleTo::create(0.1, 1.0),
                                                   NULL));
}

#pragma mark - user function

void E002_C030_P330::setQuestions()
{
    float delay = 0.0f;
    
    for (int i = kTagPieceNormal001; i <= kTagPieceNormal006; i++)
    {
        E002_Base_ExampleItem *item = mExamples->at(i - kTagPieceNormal001);
        item->setOriginalPosition(CJPsdParser::getPsdPosition(item->getImgPath(), m_psdDictionary));

        CJSprite *example = CJPsdParser::getPsdSprite(item->getImgPath(), m_psdDictionary);
        addChild(example, kDepth3_examples, i);
        
        item->setItemSprite(example);
        
        CJSprite *point = CJPsdParser::getPsdSprite(mPoints->at(i- kTagPieceNormal001), m_psdDictionary);
        point->setOpacity(0);
        example->addChildIgnoreParent(point, kDepth3_examples, i + 12 );
        
        example->setScale(0);
        
        if(i == kTagPieceNormal006)
        {
            example->runAction(CCSequence::create(CCDelayTime::create(delay),
                                                  CCCallFuncND::create(this, callfuncND_selector(E002_C030_P330::playEffect), (void*)10),
                                                  CCEaseElasticOut::create(CCScaleTo::create(1, 1.0)),
                                                  CCCallFunc::create(this, callfunc_selector(E002_C030_P330::completeShowExamples)),
                                                  NULL));
        }
        else
        {
            example->runAction(CCSequence::create(CCDelayTime::create(delay),
                                                  CCCallFuncND::create(this, callfuncND_selector(E002_C030_P330::playEffect), (void*)10),
                                                  CCEaseElasticOut::create(CCScaleTo::create(1, 1.0)),
                                                  NULL));
        }
        
        delay += 0.5f;
        
    }
}

void E002_C030_P330::playEffect(CCNode* node, int index)
{
    mSndManager->playLetsPlay1Effect(index);
}

void E002_C030_P330::completeShowExamples()
{
    setTouchEnableBaseLayer();
}

#pragma mark - sound & narration


#pragma mark - navigation delegate

void E002_C030_P330::onTouchedNavigationButtonAtIndex()
{
    E002_Base_Reward::onTouchedNavigationButtonAtIndex();
    
    E002_C030_P000_Index* _indexClass = E002_C030_P000_Index::create();
    _indexClass->init();
    _indexClass->setIndexDelegate(this);
    _indexClass->showIndex(this, _indexClass);
    addChild(_indexClass, kDepth11_Index);
}

void E002_C030_P330::onTouchedNavigationButtonAtInfo()
{
    E002_Base_Reward::onTouchedNavigationButtonAtInfo();
    
    showGuide(new E002_Base_ImageGuide_Item("e002_c030_p330_guide.jpg",
                                            CJPsdParser::getPsdPosition("e002_common_img_guide_hand@00", m_psdDictionary),
                                            CJPsdParser::getPsdPosition("e002_common_img_guide_hand@01", m_psdDictionary)
                                            ));
}

void E002_C030_P330::onTouchedNavigationButtonAtPrev()
{
    E002_Base_Reward::onTouchedNavigationButtonAtPrev();
    replaceSceneTransitionFadeOut(E002_C030_P320);
}

void E002_C030_P330::onTouchedNavigationButtonAtNext()
{
    E002_Base_Reward::onTouchedNavigationButtonAtNext();
    
    replaceSceneTransitionFadeOut(E002_C030_P300_Ending);
}

void E002_C030_P330::OnLastFrame(CJAnimation* pAnimation)
{
    E002_Base_Reward::OnLastFrame(pAnimation);
    
    if(pAnimation->getName() == "e002_c030_p330_flash_reward_mk_action")
    {
        if (getUserDefaultFirstGuide(eGuidePageP330) == false)
        {
            mShowFirstGuide = true;
            
            setUserDefaultFirstGuide(eGuidePageP330);
            
            showGuide(new E002_Base_ImageGuide_Item("e002_c030_p330_guide.jpg",
                                                    CJPsdParser::getPsdPosition("e002_common_img_guide_hand@00", m_psdDictionary),
                                                    CJPsdParser::getPsdPosition("e002_common_img_guide_hand@01", m_psdDictionary)
                                                    ));
        }
        else
        {
            CJUtils::performSelector(this, callfunc_selector(E002_C030_P330::setQuestions),1.0f);
        }
    }
}

void E002_C030_P330::completeFirstGuide()
{
    CJUtils::performSelector(this, callfunc_selector(E002_C030_P330::setQuestions), 1.0f);
}

#pragma mark - sprite create
void E002_C030_P330::createBlankPiece()
{
    for (int i = kTagPieceBlank001; i <= kTagPieceBlank006; i++)
    {
        CCPoint target = CJPsdParser::getPsdPosition(mQuestions->at(i - kTagPieceBlank001), m_psdDictionary);
        mTargets->push_back(target);
        
        CJSprite *blank = CJPsdParser::getPsdSprite(mExamples->at(i - kTagPieceBlank001)->getSelectImgPath(), m_psdDictionary);
        addChild(blank, kDepth3_examples, i);
        blank->setVisible(false);
    }
}

void E002_C030_P330::setExampleZorder(CCNode *node, int depth)
{
    node->setZOrder(depth);
}