//
//  CJSprite.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 6. 21..
//
//

#ifndef SoundPhonics_Template_CJSprite_h
#define SoundPhonics_Template_CJSprite_h

#include "cocos2d.h"

using namespace cocos2d;

class CJSprite : public CCSprite , public CCTouchDelegate{
public:
    CCPoint         m_originPosition;
    CCPoint         m_secondPosition;   // position for user mind
private:
    bool            _bTouchComplete;
    CCAction*       _defaultTouchAction;
    CCAction*       _defaultTouchActionReverse;
    
    CCAction*       _touchAction;
    CCAction*       _touchActionReverse;
    
    bool            _bIsTouchEnable;
    float           _scale;
    float           _opacity;
    
    SEL_CallFunc    _callfuncSelector;
    CCNode*         _delegate;
    
public:
    ~CJSprite();
    CJSprite();
    
    static CJSprite* create(const char *pszFileName);
    static CJSprite* createWithFullPath(const char *pszFileName);
    static CJSprite* createWithCommonPath(const char *pszFileName);
//    static CJSprite* createWithTexture(CCTexture2D *pTexture, const CCRect& rect);
    CREATE_FUNC(CJSprite);
    
    virtual bool initWithFile(const char *pszFilename);
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual void addChild(CCNode *child);
    virtual void addChild(CCNode *child, int zOrder);
    virtual void addChild(CCNode *child, int zOrder, int tag);
    
    void addChildIgnoreParent(CCNode *child);
    void addChildIgnoreParent(CCNode *child, int zOrder);
    void addChildIgnoreParent(CCNode *child, int zOrder, int tag);
    
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
    //touch action
    void setTouchEnable(bool enable);
    bool isTouchEnabled(){return _bIsTouchEnable;};
    
    void onTouchEvent();
    void setTouchEvent(CCNode* delegate, SEL_CallFunc selector);
    
    void setTouchAction(CCAction* action);
    void setTouchActionReverse(CCAction* action);
    
    void onTouchActionEvent();
    void onTouchEndActionEvent();
    
    //position
    void setAnchorPointWithoutPosition(CCPoint anchor);
    void setPositionForParent();
    void setPositionForRootParent(CCNode* rootParents);
    
    void setComplete(bool complete){_bTouchComplete = complete;};
    bool isComplete(){return _bTouchComplete;};
    
    //texture
    void changeTexture(std::string filePath);
    void changeTextureWithFullPath(std::string fileName);
    void changeTextureWithCommonPath(std::string fileName);
    
private:
    void _setPositionForParent(CCNode* child);
    void setDefualtOption();
    
    
    

};


#endif
