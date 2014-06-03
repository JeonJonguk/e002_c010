//
//  CJLMS_FileInterface.h
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 22..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#ifndef __SoundPhonics__CJLMS_FileInterface__
#define __SoundPhonics__CJLMS_FileInterface__

#include "CJLMSFile.h"

class CJLMS_FileInterface
{
//////////////////////////////////////////////////
//
// CJLMS_FileInterface basic functions.
//
//////////////////////////////////////////////////
public:
    CJLMS_FileInterface(CJLMSDBManage *pDBManager);
    virtual ~CJLMS_FileInterface();
    
    static CJLMS_FileInterface* create(CJLMSDBManage *pDBManager);
    
    
    
private:
    CJLMSDBManage                           *_dbManager;
    CJLMSFile                               *_dbFile;
    
    ResFile                                 _currentFile;
    
    
public:
    void                    setCurrentFile(ResFile resFile);
    ResFile                 getCurrentFile();
    
    
//////////////////////////////////////////////////
//
// CJLMS_FileInterface QUERY functions.
//
//////////////////////////////////////////////////
public:
//////////////////////////////////////////////////
// INSERT
//////////////////////////////////////////////////
    bool                    saveCurrentFile();
    
    
//////////////////////////////////////////////////
// DELETE
//////////////////////////////////////////////////
    bool                    removeFile(ResFile resFile);
    
    
//////////////////////////////////////////////////
// UPDATE
//////////////////////////////////////////////////
    bool                    setFilePraiseType(int iFilePrimaryKey, int iPraiseType);
    
    
//////////////////////////////////////////////////
// SELECT
//////////////////////////////////////////////////
    std::string             getFilePath(int iContentPrimaryKey, int iMenuID, int iFileType, int iIdxKids);
    std::string             getCurrentFilePath(int iIdxKids);
    std::vector<ResFile>*   getContentFiles(int iContentPrimaryKey, int iFileType, int iIdxKids);
    std::vector<ResFile>*   getPackageFiles(int iFileType, int iIdxKids);
    std::vector<ResFile>*   getRemoveFiles(int iContentPrimaryKey, int iFileType, int iIdxKids);
    std::vector<ResFile>*   getRemoveFiles(int iContentPrimaryKey, int iFileType, int iIdxKids, int iMenuID);
    
    
    ResFile getResFile(int contentId, int gubun, int idxKids, int menuId);
};

#endif /* defined(__SoundPhonics__CJLMS_FileInterface__) */
