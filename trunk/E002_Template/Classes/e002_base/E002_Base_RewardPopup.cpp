//
//  E002_Base_RewardPopup.cpp
//  E002_Template
//
//  Created by Jeong.YJ on 2014. 4. 1..
//
//

#include "E002_Base_RewardPopup.h"

enum
{
    kTagPopupBG = 890,
    kTagRewardItem,
    kTagDim,
};

E002_Base_RewardPopup::E002_Base_RewardPopup()
{
    m_psdDictionary = new CCDictionary();
    mItems = new std::vector<const char*>();
    mShowRewardPopup = false;
    mShowMotionComplete = false;
    mSndManager = new E002_Base_SoundManager();
}

E002_Base_RewardPopup::~E002_Base_RewardPopup()
{
    
}

bool E002_Base_RewardPopup::init(int pageNumber)
{
    mPageNumber = pageNumber;
    
    if (CJPopup::initWithColor(ccc4(0, 0, 0, 0))) {
        return true;
    }
    
    return false;
}

void E002_Base_RewardPopup::onEnter()
{
    CJPopup::onEnter();
    
    CJPsdParser::parseToPsdJSON(getContentID("_reward.json"), &m_psdDictionary);

    mGiftBox = CJSprite::createWithFullPath(CJUtils::getInstance()->getContentID().append("_common_img_btn_reward.png").c_str());
    mGiftBox->setPosition(POS_BOTTOMLEFT);
    addChild(mGiftBox, kDepth10_guide);
}

void E002_Base_RewardPopup::onExit()
{
    CJPopup::onExit();
}


bool E002_Base_RewardPopup::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
    if(mShowRewardPopup && mShowMotionComplete)
    {
        hideRewardPopup();
    }
    else if(mShowRewardPopup && !mShowMotionComplete)
    {
        sendRewardPopupCompleteMsg();
    }
    
    return true;
}
void E002_Base_RewardPopup::setRewardItems(const char* key, ...)
{
    va_list args;
    va_start(args,key);
    
    while (key != NULL) {
        
        mItems->push_back(key);
        
        key = va_arg(args, const char*);
    }
    
    va_end(args);
}

void E002_Base_RewardPopup::showRewardItem(int index)
{
    mSndManager->playRewardCreateSfxSnd();
    
    std::string resource = getFilePath("img", getContentID(CJUtils::getStringFormatInteger("_reward_piece_%02d_get", index)).append(".png"));
    CCLog("show Reward Item = %s", resource.c_str());
    CJSprite *item = CJSprite::create(resource.c_str());
    item->setPosition(winCenter);
    addChild(item, kDepth9_navigations, kTagRewardItem);
    
    item->setScale(0);
    
    showGetRewardParticle();
    
    ccBezierConfig bezier;
    bezier.controlPoint_1 = ccp(300, item->getPositionY());
    bezier.controlPoint_2 = ccp(49, 230);
    bezier.endPosition = POS_BOTTOMLEFT;
    
    CCActionInterval*  bezierA = CCBezierTo::create(0.8f, bezier);
    CCActionInterval*  bezierE = CCEaseSineInOut::create(bezierA);

    
    item->runAction(CCSequence::create(CCEaseElasticOut::create(CCScaleTo::create(1.0f, 1.0)),
                                       CCCallFunc::create(this, callfunc_selector(E002_Base_RewardPopup::showMoveRewardParticle)),
                                       CCScaleTo::create(0.3f, 1.2),
                                       CCSpawn::create(CCRotateTo::create(0.8, -45),
                                                       bezierE,
                                                       CCEaseSineOut::create(CCScaleTo::create(0.8, 0.1)),
                                                       NULL),
                                        CCCallFunc::create(this, callfunc_selector(E002_Base_RewardPopup::playEffectGetItem)),
                                       CCCallFunc::create(this, callfunc_selector(E002_Base_RewardPopup::showGiftBoxEffect)),
                                       CCDelayTime::create(1.5f),
                                       CCCallFunc::create(this, callfunc_selector(E002_Base_RewardPopup::sendRewardItemCompleteMsg)),
                                       CCCallFuncN::create(this, callfuncN_selector(CJLayer::removeChild)),
                                       NULL));
    
}

void E002_Base_RewardPopup::playEffectGetItem()
{
    playCommonEffect("e002_common_sfx_box_02.mp3");
}


void E002_Base_RewardPopup::showRewardBox(int index)
{
    addDimBackgound();
    
    showGiftBoxEffect();
    
    mShowRewardPopup = true;
    mShowMotionComplete = false;
    
    CJSprite *bg = CJPsdParser::getPsdSprite(getContentID("_reward_popup_bg"), m_psdDictionary);
    addChild(bg, kDepth7_popup, kTagPopupBG);
    
    for (int i = 0; i < index; i++)
    {
        CJSprite *item = CJPsdParser::getPsdSprite(getContentID(CJUtils::getStringFormatInteger("_reward_piece_%02d_popup", i)), m_psdDictionary);
        bg->addChildIgnoreParent(item, kDepth7_popup+1);
    }
    
    bg->setPosition(POS_BOTTOMLEFT);
    bg->setScale(0);
    
    CCActionInterval* scaleA1 = CCScaleTo::create(0.3f, 1.0f);
    CCActionInterval* scaleE1 = CCEaseSineOut::create(scaleA1);
    
    CCFiniteTimeAction* seq_scale = CCSequence::create(
                                                       //CCDelayTime::create(0.1f),
                                                       scaleE1,
                                                       NULL);
    
    ccBezierConfig bezier;
    bezier.controlPoint_1 = ccp(49, 230);
    bezier.controlPoint_2 = ccp(300, winCenter.y);
    bezier.endPosition = winCenter;

    CCActionInterval*  bezierA = CCBezierTo::create(0.3f, bezier);
    CCActionInterval*  bezierE = CCEaseSineOut::create(bezierA);
    
    
    
    CCActionInterval* spawn = CCSpawn::create(seq_scale,
                                              bezierE,
                                              NULL);
    
    bg->runAction(CCSequence::create(spawn,
                                     //CCScaleTo::create(0.1, 1.0),
                                     CCCallFunc::create(this, callfunc_selector(E002_Base_RewardPopup::setShowMotionComplete)),
                                     NULL));

}

void E002_Base_RewardPopup::setShowMotionComplete()
{
    mShowMotionComplete = true;
}

void E002_Base_RewardPopup::hideRewardPopup()
{
    mShowMotionComplete = false;
    
    CJSprite *bg = (CJSprite*)getChildByTag(kTagPopupBG);
    
    CCActionInterval* scaleA1 = CCEaseSineInOut::create(CCScaleTo::create(0.3f, 0));
    
    ccBezierConfig bezier;
    bezier.controlPoint_1 = ccp(300, winCenter.y);
    bezier.controlPoint_2 = ccp(49, 230);
    bezier.endPosition = POS_BOTTOMLEFT;
    
    CCActionInterval*  bezierA = CCBezierTo::create(0.3f, bezier);
    CCActionInterval*  bezierE = CCEaseSineInOut::create(bezierA);
    
    
    
    CCActionInterval* spawn = CCSpawn::create(scaleA1,
                                              bezierE,
                                              NULL);
    
    bg->runAction(CCSequence::create(CCEaseSineOut::create(CCScaleTo::create(0.2, 1.1)),
                                     //CCDelayTime::create(0.1),
                                     spawn,
                                     CCCallFunc::create(this, callfunc_selector(E002_Base_RewardPopup::showGiftBoxEffect)),
                                     CCCallFunc::create(this, callfunc_selector(E002_Base_RewardPopup::removeDimBackground)),
                                     CCDelayTime::create(1.2f),
                                     CCCallFunc::create(this, callfunc_selector(E002_Base_RewardPopup::setShowMotionComplete)),
                                     CCCallFunc::create(this, callfunc_selector(E002_Base_RewardPopup::sendRewardPopupCompleteMsg)),
                                     NULL));

}

void E002_Base_RewardPopup::sendRewardItemCompleteMsg()
{
    CCNotificationCenter::sharedNotificationCenter()->postNotification(CJNOTIFICATION_REWARD_ITEM_COMPLETE_CALL);
}

void E002_Base_RewardPopup::sendRewardPopupCompleteMsg()
{
    CCNotificationCenter::sharedNotificationCenter()->postNotification(CJNOTIFICATION_REWARD_POPUP_COMPLETE_CALL);
}

std::string E002_Base_RewardPopup::getContentID(std::string resource)
{
    std::string page;
    
    if(mPageNumber == P100)
    {
        page = "_p100";
    }
    else if(mPageNumber == P200)
    {
        page = "_p200";
    }
    else if(mPageNumber == P300)
    {
        page = "_p300";
    }
    
    page.append(resource);
    
    return CJUtils::getInstance()->getContentID().append(page);
}

void E002_Base_RewardPopup::showGetRewardParticle()
{
    CCParticleSystemQuad * particle = CCParticleSystemQuad::create(getCommonFilePath("img","e002_common_reward_01.plist").c_str());
    addChild(particle, kDepth7_popup+1);
    particle->setAutoRemoveOnFinish(true);
}

void E002_Base_RewardPopup::showMoveRewardParticle()
{
    CCSprite* item = (CCSprite*)getChildByTag(kTagRewardItem);
    
    CCParticleSystemQuad * particle = CCParticleSystemQuad::create(getCommonFilePath("img","e002_common_reward_02.plist").c_str());
    addChild(particle, kDepth9_navigations-1);
    particle->setPosition(ccp(item->getPositionX(), item->getPositionY()));
    particle->setAutoRemoveOnFinish(true);
    particle->runAction(CCSequence::create(CCDelayTime::create(0.1f),
                                                CCCallFunc::create(this, callfunc_selector(E002_Base_RewardPopup::showMoveRewardParticle)),
                                                NULL));
    
}

void E002_Base_RewardPopup::showGiftBoxEffect()
{
    mGiftBox->runAction(CCSequence::create(CCEaseSineOut::create(CCScaleTo::create(0.17, 1.3)),
                                           CCEaseSineIn::create(CCScaleTo::create(0.17, 0.9)),
                                           CCEaseSineOut::create(CCScaleTo::create(0.15, 1.1)),
                                           CCEaseSineIn::create(CCScaleTo::create(0.15, 0.95)),
                                           CCEaseSineOut::create(CCScaleTo::create(0.12, 1.05)),
                                           CCEaseSineIn::create(CCScaleTo::create(0.12, 1)),
                                           NULL));
}

void E002_Base_RewardPopup::addDimBackgound()
{
    CCSprite* m_Dim =  CCSprite::create();
	m_Dim->setTextureRect(CCRectMake(0, 0, winSize.width, winSize.height));
	m_Dim->setColor(ccBLACK);
	m_Dim->setOpacity(210);
	m_Dim->setAnchorPoint(CCPointZero);
	m_Dim->setPosition(CCPointZero);
	m_Dim->setTag(kTagDim);
	addChild(m_Dim);
}

void E002_Base_RewardPopup::removeDimBackground()
{
    removeChildByTag(kTagDim);
}