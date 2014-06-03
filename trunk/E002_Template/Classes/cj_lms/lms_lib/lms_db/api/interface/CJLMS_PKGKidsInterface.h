//
//  CJLMS_PKGKidsInterface.h
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 22..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#ifndef __SoundPhonics__CJLMS_PKGKidsInterface__
#define __SoundPhonics__CJLMS_PKGKidsInterface__

#include "CJLMSPKGKids.h"

class CJLMS_PKGKidsInterface
{
//////////////////////////////////////////////////
//
// CJLMS_PKGKidsInterface basic functions.
//
//////////////////////////////////////////////////
public:
    CJLMS_PKGKidsInterface(CJLMSDBManage *pDBManager);
    virtual ~CJLMS_PKGKidsInterface();
    
    static CJLMS_PKGKidsInterface* create(CJLMSDBManage *pDBManager);
    
    
    
private:
    CJLMSDBManage                           *_dbManager;
    CJLMSPKGKids                            *_dbPKGKids;
    
    
    
//////////////////////////////////////////////////
//
// CJLMS_PKGKidsInterface QUERY functions.
//
//////////////////////////////////////////////////
public:
//////////////////////////////////////////////////
// INSERT
//////////////////////////////////////////////////
    bool                    setKidsInfo(KidsInfo kidsInfo, int iIdxKids);
    
    
//////////////////////////////////////////////////
// UPDATE
//////////////////////////////////////////////////
    bool                    setKidsStage(int iKidsPrimaryKey, int iStage);
    bool                    setKidsStartDate(int iKidsPrimaryKey, std::string strStartDate);
    bool                    setKidsUpdateID(int iKidsPrimaryKey, int iUpdateID);

    
//////////////////////////////////////////////////
// SELECT
//////////////////////////////////////////////////
    int                     getPKGKidsPrimayKey(std::string strPKGCode, int iIdxKids);
    
    KidsInfo                getPKGKidsInfo(int iIdxKids, std::string strPKGcode);
    
    int                     getPKGKidsIdxKids(int iIdxKids, std::string strPKGCode);
    int                     getPKGKidsPrimaryKey(int iIdxKids, std::string strPKGCode);
    int                     getPKGKidsStage(int iIdxKids, std::string strPKGCode);
    int                     getPKGKidsTotalStage(int iIdxKids, std::string strPKGCode);
    std::string             getPKGKidsName(int iIdxKids, std::string strPKGCode);
    std::string             getPKGKidsBirth(int iIdxKids, std::string strPKGCode);
    std::string             getPKGKidsImagePath(int iIdxKids, std::string strPKGCode);
    std::string             getPKGKidsWriteDate(int iIdxKids, std::string strPKGCode);
    std::string             getPKGKidsComplateDate(int iIdxKids, std::string strPKGCode);
    std::string             getPKGKidsPKGCode(int iIdxKids, std::string strPKGCode);
    
    std::vector<KidsInfo>*  getPKGKidsForUpdate(int iIdxKids);
};

#endif /* defined(__SoundPhonics__CJLMS_PKGKidsInterface__) */
