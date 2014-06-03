//
//  E001_Base_Popup.h
//  S001-C130
//
//  Created by Lee.YJ on 13. 2. 18..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#pragma once

#include "cocos2d.h"
#include "CJLayer.h"

using namespace cocos2d;


namespace CJPopupDef
{
    typedef enum
    {
        ePopupDepth_BackgroundImage                     = 0,
        ePopupDepth_Images,
        ePopupDepth_Buttons,
    }ePopupDepth;
    
    
    struct Button
    {
        std::vector<CCMenu *>                   buttons;
        float                                   delayTime;
        
        std::vector<CCObject *>                 targets;
        std::vector<SEL_CallFunc>               selectors;
        std::vector<std::string>                buttonSounds;
    };
};



/**
 * @author      Lee.YJ
 * @brief       Common popup class
 * @version     1.2
 * @date        2013.03.21
 * @since       2013.02.18
 */
class CJPopup : public CJLayer
{
////////////////////////////////////////////////////
//
// Popup bases
//
////////////////////////////////////////////////////
private:
    /**
     * @brief Parent node class of popup class.
     */
    CCLayer                                     *_parentClass;
    
    std::vector<CCTouchDelegate *>              _touchDispatchers;
    
public:
    /**
     * @brief Device window size.
     */
    CCSize                                      winSize;
   
    
private:
    /**
     * @author      Lee.YJ
     * @brief       Set pNode all touch enable setting
     * @version     1.2
     * @param       CCNode *pNode : parent class
     * @param       bool bIsTouchable : touch enable boolean value
     * @return      void
     * @exception
     * @date        2013.03.21
     * @since       2013.02.18
     */
    void _setAllNodeTouchEnable(CCNode *pNode, bool bIsTouchable);
    
    /**
     * @author      Lee.YJ
     * @brief
     * @version     1.0
     * @param       CCNode *pNode : parent class
     * @return      CCNode* : Super node
     * @exception
     * @date        2013.03.21
     * @since       2013.02.18
     */
    CCNode* _findSuperNode(CCNode *pNode);
    
    /**
     * @author      Lee.YJ
     * @brief       Set CCMenu touch enable to all nodes
     * @version     1.2
     * @param       CCNode *pNode : parent class
     * @param       bool bIsTouchable : touch enable boolean value
     * @return      void
     * @exception
     * @date        2013.03.21
     * @since       2013.02.18
     */
    void _setMenuEnable(CCNode *pNode, bool bIsTouchable);
    
    /**
     * @author      Lee.YJ
     * @brief       set touchdispatcher enable
     * @version     1.0
     * @param       bool bIsTouchable : touch enable boolean value
     * @return      void
     * @exception
     * @date        2013.03.21
     * @since       2013.03.21
     */
    void _setDispatcherEnable(bool bIsTouchable);
    
    


public:
    CREATE_FUNC(CJPopup);
    CJPopup();
    virtual ~CJPopup();
    
    virtual bool init();
    virtual bool initWithColor(const ccColor4B &color);
    virtual void onExit();
    
    virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event) { return true; }
    virtual void ccTouchMoved(CCTouch *touch, CCEvent *event) {}
    virtual void ccTouchEnded(CCTouch *touch, CCEvent *event) {}

    

    /**
     * @author      Lee.YJ
     * @brief       Show popup.
     * @version     1.0
     * @param       CCNode *pNode : parent class.
     * @param       std::string strPopupSound : play sound resource name when showing popup. (DEFAULT is "")
     * @return      void
     * @exception
     * @date        2013.02.18
     * @since       2013.02.18
     */
    void showPopup(CCLayer *pLayer, std::string strPopupSound = "");
    
    /**
     * @author      Lee.YJ
     * @brief       Hide popup.
     * @version     1.0
     * @param       CCSprite : parent class.
     * @return      void
     * @exception
     * @date        2013.02.18
     * @since       2013.02.18
     */
    void hidePopup();
    
    
    
    
    
    

    
////////////////////////////////////////////////////
//
// Sound
//
////////////////////////////////////////////////////
private:
    /**
     * @brief Sound effect ids of used this popup class effect sound.
     */
    std::vector<unsigned int>                   _soundEffectIds;

protected:
    /**
     * @author      Lee.YJ
     * @brief       Play sound effect
     * @version     1.0
     * @param       std::string strSoundResourceName : play sound effect name
     * @return      void
     * @exception
     * @date        2013.02.18
     * @since       2013.02.18
     */
    void playSoundEffect(std::string strSoundResourceName);
    
    /**
     * @author      Lee.YJ
     * @brief       Play sound effect for buttons
     * @version     1.0
     * @param       std::string strSoundResourceName : play sound effect name
     * @return      void
     * @exception
     * @date        2013.02.18
     * @since       2013.02.18
     */
    void playSoundButtonEffect(std::string strSoundResourceName);
    
    /**
     * @author      Lee.YJ
     * @brief       Stop all sound effects (don't stop the button sound effect)
     * @version     1.0
     * @param       void
     * @return      void
     * @exception
     * @date        2013.02.18
     * @since       2013.02.18
     */
    void stopAllSoundEffects();
    
    
    void playSoundNarration(std::string strSoundResourceName);
    void stopSoundNarration();
    
    
    

////////////////////////////////////////////////////
//
// Popup background
//
////////////////////////////////////////////////////
private:
    /**
     * @brief Popup background image sprite.
     */
    CCSprite                                    *_imgBackground;
    
private:
    /**
     * @author      Lee.YJ
     * @brief       Popup background image setting private method.
     * @version     1.0
     * @param       CCSprite *pSprite : background image sprite.
     * @return      void
     * @exception
     * @date        2013.02.18
     * @since       2013.02.18
     */
    void _setBackground(CCSprite *pSprite);
    
public:
    /**
     * @author      Lee.YJ
     * @brief       Popup background image setting.
     * @version     1.0
     * @param       CCSprite *pSprite : background image sprite.
     * @return      void
     * @exception
     * @date        2013.02.18
     * @since       2013.02.18
     */
    void setBackground(CCSprite *pSprite);
    
    /**
     * @author      Lee.YJ
     * @brief       Popup background image setting.
     * @version     1.0
     * @param       std::string strImageName : resource full name of background image.
     * @return      void
     * @exception
     * @date        2013.02.18
     * @since       2013.02.18
     */
    void setBackground(std::string strImageName);
    
    /**
     * @author      Lee.YJ
     * @brief       Popup background image setting.
     * @version     1.0
     * @param       std::string strImageName : resource full name of background image.
     * @return      void
     * @exception
     * @date        2013.02.18
     * @since       2013.02.18
     */
    void setBackgroundPosition(CCPoint aPoint);
    
    
    
    
    
    
////////////////////////////////////////////////////
//
// Close button
//
////////////////////////////////////////////////////
private:
    /**
     * @brief Close button instance of this popup view.
     */
    CJPopupDef::Button                               *_btnClose;


private:
    /**
     * @author      Lee.YJ
     * @brief       Add close button private method.
     * @version     1.0
     * @param       CCPoint aButtonPosition : button postion.
     * @param       CCSprite *pNormalSprite : normal style button sprite.
     * @param       CCSprite *pSelectSprite : select style button sprite.
     * @return      void
     * @exception
     * @date        2013.02.18
     * @since       2013.02.18
     */
    void _addCloseButton(CCPoint aButtonPosition, CCSprite *pNormalSprite, CCSprite *pSelectSprite);
    
    /**
     * @author      Lee.YJ
     * @brief       Callback when touched close button.
     * @version     1.0
     * @param       void
     * @return      void
     * @exception
     * @date        2013.02.18
     * @since       2013.02.18
     */
    void _onTouchedCloseButton();

    
public:
    /**
     * @author      Lee.YJ
     * @brief       Popup background image setting.
     * @version     1.0
     * @param       std::string strNormalButtonImageName : Button normal image resource name
     * @param       std::string strSelectButtonImageName : Button selected image resource name
     * @param       std::string strButtonEffectName : Button click effect sound resource name
     * @param       CCPoint aButtonPosition : Button postion
     * @param       CCObject *pCallbackTarget : Callback target when clicked button
     * @param       SEL_CallFunc aCallbackSelector : Callback method when clicked button
     * @param       float fCallbackDelayTime : Call callback delay time
     * @return      void
     * @exception
     * @date        2013.02.18
     * @since       2013.02.18
     */
    void addCloseButton(std::string strNormalButtonImageName, std::string strSelectButtonImageName, std::string strButtonEffectName,
                        CCPoint aButtonPosition, CCObject *pCallbackTarget, SEL_CallFunc aCallbackSelector,
                        float fCallbackDelayTime = 0.0f);
    
    /**
     * @author      Lee.YJ
     * @brief       Popup background image setting.
     * @version     1.0
     * @param       CCSprite *pNormalSprite : Button normal image resource name
     * @param       CCSprite *pSelectSprite : Button selected image resource name
     * @param       std::string strButtonEffectName : Button click effect sound resource name
     * @param       CCPoint aButtonPosition : Button position
     * @param       CCObject *pCallbackTarget : Callback target when clicked button
     * @param       SEL_CallFunc aCallbackSelector : Callback method when clicked button
     * @param       float fCallbackDelayTime : Call callback delay time
     * @return      void
     * @exception
     * @date        2013.02.18
     * @since       2013.02.18
     */
    void addCloseButton(CCSprite *pNormalSprite, CCSprite *pSelectSprite, std::string strButtonEffectName,
                        CCPoint aButtonPosition, CCObject *pCallbackTarget, SEL_CallFunc aCallbackSelector,
                        float fCallbackDelayTime = 0.0f);
    
    /**
     * @author      Lee.YJ
     * @brief       Popup background image setting.
     * @version     1.0
     * @param       std::string strImageName : resource full name of background image.
     * @return      void
     * @exception
     * @date        2013.02.18
     * @since       2013.02.18
     */
    void setCloseButtonPosition(CCPoint aPoint);
    
    /**
     * @author      Lee.YJ
     * @brief       Popup background image setting.
     * @version     1.0
     * @param       std::string strImageName : resource full name of background image.
     * @return      void
     * @exception
     * @date        2013.02.18
     * @since       2013.02.18
     */
    void setCloseButtonSelector(CCObject *pCallbackTarget, SEL_CallFunc aCallbackSelector);
    
    /**
     * @author      Lee.YJ
     * @brief       Popup background image setting.
     * @version     1.0
     * @param       std::string strImageName : resource full name of background image.
     * @return      void
     * @exception
     * @date        2013.02.18
     * @since       2013.02.18
     */
    void setCloseButtonEffectSound(std::string strButtonEffectName);
};


