//
//  E002_Base_P420_Diary.cpp
//  SoundPhonics_Template
//
//  Created by Soonho Hong on 13. 7. 10..
//
//

#include "E002_Base_P420_Diary.h"
#include "E002_Base_DrawLayer.h"
#include "CJLMSContentInterface.h"
#include "cocos-ext.h"
#include "CJMenu.h"

namespace  {
enum
{
	kTagDrawLayer,
	kTagDrawBG,
    kTagDiaryLayer,
    kTagDrawLine,
    kTagDimm,

    kTagStickerAS,
    kTagStickerCH,
    kTagStickerBB,
    kTagStickerGB,
    kTagStickerAR,
    
    kTagFlashAS,
    kTagFlashCH,
    kTagFlashBB,
    kTagFlashGB,
    kTagFlashAR,
    
    kTagFlashReplaceBtn,
    kTagFlashRemoveBtn,
    kTagFlashBtns,
    
    kTagColorBG,
    kTagToolBG,
    kTagToolEraser,
    kTagToolStamp,
    kTagToolCrayon,
    kTagToolPen,
    kTagToolPencil,
    kTagContainer,
    kTagScrollView,
    kTagStampBox,
    kTagSave,
    kTagSaveMenu,
    kTagIndex,
    kTagIndexMenu,
    kTagBrushMenu,
    kTagBrushBox,
    
    kTagColor = 200,
    kTagStamp = 300,
    kTagBrush = 400,
};
}

// tool box color's RGB value list
const float colorRGB[24][3] = {
		{110,62,25},
        {185,104,38},
        {255,218,160},
        {255,166,172},
        {243,95,162},
        {203,54,133},
        {223,54,79},
        {144,0,142},
        {8,57,136},
        {2,93,174},
        {2,172,184},
        {0,157,255},
        {0,204,255},
        {130,146,0},
        {55,124,0},
        {181,219,0},
        {242,235,24},
        {255,210,0},
        {245,169,46},
        {255,116,0},
        {219,5,0},
        {255,255,255},
        {180,180,180},
        {0,0,0}
};

// tool box menu button key string list
const char* menuBtnKey[13] = {
		"e001_common_funtime_img_btn_color_00_s",
		"e001_common_funtime_img_btn_color_01_s",
		"e001_common_funtime_img_btn_color_02_s",
		"e001_common_funtime_img_btn_color_03_s",
		"e001_common_funtime_img_btn_color_04_s",
		"e001_common_funtime_img_btn_color_05_s",
		"e001_common_funtime_img_btn_color_06_s",
		"e001_common_funtime_img_btn_eraser_s",
		"e001_common_funtime_img_btn_stamp",
		"e001_common_funtime_img_btn_save",
		"e001_common_img_btn_close",
		"e001_common_funtime_img_btn_finish",
		"e001_common_funtime_img_btn_rework"
};

// stamp position in stamp box
const CCPoint stampPoint[8] = {
		ccp(510, 401),
		ccp(633, 401),
		ccp(758, 401),
		ccp(881, 401),
		ccp(510, 278),
		ccp(633, 278),
		ccp(758, 278),
		ccp(881, 278)
};

#define PEN     0
#define PENCIL  1
#define CRAYON  2

#define ANISON_FLASH_COUNT       4
#define CHU_FLASH_COUNT          3
#define BOOMBOOM_FLASH_COUNT     4
#define GRUMBIE_FLASH_COUNT      4
#define ALPHAROBOT_FLASH_COUNT   2

#pragma mark - init

E002_Base_P420_Diary::E002_Base_P420_Diary()
{
	m_psdDictionary = new CCDictionary();
	m_selectNode = NULL;
	m_brush = NULL;
	m_isAction = false;
	m_isStampBoxOn = false;
    m_isToolBoxMode = false;
	
    m_currentFlashIndexAS = 0;
    m_currentFlashIndexBB = 0;
    m_currentFlashIndexAR = 0;
    m_currentFlashIndexGB = 0;
    m_currentFlashIndexCH = 0;
    
    m_vStickerSoundFileName.clear();
    
    mCharacterName = new std::vector<const char*>();
    m_currentBrushSize = 1;
    m_currentBrushStyle = PEN;
    m_showTools = true;
    
    m_showingAnimation = new std::vector<E002_Base_DiaryAnimationInfo*>();
}

E002_Base_P420_Diary::~E002_Base_P420_Diary()
{
	CC_SAFE_DELETE(m_psdDictionary);
	CC_SAFE_DELETE(m_brush);

	m_vStickerSoundFileName.clear();
}   


bool E002_Base_P420_Diary::init()
{
	if (!CJLayer::initWithColor(ccc4(255, 255, 255, 255))) {
		return false;
	}

    m_currentDiary = CJUtils::getInstance()->getUserDefaultIntegerForKey(E002_USERDEFAULT_DIARY_NUMBER);
    
	return true;
}

void E002_Base_P420_Diary::useCharacter(const char *name, ...)
{
    va_list args;
    va_start(args,name);
    
    while (name != NULL)
    {
        mCharacterName->push_back(name);
        
        name = va_arg(args, const char*);
    }
    
    va_end(args);
}

void E002_Base_P420_Diary::onEnter()
{
	CJLayer::onEnter();
}


void E002_Base_P420_Diary::onExit()
{
    removeDrawingObserver();
	removeSoundObserver();
	CJLayer::onExit();
}

#pragma mark - touch

bool E002_Base_P420_Diary::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint tp = pTouch->getLocation();
    E002_Base_DrawLayer* drawLayer = (E002_Base_DrawLayer*)getChildByTag(kTagDiaryLayer)->getChildByTag(kTagDrawBG)->getChildByTag(kTagDrawLayer);
    m_touchedCharacter = NULL;
    
    for (int i = kTagFlashAS; i <= kTagFlashAR; i++)
    {
        if (getChildByTag(kTagDiaryLayer)->getChildByTag(i) != NULL)
        {
            removeAnimationBtns(getChildByTag(kTagDiaryLayer)->getChildByTag(i));
        }
    }

    if(CJUtils::hitTestPoint(getChildByTag(kTagColorBG), tp, false))
    {
        m_isToolBoxMode = false;
        
        drawLayer->setDraweable(false);
        return false;

    }
    else if(CJUtils::hitTestPoint(getChildByTag(kTagBrushBox), tp, false))
    {
        drawLayer->setDraweable(false);
        return false;
    }
    else if(CJUtils::hitTestPoint(getChildByTag(kTagStampBox), tp, false))
    {
        drawLayer->setDraweable(false);
        return false;
    }
    else if(CJUtils::hitTestPoint(getChildByTag(kTagToolBG)->getChildByTag(kTagToolEraser), tp, false))
    {
        selectEraseTool();
        return true;
    }
    else if(CJUtils::hitTestPoint(getChildByTag(kTagToolBG)->getChildByTag(kTagToolCrayon), tp, false))
    {
        selectCrayonTool();
        return true;
    }
    else if(CJUtils::hitTestPoint(getChildByTag(kTagToolBG)->getChildByTag(kTagToolPen), tp, false))
    {
        selectPenTool();
        return true;
    }
    else if(CJUtils::hitTestPoint(getChildByTag(kTagToolBG)->getChildByTag(kTagToolPencil), tp, false))
    {
        selectPencilTool();
        return true;
    }
    else if(CJUtils::hitTestPoint(getChildByTag(kTagToolBG)->getChildByTag(kTagToolStamp), tp, false))
    {
        showStampBox();
        return true;
    }
    else if( CJUtils::hitTestPoint(getChildByTag(kTagIndexMenu)->getChildByTag(kTagIndex), tp, false)
          || CJUtils::hitTestPoint(getChildByTag(kTagToolBG)->getChildByTag(kTagSaveMenu)->getChildByTag(kTagSave), tp, false) )
    {
        drawLayer->setDraweable(false);
        return false;
    }
    
    for (int i = kTagStickerAS; i <= kTagStickerAR; i++)
    {
        if (getChildByTag(i) != NULL && CJUtils::hitTestPoint(getChildByTag(i), tp, false))
        {
            playCommonEffect("e002_common_sfx_btn_02.mp3");

            if (getChildByTag(kTagDiaryLayer)->getChildByTag(i+5) != NULL) {
                getChildByTag(kTagDiaryLayer)->getChildByTag(i+5)->runAction(CCSequence::create(CCSpawn::create(CCEaseSineIn::create(CCScaleTo::create(0.3, 0.8f)),
                                                                                                                CCEaseSineIn::create(CCMoveTo::create(0.3, ccp(CJUtils::randomInteger(200, 900), CJUtils::randomInteger(200, 600)))),
                                                                                                                NULL),
                                                                                                CCEaseSineIn::create(CCScaleTo::create(0.1, 1.2)),
                                                                                                CCEaseSineIn::create(CCScaleTo::create(0.1, 0.9)),
                                                                                                CCEaseSineIn::create(CCScaleTo::create(0.1, 1.0)),
                                                                                                CCCallFuncN::create(this, callfuncN_selector(E002_Base_P420_Diary::addAnimationVector)),
                                                                                                NULL));
            }
         
            
            changeSelectedSticker(getChildByTag(i), true);
            
            return true;
        }
    }
    
    for (int i = kTagFlashAS; i <= kTagFlashAR; i++)
    {
        if (getChildByTag(kTagDiaryLayer)->getChildByTag(i) != NULL && CJUtils::hitTestPoint(getChildByTag(kTagDiaryLayer)->getChildByTag(i), tp, false))
        {
            makeAnimationBtns(getChildByTag(kTagDiaryLayer)->getChildByTag(i));
            
            hideTools();
            mTouchedPointGab = ccpSub(getChildByTag(kTagDiaryLayer)->getChildByTag(i)->getPosition(), tp);
            m_touchedCharacter = (CJAnimation*)getChildByTag(kTagDiaryLayer)->getChildByTag(i);
            
            return true;
        }
    }

    drawLayer->setDraweable(true);
    hideTools();
    return false;
}

void E002_Base_P420_Diary::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint tp = pTouch->getLocation();
    
    if(m_touchedCharacter != NULL)
        m_touchedCharacter->setPosition(ccp(tp.x + mTouchedPointGab.x, tp.y + mTouchedPointGab.y));
}

void E002_Base_P420_Diary::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint tp = pTouch->getLocation();

    if (!m_showTools)
    {
        if (m_touchedCharacter != NULL && CJUtils::hitTestPoint(m_touchedCharacter, tp, false))
        {
            changeAnimationVector(m_touchedCharacter);
        }
        
        CJUtils::performSelector(this, callfunc_selector(E002_Base_P420_Diary::showTools), 1.0f);
    }
}

#pragma mark - load view


void E002_Base_P420_Diary::onViewLoad()
{
	CJLayer::onViewLoad();

	// load common p420 psd xml file
	CJPsdParser::parseToPsdJSON("e002_common_diary_p420_draw.json", &m_psdDictionary, true);

    setAnimationParent(this);

    setDrawBG(m_currentDiary);
    
	// add tool box bg
	

	E002_Base_DrawLayer* drawLayer = E002_Base_DrawLayer::create();
	drawLayer->init(
			getContentSize(),
			ccp(0,0),
			CJUtils::getInstance()->getCommonFilePath("img", "e002_common_diary_img_pen_brush01.png")
	);
	drawLayer->setTag(kTagDrawLayer);
	drawLayer->setBrushStroke(m_currentBrushSize);
	getChildByTag(kTagDiaryLayer)->getChildByTag(kTagDrawBG)->addChild(drawLayer);
    
    drawLayer->setDraweable(true);
    drawLayer->setBrushColor(getColor(0));
    drawLayer->setDrawSound("e002_common_diary_sfx_write01.mp3");
    
    makeBrushColors();
    makeTools();
    makeStampBox();
    makeBrushBox();

    setAnimationCommonFile("e002_common_diary_flash_as_sheets.json", "e002_common_diary_flash_as_animations.json", ANISON);
    setAnimationCommonFile("e002_common_diary_flash_ch_sheets.json", "e002_common_diary_flash_ch_animations.json", CHU);
    setAnimationCommonFile("e002_common_diary_flash_bb_sheets.json", "e002_common_diary_flash_bb_animations.json", BOOMBOOM);
    setAnimationCommonFile("e002_common_diary_flash_gb_sheets.json", "e002_common_diary_flash_gb_animations.json", GRUMBIE);
    setAnimationCommonFile("e002_common_diary_flash_ar_sheets.json", "e002_common_diary_flash_ar_animations.json", ALPHAROBOT);
    
    animationManagerParseStart();

    
}

void E002_Base_P420_Diary::animationManagerParseComplete()
{
    makeStickers();
    
    if (getChildByTag(kTagStickerAS) != NULL)
    {
        createAnimationsInDataPool(ANISON);
        m_currentFlashIndexAS = CJUtils::randomInteger(0, ANISON_FLASH_COUNT - 1);

        CJAnimation *anison = playAnimationWithCommonPath(ANISON, CJUtils::getStringFormatInteger("e002_common_diary_flash_as%02d_loop", m_currentFlashIndexAS), -1, kDepth2_questions, getChildByTag(kTagDiaryLayer));
        anison->setPosition(getChildByTag(kTagStickerAS)->getPosition());
        anison->setScale(0);
        anison->setTag(kTagFlashAS);
    }
    
    if(getChildByTag(kTagStickerAR) != NULL)
    {
        createAnimationsInDataPool(ALPHAROBOT);
        m_currentFlashIndexAR = CJUtils::randomInteger(0, ALPHAROBOT_FLASH_COUNT - 1);
        
        CJAnimation *alphaRobot = playAnimationWithCommonPath(ALPHAROBOT, CJUtils::getStringFormatInteger("e002_common_diary_flash_ar%02d_loop", m_currentFlashIndexAR), -1, kDepth2_questions, getChildByTag(kTagDiaryLayer));
        alphaRobot->setPosition(getChildByTag(kTagStickerAR)->getPosition());
        alphaRobot->setScale(0);
        alphaRobot->setTag(kTagFlashAR);
    }
    
    if(getChildByTag(kTagStickerBB) != NULL)
    {
        createAnimationsInDataPool(BOOMBOOM);
        m_currentFlashIndexBB = CJUtils::randomInteger(0, BOOMBOOM_FLASH_COUNT - 1);

        CJAnimation *boomboom = playAnimationWithCommonPath(BOOMBOOM, CJUtils::getStringFormatInteger("e002_common_diary_flash_bb%02d_loop", m_currentFlashIndexBB), -1, kDepth2_questions, getChildByTag(kTagDiaryLayer));
        boomboom->setPosition(getChildByTag(kTagStickerBB)->getPosition());
        boomboom->setScale(0);
        boomboom->setTag(kTagFlashBB);
    }
    
    if(getChildByTag(kTagStickerCH) != NULL)
    {
        createAnimationsInDataPool(CHU);

        m_currentFlashIndexCH = CJUtils::randomInteger(0, CHU_FLASH_COUNT - 1);
        
        CJAnimation *chu = playAnimationWithCommonPath(CHU, CJUtils::getStringFormatInteger("e002_common_diary_flash_ch%02d_loop", m_currentFlashIndexCH), -1, kDepth2_questions, getChildByTag(kTagDiaryLayer));
        chu->setPosition(getChildByTag(kTagStickerCH)->getPosition());
        chu->setScale(0);
        chu->setTag(kTagFlashCH);
    }
    
    if(getChildByTag(kTagStickerGB) != NULL)
    {
        createAnimationsInDataPool(GRUMBIE);
        m_currentFlashIndexGB = CJUtils::randomInteger(0, GRUMBIE_FLASH_COUNT - 1);
        
        CJAnimation *grumbie = playAnimationWithCommonPath(GRUMBIE, CJUtils::getStringFormatInteger("e002_common_diary_flash_gb%02d_loop", m_currentFlashIndexGB), -1, kDepth2_questions, getChildByTag(kTagDiaryLayer));
        grumbie->setPosition(getChildByTag(kTagStickerGB)->getPosition());
        grumbie->setScale(0);
        grumbie->setTag(kTagFlashGB);
    }
    
    firstShowItems();
}

void E002_Base_P420_Diary::onViewLoaded()
{
	CJLayer::onViewLoaded();
	addSoundObserver();
    addDrawingObserver();
}

void E002_Base_P420_Diary::firstShowItems()
{
    playShowToolsEffect();

    getChildByTag(kTagToolBG)->runAction(CCMoveBy::create(0.3f, ccp(0, getChildByTag(kTagToolBG)->getChildByTag(kTagToolCrayon)->getContentSize().height)));
    
    getChildByTag(kTagColorBG)->runAction(CCSequence::create(CCDelayTime::create(0.5f),
                                                             CCCallFunc::create(this, callfunc_selector(E002_Base_P420_Diary::playShowToolsEffect)),
                                                             CCMoveBy::create(0.3f, ccp(getChildByTag(kTagColorBG)->getContentSize().width, 0)),
                                                             NULL));
    
    getChildByTag(kTagBrushBox)->runAction(CCSequence::create(CCDelayTime::create(0.5f),
                                                              CCCallFunc::create(this, callfunc_selector(E002_Base_P420_Diary::playShowToolsEffect)),
                                                              CCMoveBy::create(0.3f, ccp(getChildByTag(kTagBrushBox)->getContentSize().width, 0)),
                                                              NULL));
    
    for (int i = 0; i < mCharacterName->size(); i++)
    {
        CJSprite *sticker;
        
        if(strcmp(mCharacterName->at(i), ANISON) == 0 )
        {
            sticker = (CJSprite*)getChildByTag(kTagStickerAS);
        }
        else if(strcmp(mCharacterName->at(i), CHU) == 0 )
        {
            sticker = (CJSprite*)getChildByTag(kTagStickerCH);
        }
        else if(strcmp(mCharacterName->at(i), BOOMBOOM) == 0 )
        {
            sticker = (CJSprite*)getChildByTag(kTagStickerBB);
        }
        else if(strcmp(mCharacterName->at(i), GRUMBIE) == 0 )
        {
            sticker = (CJSprite*)getChildByTag(kTagStickerGB);
        }
        else if(strcmp(mCharacterName->at(i), ALPHAROBOT) == 0 )
        {
            sticker = (CJSprite*)getChildByTag(kTagStickerAR);
        }
        
        sticker->runAction(CCSequence::create(CCDelayTime::create(1.0f),
                                              CCCallFunc::create(this, callfunc_selector(E002_Base_P420_Diary::playShowToolsEffect)),
                                              CCMoveBy::create(0.3f, ccp(-sticker->getContentSize().width, 0)),
                                              NULL));
    }
}

void E002_Base_P420_Diary::playShowToolsEffect()
{
    playCommonEffect("e002_common_diary_sfx_toolbox_open.mp3");
}

void E002_Base_P420_Diary::addAnimationVector(CCNode *node)
{
    E002_Base_DiaryAnimationInfo *info = new E002_Base_DiaryAnimationInfo();
    
    if (node->getTag() == kTagFlashAS)
    {
        info->setAniName(ANISON);
        info->setNumber(m_currentFlashIndexAS);
    }
    else if (node->getTag() == kTagFlashCH)
    {
        info->setAniName(CHU);
        info->setNumber(m_currentFlashIndexCH);
    }
    else if (node->getTag() == kTagFlashBB)
    {
        info->setAniName(BOOMBOOM);
        info->setNumber(m_currentFlashIndexBB);
    }
    else if (node->getTag() == kTagFlashGB)
    {
        info->setAniName(GRUMBIE);
        info->setNumber(m_currentFlashIndexGB);
    }
    else if (node->getTag() == kTagFlashAR)
    {
        info->setAniName(ALPHAROBOT);
        info->setNumber(m_currentFlashIndexAR);
    }
    
    info->setTag(node->getTag());
    info->setPositionX(node->getPositionX());
    info->setPositionY(node->getPositionY());
    
    m_showingAnimation->push_back(info);

}

void E002_Base_P420_Diary::changeAnimationVector(CCNode *node)
{
    for (int i = 0; i < m_showingAnimation->size(); i++)
    {
        if(node->getTag() == m_showingAnimation->at(i)->getTag())
        {
            if(node->getTag() == kTagFlashAS)
            {
                m_showingAnimation->at(i)->setNumber(m_currentFlashIndexAS);
            }
            else if(node->getTag() == kTagFlashCH)
            {
                m_showingAnimation->at(i)->setNumber(m_currentFlashIndexCH);
            }
            else if(node->getTag() == kTagFlashBB)
            {
                m_showingAnimation->at(i)->setNumber(m_currentFlashIndexBB);
            }
            else if(node->getTag() == kTagFlashGB)
            {
                m_showingAnimation->at(i)->setNumber(m_currentFlashIndexGB);
            }
            else if(node->getTag() == kTagFlashAR)
            {
                m_showingAnimation->at(i)->setNumber(m_currentFlashIndexAR);
            }

            m_showingAnimation->at(i)->setPositionX(node->getPositionX());
            m_showingAnimation->at(i)->setPositionY(node->getPositionY());
        
        }
    }
}

void E002_Base_P420_Diary::removeAnimationVector(CCNode *node)
{
    for (std::vector<E002_Base_DiaryAnimationInfo*>::iterator iter = m_showingAnimation->begin(); iter != m_showingAnimation->end(); )
    {
        if (node->getParent()->getParent()->getTag() == (*iter)->getTag())
        {
            iter =  m_showingAnimation->erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

void E002_Base_P420_Diary::makeAnimationBtns(CCNode *node)
{
    CJSprite *replceBtnN = CJSprite::createWithCommonPath("e002_common_diary_btn_reload_n.png");
    CJSprite *replceBtnS = CJSprite::createWithCommonPath("e002_common_diary_btn_reload_s.png");
    
    CCMenuItemSprite* replaceBtn = CCMenuItemSprite::create(replceBtnN,
                                                            replceBtnS,
                                                            this,
                                                            menu_selector(E002_Base_P420_Diary::replaceAnimation));
    
    replaceBtn->setTag(kTagFlashReplaceBtn);
    replaceBtn->setPosition(ccp(node->getContentSize().width, node->getContentSize().height - replaceBtn->getContentSize().height - 5));
    
    CJSprite *deleteBtnN = CJSprite::createWithCommonPath("e002_common_diary_btn_delete_n.png");
    CJSprite *deleteBtnS = CJSprite::createWithCommonPath("e002_common_diary_btn_delete_s.png");
    
    CCMenuItemSprite* deleteBtn = CCMenuItemSprite::create(deleteBtnN,
                                                            deleteBtnS,
                                                            this,
                                                            menu_selector(E002_Base_P420_Diary::removeAnimation));
    
    deleteBtn->setTag(kTagFlashRemoveBtn);
    deleteBtn->setPosition(ccp(node->getContentSize().width, node->getContentSize().height));
    
    CCMenu *menu = CCMenu::create(replaceBtn, deleteBtn, NULL);
    menu->setPosition(CCPointZero);
    menu->setTag(kTagFlashBtns);
    
    node->addChild(menu, kDepth7_popup);
    
}

void E002_Base_P420_Diary::removeAnimationBtns(CCNode *node)
{
    node->removeChildByTag(kTagFlashBtns);
}

void E002_Base_P420_Diary::replaceAnimation(CCNode *node)
{
    CCPoint prePosition = node->getParent()->getParent()->getPosition();
    CJAnimation *character;
    
    if(node->getParent()->getParent()->getTag() == kTagFlashAS)
    {
        node->getParent()->getParent()->removeChild(node->getParent());

        removeAllAnimationsInDataPool(ANISON, true);
        
        m_currentFlashIndexAS++;
            
        if(m_currentFlashIndexAS > ANISON_FLASH_COUNT - 1)
        {
            m_currentFlashIndexAS = 0;
        }
        
        character = playAnimationWithCommonPath(ANISON, CJUtils::getStringFormatInteger("e002_common_diary_flash_as%02d_loop", m_currentFlashIndexAS), -1, kDepth2_questions, getChildByTag(kTagDiaryLayer));
        character->setPosition(prePosition);;
        character->setTag(kTagFlashAS);
        
    }
    else if(node->getParent()->getParent()->getTag() == kTagFlashAR)
    {
        node->getParent()->getParent()->removeChild(node->getParent());
        
        removeAllAnimationsInDataPool(ALPHAROBOT, true);
        
        m_currentFlashIndexAR++;
        
        if(m_currentFlashIndexAR > ALPHAROBOT_FLASH_COUNT - 1)
        {
            m_currentFlashIndexAR = 0;
        }
        
        character = playAnimationWithCommonPath(ALPHAROBOT, CJUtils::getStringFormatInteger("e002_common_diary_flash_ar%02d_loop", m_currentFlashIndexAR), -1, kDepth2_questions, getChildByTag(kTagDiaryLayer));
        character->setPosition(prePosition);;
        character->setTag(kTagFlashAR);
        
    }
    else if(node->getParent()->getParent()->getTag() == kTagFlashBB)
    {
        node->getParent()->getParent()->removeChild(node->getParent());
        
        removeAllAnimationsInDataPool(BOOMBOOM, true);
        
        m_currentFlashIndexBB++;
        
        if(m_currentFlashIndexBB > BOOMBOOM_FLASH_COUNT - 1)
        {
            m_currentFlashIndexBB = 0;
        }
        
        character = playAnimationWithCommonPath(BOOMBOOM, CJUtils::getStringFormatInteger("e002_common_diary_flash_bb%02d_loop", m_currentFlashIndexBB), -1, kDepth2_questions, getChildByTag(kTagDiaryLayer));
        character->setPosition(prePosition);;
        character->setTag(kTagFlashBB);
        
    }
    else if(node->getParent()->getParent()->getTag() == kTagFlashCH)
    {
        node->getParent()->getParent()->removeChild(node->getParent());
        
        removeAllAnimationsInDataPool(CHU, true);
        
        m_currentFlashIndexCH++;
        
        if(m_currentFlashIndexCH > CHU_FLASH_COUNT - 1)
        {
            m_currentFlashIndexCH = 0;
        }
        
        character = playAnimationWithCommonPath(CHU, CJUtils::getStringFormatInteger("e002_common_diary_flash_ch%02d_loop", m_currentFlashIndexCH), -1, kDepth2_questions, getChildByTag(kTagDiaryLayer));
        character->setPosition(prePosition);;
        character->setTag(kTagFlashCH);
        
    }
    else if(node->getParent()->getParent()->getTag() == kTagFlashGB)
    {
        node->getParent()->getParent()->removeChild(node->getParent());
        
        removeAllAnimationsInDataPool(GRUMBIE, true);
        
        m_currentFlashIndexGB++;
        
        if(m_currentFlashIndexGB > GRUMBIE_FLASH_COUNT - 1)
        {
            m_currentFlashIndexGB = 0;
        }
        
        character = playAnimationWithCommonPath(GRUMBIE, CJUtils::getStringFormatInteger("e002_common_diary_flash_gb%02d_loop", m_currentFlashIndexGB), -1, kDepth2_questions, getChildByTag(kTagDiaryLayer));
        character->setPosition(prePosition);;
        character->setTag(kTagFlashGB);
    }
    
    makeAnimationBtns(character);
    changeAnimationVector(character);
}

void E002_Base_P420_Diary::removeAnimation(CCNode *node)
{
    removeAnimationVector(node);
    
    if(node->getParent()->getParent()->getTag() == kTagFlashAS)
    {
        node->getParent()->getParent()->removeChild(node->getParent());
        removeAllAnimationsInDataPool(ANISON, true);
        
        CJAnimation *anison = playAnimationWithCommonPath(ANISON, CJUtils::getStringFormatInteger("e002_common_diary_flash_as%02d_loop", m_currentFlashIndexAS), -1, kDepth2_questions, getChildByTag(kTagDiaryLayer));
        anison->setPosition(getChildByTag(kTagStickerAS)->getPosition());
        anison->setScale(0);
        anison->setTag(kTagFlashAS);
        
        changeSelectedSticker(getChildByTag(kTagFlashAS-5), false);
        
    }
    else if(node->getParent()->getParent()->getTag() == kTagFlashAR)
    {
        node->getParent()->getParent()->removeChild(node->getParent());
        removeAllAnimationsInDataPool(ALPHAROBOT, true);
        
        CJAnimation *alphaRobot = playAnimationWithCommonPath(ALPHAROBOT, CJUtils::getStringFormatInteger("e002_common_diary_flash_ar%02d_loop", m_currentFlashIndexAR), -1, kDepth2_questions, getChildByTag(kTagDiaryLayer));
        alphaRobot->setPosition(getChildByTag(kTagStickerAR)->getPosition());
        alphaRobot->setScale(0);
        alphaRobot->setTag(kTagFlashAR);
        
        changeSelectedSticker(getChildByTag(kTagFlashAR-5), false);
    }
    else if(node->getParent()->getParent()->getTag() == kTagFlashBB)
    {
        node->getParent()->getParent()->removeChild(node->getParent());
        removeAllAnimationsInDataPool(BOOMBOOM, true);
 
        CJAnimation *boomboom = playAnimationWithCommonPath(BOOMBOOM, CJUtils::getStringFormatInteger("e002_common_diary_flash_bb%02d_loop", m_currentFlashIndexBB), -1, kDepth2_questions, getChildByTag(kTagDiaryLayer));
        boomboom->setPosition(getChildByTag(kTagStickerBB)->getPosition());
        boomboom->setScale(0);
        boomboom->setTag(kTagFlashBB);
        
        changeSelectedSticker(getChildByTag(kTagFlashBB-5), false);
    }
    else if(node->getParent()->getParent()->getTag() == kTagFlashCH)
    {
        node->getParent()->getParent()->removeChild(node->getParent());
        removeAllAnimationsInDataPool(CHU, true);
        
        CJAnimation *chu = playAnimationWithCommonPath(CHU, CJUtils::getStringFormatInteger("e002_common_diary_flash_ch%02d_loop", m_currentFlashIndexCH), -1, kDepth2_questions, getChildByTag(kTagDiaryLayer));
        chu->setPosition(getChildByTag(kTagStickerCH)->getPosition());
        chu->setScale(0);
        chu->setTag(kTagFlashCH);
        
        changeSelectedSticker(getChildByTag(kTagFlashCH-5), false);
    }
    else if(node->getParent()->getParent()->getTag() == kTagFlashGB)
    {
        node->getParent()->getParent()->removeChild(node->getParent());
        removeAllAnimationsInDataPool(GRUMBIE, true);
        
        CJAnimation *grumbie = playAnimationWithCommonPath(GRUMBIE, CJUtils::getStringFormatInteger("e002_common_diary_flash_gb%02d_loop", m_currentFlashIndexGB), -1, kDepth2_questions, getChildByTag(kTagDiaryLayer));
        grumbie->setPosition(getChildByTag(kTagStickerGB)->getPosition());
        grumbie->setScale(0);
        grumbie->setTag(kTagFlashGB);
        
        changeSelectedSticker(getChildByTag(kTagFlashGB-5), false);
    }
}

void E002_Base_P420_Diary::setDrawBG(int index)
{
    CJSprite* diaryLayer = CJSprite::create();
    
    diaryLayer->setTextureRect(CCRectMake(0, 0, winSize.width, winSize.height));
	diaryLayer->setColor(ccWHITE);
	diaryLayer->setPosition(winCenter);
	addChild(diaryLayer, kDepth0_backImage, kTagDiaryLayer);
    
    CJSprite* drawBG = CJSprite::create();
    
    drawBG->setTextureRect(CCRectMake(0, 0, winSize.width, winSize.height));
	drawBG->setColor(ccWHITE);
	drawBG->setPosition(winCenter);
	diaryLayer->addChild(drawBG, kDepth0_backImage, kTagDrawBG);
    
    CJSprite* drawLine = CJSprite::createWithFullPath(getContentID(CJUtils::getStringFormatInteger("_p420_img_line%02d.png", index - DIARY_1)).c_str());
	drawLine->setPosition(winCenter);
	drawBG->addChild(drawLine, kDepth0_backImage, kTagDrawLine);
}

CCImage* E002_Base_P420_Diary::getSaveImage()
{
	CCNode* drawBG = getChildByTag(kTagDiaryLayer)->getChildByTag(kTagDrawBG);
	CCSize imgSize = drawBG->getContentSize();
	CCRenderTexture* render = CCRenderTexture::create(imgSize.width, imgSize.height);

	render->begin();
	drawBG->visit();
	render->end();
    
	return render->newCCImage();
}

CCImage* E002_Base_P420_Diary::getCaptureImage()
{
    CCNode* diaryLayer = getChildByTag(kTagDiaryLayer);
	CCSize imgSize = diaryLayer->getContentSize();
	CCRenderTexture* render = CCRenderTexture::create(imgSize.width, imgSize.height);
    
	render->begin();
    diaryLayer->visit();
	render->end();
    
	return render->newCCImage();
}

#pragma mark - menu callback func




void E002_Base_P420_Diary::setStickerSoundFileName(std::string names[])
{
	for (int i = 0; i < 8; i++) {
		m_vStickerSoundFileName.push_back(names[i]);
	}
}

void E002_Base_P420_Diary::speakStickerSound(int index)
{
	if (index < m_vStickerSoundFileName.size() && m_vStickerSoundFileName[index] != "") {
		playEffect(m_vStickerSoundFileName[index]);

		CCNode* drawBG = getChildByTag(kTagDiaryLayer)->getChildByTag(kTagDrawBG);
		E002_Base_DrawLayer* drawLayer = (E002_Base_DrawLayer*)drawBG->getChildByTag(kTagDrawLayer);
		drawLayer->addStempSoundEffect(getFilePath("snd",m_vStickerSoundFileName[index]));
	}
}

#pragma mark - private func

ccColor3B E002_Base_P420_Diary::getColor(int selectIndex)
{
	return ccc3(colorRGB[selectIndex][0], colorRGB[selectIndex][1], colorRGB[selectIndex][2]);
}

void E002_Base_P420_Diary::setPositionForParent(CCNode* parent, CCNode* child)
{
	CCSize parentSize = parent->getContentSize();
	CCPoint parentAnchor = parent->getAnchorPoint();
	CCPoint childModifyPoint = ccpSub(child->getPosition(), parent->getPosition());
	child->setPosition(
			ccp(
					childModifyPoint.x+parentSize.width*parentAnchor.x,
					childModifyPoint.y+parentSize.height*parentAnchor.y
			)
	);
}

void E002_Base_P420_Diary::finishAction()
{
	m_isAction = false;
}

void E002_Base_P420_Diary::stampBoxOn()
{
	m_isStampBoxOn = true;
	finishAction();
}

void E002_Base_P420_Diary::stampBoxOff()
{
	m_isStampBoxOn = false;
	finishAction();
}


void E002_Base_P420_Diary::addDimm()
{
	if (m_selectNode) {
		if (m_selectNode->getTag() == ToolBoxMenuButton::Stamp) {
			m_isStampBoxOn = true;
		} else if (m_selectNode->getTag() <= ToolBoxMenuButton::Eraser) {
			m_selectNode->runAction(
					CCSequence::create(
							CCEaseSineInOut::create(
									CCJumpTo::create(
											0.4f,
											ccp(
													m_selectNode->getPosition().x,
													m_toolBoxDefaultHeight
											),
											-20,
											1
									)
							),
							CCCallFunc::create(
									this,
									callfunc_selector(E002_Base_P420_Diary::finishAction)
							),
							NULL
					)
			);
		}
	}

	CCSprite* m_Dim =  CCSprite::create();
	m_Dim->setTextureRect(CCRectMake(0, 0, winSize.width, winSize.height));
	m_Dim->setColor(ccBLACK);
	m_Dim->setOpacity(0);
	m_Dim->setAnchorPoint(CCPointZero);
	m_Dim->setPosition(CCPointZero);
	m_Dim->setTag(kTagDimm);
	addChild(m_Dim);

	m_Dim->runAction(
			CCSequence::create(
					CCDelayTime::create(0.5f),
					CCEaseSineOut::create(CCFadeTo::create(0.3f, 210)),
					NULL
			)
	);
}

void E002_Base_P420_Diary::_saveButtonSelect()
{
    stopAllNarration();
    playCommonNarration("e002_common_snd_btn_03_as.mp3");
}


void E002_Base_P420_Diary::saveButtonSelect()
{
    playCommonEffect("e002_common_diary_sfx_camera.mp3");
    
    CCImage* saveImage = getSaveImage();
    CCImage* captureImage = getCaptureImage();

    std::string result =  makeFileToFlashInfo();

    std::string savePath = CJUtils::getLMSFileName(m_currentDiary, eFileType_Extend, result);
    std::string tempPath = savePath;
    
    CCLog("savePath %s", savePath.c_str());
	saveImage->saveToFile(savePath.append("_bg.png").c_str());
    captureImage->saveToFile(tempPath.append("_capture.png").c_str());
    
    CJUtils::saveLMSFile();
  
    showCompletePopup();

}

std::string E002_Base_P420_Diary::makeFileToFlashInfo()
{
    std::string result;
    
    for (int i = 0; i < m_showingAnimation->size(); i++)
    {
        result.append(m_showingAnimation->at(i)->getAniName());
        result.append("/");
        result.append(CJUtils::getStringFormatInteger("%d", m_showingAnimation->at(i)->getNumber()));
        result.append("/");
        result.append(cocos2d::CCString::createWithFormat("%f", m_showingAnimation->at(i)->getPositionX())->getCString());
        result.append("/");
        result.append(cocos2d::CCString::createWithFormat("%f", m_showingAnimation->at(i)->getPositionY())->getCString());
        
        if (i < m_showingAnimation->size() - 1)
        {
            result.append("%");
        }
    }
    
    CCLog("makeFileToFlashInfo result %s", result.c_str());
    return result;
}

void E002_Base_P420_Diary::onNarrationFinishedCallback(std::string fileName)
{
    if (fileName == "e002_common_snd_btn_03_as.mp3")
    {
        saveButtonSelect();
    }
}

void E002_Base_P420_Diary::makeBrushColors()
{
    CJSprite *colorBG = CJPsdParser::getPsdCommonSprite("e002_common_diary_img_color_bg", m_psdDictionary);
    addChild(colorBG, kDepth5_particle, kTagColorBG);
    
    CCArray* temp = CCArray::create();
    
    const int MAX_ITEMS = 23;

    float itemWidth = 0;
    float itemHeight = 0;
    
    for (int i = MAX_ITEMS; i > -1; i--)
    {
        CJSprite *colorN = CJSprite::createWithCommonPath(CJUtils::getStringFormatInteger("e002_common_diary_img_color%02d_n", i).append(".png") .c_str());
        
        CCMenuItemSprite* colorItem = CCMenuItemSprite::create(colorN,
                                                               colorN,
                                                               this,
                                                               menu_selector(E002_Base_P420_Diary::selectBrushColor));
        
        colorItem->setTag(kTagColor+i);
        colorItem->setPosition(ccp(49, (MAX_ITEMS - i)*74 + (colorItem->getContentSize().height / 2) + 25));
        
        temp->addObject(colorItem);

        itemWidth = colorItem->getContentSize().width;
        itemHeight = colorItem->getContentSize().height;
        
        if(i == 0)
        {
            m_selectColor = colorItem;
            colorN->setTexture(CCTextureCache::sharedTextureCache()->
                               addImage(CJUtils::getInstance()->getCommonFilePath("img",CJUtils::getStringFormatInteger("e002_common_diary_img_color%02d_s",i)).append(".png").c_str()));
        }
    }
    
    CJMenu *colors = CJMenu::createWithArray(temp);
    colors->setPosition(CCPointZero);

    CCLayer *container = CCLayer::create();
    container->setTag(kTagContainer);
    container->addChild(colors);
    container->setContentSize(ccp(itemWidth, MAX_ITEMS * itemHeight + (getChildByTag(kTagColorBG)->getContentSize().height/2 + 80)));
    
    CCSize size = CCSizeMake(colorBG->getContentSize().width, colorBG->getContentSize().height);
    extension::CCScrollView *scrollView = extension::CCScrollView::create(size, container);
    scrollView->setDirection(extension::kCCScrollViewDirectionVertical);
    scrollView->setTag(kTagScrollView);
    scrollView->setContentOffset(ccp(0, -1390), true);
    scrollView->setContentOffsetInDuration(CCPointZero, 5.0f);
    scrollView->setBounceable(true);

    colorBG->addChild(scrollView);
    
    colorBG->setPosition(ccp(colorBG->getPositionX() - colorBG->getContentSize().width, colorBG->getPositionY()));

    
}

void E002_Base_P420_Diary::selectBrushColor(CCNode *sender)
{
    if (m_isToolBoxMode || m_isAction)
    {
        return;
    }
    
    if (m_isStampBoxOn)
    {
        hideStampBox();
    }

    CCNode *selNormalImg = m_selectColor->getNormalImage();
    ((CJSprite*)selNormalImg)->setTexture(CCTextureCache::sharedTextureCache()->
                       addImage(CJUtils::getInstance()->getCommonFilePath("img",CJUtils::getStringFormatInteger("e002_common_diary_img_color%02d_n",m_selectColor->getTag()-kTagColor)).append(".png").c_str()));
    
	CCNode* node = (CCNode*)sender;
    m_selectColor = (CCMenuItemSprite*)node;
    
    E002_Base_DrawLayer* drawLayer = (E002_Base_DrawLayer*)getChildByTag(kTagDiaryLayer)->getChildByTag(kTagDrawBG)->getChildByTag(kTagDrawLayer);
	   
    drawLayer->setDraweable(false);
    drawLayer->setStampMode(false);
    drawLayer->setEraseMode(false);

    drawLayer->setBrushStroke(1);
    
    selNormalImg = m_selectColor->getNormalImage();
    ((CJSprite*)selNormalImg)->setTexture(CCTextureCache::sharedTextureCache()->
                                          addImage(CJUtils::getInstance()->getCommonFilePath("img",CJUtils::getStringFormatInteger("e002_common_diary_img_color%02d_s",m_selectColor->getTag()-kTagColor)).append(".png").c_str()));

    
    drawLayer->setBrushColor(getColor(sender->getTag()-kTagColor));
	
}

void E002_Base_P420_Diary::selectCrayonTool()
{
    if (m_isAction) {
        return;
    }
    
    if (m_isStampBoxOn)
    {
        hideStampBox();
    }
    
    E002_Base_DrawLayer* drawLayer = (E002_Base_DrawLayer*)getChildByTag(kTagDiaryLayer)->getChildByTag(kTagDrawBG)->getChildByTag(kTagDrawLayer);
    
    drawLayer->setDraweable(false);
    drawLayer->setStampMode(false);
    drawLayer->setEraseMode(false);
    drawLayer->setBrushStroke(1);
    drawLayer->setDrawSound("e002_common_diary_sfx_write02.mp3");
    
    m_isToolBoxMode = true;
    
    if(m_selectNode != NULL)
        m_selectNode->runAction(getUnselectToolAction());

    CJSprite *crayon =  (CJSprite*)getChildByTag(kTagToolBG)->getChildByTag(kTagToolCrayon);
    m_selectNode = crayon;

    m_selectNode->runAction(getSelectToolAction());
    
    m_currentBrushStyle = CRAYON;
    
    replaceBrush();
}

void E002_Base_P420_Diary::selectPenTool()
{
    if (m_isAction) {
        return;
    }
    
    if (m_isStampBoxOn)
    {
        hideStampBox();
    }
    
    E002_Base_DrawLayer* drawLayer = (E002_Base_DrawLayer*)getChildByTag(kTagDiaryLayer)->getChildByTag(kTagDrawBG)->getChildByTag(kTagDrawLayer);
    
    drawLayer->setDraweable(false);
    drawLayer->setStampMode(false);
    drawLayer->setEraseMode(false);
    drawLayer->setBrushStroke(1);
    drawLayer->setDrawSound("e002_common_diary_sfx_write01.mp3");

    m_isToolBoxMode = true;
    
    if(m_selectNode != NULL)
        m_selectNode->runAction(getUnselectToolAction());

    CJSprite *pen =  (CJSprite*)getChildByTag(kTagToolBG)->getChildByTag(kTagToolPen);
    m_selectNode = pen;
    
    m_selectNode->runAction(getSelectToolAction());

    m_currentBrushStyle = PEN;

    replaceBrush();
}

void E002_Base_P420_Diary::selectPencilTool()
{
    if (m_isAction) {
        return;
    }
    
    if (m_isStampBoxOn)
    {
        hideStampBox();
    }
    
    E002_Base_DrawLayer* drawLayer = (E002_Base_DrawLayer*)getChildByTag(kTagDiaryLayer)->getChildByTag(kTagDrawBG)->getChildByTag(kTagDrawLayer);
    
    drawLayer->setDraweable(false);
    drawLayer->setStampMode(false);
    drawLayer->setEraseMode(false);
    drawLayer->setBrushStroke(1);
    drawLayer->setDrawSound("e002_common_diary_sfx_write03.mp3");

    m_isToolBoxMode = true;
    
    if(m_selectNode != NULL)
        m_selectNode->runAction(getUnselectToolAction());

    CJSprite *pencil =  (CJSprite*)getChildByTag(kTagToolBG)->getChildByTag(kTagToolPencil);
    m_selectNode = pencil;

    m_selectNode->runAction(getSelectToolAction());

    m_currentBrushStyle = PENCIL;
    
    replaceBrush();
}

void E002_Base_P420_Diary::selectEraseTool()
{
    if (m_isAction) {
        return;
    }
    
    if (m_isStampBoxOn)
    {
        hideStampBox();
    }
    
    m_isToolBoxMode = true;
    
    if(m_selectNode != NULL)
        m_selectNode->runAction(getUnselectToolAction());

    CJSprite *eraser =  (CJSprite*)getChildByTag(kTagToolBG)->getChildByTag(kTagToolEraser);
    m_selectNode = eraser;
    
    eraser->runAction(CCSequence::create(getSelectToolAction(),
                                         CCCallFunc::create(this,callfunc_selector(E002_Base_P420_Diary::finishAction)),
                                         NULL
                                         ));
    
    E002_Base_DrawLayer *drawLayer = (E002_Base_DrawLayer*)getChildByTag(kTagDiaryLayer)->getChildByTag(kTagDrawBG)->getChildByTag(kTagDrawLayer);
    drawLayer->setStampMode(false);
    drawLayer->setEraseMode(true);
    drawLayer->setBrushStroke(1);
    drawLayer->setDrawSound("e002_common_diary_sfx_eraser.mp3");

}

void E002_Base_P420_Diary::selectStamp(CCNode *sender)
{
    if (m_isAction) {
        return;
    }
    
    m_isAction = true;
    
    m_isToolBoxMode = true;
    
    if(m_selectNode != NULL)
        m_selectNode->runAction(getUnselectToolAction());

    E002_Base_DrawLayer *drawLayer = (E002_Base_DrawLayer*)getChildByTag(kTagDiaryLayer)->getChildByTag(kTagDrawBG)->getChildByTag(kTagDrawLayer);
    
    CCNode* node = (CCNode*)sender;
    
	if (m_isStampBoxOn)
    {
        playEffect(getContentID(CJUtils::getStringFormatInteger("_p410_snd_stamp_%02d.mp3", node->getTag()-kTagStamp + 1)));

		CJSprite* stamp = CJSprite::createWithFullPath(getContentID(CJUtils::getStringFormatInteger("_p420_img_stamp%02d_big", node->getTag()-kTagStamp).append(".png")).c_str());
        
		drawLayer->setStampNode(stamp);
        drawLayer->addStempSoundEffect(getFilePath("snd", getContentID(CJUtils::getStringFormatInteger("_p410_snd_stamp_%02d.mp3", node->getTag()-kTagStamp + 1))));
        
		node->runAction(
                        CCSequence::create(
                                           CCEaseSineOut::create(CCScaleTo::create(0.2f, 1.1)),
                                           CCEaseSineIn::create(CCScaleTo::create(0.2f, 1)),
                                           CCCallFunc::create(this, callfunc_selector(E002_Base_P420_Diary::finishAction)),
                                           NULL
                                           )
                        );
        
		hideStampBox();
	}
    
	m_isAction = true;
    
    
}

void E002_Base_P420_Diary::makeTools()
{
    CJSprite *toolBG = CJPsdParser::getPsdCommonSprite("e002_common_diary_img_tool_bg", m_psdDictionary);
    addChild(toolBG, kDepth4_title+1, kTagToolBG);

    CJSprite *eraser = CJPsdParser::getPsdCommonSprite("e002_common_diary_img_eraser", m_psdDictionary);
    toolBG->addChildIgnoreParent(eraser, kDepth1_actors , kTagToolEraser);

    CJSprite *stamp = CJPsdParser::getPsdCommonSprite("e002_common_diary_img_stamp", m_psdDictionary);
    toolBG->addChildIgnoreParent(stamp, kDepth1_actors, kTagToolStamp);

    CJSprite *crayon = CJPsdParser::getPsdCommonSprite("e002_common_diary_img_crayon", m_psdDictionary);
    toolBG->addChildIgnoreParent(crayon, kDepth1_actors, kTagToolCrayon);

    CJSprite *pen = CJPsdParser::getPsdCommonSprite("e002_common_diary_img_pen", m_psdDictionary);
    toolBG->addChildIgnoreParent(pen, kDepth1_actors, kTagToolPen);
    m_selectNode = pen;
    m_selectNode->runAction(CCSequence::create(CCDelayTime::create(2.0f),
                                               CCMoveBy::create(0.2, ccp(0, 40)),
                                               //getSelectToolAction(),
                                               NULL));

    CJSprite *pencil = CJPsdParser::getPsdCommonSprite("e002_common_diary_img_pencil", m_psdDictionary);
    toolBG->addChildIgnoreParent(pencil, kDepth1_actors, kTagToolPencil);

    CJSprite *saveN = CJSprite::createWithCommonPath("e002_common_diary_btn_save_n.png");
    CJSprite *saveS = CJSprite::createWithCommonPath("e002_common_diary_btn_save_s.png");
    
    CCMenuItemSprite* saveBtn = CCMenuItemSprite::create(saveN,
                                                         saveS,
                                                         this,
                                                         menu_selector(E002_Base_P420_Diary::_saveButtonSelect));
    
    saveBtn->setTag(kTagSave);
    saveBtn->setPosition(CJPsdParser::getPsdPosition("e002_common_diary_btn_save_n", m_psdDictionary));

    CJMenu *btn = CJMenu::create(saveBtn,NULL);
    btn->setPosition(CCPointZero);
    btn->setTag(kTagSaveMenu);
    
    toolBG->addChildIgnoreParent(btn, kDepth1_actors);
    
    toolBG->setPosition(ccp(toolBG->getPositionX(), -getChildByTag(kTagToolBG)->getChildByTag(kTagToolCrayon)->getContentSize().height));

}

CCActionInterval* E002_Base_P420_Diary::getSelectToolAction()
{
    playCommonEffect("e002_common_sfx_btn_02.mp3");
    
    return CCMoveBy::create(0.2, ccp(0, 40));
}

CCActionInterval* E002_Base_P420_Diary::getUnselectToolAction()
{
    return CCMoveTo::create(0.2, ccp(m_selectNode->getPositionX(), CJPsdParser::getPsdPosition("e002_common_diary_img_eraser", m_psdDictionary).y));
}

void E002_Base_P420_Diary::makeStampBox()
{
    CJSprite *box = CJPsdParser::getPsdCommonSprite("e002_common_diary_img_stamp_bg", m_psdDictionary);
    
    CCArray *temp = new CCArray();
    
    for (int i = 0; i < 8; i++)
    {
        CJSprite *stampN = CJSprite::createWithFullPath(getContentID(CJUtils::getStringFormatInteger("_p420_img_stamp%02d_n", i).append(".png")).c_str());
        CJSprite *stamps = CJSprite::createWithFullPath(getContentID(CJUtils::getStringFormatInteger("_p420_img_stamp%02d_s", i).append(".png")).c_str());
        
        CCMenuItemSprite* colorItem = CCMenuItemSprite::create(stampN,
                                                               stamps,
                                                               this,
                                                               menu_selector(E002_Base_P420_Diary::selectStamp));
        
        colorItem->setTag(kTagStamp+i);
        colorItem->setPosition(CJPsdParser::getPsdPosition(CJUtils::getStringFormatInteger("e002_common_diary_img_stamp%02d_n", i), m_psdDictionary));
        
        temp->addObject(colorItem);
        
    }
    
    CJMenu *stamps = CJMenu::createWithArray(temp);
    stamps->setPosition(CCPointZero);
    
    box->addChildIgnoreParent(stamps);
    
    box->setScale(0);
    box->setAnchorPointWithoutPosition(ccp(0.5,0));
    
    addChild(box, kDepth5_particle, kTagStampBox);


}

void E002_Base_P420_Diary::showStampBox()
{
    if (m_isAction) {
        return;
    }
    
    if(m_selectNode != NULL)
        m_selectNode->runAction(getUnselectToolAction());

    E002_Base_DrawLayer *drawLayer = (E002_Base_DrawLayer*)getChildByTag(kTagDiaryLayer)->getChildByTag(kTagDrawBG)->getChildByTag(kTagDrawLayer);
    drawLayer->setStampMode(true);
    drawLayer->setEraseMode(false);
    drawLayer->setBrushStroke(0);
    drawLayer->setStampNode(NULL);
    
    m_isAction = true;
    m_isStampBoxOn = true;
    
    playCommonEffect("e002_common_sfx_btn_01.mp3");
    
    getChildByTag(kTagStampBox)->runAction(CCSequence::create(CCEaseElasticOut::create(CCScaleTo::create(0.5, 1.0)),
                                                              CCCallFunc::create(this, callfunc_selector(E002_Base_P420_Diary::finishAction)),
                                                              NULL));
}

void E002_Base_P420_Diary::hideStampBox()
{
    m_isStampBoxOn = false;
    getChildByTag(kTagStampBox)->setScale(0.2f, 0);
}

void E002_Base_P420_Diary::makeBrushBox()
{
    CJSprite *brushBox = CJPsdParser::getPsdCommonSprite("e002_common_diary_img_brush_bg", m_psdDictionary);
    
    CCArray *temp = new CCArray();
    
    for (int i = 0; i < 3; i++)
    {
        CJSprite *brushN = CJSprite::createWithCommonPath(CJUtils::getStringFormatInteger("e002_common_diary_img_brush%02d_n", i).append(".png").c_str());
        CJSprite *brushS = CJSprite::createWithCommonPath(CJUtils::getStringFormatInteger("e002_common_diary_img_brush%02d_s", i).append(".png").c_str());
        
        CCMenuItemSprite* brushItem = CCMenuItemSprite::create(brushN,
                                                               brushS,
                                                               this,
                                                               menu_selector(E002_Base_P420_Diary::selectBrushSize));
        
        brushItem->setTag(kTagBrush+i);
        brushItem->setPosition(CJPsdParser::getPsdPosition(CJUtils::getStringFormatInteger("e002_common_diary_img_brush%02d_n", i), m_psdDictionary));
        
        temp->addObject(brushItem);
        
        if (i == 1)
        {
            brushItem->selected();
        }
    }
    
    CJSprite *indexN = CJSprite::createWithCommonPath("e002_common_diary_btn_index_n.png");
    CJSprite *indexS = CJSprite::createWithCommonPath("e002_common_diary_btn_index_s.png");
    
    CCMenuItemSprite* indexBtn = CCMenuItemSprite::create(indexN,
                                                          indexS,
                                                          this,
                                                          menu_selector(E002_Base_P420_Diary::selectIndexBtn));
    
    indexBtn->setTag(kTagIndex);
    indexBtn->setPosition(CJPsdParser::getPsdPosition("e002_common_diary_btn_index_n", m_psdDictionary));
    
    CCMenu *indexMenu = CCMenu::create(indexBtn, NULL);
    indexMenu->setPosition(CCPointZero);
    indexMenu->setTag(kTagIndexMenu);
    addChild(indexMenu, kDepth5_particle);
    
    CJMenu *brushes = CJMenu::createWithArray(temp);
    brushes->setPosition(CCPointZero);
    brushes->setTag(kTagBrushMenu);
    
    brushBox->addChildIgnoreParent(brushes);
    
    addChild(brushBox, kDepth5_particle, kTagBrushBox);
    
    brushBox->setPosition(ccp(brushBox->getPositionX() - brushBox->getContentSize().width, brushBox->getPositionY()));
}

void E002_Base_P420_Diary::selectBrushSize(cocos2d::CCNode *sender)
{
    m_isToolBoxMode = true;
    m_currentBrushSize = sender->getTag() - kTagBrush;
    
    for (int i = 0; i < sender->getParent()->getChildrenCount(); i++)
    {
        ((CCMenuItemSprite*)sender->getParent()->getChildren()->objectAtIndex(i))->unselected();
    }
    
    ((CCMenuItemSprite*)sender)->selected();
    
    replaceBrush();
}

void E002_Base_P420_Diary::showTools()
{
    if (!m_showTools)
    {
        m_showTools = true;
        
        getChildByTag(kTagIndexMenu)->runAction(CCMoveBy::create(0.3f, ccp(getChildByTag(kTagBrushBox)->getContentSize().width, 0)));
        getChildByTag(kTagBrushBox)->runAction(CCMoveBy::create(0.3f, ccp(getChildByTag(kTagBrushBox)->getContentSize().width, 0)));
        getChildByTag(kTagColorBG)->runAction(CCMoveBy::create(0.3f, ccp(getChildByTag(kTagColorBG)->getContentSize().width, 0)));
        getChildByTag(kTagToolBG)->runAction(CCMoveBy::create(0.3f, ccp(0, getChildByTag(kTagToolBG)->getChildByTag(kTagToolCrayon)->getContentSize().height)));
        
        for (int i = kTagStickerAS; i <= kTagStickerAR; i++)
        {
            if(getChildByTag(i) != NULL)
            {
                getChildByTag(i)->runAction(CCMoveBy::create(0.3, ccp(-getChildByTag(i)->getContentSize().width, 0)));
            }
        }
    }
}

void E002_Base_P420_Diary::showToolsAfterDelay()
{
    CJUtils::performSelector(this, callfunc_selector(E002_Base_P420_Diary::showTools), 1.0f);
}

void E002_Base_P420_Diary::stopToShowTools()
{
    stopAllActions();
}

void E002_Base_P420_Diary::hideTools()
{
    if (m_showTools)
    {
        m_showTools = false;
        
        getChildByTag(kTagIndexMenu)->runAction(CCMoveBy::create(0.3f, ccp(-getChildByTag(kTagBrushBox)->getContentSize().width, 0)));
        getChildByTag(kTagBrushBox)->runAction(CCMoveBy::create(0.3f, ccp(-getChildByTag(kTagBrushBox)->getContentSize().width, 0)));
        getChildByTag(kTagColorBG)->runAction(CCMoveBy::create(0.3f, ccp(-getChildByTag(kTagColorBG)->getContentSize().width, 0)));
        getChildByTag(kTagToolBG)->runAction(CCMoveBy::create(0.3f, ccp(0, -getChildByTag(kTagToolBG)->getChildByTag(kTagToolCrayon)->getContentSize().height)));
        
        for (int i = kTagStickerAS; i <= kTagStickerAR; i++)
        {
            if(getChildByTag(i) != NULL)
            {
                getChildByTag(i)->runAction(CCMoveBy::create(0.3, ccp(getChildByTag(i)->getContentSize().width, 0)));
            }
        }
    }
    
}

void E002_Base_P420_Diary::makeStickers()
{
    int count = 0;
    
    for (int i = 0; i < mCharacterName->size(); i++)
    {
        CJSprite *sticker;
        
        if(strcmp(mCharacterName->at(i), ANISON) == 0 )
        {
            sticker = CJSprite::createWithCommonPath("e002_common_diary_img_sticker00_n.png");
            addChild(sticker, kDepth1_actors, kTagStickerAS);
        }
        else if(strcmp(mCharacterName->at(i), CHU) == 0 )
        {
            sticker = CJSprite::createWithCommonPath("e002_common_diary_img_sticker01_n.png");
            addChild(sticker, kDepth1_actors, kTagStickerCH);
        }
        else if(strcmp(mCharacterName->at(i), BOOMBOOM) == 0 )
        {
            sticker = CJSprite::createWithCommonPath("e002_common_diary_img_sticker02_n.png");
            addChild(sticker, kDepth1_actors, kTagStickerBB);
        }
        else if(strcmp(mCharacterName->at(i), GRUMBIE) == 0 )
        {
            sticker = CJSprite::createWithCommonPath("e002_common_diary_img_sticker03_n.png");
            addChild(sticker, kDepth1_actors, kTagStickerGB);
        }
        else if(strcmp(mCharacterName->at(i), ALPHAROBOT) == 0 )
        {
            sticker = CJSprite::createWithCommonPath("e002_common_diary_img_sticker04_n.png");
            addChild(sticker, kDepth1_actors, kTagStickerAR);
        }
        
        if (count == 0)
        {
            sticker->setPosition(CJPsdParser::getPsdPosition("e002_common_diary_img_sticker00_n", m_psdDictionary));
        }
        else if (count == 1)
        {
            sticker->setPosition(CJPsdParser::getPsdPosition("e002_common_diary_img_sticker01_n", m_psdDictionary));
        }
        else if (count == 2)
        {
            sticker->setPosition(CJPsdParser::getPsdPosition("e002_common_diary_img_sticker02_n", m_psdDictionary));
        }
        else if (count == 3)
        {
            sticker->setPosition(CJPsdParser::getPsdPosition("e002_common_diary_img_sticker03_n", m_psdDictionary));
        }
        else if (count == 4)
        {
            sticker->setPosition(CJPsdParser::getPsdPosition("e002_common_diary_img_sticker04_n", m_psdDictionary));
        }
        
        sticker->setPosition(ccp(sticker->getPositionX() + sticker->getContentSize().width, sticker->getPositionY()));

        count++;
    }
    
}

void E002_Base_P420_Diary::changeSelectedSticker(CCNode *node, bool isSelectd)
{

    if (isSelectd)
    {
        for (int i = kTagStickerAS; i <= kTagStickerAR; i++)
        {
            if(node->getTag() == i)
            {
                ((CJSprite*)node)->setTexture(CCTextureCache::sharedTextureCache()->
                                              addImage(CJUtils::getInstance()->getCommonFilePath("img",CJUtils::getStringFormatInteger("e002_common_diary_img_sticker%02d_s",i-kTagStickerAS)).append(".png").c_str()));
            }
        }
    }
    else
    {
        for (int i = kTagStickerAS; i <= kTagStickerAR; i++)
        {
            if(node->getTag() == i)
            {
                ((CJSprite*)node)->setTexture(CCTextureCache::sharedTextureCache()->
                                              addImage(CJUtils::getInstance()->getCommonFilePath("img",CJUtils::getStringFormatInteger("e002_common_diary_img_sticker%02d_n",i-kTagStickerAS)).append(".png").c_str()));
            }
        }
    }
    


}

void E002_Base_P420_Diary::replaceBrush()
{
    std::string brushFilePath;
    
    switch (m_currentBrushStyle)
    {
        case PEN:
            switch (m_currentBrushSize)
            {
                case 0:
                    brushFilePath = "e002_common_diary_img_pen_brush00.png";
                    break;
                case 1:
                    brushFilePath = "e002_common_diary_img_pen_brush01.png";
                    break;
                case 2:
                    brushFilePath = "e002_common_diary_img_pen_brush02.png";
                    break;
                default:
                    break;
            }
            
            break;
            
        case PENCIL:
            switch (m_currentBrushSize)
            {
            case 0:
                brushFilePath = "e002_common_diary_img_pencil_brush00.png";
                break;
            case 1:
                brushFilePath = "e002_common_diary_img_pencil_brush01.png";
                break;
            case 2:
                brushFilePath = "e002_common_diary_img_pencil_brush02.png";
                break;
            default:
                break;
            }
            
            break;
            
        case CRAYON:
            switch (m_currentBrushSize)
            {
            case 0:
                brushFilePath = "e002_common_diary_img_crayon_brush00.png";
                break;
            case 1:
                brushFilePath = "e002_common_diary_img_crayon_brush01.png";
                break;
            case 2:
                brushFilePath = "e002_common_diary_img_crayon_brush02.png";
                break;
            default:
                break;
            }
            
            break;
        default:
            break;
    }
    
    
    E002_Base_DrawLayer* drawLayer = (E002_Base_DrawLayer*)getChildByTag(kTagDiaryLayer)->getChildByTag(kTagDrawBG)->getChildByTag(kTagDrawLayer);
    drawLayer->changeBrush(getCommonFilePath("img",brushFilePath));
    
    if(drawLayer->getEraseMode())
        drawLayer->setEraseMode(true);
}

std::string E002_Base_P420_Diary::getContentID(std::string resource)
{
    return CJUtils::getInstance()->getContentID().append(resource);
}

void E002_Base_P420_Diary::addDrawingObserver()
{
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(E002_Base_P420_Diary::showToolsAfterDelay),
                                                                  E002_NOTIFICATION_DIARY_DRAWING_FINISHCALL,
                                                                  NULL);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(E002_Base_P420_Diary::stopToShowTools),
                                                                  E002_NOTIFICATION_DIARY_DRAWING_STARTCALL,
                                                                  NULL);

}

void E002_Base_P420_Diary::removeDrawingObserver()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, E002_NOTIFICATION_DIARY_DRAWING_FINISHCALL);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, E002_NOTIFICATION_DIARY_DRAWING_STARTCALL);

}

void E002_Base_P420_Diary::sendPopupObject(E002_Base_P420_CompletePopup *popup)
{
    popup->setFlashDataPool(getAllDatapool());
}


