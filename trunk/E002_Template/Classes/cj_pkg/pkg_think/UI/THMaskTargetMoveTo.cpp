//
//  THMaskTargetMoveTo.cpp
//  PackageApp
//
//  Created by pureye4u BX on 12. 7. 5..
//  Copyright CJ Educations 2012. All rights reserved.
//

#include "THMaskTargetMoveTo.h"
#include "THMask.h"

using namespace cocos2d;

THMaskTargetMoveTo* THMaskTargetMoveTo::actionWithDuration(float duration, const CCPoint& position)
{
	THMaskTargetMoveTo *pMoveTo = new THMaskTargetMoveTo();
	pMoveTo->initWithDuration(duration, position);
	pMoveTo->autorelease();
	
	return pMoveTo;
}

void THMaskTargetMoveTo::startWithTarget(CCNode *target)
{
	CCActionInterval::startWithTarget(target);
	m_startPosition = ((THMask *)target)->getTargetPosition();
    
    /*
     * cocos2dx v2.1.4 CCMoveTo, CCMoveBy Inherit struct change.
     * m_delta variable removed.
     *
     * m_delta = ccpSub(m_endPosition, m_startPosition);
     */
    m_positionDelta = ccpSub(m_endPosition, m_startPosition);
}

void THMaskTargetMoveTo::update(float time)
{
	if(m_pTarget)
	{
        /*
         * cocos2dx v2.1.4 CCMoveTo, CCMoveBy Inherit struct change.
         * m_delta variable removed.
         *
         * ((THMask *)m_pTarget)->setTargetPosition(ccp(m_startPosition.x + m_delta.x * time, m_startPosition.y + m_delta.y * time));
         */
		((THMask *)m_pTarget)->setTargetPosition(ccp(m_startPosition.x + m_positionDelta.x * time, m_startPosition.y + m_positionDelta.y * time));
	}
}

CCObject* THMaskTargetMoveTo::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	CCMoveTo* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (THMaskTargetMoveTo*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new THMaskTargetMoveTo();
		pZone = pNewZone = new CCZone(pCopy);
	}
	
	CCActionInterval::copyWithZone(pZone);
	
	pCopy->initWithDuration(m_fDuration, m_endPosition);
	
	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}