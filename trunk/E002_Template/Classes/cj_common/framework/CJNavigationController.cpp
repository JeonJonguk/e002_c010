//
//  CJNavigationController.cpp
//  SoundPhonics_Package
//
//  Created by j2enty on 13. 7. 8..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#include "CJNavigationController.h"

using namespace cocos2d;


CJNavigationController::CJNavigationController()
{
    parentNode              = NULL;
    naviWinSize             = cocos2d::CCDirector::sharedDirector()->getWinSize();
    winHalfSize             = cocos2d::CCSizeMake(naviWinSize.width/2, naviWinSize.height/2);

    
    btnNavigationIdx.clear();
}

CJNavigationController::~CJNavigationController()
{
    for(int buttonIdx=0; buttonIdx<btnNavigationIdx.size(); buttonIdx++)
    {
        delete btnNavigations[btnNavigationIdx[buttonIdx]];
    }
    
    
    parentNode              = NULL;
    naviWinSize                 = cocos2d::CCSizeZero;
    winHalfSize             = cocos2d::CCSizeZero;
    

    btnNavigationIdx.clear();
}



void CJNavigationController::init(cocos2d::CCNode *pTargetLayer)
{
    parentNode              = pTargetLayer;
    
    
    for(int buttonIdx=0; buttonIdx<btnNavigationIdx.size(); buttonIdx++)
    {
        btnNavigations[btnNavigationIdx[buttonIdx]]     = new CJNavigation::CJNavigationButton();
    }
}


void CJNavigationController::callFunctionWithDelay(cocos2d::SEL_CallFunc aSelector, float fDelayTime)
{
    cocos2d::CCActionManager *manager = cocos2d::CCDirector::sharedDirector()->getActionManager();
    cocos2d::CCCallFunc *callFunc = cocos2d::CCCallFunc::create((cocos2d::CCObject *)this, aSelector);
    cocos2d::CCDelayTime *delay = cocos2d::CCDelayTime::create(fDelayTime);
    cocos2d::CCSequence *action = cocos2d::CCSequence::create(delay, callFunc, NULL);
    
    manager->addAction(CCSequence::create(action,NULL), (cocos2d::CCNode *)this, false);
}








void CJNavigationController::_showNavigation()
{
    for(int buttonIdx=0; buttonIdx<btnNavigationIdx.size(); buttonIdx++)
    {
        this->setVisibleButton(true, btnNavigationIdx[buttonIdx]);
    }
}

void CJNavigationController::_hideNavigation()
{
    for(int buttonIdx=0; buttonIdx<btnNavigationIdx.size(); buttonIdx++)
    {
        this->setVisibleButton(false, btnNavigationIdx[buttonIdx]);
    }
}

void CJNavigationController::_setEnableNavigation()
{
    for(int buttonIdx=0; buttonIdx<btnNavigationIdx.size(); buttonIdx++)
    {
        this->setEnableButton(true, btnNavigationIdx[buttonIdx]);
    }
}

void CJNavigationController::_setDisableNavigation()
{
    for(int buttonIdx=0; buttonIdx<btnNavigationIdx.size(); buttonIdx++)
    {
        this->setEnableButton(false, btnNavigationIdx[buttonIdx]);
    }
}

void CJNavigationController::_setVisibleNavigation()
{
    for(int buttonIdx=0; buttonIdx<btnNavigationIdx.size(); buttonIdx++)
    {
        this->setVisibleButton(true, btnNavigationIdx[buttonIdx]);
    }
}

void CJNavigationController::_setInvisibleNavigation()
{
    for(int buttonIdx=0; buttonIdx<btnNavigationIdx.size(); buttonIdx++)
    {
        this->setVisibleButton(false, btnNavigationIdx[buttonIdx]);
    }
}

void CJNavigationController::showNavigation(float fDelayTime)
{
    if (fDelayTime == 0) {
        _showNavigation();
    }else{
        this->callFunctionWithDelay(callfunc_selector(CJNavigationController::_showNavigation), fDelayTime);
    }
}

void CJNavigationController::hideNavigation(float fDelayTime)
{
    if (fDelayTime == 0) {
        _hideNavigation();
    }else{
        this->callFunctionWithDelay(callfunc_selector(CJNavigationController::_hideNavigation), fDelayTime);
    }
}

void CJNavigationController::setEnableNavigation(bool bIsEnable, float fDelayTime)
{
    if(true == bIsEnable)
    {
        this->callFunctionWithDelay(callfunc_selector(CJNavigationController::_setEnableNavigation), fDelayTime);
    }
    else
    {
        this->callFunctionWithDelay(callfunc_selector(CJNavigationController::_setDisableNavigation), fDelayTime);
    }
}

void CJNavigationController::setVisibleNavigation(bool bIsVisible, float fDelayTime)
{
    if(true == bIsVisible)
    {
        this->callFunctionWithDelay(callfunc_selector(CJNavigationController::_setVisibleNavigation), fDelayTime);
    }
    else
    {
        this->callFunctionWithDelay(callfunc_selector(CJNavigationController::_setInvisibleNavigation), fDelayTime);
    }
}

void CJNavigationController::setEnableButton(bool bIsEnable, int eNavigationButtonType)
{
    if(NULL != btnNavigations[eNavigationButtonType]->menuItemImage)
    {
        btnNavigations[eNavigationButtonType]->menuItemImage->setEnabled(bIsEnable);
    }
    else if(NULL != btnNavigations[eNavigationButtonType]->menuItemSprite)
    {
        btnNavigations[eNavigationButtonType]->menuItemSprite->setEnabled(bIsEnable);
    }
}

void CJNavigationController::setEnableButtons(bool bIsEnable, int eNavigationButtonType, ...)
{
    va_list args;
    va_start(args, eNavigationButtonType);
    while(eNavigationButtonType != -1)
    {
        this->setEnableButton(bIsEnable, eNavigationButtonType);
        
        eNavigationButtonType = va_arg(args, int);
        if(eNavigationButtonType == -1)
        {
            break ;
        }
    }
    va_end(args);
}

void CJNavigationController::setVisibleButton(bool bIsVisible, int eNavigationButtonType)
{
    if(NULL != btnNavigations[eNavigationButtonType]->menuItemImage)
    {
        btnNavigations[eNavigationButtonType]->menuItemImage->setVisible(bIsVisible);
    }
    else if(NULL != btnNavigations[eNavigationButtonType]->menuItemSprite)
    {
        btnNavigations[eNavigationButtonType]->menuItemSprite->setVisible(bIsVisible);
    }
}

void CJNavigationController::setVisibleButtons(bool bIsVisible, int eNavigationButtonType, ...)
{
    va_list args;
    va_start(args, eNavigationButtonType);
    while(eNavigationButtonType != -1)
    {
        this->setVisibleButton(bIsVisible, eNavigationButtonType);
        
        eNavigationButtonType = va_arg(args, int);
        if(eNavigationButtonType == -1)
        {
            break ;
        }
    }
    va_end(args);
}
