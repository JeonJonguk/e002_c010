//
//  NavigationTest1.h
//  SoundPhonics_Package
//
//  Created by j2enty on 13. 7. 10..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#ifndef __SoundPhonics_Package__NavigationTest1__
#define __SoundPhonics_Package__NavigationTest1__

#include "CJLayer.h"
#include "E002_Base_Navigation.h"

class NavigationTest1 : public CJLayer, public E002_Base_Navigation
{
public:
    static CCScene* scene();
    
    bool init();
    void onEnter();
    void onExit();
    
    CREATE_FUNC(NavigationTest1);
    

    
// Navigation DELEGATE functions.
public:
    void onTouchedNavigationButtonAtIndex();
    void onTouchedNavigationButtonAtInfo();
    void onTouchedNavigationButtonAtPrev();
    void onTouchedNavigationButtonAtNext();
    
    
    
    
    void onTouchedNavigationButtonAtPackage();
};

#endif /* defined(__SoundPhonics_Package__NavigationTest1__) */
