//
//  CJLMSInfoManage.cpp
//  S001_Template
//
//  Created by Soonho Hong on 12. 10. 24..
//
//

#include "CJLMSDBManage.h"
#include "CJLMSExtension.h"
#include "CJLMSDataStorage.h"
#include "cocos2d.h"

using namespace LMSExtension;


#pragma mark - base func
CJLMSDBManage::CJLMSDBManage(CJLMSDataStorage *pDataStorage)
{
    m_lmsDataStorage = pDataStorage;
}

CJLMSDBManage::~CJLMSDBManage()
{
    
}

CJLMSDBManage* CJLMSDBManage::create(CJLMSDataStorage *pDataStorage)
{
    CJLMSDBManage *ret = new CJLMSDBManage(pDataStorage);
    if(NULL != ret)
    {
        ret->open();
        return ret;
    }
    else
    {
        delete ret;
        return NULL;
    }
}




#pragma mark - user func
sqlite3* CJLMSDBManage::getDB()
{
	CJLMSExtension::sharedInstance()->checkStorageSize();
    if (m_db != NULL)
    {
        return m_db;
    }
    else
    {
        return 0;
    }
}

int CJLMSDBManage::open()
{
    m_db = NULL;
    
    int rc = sqlite3_open(m_lmsDataStorage->getDBPath().c_str(), &m_db);
    if(rc != SQLITE_OK) {
        printf("fail to open db file.\n");
        sqlite3_close(m_db);
        return rc;
    }
    
    sqlite3_busy_timeout(m_db, 2000);
    
    printf("open db file.\n");
    return rc;
}

bool CJLMSDBManage::close()
{
    if (m_db == NULL) return false;
    
    
    int numOfRetries = 0;
    int rc;
    
    do {
        rc = sqlite3_close(m_db);

        if (rc == SQLITE_OK) {
            printf("SQLite close.\n");
            break;
        }
        
        if (rc == SQLITE_BUSY) {
            if (numOfRetries == m_lmsDataStorage->getDBConnectionTimeOut()) {
                printf("SQLite Busy, unable to close.\n");
                break;
            }
        } else {
            printf("SQLite Closing Error: %s\n", sqlite3_errmsg(m_db));
            break;
        }
    } while (numOfRetries++ > m_lmsDataStorage->getDBConnectionTimeOut());
    
    m_db = NULL;
    
    return true;
}
