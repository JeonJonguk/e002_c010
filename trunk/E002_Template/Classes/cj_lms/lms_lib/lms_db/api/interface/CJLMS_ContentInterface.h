//
//  CJLMS_ContentInterface.h
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 22..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#ifndef __SoundPhonics__CJLMS_ContentInterface__
#define __SoundPhonics__CJLMS_ContentInterface__

#include "CJLMSContent.h"

class CJLMS_ContentInterface
{
//////////////////////////////////////////////////
//
// CJLMS_ContentInterface basic functions.
//
//////////////////////////////////////////////////
public:
    CJLMS_ContentInterface(CJLMSDBManage *pDBManager);
    virtual ~CJLMS_ContentInterface();
    
    static CJLMS_ContentInterface* create(CJLMSDBManage *pDBManager);
    
    
    
private:
    CJLMSDBManage                           *_dbManager;
    CJLMSContent                            *_dbContent;
    
    

//////////////////////////////////////////////////
//
// CJLMS_ContentInterface QUERY functions.
//
//////////////////////////////////////////////////
public:
//////////////////////////////////////////////////
// INSERT
//////////////////////////////////////////////////
    
//////////////////////////////////////////////////
// UPDATE
//////////////////////////////////////////////////
    
//////////////////////////////////////////////////
// SELECT
//////////////////////////////////////////////////
    int                     getContentPrimaryKey(std::string strPKGCode, std::string strContentCode);
    int                     getContentMax();
    
    Content                 getContent(int iContentPrimaryKey);
    int                     getContentStage(int iContentPrimaryKey);
    int                     getContentMenuCount(int iContentPrimaryKey);
    std::string             getContentPKGCode(int iContentPrimaryKey);
    std::string             getContentCode(int iContentPrimaryKey);
    std::string             getCotnentTitle(int iContentPrimaryKey);
    std::string             getCotnentDesc(int iContentPrimaryKey);
    std::string             getCotnentGalleryTile(int iContentPrimaryKey);
    std::string             getContentGalleryDesc(int iContentPrimaryKey);
    
    Content                 getContent(std::string strPKGCode, int iStage);
    int                     getContentStage(std::string strPKGCode, int iStage);
    int                     getContentMenuCount(std::string strPKGCode, int iStage);
    std::string             getContentPKGCode(std::string strPKGCode, int iStage);
    std::string             getContentCode(std::string strPKGCode, int iStage);
    std::string             getCotnentTitle(std::string strPKGCode, int iStage);
    std::string             getCotnentDesc(std::string strPKGCode, int iStage);
    std::string             getCotnentGalleryTile(std::string strPKGCode, int iStage);
    std::string             getContentGalleryDesc(std::string strPKGCode, int iStage);

    Content                 getContent(std::string strPKGCode, std::string strContentCode);
    int                     getContentStage(std::string strPKGCode, std::string strContentCode);
    int                     getContentMenuCount(std::string strPKGCode, std::string strContentCode);
    std::string             getContentPKGCode(std::string strPKGCode, std::string strContentCode);
    std::string             getContentCode(std::string strPKGCode, std::string strContentCode);
    std::string             getCotnentTitle(std::string strPKGCode, std::string strContentCode);
    std::string             getCotnentDesc(std::string strPKGCode, std::string strContentCode);
    std::string             getCotnentGalleryTile(std::string strPKGCode, std::string strContentCode);
    std::string             getContentGalleryDesc(std::string strPKGCode, std::string strContentCode);
};

#endif /* defined(__SoundPhonics__CJLMS_ContentInterface__) */
