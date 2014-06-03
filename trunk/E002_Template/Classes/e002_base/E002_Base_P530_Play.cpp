//
//  E002_Base_P530_Play.cpp
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 8. 26..
//
//


#include "E002_Base_P530_Play.h"
#include <math.h>

#define POS_TOPLEFT                                     CCPointMake(winHalfSize.width-463, winHalfSize.height+309)

enum{
    kTagBgLight,
    
    kTagThree,
    kTagTwo,
    kTagOne,
    kTagGo,
    
    kTagBtnLeft_s,
    kTagBtnRight_s,
    kTagBtnCenter_s,
    
    kTagGuideImg,
    kTagGuideCharactor,
    kTagGuideDial,
    kTagGuideDivision,
    kTagGuideMenu,
};

#pragma mark - init

E002_Base_P530_Play::E002_Base_P530_Play()
{
    m_psdDictionary = new CCDictionary();
    
 
    
}

E002_Base_P530_Play::~E002_Base_P530_Play()
{
    CC_SAFE_DELETE(m_psdDictionary);
 ;
}



bool E002_Base_P530_Play::init()
{
    if (!CJLayer::init()) {
        return false;
    }
 
    
    return true;
}


void E002_Base_P530_Play::onEnter()
{
    CJLayer::onEnter();
    
}

void E002_Base_P530_Play::onExit()
{
    removeSoundObserver();
    CJMultimedia::getInstance()->stopBGM();
    CJLayer::onExit();
}

void E002_Base_P530_Play::onNarrationFinishedCallback(std::string fileName)
{
 
}

#pragma mark - touch

bool E002_Base_P530_Play::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint tp = pTouch->getLocation();
    
 
    return false;
}

void E002_Base_P530_Play::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void E002_Base_P530_Play::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
 
}

#pragma mark - load view

void E002_Base_P530_Play::onViewLoad()
{
    CJLayer::onViewLoad();
    
   
    
    CJPsdParser::parseToPsdXML("e001_common_drum.xml", &m_psdDictionary, true);
    
    
    
}

void E002_Base_P530_Play::onViewLoaded()
{
    CJLayer::onViewLoaded();
    addSoundObserver();
    setMenuNavigation();

}


void E002_Base_P530_Play::setMenuNavigation()
{
    std::string _strResPrefix = CJUtils::getInstance()->getContentID();
    std::string strNormalImageName  = _strResPrefix;
    std::string strSelectImageName  = _strResPrefix;
    std::string strDisableImageName = _strResPrefix;
    
    std::string normal = strNormalImageName.append("_p510_img_btn_singmain_n.png");
    std::string select = strSelectImageName.append("_p510_img_btn_singmain_s.png");
    
    CJSprite* normalSp = CJSprite::createWithFullPath(strNormalImageName.c_str());
    CJSprite* selectedSp = CJSprite::createWithFullPath(strSelectImageName.c_str());
    
    // Make CCMenu item
    CCMenuItemSprite* menuItemSp = CCMenuItemSprite::create(normalSp,
                                                            selectedSp,
                                                            this,
                                                            menu_selector(E002_Base_P530_Play::onTouchedMenuAtSongMenu));
    
//    menu = CCMenu::create(menuItemSp,NULL);
//    menu->setPosition(POS_TOPLEFT);
//    addChild(menu, kDepth7_popup-1);
}
 