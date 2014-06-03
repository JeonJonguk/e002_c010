//
//  SSItem.h
//  E002_C010_Project
//
//  Created by smallsnail on 2014. 4. 1..
//
//

#ifndef E002_C010_Project_SSItem_h
#define E002_C010_Project_SSItem_h


#include "cocos2d.h"
#include "CJSprite.h"
using namespace cocos2d;

class SSItem:public CJSprite
{
public:

    std::string img;
    std::string snd;
    
    SSItem();
    ~SSItem();

    
    //sound
    void playEffect();
    void playNarration();
    void playNarrationRepeat();
    
    CCCallFunc* playEffectCallfunc();
};


#endif
