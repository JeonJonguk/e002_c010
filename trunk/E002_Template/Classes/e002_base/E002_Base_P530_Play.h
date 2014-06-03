//
//  E002_Base_P530_Play.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 8. 26..
//
//

#ifndef SoundPhonics_Template_E002_Base_P530_Play_h
#define SoundPhonics_Template_E002_Base_P530_Play_h


#include "cocos2d.h"
#include "CJLayer.h"
#include "CJAnimationManager.h"
#include "CJPopup.h"

 

using namespace cocos2d;



class E002_Base_P530_Play : public CJLayer, public CJAnimationManager
{
protected:
    CCDictionary*                   m_psdDictionary;
 
private:
  
    
public:
    ~E002_Base_P530_Play();
    E002_Base_P530_Play();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual void onViewLoad();
    virtual void onViewLoaded();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    //virtual void OnLastFrame(CJAnimation* pAnimation);
    virtual void onNarrationFinishedCallback(std::string fileName);
   // virtual void onComplete();
    
    CREATE_FUNC(E002_Base_P530_Play);

    void setMenuNavigation();
    virtual void onTouchedMenuAtSongMenu(){};
    
  
    
    // guide popup
    void showGuidePopup(std::string pGuideNarration, std::string pDialAlphabetFileName);
    void onTouchedGuidePopupNext(CCNode* sender);
   // virtual void onGuidePopupComplete();
 
   
 
};



#endif


