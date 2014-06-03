//
//  CJNavigationController.h
//  SoundPhonics_Package
//
//  Created by j2enty on 13. 7. 8..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#ifndef __SoundPhonics_Package__CJNavigationController__
#define __SoundPhonics_Package__CJNavigationController__

#include "cocos2d.h"
#include "CJMenu.h"


namespace CJNavigation
{
    // Navigation button structure.
    struct CJNavigationButton
    {
        
        cocos2d::CCSprite                       *imgNormal;
        cocos2d::CCSprite                       *imgDisable;
        cocos2d::CCSprite                       *imgSelect;
        
        cocos2d::CCMenuItemSprite               *menuItemSprite;
        cocos2d::CCMenuItemImage                *menuItemImage;
        
        CJMenu                         *menu;
    };
}



/**
 * @author          Lee.YJ
 * @brief           CJNavigation super class.
 * @version         1.0
 * @date            2013.07.08
 * @since           2013.07.08
 */
class CJNavigationController
{
////////////////////////////////////////////////////////
//
// Class variables.
//
////////////////////////////////////////////////////////
protected:
    /**
     * @brief       Window size variable.
     */
    cocos2d::CCSize                             naviWinSize;
    
    /**
     * @brief       Window half size variable.
     */
    cocos2d::CCSize                             winHalfSize;
    
    
    /**
     * @brief       Navigation button add target node.
     */
    cocos2d::CCNode                             *parentNode;
    
    /**
     * @brief       Navigation button array. (Used CJNavigationButton structure)
     */
    CJNavigation::CJNavigationButton            *btnNavigations[10];
    
    /**
     * @brief       Use navigation button type indexs.
     */
    std::vector<int>                            btnNavigationIdx;
    
    
    
    
    
    
    
////////////////////////////////////////////////////////
//
// Class Creator & Destoryer.
//
////////////////////////////////////////////////////////
public:
    CJNavigationController();
    virtual ~CJNavigationController();

    
    


    
////////////////////////////////////////////////////////
//
// Class oeprate functions.
//
////////////////////////////////////////////////////////
protected:
    /**
     * @author      Lee.YJ
     * @brief       Initialize function.
     * @version     1.0
     * @param       CCNode *pTargetLayer    -   Parent layer node.
     * @return      void
     * @exception
     * @date        2013.07.08
     * @since       2013.07.08
     */
    virtual void init(cocos2d::CCNode *pTargetLayer);
    
    

    
    
    
    
////////////////////////////////////////////////////////
//
// Class utility function.
//
////////////////////////////////////////////////////////
    /**
     * @author      Lee.YJ
     * @brief       Make CCCallFunc callback function.
     * @version     1.0
     * @param       SEL_CallFunc aSelector  -   Callback target function.
     *              float fDelayTime        -   Call callback function after the fDelayTime.
     * @return      void
     * @exception
     * @date        2013.07.08
     * @since       2013.07.08
     */
    void callFunctionWithDelay(cocos2d::SEL_CallFunc aSelector, float fDelayTime);

    
    
    
    
    
    
////////////////////////////////////////////////////////
//
// Class oeprate functions.
//
////////////////////////////////////////////////////////
private:
    void _showNavigation();
    void _hideNavigation();

    void _setEnableNavigation();
    void _setDisableNavigation();

    void _setVisibleNavigation();
    void _setInvisibleNavigation();

protected:
    /**
     * @author      Lee.YJ
     * @brief       Show navigation buttons.
     * @version     1.0
     * @param       float fDelayTime    - Showing navigation delay time. (default 0.0f)
     * @return      void
     * @exception
     * @date        2013.07.08
     * @since       2013.07.08
     */
    virtual void showNavigation(float fDelayTime = 0.0f);
    
    /**
     * @author      Lee.YJ
     * @brief       Hide navigation buttons.
     * @version     1.0
     * @param       float fDelayTime    - Hiding navigation delay time. (default 0.0f)
     * @return      void
     * @exception
     * @date        2013.07.08
     * @since       2013.07.08
     */
    virtual void hideNavigation(float fDelayTime = 0.0f);

    /**
     * @author      Lee.YJ
     * @brief       Set added all navigation button touch enable.
     * @version     1.0
     * @param       bool bIsEnable      - true : enable / false : disable (default enable)
     *              float fDelayTime    - Enablity navigation delay time. (default 0.0f)
     * @return      void
     * @exception
     * @date        2013.07.08
     * @since       2013.07.08
     */
    virtual void setEnableNavigation(bool bIsEnable, float fDelayTime = 0.0f);
    
    /**
     * @author      Lee.YJ
     * @brief       Set added all navigation button visible.
     * @version     1.0
     * @param       bool bIsVisible     - true : visible / false : invisible (default invisible)
     *              float fDelayTime    - Visiblity navigation delay time. (default 0.0f)
     * @return      void
     * @exception
     * @date        2013.07.08
     * @since       2013.07.08
     */
    virtual void setVisibleNavigation(bool bIsVisible, float fDelayTime = 0.0f);

    /**
     * @author      Lee.YJ
     * @brief       Set navigation button touch enable.
     * @version     1.0
     * @param       bool bIsEnable              - true : enable / false : disable (default enable)
     *              int eNavigationButtonType   - navigation button type. (eNavigationButtonType)
     * @return      void
     * @exception
     * @date        2013.07.08
     * @since       2013.07.08
     */
    virtual void setEnableButton(bool bIsEnable, int eNavigationButtonType);
    virtual void setEnableButtons(bool bIsEnable, int eNavigationButtonType, ...);

    
    /**
     * @author      Lee.YJ
     * @brief       set navigation button visible.
     * @version     1.0
     * @param       bool bIsVisible             - true : visible / false : invisible (default invisible)
     *              int eNavigationButtonType   - navigation button type. (eNavigationButtonType)
     * @return      void
     * @exception
     * @date        2013.07.08
     * @since       2013.07.08
     */
    virtual void setVisibleButton(bool bIsVisible, int eNavigationButtonType);
    virtual void setVisibleButtons(bool bIsVisible, int eNavigationButtonType, ...);


    
    
    
    
    
////////////////////////////////////////////////////////
//
// Navigation button callback vitual function.
//
////////////////////////////////////////////////////////
    /**
     * @author      Lee.YJ
     * @brief       Callback function when Navigation button clicked.
     * @version     1.0
     * @param       CCNode *pNode       - CCMenuitemImage(CCMemuItemSprite) object. (Use object tag value.)
     * @return      void
     * @exception
     * @date        2013.07.08
     * @since       2013.07.08
     */
    virtual void onTouchedNavigationButton(cocos2d::CCNode *pNode) {}
};


#endif /* defined(__SoundPhonics_Package__CJNavigationController__) */
