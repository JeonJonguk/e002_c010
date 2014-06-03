//
//  E002_LMSInterface.h
//  SoundPhonics_Step2
//
//  Created by j2enty on 2014. 4. 28..
//  Copyright (c) 2014년 CJ Educations. All rights reserved.
//

#ifndef __SoundPhonics_Step2__E002_LMSInterface__
#define __SoundPhonics_Step2__E002_LMSInterface__

#include "CJLMSInterface.h"

class E002_LMSInterface : public CJLMSInterface {
//////////////////////////////////////////////////
// CJLMSInterface basic functions.
//////////////////////////////////////////////////
public:
    static E002_LMSInterface* getInstance();
    static void release();
    static bool isExistInstance();
    
    
    
//////////////////////////////////////////////////
// CJLMSInterface CONTENT OPERATION FUNCTIONS.
//////////////////////////////////////////////////
private:
public:
    std::string getFileExtension(eFileType eFileType);
    bool deleteLMSFile(int iMenuID, eFileType eFileType);
    std::string createLMSFile(int iMenuID, eFileType eFileType);
    std::string getLMSFileName(int iMenuID, eFileType eFileType,
                               std::string strExtend1, std::string strExtend2);
    CJLMSResource getResFile(int iMenuID, eFileType eFileType);
    bool saveLMSFile();
    
    
    
    
//////////////////////////////////////////////////
// CJLMS Recovery Interface CONTENT OPERATION FUNCTIONS.
//////////////////////////////////////////////////
private:
public:
    bool recoveryStartPackage(int iTotalStage, std::string strPKGCode, int iIdxKids,
                              std::string strStartDate, std::string strEndDate);
    bool recoveryEndPackage();
    bool recoveryStartContent(std::string strContentCode,
                              std::string strStartDate, std::string strEndDate);
    bool recoveryEndContent();
    bool recoverySetContentProgress(int iMenuID, int iCount, std::string strKey,
                                    std::string strStartDate, std::string strEndDate);
    bool recoverySetContentGrade(std::string strExtra, std::string strDate);
};


#endif /* defined(__SoundPhonics_Step2__E002_LMSInterface__) */
