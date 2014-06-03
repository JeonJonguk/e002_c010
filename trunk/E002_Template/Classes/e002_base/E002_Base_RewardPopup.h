//
//  E002_Base_RewardPopup.h
//  E002_Template
//
//  Created by Jeong.YJ on 2014. 4. 1..
//
//

#ifndef E002_Template_E002_Base_RewardPopup_h
#define E002_Template_E002_Base_RewardPopup_h

#include "CJPopup.h"
#include "CJLayer.h"
#include "E002_Base_Define.h"
#include "E002_Base_SoundManager.h"

class E002_Base_RewardPopup : public CJPopup
{
private:
    std::vector<const char*>        *mItems;
    CCDictionary                    *m_psdDictionary;
    int                             mPageNumber;
    bool                            mShowRewardPopup;
    bool                            mShowMotionComplete;
    bool                            mHideMotionComplete;
    CJSprite                        *mGiftBox;
    E002_Base_SoundManager          *mSndManager;
public:
    
    ~E002_Base_RewardPopup();
    E002_Base_RewardPopup();
    
    
    virtual bool init(int pageNumber);
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);
    
    void setRewardItems(const char* key, ...);
    void showRewardItem(int index);
    void showRewardBox(int index);
    
    std::string getContentID(std::string resource);
    
    void sendRewardItemCompleteMsg();
    void sendRewardPopupCompleteMsg();
    
    void showGetRewardParticle();
    void showMoveRewardParticle();
    
    void hideRewardPopup();
    void setShowMotionComplete();
    
    void showGiftBoxEffect();
    
    void addDimBackgound();
    void removeDimBackground();
    void playEffectGetItem();
};


#endif
