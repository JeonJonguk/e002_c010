

#include "PsdTest.h"
#include "CJUtils.h"
#include "CJMultimedia.h"
#include "CJPsdParser.h"

static clock_t startTime;

CCScene* PsdTest::scene()
{
	CCScene *scene = CCScene::create();
    
	PsdTest *layer = PsdTest::create();
    
	scene->addChild(layer);
    
	return scene;
}

bool PsdTest::init()
{
    CCLog("PsdTest::init()");
    
    startTime = clock();
    

    
    return true;
}

void PsdTest::onEnter()
{
    CCLayer::onEnter();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);


    m_psdDictionary = new CCDictionary();
    CJPsdParser::parseToPsdJSON("e001_c130_p610_test.json", &m_psdDictionary);
    
    
    

    CCSprite* test1 = CJPsdParser::getPsdSprite("e001_c130_p610_img_guide_bg", m_psdDictionary);
    addChild(test1);
    
    CCSprite* test2 = CJPsdParser::getPsdSprite("e001_c130_p610_img_ans00_00", m_psdDictionary);
    addChild(test2);
    
    CCSprite* test3 = CJPsdParser::getPsdSprite("e001_c130_p610_img_ans00_01", m_psdDictionary);
    addChild(test3);
    
    CCSprite* test4 = CJPsdParser::getPsdSprite("e001_c130_p610_img_que00_00", m_psdDictionary);
    addChild(test4);
    
    clock_t endTime;
    endTime = clock();
    
    clock_t deltaTime;
    deltaTime = endTime - startTime;
    
    double seconds_elspased = static_cast<double>(deltaTime) / CLOCKS_PER_SEC;
    CCLog("seconds_elspased : %lf", seconds_elspased);
}


void PsdTest::onExit()
{
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}


bool PsdTest::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    CCPoint tp = touch->getLocation();
    
    return false;
}

void PsdTest::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
}

void PsdTest::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
}
