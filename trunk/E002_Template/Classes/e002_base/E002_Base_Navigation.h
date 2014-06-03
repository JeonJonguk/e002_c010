//
//  E002_Base_Navigation.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 5. 31..
//
//

#ifndef SoundPhonics_Template_E002_Base_Navigation_h
#define SoundPhonics_Template_E002_Base_Navigation_h


#include "CJNavigationController.h"
//#include "E001_Base_Map.h"

using namespace cocos2d;
using namespace CJNavigation;


#define NAVIGATION_GLOBAL_INDEX_KEY                            "navigation_global_index_key"


// Navigation button types
typedef enum
{
    eNavigationButton_Index                             = 0,
    eNavigationButton_Guide,
    eNavigationButton_Prev,
    eNavigationButton_Next,
    eNavigationButton_Package,
    eNavigationButton_Close,
    eNavigationButton_Reward,
} eNavigationButton;

typedef enum
{
    eNavigationType_Index                                = 0,
    eNavigationType_Question,
    eNavigationType_Reward,
    eNavigationType_Intro,
    eNavigationType_Menu,
    eNavigationType_Diary,
    eNavigationType_Sing,
} eNavigationType;

//typedef enum
//{
//    eMapIndex_
//} eMapIndex;

//for scrollPosition in 'Index'Page.
typedef enum
{
    eNavigationMenuIndex_intro      = 0,
    eNavigationMenuIndex_page1      = 1,
    eNavigationMenuIndex_lecture    = 2,
    eNavigationMenuIndex_page2      = 3,
    eNavigationMenuIndex_page3      = 4,
    eNavigationMenuIndex_diary      = 5,
    eNavigationMenuIndex_song       = 6,
    eNavigationMenuIndex_card       = 7,
    eNavigationMenuIndex_magic      = 8,
} eNavigationMenuIndex;


/**
 * @author          Lee.YJ
 * @brief           SoundPhonics Navigation class.
 * @version         1.0
 * @date            2013.07.09
 * @since           2013.07.09
 */
class E002_Base_Navigation : public CJNavigationController
{
public:
    // E002_Base_Navigation class Creator & Destoryer
    E002_Base_Navigation();
    ~E002_Base_Navigation();


////////////////////////////////////////////////////////
//
// Class initalize functions.
//
////////////////////////////////////////////////////////
private:
    /**
     * @brief       SoundPhonics content id varialbe.
     */
    std::string                                         _strResPrefix;
    
    float                                               _fTouchDelay;

    
    eNavigationType                                     _currentPage;
    
private:
    /**
     * @author      Lee.YJ
     * @brief       Navigation buttons init, set layout, add button at target node.
     * @version     1.0
     * @param       std::string strPsdXMLFileName   -   PSD xml file name.
     * @return      void
     * @exception
     * @date        2013.07.08
     * @since       2013.07.08
     */
    void _setNavigationButtons(std::string strPsdXMLFileName);
    
protected:
    /**
     * @author      Lee.YJ
     * @brief       Initialize function.
     * @version     1.0
     * @param       CCNode *pTargetLayer            -   Parent layer node.
     *              std::string strPsdXMLFileName   -   PSD xml file name. (Only filename,  If not use PSD, input "" at this parameter)
     *              int eNavigationButtonType, ...  -   eNavigationButtonType input, (MUST input -1 at last parameter)
     * @return      void
     * @exception
     * @date        2013.07.08
     * @since       2013.07.08
     */
    void initWithButtonTypes(cocos2d::CCNode *pTargetLayer,
                             std::string strPsdXMLFileName,
                             int eNavigationButtonType, ...);
    
    void initWithNavigationType(cocos2d::CCNode *pTargetNode,
                                std::string strPsdXMLFileName,
                                eNavigationType eNavigationType);
    
    void setTouchDelay(float delay){ _fTouchDelay = delay; };

 
    
//////////////////////////////////////////////////////////
////
//// Class oeprate functions.
////
//////////////////////////////////////////////////////////
protected:
    // ---------- Implemente CJNavigationController virtual functions.
    void onTouchedNavigationButton(cocos2d::CCNode *pNode);
    // Implemente CJNavigationController virtual functions ----------.
    
    
    // Navigation buttons callback functions.
    virtual void onTouchedNavigationButtonAtIndex()     {}
    virtual void onTouchedNavigationButtonAtInfo()      {}
    virtual void onTouchedNavigationButtonAtPrev()      {}
    virtual void onTouchedNavigationButtonAtNext()      {}
    virtual void onTouchedNavigationButtonAtPackage()   {}
    virtual void onTouchedNavigationButtonAtReward()    {}
    virtual void onTouchedNavigationButtonAtClose()     {}

};


#endif
