//
//  CJLMSDataStorage.h
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 23..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#ifndef __SoundPhonics__CJLMSDataStorage__
#define __SoundPhonics__CJLMSDataStorage__

#include "CJLMSStruct.h"
#include "CJLMSDefines.h"

class CJLMSDataStorage
{
//////////////////////////////////////////////////
//
// CJLMSDataStorage basic functions.
//
//////////////////////////////////////////////////
public:
    CJLMSDataStorage();
    ~CJLMSDataStorage();
    
    static CJLMSDataStorage* create();
    
    
    
    
private:
    std::string                     _strDBPath;
    int                             _dbConnectTimeout;
    
    KidsInfo                        _kidsInfo;
    Content                         _currentContent;
    
    ResFile                         _currentFile;
    
    std::string                     _strPKGCode;
    
    
//////////////////////////////////////////////////
//
// CJLMSDataStorage operating functions.
//
//////////////////////////////////////////////////
private:
    void            _resetKidsInfo();
    
public:
    void            setDBPath(std::string strDBPath);
    void            setDBConnectionTimeout(int iDBConnectionTimeOut);
    
    void            setKidsInfo(KidsInfo kidsInfo);
    void            setCurrentContent(Content content);
    void            setCurrentStage(int iStage);
    
    void            setCurrentFile(ResFile resFile);
    void            setPKGCode(std::string strPKGCode);
    
    std::string     getDBPath();
    int             getDBConnectionTimeOut();
    
    KidsInfo        getKidsInfo();
    int             getKidsPrimaryKey();
    int             getCurrentStage();
    
    Content         getCurrentContent();
    int             getCurrentContentPrimaryKey();
    std::string     getCurrentContentCode();
    
    
    ResFile         getCurrentFile();
    std::string     getPKGCode();
    int             getPKGID();
    
};

#endif /* defined(__SoundPhonics__CJLMSDataStorage__) */
