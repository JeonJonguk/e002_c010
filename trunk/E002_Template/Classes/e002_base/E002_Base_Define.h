//
//  E002_Base_Define.h
//  E002_Template
//
//  Created by Jeong.YJ on 2014. 2. 21..
//
//

#ifndef E002_Template_E002_Base_Define_h
#define E002_Template_E002_Base_Define_h

#define LMS_MENU_END_LETSPLAY1 10
#define LMS_MENU_END_LETSPLAY2 20
#define LMS_MENU_END_LETSPLAY3 30

#define FLASH_INTRO_DATEPOOL_KEY "flash_intro_datepool_key"

#define P100 100
#define P200 200
#define P300 300

#define DIARY_1 40
#define DIARY_2 41
#define DIARY_3 42
#define DIARY_4 43

#define ANISON     "ANISON"
#define BOOMBOOM   "BOOMBOOM"
#define ALPHAROBOT "ALPHAROBOT"
#define CHU        "CHU"
#define GRUMBIE    "GRUMBIE"

#define E002_NOTIFICATION_DIARY_DRAWING_STARTCALL                            "notification_e002_diary_drawing_startcall"
#define E002_NOTIFICATION_DIARY_DRAWING_FINISHCALL                           "notification_e002_diary_drawing_finishicall"
#define E002_NOTIFICATION_DIARY_WRITE_FINISHCALL                             "notification_e002_diary_write_finishicall"
#define E002_NOTIFICATION_DIARY_WRITE_CLOSECALL                              "notification_e002_diary_write_closecall"

#define E002_USERDEFAULT_DIARY_NUMBER                                        "userdefault_e002_diary_number"

// For IOS, ANDROID Height gap.
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define OS_HEIGHT_GAP                                   24
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define OS_HEIGHT_GAP                                   24
#endif

#define POS_BOTTOMLEFT                                  CCPointMake(49, 49 + 24 - OS_HEIGHT_GAP+24)

#endif
