//
//  E002_Base_Reward.cpp
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 6. 24..
//
//

#include "E002_Base_Reward.h"
#include "E002_Base_Define.h"

E002_Base_Reward::E002_Base_Reward()
{
    _touchEnable = false;

    m_arrExamples = new CCArray();
    m_arrShadows = new CCArray();
    m_arrExamplesOriginPosition = new CCPointArray();
    m_arrExamplesOriginPosition->initWithCapacity(0);
    m_psdDictionary = new CCDictionary();
    m_bIsCompleteFlashParsing = false;
    mShowFirstGuide = false;
}

E002_Base_Reward::~E002_Base_Reward()
{
    CC_SAFE_RELEASE(m_arrExamples);
    CC_SAFE_RELEASE(m_arrShadows);
    CC_SAFE_RELEASE(m_arrExamplesOriginPosition);
    CC_SAFE_RELEASE(m_psdDictionary);
    
    //    CC_SAFE_DELETE(m_GuidePopup);
}


#pragma mark - init()

bool E002_Base_Reward::init()
{
    if (!CJLayer::init()) {
        return false;
    }
    
    return true;
}

void E002_Base_Reward::onEnter()
{
    CJLayer::onEnter();
    
    addGuidePopupCompleteObserver();
}

void E002_Base_Reward::onExit()
{
    removeGuidePopupCompleteObserver();
    
    removeSoundObserver();
    stopTimer();
    //CJMultimedia::getInstance()->stopBGM();
    CJLayer::onExit();
}

#pragma mark - view load

void E002_Base_Reward::onViewLoad()
{
    CJLayer::onViewLoad();
    
    setAnimationParent(this);
}

void E002_Base_Reward::onViewLoaded()
{
    CJLayer::onViewLoaded();
    
    E002_Base_Navigation::initWithNavigationType(this, "",
                                                 eNavigationType_Reward);
    E002_Base_Navigation::showNavigation();

    addSoundObserver();
    
    onTimer();
}

#pragma mark - narration

void E002_Base_Reward::onFirstNarration()
{
    setTouchEnableBaseLayer(true);
    
}

void E002_Base_Reward::onFirstNarrationEnd()
{
    CJMultimedia::getInstance()->stopAllNarration();
}


void E002_Base_Reward::onNarrationFinishedCallback(std::string fileName)
{
    /* override me */
}

#pragma mark - touch

bool E002_Base_Reward::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint tp = pTouch->getLocation();
    
    _touchBeganPos = tp;
  
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

void E002_Base_Reward::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint tp = pTouch->getLocation();
    
    if (_touchEnable) {onTouchMoved(tp);}
    
}

void E002_Base_Reward::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint tp = pTouch->getLocation();
    
    if (_touchEnable)
    {
        onTouchEnded(tp);
    }
}



#pragma mark - set examples

void E002_Base_Reward::createExampleSprite(const char* fileName, ...)
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


void E002_Base_Reward::createExampleSpriteForPsd(const char * fileName, ...)
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

void E002_Base_Reward::setExampleOriginPosition(std::vector<CCPoint>* originPositionVector)
{
    m_arrExamples->removeAllObjects();
    for (int i = 0; i < originPositionVector->size(); i++) {
        m_arrExamplesOriginPosition->addControlPoint(originPositionVector->at(i));
    }
}


void E002_Base_Reward::addChildExamples(int zorder /* = kDepth3_examples */)
{
    for (int i = 0; i < m_arrExamples->count(); i++) {
        CJSprite* example = (CJSprite*)m_arrExamples->objectAtIndex(i);
        this->addChild(example, zorder);
    }
}



void E002_Base_Reward::onExamplesTouched(int index)
{
    CCLog(" example touch : %d", index);
    /* override me */
}

void E002_Base_Reward::removeAllExamples()
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


#pragma mark - animation functions


void E002_Base_Reward::animationManagerParseComplete()
{
    startFlashAnimation();
}

void E002_Base_Reward::OnLastFrame(CJFlash::CJAnimation *pAnimation)
{
}

#pragma mark - utils functions

void E002_Base_Reward::setTouchEnableBaseLayer(bool enable)
{
    if (_touchEnable != enable) {
        _touchEnable = enable;
    }
}

bool E002_Base_Reward::getUserDefaultFirstGuide(eGuideRewardPageIndex page)
{
    std::string _key;
    
    if (page == eGuidePageP130)
    {
        _key = "_p130_guide_isFirst";
    }
    else if (page == eGuidePageP230)
    {
        _key = "_p230_guide_isFirst";
    }
    else if (page == eGuidePageP330)
    {
        _key = "_p330_guide_isFirst";
    }
    else
    {
        return false;
    }
    
    std::string resultKey = CJUtils::getStringMerge(CJUtils::getInstance()->getContentID(), _key);
    return CJUtils::getInstance()->getUserDefaultBoolForKey(resultKey);
}

void E002_Base_Reward::setUserDefaultFirstGuide(eGuideRewardPageIndex page)
{
    std::string _key;
    
    if (page == eGuidePageP130)
    {
        _key = "_p130_guide_isFirst";
    }
    else if (page == eGuidePageP230)
    {
        _key = "_p230_guide_isFirst";
    }
    else if (page == eGuidePageP330)
    {
        _key = "_p330_guide_isFirst";
    }

    std::string resultKey = CJUtils::getStringMerge(CJUtils::getInstance()->getContentID(), _key);
    CJUtils::getInstance()->setUserDefaultBoolForKey(resultKey, true);
}

void E002_Base_Reward::showGuide(std::vector<E002_Base_ImageGuide_Item*> *items)
{
    CJUtils::getInstance()->pauseAllAnimations(this);
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
    CJMultimedia::getInstance()->pauseAllNarration();

    mGuide = new E002_Base_ImageGuide();
    mGuide->init();
    
    if (mShowFirstGuide)
    {
        mGuide->setFirstGuide(true);
    }
    
    mGuide->setGuide(items);
    
    addChild(mGuide, kDepth10_guide);
    
    mGuide->showPopup(this);
    
}

void E002_Base_Reward::showGuide(E002_Base_ImageGuide_Item *item)
{
    std::vector<E002_Base_ImageGuide_Item*> *items = new std::vector<E002_Base_ImageGuide_Item*>();
    
    items->push_back(item);
    
    showGuide(items);
}

void E002_Base_Reward::removeGuide()
{
    if(mShowFirstGuide)
    {
        completeFirstGuide();
        mShowFirstGuide = false;
    }
    
    CJUtils::getInstance()->resumeAllAnimations(this);
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    CJMultimedia::getInstance()->resumeAllNarration();
    
    mGuide->hidePopup();
    removeChild(mGuide);
}


void E002_Base_Reward::addGuidePopupCompleteObserver()
{
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(E002_Base_Reward::removeGuide),
                                                                  CJNOTIFICATION_GUIDE_CLOSECALL,
                                                                  NULL);
}

void E002_Base_Reward::removeGuidePopupCompleteObserver()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, CJNOTIFICATION_GUIDE_CLOSECALL);
}
