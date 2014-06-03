//
//  E002_C030_P000_Lecture.h
//  E002_Template
//
//  Created by whitems on 14. 1. 14..
//
//

#ifndef E002_C030_P000_Lecture_h
#define E002_C030_P000_Lecture_h


#include "cocos2d.h"
#include "E002_Base_VideoLayer.h"

using namespace cocos2d;

class E002_C030_P000_Lecture : public E002_Base_VideoLayer {

    
public:
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual void onViewLoad();
    virtual void onViewLoaded();
    
    CREATE_FUNC(E002_C030_P000_Lecture);
    
    virtual void onVideoFinishedCallback();
    virtual void onIndexBtnTouch();
};
#endif
