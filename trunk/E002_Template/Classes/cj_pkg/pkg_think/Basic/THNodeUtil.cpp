//
//  THNodeUtil.cpp
//  Think
//
//  Created by pureye4u BX on 12. 7. 9..
//  Copyright CJ Educations 2012. All rights reserved.
//

#include "THNodeUtil.h"

using namespace cocos2d;

// Remove all children on CCNode
void THNodeUtil::removeAllChildren(cocos2d::CCNode *pParent)
{
	while(pParent->getChildrenCount())
	{
		CCNode *firstChild = (CCNode *)pParent->getChildren()->objectAtIndex(0);
		THNodeUtil::cleanNode(firstChild);
	}
}

// Remove all children and cleanup
void THNodeUtil::cleanNode(CCNode *pNode)
{
	while(pNode->getChildrenCount())
	{
		CCNode *firstChild = (CCNode *)pNode->getChildren()->objectAtIndex(0);
		THNodeUtil::cleanNode(firstChild);
	}
	
	pNode->removeFromParentAndCleanup(true);
}

// Get is parent contains child
bool THNodeUtil::isChildren(cocos2d::CCNode *pParent, cocos2d::CCNode *pChild)
{
	CCArray *children = pParent->getChildren();
	int l = children->count();
	if(l)
	{
		for(int i = 0; i < l; i++)
		{
			if(children->objectAtIndex(i) == pChild)
			{
				return true;
			}
		}
	}
	
	return false;
}

void THNodeUtil::setAliasTexParameters(cocos2d::CCSprite *pSprite)
{
	pSprite->getTexture()->setAliasTexParameters();
}

void THNodeUtil::setAliasTexParameters(cocos2d::CCMenuItemImage *pItem)
{
	CCSprite *temp;
	
	temp = (CCSprite *)(pItem->getNormalImage());
	if(temp)
	{
		THNodeUtil::setAliasTexParameters(temp);
	}
	
	temp = (CCSprite *)(pItem->getSelectedImage());
	if(temp)
	{
		THNodeUtil::setAliasTexParameters(temp);
	}
	
	temp = (CCSprite *)(pItem->getDisabledImage());
	if(temp)
	{
		THNodeUtil::setAliasTexParameters(temp);
	}
}

void THNodeUtil::setAntiAliasTexParameters(cocos2d::CCSprite *pSprite)
{
	pSprite->getTexture()->setAntiAliasTexParameters();
}

void THNodeUtil::setAntiAliasTexParameters(cocos2d::CCMenuItemImage *pItem)
{
	CCSprite *temp;
	
	temp = (CCSprite *)(pItem->getNormalImage());
	if(temp)
	{
		THNodeUtil::setAntiAliasTexParameters(temp);
	}
	
	temp = (CCSprite *)(pItem->getSelectedImage());
	if(temp)
	{
		THNodeUtil::setAntiAliasTexParameters(temp);
	}
	
	temp = (CCSprite *)(pItem->getDisabledImage());
	if(temp)
	{
		THNodeUtil::setAntiAliasTexParameters(temp);
	}
}

CCSprite *THNodeUtil::capture(cocos2d::CCNode *pTarget)
{
	CCRect bounds = pTarget->boundingBox();
	
	return THNodeUtil::captureWithSize(pTarget, bounds);
}

CCSprite *THNodeUtil::captureWithSize(cocos2d::CCNode *pTarget, const cocos2d::CCRect &tBounds)
{
	CCRenderTexture *texture = CCRenderTexture::create(tBounds.size.width, tBounds.size.height);
	texture->begin();
	pTarget->visit();
	texture->end();
	
	CCSprite *temp = texture->getSprite();
	
	CCSprite *capture = CCSprite::createWithTexture(temp->getTexture());
	capture->setFlipY(true);
	
	
	return capture;
}
