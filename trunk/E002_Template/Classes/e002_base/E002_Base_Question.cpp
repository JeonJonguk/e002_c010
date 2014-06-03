//
//  E002_Base_Question.cpp
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 6. 24..
//
//

#include "E002_Base_Question.h"
#include "E002_Base_Define.h"
#include "E002_Base_RewardPopup.h"

enum
{
    kTagReward = 997,
    kTagHand,
    kTagGuideTitle,
};

E002_Base_Question::E002_Base_Question()
{
    m_nCurrentStageIndex = 1;
    _touchEnable = false;

    _bIsFirstSkip = false;
    _bIsFirstNarrationStarted = false;
    
    m_bIsGuide = false;
    m_bIsGuideSkiped = false;
    
    _examplesSoundId = 0;
    _answerSoundId = "";
    
    m_arrExamples = new CCArray();
    m_arrShadows = new CCArray();
    m_arrExamplesOriginPosition = new CCPointArray();
    m_arrExamplesOriginPosition->initWithCapacity(0);
    m_psdDictionary = new CCDictionary();
    

    _exampleRepeatAction = NULL;
    _exampleEffectId = 0;
    
    _characters = new std::vector<CJAnimationCharacter*>();
    _guidePositon = ccp(100, -200);
    m_currentGuideIndex = 0;
    mShowFirstGuide = false;
}

E002_Base_Question::~E002_Base_Question()
{
    CC_SAFE_RELEASE(m_arrExamples);
    CC_SAFE_RELEASE(m_arrShadows);
    CC_SAFE_RELEASE(m_arrExamplesOriginPosition);
    CC_SAFE_RELEASE(m_psdDictionary);
    
    if(!m_bIsGuide)
    {
        removeAllDatapool();
    }
    
    
    //    CC_SAFE_DELETE(m_GuidePopup);
}


#pragma mark - init()

bool E002_Base_Question::init()
{
    if (!CJLayer::init()) {
        return false;
    }
    
    return true;
}

void E002_Base_Question::setDatapool(std::multimap<std::string, CJFlash::CJAnimationDataPool*> data)
{
    std::multimap<std::string, CJFlash::CJAnimationDataPool*> copy;
    
//    std::multimap<std::string, CJFlash::CJAnimationDataPool*>::iterator iter = data.begin();
//    std::multimap<std::string, CJFlash::CJAnimationDataPool*>::iterator stop = data.end();
//    
//    for (; iter != stop; ++iter)
//    {
//        std::string key = iter->first;
//        CJFlash::CJAnimationDataPool* value = iter->second;
//        
//        std::pair<std::string, CJFlash::CJAnimationDataPool*> Enumerator( key, value );
//        copy.insert( Enumerator );
//    }
    
    //std::copy(data.begin(), data.end(), std::inserter(copy, copy.end()));
    
    setAllDatapool(data);
    
    //std::copy(data.begin(), data.end(), std::inserter(copy, copy.end()));
}

void E002_Base_Question::setGuide(bool isGuide)
{
    m_bIsGuide = isGuide;
    m_nCurrentStageIndex = 0;
}

void E002_Base_Question::removeTouchDelegateForGuide()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void E002_Base_Question::onEnter()
{
    CJLayer::onEnter();
}

void E002_Base_Question::onExit()
{

    removeSoundObserver();
    removeRewardPopupCompleteObserver();
    
    stopTimer();
    //CJMultimedia::getInstance()->stopBGM();
    CJLayer::onExit();
}

#pragma mark - view load

void E002_Base_Question::onViewLoad()
{
    CJLayer::onViewLoad();
    
    setAnimationParent(this);
}

void E002_Base_Question::onViewLoaded()
{
    CJLayer::onViewLoaded();

    if(!m_bIsGuide)
    {
        E002_Base_Navigation::initWithNavigationType(this, "",
                                                     eNavigationType_Question);
        E002_Base_Navigation::showNavigation();
        
        E002_Base_Navigation::setVisibleButton(false, eNavigationButton_Prev);
        E002_Base_Navigation::setVisibleButton(false, eNavigationButton_Close);
        
        addRewardPopupCompleteObserver();
    }
    
    addSoundObserver();
}

#pragma mark - narration

void E002_Base_Question::onFirstNarration()
{
    setTouchEnableBaseLayer(true);
    _bIsFirstNarrationStarted = true;
    
}

void E002_Base_Question::onFirstNarrationEnd()
{
    _bIsFirstSkip = true;
    CJMultimedia::getInstance()->stopAllNarration();
}


void E002_Base_Question::onNarrationFinishedCallback(std::string fileName)
{
    /* override me */
}

#pragma mark - touch

bool E002_Base_Question::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLog("ccTouch");
    CCPoint tp = pTouch->getLocation();
    
    _touchBeganPos = tp;
    m_bIsTapped = true;
    
    if (_bIsFirstSkip == false && _bIsFirstNarrationStarted == true)
    {
        stopAllActions();
        onFirstNarrationEnd();
        return false;
    }
    
    if (_touchEnable) {
        
        if (m_arrExamples!= NULL) {
            for (int i = 0; i < m_arrExamples->count() ; i++) {
                CJSprite* sp = (CJSprite*)m_arrExamples->objectAtIndex(i);
                
                if (CJUtils::hitTestPoint(sp, tp, false))
                {
                    if (sp->isComplete() == true)
                    {return false;}
                    
                    m_touchingExampleSp = sp;
                    m_nExamplesTouchedIndex = i;
                    reorderChild(sp, sp->getZOrder());
                    onExamplesTouched(i);
                }
            }
        }
        return onTouchBegan(tp);
    }
    
    return false;
}

void E002_Base_Question::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint tp = pTouch->getLocation();
    
    if(ccpDistance(tp, _touchBeganPos) > 30)
    {
        m_bIsTapped = false;
    }
    
    if (_touchEnable) {onTouchMoved(tp);}
    
}

void E002_Base_Question::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint tp = pTouch->getLocation();
    
    if (_touchEnable)
    {
        onTouchEnded(tp);
    }
}



#pragma mark - set examples

void E002_Base_Question::createExampleSprite(const char* fileName, ...)
{
    m_arrExamples->removeAllObjects();
    
    va_list args;
    va_start(args,fileName);
    
    while (fileName != NULL) {
        CJSprite* example = CJSprite::createWithFullPath(fileName);
        m_arrExamples->addObject(example);
        
        fileName = va_arg(args, const char*);
    }
    va_end(args);
}


void E002_Base_Question::createExampleSpriteForPsd(const char * fileName, ...)
{
    m_arrExamples->removeAllObjects();
    
    va_list args;
    va_start(args,fileName);
    
    while (fileName != NULL) {
        CJSprite* example = (CJSprite*)CJPsdParser::getPsdSprite(fileName, m_psdDictionary);
        m_arrExamples->addObject(example);
        m_arrExamplesOriginPosition->addControlPoint(example->getPosition());
        
        example->setTouchEnable(true);
        
        
        fileName = va_arg(args, const char*);
    }
    
    va_end(args);
}

void E002_Base_Question::setExampleOriginPosition(std::vector<CCPoint>* originPositionVector)
{
    m_arrExamples->removeAllObjects();
    for (int i = 0; i < originPositionVector->size(); i++) {
        m_arrExamplesOriginPosition->addControlPoint(originPositionVector->at(i));
    }
}


void E002_Base_Question::addChildExamples(int zorder /* = kDepth3_examples */)
{
    for (int i = 0; i < m_arrExamples->count(); i++) {
        CJSprite* example = (CJSprite*)m_arrExamples->objectAtIndex(i);
        this->addChild(example, zorder);
    }
}



void E002_Base_Question::onExamplesTouched(int index)
{
    CCLog(" example touch : %d", index);
    /* override me */
}


void E002_Base_Question::examplesAppearanceAnimation(CCPoint point)
{
    float delay = 0.5;
    for (int i = 0; i < m_arrExamples->count(); i++)
    {
        CJSprite* example = (CJSprite*)m_arrExamples->objectAtIndex(i);
        example->setPosition(ccpAdd(example->getPosition(), point));
        example->runAction(CCSequence::create(CCDelayTime::create(delay),
                                              CCCallFuncND::create(this, callfuncND_selector(E002_Base_Question::playAppearanceExamplesSound),(void*)i),
                                              CCEaseElasticOut::create(CCMoveTo::create(0.45, m_arrExamplesOriginPosition->getControlPointAtIndex(i)), 0.7),
                                              CCCallFuncND::create(this, callfuncND_selector(E002_Base_Question::examplesShadowAppearanceAnimation),(void*)i),
                                              NULL));
        delay += 0.7;
    }
    
    runAction(CCSequence::create(CCDelayTime::create(delay+0.45 -1.0),
                                 CCCallFunc::create(this, callfunc_selector(E002_Base_Question::examplesAppearanceAnimationEnd)),
                                 NULL));
    
}

void E002_Base_Question::examplesAppearanceAnimationEnd()
{
    setTouchEnableBaseLayer(true);
    /* override me */
}

void E002_Base_Question::removeAllExamples()
{
    for (int i = 0; i < m_arrExamples->count(); i++)
    {
        CJSprite* example = (CJSprite*)m_arrExamples->objectAtIndex(i);
        if (example->getParent()!= NULL) {
            CJUtils::removeAllchildren(example);
            removeChild(example);
        }
    }
}


#pragma mark - set shadows

void E002_Base_Question::createExampleShadowSprite(const char* fileName, ...)
{
    m_arrShadows->removeAllObjects();
    
    va_list args;
    va_start(args,fileName);
    
    while (fileName != NULL) {
        CJSprite* example = CJSprite::createWithFullPath(fileName);
        m_arrShadows->addObject(example);
        
        fileName = va_arg(args, const char*);
    }
    va_end(args);
}


void E002_Base_Question::createExampleShadowSpriteForPsd(const char * fileName, ...)
{
    m_arrShadows->removeAllObjects();
    
    va_list args;
    va_start(args,fileName);
    
    while (fileName != NULL) {
        CJSprite* example = (CJSprite*)CJPsdParser::getPsdSprite(fileName, m_psdDictionary);
        m_arrShadows->addObject(example);
        
        fileName = va_arg(args, const char*);
    }
    
    va_end(args);
}

void E002_Base_Question::addChildShadows(int zorder)
{
    for (int i = 0; i < m_arrShadows->count(); i++) {
        CJSprite* shadow = (CJSprite*)m_arrShadows->objectAtIndex(i);
        this->addChild(shadow, zorder);
        shadow->setOpacity(0);
    }
}

void E002_Base_Question::examplesShadowAppearanceAnimation(CCNode* sender, void* nIndex)
{
    int index = (int)nIndex;
    showShadowAnimation(index);
}

void E002_Base_Question::showShadowAnimation(int index)
{
    if (m_arrShadows != NULL && m_arrShadows->count()!= 0) {
        CJSprite* shadow = (CJSprite*)m_arrShadows->objectAtIndex(index);
        if (shadow == NULL) {return;}
        shadow->stopAllActions();
        shadow->runAction(CCFadeIn::create(0.1));
    }
}

void E002_Base_Question::hideShadowAnimation(int index)
{
    if (m_arrShadows != NULL && m_arrShadows->count()!= 0) {
        CJSprite* shadow = (CJSprite*)m_arrShadows->objectAtIndex(index);
        if (shadow == NULL) {return;}
        shadow->stopAllActions();
        shadow->runAction(CCFadeOut::create(0.1));
    }
}


void E002_Base_Question::removeAllShadows()
{
    for (int i = 0; i < m_arrShadows->count(); i++)
    {
        CJSprite* shadow = (CJSprite*)m_arrShadows->objectAtIndex(i);
        if (shadow->getParent()!= NULL) {
            removeChild(shadow);
        }
    }
    m_arrShadows->removeAllObjects();
}

#pragma mark - sound & narration
void E002_Base_Question::playAppearanceExamplesSound(CCNode* sender, void* index)
{
    /* override me */
}

void E002_Base_Question::playExamplesSound(std::string fileName, bool bLoop)
{
    stopAllNarration();
    if (_exampleEffectId != 0) {
        stopEffect(_exampleEffectId);
    }
    _exampleEffectId = playEffect(fileName, bLoop);
}

void E002_Base_Question::stopExamplesSound()
{
    CJMultimedia::getInstance()->stopAllEffect();
}

void E002_Base_Question::playAnswerSound(std::string fileName, bool bLoop)
{
    stopAllNarration();
    _answerSoundId = fileName;
    playNarration(fileName, bLoop);
}

void E002_Base_Question::stopAnswerSound()
{
    CJMultimedia::getInstance()->stopNarration(_answerSoundId);
    _answerSoundId = "";
}


void E002_Base_Question::playExampleNarrationRepeat(std::string fileName)
{
    stopAllNarration();
    float delay = CJMultimedia::getInstance()->getNarrationTime(getFilePath("snd",fileName));
    CJLog("playExampleNarrationRepeat delay = %f",delay);

    _exampleNarrationString = new CCString(fileName);
    
    _playExampleNarrationRepeat(NULL, _exampleNarrationString);
    _exampleRepeatAction = CCRepeatForever::create(CCSequence::create(
                                                                      CCDelayTime::create(delay),
                                                                      CCCallFuncND::create(this, callfuncND_selector(E002_Base_Question::_playExampleNarrationRepeat), _exampleNarrationString),
                                                                      NULL));
    runAction(_exampleRepeatAction);
}

void E002_Base_Question::stopExampleNarrationRepeat()
{
    stopAction(_exampleRepeatAction);
    
    //if(_exampleNarrationString != NULL && _exampleNarrationString->retainCount() > 0)
    //    CC_SAFE_RELEASE(_exampleNarrationString);
}

void E002_Base_Question::_playExampleNarrationRepeat(CCNode* sender, void* path)
{
    CCString* fileName = (CCString*)path;
    playNarration(fileName->getCString());

}

#pragma mark - guide

void E002_Base_Question::showGuide()
{
    E002_Base_Navigation::setVisibleButton(false, eNavigationButton_Index);
    E002_Base_Navigation::setVisibleButton(false, eNavigationButton_Guide);
    E002_Base_Navigation::setVisibleButton(false, eNavigationButton_Reward);
    E002_Base_Navigation::setVisibleButton(true, eNavigationButton_Close);
    
    CJUtils::getInstance()->pauseAllAnimations(this);
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
    CJMultimedia::getInstance()->pauseToPlayingNarration();
    
    CCDictionary *commonDic = new CCDictionary();
    CJPsdParser::parseToPsdJSON("e002_common_guide.json", &commonDic, true);
    
    CJSprite *guideTitle = CJPsdParser::getPsdCommonSprite("e002_common_img_guide_title", commonDic);
    addChild(guideTitle, kDepth10_guide+1, kTagGuideTitle);
    
    setTouchDisalbeBaseLayer();
}

void E002_Base_Question::removeGuide()
{
    if(!m_bIsGuide)
    {
        E002_Base_Navigation::setVisibleButton(true, eNavigationButton_Index);
        E002_Base_Navigation::setVisibleButton(true, eNavigationButton_Guide);
        E002_Base_Navigation::setVisibleButton(true, eNavigationButton_Reward);
        E002_Base_Navigation::setVisibleButton(false, eNavigationButton_Close);
    }
    
    removeChildByTag(kTagGuideTitle);
    
    
    CJUtils::getInstance()->resumeAllAnimations(this);
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    CJMultimedia::getInstance()->resumePausedNarration();
    
    setTouchEnableBaseLayer();
    
    if(mShowFirstGuide)
    {
        completeFirstGuide();
        mShowFirstGuide = false;
    }
}

#pragma mark - animation functions

void E002_Base_Question::addAnimationCharacter(CJAnimationCharacter *character, ...)
{
    va_list args;
    va_start(args,character);
    
    while (character != NULL) {
        _characters->push_back(character);
        
        character = va_arg(args, CJAnimationCharacter*);
    }
    
    va_end(args);
}

void E002_Base_Question::animationManagerParseComplete()
{
    startFlashAnimation();
}

void E002_Base_Question::OnLastFrame(CJFlash::CJAnimation *pAnimation)
{
    if(_characters != NULL && _characters->size() > 0)
    { 
        for (int i= 0; i < _characters->size(); i++)
        {
            for (int j = 0; j < _characters->at(i)->getFailKeys()->size(); j++)
            {
                if (strcmp(_characters->at(i)->getFailKeys()->at(j), pAnimation->getName().c_str())  == 0)
                {
                    _characters->at(i)->showLooping();
                    return;
                }
            }
            
            for (int j = 0; j < _characters->at(i)->getSuccessKeys()->size(); j++)
            {
                if (strcmp(_characters->at(i)->getSuccessKeys()->at(j), pAnimation->getName().c_str())  == 0)
                {
                    _characters->at(i)->showLooping();
                    return;
                }
            }

        }
    }
}

#pragma mark - utils functions

void E002_Base_Question::setTouchEnableBaseLayer(bool enable)
{
    if (_touchEnable != enable) {
        _touchEnable = enable;
    }
}

void E002_Base_Question::completeLetsPlay1()
{
    CJUtils::getInstance()->setLmsMenuEnd(LMS_MENU_END_LETSPLAY1);
    
    std::string userdefualtKey = CJUtils::getStringMerge(CJUtils::getInstance()->getContentID(),"_completeIndex");
    
    if (CJUtils::getInstance()->getUserDefaultIntegerForKey(userdefualtKey) < LMS_MENU_END_LETSPLAY1)
    {
        CJUtils::getInstance()->setUserDefaultIntegerForKey(userdefualtKey, LMS_MENU_END_LETSPLAY1);
    }
}

void E002_Base_Question::completeLetsPlay2()
{
    CJUtils::getInstance()->setLmsMenuEnd(LMS_MENU_END_LETSPLAY2);
    
    std::string userdefualtKey = CJUtils::getStringMerge(CJUtils::getInstance()->getContentID(),"_completeIndex");
    
    if (CJUtils::getInstance()->getUserDefaultIntegerForKey(userdefualtKey) < LMS_MENU_END_LETSPLAY2)
    {
        CJUtils::getInstance()->setUserDefaultIntegerForKey(userdefualtKey, LMS_MENU_END_LETSPLAY2);
    }
}

void E002_Base_Question::completeLetsPlay3()
{
    CJUtils::getInstance()->setLmsMenuEnd(LMS_MENU_END_LETSPLAY3);
    
    std::string userdefualtKey = CJUtils::getStringMerge(CJUtils::getInstance()->getContentID(),"_completeIndex");
    
    if (CJUtils::getInstance()->getUserDefaultIntegerForKey(userdefualtKey) < LMS_MENU_END_LETSPLAY3)
    {
        CJUtils::getInstance()->setUserDefaultIntegerForKey(userdefualtKey, LMS_MENU_END_LETSPLAY3);
    }
}


void E002_Base_Question::showLetPlay1RewardItem(CCNode *node, int currentIndex)
{
    E002_Base_RewardPopup *popup = new E002_Base_RewardPopup();
    popup->init(P100);
    addChild(popup, kDepth7_popup, kTagReward);
    
    popup->showPopup(this);
    popup->showRewardItem(currentIndex);
}

void E002_Base_Question::showLetPlay1RewardPopup(CCNode *node,int currentIndex)
{
    CJUtils::getInstance()->pauseAllAnimations(this);
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
    CJMultimedia::getInstance()->pauseAllNarration();
    
    E002_Base_RewardPopup *popup = new E002_Base_RewardPopup();
    popup->init(P100);
    addChild(popup, kDepth10_guide, kTagReward);
    
    popup->showPopup(this);
    popup->showRewardBox(currentIndex);
}

void E002_Base_Question::showLetPlay2RewardItem(CCNode *node,int currentIndex)
{
    E002_Base_RewardPopup *popup = new E002_Base_RewardPopup();
    popup->init(P200);
    addChild(popup, kDepth7_popup, kTagReward);
    
    popup->showPopup(this);
    popup->showRewardItem(currentIndex);
}

void E002_Base_Question::showLetPlay2RewardPopup(CCNode *node,int currentIndex)
{
    CJUtils::getInstance()->pauseAllAnimations(this);
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
    CJMultimedia::getInstance()->pauseAllNarration();
    
    E002_Base_RewardPopup *popup = new E002_Base_RewardPopup();
    popup->init(P200);
    addChild(popup, kDepth10_guide, kTagReward);
    
    popup->showPopup(this);
    popup->showRewardBox(currentIndex);
}

void E002_Base_Question::showLetPlay3RewardItem(CCNode *node,int currentIndex)
{
    E002_Base_RewardPopup *popup = new E002_Base_RewardPopup();
    popup->init(P300);
    addChild(popup, kDepth10_guide, kTagReward);
    
    popup->showPopup(this);
    popup->showRewardItem(currentIndex);
}

void E002_Base_Question::showLetPlay3RewardPopup(CCNode *node, int currentIndex)
{
    CJUtils::getInstance()->pauseAllAnimations(this);
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
    CJMultimedia::getInstance()->pauseAllNarration();
    
    E002_Base_RewardPopup *popup = new E002_Base_RewardPopup();
    popup->init(P300);
    addChild(popup, kDepth10_guide, kTagReward);
    
    popup->showPopup(this);
    popup->showRewardBox(currentIndex);
}

void E002_Base_Question::completeToGetRewardItem()
{
    ((E002_Base_RewardPopup*)getChildByTag(kTagReward))->hidePopup();
    removeChildByTag(kTagReward);
}

void E002_Base_Question::completeRewardPopup()
{
    CJUtils::getInstance()->resumeAllAnimations(this);
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    CJMultimedia::getInstance()->resumeAllNarration();
    
    ((E002_Base_RewardPopup*)getChildByTag(kTagReward))->hidePopup();
    removeChildByTag(kTagReward);
}

void E002_Base_Question::addRewardPopupCompleteObserver()
{
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(E002_Base_Question::completeToGetRewardItem),
                                                                  CJNOTIFICATION_REWARD_ITEM_COMPLETE_CALL,
                                                                  NULL);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(E002_Base_Question::completeRewardPopup),
                                                                  CJNOTIFICATION_REWARD_POPUP_COMPLETE_CALL,
                                                                  NULL);
}

void E002_Base_Question::removeRewardPopupCompleteObserver()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, CJNOTIFICATION_REWARD_ITEM_COMPLETE_CALL);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, CJNOTIFICATION_REWARD_POPUP_COMPLETE_CALL);
}

bool E002_Base_Question::getUserDefaultFirstGuide(eGuidePageIndex page)
{
    std::string _key;
    
    if (page == eGuidePageP110)
    {
        _key = "_p110_guide_isFirst";
    }
    else if (page == eGuidePageP120)
    {
        _key = "_p120_guide_isFirst";
    }
    else if (page == eGuidePageP210)
    {
        _key = "_p210_guide_isFirst";
    }
    else if (page == eGuidePageP220)
    {
        _key = "_p220_guide_isFirst";
    }
    else if (page == eGuidePageP310)
    {
        _key = "_p310_guide_isFirst";
    }
    else if (page == eGuidePageP320)
    {
        _key = "_p320_guide_isFirst";
    }
    else
    {
        return false;
    }
    
    std::string resultKey = CJUtils::getStringMerge(CJUtils::getInstance()->getContentID(), _key);
    return CJUtils::getInstance()->getUserDefaultBoolForKey(resultKey);
}

void E002_Base_Question::setUserDefaultFirstGuide(eGuidePageIndex page)
{
    std::string _key;
    
    if (page == eGuidePageP110)
    {
        _key = "_p110_guide_isFirst";
    }
    else if (page == eGuidePageP120)
    {
        _key = "_p120_guide_isFirst";
    }
    else if (page == eGuidePageP210)
    {
        _key = "_p210_guide_isFirst";
    }
    else if (page == eGuidePageP220)
    {
        _key = "_p220_guide_isFirst";
    }
    else if (page == eGuidePageP310)
    {
        _key = "_p310_guide_isFirst";
    }
    else if (page == eGuidePageP320)
    {
        _key = "_p320_guide_isFirst";
    }
    else{
        return;
    }
    
    std::string resultKey = CJUtils::getStringMerge(CJUtils::getInstance()->getContentID(), _key);
    CJUtils::getInstance()->setUserDefaultBoolForKey(resultKey, true);
}

void E002_Base_Question::createGuideDim(int zOrder)
{
    CCSprite* dim = CCSprite::create();
    dim->setTextureRect(CCRectMake(0, 0, winSize.width, winSize.height));
    dim->setColor(ccBLACK);
    dim->setContentSize(CCSizeMake(winSize.width, winSize.height));
    dim->setPosition(ccp(winSize.width/2, winSize.height/2));
    dim->setOpacity(190);
    dim->setZOrder(zOrder);
    
	addChild(dim);

}

void E002_Base_Question::setGuideHandPosition(std::vector<CCPoint> *guideHandPositions)
{
    mGuidehandPositions = guideHandPositions;
}

void E002_Base_Question::showHand(CCNode *node, int index)
{
    hideHand();
    
    m_currentGuideIndex = index;
    
    CJSprite *hand = CJSprite::create(getCommonFilePath("img", "e002_common_img_guide_hand.png").c_str());
    hand->setPosition(_guidePositon);
    _guidePositon = mGuidehandPositions->at(index);
    
    addChild(hand, kDepth10_guide+1, kTagHand);
    
    if(mGuidehandPositions->size() - 1 == index)
    {
        hand->runAction(CCSequence::create(CCSpawn::create(CCEaseSineOut::create(CCMoveTo::create(0.7f, mGuidehandPositions->at(index))),
                                                           CCScaleTo::create(0.7, 1.1),
                                                           NULL),
                                           
                                           CCSpawn::create(CCMoveBy::create(0.15, ccp(0, -10)),
                                                           CCScaleTo::create(0.15, 1.0),
                                                           NULL),
                                           CCSpawn::create(CCMoveBy::create(0.15, ccp(0, +10)),
                                                           CCScaleTo::create(0.15, 1.1),
                                                           NULL),
                                           CCDelayTime::create(0.1),

                                           CCCallFuncND::create(this, callfuncND_selector(E002_Base_Question::completeToMoveHand), (void*)index),
                                           CCEaseSineOut::create(CCMoveTo::create(0.7f, ccp(500, -200))),
                                           NULL));
    }
    else
    {
        hand->runAction(CCSequence::create(CCSpawn::create(CCEaseSineOut::create(CCMoveTo::create(0.7f, mGuidehandPositions->at(index))),
                                                           CCScaleTo::create(0.7, 1.1),
                                                           NULL),
                                           
                                           CCSpawn::create(CCMoveBy::create(0.15, ccp(0, -10)),
                                                           CCScaleTo::create(0.15, 1.0),
                                                           NULL),
                                           CCSpawn::create(CCMoveBy::create(0.15, ccp(0, +10)),
                                                           CCScaleTo::create(0.15, 1.1),
                                                           NULL),
                                           CCDelayTime::create(0.1),
                                           CCCallFuncND::create(this, callfuncND_selector(E002_Base_Question::completeToMoveHand), (void*)index),
                                           NULL));
    }
}

void E002_Base_Question::hideHand()
{
    if (getChildByTag(kTagHand) != NULL)
    {
        removeChildByTag(kTagHand);
    }
}
