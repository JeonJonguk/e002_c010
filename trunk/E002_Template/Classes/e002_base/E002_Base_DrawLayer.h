//
//  E002_Base_DrawLayer.h
//
//  Created by Lee.YJ on 13. 3. 28..
//  Copyright (c) 2013 CJ Educations. All rights reserved.
//

#ifndef __S001_C130__S001_C130_GuideLayer__
#define __S001_C130__S001_C130_GuideLayer__

#include "cocos2d.h"

using namespace cocos2d;

class E002_Base_DrawLayer : public CCLayerColor
{
private:
    CCSprite                            *m_brush;
    CCNode                              *m_stamp;
    CCRenderTexture                     *m_target;
    
    std::string                         _strDrawEffectName;
    std::string                         _strStempSoundName;
    
    bool                                _playingDrawingSound;
    bool                                _drawable;
    bool                                _stamp;
    bool                                _bIsEraseMode;
    
    unsigned int                        _drawSoundID;
    std::string                         m_drawSndPath;
private:
    void _playDrawingEffectSound();
    void _playStempEffectSound();
    void _resetDrawingSoundState();
    void _sendDrawingStartMsg();
    void _sendDrawingCompleteMsg();
public:
    virtual void onEnter();
    virtual void onExit();
    
    static E002_Base_DrawLayer* create();
    
    // Init Function
    bool init(CCSize size, CCPoint point, std::string strBrushName);
    
    
    // Brush Function
    void addDrawSoundEffect(std::string strSoundName);
    void addStempSoundEffect(std::string strSoundName);
    
    void clearCanvas();
    void setBrush(std::string strBrushName);
    void setBrushStroke(float rate);
    void setBrushColor(ccColor3B color);
    void setDrawSound(std::string sndPath);
    void setEraseMode(bool enable);
    bool getEraseMode();
    void brushTouchMoved(cocos2d::CCTouch *touches, cocos2d::CCEvent *event);
    void brushTouchEnded(cocos2d::CCTouch *touches, cocos2d::CCEvent *event);
    void changeBrush(std::string strBrushName);
    
    // Stamp Function
    void setStampMode(bool enable);
    void setStampNode(CCNode* stamp);

    void setDraweable(bool enable);
    
    // Touch Function
    virtual bool ccTouchBegan(CCTouch *touches, CCEvent *event);
    virtual void ccTouchMoved(CCTouch *touches, CCEvent *event);
    virtual void ccTouchEnded(CCTouch *touches, CCEvent *event);
};

#endif /* defined(__S001_C130__S001_C130_GuideLayer__) */
