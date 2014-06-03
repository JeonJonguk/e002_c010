
#include "CJMenu.h"

CJMenu::CJMenu()
{
    
}

CJMenu::~CJMenu()
{
    
}

CJMenu* CJMenu::create()
{
    return CJMenu::create(NULL, NULL);
}

CJMenu * CJMenu::create(CCMenuItem* item, ...)
{
    va_list args;
    va_start(args,item);
    
    CJMenu *pRet = CJMenu::createWithItems(item, args);
    
    va_end(args);
    
    return pRet;
}

CJMenu* CJMenu::createWithArray(CCArray* pArrayOfItems)
{
    CJMenu *pRet = new CJMenu();
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

CJMenu* CJMenu::createWithItems(CCMenuItem* item, va_list args)
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
    
    return CJMenu::createWithArray(pArray);
}

CJMenu* CJMenu::createWithItem(CCMenuItem* item)
{
    return CJMenu::create(item, NULL);
}

void CJMenu::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, this->getTouchPriority(), false);
}

//bool CJMenu::ccTouchBegan(CCTouch* touch, CCEvent* event)
//{
//    m_touchedStart = touch->getStartLocation();
//    
//    return CCMenu::ccTouchBegan(touch, event);
//}
//
//void CJMenu::ccTouchEnded(CCTouch *touch, CCEvent* event)
//{
//    m_touchesEnd = touch ->getLocation();
//    
//    CCPoint different = ccpSub(m_touchesEnd, m_touchedStart);
//    
//    if (different.x > 5.0f || different.y < -5.0f)
//    {
//        CCMenu::ccTouchCancelled(touch, event);
//    }
//    else if( different.x < -5.0f || different.y < -5.0f)
//    {
//        CCMenu::ccTouchCancelled(touch, event);
//    }
//    else
//    {
//        CCMenu::ccTouchEnded(touch, event);
//    }
//}
//
//void CJMenu::ccTouchMoved(CCTouch* touch, CCEvent* event)
//{
//    CCMenu::ccTouchMoved(touch, event);
//}
