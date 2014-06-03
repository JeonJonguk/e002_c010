//
//  SSItem.cpp
//  E002_C010_Project
//
//  Created by smallsnail on 2014. 4. 1..
//
//

#include "SSItem.h"
#include "CJUtils.h"
#include "CJMultimedia.h"


SSItem::SSItem()
{
    img = "";
    snd = "";
}
SSItem::~SSItem()
{
    
}


void SSItem::playEffect()
{
    CJMultimedia::getInstance()->playEffect(CJUtils::getInstance()->getFilePath("snd",snd));
}

void SSItem::playNarration()
{
    CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getFilePath("snd",snd));
}

void SSItem::playNarrationRepeat()
{
    
}

CCCallFunc* SSItem::playEffectCallfunc()
{
    return CCCallFunc::create(this, callfunc_selector(SSItem::playEffect));
}
