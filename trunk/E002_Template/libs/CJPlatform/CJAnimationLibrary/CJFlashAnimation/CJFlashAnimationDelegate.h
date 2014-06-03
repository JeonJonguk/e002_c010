//
//  CJFlashAnimationBaseLayer.h
//  CJTemplate
//
//  Created by SangSeong Lee on 1/15/13.
//
//

#pragma once

#include <iostream>
#include "cocos2d.h"
#include "CJAnimationLibrary.h"

using namespace cocos2d;
using namespace CJFlash;

class CJFlashAnimationDelegate : public CJAnimationEventDelegator
{
public:
    virtual void OnPlay(CJAnimation* pAnimation){}
    virtual void OnStop(CJAnimation* pAnimation){}
    virtual void OnLastFrame(CJAnimation* pAnimation){}
    virtual void OnPause(CJAnimation* pAnimation){}
    virtual void OnUpdate(CJAnimation* pAnimation){}
};
