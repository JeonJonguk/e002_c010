//
//  CJDefine.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 6. 10..
//
//

#ifndef e_CJMacros_h
#define e_CJMacros_h

#include "cocos2d.h"
using namespace cocos2d;

//==================
#pragma mark - color
#define COLOR_BACKGROUND_WHITE              ccc4(255, 255, 255, 255)
#define COLOR_BACKGROUND_BALCK              ccc4(0, 0, 0, 255)
#define COLOR_BACKGROUND_DIMMED             ccc4(0, 0, 0, 190)
#define COLOR_BACKGROUND_TRANSPARENT        ccc4(0, 0, 0, 0)

//==================
#pragma mark - frame
//#define x(a) a->getPositionX()
//#define y(a) a->getPositionY()
//#define width(a) a->getContentSize().width
//#define height(a) a->getContentSize().height

//==================

#define replaceSceneNoTransition(classType)\
do {\
CCScene *scene = CCScene::create();\
classType *layer = classType::create();\
scene->addChild(layer);\
CCDirector::sharedDirector()->replaceScene(scene);\
}\
while(false)


#define replaceSceneTransitionFadeOut(classType)\
do {\
\
CCScene *scene = CCScene::create();\
classType *layer = classType::create();\
scene->addChild(layer);\
CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, scene, ccc3(0, 0, 0)));\
}\
while(false)

#define runSceneMacro(classType)\
do {\
CCScene *scene = CCScene::create();\
classType *layer = classType::create();\
scene->addChild(layer);\
CCDirector::sharedDirector()->runWithScene(scene);\
}\
while(false)



#endif
