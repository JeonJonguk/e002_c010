//
//  CJSprite.cpp
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 6. 21..
//
//

#include "CJSprite.h"
#include "CJUtils.h"

CJSprite::CJSprite()
{
    _defaultTouchAction = NULL;
    _defaultTouchActionReverse = NULL;
    
    _touchAction = NULL;
    _touchActionReverse = NULL;
    
    _bIsTouchEnable = false;
    _bTouchComplete = false;

    _callfuncSelector = NULL;
    _delegate = NULL;
}

CJSprite::~CJSprite()
{
    CJUtils::stopAllAnimations(this);
    CJUtils::removeAllchildren(this);
    
    CC_SAFE_RELEASE(_defaultTouchAction);
    CC_SAFE_RELEASE(_defaultTouchActionReverse);
    _defaultTouchAction = NULL;
    _defaultTouchActionReverse = NULL;
    
    CC_SAFE_RELEASE(_touchAction);
    CC_SAFE_RELEASE(_touchActionReverse);
    _touchAction = NULL;
    _touchActionReverse = NULL;
    
    _bIsTouchEnable = false;
}


CJSprite* CJSprite::create(const char *pszFileName)
{
    CJSprite *pobSprite = new CJSprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;

}

CJSprite* CJSprite::createWithFullPath(const char *pszFileName)
{
    CJSprite *pobSprite = new CJSprite();

    if (pobSprite && pobSprite->initWithFile(CJUtils::getInstance()->getFilePath("img",pszFileName).c_str()))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

CJSprite* CJSprite::createWithCommonPath(const char *pszFileName)
{
    CJSprite *pobSprite = new CJSprite();
    std::string str = pszFileName;
    if (pobSprite && pobSprite->initWithFile(CJUtils::getInstance()->getCommonFilePath("img", pszFileName).c_str()))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;

}

//CJSprite* CJSprite::createWithTexture(CCTexture2D *pTexture, const CCRect& rect)
//{
//    CJSprite *pobSprite = new CJSprite();
//    if (pobSprite && pobSprite->initWithTexture(pTexture, rect))
//    {
//        pobSprite->autorelease();
//        return pobSprite;
//    }
//    CC_SAFE_DELETE(pobSprite);
//    return NULL;
//}

bool CJSprite::initWithFile(const char *pszFilename)
{
    if (CCSprite::initWithFile(pszFilename)) {
        setDefualtOption();
        return true;
    }
    return false;
}


bool CJSprite::init()
{
    if (CCSprite::init()) {
        setDefualtOption();
        return true;
    }
    return false;
}

void CJSprite::onEnter()
{
    CCSprite::onEnter();
    m_originPosition = this->getPosition();
}

void CJSprite::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}

#pragma mark - addchild override

void CJSprite::addChild(CCNode *child)
{
    CCSprite::addChild(child);
}

void CJSprite::addChild(CCNode *child, int zOrder)
{
    CCSprite::addChild(child, zOrder);
}

void CJSprite::addChild(CCNode *child, int zOrder, int tag)
{
    if (child->getParent() != NULL) {
        child->removeFromParent();
    }
    CCSprite::addChild(child, zOrder, tag);
    
}

void CJSprite::addChildIgnoreParent(CCNode *child)
{
    if (child!= NULL && child->getParent() == this)
        return;
    
    addChild(child);
    this->_setPositionForParent(child);
}

void CJSprite::addChildIgnoreParent(CCNode *child, int zOrder)
{
    if (child->getParent() == this)
        return;
    
    addChild(child, zOrder);
    this->_setPositionForParent(child);
}


void CJSprite::addChildIgnoreParent(CCNode *child, int zOrder, int tag)
{
    if (child->getParent() == this)
        return;
    
    addChild(child, zOrder, tag);
    this->_setPositionForParent(child);
}



#pragma mark - touch delegate

bool CJSprite::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    
    if (!_bIsTouchEnable)
        return false;
    
    CCPoint sLocalPos = convertToNodeSpace(touch->getLocation());
    CCRect sRC = CCRect(getPositionX() - getContentSize().width * getAnchorPoint().x,
                        getPositionY() - getContentSize().height * getAnchorPoint().y,
                        getContentSize().width, getContentSize().height);
    
    
    sRC.origin = CCPointZero;
    bool isTouched = sRC.containsPoint(sLocalPos);
    if(isTouched)
    {
        onTouchEvent();
        
        return true;
    }
    
    return false;
}

void CJSprite::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    
}

void CJSprite::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    
}

void CJSprite::setTouchEnable(bool enable)
{
    if (enable == true) {
        if(CCDirector::sharedDirector()->getTouchDispatcher()->findHandler(this) == NULL){
            CCDirector* pDirector = CCDirector::sharedDirector();
            pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
        }
    }

    _bIsTouchEnable = enable;
};


#pragma mark - set sprite option

void CJSprite::setDefualtOption()
{
    _scale = this->getScale();
    _opacity = this->getOpacity();
    
    _defaultTouchAction = CCEaseElasticOut::create(CCScaleTo::create(0.2, 1.2) , 0.7);
    _defaultTouchActionReverse = CCEaseElasticOut::create(CCScaleTo::create(0.2, 1.0) , 0.7);
    _defaultTouchAction->retain();
    _defaultTouchActionReverse->retain();
}



void CJSprite::onTouchEvent()
{
    if (_bTouchComplete)
        return;
    
    if (_callfuncSelector && _delegate) {
        _delegate->runAction(CCCallFunc::create(_delegate, _callfuncSelector));
    }
}

void CJSprite::setTouchEvent(CCNode* delegate, SEL_CallFunc selector)
{
    _delegate = delegate;
    _callfuncSelector = selector;
}





void CJSprite::setTouchAction(CCAction* action)
{
    if (action) {
        _touchAction = action;
        _touchAction->retain();
    }

}

void CJSprite::setTouchActionReverse(CCAction* action)
{
    if (action) {
        _touchActionReverse = action;
        _touchActionReverse->retain();
    }
}

void CJSprite::onTouchActionEvent()
{
    if (_bIsTouchEnable)
    {
        stopAllActions();
        if (_touchAction) {
//            this->stopAction(_touchAction);
            this->runAction(_touchAction);
        }else{
//            this->stopAction(_defaultTouchAction);
            this->runAction(_defaultTouchAction);
        }
    }
}

void CJSprite::onTouchEndActionEvent()
{
    if (_bIsTouchEnable)
    {
        stopAllActions();
        if (_touchActionReverse) {
//            this->stopAction(_touchActionReverse);
            this->runAction(_touchActionReverse);
        }else{

//            this->stopAction(_defaultTouchActionReverse);
            this->runAction(_defaultTouchActionReverse);
        }
    }
}


#pragma mark - position
void CJSprite::setPositionForParent()
{
    CCNode* parent = this->getParent();
    CCNode* child = this;
    
    CCSize parentSize = parent->getContentSize();
    CCPoint parentAnchor = parent->getAnchorPoint();
    CCPoint childModifyPoint = ccpSub(child->getPosition(), parent->getPosition());
    child->setPosition(
                       ccp(
                           childModifyPoint.x+parentSize.width*parentAnchor.x,
                           childModifyPoint.y+parentSize.height*parentAnchor.y
                           )
                       );

}

void CJSprite::setPositionForRootParent(CCNode* rootParents)
{
    CCNode* parent = this->getParent();
    CCNode* child = this;
    
    while (parent != rootParents) {
        CCSize parentSize = parent->getContentSize();
        CCPoint parentAnchor = parent->getAnchorPoint();
        CCPoint childModifyPoint = ccpSub(child->getPosition(), parent->getPosition());
        child->setPosition(
                           ccp(
                               childModifyPoint.x+parentSize.width*parentAnchor.x,
                               childModifyPoint.y+parentSize.height*parentAnchor.y
                               )
                           );
        
        parent = parent->getParent();
    }
    
}


void CJSprite::_setPositionForParent(CCNode* child)
{
    CJSprite* parent = this;
    
    CCSize parentSize = parent->getContentSize();
	CCPoint parentAnchor = parent->getAnchorPoint();
	CCPoint childModifyPoint = ccpSub(child->getPosition(), parent->getPosition());
	child->setPosition(
                       ccp(
                           childModifyPoint.x+parentSize.width*parentAnchor.x,
                           childModifyPoint.y+parentSize.height*parentAnchor.y
                           )
                       );
}


void CJSprite::setAnchorPointWithoutPosition(CCPoint anchor)
{
    CCSize size = this->getContentSize();
    CCPoint position = this->getPosition();
    CCPoint originAnchor = this->getAnchorPoint();
    
    this->setPosition(ccp(position.x-(size.width*(originAnchor.x-anchor.x)), position.y-(size.height*(originAnchor.y-anchor.y))));
    this->setAnchorPoint(anchor);
}

#pragma mark - texture 

void CJSprite::changeTexture(std::string filePath)
{
    this->setTexture(CCTextureCache::sharedTextureCache()->addImage(filePath.c_str()));
}

void CJSprite::changeTextureWithFullPath(std::string fileName)
{
    this->setTexture(CCTextureCache::sharedTextureCache()->addImage( CJUtils::getInstance()->getFilePath("img",fileName).c_str() ));
}

void CJSprite::changeTextureWithCommonPath(std::string fileName)
{
    this->setTexture(CCTextureCache::sharedTextureCache()->addImage( CJUtils::getInstance()->getCommonFilePath("img",fileName).c_str() ));
}

