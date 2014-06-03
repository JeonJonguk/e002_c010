//
//  E002_Base_ImageGuide.h
//  SoundPhonics_Template
//
//  Created by whitems on 13. 7. 5..
//
//

#ifndef SoundPhonics_Template_E002_Base_ImageGuide_h
#define SoundPhonics_Template_E002_Base_ImageGuide_h


#include "CJPopup.h"
#include "E002_Base_Define.h"

class E002_Base_ImageGuide_Item
{
    CC_SYNTHESIZE(std::string, img, BackgroundImg);
    CC_SYNTHESIZE(CCPoint, start, StartPosition);
    CC_SYNTHESIZE(CCPoint, end, EndPosition);

    E002_Base_ImageGuide_Item(){};
    
    E002_Base_ImageGuide_Item(std::string backImg, CCPoint startPoint, CCPoint endPoint)
    {
        img = backImg;
        start = startPoint;
        end = endPoint;
    }
};

class E002_Base_ImageGuide : public CJPopup
{
private:
    std::vector<E002_Base_ImageGuide_Item*>    *mGuideItems;
    bool                                       isOnePageGuide;
    int                                        mCurrentPage;
    CCDictionary*                              m_psdDictionary;
    bool                                       mIsFirstGuide;
public:
    
    ~E002_Base_ImageGuide();
    E002_Base_ImageGuide();
    
    static E002_Base_ImageGuide* createWithPage(CCDictionary *psdDic);
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    
    virtual bool onTouchBegan(CCPoint tp);
    virtual void onTouchMoved(CCPoint tp);
	virtual void onTouchEnded(CCPoint tp);

    CREATE_FUNC(E002_Base_ImageGuide);
    
    //user function
    
    void setGuide(std::vector<E002_Base_ImageGuide_Item*> *items);

    void setBackground();
    void setGuideSprite();
    
    void onTouchedCloseBtn();
    void onTouchedStartBtn();
    void onTouchedNextBtn();
    void onTouchedPreBtn();
    
    void showHandGuide();
    void sendCompleteMsg();

    void playBtnEffect();
    
    void setFirstGuide(bool isFirst);
};

#endif
