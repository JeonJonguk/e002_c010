//
//  CJMenu.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 5. 31..
//
//

#ifndef SoundPhonics_Template_CJMenu_h
#define SoundPhonics_Template_CJMenu_h

#include "CJLayer.h"
#include "cocos2d.h"

using namespace cocos2d;

class CJMenu : public CCMenu {
    

public:
    CJMenu();
    ~CJMenu();
    
    bool isTouching;
    CCPoint m_touchedStart;
    CCPoint m_touchesEnd;
    
    static CJMenu* create();
    static CJMenu* create(CCMenuItem* item, ...);
    static CJMenu* createWithArray(CCArray* pArrayOfItems);
    static CJMenu* createWithItem(CCMenuItem* item);
    static CJMenu* createWithItems(CCMenuItem *firstItem, va_list args);

//    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
//    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
//    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
//    
    virtual void registerWithTouchDispatcher();
};

#endif

