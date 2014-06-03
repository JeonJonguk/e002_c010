
#include "cocos2d.h"

#include "CJAnimationManager.h"
#include "CJAnimationDataPool.h"

enum
{
    kAnimationManager_Loading = 10000,
};


CJAnimationManager::CJAnimationManager(void)
{
    m_pAnimationParent = NULL;
    m_pLoadingParent = CCNode::create();
    
    m_parseType = kParseTypeJSON;
    m_bIsLoading = false;
}

CJAnimationManager::~CJAnimationManager(void)
{
    m_pAnimationParent = NULL;
    m_pLoadingParent = NULL;
    
    CC_SAFE_DELETE(m_pLoadingParent);
}

void CJAnimationManager::removeAllDatapool()
{
    STL_MULTIMAP_DATAPOOL::iterator it = m_stl_mmap_Datapool.begin();
    while( it != m_stl_mmap_Datapool.end() )
    {
        CJ_SAFE_DELETE( it->second );
        it++;
    }
    m_stl_mmap_Datapool.clear();

}

#pragma mark - setting function

void CJAnimationManager::setAnimationFile(std::string sStr, std::string aStr, std::string kStr)
{
    CJAnimationFiles file = CJAnimationFiles(sStr, aStr, kStr, true);
//    file.setFiles;
    m_animationFiles.push_back(file);
}


void CJAnimationManager::setAnimationCommonFile(std::string sStr, std::string aStr, std::string kStr)
{
    std::string sheetfile = CJUtils::getInstance()->getCommonFilePath("flash", sStr).c_str();
    std::string animationfile = CJUtils::getInstance()->getCommonFilePath("flash", aStr).c_str();
    
    CJAnimationFiles file = CJAnimationFiles(sheetfile, animationfile, kStr, false);
//    file.setFiles(;
    m_animationFiles.push_back(file);
}

void CJAnimationManager::setAnimationParent(CCNode* node)
{
    m_pAnimationParent = node;
}

//void CJAnimationManager::setAnimationParseType(ParseType pType)
//{
//    m_parseType = pType;
//}

void CJAnimationManager::setLoadingToParent(CCNode* parent)
{
    m_bIsLoading = true;
    
    CC_SAFE_DELETE(m_pLoadingParent);
    m_pLoadingParent = parent;
}




#pragma mark - start/end function


void CJAnimationManager::animationManagerParseStart()
{
//    if (m_bIsLoading)
//    {
//        m_loadingAnimation = new CJLoadingAnimation();
//        m_loadingAnimation->init();
//        m_pLoadingParent->addChild(m_loadingAnimation, kAnimationManager_Loading, kAnimationManager_Loading);
//    }
//    
//    CJParseThread* s_CJParseThread = new CJParseThread();
//    s_CJParseThread->parseStart(this);
    
    parseThreadStartCallback();
    animationManagerParseComplete();
}


void CJAnimationManager::_completeCallback()
{
    if(m_bIsLoading)
    {
        m_loadingAnimation->stopAllActions();
        m_loadingAnimation->removeFromParent();
    }
    
    animationManagerParseComplete();
}

void CJAnimationManager::_callFunctionWithDelay(cocos2d::SEL_CallFunc aSelector, float fDelayTime)
{
    cocos2d::CCActionManager *manager = cocos2d::CCDirector::sharedDirector()->getActionManager();
    cocos2d::CCCallFunc *callFunc = cocos2d::CCCallFunc::create((cocos2d::CCObject *)this, aSelector);
    cocos2d::CCDelayTime *delay = cocos2d::CCDelayTime::create(fDelayTime);
    cocos2d::CCSequence *action = cocos2d::CCSequence::create(delay, callFunc, NULL);
    
    manager->addAction(CCSequence::create(action,NULL), (cocos2d::CCNode *)this, false);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - override function

void CJAnimationManager::begin()
{
    CCLog("ANIMATION MANAGER BEGIN");
}

void CJAnimationManager::parseThreadStartCallback()
{
    CCLog("PARSER START");
    
    CCAssert(m_animationFiles.size() > 0, "animation files did not exist");
    
    std::vector<CJAnimationFiles> ::iterator aniIter;
    
    for(aniIter=m_animationFiles.begin(); aniIter!=m_animationFiles.end(); aniIter++)
    {
        std::string sheetName = aniIter->sheetsName;
        std::string aniName = aniIter->animationsName;
        std::string dataPoolKey = aniIter->dataPoolKeyName;
        bool isFullPath = aniIter->isFullPath;
        
        CJAnimationDataPool* datapool = NULL;
        if (m_parseType == kParseTypeXML)
        {
            datapool = CJFlash::parseXmlAnimation(sheetName.c_str(), aniName.c_str(), isFullPath);
        }
        else if( m_parseType == kParseTypeJSON)
        {
            datapool = CJFlash::parseJsonAnimation(sheetName.c_str(), aniName.c_str(), isFullPath);
        }
        
        std::pair<std::string, CJFlash::CJAnimationDataPool*> Enumerator( dataPoolKey, datapool );
        m_stl_mmap_Datapool.insert( Enumerator );
        datapool->setDataPoolKey(dataPoolKey);
    }
}

void CJAnimationManager::parseThreadEndCallback()
{
    CCLog("PARSER COMPLETE");
    
    _callFunctionWithDelay(callfunc_selector(CJAnimationManager::_completeCallback), 0.2f);
}

void CJAnimationManager::end()
{
    CCLog("ANIMATION MANAGER END");
}



void CJAnimationManager::parseStart()
{
    CCLog("PARSER START");
    
    CCAssert(m_animationFiles.size() > 0, "animation files did not exist");
    
    std::vector<CJAnimationFiles> ::iterator aniIter;
    
    for(aniIter=m_animationFiles.begin(); aniIter!=m_animationFiles.end(); aniIter++)
    {
        std::string sheetName = aniIter->sheetsName;
        std::string aniName = aniIter->animationsName;
        std::string dataPoolKey = aniIter->dataPoolKeyName;
        bool isFullPath = aniIter->isFullPath;
        
        CJAnimationDataPool* datapool;
        if (m_parseType == kParseTypeXML)
        {
            datapool = CJFlash::parseXmlAnimation(sheetName.c_str(), aniName.c_str(), isFullPath);
        }
        else if( m_parseType == kParseTypeJSON)
        {
            datapool = CJFlash::parseJsonAnimation(sheetName.c_str(), aniName.c_str(), isFullPath);
        }
        
        std::pair<std::string, CJFlash::CJAnimationDataPool*> Enumerator( dataPoolKey, datapool );
        m_stl_mmap_Datapool.insert( Enumerator );
        datapool->setDataPoolKey(dataPoolKey);
    }
}



#pragma mark - setting function
std::multimap<std::string, CJFlash::CJAnimationDataPool*> CJAnimationManager::getAllDatapool()
{
    return m_stl_mmap_Datapool;
}

void CJAnimationManager::setAllDatapool(STL_MULTIMAP_DATAPOOL allDatapool)
{
    m_stl_mmap_Datapool = allDatapool;
}

void CJAnimationManager::createAllAnimations()
{
    CCAssert(m_stl_mmap_Datapool.size() > 0, "datapool did not exist");
    
    STL_MULTIMAP_DATAPOOL::iterator it = m_stl_mmap_Datapool.begin();
    for (; it != m_stl_mmap_Datapool.end(); ++it)
    {
        createAnimationsInDataPool(it->first);
    }
}


void CJAnimationManager::createAnimationsInDataPool(std::string datapoolKey)
{
    CJAnimationDataPool* dataPool = getDataPoolByKey(datapoolKey);
    dataPool->createAllAnimations();
    
    std::vector<CJAnimation*>* allAni = dataPool->getAllAnimations();
    
    std::vector<CJAnimation*>::iterator aniIter;
    
    for(aniIter = allAni->begin(); aniIter != allAni->end(); aniIter++)
    {
        CJAnimation* _flashAni = *aniIter;
        _flashAni->init(this);
    }
}

void CJAnimationManager::createAnimation(std::string datapoolKey, std::string animationName)
{
    CJAnimationDataPool*dataPool = getDataPoolByKey(datapoolKey);
    CJAnimation* _flashAni = dataPool->createAnimationObjectFromAnimationName(animationName);
    
    _flashAni->init(this);
    
}

void CJAnimationManager::createAnimationAndSetKey(std::string datapoolKey, std::string animationName, std::string animationKey)
{
    createAnimation(datapoolKey, animationName);
    
    CJAnimation* _flashAni = getAnimationByName(datapoolKey, animationName);
    _flashAni->setAnimationKey(animationKey.c_str());
}




CJAnimationDataPool* CJAnimationManager::getDataPoolByKey(std::string strKey)
{
    CCAssert(m_stl_mmap_Datapool.size() > 0, "datapool did not exist");
    
    STL_MULTIMAP_DATAPOOL::iterator it = m_stl_mmap_Datapool.find( strKey );
    
    CCAssert(it != m_stl_mmap_Datapool.end(), "datapool key is not found");
    
    CJAnimationDataPool* dataPool = (CJAnimationDataPool*)it->second;
    return dataPool;
}

CJAnimation* CJAnimationManager::getAnimationByName(std::string datapoolKey, std::string animationName)
{
    CJAnimationDataPool*dataPool = getDataPoolByKey(datapoolKey);
    CJAnimation* pAni = (CJAnimation*)dataPool->getAnimationFromAnimationName(animationName);
    return pAni;
}

CJAnimation* CJAnimationManager::getAnimationByKey(std::string datapoolKey, std::string animationKey)
{
    CJAnimationDataPool*dataPool = getDataPoolByKey(datapoolKey);
    
    return dataPool->getAnimationFromAnimationKey(animationKey);
}

std::vector<CJAnimation*>* CJAnimationManager::getAllAnimationsByKey(std::string datapoolKey)
{
    CJAnimationDataPool*dataPool = getDataPoolByKey(datapoolKey);
    
    return dataPool->getAllAnimations();
}



void CJAnimationManager::setAnimationKey(CJAnimation* animation, std::string animationKey)
{
    animation->setAnimationKey(animationKey.c_str());
}

std::string CJAnimationManager::getAnimationKey(CJAnimation* animation)
{
    return animation->getKey();
}

void CJAnimationManager::setAnimationKey(std::string datapoolKey, std::string animationName, std::string animationKey)
{
    CJAnimation* _flashAni = getAnimationByName(datapoolKey, animationName);
    _flashAni->setAnimationKey(animationKey.c_str());
}

std::string CJAnimationManager::getAnimationKey(std::string datapoolKey, std::string animationName)
{
    CJAnimation* _flashAni = getAnimationByName(datapoolKey, animationName);
    return _flashAni->getKey();
}



int CJAnimationManager::getDataPoolCount()
{
    return m_stl_mmap_Datapool.size();
}

int CJAnimationManager::getAnimationCount(std::string datapoolKey)
{
    CJAnimationDataPool*dataPool = getDataPoolByKey(datapoolKey);
    
    return dataPool->getAnimationCount();
}


#pragma mark - CJFlashAnimationDelegate

void CJAnimationManager::OnPlay(CJAnimation* pAnimation)
{
//    CCLog("OnPlay");
}

void CJAnimationManager::OnStop(CJAnimation* pAnimation)
{
//    CCLog("OnStop");
}

void CJAnimationManager::OnLastFrame(CJAnimation* pAnimation)
{
//    CCLog("OnLastFrame");
}

void CJAnimationManager::OnPause(CJAnimation* pAnimation)
{
//    CCLog("OnPause");
}

void CJAnimationManager::OnUpdate(CJAnimation* pAnimation)
{
//    CCLog("OnUpdate");
}



#pragma mark - addParticularFrameCallback

void CJAnimationManager::addNarrationOnFlashFrame(CJAnimation* animation, int pFrame, const char* pSoundPath)
{
    animation->addParticularFrameCallback(animation,
                                           CJAnimationManager::onArriveAtParticularFrameNarr,
                                           pFrame,
                                           new CCString(pSoundPath));
}

void CJAnimationManager::addEffectOnFlashFrame(CJAnimation* animation, int pFrame, const char* pSoundPath)
{
    CCLog(">>>> %s", pSoundPath);
    animation->addParticularFrameCallback(animation,
                                           CJAnimationManager::onArriveAtParticularFrameEffect,
                                           pFrame,
                                           new CCString(pSoundPath));
}

void CJAnimationManager::addNarrationOnFlashFrameByName(std::string datapoolKey, std::string animationName, int pFrame, const char* pSoundPath)
{
    CJAnimation* _flashAni = getAnimationByName(datapoolKey, animationName);
    _flashAni->addParticularFrameCallback(_flashAni,
                                           CJAnimationManager::onArriveAtParticularFrameNarr,
                                           pFrame,
                                           new CCString(pSoundPath));
}

void CJAnimationManager::addEffectOnFlashFrameByName(std::string datapoolKey, std::string animationName, int pFrame, const char* pSoundPath)
{
    CJAnimation* _flashAni = getAnimationByName(datapoolKey, animationName);
    _flashAni->addParticularFrameCallback(_flashAni,
                                           CJAnimationManager::onArriveAtParticularFrameEffect,
                                           pFrame,
                                           new CCString(pSoundPath));
}



void CJAnimationManager::onArriveAtParticularFrameNarr(CCNode* sender, SEL_CallFuncND pCallFunc, void *pUserData)
{
    CCString *fileName = (CCString *)pUserData;
    CCLog("ARRIVE FRAME NAR:%s", fileName->getCString());
    if (fileName != NULL)
    {
        CJMultimedia::getInstance()->playNarration(fileName->getCString());
    }
}

void CJAnimationManager::onArriveAtParticularFrameEffect(CCNode* sender, SEL_CallFuncND pCallFunc, void *pUserData)
{
    CCString *fileName = (CCString *)pUserData;
    CCLog("ARRIVE FRAME EFF:%s", fileName->getCString());
    if (fileName != NULL)
    {
        CJMultimedia::getInstance()->playEffect(fileName->getCString());
    }
}



#pragma mark - playAnimation



CJAnimation* CJAnimationManager::attachAnimation(std::string datapoolKey, std::string animationName, bool bIsCommonPath, CCNode* parent)
{
    CJAnimation* _flashAni = getAnimationByName(datapoolKey, animationName);
    _flashAni->m_bIsCommonPath = bIsCommonPath;
    _flashAni->preload();
    _flashAni->setVisible(true);
    _flashAni->setFrame(0);
    
    CCNode* _parent;
    
    parent == NULL ? _parent = m_pAnimationParent : _parent = parent;
    
    if (_flashAni->getParent() != _parent)
    {
        _parent->addChild(_flashAni);
    }
    
    return _flashAni;
    
}

void CJAnimationManager::playAnimation(CJAnimation* animation, int repeatCount, int depth, CCNode* parent)
{
    CCNode* _parent;
    
    parent == NULL ? _parent = m_pAnimationParent : _parent = parent;
    
    if (animation->getParent() != _parent)
    {
        _parent->addChild(animation, depth);
    }
    
    if (repeatCount < 0)
    {
        animation->playAnimation(0, true);
    }
    else
    {
        animation->playAnimationRepeatCount(repeatCount);
    }
}

CJAnimation* CJAnimationManager::playAnimation(std::string datapoolKey, std::string animationName, int repeatCount, int depth, CCNode* parent)
{
    CJAnimation* _flashAni = getAnimationByName(datapoolKey, animationName);
    _flashAni->setVisible(true);
    playAnimation(_flashAni, repeatCount, depth, parent);
    
    return _flashAni;
}

CJAnimation* CJAnimationManager::playAnimationByKey(std::string datapoolKey, std::string animationKey, int repeatCount, int depth, CCNode* parent)
{
    CJAnimation* _flashAni = getAnimationByKey(datapoolKey, animationKey);
    
    playAnimation(_flashAni, repeatCount, depth, parent);
    
    return _flashAni;
}

CJAnimation* CJAnimationManager::playAnimationWithCommonPath(CJAnimation* animation, int repeatCount, int depth, CCNode* parent)
{
    animation->m_bIsCommonPath = true;
    
    CCNode* _parent;
    
    parent == NULL ? _parent = m_pAnimationParent : _parent = parent;
    
    
    if (animation->getParent() != _parent)
    {
        _parent->addChild(animation, depth);
    }
    
    if (repeatCount < 0)
    {
        animation->playAnimation(0, true);
    }
    else
    {
        animation->playAnimationRepeatCount(repeatCount);
    }
    
    return animation;
}

CJAnimation* CJAnimationManager::playAnimationWithCommonPath(std::string datapoolKey, std::string animationName, int repeatCount, int depth, CCNode* parent)
{
    CJAnimation* animation = getAnimationByName(datapoolKey, animationName);
    
    return playAnimationWithCommonPath(animation, repeatCount, depth, parent);
}


CJAnimation* CJAnimationManager::playAnimationWithCommonPathByKey(std::string datapoolKey, std::string animationKey, int repeatCount, int depth, CCNode* parent)
{
    CJAnimation* animation = getAnimationByKey(datapoolKey, animationKey);
    return playAnimationWithCommonPath(animation, repeatCount, depth, parent);
}

void CJAnimationManager::playLoopingAnimation(CJAnimation* animation, int depth, CCNode* parent)
{
    CCNode* _parent;
    
    parent == NULL ? _parent = m_pAnimationParent : _parent = parent;
    
    if (animation->getParent() != _parent)
    {
        _parent->addChild(animation, depth);
    }
    
    animation->playAnimation(0, true);
}

CJAnimation* CJAnimationManager::playLoopingAnimation(std::string datapoolKey, std::string animationName, int depth, CCNode* parent)
{
    CJAnimation* _flashAni = getAnimationByName(datapoolKey, animationName);
    
    playLoopingAnimation(_flashAni, depth, parent);
    
    return _flashAni;
}

CJAnimation* CJAnimationManager::playLoopingAnimationByKey(std::string datapoolKey, std::string animationKey, int depth, CCNode* parent)
{
    CJAnimation* _flashAni = getAnimationByKey(datapoolKey, animationKey);
    playLoopingAnimation(_flashAni, depth, parent);
    return _flashAni;
}


void CJAnimationManager::stopAnimation(CJAnimation* animation)
{
    animation->stopAnimation(false);
}

void CJAnimationManager::stopAnimation(std::string datapoolKey, std::string animationName)
{
    CJAnimation* animation = getAnimationByName(datapoolKey, animationName);
    stopAnimation(animation);
}

void CJAnimationManager::stopAnimationByKey(std::string datapoolKey, std::string animationKey)
{
    CJAnimation* animation = getAnimationByName(datapoolKey, animationKey);
    stopAnimation(animation);
}

void CJAnimationManager::stopAllAnimationsInDataPool(CJAnimationDataPool* datapool)
{
    std::vector<CJAnimation*>* allAni = datapool->getAllAnimations();
    
    std::vector<CJAnimation*>::iterator aniIter;
    
    for(aniIter = allAni->begin(); aniIter != allAni->end(); aniIter++)
    {
        CJAnimation* _flashAni = *aniIter;
//        _flashAni->stopAnimation();
        stopAnimation(_flashAni);
    }
}

void CJAnimationManager::stopAllAnimationsInDataPool(std::string datapoolKey)
{
    CJAnimationDataPool*dataPool = getDataPoolByKey(datapoolKey);
    stopAllAnimationsInDataPool(dataPool);
}




void CJAnimationManager::stopAllAnimations()
{
    STL_MULTIMAP_DATAPOOL::iterator it = m_stl_mmap_Datapool.begin();
    for (; it != m_stl_mmap_Datapool.end(); ++it)
    {
        stopAllAnimationsInDataPool(it->first);
    }
}

void CJAnimationManager::pauseAnimation(CJAnimation* animation)
{
    if(animation->isPlay() == true)
    {
        animation->pauseAnimation();
    }
}

void CJAnimationManager::pauseAnimation(std::string datapoolKey, std::string animationName)
{
    CJAnimation* animation = getAnimationByName(datapoolKey, animationName);
    pauseAnimation(animation);
}

void CJAnimationManager::pauseAnimationByKey(std::string datapoolKey, std::string animationKey)
{
    CJAnimation* animation = getAnimationByKey(datapoolKey, animationKey);
    pauseAnimation(animation);
}


void CJAnimationManager::pauseAllAnimationsInDataPool(CJAnimationDataPool* datapool)
{
    std::vector<CJAnimation*>* allAni = datapool->getAllAnimations();
    
    std::vector<CJAnimation*>::iterator aniIter;
    
    for(aniIter = allAni->begin(); aniIter != allAni->end(); aniIter++)
    {
        CJAnimation* _flashAni = *aniIter;
        
        if(_flashAni->isPlay() == true)
        {
            _flashAni->pauseAnimation();
        }
    }
}
void CJAnimationManager::pauseAllAnimationsInDataPool(std::string datapoolKey)
{
    CJAnimationDataPool*datapool = getDataPoolByKey(datapoolKey);
    pauseAllAnimationsInDataPool(datapool);
}

void CJAnimationManager::pauseAllAnimations()
{
    STL_MULTIMAP_DATAPOOL::iterator it = m_stl_mmap_Datapool.begin();
    for (; it != m_stl_mmap_Datapool.end(); ++it)
    {
        pauseAllAnimationsInDataPool(it->first);
    }
}

void CJAnimationManager::resumeAnimation(CJAnimation* animation)
{
    if(animation->isPause() == true)
    {
        animation->resumeAnimation();
    }
}

void CJAnimationManager::resumeAnimation(std::string datapoolKey, std::string animationName)
{
    CJAnimation* animation = getAnimationByName(datapoolKey, animationName);
    resumeAnimation(animation);
}

void CJAnimationManager::resumeAnimationByKey(std::string datapoolKey, std::string animationKey)
{
    CJAnimation* animation = getAnimationByKey(datapoolKey, animationKey);
    resumeAnimation(animation);
}

void CJAnimationManager::resumeAllAnimationsInDataPool(CJAnimationDataPool* datapool)
{
    std::vector<CJAnimation*>* allAni = datapool->getAllAnimations();
    
    std::vector<CJAnimation*>::iterator aniIter;
    
    for(aniIter = allAni->begin(); aniIter != allAni->end(); aniIter++)
    {
        CJAnimation* _flashAni = *aniIter;
        
        if(_flashAni->isPause() == true)
        {
            _flashAni->resumeAnimation();
        }
    }
}

void CJAnimationManager::resumeAllAnimationsInDataPool(std::string datapoolKey)
{
    CJAnimationDataPool*datapool = getDataPoolByKey(datapoolKey);
    resumeAllAnimationsInDataPool(datapool);
}

void CJAnimationManager::resumeAllAnimations()
{
    STL_MULTIMAP_DATAPOOL::iterator it = m_stl_mmap_Datapool.begin();
    for (; it != m_stl_mmap_Datapool.end(); ++it)
    {
        resumeAllAnimationsInDataPool(it->first);
    }
}

void CJAnimationManager::removeAnimation(CJAnimation* animation, bool bClean)
{
    animation->stopAnimation(bClean);
    if (bClean) {
        animation->removeFromParent();
    }
    else
    {
        animation->setVisible(false);
    }
}

void CJAnimationManager::removeAnimation(std::string datapoolKey, std::string animationName, bool bClean)
{
    CJAnimation* animation  = getAnimationByName(datapoolKey, animationName);
    removeAnimation(animation, bClean);
}

void CJAnimationManager::removeAnimationByKey(std::string datapoolKey, std::string animationKey, bool bClean)
{
    CJAnimation* animation  = getAnimationByKey(datapoolKey, animationKey);
    removeAnimation(animation, bClean);
}


void CJAnimationManager::removeAllAnimationsInDataPool(CJAnimationDataPool* datapool, bool bClean)
{
    std::vector<CJAnimation*>* allAni = datapool->getAllAnimations();
    
    std::vector<CJAnimation*>::iterator aniIter;
    
    for(aniIter = allAni->begin(); aniIter != allAni->end(); aniIter++)
    {
        CJAnimation* _flashAni = *aniIter;
        
        removeAnimation(_flashAni, bClean);
//        _flashAni->stopAnimation(true);
//        if (_flashAni->getParent() != NULL)
//        {
//            _flashAni->removeFromParent();
//        }
    }
}

void CJAnimationManager::removeAllAnimationsInDataPool(std::string datapoolKey, bool bClean)
{
    CJAnimationDataPool*datapool = getDataPoolByKey(datapoolKey);
    removeAllAnimationsInDataPool(datapool, bClean);
}

void CJAnimationManager::removeAllAnimations(bool bClean)
{
    STL_MULTIMAP_DATAPOOL::iterator it = m_stl_mmap_Datapool.begin();
    for (; it != m_stl_mmap_Datapool.end(); ++it)
    {
        removeAllAnimationsInDataPool(it->first, bClean);
    }
}


// dictionary에서 완전히 삭제후 새로운 flash 객체 생성 (모든 설정 초기화)

CJAnimation* CJAnimationManager::cleanAndNewAnimation(std::string datapoolKey, std::string animationName)
{
    removeAnimation(datapoolKey, animationName);
    createAnimation(datapoolKey, animationName);
    return getAnimationByName(datapoolKey, animationName);
}

CJAnimation* CJAnimationManager::cleanAndNewAnimationAndSetKey(std::string datapoolKey, std::string animationName, std::string animationKey)
{
    CJAnimation* animation = cleanAndNewAnimation(datapoolKey, animationName);
    animation->setAnimationKey(animationKey.c_str());
    return animation;
}

void CJAnimationManager::reorderFlashChildren(CJAnimation* animation)
{
    
}

CJAnimation* CJAnimationManager::replaceAnimation(std::string oldDataPoolKey, std::string oldAnimationName, std::string newDataPoolKey, std::string newAnimationName, int repeatCount)
{
    CJAnimation* _flashAni = getAnimationByName(oldDataPoolKey, oldAnimationName);
    
    int depth = _flashAni->getZOrder();
    CCNode* parent = _flashAni->getParent();
    CCPoint pos = _flashAni->getPosition();
    
    CJAnimation* newAni = playAnimation(newDataPoolKey, newAnimationName, repeatCount, depth, parent);
    newAni->setPosition(pos);
    
    stopAnimation(oldDataPoolKey, oldAnimationName);
    
    return newAni;
}


#pragma mark - sprite

CCSprite* CJAnimationManager::getSpriteFromFlash(CJAnimation* animation, const char* spriteName)
{
    CCSprite* sp = (CCSprite*)animation->getSpriteFromSpriteName(spriteName);
    return sp;
}

CCSprite* CJAnimationManager::getSpriteFromFlash(const char* dataPoolKey, const char* animationName, const char* spriteName)
{
    CJAnimation* animation = getAnimationByName(dataPoolKey, animationName);
    return getSpriteFromFlash(animation, spriteName);
}

void CJAnimationManager::replaceFlashSpriteTexture(CCSprite* spriteInFlash, CCSprite* spriteForTexture)
{
    CCTexture2D* texture = spriteForTexture->getTexture();
    spriteInFlash->setTexture(texture);
    spriteInFlash->setVisible(true);
    
    spriteForTexture->setVisible(false);
}

void CJAnimationManager::replaceFlashSpriteTextureRestore(CCSprite* spriteInFlash, CCSprite* spriteForTexture)
{
    spriteForTexture->setVisible(true);
    spriteInFlash->setVisible(false);
}
