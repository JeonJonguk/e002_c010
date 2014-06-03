//
//  E002_Base_Navigation.cpp
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 5. 31..
//
//

#include "E002_Base_Navigation.h"
#include "CJPsdParser.h"
#include "CJUtils.h"


// For IOS, ANDROID Height gap.
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define OS_HEIGHT_GAP                                   24
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define OS_HEIGHT_GAP                                   24
#endif


// For Navigation Positions.
//#define POS_TOPLEFT                                     CCPointMake(49, naviWinSize.height-49)
//#define POS_TOPRIGHT                                    CCPointMake(naviWinSize.width - 49, naviWinSize.height-49)
//
//#define POS_CENTERLEFT                                  CCPointMake(30, winHalfSize.height)
//#define POS_CENTERRIGHT                                 CCPointMake(naviWinSize.width - 30, winHalfSize.height)
//
//#define POS_BOTTOMLEFT                                  CCPointMake(49, 49 + 24 - OS_HEIGHT_GAP)
//#define POS_BOTTOMRIGHT                                 CCPointMake(naviWinSize.width - 49, winHalfSize.height-304-OS_HEIGHT_GAP)

#define POS_TOPLEFT                                     CCPointMake(49, naviWinSize.height- (49 + OS_HEIGHT_GAP ))
#define POS_TOPRIGHT                                    CCPointMake(naviWinSize.width - 49, naviWinSize.height- (49+ OS_HEIGHT_GAP))

#define POS_CENTERLEFT                                  CCPointMake(30, winHalfSize.height)
#define POS_CENTERRIGHT                                 CCPointMake(naviWinSize.width - 30, winHalfSize.height)

#define POS_BOTTOMLEFT                                  CCPointMake(49, 49 + 24 - OS_HEIGHT_GAP + 24)
#define POS_BOTTOMRIGHT                                 CCPointMake(naviWinSize.width - 49, winHalfSize.height-304-OS_HEIGHT_GAP)

// For Navigation button menu depth.
#define nNavigation_Depth                               1000

////////////////////////////////////////////////////////
//
// Class initalize functions.
//
////////////////////////////////////////////////////////
E002_Base_Navigation::E002_Base_Navigation()
{
    _strResPrefix = CJUtils::getInstance()->getContentID();
    _fTouchDelay = 0.5;
}


E002_Base_Navigation::~E002_Base_Navigation()
{
    _strResPrefix.clear();
}



void E002_Base_Navigation::_setNavigationButtons(std::string strPsdXMLFileName)
{
    CCDictionary *psdDatas = NULL;
    
    // if strPsdXMLFileName is not "". (Exist psd file.)
    if(0 != strPsdXMLFileName.compare(""))
    {
        // psd file parsing.
        psdDatas = new CCDictionary();
        CJPsdParser::parseToPsdXML(strPsdXMLFileName, &psdDatas);
        //        psdDatas->autorelease();
    }
    
    
    // Make navigation buttons.
    for(int buttonIdx=0; buttonIdx<btnNavigationIdx.size(); buttonIdx++)
    {
        // current navigation button index.
        int             navigationIdx       = btnNavigationIdx[buttonIdx];
        // navigation button position.
        CCPoint         menuPos             = CCPointZero;
        // navigation button normal image name.
        std::string     strNormalImageName  = _strResPrefix;
        // navigation button select image name.
        std::string     strSelectImageName  = _strResPrefix;
        // navigation button disable image name.
        std::string     strDisableImageName = _strResPrefix;
        
        
        switch(navigationIdx)
        {
            case eNavigationButton_Index:
                if(NULL == psdDatas)        menuPos = POS_TOPLEFT;
                else                        menuPos = CJPsdParser::getPsdPosition(CJUtils::getStringMerge(_strResPrefix, "_common_img_btn_index_n"), psdDatas);
                
                strNormalImageName.append("_common_img_btn_index_n.png");
                strSelectImageName.append("_common_img_btn_index_s.png");
                //                strDisableImageName.append("_common_img_btn_index_d.png");
                btnNavigations[navigationIdx]->imgNormal    = CJSprite::createWithFullPath(strNormalImageName.c_str());
                btnNavigations[navigationIdx]->imgSelect    = CJSprite::createWithFullPath(strSelectImageName.c_str());
                //                btnNavigations[navigationIdx]->imgDisable   = CJSprite::createWithFullPath(strDisableImageName.c_str());
                break;
                
            case eNavigationButton_Guide:
                if(NULL == psdDatas)        menuPos = POS_TOPRIGHT;
                else                        menuPos = CJPsdParser::getPsdPosition(CJUtils::getStringMerge(_strResPrefix, "_common_img_btn_info_n"), psdDatas);
                
                strNormalImageName.append("_common_img_btn_info_n.png");
                strSelectImageName.append("_common_img_btn_info_s.png");
                //                strDisableImageName.append("_common_img_btn_info_d.png");
                btnNavigations[navigationIdx]->imgNormal    = CJSprite::createWithFullPath(strNormalImageName.c_str());
                btnNavigations[navigationIdx]->imgSelect    = CJSprite::createWithFullPath(strSelectImageName.c_str());
                //                btnNavigations[navigationIdx]->imgDisable   = CJSprite::createWithFullPath(strDisableImageName.c_str());
                break;
                
            case eNavigationButton_Prev:
                if(NULL == psdDatas)        menuPos = POS_CENTERLEFT;
                else                        menuPos = CJPsdParser::getPsdPosition("e002_common_img_btn_prev_n", psdDatas);
                
                btnNavigations[navigationIdx]->imgNormal    = CJSprite::createWithCommonPath("e002_common_img_btn_arrow01_n.png");
                btnNavigations[navigationIdx]->imgSelect    = CJSprite::createWithCommonPath("e002_common_img_btn_arrow01_s.png");
                break;
                
            case eNavigationButton_Next:
                if(NULL == psdDatas)        menuPos = POS_CENTERRIGHT;
                else                        menuPos = CJPsdParser::getPsdPosition("e002_common_img_btn_next_n", psdDatas);
                
                btnNavigations[navigationIdx]->imgNormal    = CJSprite::createWithCommonPath("e002_common_img_btn_arrow00_n.png");
                btnNavigations[navigationIdx]->imgSelect    = CJSprite::createWithCommonPath("e002_common_img_btn_arrow00_s.png");
                break;
                
            case eNavigationButton_Package:
                if(NULL == psdDatas)        menuPos = POS_TOPLEFT;
                else                        menuPos = CJPsdParser::getPsdPosition(CJUtils::getStringMerge(_strResPrefix, "_common_img_btn_package_n"), psdDatas);
                
                strNormalImageName.append("_common_img_btn_package_n.png");
                strSelectImageName.append("_common_img_btn_package_s.png");

                btnNavigations[navigationIdx]->imgNormal    = CJSprite::createWithFullPath(strNormalImageName.c_str());
                btnNavigations[navigationIdx]->imgSelect    = CJSprite::createWithFullPath(strSelectImageName.c_str());

                break;
                
            case eNavigationButton_Close:
                if(NULL == psdDatas)        menuPos = POS_TOPRIGHT;
                else                        menuPos = CJPsdParser::getPsdPosition("e002_common_img_btn_close_n", psdDatas);
                
                btnNavigations[navigationIdx]->imgNormal    = CJSprite::createWithCommonPath("e002_common_btn_close_n.png");
                btnNavigations[navigationIdx]->imgSelect    = CJSprite::createWithCommonPath("e002_common_btn_close_s.png");
                //                btnNavigations[navigationIdx]->imgDisable   = CJSprite::createWithCommonPath("e001_common_img_btn_close_d.png");
                break;
            case eNavigationButton_Reward:
                if(NULL == psdDatas)        menuPos = POS_BOTTOMLEFT;
                else                        menuPos = CJPsdParser::getPsdPosition("e002_common_btn_reward_n", psdDatas);
                
                strNormalImageName.append("_common_img_btn_reward.png");
                strSelectImageName.append("_common_img_btn_reward.png");
                
                btnNavigations[navigationIdx]->imgNormal    = CJSprite::createWithFullPath(strNormalImageName.c_str());
                btnNavigations[navigationIdx]->imgSelect    = CJSprite::createWithFullPath(strSelectImageName.c_str());
                //                btnNavigations[navigationIdx]->imgDisable   = CJSprite::createWithCommonPath("e001_common_img_btn_close_d.png");
                break;
            default:
                break;
        }
        
        
        // Make CCMenu item
        btnNavigations[navigationIdx]->menuItemSprite = CCMenuItemSprite::create(btnNavigations[navigationIdx]->imgNormal,
                                                                                 btnNavigations[navigationIdx]->imgSelect,
                                                                                 //                                                                                 btnNavigations[navigationIdx]->imgDisable,
                                                                                 (CCNode *)this, menu_selector(E002_Base_Navigation::onTouchedNavigationButton));
        // add navigation tag.
        btnNavigations[navigationIdx]->menuItemSprite->setTag(navigationIdx);
        
        // Make CCMenu.
        btnNavigations[navigationIdx]->menu = CJMenu::createWithItem(btnNavigations[navigationIdx]->menuItemSprite);
        btnNavigations[navigationIdx]->menu->setPosition(menuPos);
        this->setVisibleButton(false, navigationIdx);
        
        if (navigationIdx == eNavigationButton_Close)
        {
            parentNode->addChild(btnNavigations[navigationIdx]->menu, kDepth10_guide+1);
        }
        else
        {
            parentNode->addChild(btnNavigations[navigationIdx]->menu, kDepth9_navigations);
        }
        
    }
    
}

void E002_Base_Navigation::initWithButtonTypes(cocos2d::CCNode *pTargetLayer,
                                               std::string strPsdXMLFileName,
                                               int eNavigationButtonType, ...)
{
    va_list args;
    va_start(args, eNavigationButtonType);
    while(eNavigationButtonType != -1)
    {
        btnNavigationIdx.push_back(eNavigationButtonType);
        
        eNavigationButtonType = va_arg(args, int);
        if(eNavigationButtonType == -1)
        {
            break ;
        }
    }
    va_end(args);
    
    
    CJNavigationController::init(pTargetLayer);
    this->_setNavigationButtons(strPsdXMLFileName);
}

void E002_Base_Navigation::initWithNavigationType(cocos2d::CCNode *pTargetNode,
                                                  std::string strPsdXMLFileName,
                                                  eNavigationType eNavigationType)
{
    
    _currentPage = eNavigationType;
    
    if(eNavigationType_Question == eNavigationType)
    {
        this->initWithButtonTypes(pTargetNode,
                                  strPsdXMLFileName,
                                  eNavigationButton_Index, eNavigationButton_Guide, eNavigationButton_Close, eNavigationButton_Prev, eNavigationButton_Next, eNavigationButton_Reward, -1);
 
        
    }
    else if(eNavigationType_Reward == eNavigationType)
    {
        this->initWithButtonTypes(pTargetNode,
                                  strPsdXMLFileName,
                                  eNavigationButton_Index, eNavigationButton_Guide, eNavigationButton_Prev, eNavigationButton_Next, -1);
        
        
    }
    
    else if (eNavigationType_Diary == eNavigationType || eNavigationType_Sing == eNavigationType )
    {
        this->initWithButtonTypes(pTargetNode,
                                  strPsdXMLFileName,
                                  eNavigationButton_Index, eNavigationButton_Guide, eNavigationButton_Next, -1);
        
    }
    
    else if(eNavigationType_Index == eNavigationType)
    {
        this->initWithButtonTypes(pTargetNode,
                                  strPsdXMLFileName,
                                  eNavigationButton_Package, -1);
        
    }
    
    else if(eNavigationType_Menu == eNavigationType)
    {
        this->initWithButtonTypes(pTargetNode,
                                  strPsdXMLFileName,
                                  eNavigationButton_Index, eNavigationButton_Guide, -1);
    }
    
    else if(eNavigationType_Intro == eNavigationType)
    {
        this->initWithButtonTypes(pTargetNode,
                                  strPsdXMLFileName,
                                  eNavigationButton_Index, -1);
    }
    
}








////////////////////////////////////////////////////////
//
// Class oeprate functions.
//
////////////////////////////////////////////////////////
void E002_Base_Navigation::onTouchedNavigationButton(cocos2d::CCNode *pNode)
{
    this->setEnableNavigation(false);
    this->setEnableNavigation(true, _fTouchDelay);
 
    switch(pNode->getTag())
    {
        case eNavigationButton_Index:           this->onTouchedNavigationButtonAtIndex();       break;
        case eNavigationButton_Guide:            this->onTouchedNavigationButtonAtInfo();        break;
        case eNavigationButton_Prev:            this->onTouchedNavigationButtonAtPrev();        break;
        case eNavigationButton_Next:            this->onTouchedNavigationButtonAtNext();        break;
        case eNavigationButton_Package:         this->onTouchedNavigationButtonAtPackage();     break;
        case eNavigationButton_Reward:         this->onTouchedNavigationButtonAtReward();       break;
        case eNavigationButton_Close:   this->onTouchedNavigationButtonAtClose();               break;
        default:                                                                                break;
    }
    
    CJMultimedia::getInstance()->playEffect(CJUtils::getInstance()->getCommonFilePath("snd","e002_common_sfx_btn_01.mp3"));
}