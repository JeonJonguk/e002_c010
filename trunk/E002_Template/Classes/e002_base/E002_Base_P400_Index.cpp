//
//  E002_Base_P400_Index.cpp
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 5. 31..
//
//

#include "E002_Base_P400_Index.h"
#include "E002_Base_Define.h"
//#include "E001_C010_P000_Info.h"

enum {
    kTagPicture = 500,
};

#pragma mark - init

E002_Base_P400_Index::E002_Base_P400_Index()
{
    m_psdDictionary = new CCDictionary();
    m_completeDiary = new std::vector<bool>();

}

E002_Base_P400_Index::~E002_Base_P400_Index()
{
    CC_SAFE_DELETE(m_psdDictionary);
}



bool E002_Base_P400_Index::init()
{
    if (!CJLayer::initWithColor(ccc4(255, 255, 255, 255))) {
		return false;
	}

    return true;
}


void E002_Base_P400_Index::onEnter()
{
    CJLayer::onEnter();
}

void E002_Base_P400_Index::onExit()
{
    removeSoundObserver();
    CJLayer::onExit();
}


#pragma mark - touch

bool E002_Base_P400_Index::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint tp = pTouch->getLocation();
    
    for (int i = kTagPicture; i <= kTagPicture + 4; i++)
    {
        if(getChildByTag(i) != NULL && CJUtils::hitTestPoint(getChildByTag(i), tp, false))
        {
            CJUtils::getInstance()->setUserDefaultIntegerForKey(E002_USERDEFAULT_DIARY_NUMBER, i - kTagPicture + DIARY_1);

            if (m_completeDiary->at(i - kTagPicture))
            {
                showCompletePopup();
            }
            else
            {
                showDiaryIntro();
            }
        }
    }
    
    return false;
}

void E002_Base_P400_Index::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void E002_Base_P400_Index::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

#pragma mark - load view

void E002_Base_P400_Index::onViewLoad()
{
    CJLayer::onViewLoad();
    
    CJPsdParser::parseToPsdJSON("e002_common_diary_p400_index.json", &m_psdDictionary, true);

    CJSprite* bg = CJPsdParser::getPsdCommonSprite("e002_common_diary_img_index_bg", m_psdDictionary);
    addChild(bg, kDepth1_actors);
    
    
    showPictures();
    
    setTouchEnableCJLayer(this, false);
    
    CJMultimedia::getInstance()->playBGM(getCommonFilePath("snd", "e002_common_snd_bgm_diary.mp3"), true);


}

void E002_Base_P400_Index::onViewLoaded()
{
    CJLayer::onViewLoaded();
    E002_Base_Navigation::initWithNavigationType(this, "",
                                                 eNavigationType_Menu);
    E002_Base_Navigation::showNavigation();

    setAnimationCommonFile("e002_common_diary_flash_as_sheets.json", "e002_common_diary_flash_as_animations.json", ANISON);
    setAnimationCommonFile("e002_common_diary_flash_ar_sheets.json", "e002_common_diary_flash_ar_animations.json", ALPHAROBOT);
    setAnimationCommonFile("e002_common_diary_flash_bb_sheets.json", "e002_common_diary_flash_bb_animations.json", BOOMBOOM);
    setAnimationCommonFile("e002_common_diary_flash_gb_sheets.json", "e002_common_diary_flash_gb_animations.json", GRUMBIE);
    setAnimationCommonFile("e002_common_diary_flash_ch_sheets.json", "e002_common_diary_flash_ch_animations.json", CHU);

    animationManagerParseStart();

}

void E002_Base_P400_Index::animationManagerParseComplete()
{
    setTouchEnableCJLayer(this, true);
}

void E002_Base_P400_Index::showPictures()
{
    for (int i = 0 ; i < 4; i++)
    {
        CJLMSResource resource = CJLMSContentInterface::getInstance()->getResFile(i + DIARY_1, eFileType_Extend);
        
        CJSprite* diaryLayer;
        
        if (resource.szCaptureImageName == "")
        {
            m_completeDiary->push_back(false);
            diaryLayer = CJSprite::createWithFullPath(getContentID(CJUtils::getStringFormatInteger("_p420_img_line%02d.png", i)).c_str());
        }
        else
        {
            m_completeDiary->push_back(true);
            diaryLayer = CJSprite::create(resource.szCaptureImageName.c_str());
        }
        
        diaryLayer->setColor(ccWHITE);

        diaryLayer->setPosition(CJPsdParser::getPsdPosition(CJUtils::getStringFormatInteger("e002_common_diary_img_index_thumb%02d", i), m_psdDictionary));
        addChild(diaryLayer, kDepth0_backImage, kTagPicture+i);
        
        diaryLayer->setScale(0.27);
    }
    
}

void E002_Base_P400_Index::onNarrationFinishedCallback(std::string fileName)
{
    
}


void E002_Base_P400_Index::onTouchedNavigationButtonAtInfo()
{
    
}

std::string E002_Base_P400_Index::getContentID(std::string resource)
{
    return CJUtils::getInstance()->getContentID().append(resource);
}

