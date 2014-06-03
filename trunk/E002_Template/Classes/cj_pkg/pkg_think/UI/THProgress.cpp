//
//  THProgress.cpp
//  PackageApp
//
//  Created by pureye4u BX on 12. 8. 2..
//  Copyright CJ Educations 2012. All rights reserved.
//

#include "THProgress.h"

using namespace cocos2d;

THProgress::THProgress()
{
	
}

THProgress::~THProgress()
{
	this->removeAllChildrenWithCleanup(true);
}

bool THProgress::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	
	// Initialize
	CCSprite *bg = CCSprite::create("BookShelf/popup/popup_book_waiting_frame.png");
	bg->getTexture()->setAliasTexParameters();
	this->addChild(bg);
	
	CCPoint p = CCPointMake(0, 20);
	
	CCSprite *loading00 = CCSprite::create("BookShelf/popup/loading_00.png");
	loading00->getTexture()->setAliasTexParameters();
	loading00->setOpacity(127.0f);
	loading00->setPosition(p);
	this->addChild(loading00);
	loading00->runAction(CCRepeatForever::create((CCActionInterval *)CCSequence::create(
																								   CCFadeTo::create(1.0f, 255.0f),
																								   CCFadeTo::create(1.0f, 127.0f),
																								   NULL)));
	
	CCSprite *loading01 = CCSprite::create("BookShelf/popup/loading_01.png");
	loading01->setTag(1);
	loading01->getTexture()->setAliasTexParameters();
//	loading01->setOpacity(127.0f);
	loading01->setPosition(p);
	this->addChild(loading01);
	
	CCSprite *loading02 = CCSprite::create("BookShelf/popup/loading_02.png");
	loading02->setTag(2);
	loading02->getTexture()->setAliasTexParameters();
	loading02->setOpacity(127.0f);
	loading02->setPosition(p);
	this->addChild(loading02);
	
	CCSprite *loading03 = CCSprite::create("BookShelf/popup/loading_03.png");
	loading03->setTag(3);
	loading03->getTexture()->setAliasTexParameters();
	loading03->setOpacity(127.0f);
	loading03->setPosition(p);
	this->addChild(loading03);
	
	CCSprite *loading04 = CCSprite::create("BookShelf/popup/loading_04.png");
	loading04->setTag(4);
	loading04->getTexture()->setAliasTexParameters();
	loading04->setOpacity(127.0f);
	loading04->setPosition(p);
	this->addChild(loading04);
	
	CCSprite *loading05 = CCSprite::create("BookShelf/popup/loading_05.png");
	loading05->setTag(5);
	loading05->getTexture()->setAliasTexParameters();
	loading05->setOpacity(127.0f);
	loading05->setPosition(p);
	this->addChild(loading05);
	
	CCSprite *loading06 = CCSprite::create("BookShelf/popup/loading_06.png");
	loading06->setTag(6);
	loading06->getTexture()->setAliasTexParameters();
	loading06->setOpacity(127.0f);
	loading06->setPosition(p);
	this->addChild(loading06);
	
	CCSprite *loading07 = CCSprite::create("BookShelf/popup/loading_07.png");
	loading07->setTag(7);
	loading07->getTexture()->setAliasTexParameters();
	loading07->setOpacity(127.0f);
	loading07->setPosition(p);
	this->addChild(loading07);
	
	CCSprite *loading08 = CCSprite::create("BookShelf/popup/loading_08.png");
	loading08->setTag(8);
	loading08->getTexture()->setAliasTexParameters();
	loading08->setOpacity(127.0f);
	loading08->setPosition(p);
	this->addChild(loading08);
	
	m_currentProgress = 1;
	
	/*
	loading01->runAction(CCRepeatForever::actionWithAction((CCActionInterval *)CCSequence::actions(
//																								   CCDelayTime::actionWithDuration(2.0f),
																								   CCFadeTo::actionWithDuration(0.25f, 127.0f),
																								   CCDelayTime::actionWithDuration(1.5f),
																								   CCFadeTo::actionWithDuration(0.25f, 255.0f),
																								   CCDelayTime::actionWithDuration(0.25f),
																								   NULL)));
	
	loading02->runAction(CCRepeatForever::actionWithAction((CCActionInterval *)CCSequence::actions(
																								   CCDelayTime::actionWithDuration(0.25f),
																								   CCFadeTo::actionWithDuration(0.25f, 127.0f),
																								   CCDelayTime::actionWithDuration(1.5f),
//																								   CCDelayTime::actionWithDuration(2.0f),
																								   CCFadeTo::actionWithDuration(0.25f, 255.0f),
																								   NULL)));
	
	loading03->runAction(CCRepeatForever::actionWithAction((CCActionInterval *)CCSequence::actions(
																								   CCDelayTime::actionWithDuration(0.25f),
																								   CCFadeTo::actionWithDuration(0.25f, 255.0f),
																								   CCDelayTime::actionWithDuration(0.25f),
//																								   CCDelayTime::actionWithDuration(2.0f),
																								   CCFadeTo::actionWithDuration(0.25f, 127.0f),
																								   CCDelayTime::actionWithDuration(1.25f),
																								   NULL)));
	
	loading04->runAction(CCRepeatForever::actionWithAction((CCActionInterval *)CCSequence::actions(
																								   CCDelayTime::actionWithDuration(0.5f),
																								   CCFadeTo::actionWithDuration(0.25f, 255.0f),
																								   CCDelayTime::actionWithDuration(0.25f),
//																								   CCDelayTime::actionWithDuration(2.0f),
																								   CCFadeTo::actionWithDuration(0.25f, 127.0f),
																								   CCDelayTime::actionWithDuration(1.0f),
																								   NULL)));
	
	loading05->runAction(CCRepeatForever::actionWithAction((CCActionInterval *)CCSequence::actions(
																								   CCDelayTime::actionWithDuration(0.75f),
																								   CCFadeTo::actionWithDuration(0.25f, 255.0f),
																								   CCDelayTime::actionWithDuration(0.25f),
//																								   CCDelayTime::actionWithDuration(2.0f),
																								   CCFadeTo::actionWithDuration(0.25f, 127.0f),
																								   CCDelayTime::actionWithDuration(0.75f),
																								   NULL)));
	
	loading06->runAction(CCRepeatForever::actionWithAction((CCActionInterval *)CCSequence::actions(
																								   CCDelayTime::actionWithDuration(1.0f),
																								   CCFadeTo::actionWithDuration(0.25f, 255.0f),
																								   CCDelayTime::actionWithDuration(0.25f),
//																								   CCDelayTime::actionWithDuration(2.0f),
																								   CCFadeTo::actionWithDuration(0.25f, 127.0f),
																								   CCDelayTime::actionWithDuration(0.5f),
																								   NULL)));
	
	loading07->runAction(CCRepeatForever::actionWithAction((CCActionInterval *)CCSequence::actions(
																								   CCDelayTime::actionWithDuration(1.25f),
																								   CCFadeTo::actionWithDuration(0.25f, 255.0f),
																								   CCDelayTime::actionWithDuration(0.25f),
																								   CCFadeTo::actionWithDuration(0.25f, 127.0f),
																								   CCDelayTime::actionWithDuration(0.25f),
																								   NULL)));
	
	loading08->runAction(CCRepeatForever::actionWithAction((CCActionInterval *)CCSequence::actions(
																								   CCDelayTime::actionWithDuration(1.5f),
																								   CCFadeTo::actionWithDuration(0.25f, 255.0f),
																								   CCDelayTime::actionWithDuration(0.25f),
																								   CCFadeTo::actionWithDuration(0.25f, 127.0f),
																								   NULL)));
	*/
	CCLabelTTF *label = CCLabelTTF::create("Waiting", "HelveticaNeue", 16, CCSizeZero, kCCTextAlignmentCenter);
	label->getTexture()->setAliasTexParameters();
	label->setPosition(CCPointMake(0, -60));
	this->addChild(label);
	
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(THProgress::hndUpdateProgress), this, 0.2, false);
	
//	CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(ResourceUtils::hndDownloadEnded), this, 0.0, false);
	
	return true;
}

void THProgress::hndUpdateProgress()
{
//	CCLog("%d", m_currentProgress);
	CCSprite *before = (CCSprite *)this->getChildByTag(m_currentProgress);
	if(before)
	{
		before->runAction(CCSequence::create(
											  CCFadeTo::create(0.25f, 127.0f),
											  NULL));
	}
	
	m_currentProgress++;
	if(m_currentProgress > 8)
	{
		m_currentProgress = 1;
	}
	
	CCSprite *after = (CCSprite *)this->getChildByTag(m_currentProgress);
	if(after)
	{
		after->runAction(CCSequence::create(
											  CCFadeTo::create(0.25f, 255.0f),
											  NULL));
	}
}


