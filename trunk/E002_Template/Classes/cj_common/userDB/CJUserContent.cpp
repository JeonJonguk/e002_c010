//
//  CJUserContent.cpp
//  S001_Template
//
//  Created by Soonho Hong on 12. 10. 24..
//
//

#include "CJUserContent.h"
#include "CJUserDBManage.h"
#include "cocos2d.h"


static CJUserContent *manageInstance;

#pragma mark - base func

CJUserContent::CJUserContent()
{
    
}

CJUserContent::~CJUserContent()
{
    
}

CJUserContent* CJUserContent::sharedInstance()
{
    if(!manageInstance)
    {
        manageInstance  = new CJUserContent();
        
        if (!manageInstance->createTable())
        {
            return false;
        }
    }
    
    return manageInstance;
}

void CJUserContent::releaseInstance()
{
    if (manageInstance)
    {
        delete manageInstance;
        manageInstance = NULL;
    }
}


#pragma mark - manage func

std::string CJUserContent::selectContent(std::string strKeyValue)
{
    UserInforTable data;
    

    sqlite3_stmt* stmt;
    int rst = sqlite3_prepare_v2( CJUserDBManage::sharedInstance()->getDB(), SELECT_CONTENT1, strlen(SELECT_CONTENT1)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return "";
    
    sqlite3_bind_text( stmt, 1, strKeyValue.c_str(), strKeyValue.size(), NULL );
    
    int s;
    
    s = sqlite3_step(stmt);
    
    if (s == SQLITE_ROW) {
        
        data.strSaveValue       = (char*)sqlite3_column_text(stmt,2);
        cocos2d::CCLog("(char*)sqlite3_column_text(stmt,2) = %s",(char*)sqlite3_column_text(stmt,2));

    } else if (s == SQLITE_DONE) {
        data.strSaveValue = "default";
        cocos2d::CCLog("done or no data in CJUserContent\n");
    } else {
        data.strSaveValue = "default";
        cocos2d::CCLog("db select fail. rc : %d, err : %s in CJUserContent\n", s, sqlite3_errmsg(CJUserDBManage::sharedInstance()->getDB()));
    }
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return data.strSaveValue;
}
bool CJUserContent::updateFile(std::string keyValue , std::string strData)
{
    sqlite3_stmt* stmt;
    cocos2d::CCLog("Update call %s key =  %s  strData = %s",__FUNCTION__ , keyValue.c_str() , strData.c_str());
    assert( sqlite3_exec(CJUserDBManage::sharedInstance()->getDB(), "PRAGMA synchronous=OFF;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_exec(CJUserDBManage::sharedInstance()->getDB(), "BEGIN;", NULL, NULL, NULL) == SQLITE_OK);
    
    int rst = sqlite3_prepare_v2( CJUserDBManage::sharedInstance()->getDB(), UPDATE_COLUMN, strlen(UPDATE_COLUMN)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return false;
    sqlite3_bind_text( stmt, 1 , strData.c_str(), strData.size(), NULL );
    sqlite3_bind_text( stmt, 2, keyValue.c_str(), keyValue.size(), NULL );
    
    sqlite3_step(stmt);
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_exec(CJUserDBManage::sharedInstance()->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    return true;
}

bool CJUserContent::insertFile(std::string keyValue , std::string strData)
{
    sqlite3_stmt* stmt;
    
    assert( sqlite3_exec(CJUserDBManage::sharedInstance()->getDB(), "PRAGMA synchronous=OFF;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_exec(CJUserDBManage::sharedInstance()->getDB(), "BEGIN;", NULL, NULL, NULL) == SQLITE_OK);
    
    int rst = sqlite3_prepare_v2( CJUserDBManage::sharedInstance()->getDB(), INSERT_COLUMN, strlen(INSERT_COLUMN)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return false;
    sqlite3_bind_text( stmt, 1 , keyValue.c_str(), keyValue.size(), NULL );
    sqlite3_bind_text( stmt, 2, strData.c_str(), strData.size(), NULL );
    
    sqlite3_step(stmt);
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_exec(CJUserDBManage::sharedInstance()->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
//    CJUserDBManage::sharedInstance()->showAllTable();
    
    return true;
}

bool CJUserContent::createTable()
{
	char    *szErrMsg = NULL;

	if ( sqlite3_exec(CJUserDBManage::sharedInstance()->getDB(), CREATE_TABLE, NULL, NULL, &szErrMsg) != SQLITE_OK )
	{
		printf("db error message (content) : %s\n", szErrMsg);
		sqlite3_close(CJUserDBManage::sharedInstance()->getDB());
		return false;
	} else {
		return true;
	}
}

bool CJUserContent::dropTable()
{
	char    *szErrMsg = NULL;

	if ( sqlite3_exec(CJUserDBManage::sharedInstance()->getDB(), DROP_TABLE, NULL, NULL, &szErrMsg) != SQLITE_OK )
	{
		printf("db error message (content) : %s\n", szErrMsg);
		sqlite3_close(CJUserDBManage::sharedInstance()->getDB());
		return false;
	} else {
		return true;
	}
}
