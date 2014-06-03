//
//  CJLMSInterfaceDefine.h
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 23..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#ifndef SoundPhonics_CJLMSInterfaceDefine_h
#define SoundPhonics_CJLMSInterfaceDefine_h

#include <string>

typedef enum
{
    eFileType_Image             = 1,
    eFileType_Sound,
    eFileType_Video,
    eFileType_Extend,
} eFileType;

typedef enum
{
    ePraiseType_A               = 1,
    ePraiseType_B,
    ePraiseType_C,
    ePraiseType_D,
    ePraiseType_E,
    ePraiseType_F,
    ePraiseType_G,
    ePraiseType_H,
} ePraiseType;

typedef enum
{
    eQuestionType_A             = 1,
    eQuestionType_B,
    eQuestionType_C,
    eQuestionType_D,
    eQuestionType_E,
    eQuestionType_F,
    eQuestionType_G,
} eQuestionType;

struct CJLMSQuestionResult
{
    eQuestionType               questionType;
    
    int                         questionCount;
    int                         answerCount;
};

struct CJLMSResource {
    int menuID;
    std::string szBGImageName;
    std::string szCaptureImageName;
    std::string szExtendData;
};


#endif
