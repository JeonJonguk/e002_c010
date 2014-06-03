//
//  E002_C030_ImageGuide.cpp
//  SoundPhonics_Template
//
//  Created by whitems on 13. 7. 5..
//
//

#include "E002_C030_P410_WritePopup.h"

#include "CJUtils.h"

E002_C030_P410_WritePopup::E002_C030_P410_WritePopup()
{
    m_psdDictionary = new CCDictionary();
}

E002_C030_P410_WritePopup::~E002_C030_P410_WritePopup()
{
    delete m_psdDictionary;
}

#pragma mark - init
bool E002_C030_P410_WritePopup::init()
{
    if (!E002_Base_P410_WritePopup::init()) {
        return false;
    }
    
    return true;
}

void E002_C030_P410_WritePopup::onEnter()
{
    E002_Base_P410_WritePopup::onEnter();
    
    CJPsdParser::parseToPsdJSON("e002_c030_p410_write.json", &m_psdDictionary);
    
    setChildDictionary(m_psdDictionary);
}

void E002_C030_P410_WritePopup::onExit()
{
    E002_Base_P410_WritePopup::onExit();
}

