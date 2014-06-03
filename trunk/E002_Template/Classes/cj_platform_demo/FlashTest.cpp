

#include "FlashTest.h"
#include "CJUtils.h"
#include "CJMultimedia.h"

static clock_t startTime;

CCScene* FlashTest::scene()
{
	CCScene *scene = CCScene::create();
    
	FlashTest *layer = FlashTest::create();
    
	scene->addChild(layer);
    
	return scene;
}

bool FlashTest::init()
{
    CCLog("FlashTest::init()");
    
    startTime = clock();
    stagecount = 0;
    
      return true;
}

void FlashTest::onEnter()
{
    CCLayer::onEnter();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    
    winSize = CCDirector::sharedDirector()->getWinSize();

    
    
    //////////////////////////////////////
    
    this->setAnimationFile("e002_c030_p100_intro_flash_sheets.json", "e002_c030_p100_intro_flash_animations.json", "first");
//    this->setAnimationFile("e001_c020_p210_flash_cru_sheets.json", "e001_c020_p210_flash_cru_animations.json", "second");
//    this->setAnimationFile("e001_c010_p110_flash_cru_sheets.json", "e001_c010_p110_flash_cru_animations.json", "third");
//    this->setAnimationFile("e001_c010_p300_flash_br_out_sheets.json", "e001_c010_p300_flash_br_out_animations.json", "fourth");

    //setAnimationParseType(kParseTypeXML);
     
    setAnimationParent(this);
    animationManagerParseStart();
    
    //////////////////////////////////////
    
    
    
    clock_t endTime;
    endTime = clock();
    
    clock_t deltaTime;
    deltaTime = endTime - startTime;
    
    double seconds_elspased = static_cast<double>(deltaTime) / CLOCKS_PER_SEC;
    CCLog("seconds_elspased : %lf", seconds_elspased);
}

void FlashTest::loadingCallback()
{

}

void FlashTest::play()
{
    CCLog("PLAY");
    
    CJAnimation* ani = getAnimationByKey("first", "e002_c030_p100_intro_flash_s01");
    ani->playAnimation(0, -1);
    addChild(ani, 100);

    //CJAnimationDataPool* dp = getDataPoolForKey("second");
    
    //CCLog("DATAPOOL COUNT:%d", getDataPoolCount());
    //CCLog("ANIMATION COUNT:%d", getAnimationCount("second"));

}

void FlashTest::onExit()
{
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
}


bool FlashTest::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    CCPoint tp = touch->getLocation();

    CCLog("AAA");
    if (CJUtils::hitTestPoint(mBtn, tp, false) && stagecount == 0)
    {
        removeAllAnimations();
        play2();
    }
    else if(CJUtils::hitTestPoint(mBtn, tp, false) && stagecount == 1)
    {
        removeAllAnimations();
        play3();
    }
    else if(CJUtils::hitTestPoint(mBtn, tp, false) && stagecount == 2)
    {
        removeAllAnimations();
        play4();
    }
    else if(CJUtils::hitTestPoint(mBtn, tp, false) && stagecount == 3)
    {
        removeAllAnimations();
        play1();
        stagecount = 0;
        
        return false;
    }
    
    stagecount++;
    
    return false;
}

void FlashTest::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
}

void FlashTest::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
}

void FlashTest::OnPlay(CJAnimation* pAnimation)
{
    CCLog("ON PLAY");
}
void FlashTest::OnStop(CJAnimation* pAnimation)
{
    CCLog("ON STOP");
}

void FlashTest::OnLastFrame(CJAnimation* pAnimation)
{
    CCLog("ON LASTFRAME");
    
    if(pAnimation->getName() == "e002_c030_p100_intro_flash_s01")
    {
        play1btn();
    }
    else if(pAnimation->getName() == "e002_c030_p100_intro_flash_s03")
    {
        play2btn();
    }
    else if(pAnimation->getName() == "e002_c030_p100_intro_flash_s04")
    {
        play3btn();
    }
    else if(pAnimation->getName() == "e002_c030_p100_intro_flash_s05")
    {
        play4btn();
    }
}

void FlashTest::OnPause(CJAnimation* pAnimation)
{
//    CCLog("ON PAUSE");
}

void FlashTest::OnUpdate(CJAnimation* pAnimation)
{
//    CCLog("ON UPDATE");
}




void FlashTest::animationManagerParseComplete()
{
    CCLog("FLASH TEST PARSE COMPLETE");

    createAllAnimations();


    play1();
    
 
}

void FlashTest::play1()
{
    playAnimation("first", "e002_c030_p100_intro_flash_s01", 1, 100);
}

void FlashTest::play1btn()
{
    removeAllAnimations();
    
    playAnimation("first", "e002_c030_p100_intro_flash_s02_btn", -1, 200);
    mBtn = getSpriteFromFlash("first", "e002_c030_p100_intro_flash_s02_btn", "e002_c030_p100_intro_flash_btn");

}

void FlashTest::play2()
{
    playAnimation("first", "e002_c030_p100_intro_flash_s03", 1, 100);

}

void FlashTest::play2btn()
{
    removeAllAnimations();
    
    playAnimation("first", "e002_c030_p100_intro_flash_s03_btn", -1, 200);
    mBtn = getSpriteFromFlash("first", "e002_c030_p100_intro_flash_s03_btn", "e002_c030_p100_intro_flash_btn");

}

void FlashTest::play3()
{
    playAnimation("first", "e002_c030_p100_intro_flash_s04", 1, 100);
}

void FlashTest::play3btn()
{
    removeAllAnimations();
    
    playAnimation("first", "e002_c030_p100_intro_flash_s04_btn", -1, 200);
    mBtn = getSpriteFromFlash("first", "e002_c030_p100_intro_flash_s04_btn", "e002_c030_p100_intro_flash_btn");

}

void FlashTest::play4()
{
    playAnimation("first", "e002_c030_p100_intro_flash_s05", 1, 100);

}

void FlashTest::play4btn()

{
    removeAllAnimations();
    
    playAnimation("first", "e002_c030_p100_intro_flash_s05_btn", -1, 200);
    mBtn = getSpriteFromFlash("first", "e002_c030_p100_intro_flash_s05_btn", "e002_c030_p100_intro_flash_btn");

}



