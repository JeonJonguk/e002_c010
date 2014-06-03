//
//  CJLMSDefines.h
//
//  Created by j2enty on 13. 8. 20..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#ifndef CJLMSDefines_h
#define CJLMSDefines_h

#define DB_ERROR                    -1
#define DB_SUCCESS                  0

#define RECOVERY_NEED               0
#define RECOVERY_SUCCESS            1

#define INT_DEFAULT                 -1

#define DEFAULT_DBCONN_TIMEOUT      1


#define DB_FILE_NAME                "lms.sqlite"
    
#define GRADE_KEY_CODE              "grade"
#define PROGRESS_KEY_CODE           "progress"
#define KIDSCONTENT_KEY_CODE        "kidscontent"
#define FILE_KEY_CODE               "file"

#define CONTENT_EXTRA_KEY           "appType"
#define CONTENT_EXTRA_PACKAGE       "0"
#define CONTENT_EXTRA_APP           "1"
#define STEP_EXTRA_KEY              "menuNum"
//#define GRADE_EXTRA_KEY             "gradeExtra"


#define kProjName_Han1              "h001"
#define kProjName_Han2              "h001"
#define kProjName_Think             "s001"
#define kProjName_EngPop1           ""
#define kProjName_EngPop2           ""
#define kProjName_SoundPhonics1     "e001"
#define kProjName_SoundPhonics2     "e002"

#define kPKGName_Han1               "com.cjeducations.ithink.hanlv1"
#define kPKGName_Han2               "com.cjeducations.ithink.hanlv2"
#define kPKGName_Think              "com.cjeducations.ithink.s001"
#define kPKGName_EngPop1            ""
#define kPKGName_EngPop2            ""
#define kPKGName_SoundPhonics1      "com.cjeducations.ithink.e001"
#define kPKGName_SoundPhonics2      "com.cjeducations.ithink.e002"

enum
{
    kPKGCode_HanLv1             = 1,
    kPKGCode_HanLv2,
    kPKGCode_Think              = 1,
    kPKGCode_EngPop1            = 1,
    kPKGCode_EngPop2,
    kPKGCode_SoundPhonics1      = 4,
    kPKGCode_SoundPhonics2,
};




#endif
