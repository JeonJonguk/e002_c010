//
//  THBasicLayer.cpp
//  Think
//
//  Created by pureMini on 13. 2. 12..
//
//

#include "THBasicLayer.h"

// Class methods

// Remove all children and cleanup
void THBasicLayer::cleanNode(CCNode *pNode)
{
	while(pNode->getChildrenCount())
	{
		CCNode *firstChild = (CCNode *)pNode->getChildren()->objectAtIndex(0);
		THBasicLayer::cleanNode(firstChild);
	}
	
	pNode->removeFromParentAndCleanup(true);
}

// Constructor
THBasicLayer::THBasicLayer()
{
	
}

// Destructor
THBasicLayer::~THBasicLayer()
{
	this->removeAllChildren();
	CCTextureCache::sharedTextureCache()->removeUnusedTextures();
	CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
}

// Initializer
bool THBasicLayer::init()
{
	if(!CCLayerColor::init())
	{
		return false;
	}
	
	// Initialize
	m_tWinSize = CCDirector::sharedDirector()->getWinSize();
	m_tWinCenter = CCPointMake(m_tWinSize.width / 2.0f, m_tWinSize.height / 2.0f);
	
	return true;
}

bool THBasicLayer::initWithColor(const ccColor4B &tColor)
{
	if(!CCLayerColor::initWithColor(tColor))
	{
		return false;
	}
	
	// Initialize
	m_tWinSize = CCDirector::sharedDirector()->getWinSize();
	m_tWinCenter = CCPointMake(m_tWinSize.width / 2.0f, m_tWinSize.height / 2.0f);
	
	return true;
}

bool THBasicLayer::initWithColor(const ccColor4B &tColor, GLfloat fWidth, GLfloat fHeight)
{
	if(!CCLayerColor::initWithColor(tColor, fWidth, fHeight))
	{
		return false;
	}
	
	// Initialize
	m_tWinSize = CCDirector::sharedDirector()->getWinSize();
	m_tWinCenter = CCPointMake(m_tWinSize.width / 2.0f, m_tWinSize.height / 2.0f);
	
	return true;
}

// Member methods

// Remove all children
void THBasicLayer::removeAllChildren()
{
	while(this->getChildrenCount())
	{
		CCNode *firstChild = (CCNode *)this->getChildren()->objectAtIndex(0);
		THBasicLayer::cleanNode(firstChild);
	}
}

// Get is parent contains child
bool THBasicLayer::isChildren(CCNode *pNode)
{
	CCArray *children = this->getChildren();
	int l = children->count();
	if(l)
	{
		for(int i = 0; i < l; i++)
		{
			if(children->objectAtIndex(i) == pNode)
			{
				return true;
			}
		}
	}
	
	return false;
}

//// Begin draw
//void THBasicLayer::onEnter()
//{
//	CCLog("On enter");
//}
//
//// Finish draw
//void THBasicLayer::onExit()
//{
//	CCLog("On exit");
//}
//
//// For touch events
//bool THBasicLayer::ccTouchBegan(CCTouch *touch, CCEvent *event)
//{
//	CCPoint tp = touch->getLocation();
//	
//	return false;
//}
//
//void THBasicLayer::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
//{
//	CCPoint tp = touch->getLocation();
//}
//
//void THBasicLayer::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
//{
//	CCPoint tp = touch->getLocation();
//}

