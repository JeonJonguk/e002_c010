//
//  E002_Base_P420_Diary.h
//  SoundPhonics_Template
//
//  Created by Soonho Hong on 13. 7. 10..
//
//

#ifndef __SoundPhonics_Template__E002_Base_P420_Diary__
#define __SoundPhonics_Template__E002_Base_P420_Diary__

#include "cocos2d.h"
#include "CJLayer.h"
#include "CJAnimationManager.h"
#include "E002_Base_Define.h"
#include "E002_Base_P420_CompletePopup.h"
#include "E002_Base_DiaryAnimationInfo.h"

using namespace cocos2d;

// tool box menu button tag enum
namespace ToolBoxMenuButton {
    enum Enum
    {
        ColorRed,
        ColorYellow,
        ColorGreen,
        ColorBlue,
        ColorPupple,
        ColorGrey,
        ColorWhite,
        Eraser,
        Stamp,
        Save,
        Close,
        Finish,
        Rework,
    };
}

class E002_Base_P420_Diary : public CJLayer, CJAnimationManager
{
    // variable
public:
    
protected:
    CCDictionary*                          m_psdDictionary;
    CCSprite*                              m_brush;
    std::vector<std::string>               m_vStickerSoundFileName;
    std::vector<std::string>               m_familyTimeImageFileName;
    std::string                            m_familyTimeSound;
    CCPoint mTouchedPointGab;
    std::vector<const char*>              *mCharacterName;
    CCNode                                *m_touchedCharacter;
    
    int                                    m_currentBrushSize;
    int                                    m_currentBrushStyle;
    bool                                   m_showTools;
    std::vector<E002_Base_DiaryAnimationInfo*>       *m_showingAnimation;
    int                                    m_currentDiary;
    
private:
    bool                    m_isAction;
    bool                    m_isStampBoxOn;
    float                   m_toolBoxDefaultHeight;
    float                   m_stampBoxDefaultHeight;
    CCNode*                 m_selectNode;
    CCMenuItemSprite*       m_selectColor;
    bool                    m_isToolBoxMode;
    
    int                     m_currentFlashIndexAS;
    int                     m_currentFlashIndexBB;
    int                     m_currentFlashIndexAR;
    int                     m_currentFlashIndexGB;
    int                     m_currentFlashIndexCH;
    
    // function
public:
    ~E002_Base_P420_Diary();
    E002_Base_P420_Diary();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual void onViewLoad();
    virtual void onViewLoaded();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    CREATE_FUNC(E002_Base_P420_Diary);
    
    void finishMenuCallback(CCObject* sender);
    void closeMenuCallback(CCObject* sender);
    
    void speakStickerSound(int index);
    void setStickerSoundFileName(std::string names[]);
    virtual void animationManagerParseComplete();
    void sendPopupObject(E002_Base_P420_CompletePopup *popup);
    
protected:
    CCImage* getSaveImage();
    CCImage* getCaptureImage();
    void useCharacter(const char* name, ...);
    
private:
    ccColor3B getColor(int selectIndex);
    void setPositionForParent(CCNode* parent, CCNode* child);
    void finishAction();
    void stampBoxOn();
    void stampBoxOff();

    void addDimm();
    void onNarrationFinishedCallback(std::string fileName);
    
    void addAnimationVector(CCNode *node);
    void changeAnimationVector(CCNode *node);
    void removeAnimationVector(CCNode *node);
    
    void makeAnimationBtns(CCNode *node);
    void removeAnimationBtns(CCNode *node);
    void replaceAnimation(CCNode *node);
    void removeAnimation(CCNode *node);
    
    void setDrawBG(int index);
    
    void makeBrushColors();
    void selectBrushColor(CCNode *sender);
    void selectEraseTool();
    void selectStamp(CCNode *sender);
    void selectCrayonTool();
    void selectPenTool();
    void selectPencilTool();
    void selectBrushSize(CCNode *sender);
    
    void changeSelectedSticker(CCNode *node, bool isSelectd);
    
    CCActionInterval* getSelectToolAction();
    CCActionInterval* getUnselectToolAction();
    
    void makeTools();
    void makeStampBox();
    void showStampBox();
    void hideStampBox();
    
    void makeBrushBox();
    void makeStickers();
    
    void showTools();
    void stopToShowTools();
    void showToolsAfterDelay();
    void hideTools();
    
    void firstShowItems();
    void playShowToolsEffect();
    void replaceBrush();
    
    virtual void selectIndexBtn(){};
    void _saveButtonSelect();
    void saveButtonSelect();
    std::string makeFileToFlashInfo();
    
    std::string getContentID(std::string resource);
    
    void addDrawingObserver();
    void removeDrawingObserver();
    
    virtual void showCompletePopup(){};
    
    void nextScene();
};

#endif /* defined(__SoundPhonics_Template__E002_Base_P420_Diary__) */
