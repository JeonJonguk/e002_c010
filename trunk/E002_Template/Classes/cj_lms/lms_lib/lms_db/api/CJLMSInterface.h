//
//  CJLMSInterface.h
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 23..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#ifndef __SoundPhonics__CJLMSInterface__
#define __SoundPhonics__CJLMSInterface__

#include "CJLMSInterfaceDefine.h"

#include "CJLMS_DBManageInterface.h"
#include "CJLMS_PKGKidsInterface.h"
#include "CJLMS_ProgressInterface.h"
#include "CJLMS_KidsContentInterface.h"
#include "CJLMS_GradeInterface.h"
#include "CJLMS_FileInterface.h"
#include "CJLMS_ContentInterface.h"
#include "CJLMS_QuestionInterface.h"
#include "CJLMSDataStorage.h"

#include "cocos2d.h"


class CJLMSInterface
{
//////////////////////////////////////////////////
//
// CJLMSInterface basic functions.
//
//////////////////////////////////////////////////
public:
    CJLMSInterface();
    virtual ~CJLMSInterface();
    
    bool init(std::string strDBPath);
    
protected:
    CJLMS_DBManageInterface         *mDBManageInterface;
    CJLMS_PKGKidsInterface          *mPKGKidsInterface;
    CJLMS_ProgressInterface         *mProgressInterface;
    CJLMS_KidsContentInterface      *mKidsContentInterface;
    CJLMS_GradeInterface            *mGradeInterface;
    CJLMS_FileInterface             *mFileInterface;
    CJLMS_ContentInterface          *mContentInterface;
    CJLMS_QuestionInterface         *mQuestionInterface;
    CJLMSDataStorage                *mDataStorage;
    

    
    
    
    
//////////////////////////////////////////////////
//
// CJLMSInterface operating functions.
//
//////////////////////////////////////////////////
protected:
    virtual bool    isInit();
    std::string     getCurrentDate();
    std::string     getCompateDate();
    
    void            updateData();
    bool            setContentKidsEndDate();
    
    
//////////////////////////////////////////////////
// CJLMSInterface PAKCAGE OPERATION FUNCTIONS.
//////////////////////////////////////////////////
public:
    virtual bool        isLauncherLogined();

    virtual bool        startPackage(int iTotalStage, std::string strPKGCode);
    virtual bool        endPackage();
    
    virtual bool        setContentResourcePraise(int iFileID, ePraiseType ePraiseType);
    
    virtual int         getOpenStage();
    virtual bool        setOpenStage(int iStage);
    
    virtual int         getCurrentStage();
    
    virtual KidsInfo    getKidsInfo();
    
    virtual Content     getContent();
    virtual Content     getContent(int iStage);
    
    virtual KidsContent getKidsContent(int iContentPrimaryKey);
    virtual std::vector<KidsContent>* getKidsContents();
    
    
    virtual std::vector<Progress>*  getProgresses(int iContentPrimaryKey);
    virtual std::vector<Grade>*     getGrades(int iContentPrimaryKey);
    virtual std::vector<Grade>*     getGrades(int iContentPrimaryKey, int iQuestionPrimaryKey);
    
    virtual std::vector<ResFile>*   getContentResources(int iContentPrimaryKey, eFileType eFileType);
    virtual std::vector<ResFile>*   getPackageResources(eFileType eFileType);
    

    
    
    

//////////////////////////////////////////////////
// CJLMSInterface CONTENT OPERATION FUNCTIONS.
//////////////////////////////////////////////////
private:
    
protected:
    
public:
    virtual bool        startContent(std::string strContentCode);
    virtual bool        endContent();
    
    virtual int         getKidsIdxKids();
    virtual std::string getResourceRootPath();
    
    virtual bool        setContentProgress(int iMenuID);
    virtual bool        setContentGrade(int iMenuID, int iPointValue, int iPointIndex);
    
    
    virtual std::string getSavedFileName(int iMenuID, eFileType eFileType);
    virtual std::string getFileExtension(eFileType eFileType);
    virtual bool        deleteLMSFile(eFileType eFileType);
    virtual std::string createLMSFile(int iMenuID, eFileType eFileType);
    virtual std::string getLMSFileName(int iMenuID, eFileType eFileType);
    virtual bool        saveLMSFile();
    
    
    
//////////////////////////////////////////////////
// CJLMS Recovery Interface CONTENT OPERATION FUNCTIONS.
//////////////////////////////////////////////////
private:
public:
    virtual bool        recoveryStartPackage(int iTotalStage, std::string strPKGCode, int iIdxKids,
                                             std::string strStartDate, std::string strEndDate) = 0;
    virtual bool        recoveryEndPackage() = 0;
    virtual bool        recoveryStartContent(std::string strContentCode,
                                             std::string strStartDate, std::string strEndDate) = 0;
    virtual bool        recoveryEndContent()  = 0;
    virtual bool        recoverySetContentProgress(int iMenuID, int iCount, std::string strKey,
                                                   std::string strStartDate, std::string strEndDate)  = 0;
    virtual bool        recoverySetContentGrade(std::string strExtra, std::string strDate)  = 0;
};

#endif /* defined(__SoundPhonics__CJLMSInterface__) */
