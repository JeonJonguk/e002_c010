//
//  CJLMS_ContentInterface.cpp
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 22..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#include "CJLMS_ContentInterface.h"

//////////////////////////////////////////////////
//
// CJLMS_ContentInterface basic functions.
//
//////////////////////////////////////////////////
CJLMS_ContentInterface::CJLMS_ContentInterface(CJLMSDBManage *pDBManager)
{
    _dbManager      = pDBManager;
    _dbContent      = CJLMSContent::create(_dbManager);
}

CJLMS_ContentInterface::~CJLMS_ContentInterface()
{
    delete _dbContent;
    
    _dbManager      = NULL;
    _dbContent      = NULL;
}

CJLMS_ContentInterface* CJLMS_ContentInterface::create(CJLMSDBManage *pDBManager)
{
    CJLMS_ContentInterface *pInterface = new CJLMS_ContentInterface(pDBManager);
    if(NULL!=pInterface)
    {
        return pInterface;
    }
    else
    {
        delete pInterface;
        pInterface = NULL;
        
        return NULL;
    }
}





//////////////////////////////////////////////////
//
// CJLMS_ContentInterface operating functions.
//
//////////////////////////////////////////////////
//////////////////////////////////////////////////
// INSERT
//////////////////////////////////////////////////

//////////////////////////////////////////////////
// UPDATE
//////////////////////////////////////////////////

//////////////////////////////////////////////////
// SELECT
//////////////////////////////////////////////////
int CJLMS_ContentInterface::getContentPrimaryKey(std::string strPKGCode, std::string strContentCode)
{
    return _dbContent->selectContentId(strPKGCode, strContentCode);
}

int CJLMS_ContentInterface::getContentMax()
{
    return _dbContent->getContentCount();
}

Content CJLMS_ContentInterface::getContent(int iContentPrimaryKey)
{
    return _dbContent->selectContent(iContentPrimaryKey);
}

int CJLMS_ContentInterface::getContentStage(int iContentPrimaryKey)
{
    Content content = this->getContent(iContentPrimaryKey);
    return content.iStage;
}

int CJLMS_ContentInterface::getContentMenuCount(int iContentPrimaryKey)
{
    Content content = this->getContent(iContentPrimaryKey);
    return content.nMenuCount;
}

std::string CJLMS_ContentInterface::getContentPKGCode(int iContentPrimaryKey)
{
    Content content = this->getContent(iContentPrimaryKey);
    return content.szPKGCode;
}

std::string CJLMS_ContentInterface::getContentCode(int iContentPrimaryKey)
{
    Content content = this->getContent(iContentPrimaryKey);
    return content.szContentCode;
}

std::string CJLMS_ContentInterface::getCotnentTitle(int iContentPrimaryKey)
{
    Content content = this->getContent(iContentPrimaryKey);
    return content.szTitle;
}

std::string CJLMS_ContentInterface::getCotnentDesc(int iContentPrimaryKey)
{
    Content content = this->getContent(iContentPrimaryKey);
    return content.szDescription;
}

std::string CJLMS_ContentInterface::getCotnentGalleryTile(int iContentPrimaryKey)
{
    Content content = this->getContent(iContentPrimaryKey);
    return content.szGalleryTitle;
}

std::string CJLMS_ContentInterface::getContentGalleryDesc(int iContentPrimaryKey)
{
    Content content = this->getContent(iContentPrimaryKey);
    return content.szGalleryDesc;
}

Content CJLMS_ContentInterface::getContent(std::string strPKGCode, int iStage)
{
    return _dbContent->selectContent(strPKGCode, iStage);
}

int CJLMS_ContentInterface::getContentStage(std::string strPKGCode, int iStage)
{
    Content content = this->getContent(strPKGCode, iStage);
    return content.iStage;
}

int CJLMS_ContentInterface::getContentMenuCount(std::string strPKGCode, int iStage)
{
    Content content = this->getContent(strPKGCode, iStage);
    return content.nMenuCount;
}

std::string CJLMS_ContentInterface::getContentPKGCode(std::string strPKGCode, int iStage)
{
    Content content = this->getContent(strPKGCode, iStage);
    return content.szPKGCode;
}

std::string CJLMS_ContentInterface::getContentCode(std::string strPKGCode, int iStage)
{
    Content content = this->getContent(strPKGCode, iStage);
    return content.szContentCode;
}

std::string CJLMS_ContentInterface::getCotnentTitle(std::string strPKGCode, int iStage)
{
    Content content = this->getContent(strPKGCode, iStage);
    return content.szTitle;
}

std::string CJLMS_ContentInterface::getCotnentDesc(std::string strPKGCode, int iStage)
{
    Content content = this->getContent(strPKGCode, iStage);
    return content.szDescription;
}

std::string CJLMS_ContentInterface::getCotnentGalleryTile(std::string strPKGCode, int iStage)
{
    Content content = this->getContent(strPKGCode, iStage);
    return content.szGalleryTitle;
}

std::string CJLMS_ContentInterface::getContentGalleryDesc(std::string strPKGCode, int iStage)
{
    Content content = this->getContent(strPKGCode, iStage);
    return content.szGalleryDesc;
}

Content CJLMS_ContentInterface::getContent(std::string strPKGCode, std::string strContentCode)
{
    return _dbContent->selectContent(strPKGCode, strContentCode);
}

int CJLMS_ContentInterface::getContentStage(std::string strPKGCode, std::string strContentCode)
{
    Content content = this->getContent(strPKGCode, strContentCode);
    return content.iStage;
}

int CJLMS_ContentInterface::getContentMenuCount(std::string strPKGCode, std::string strContentCode)
{
    Content content = this->getContent(strPKGCode, strContentCode);
    return content.nMenuCount;
}

std::string CJLMS_ContentInterface::getContentPKGCode(std::string strPKGCode, std::string strContentCode)
{
    Content content = this->getContent(strPKGCode, strContentCode);
    return content.szPKGCode;
}

std::string CJLMS_ContentInterface::getContentCode(std::string strPKGCode, std::string strContentCode)
{
    Content content = this->getContent(strPKGCode, strContentCode);
    return content.szContentCode;
}

std::string CJLMS_ContentInterface::getCotnentTitle(std::string strPKGCode, std::string strContentCode)
{
    Content content = this->getContent(strPKGCode, strContentCode);
    return content.szTitle;
}

std::string CJLMS_ContentInterface::getCotnentDesc(std::string strPKGCode, std::string strContentCode)
{
    Content content = this->getContent(strPKGCode, strContentCode);
    return content.szDescription;
}

std::string CJLMS_ContentInterface::getCotnentGalleryTile(std::string strPKGCode, std::string strContentCode)
{
    Content content = this->getContent(strPKGCode, strContentCode);
    return content.szGalleryTitle;
}

std::string CJLMS_ContentInterface::getContentGalleryDesc(std::string strPKGCode, std::string strContentCode)
{
    Content content = this->getContent(strPKGCode, strContentCode);
    return content.szGalleryDesc;
}
