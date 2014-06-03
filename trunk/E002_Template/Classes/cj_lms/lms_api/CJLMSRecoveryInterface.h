//
//  CJLMSRecoveryInterface.h
//  SoundPhonics
//
//  Created by j2enty on 13. 10. 17..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#ifndef __SoundPhonics__CJLMSRecoveryInterface__
#define __SoundPhonics__CJLMSRecoveryInterface__

#include "E002_LMSInterface.h"

class CJLMSRecoveryInterface
{
//////////////////////////////////////////////////
//
// CJLMSRecoveryInterface basic functions.
//
//////////////////////////////////////////////////
public:
    CJLMSRecoveryInterface();
    virtual ~CJLMSRecoveryInterface();
    
    static CJLMSRecoveryInterface* getInstance();
    static void release();
    static bool isExistInstance();
    
    
//////////////////////////////////////////////////
//
// CJLMSRecoveryInterface recovery functions.
//
//////////////////////////////////////////////////
public:
    bool        startPackage(int iTotalStage, std::string strPKGCode, int iIdxKids,
                             std::string strStartDate, std::string strEndDate);
    bool        endPackage();
    bool        startContent(std::string strContentCode,
                             std::string strStartDate, std::string strEndDate);
    bool        endContent();
    bool        setContentProgress(int iMenuID, int iCount, std::string strKey,
                                   std::string strStartDate, std::string strEndDate);
    bool        setContentGrade(std::string strExtra, std::string strDate);
};



#endif /* defined(__SoundPhonics__CJLMSRecoveryInterface__) */
