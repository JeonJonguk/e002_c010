//
//  THBasicLayer.h
//  Think
//
//  Created by pureMini on 13. 2. 12..
//
//

#ifndef __Think__THBasicLayer__
#define __Think__THBasicLayer__

#include "cocos2d.h"

USING_NS_CC;

class THBasicLayer : public CCLayerColor
{
private:
	
	// Class methods
	static void cleanNode(CCNode *pNode);
	
public:
	
	// Constructor, Destructor
	THBasicLayer();
	virtual ~THBasicLayer();
	
	// Initializer
	virtual bool init();
	virtual bool initWithColor(const ccColor4B &tColor);
	virtual bool initWithColor(const ccColor4B &tColor, GLfloat fWidth, GLfloat fHeight);
	
	// Member methods
	virtual bool isChildren(CCNode *pNode);
	
	
    CREATE_FUNC(THBasicLayer);
	
protected:
	
	// Member properties
	CCSize m_tWinSize;
	CCPoint m_tWinCenter;
	
	// Member methods
	virtual void removeAllChildren();
	
//	// For begin & finish
//	virtual void onEnter();
//	virtual void onExit();
//	
//	// For touch events
//    bool ccTouchBegan(CCTouch *touch, CCEvent *event);
//	void ccTouchEnded(CCTouch *touch, CCEvent *event);
//	void ccTouchMoved(CCTouch *touch, CCEvent *event);
	
private:
	
};

#endif /* defined(__Kidstory__THBasicLayer__) */
