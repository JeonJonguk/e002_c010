//
//  CJPopupMenu.h
//  CJTemplate
//
//  Created by Dongjin Park on 13. 1. 1..
//
//

#ifndef __CJTemplate__CJPopupMenu__
#define __CJTemplate__CJPopupMenu__

#include "cocos2d.h"

USING_NS_CC;

class CJPopupMenu : public CCMenu
{
public:
    
    /** creates a CJPopupMenu with CCMenuItem objects */
    static CJPopupMenu* create(CCMenuItem* item, ...);
    
    /** creates a CJPopupMenu with a CCArray of CCMenuItem objects */
    static CJPopupMenu* createWithArray(CCArray* pArrayOfItems);
    
    /** creates a CJPopupMenu with it's item, then use addChild() to add
     * other items. It is used for script, it can't init with undetermined
     * number of variables.
     */
    static CJPopupMenu* createWithItem(CCMenuItem* item);
    
    /** creates a CCMenu with CCMenuItem objects */
    static CJPopupMenu* createWithItems(CCMenuItem *firstItem, va_list args);
    
	virtual void registerWithTouchDispatcher();
	
protected:
	
};

#endif /* defined(__CJTemplate__CJPopupMenu__) */
