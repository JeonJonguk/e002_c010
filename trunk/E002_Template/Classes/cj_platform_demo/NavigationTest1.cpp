//
//  NavigationTest1.cpp
//  SoundPhonics_Package
//
//  Created by j2enty on 13. 7. 10..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#include "NavigationTest1.h"


CCScene* NavigationTest1::scene()
{
    CCScene *scene = CCScene::create();
    NavigationTest1* layer = NavigationTest1::create();
    scene->addChild(layer);
    return scene;
}

bool NavigationTest1::init()
{
    if (!CJLayer::init()) {
        return false;
    }
    
    return true;
}

void NavigationTest1::onEnter()
{
    CJLayer::onEnter();
    
    E002_Base_Navigation::initWithButtonTypes(this, "",
                                              eNavigationButton_Index, eNavigationButton_Guide, eNavigationButton_Prev, eNavigationButton_Next, -1);
//    E001_Base_Navigation::initWithButtonTypes(this, "",
//                                              eNavigationButton_Package, eNavigationButton_Close, -1);
    
    
//    E001_Base_Navigation::initWithNavigationType(this, "", eNavigationType_Page);
//    E001_Base_Navigation::initWithNavigationType(this, "", eNavigationType_Index);

    
    E002_Base_Navigation::showNavigation();
}

void NavigationTest1::onExit()
{
    CJLayer::onExit();
}



void NavigationTest1::onTouchedNavigationButtonAtIndex()
{
    E002_Base_Navigation::setEnableButton(false, eNavigationButton_Index);
}

void NavigationTest1::onTouchedNavigationButtonAtInfo()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, NavigationTest1::scene(), ccRED));
}

void NavigationTest1::onTouchedNavigationButtonAtPrev()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, NavigationTest1::scene(), ccBLUE));
}

void NavigationTest1::onTouchedNavigationButtonAtNext()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, NavigationTest1::scene(), ccYELLOW));
}











void NavigationTest1::onTouchedNavigationButtonAtPackage()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, NavigationTest1::scene(), ccWHITE));
}

