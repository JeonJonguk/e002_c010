//
//  E002_Base_Character.cpp
//  E002_Template
//
//  Created by Jeong.YJ on 2014. 2. 17..
//
//

#include "CJAnimationCharacter.h"


CJAnimationCharacter::CJAnimationCharacter(CJAnimationManager *manager, std::string dataKey)
{
    mAnimationManager = manager;
    
    mDataKey = "";
    mLoopingKey = "";
    
    
    mDataKey = dataKey;
    
    mSuccessKeys = new std::vector<const char*>();
    mFailKeys = new std::vector<const char*>();
    
    mSuccessCount = 0;
    mFailCount = 0;
    mZorder = 50;
}

CJAnimationCharacter::~CJAnimationCharacter()
{
    delete mLoopingKey;
    delete mSuccessKeys;
    delete mFailKeys;
}

void CJAnimationCharacter::setFails(const char* key, ...)
{
    va_list args;
    va_start(args,key);
    
    while (key != NULL) {
        
        mFailKeys->push_back(key);
        
        key = va_arg(args, const char*);
    }
    
    va_end(args);
}

void CJAnimationCharacter::setSuccess(const char* key, ...)
{
    va_list args;
    va_start(args,key);
    
    while (key != NULL)
    {
        CCLog("Success key = %s", key);
        
        mSuccessKeys->push_back(key);
        
        key = va_arg(args, const char*);
    }
    
    va_end(args);
}

void CJAnimationCharacter::setLooping(const char* key)
{
    mLoopingKey = key;
}

CJAnimation* CJAnimationCharacter::showFails()
{
    mAnimationManager->removeAllAnimationsInDataPool(mDataKey);
    
    if(mFailKeys->size() > 1)
    {
        if(mFailCount % 2 == 0)
        {
            _mCurrentAnimation = mAnimationManager->playAnimation(mDataKey, mFailKeys->at(0), 1, mZorder);
        }
        else
        {
            _mCurrentAnimation = mAnimationManager->playAnimation(mDataKey, mFailKeys->at(1), 1, mZorder);
        }
        
        mFailCount++;
    }
    else
        _mCurrentAnimation = mAnimationManager->playAnimation(mDataKey, mFailKeys->at(0), 1, mZorder);
    
    return _mCurrentAnimation;
    
}

CJAnimation* CJAnimationCharacter::showSuccess()
{
    mAnimationManager->removeAllAnimationsInDataPool(mDataKey);
    
    if(mSuccessKeys->size() > 1)
    {
        if(mSuccessCount % 2 == 0)
        {
            _mCurrentAnimation = mAnimationManager->playAnimation(mDataKey, mSuccessKeys->at(0), 1, mZorder);
        }
        else
        {
            _mCurrentAnimation = mAnimationManager->playAnimation(mDataKey, mSuccessKeys->at(1), 1, mZorder);
        }
        
        mSuccessCount++;
    }
    else
        _mCurrentAnimation = mAnimationManager->playAnimation(mDataKey, mSuccessKeys->at(0), 1, mZorder);
    
    return _mCurrentAnimation;
}

CJAnimation* CJAnimationCharacter::showLooping()
{
    CCLOG("showLooping :: datakey = %s, loopingKey = %s",mDataKey.c_str(), mLoopingKey);
    mAnimationManager->removeAllAnimationsInDataPool(mDataKey);
    _mCurrentAnimation = mAnimationManager->playAnimation(mDataKey, mLoopingKey, -1, mZorder);
    return _mCurrentAnimation;
}

CJAnimation* CJAnimationCharacter::getCurrentAnimationCharacter()
{
    return _mCurrentAnimation;
}

std::vector<const char*>* CJAnimationCharacter::getAllKeys()
{
    std::vector<const char*> *tempKeys = new std::vector<const char*>();
    
    for (int i = 0 ; i < mFailKeys->size(); i++)
    {
        tempKeys->push_back(mFailKeys->at(i));
    }
    
    for (int i = 0 ; i < mSuccessKeys->size(); i++)
    {
        tempKeys->push_back(mSuccessKeys->at(i));
    }
    
    
    return tempKeys;
}

std::vector<const char*>* CJAnimationCharacter::getFailKeys()
{
    return mFailKeys;
}

std::vector<const char*>* CJAnimationCharacter::getSuccessKeys()
{
    return mSuccessKeys;
}

CCSprite* CJAnimationCharacter::getSprite(const char* spriteName)
{
    return mAnimationManager->getSpriteFromFlash(_mCurrentAnimation, spriteName);
}

void CJAnimationCharacter::setZorder(int zOrder)
{
    mZorder = zOrder;
}