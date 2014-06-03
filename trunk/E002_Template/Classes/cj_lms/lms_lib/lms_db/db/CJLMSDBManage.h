//
//  CJLMSDBManage.h
//  S001_Template
//
//  Created by Soonho Hong on 12. 10. 24..
//
//

#ifndef CJLMSDBManage_h
#define CJLMSDBManage_h

#pragma once

#include "CJLMSStruct.h"

class CJLMSDataStorage;

/**
 * @author CJEducations
 * @brief db file manage class (modify open, setWritePath func)
 * @version v1.0.4
 * @date 2012. 11. 28
 * @since v1.0.0
 */
class CJLMSDBManage
{
public:
    CJLMSDBManage(CJLMSDataStorage *pDataStorage);
    ~CJLMSDBManage();
    static CJLMSDBManage* create(CJLMSDataStorage *pDataStorage);
    
    sqlite3* getDB();
    
    
private:
    CJLMSDataStorage *m_lmsDataStorage;
    sqlite3* m_db;
    
    int open();
    bool close();
};

#endif
