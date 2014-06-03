//
//  CJPopupMenu.cpp
//  CJTemplate
//
//  Created by Dongjin Park on 13. 1. 1..
//
//

#include "CJPopupMenu.h"
#include "CJDefines.h"

CJPopupMenu *CJPopupMenu::create(CCMenuItem* item, ...)
{
    va_list args;
    va_start(args,item);
    
    CJPopupMenu *pRet = (CJPopupMenu*)CJPopupMenu::createWithItems(item, args);

    va_end(args);
    
    return pRet;
}

CJPopupMenu* CJPopupMenu::createWithArray(CCArray* pArrayOfItems)
{
    CJPopupMenu *pRet = new CJPopupMenu();
    if (pRet && pRet->initWithArray(pArrayOfItems))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

CJPopupMenu* CJPopupMenu::createWithItem(CCMenuItem* item)
{
    return CJPopupMenu::create(item, NULL);
}

CJPopupMenu* CJPopupMenu::createWithItems(CCMenuItem* item, va_list args)
{
    CCArray* pArray = NULL;
    if( item )
    {
        pArray = CCArray::create(item, NULL);
        CCMenuItem *i = va_arg(args, CCMenuItem*);
        while(i)
        {
            pArray->addObject(i);
            i = va_arg(args, CCMenuItem*);
        }
    }
    
    return CJPopupMenu::createWithArray(pArray);
}

void CJPopupMenu::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, CJTOUCH_PRIORITY_POPUPMENU, true);
}
