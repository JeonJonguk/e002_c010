//
//  CJLMSInfoManage.cpp
//  S001_Template
//
//  Created by Soonho Hong on 12. 10. 24..
//
//

#include "CJUserDBManage.h"
#include "CCFileUtils.h"
#include "CJUserContent.h"
#include "CJLMSExtension.h"
#include "CJSaveDataInterface.h"
#include "cocos2d.h"

using namespace LMSExtension;

static CJUserDBManage *manageInstance;

#pragma mark - base func

CJUserDBManage::CJUserDBManage()
{
    busyRetryTimeout = 1;
    
}

CJUserDBManage::~CJUserDBManage()
{
    
}

CJUserDBManage* CJUserDBManage::sharedInstance()
{
    if(!manageInstance)
    {
        manageInstance  = new CJUserDBManage();
        
    }
    
    return manageInstance;
}

void CJUserDBManage::releaseInstance()
{
    if (manageInstance)
    {
        manageInstance->close();
        
        delete manageInstance;
        manageInstance = NULL;
    }
}


sqlite3* CJUserDBManage::getDB()
{
//	CJLMSExtension::sharedInstance()->checkStorageSize();

    if (m_db != NULL) {
        return m_db;
    } else {
        return 0;
    }
}

#pragma mark - private func

bool CJUserDBManage::open(int platform)
{
    m_db = NULL;
    
    
    std::string dbpath;
//    dbpath.append(m_sWritePath);
    if(platform ==1)
        dbpath = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath();
    else if(platform == 2) {    // android
        
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        dbpath = CJSaveDataInterface::sharedInstance()->getHiddenDirPath();
        #endif
    }
    dbpath.append("/");
    dbpath.append(DB_USER_NAME);
    int rc = sqlite3_open(dbpath.c_str(), &m_db);
    if(rc != SQLITE_OK) {
        printf("fail to open db file.\n");
        sqlite3_close(m_db);
        return false;
    }
    
    sqlite3_busy_timeout(m_db, 2000);
    
    printf("open db file.\n");
    return true;
}

bool CJUserDBManage::close()
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
            if (numOfRetries == busyRetryTimeout) {
                printf("SQLite Busy, unable to close.\n");
                break;
            }
        } else {
            printf("SQLite Closing Error: %s\n", sqlite3_errmsg(m_db));
            break;
        }
    } while (numOfRetries++ > busyRetryTimeout);
    
    m_db = NULL;
    
    return true;
}
