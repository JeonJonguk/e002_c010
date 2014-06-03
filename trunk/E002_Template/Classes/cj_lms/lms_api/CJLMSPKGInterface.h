//
//  CJLMSPKGInterface.h
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 23..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#ifndef __SoundPhonics__CJLMSPKGInterface__
#define __SoundPhonics__CJLMSPKGInterface__

#include <iostream>
#include "CJLMSStruct.h"
#include "CJLMSInterfaceDefine.h"

class CJLMSPKGInterface
{
//////////////////////////////////////////////////
//
// CJLMSPKGInterface basic functions.
//
//////////////////////////////////////////////////
public:
    CJLMSPKGInterface();
    ~CJLMSPKGInterface();
    
    static CJLMSPKGInterface* getInstance();
    static void release();
    static bool isExistInstance();
    

    
    
//////////////////////////////////////////////////
//
// CJLMSPKGInterface operating functions.
//
//////////////////////////////////////////////////
protected:
    
public:
    bool            isChildIDLogined();
    std::string     getResourceRootPath();


    bool            startPackage(int iTotalStage, std::string strPKGCode);
    bool            endPackage();
    bool            startContent(std::string strContentCode);
    bool            endContent();

    bool            setContentResourcePraise(int iFileID, ePraiseType ePraiseType);
    
    int             getOpenStage();
    bool            setOpenStage(int iStage);
    
    int             getCurrentStage();
    
    
    KidsInfo        getKidsInfo();
    Content         getContent();
    Content         getContent(int iStage);
    
    KidsContent     getKidsContent(int iContentPrimaryKey);
    std::vector<KidsContent>* getKidsContents();
    
    std::vector<Progress>*  getProgresses(int iContentPrimaryKey);
    std::vector<Grade>*     getGrades(int iContentPrimaryKey);
    std::vector<Grade>*     getGrades(int iContentPrimaryKey, int iQuestionPrimaryKey);
    
    std::vector<ResFile>*   getContentResources(int iContentPrimaryKey, eFileType eFileType);
    std::vector<ResFile>*   getPackageResources(eFileType eFileType);
};

#endif /* defined(__SoundPhonics__CJLMSPKGInterface__) */
