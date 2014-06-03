//
//  E002_Base_DrawLayer.cpp
//
//  Created by Lee.YJ on 13. 3. 28..
//  Copyright (c) 2013 CJ Educations. All rights reserved.
//

#include "E002_Base_DrawLayer.h"
#include "CJMultimedia.h"
#include "CJUtils.h"
#include "E002_Base_Define.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define ANDROID_GAP		0
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define ANDROID_GAP		0
#endif

E002_Base_DrawLayer* E002_Base_DrawLayer::create()
{
    E002_Base_DrawLayer* guideLayer = new E002_Base_DrawLayer();
    if(guideLayer != NULL)
    {
        guideLayer->autorelease();
        return guideLayer;
    }

    delete guideLayer;
    return NULL;
}

bool E002_Base_DrawLayer::init(CCSize size, CCPoint point, std::string strBrushName)
{
    if(!CCLayerColor::initWithColor(ccc4(255, 255, 255, 0)))
    {
        return false;
    }
    
    _playingDrawingSound = false;
    _drawable = false;
    _stamp = false;
    _bIsEraseMode = false;
    _drawSoundID = 0;
    
    _strStempSoundName.clear();
    _strStempSoundName = "";
    
    this->setContentSize(size);
    this->setPosition(point);
    this->setBrush(strBrushName);

    return true;
}

void E002_Base_DrawLayer::onEnter()
{
    CCLayerColor::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void E002_Base_DrawLayer::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
    CCLayerColor::onExit();
}

void E002_Base_DrawLayer::addDrawSoundEffect(std::string strSoundName)
{
    _strDrawEffectName = strSoundName;
}

void E002_Base_DrawLayer::addStempSoundEffect(std::string strSoundName)
{
    _strStempSoundName = strSoundName;
}

void E002_Base_DrawLayer::clearCanvas()
{
	m_target->clear(0, 0, 0, 0);
}

void E002_Base_DrawLayer::setBrush(std::string strBrushName)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize s = this->getContentSize();
    m_target = CCRenderTexture::create(s.width, s.height);
    
	if (NULL == m_target)
	{
		return;
	}
	
    m_target->setPosition(ccp(s.width/2, s.height/2 - (winSize.height-s.height)-ANDROID_GAP));

    addChild(m_target);

    m_brush = CCSprite::create(strBrushName.c_str());
    m_brush->setColor(ccc3(0, 0, 0));
    m_brush->retain();
    
    ccBlendFunc bf = { GL_ONE, GL_ONE_MINUS_SRC_ALPHA };
	m_brush->setBlendFunc(bf);
    setTouchEnabled(true);
}

void E002_Base_DrawLayer::changeBrush(std::string strBrushName)
{
    m_brush->setTexture(CCTextureCache::sharedTextureCache()->addImage(strBrushName.c_str()));
}

void E002_Base_DrawLayer::setBrushStroke(float rate)
{
    m_brush->setScale(rate);
}

void E002_Base_DrawLayer::setBrushColor(ccColor3B color)
{
    m_brush->setColor(color);
}

void E002_Base_DrawLayer::setDrawSound(std::string sndPath)
{
    m_drawSndPath = sndPath;
}

void E002_Base_DrawLayer::setEraseMode(bool enable)
{
    if(enable)
    {
        _ccBlendFunc f = {GL_ZERO,GL_ONE_MINUS_SRC_ALPHA };
        m_brush->setBlendFunc(f);
    }
    else
    {
        _ccBlendFunc f = {GL_ONE,GL_ONE_MINUS_SRC_ALPHA};
        m_brush->setBlendFunc(f);
    }
    _bIsEraseMode = enable;
}

bool E002_Base_DrawLayer::getEraseMode()
{
    return _bIsEraseMode;
}

void E002_Base_DrawLayer::setDraweable(bool enable)
{
    _drawable = enable;
}

void E002_Base_DrawLayer::brushTouchMoved(cocos2d::CCTouch *touches, cocos2d::CCEvent *event)
{
    CCPoint start = touches->getLocation();
    CCPoint end = touches->getPreviousLocation();
    
    float var = CCDirector::sharedDirector()->getWinSize().height-this->getContentSize().height;
    start.y = start.y-var-ANDROID_GAP;
    end.y = end.y-var-ANDROID_GAP;

    // begin drawing to the render texture
    m_target->begin();
    
    // for extra points, we'll draw this smoothly from the last position and vary the sprite's
    // scale/rotation/offset
    float distance = ccpDistance(start, end);
    if (distance > 1)
    {
        int d = (int)distance;
        for (int i = 0; i < d; i++)
        {
            float difx = end.x - start.x;
            float dify = end.y - start.y;
            float delta = (float)i / distance;
            CCPoint p1 = ccp(start.x + (difx * delta), start.y + (dify * delta));
            
            m_brush->setPosition( p1 );
            m_brush->setRotation( rand()%360 );
            
            m_brush->visit();
        }
    }
    // finish drawing and return context back to the screen
    m_target->end();
}

void E002_Base_DrawLayer::brushTouchEnded(cocos2d::CCTouch *touches, cocos2d::CCEvent *event)
{
    
}

#pragma mark - Stamp Function
void E002_Base_DrawLayer::setStampMode(bool enable)
{
    _stamp = enable;
}

void E002_Base_DrawLayer::setStampNode(CCNode* stamp)
{
	if (NULL == m_target)
	{
		return;
	}
    
	if (stamp) {
		m_stamp = stamp;
		m_stamp->retain();

		setTouchEnabled(true);
	} else {
		if (m_stamp) {
			m_stamp = NULL;
		}
	}
}

#pragma mark - Touch Function
bool E002_Base_DrawLayer::ccTouchBegan(CCTouch *touches, CCEvent *event)
{
    if(_drawable == false)
    {
        return false;
    }
    
    _sendDrawingStartMsg();
    
    CCPoint touchbegan = touches->getLocation();
    
    float var = CCDirector::sharedDirector()->getWinSize().height-this->getContentSize().height;
    touchbegan.y = touchbegan.y-var-ANDROID_GAP;

    m_target->begin();
    
    if (_stamp) {
        _playStempEffectSound();
        if (m_stamp) {
        	m_stamp->setPosition(touchbegan);
        	m_stamp->visit();
		}
    } else {
        m_brush->setPosition(touchbegan);
        m_brush->setRotation(rand()%360);
        m_brush->visit();
        
        /*if (_bIsEraseMode) {
            _drawSoundID = CJMultimedia::getInstance()->playEffect(CJUtils::getInstance()->getCommonFilePath("snd",m_drawSndPath), true);
        }else{
            _drawSoundID = CJMultimedia::getInstance()->playEffect(CJUtils::getInstance()->getCommonFilePath("snd",m_drawSndPath), true);
        }*/
        
        _drawSoundID = CJMultimedia::getInstance()->playEffect(CJUtils::getInstance()->getCommonFilePath("snd",m_drawSndPath), true);

    }
    
    m_target->end();
    return true;
}

void E002_Base_DrawLayer::ccTouchMoved(CCTouch *touches, CCEvent *event)
{
    if (!_stamp) {
        this->brushTouchMoved(touches, event);
    }
}

void E002_Base_DrawLayer::ccTouchEnded(CCTouch *touches, CCEvent *event)
{
    CCPoint touchbegan = touches->getLocation();
    
    float var = CCDirector::sharedDirector()->getWinSize().height-this->getContentSize().height;
    touchbegan.y = touchbegan.y-var;
    
    CJMultimedia::getInstance()->stopEffect(_drawSoundID);
    
    _sendDrawingCompleteMsg();
}

void E002_Base_DrawLayer::_playDrawingEffectSound()
{
    if (_playingDrawingSound == true)
    {
        return;
    }
    
    _playingDrawingSound = true;
    this->runAction(CCSequence::create(CCDelayTime::create(2.0f),
                                       CCCallFunc::create(this, callfunc_selector(E002_Base_DrawLayer::_resetDrawingSoundState)),
                                       NULL));
    _drawSoundID = CJMultimedia::getInstance()->playEffect(_strDrawEffectName.c_str());
}

void E002_Base_DrawLayer::_playStempEffectSound()
{
    CCLog("_playStempEffectSound %s", _strStempSoundName.c_str());
    
    CJMultimedia::getInstance()->playEffect(_strStempSoundName.c_str());
}



void E002_Base_DrawLayer::_resetDrawingSoundState()
{
    this->stopAllActions();
    
    CJMultimedia::getInstance()->stopEffect(_drawSoundID);
    
    _playingDrawingSound = false;
    _drawSoundID = 0;
}

void E002_Base_DrawLayer::_sendDrawingStartMsg()
{
    CCNotificationCenter::sharedNotificationCenter()->postNotification(E002_NOTIFICATION_DIARY_DRAWING_STARTCALL);
}

void E002_Base_DrawLayer::_sendDrawingCompleteMsg()
{
    CCNotificationCenter::sharedNotificationCenter()->postNotification(E002_NOTIFICATION_DIARY_DRAWING_FINISHCALL);
}
