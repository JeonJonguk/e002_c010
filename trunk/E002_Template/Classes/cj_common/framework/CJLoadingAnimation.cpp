
#include "CJLoadingAnimation.h"


CJLoadingAnimation::CJLoadingAnimation()
{

}

CJLoadingAnimation::~CJLoadingAnimation()
{

}


bool CJLoadingAnimation::init()
{
    if(false == CCSprite::init())
    {
        return false;
    }
    
    CCLog("FLASH LOADING INIT");
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    initWithFile("e002_c030/img/e002_c030_common_img_btn_index_n.png");
    setPosition(ccp(winSize.width/2, winSize.height/2));
    
    
    CCActionInterval* rot = CCRotateBy::create(1.0f, 360.0f);

    CCActionInterval* rep = CCRepeatForever::create(rot);
    
    runAction(rep);
    
    return true;
}
