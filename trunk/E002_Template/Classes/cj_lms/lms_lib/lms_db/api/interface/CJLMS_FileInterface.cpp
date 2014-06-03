//
//  CJLMS_FileInterface.cpp
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 22..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#include "CJLMS_FileInterface.h"

//////////////////////////////////////////////////
//
// CJLMS_FileInterface basic functions.
//
//////////////////////////////////////////////////
CJLMS_FileInterface::CJLMS_FileInterface(CJLMSDBManage *pDBManager)
{
    _dbManager      = pDBManager;
    _dbFile         = CJLMSFile::create(_dbManager);
}

CJLMS_FileInterface::~CJLMS_FileInterface()
{
    delete _dbFile;
    
    _dbManager      = NULL;
    _dbFile         = NULL;
}

CJLMS_FileInterface* CJLMS_FileInterface::create(CJLMSDBManage *pDBManager)
{
    CJLMS_FileInterface *pInterface = new CJLMS_FileInterface(pDBManager);
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
// CJLMS_FileInterface operating functions.
//
//////////////////////////////////////////////////
//////////////////////////////////////////////////
// INSERT
//////////////////////////////////////////////////
bool CJLMS_FileInterface::saveCurrentFile()
{
    return _dbFile->insertFile(_currentFile);
}

void CJLMS_FileInterface::setCurrentFile(ResFile resFile)
{
    _currentFile = resFile;
}

ResFile CJLMS_FileInterface::getCurrentFile()
{
    return _currentFile;
}


//////////////////////////////////////////////////
// DELETE
//////////////////////////////////////////////////
bool CJLMS_FileInterface::removeFile(ResFile resFile)
{
    return _dbFile->deleteFile(resFile);
}


//////////////////////////////////////////////////
// UPDATE
//////////////////////////////////////////////////
bool CJLMS_FileInterface::setFilePraiseType(int iFilePrimaryKey, int iPraiseType)
{
    return _dbFile->updateKind(iFilePrimaryKey, iPraiseType);
}


//////////////////////////////////////////////////
// SELECT
//////////////////////////////////////////////////
std::string CJLMS_FileInterface::getFilePath(int iContentPrimaryKey, int iMenuID, int iFileType, int iIdxKids)
{
    return _dbFile->selectPath(iContentPrimaryKey, iMenuID, iFileType, iIdxKids);
}

std::string CJLMS_FileInterface::getCurrentFilePath(int iIdxKids)
{
    return _dbFile->selectCurrentPath(iIdxKids);
}

std::vector<ResFile>* CJLMS_FileInterface::getContentFiles(int iContentPrimaryKey, int iFileType, int iIdxKids)
{
    return _dbFile->selectContentFile(iContentPrimaryKey, iFileType, iIdxKids);
}

std::vector<ResFile>* CJLMS_FileInterface::getPackageFiles(int iFileType, int iIdxKids)
{
    return _dbFile->selectPackageFile(iFileType, iIdxKids);
}

std::vector<ResFile>* CJLMS_FileInterface::getRemoveFiles(int iContentPrimaryKey, int iFileType, int iIdxKids)
{
    return _dbFile->selectRemoveFile(iContentPrimaryKey, iFileType, iIdxKids);
}

std::vector<ResFile>* CJLMS_FileInterface::getRemoveFiles(int iContentPrimaryKey, int iFileType, int iIdxKids, int iMenuID)
{
    return _dbFile->selectRemoveFile(iContentPrimaryKey, iFileType, iIdxKids, iMenuID);
}

ResFile CJLMS_FileInterface::getResFile(int contentId, int gubun, int idxKids, int menuId) {
    return _dbFile->selectFileWithMenuID(contentId, gubun, idxKids, menuId);
}