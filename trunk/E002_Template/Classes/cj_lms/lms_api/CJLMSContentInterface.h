//
//  CJLMSContentInterface.h
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 23..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#ifndef __SoundPhonics__CJLMSContentInterface__
#define __SoundPhonics__CJLMSContentInterface__

#include <string>
#include <vector>
#include "CJLMSInterfaceDefine.h"
#include "cocos2d.h"

class CJLMSContentInterface
{
//////////////////////////////////////////////////
//
// CJLMSContentInterface basic functions.
//
//////////////////////////////////////////////////
public:
    CJLMSContentInterface();
    ~CJLMSContentInterface();
    
    static CJLMSContentInterface* getInstance();
    static void release();
    static bool isExistInstance();
    
    
public:
    void            showPackage();
    
    
//////////////////////////////////////////////////
//
// CJLMSContentInterface operating functions.
//
//////////////////////////////////////////////////
protected:

public:
    bool setLMSMenuEnd(int iMenuID);
    bool setLMSGrade(std::vector<CJLMSQuestionResult> questionResults);
    
public:
    std::string getLMSFileName(int iMenuID, eFileType eFileType,
                                   std::string strExtend1 = "", std::string strExtend2 = "");
    bool saveLMSFile();
    CJLMSResource getResFile(int iMenuID, eFileType eFileType);

public:
    int getKidsIdx();
};





#endif /* defined(__SoundPhonics__CJLMSContentInterface__) */
