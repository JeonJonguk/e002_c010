//
//  THPopupView.h
//  PackageApp
//
//  Created by pureye4u BX on 12. 7. 2..
//  Copyright CJ Educations 2012. All rights reserved.
//

#ifndef PackageApp_THPopupView_h
#define PackageApp_THPopupView_h

#include "cocos2d.h"

class THPopupView : public cocos2d::CCLayer
{
public:
	THPopupView();
	~THPopupView();
	virtual bool init();
	
	virtual void show();
	virtual void hide();
	virtual void stop();
	virtual void setModal(bool isModal);
	
	CREATE_FUNC(THPopupView);
	
protected:
	bool m_isModal;
	bool m_status;
	cocos2d::CCRect m_popupArea;
	cocos2d::CCLayer *m_view;
	
	virtual void loadView();
	virtual void viewDidLoaded(){};
	
	virtual void showBlock();
	virtual void showPopup();
	
	virtual void hidePopup();
	virtual void hideBlock();
	
	virtual void hndTouchOutside();
	
	virtual void onExit();
	
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
//	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
//	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
//	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
};

#endif
