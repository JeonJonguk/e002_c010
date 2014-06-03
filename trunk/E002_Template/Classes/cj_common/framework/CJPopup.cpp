//
//  E001_Base_Popup.cpp
//  S001-C130
//
//  Created by Lee.YJ on 13. 2. 18..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#include "CJPopup.h"
#include "CJMultimedia.h"

using namespace CJPopupDef;


////////////////////////////////////////////////////
//
// Popup bases
//
////////////////////////////////////////////////////

CJPopup::CJPopup()
{
    _imgBackground = NULL;
    _btnClose = new Button();
    
    _soundEffectIds.clear();
    _touchDispatchers.clear();
    
    winSize = CCDirector::sharedDirector()->getWinSize();
}

CJPopup::~CJPopup()
{
    if(_imgBackground != NULL)
    {
        _imgBackground->release();
        _imgBackground = NULL;
    }
    
    if(_btnClose->buttons.size() != 0)
    {
        if(_btnClose->buttons[0] != NULL)
        {
            this->removeChild(_btnClose->buttons[0]);
        }
        
        _btnClose->targets.clear();
        _btnClose->selectors.clear();
        _btnClose->buttonSounds.clear();
    }
    
    delete _btnClose;
    
    _touchDispatchers.clear();
    _soundEffectIds.clear();
}

bool CJPopup::init()
{
    return this->initWithColor(ccc4(0, 0, 0, 190));
}

bool CJPopup::initWithColor(const ccColor4B &color)
{
    if(CCLayerColor::initWithColor(color) == false)
    {
        return false;
    }
    
    this->setPosition(CCPointMake(0, 0));
    this->setVisible(false);
    return true;
}

void CJPopup::onExit()
{
    CCLayerColor::onExit();
    
    if(this->isVisible() == true)
    {
        this->hidePopup();
    }
}


void CJPopup::showPopup(CCLayer *pLayer, std::string strPopupSound)
{
    this->retain();
    
    _parentClass = pLayer;
    _parentClass->retain();

    
//    this->setOpacity(0);
//    for (int i = 0; i < getChildrenCount(); i++) {
//        ((CCNode*)getChildren()->objectAtIndex(i))->runAction(CCFadeOut::create(0));
//    }
    
    this->_setAllNodeTouchEnable(_parentClass, false);
    this->setVisible(true);
    
//    this->runAction(CCFadeTo::create(0.3, 190));
//    for (int i = 0; i < getChildrenCount(); i++) {
//        ((CCNode*)getChildren()->objectAtIndex(i))->runAction(CCFadeIn::create(0.3));
//    }
    
    this->playSoundEffect(strPopupSound);
}

void CJPopup::hidePopup()
{
    this->_setAllNodeTouchEnable(_parentClass, true);
    this->setVisible(false);
    
    this->stopAllSoundEffects();
    _parentClass->release();
    
    this->release();
}

void CJPopup::_setAllNodeTouchEnable(cocos2d::CCNode *pNode, bool bIsTouchable)
{
    CCNode *superNode = this->_findSuperNode(pNode);
    
    this->_setMenuEnable(superNode, bIsTouchable);
    this->_setDispatcherEnable(bIsTouchable);
}

CCNode* CJPopup::_findSuperNode(CCNode *pNode)
{
    CCNode *superNode = pNode;
    while(true)
    {
        if(superNode->getParent() != NULL)
        {
            superNode = superNode->getParent();
        }
        else
        {
            return superNode;
        }
    }
}

void CJPopup::_setMenuEnable(cocos2d::CCNode *pNode, bool bIsTouchable)
{
    for(int childIdx=0; childIdx<pNode->getChildren()->count(); childIdx++)
    {
        CCNode *child = (CCNode *)pNode->getChildren()->objectAtIndex(childIdx);
        
        // is This popup instance?
        if(dynamic_cast<CJPopup *>(child))
        {
            continue ;
        }
        
        // is CCMenu instance?
        if(dynamic_cast<CCMenu *>(child))
        {
            CCMenu *menu = (CCMenu *)child;
            menu->setTouchEnabled(bIsTouchable);
            
            continue ;
        }
        
        // is CCLayer instance?
        if(dynamic_cast<CCLayer *>(child))
        {
            // is added touch dispatcher item?
            if(CCDirector::sharedDirector()->getTouchDispatcher()->findHandler((CCLayer *)child) != NULL)
            {
                // add touch dispatcher item.
                _touchDispatchers.push_back((CCLayer *)child);
            }
        }
        
        if(child->getChildrenCount() > 0)
        {
            this->_setMenuEnable(child, bIsTouchable);
        }
    }
}

void CJPopup::_setDispatcherEnable(bool bIsTouchable)
{
    // added touch dispatcher item iteration
    for(int dispathcherIdx=0; dispathcherIdx<_touchDispatchers.size(); dispathcherIdx++)
    {
        // is touch enable true?
        if(bIsTouchable == true)
        {
            // add touch dispatcher item by added touch dispatcher item instance.
            if(CCDirector::sharedDirector()->getTouchDispatcher()->findHandler(_touchDispatchers[dispathcherIdx]) == NULL){
                CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(_touchDispatchers[dispathcherIdx], 0, true);
            }
            CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
        }
        // is touch enable false?
        else
        {
            // remove touch dispatcher item by added touch dispatcher item instance.
            CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(_touchDispatchers[dispathcherIdx]);
            
            if(CCDirector::sharedDirector()->getTouchDispatcher()->findHandler(this) == NULL){
                CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
            }
        }
    }
}





////////////////////////////////////////////////////
//
// Sound
//
////////////////////////////////////////////////////

void CJPopup::playSoundEffect(std::string strSoundResourceName)
{
    if(strSoundResourceName.empty() == false)
    {
        _soundEffectIds.push_back(CJMultimedia::getInstance()->playEffect(strSoundResourceName.c_str()));
    }
}

void CJPopup::playSoundButtonEffect(std::string strSoundResourceName)
{
    if(strSoundResourceName.empty() == false)
    {
        CJMultimedia::getInstance()->playEffect(strSoundResourceName.c_str());
    }
}

void CJPopup::stopAllSoundEffects()
{
    for(int soundEffectIdx=0; soundEffectIdx<_soundEffectIds.size(); soundEffectIdx++)
    {
        CJMultimedia::getInstance()->stopEffect(_soundEffectIds[soundEffectIdx]);
    }
}

void CJPopup::playSoundNarration(std::string strSoundResourceName)
{
    CJMultimedia::getInstance()->playNarration(strSoundResourceName, false);
}

void CJPopup::stopSoundNarration()
{
    CJMultimedia::getInstance()->stopAllNarration();
}





////////////////////////////////////////////////////
//
// Popup background
//
////////////////////////////////////////////////////

void CJPopup::_setBackground(CCSprite *pSprite)
{
    if(_imgBackground != NULL)
    {
        if(_imgBackground->getParent() != NULL)
        {
            this->removeChild(_imgBackground, true);
        }
        
        _imgBackground->release();
    }
    
    _imgBackground = pSprite;
    _imgBackground->retain();
    
    this->addChild(_imgBackground, CJPopupDef::ePopupDepth_BackgroundImage);
}



void CJPopup::setBackground(CCSprite *pSprite)
{
    if(pSprite != NULL)
    {
        this->_setBackground(pSprite);
    }
}

void CJPopup::setBackground(std::string strImageName)
{
    CCSprite *tempSprite = CCSprite::create(strImageName.c_str());
    tempSprite->setPosition(CCPointMake(winSize.width/2, winSize.height/2));
    
    this->setBackground(tempSprite);
}

void CJPopup::setBackgroundPosition(CCPoint aPoint)
{
    if(_imgBackground != NULL)
    {
        _imgBackground->setPosition(aPoint);
    }
}










////////////////////////////////////////////////////
//
// Close button
//
////////////////////////////////////////////////////

void CJPopup::_addCloseButton(CCPoint aButtonPosition, CCSprite *pNormalSprite, CCSprite *pSelectSprite)
{
    if(pNormalSprite != NULL && pSelectSprite != NULL)
    {
        CCMenuItemSprite *menuItem = CCMenuItemSprite::create(pNormalSprite, pSelectSprite, this, menu_selector(CJPopup::_onTouchedCloseButton));
        _btnClose->buttons.push_back(CCMenu::createWithItem(menuItem));
        _btnClose->buttons[0]->setPosition(aButtonPosition);
        
        this->addChild(_btnClose->buttons[0], CJPopupDef::ePopupDepth_Buttons);
    }
}

void CJPopup::_onTouchedCloseButton()
{
    _btnClose->buttons[0]->setTouchEnabled(false);
    this->playSoundButtonEffect(_btnClose->buttonSounds[0]);
    
    CCFiniteTimeAction *action = CCSequence::create(CCDelayTime::create(_btnClose->delayTime),
                                                    CCCallFunc::create(this, callfunc_selector(CJPopup::hidePopup)),
                                                    CCCallFunc::create(_btnClose->targets[0], _btnClose->selectors[0]),
                                                    NULL);
    this->runAction(action);
}




void CJPopup::addCloseButton(std::string strNormalButtonImageName, std::string strSelectButtonImageName, std::string strButtonEffectName,
                                     CCPoint aButtonPosition, CCObject *pCallbackTarget, SEL_CallFunc aCallbackSelector,
                                     float fCallbackDelayTime)
{
    _btnClose->targets.clear();
    _btnClose->selectors.clear();
    _btnClose->buttonSounds.clear();
    
    _btnClose->targets.push_back(pCallbackTarget);
    _btnClose->selectors.push_back(aCallbackSelector);
    _btnClose->delayTime = fCallbackDelayTime;
    _btnClose->buttonSounds.push_back(strButtonEffectName);
    
    this->_addCloseButton(aButtonPosition, CCSprite::create(strNormalButtonImageName.c_str()), CCSprite::create(strSelectButtonImageName.c_str()));
}

void CJPopup::addCloseButton(CCSprite *pNormalSprite, CCSprite *pSelectSprite, std::string strButtonEffectName,
                                     CCPoint aButtonPosition, CCObject *pCallbackTarget, SEL_CallFunc aCallbackSelector, 
                                     float fCallbackDelayTime)
{
    _btnClose->targets.clear();
    _btnClose->selectors.clear();
    _btnClose->buttonSounds.clear();
    
    _btnClose->targets.push_back(pCallbackTarget);
    _btnClose->selectors.push_back(aCallbackSelector);
    _btnClose->delayTime = fCallbackDelayTime;
    _btnClose->buttonSounds.push_back(strButtonEffectName);
    
    this->_addCloseButton(aButtonPosition, pNormalSprite, pSelectSprite);
}

void CJPopup::setCloseButtonPosition(CCPoint aPoint)
{
    if(_btnClose->buttons[0] != NULL)
    {
        _btnClose->buttons[0]->setPosition(aPoint);
    }
}

void CJPopup::setCloseButtonSelector(CCObject *pCallbackTarget, SEL_CallFunc aCallbackSelector)
{
    _btnClose->targets.clear();
    _btnClose->selectors.clear();
    
    _btnClose->targets.push_back(pCallbackTarget);
    _btnClose->selectors.push_back(aCallbackSelector);
}

void CJPopup::setCloseButtonEffectSound(std::string strButtonEffectName)
{
    _btnClose->buttonSounds.clear();
    
    _btnClose->buttonSounds.pop_back();
    _btnClose->buttonSounds.push_back(strButtonEffectName);
}


