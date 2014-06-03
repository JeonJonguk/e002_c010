//
//  CJLayer.cpp
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 5. 31..
//
//

#include "CJLayer.h"


//CCScene* CJLayer::scene()
//{
//    CCScene *scene = CCScene::create();
//    CJLayer* layer = CJLayer::create();
//    scene->addChild(layer);
//    return scene;
//}

#pragma mark - init

CJLayer::CJLayer()
{
    _imgBackground = NULL;
    _vTouchEnableCJSprites.clear();
}

CJLayer::~CJLayer()
{
    _vTouchEnableCJSprites.clear();
}


CJLayer * CJLayer::create(const ccColor4B& color)
{
    CJLayer * pLayer = new CJLayer();
    if(pLayer && pLayer->initWithColor(color))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

CJLayer * CJLayer::create(const ccColor4B& color, GLfloat width, GLfloat height)
{
    CJLayer * pLayer = new CJLayer();
    if( pLayer && pLayer->initWithColor(color,width,height))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}


bool CJLayer::init()
{
    if (!CCLayerColor::init()) {
        return false;
    }
    
    _currentTime = 0;
    
    m_bIsCompleteFlashParsing = false;
    m_bIsCompleteTransition = false;
    
    return true;
}

bool CJLayer::initWithColor(const ccColor4B& color)
{
    if (!CCLayerColor::initWithColor(color)) {
        return false;
    }
    return true;
}

bool CJLayer::initWithColor(const ccColor4B& color, GLfloat w, GLfloat h)
{
    if (!CCLayerColor::initWithColor(color,w,h))
    {
        return false;
    }
    return true;
}


void CJLayer::onEnter()
{
    CCLayerColor::onEnter();

    winSize = CCDirector::sharedDirector()->getWinSize(); // 1024 ,768 = 1024, 744
    winHalfSize = CCSizeMake(winSize.width/2, winSize.height/2);
    winCenter = ccp(winSize.width/2, winSize.height/2);
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    winCenter = ccp(winSize.width/2, (winSize.height+24)/2);3
//#endif
    
//    setTouchEnableCJLayer(NULL, true);
    CJUtils::performSelector(this, callfuncND_selector(CJLayer::setTouchEnableCJLayer), (void*)true , 0.5);
    
}

void CJLayer::onEnterTransitionDidFinish()
{
    CCLayerColor::onEnterTransitionDidFinish();
    
    onViewLoaded();
}

void CJLayer::onExit()
{ 
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CJUtils::stopAllAnimations(this);
    CJUtils::removeAllchildren(this);
    CJMultimedia::getInstance()->removeAllNarration();
    CJMultimedia::getInstance()->stopAllEffect();
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    CCTextureCache::sharedTextureCache()->removeAllTextures();


    CCLayerColor::onExit();
}

#pragma mark - load view

void CJLayer::onViewLoad()
{
    /* override */
}


void CJLayer::onViewLoaded()
{
    /* override */
}


void CJLayer::setBackgroundColor(const ccColor4B& color)
{
    // default blend function
    m_tBlendFunc.src = GL_SRC_ALPHA;
    m_tBlendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
    
    _displayedColor.r = _realColor.r = color.r;
    _displayedColor.g = _realColor.g = color.g;
    _displayedColor.b = _realColor.b = color.b;
    _displayedOpacity = _realOpacity = color.a;
    
    for (size_t i = 0; i<sizeof(m_pSquareVertices) / sizeof( m_pSquareVertices[0]); i++ )
    {
        m_pSquareVertices[i].x = 0.0f;
        m_pSquareVertices[i].y = 0.0f;
    }
    
    updateColor();
    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
}

void CJLayer::addChild(CCNode *child, int zOrder, int tag)
{
    if (child->getParent() != NULL) {
        child->removeFromParent();
    }
    CCNode::addChild(child, zOrder, tag);
}

void CJLayer::addChild(CCNode *child, int zOrder)
{
    CCNode::addChild(child, zOrder);
}

void CJLayer::addChild(CCNode *child)
{
    CCNode::addChild(child);
}



#pragma mark - touch

bool CJLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return false;
}

void CJLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void CJLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}


void CJLayer::setTouchEnableCJLayer(CCNode* sender, bool bDispatchEvents)
{
    
    if(CCDirector::sharedDirector()->getTouchDispatcher()->findHandler(this) == NULL){
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    }
    CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(bDispatchEvents);
}

void CJLayer::setTouchEnableCJSprite(CCNode* sender, bool bDispatchEvents)
{
    if (bDispatchEvents) {
        //CJSprite setTouchEnable->true (just resume)
        if (_vTouchEnableCJSprites.size() > 0) {
            for (int i = 0 ; i < _vTouchEnableCJSprites.size(); i++) {
                _vTouchEnableCJSprites[i]->setTouchEnable(true);
            }
            _vTouchEnableCJSprites.clear();
        }
        
    }else{
        //CJSprite setTouchEnable->false
        for(int i=0; i < this->getChildren()->count(); i++)
        {
            CCNode *child = (CCNode *)this->getChildren()->objectAtIndex(i);
            if(dynamic_cast<CJSprite *>(child))
            {
                CJSprite* cjSp = (CJSprite*)child;
                if (cjSp->isTouchEnabled()) {
                    
                    cjSp->setTouchEnable(false);
                    _vTouchEnableCJSprites.push_back(cjSp);
                }
            }
        }
    }
}

#pragma mark - getFilePath



std::string CJLayer::getFilePath(std::string path)
{
    std::string fullPath = CJUtils::getInstance()->getFilePath(path);
    return fullPath;
}

std::string CJLayer::getFilePath(string strFolderName, std::string strFileName)
{
    std::string fullPath = CJUtils::getInstance()->getFilePath(strFolderName, strFileName);
    return fullPath;
    
}

std::string CJLayer::getCommonFilePath(std::string path)
{
    std::string fullPath = CJUtils::getInstance()->getCommonFilePath(path);
    return fullPath;
}

std::string CJLayer::getCommonFilePath(string strFolderName, std::string strFileName)
{
    std::string fullPath = CJUtils::getInstance()->getCommonFilePath(strFolderName, strFileName);
    return fullPath;
    
}

std::string CJLayer::getImageFilePath(std::string path)
{
    std::string imagePath = CJUtils::getInstance()->getFilePath("img",path);
    return imagePath;
}

std::string CJLayer::getSoundFilePath(std::string path)
{
    std::string soundPath = CJUtils::getInstance()->getFilePath("snd",path);
    return soundPath;
}

#pragma mark - Sound

void CJLayer::playNarration(std::string fileName, bool bLoop /* = false */)
{
    CJMultimedia::getInstance()->playNarration(getFilePath("snd",fileName), bLoop);
}

void CJLayer::playNarrationWithDelay(std::string fileName, float delay)
{
    CJMultimedia::getInstance()->playNarrationWithDelay(this, getFilePath("snd",fileName), delay);
}

void CJLayer::playCommonNarration(std::string fileName, bool bLoop /* = false */)
{
    CJMultimedia::getInstance()->playNarration(getCommonFilePath("snd",fileName), bLoop);
}

void CJLayer::playCommonNarrationWithDelay(std::string fileName, float delay)
{
    CJMultimedia::getInstance()->playNarrationWithDelay(this, getCommonFilePath("snd",fileName), delay);
}


unsigned int CJLayer::playEffect(std::string fileName, bool bLoop)
{
    return CJMultimedia::getInstance()->playEffect(getFilePath("snd", fileName), bLoop);
}

void CJLayer::playEffectWithDelay(std::string fileName, float delay)
{
    CJMultimedia::getInstance()->playEffectWithDelay(this, getFilePath("snd",fileName), delay);
}

unsigned int CJLayer::playCommonEffect(std::string fileName, bool bLoop)
{
    return CJMultimedia::getInstance()->playEffect(getCommonFilePath("snd", fileName), bLoop);
}
 void CJLayer::playCommonEffectWithDelay(std::string fileName, float delay)
{
    CJMultimedia::getInstance()->playEffectWithDelay(this, getCommonFilePath("snd",fileName), delay);
}



void CJLayer::stopNarration(std::string fileName)
{
    CJMultimedia::getInstance()->stopNarration(getFilePath("snd",fileName));
}

void CJLayer::stopAllNarration()
{
    CJMultimedia::getInstance()->stopAllNarration();
}

void CJLayer::removeAllNarration()
{
    CJMultimedia::getInstance()->removeAllNarration();
}

void CJLayer::stopEffect(int soundId)
{
    CJMultimedia::getInstance()->stopEffect(soundId);
}

void CJLayer::stopAllEffect()
{
    CJMultimedia::getInstance()->stopAllEffect();
}

void CJLayer::addSoundObserver()
{
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(CJLayer::_onNarrationFinishedCallback),
                                                                  CJNOTIFICATION_VOICE_FINISHCALL,
                                                                  NULL);
}

void CJLayer::removeSoundObserver()
{ 
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, CJNOTIFICATION_VOICE_FINISHCALL);
}


// private : Don't use this function
void CJLayer::_onNarrationFinishedCallback(CCString *fileName)
{
    if (this) {
//        runAction(CCCallFuncND::create(this, callfuncND_selector(CJLayer::_onNarrationFinishedCallbackTransformThread), (void*)fileName->getCString()));
        onNarrationFinishedCallback(fileName->getCString());
    }

}

// private : transfrom thread for android texture bug.
void CJLayer::_onNarrationFinishedCallbackTransformThread(CCNode *sender, const char *fileName)
{
    onNarrationFinishedCallback(fileName);
}

// public : using this function to override
void CJLayer::onNarrationFinishedCallback(std::string fileName)
{
    /* override me */
}


#pragma mark - video

void CJLayer::addVideoObserver()
{
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(CJLayer::onVideoFinishedCallback),
                                                                  CJNOTIFICATION_VIDEO_FINISHCALL,
                                                                  NULL);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(CJLayer::onVideoBtnTouchCallback),
                                                                  CJNOTIFICATION_VIDEO_BUTTONCALL,
                                                                  NULL);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(CJLayer::onVideoIndexBtnTouchCallback),
                                                                  CJNOTIFICATION_VIDEO_INDEX_BUTTONCALL,
                                                                  NULL);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(CJLayer::onVideoFrameFinishedCallback),
                                                                  CJNOTIFICATION_FRAME_VIDEOVIEW_FINISHCALL,
                                                                  NULL);
    
}
void CJLayer::removeVideoObserver()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,CJNOTIFICATION_VIDEO_FINISHCALL);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,CJNOTIFICATION_VIDEO_BUTTONCALL);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,CJNOTIFICATION_VIDEO_INDEX_BUTTONCALL);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,CJNOTIFICATION_FRAME_VIDEOVIEW_FINISHCALL);
} 

void CJLayer::onVideoFinishedCallback()
{

}

void CJLayer::onVideoBtnTouchCallback(CCObject* tag)
{
}

void CJLayer::onVideoIndexBtnTouchCallback(CCObject* tag)
{
}

void CJLayer::onVideoFrameFinishedCallback()
{
    
}

#pragma mark - recording
void CJLayer::addRecordingObserver()
{
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(CJLayer::onVoiceRecordedPlayFinishedCallback),
                                                                  CJNOTIFICATION_RECORDED_VOICE_FINISHCALL,
                                                                  NULL);
}

void CJLayer::removeRecordingObserver()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,CJNOTIFICATION_RECORDED_VOICE_FINISHCALL);
}

void CJLayer::_onVoiceRecordedPlayFinishedCallbackTransformThread()
{
    runAction(CCCallFunc::create(this, callfunc_selector(CJLayer::onVoiceRecordedPlayFinishedCallback)));
}

void CJLayer::onVoiceRecordedPlayFinishedCallback()
{
    /* override me */
}


#pragma mark - scheduler
void CJLayer::onTimer()
{
    schedule(schedule_selector(CJLayer::_tick), 1.0/10.0);

}

void CJLayer::stopTimer()
{
    unschedule(schedule_selector(CJLayer::_tick));
    _currentTime = 0;
}

void CJLayer::_tick()
{
    _currentTime = _currentTime+1;
}

float CJLayer::getCurrentTime()
{
    return (float)_currentTime/10.0;
}




#pragma mark - background
////////////////////////////////////////////////////
//
// Background
//
////////////////////////////////////////////////////
void CJLayer::_setBackground(CCSprite *pSprite)
{
    if(_imgBackground != NULL)
    {
        if(_imgBackground->getParent() != NULL)
        {
            this->removeChild(_imgBackground, true);
        }
    }
    
    _imgBackground = pSprite;
    _imgBackground->setPosition(winCenter);
    
    this->addChild(_imgBackground, kDepth0_background);
}


void CJLayer::setBackground(CCSprite *pSprite)
{
    if(pSprite != NULL)
    {
        this->_setBackground(pSprite);
    }
}

void CJLayer::setBackground(std::string strImageName, bool bIsLanguage)
{
    CJSprite *tempSprite = CJSprite::createWithFullPath(strImageName.c_str());
    
    this->setBackground(tempSprite);
}

void CJLayer::setBackgroundPosition(CCPoint aPoint)
{
    if(_imgBackground != NULL)
    {
        _imgBackground->setPosition(aPoint);
    }
}

void CJLayer::setBackgroundScale(float fScale)
{
    if(_imgBackground != NULL)
    {
        _imgBackground->setScale(fScale);
    }
}


CCSprite* CJLayer::getBackgroundSprite()
{
    if(_imgBackground != NULL)
    {
        return _imgBackground;
    }
    else
    {
        return NULL;
    }
}


#pragma mark - utils

void CJLayer::removeAllpointArray(CCPointArray* pointArray)
{
    int count = pointArray->count();
    for (int i = 0; i < count; i++) {
        pointArray->removeControlPointAtIndex(count-1-i);
    }
}

const char* CJLayer::stringFromRect(CCNode* node)
{
    printf("cclogframe:");
    CCString* rect = CCString::createWithFormat("(%.1f, %.1f), (%.1f, %.1f)",node->getPositionX(),node->getPositionY(),node->getContentSize().width,node->getContentSize().height);
    return rect->getCString();
}



void CJLayer::cjMenuTouchBegan(CCTouch *touch, CCEvent* event)
{
//    CCPoint pt = touch->getLocation();
//    CJLog("pt = %f, %f", pt.x, pt.y);
}