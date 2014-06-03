//
//  CJLMSProgress.cpp
//  S001_Template
//
//  Created by Soonho Hong on 12. 10. 24..
//
//

#include "CJLMSProgress.h"
#include "CJLMSDefines.h"

// DEFINE QUERY
#define CREATE_TABLE            "CREATE TABLE IF NOT EXISTS tblProgress (oidProgress INTEGER PRIMARY KEY  NOT NULL  DEFAULT (0) ,oidPKGKids INTEGER NOT NULL  DEFAULT (0) ,oidContentId INTEGER NOT NULL  DEFAULT (0) ,nMenuNum INTEGER NOT NULL  DEFAULT (0) ,nCount INTEGER NOT NULL  DEFAULT (0) ,nUpdateId INTEGER NOT NULL  DEFAULT (0) ,dtStartDate DATETIME NOT NULL  DEFAULT (CURRENT_DATE) ,dtEndDate DATETIME NOT NULL  DEFAULT (CURRENT_DATE) ,strKey VARCHAR);"
#define INSERT_COLUMN           "INSERT INTO tblProgress (oidPKGKids,oidContentId,nMenuNum,dtStartDate,dtEndDate) VALUES (?,?,?,?,?)"
#define INSERT_COLUMN2          "INSERT INTO tblProgress (oidPKGKids,oidContentId,nMenuNum,dtStartDate,dtEndDate, nCount, strKey) VALUES (?,?,?,?,?,?,?)"
#define SELECT_PROGRESSLIST     "SELECT * FROM tblProgress WHERE oidPKGKids = ? AND oidContentId = ?"
#define SELECT_UPDATEPROGRESS   "SELECT * FROM tblProgress WHERE oidPKGKids = ? AND oidContentId = ? AND nUpdateId = 0"
#define SELECT_PROGRESS         "SELECT * FROM tblProgress WHERE oidPKGKids = ? AND oidContentId = ? AND nMenuNum = ?"
#define SELECT_PROGRESS2        "SELECT * FROM tblProgress WHERE strKey = ?"
#define SELECT_KEY              "SELECT strKey FROM tblProgress WHERE oidPKGKids = ? AND oidContentId = ? AND nMenuNum = ?"
#define UPDATE_COUNT            "UPDATE tblProgress SET nCount = ? WHERE  oidPKGKids = ? AND oidContentId = ?  AND nMenuNum = ?"
#define UPDATE_ENDDATE          "UPDATE tblProgress SET dtEndDate = ? WHERE  oidPKGKids = ? AND oidContentId = ?  AND nMenuNum = ?"
#define UPDATE_UPDATEID         "UPDATE tblProgress SET nUpdateId = ? WHERE  oidPKGKids = ? AND oidContentId = ?  AND nMenuNum = ?"
#define UPDATE_KEY              "UPDATE tblProgress SET strKey = ? WHERE  oidPKGKids = ? AND oidContentId = ?  AND nMenuNum = ?"




#pragma mark - base func
CJLMSProgress::CJLMSProgress()
{
    
}

CJLMSProgress::CJLMSProgress(CJLMSDBManage *pLmsDBManage)
{
    m_lmsDBManage = pLmsDBManage;
}

CJLMSProgress::~CJLMSProgress()
{
    m_lmsDBManage = NULL;
}

CJLMSProgress* CJLMSProgress::create(CJLMSDBManage *pLmsDBManage)
{
    CJLMSProgress *ret = new CJLMSProgress(pLmsDBManage);
    if(NULL != ret && true == ret->init())
    {
        return ret;
    }
    else
    {
        delete ret;
        ret = NULL;
        
        return false;
    }
}

bool CJLMSProgress::init()
{
    char    *szErrMsg = NULL;
    int     rc = sqlite3_exec(m_lmsDBManage->getDB(), CREATE_TABLE, NULL, NULL, &szErrMsg);
    
    if(rc != SQLITE_OK)
    {
        printf("db error message (pkgprogress) : %s\n", szErrMsg);
        sqlite3_close(m_lmsDBManage->getDB());
        
        return false;
    }
    
    return true;
}





#pragma mark - manage func
std::vector<Progress>* CJLMSProgress::selectProgressList(int kidsId, int contentId)
{
    std::vector<Progress> *proc = new std::vector<Progress>();
    
    sqlite3_stmt* stmt;
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_PROGRESSLIST, strlen(SELECT_PROGRESSLIST)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return proc;
    
    
    sqlite3_bind_int( stmt, 1, kidsId);
    sqlite3_bind_int( stmt, 2, contentId);
    
    while (1) {
        int s;
        
        s = sqlite3_step(stmt);
        
        if (s == SQLITE_ROW) {
            Progress data;
            
            data.iProgressId            = sqlite3_column_int(stmt, 0);
            data.iKidsId                = sqlite3_column_int(stmt, 1);
            data.iContentId             = sqlite3_column_int(stmt, 2);
            data.iMenuNum               = sqlite3_column_int(stmt, 3);
            data.nCount                 = sqlite3_column_int(stmt, 4);
            data.iUpdateId              = sqlite3_column_int(stmt, 5);
            data.szStartDate.append((char*)sqlite3_column_text(stmt, 6));
            data.szEndDate.append((char*)sqlite3_column_text(stmt, 7));
            data.szKey.append((char*)sqlite3_column_text(stmt, 8));
            
            proc->push_back(data);
        } else if (s == SQLITE_DONE) {
            printf("done or no data in CJLMSProgress\n");
            sqlite3_reset( stmt );

            assert( sqlite3_finalize(stmt) == SQLITE_OK);
            break;
        } else {
            printf("db select fail. rc : %d, err : %s in CJLMSProgress\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
            break;
        }
    }
    
    return proc;
}

std::vector<Progress>* CJLMSProgress::selectUpdateProgress(int kidsId, int contentId)
{
    std::vector<Progress> *proc = new std::vector<Progress>();
    
    sqlite3_stmt* stmt;
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_UPDATEPROGRESS, strlen(SELECT_UPDATEPROGRESS)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return proc;
    
    
    sqlite3_bind_int( stmt, 1, kidsId);
    sqlite3_bind_int( stmt, 2, contentId);
    
    while (1) {
        int s;
        
        s = sqlite3_step(stmt);
        
        if (s == SQLITE_ROW) {
            Progress data;
            
            data.iProgressId            = sqlite3_column_int(stmt, 0);
            data.iKidsId                = sqlite3_column_int(stmt, 1);
            data.iContentId             = sqlite3_column_int(stmt, 2);
            data.iMenuNum               = sqlite3_column_int(stmt, 3);
            data.nCount                 = sqlite3_column_int(stmt, 4);
            data.iUpdateId              = sqlite3_column_int(stmt, 5);
            data.szStartDate.append((char*)sqlite3_column_text(stmt, 6));
            data.szEndDate.append((char*)sqlite3_column_text(stmt, 7));
            data.szKey.append((char*)sqlite3_column_text(stmt, 8));
            
            proc->push_back(data);
        } else if (s == SQLITE_DONE) {
            printf("done or no data in CJLMSProgress\n");
            sqlite3_reset( stmt );
            
            assert( sqlite3_finalize(stmt) == SQLITE_OK);
            break;
        } else {
            printf("db select fail. rc : %d, err : %s in CJLMSProgress\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
            break;
        }
    }
    
    return proc;
}

Progress CJLMSProgress::selectProgress(int kidsId, int contentId, int menuNum)
{
    Progress data;
    
    sqlite3_stmt* stmt;
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_PROGRESS, strlen(SELECT_PROGRESS)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return data;
    
    sqlite3_bind_int( stmt, 1, kidsId);
    sqlite3_bind_int( stmt, 2, contentId);
    sqlite3_bind_int( stmt, 3, menuNum);
    
    int s;
    
    s = sqlite3_step(stmt);
    
    if (s == SQLITE_ROW) {
        data.iProgressId            = sqlite3_column_int(stmt, 0);
        data.iKidsId                = sqlite3_column_int(stmt, 1);
        data.iContentId             = sqlite3_column_int(stmt, 2);
        data.iMenuNum               = sqlite3_column_int(stmt, 3);
        data.nCount                 = sqlite3_column_int(stmt, 4);
        data.iUpdateId              = sqlite3_column_int(stmt, 5);
        data.szStartDate.append((char*)sqlite3_column_text(stmt, 6));
        data.szEndDate.append((char*)sqlite3_column_text(stmt, 7));
        data.szKey.append((char*)sqlite3_column_text(stmt, 8));
    } else if (s == SQLITE_DONE) {
        printf("done or no data in CJLMSProgress\n");
        data.iUpdateId = DB_ERROR;
    } else {
        printf("db select fail. rc : %d, err : %s in CJLMSProgress\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
    }
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return data;
}

bool CJLMSProgress::isExistProgress(std::string key)
{
	bool ret = false;

	sqlite3_stmt* stmt;

	int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_PROGRESS2, strlen(SELECT_PROGRESS2)+1, &stmt, NULL );
	if( rst != SQLITE_OK ) return ret;

	sqlite3_bind_text( stmt, 1, key.c_str(), key.size(), NULL );

	int s;

	s = sqlite3_step(stmt);

	if (s == SQLITE_ROW) {
		ret = true;
	}

	sqlite3_reset( stmt );

	assert( sqlite3_finalize(stmt) == SQLITE_OK);

	return ret;
}

std::string CJLMSProgress::selectKey(int kidsId, int contentId, int menuNum)
{
    std::string key;
    
    sqlite3_stmt* stmt;
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_KEY, strlen(SELECT_KEY)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return false;
    
    sqlite3_bind_int( stmt, 1, kidsId);
    sqlite3_bind_int( stmt, 2, contentId);
    sqlite3_bind_int( stmt, 3, menuNum);
    
    int s;
    
    s = sqlite3_step(stmt);
    
    if (s == SQLITE_ROW) {
        key.append((char*)sqlite3_column_text(stmt, 0));
    } else if (s == SQLITE_DONE) {
        printf("done or no data in CJLMSProgress\n");
        std::stringstream intValue;
        intValue << DB_ERROR;
        key.append("no data ");
        key.append(intValue.str());
    } else {
        printf("db select fail. rc : %d, err : %s in CJLMSProgress\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
        std::stringstream intValue;
        intValue << DB_ERROR;
        key.append(("db select fail "));
        key.append(intValue.str());
    }
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return key;
}

bool CJLMSProgress::updateCount(int kidsId, int contentId, int menuNum)
{
    int count = this->selectProgress(kidsId, contentId, menuNum).nCount;
    
    count++;
    
    sqlite3_stmt* stmt;
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "PRAGMA synchronous=OFF;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "BEGIN;", NULL, NULL, NULL) == SQLITE_OK);
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), UPDATE_COUNT, strlen(UPDATE_COUNT)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return false;
    
    sqlite3_bind_int( stmt, 1, count);
    sqlite3_bind_int( stmt, 2, kidsId);
    sqlite3_bind_int( stmt, 3, contentId);
    sqlite3_bind_int( stmt, 4, menuNum);
    
    sqlite3_step(stmt);
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    this->updateUpdateId(kidsId, contentId, menuNum, 0);  // when update value, change update id (v1.0.3)
    
    return true;
}

bool CJLMSProgress::updateCount(int kidsId, int contentId, int menuNum, int count)
{
	int dbCount = this->selectProgress(kidsId, contentId, menuNum).nCount;

	if (dbCount >= count) {
		return true;
	}

	sqlite3_stmt* stmt;

	assert( sqlite3_exec(m_lmsDBManage->getDB(), "PRAGMA synchronous=OFF;", NULL, NULL, NULL) == SQLITE_OK);
	assert( sqlite3_exec(m_lmsDBManage->getDB(), "BEGIN;", NULL, NULL, NULL) == SQLITE_OK);

	int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), UPDATE_COUNT, strlen(UPDATE_COUNT)+1, &stmt, NULL );
	if( rst != SQLITE_OK ) return false;

	sqlite3_bind_int( stmt, 1, count);
	sqlite3_bind_int( stmt, 2, kidsId);
	sqlite3_bind_int( stmt, 3, contentId);
	sqlite3_bind_int( stmt, 4, menuNum);

	sqlite3_step(stmt);

	sqlite3_reset( stmt );

	assert( sqlite3_exec(m_lmsDBManage->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
	assert( sqlite3_finalize(stmt) == SQLITE_OK);

	return true;
}

bool CJLMSProgress::updateEndDate(Progress data)
{
    sqlite3_stmt* stmt;
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "PRAGMA synchronous=OFF;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "BEGIN;", NULL, NULL, NULL) == SQLITE_OK);
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), UPDATE_ENDDATE, strlen(UPDATE_ENDDATE)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return false;
    
    sqlite3_bind_text( stmt, 1, data.szEndDate.c_str(), data.szEndDate.size(), NULL );
    sqlite3_bind_int( stmt, 2, data.iKidsId);
    sqlite3_bind_int( stmt, 3, data.iContentId);
    sqlite3_bind_int( stmt, 4, data.iMenuNum);
    
    sqlite3_step(stmt);
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    this->updateUpdateId(data.iKidsId, data.iContentId, data.iMenuNum, 0);    // when update value, change update id (v1.0.3)
    
    return true;
}

bool CJLMSProgress::updateUpdateId(int kidsId, int contentId, int menuNum, int updateId)
{
    sqlite3_stmt* stmt;
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "PRAGMA synchronous=OFF;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "BEGIN;", NULL, NULL, NULL) == SQLITE_OK);
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), UPDATE_UPDATEID, strlen(UPDATE_UPDATEID)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return false;
    
    sqlite3_bind_int( stmt, 1, updateId);
    sqlite3_bind_int( stmt, 2, kidsId);
    sqlite3_bind_int( stmt, 3, contentId);
    sqlite3_bind_int( stmt, 4, menuNum);
    
    sqlite3_step(stmt);
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return true;
}

bool CJLMSProgress::insertProgress(Progress data, int idxKids)
{
    if (this->selectProgress(data.iKidsId, data.iContentId, data.iMenuNum).iUpdateId !=  DB_ERROR) {
    	this->updateEndDate(data);
    	return true;
    }
    
    sqlite3_stmt* stmt;
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "PRAGMA synchronous=OFF;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "BEGIN;", NULL, NULL, NULL) == SQLITE_OK);
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), INSERT_COLUMN, strlen(INSERT_COLUMN)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return false;
    
    sqlite3_bind_int( stmt, 1, data.iKidsId);
    sqlite3_bind_int( stmt, 2, data.iContentId);
    sqlite3_bind_int( stmt, 3, data.iMenuNum);
    sqlite3_bind_text( stmt, 4, data.szStartDate.c_str(), data.szStartDate.size(), NULL );
    sqlite3_bind_text( stmt, 5, data.szEndDate.c_str(), data.szEndDate.size(), NULL );
    
    sqlite3_step(stmt);
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    this->updateKey(data.iKidsId, data.iContentId, data.iMenuNum, data.szKey, idxKids);
    
    this->updateUpdateId(data.iKidsId, data.iContentId, data.iMenuNum, 0);    // when update value, change update id (v1.0.3)
    
    return true;
}

bool CJLMSProgress::insertProgressWithCount(Progress data, int count)
{
	if (this->selectProgress(data.iKidsId, data.iContentId, data.iMenuNum).iUpdateId !=  DB_ERROR) {
		this->updateEndDate(data);
		this->updateCount(data.iKidsId, data.iContentId, data.iMenuNum, count);
		this->updateUpdateId(data.iKidsId, data.iContentId, data.iMenuNum, 1);
		return true;
	}

    sqlite3_stmt* stmt;

    assert( sqlite3_exec(m_lmsDBManage->getDB(), "PRAGMA synchronous=OFF;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "BEGIN;", NULL, NULL, NULL) == SQLITE_OK);

    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), INSERT_COLUMN2, strlen(INSERT_COLUMN2)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return false;

    sqlite3_bind_int( stmt, 1, data.iKidsId);
    sqlite3_bind_int( stmt, 2, data.iContentId);
    sqlite3_bind_int( stmt, 3, data.iMenuNum);
    sqlite3_bind_text( stmt, 4, data.szStartDate.c_str(), data.szStartDate.size(), NULL );
    sqlite3_bind_text( stmt, 5, data.szEndDate.c_str(), data.szEndDate.size(), NULL );
    sqlite3_bind_int( stmt, 6, count);
    sqlite3_bind_text( stmt, 7, data.szKey.c_str(), data.szKey.size(), NULL );

    sqlite3_step(stmt);

    sqlite3_reset( stmt );

    assert( sqlite3_exec(m_lmsDBManage->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_finalize(stmt) == SQLITE_OK);

    this->updateUpdateId(data.iKidsId, data.iContentId, data.iMenuNum, 1);

    return true;
}

#pragma mark - private func

bool CJLMSProgress::updateKey(int kidsId, int contentId, int menuNum, std::string key, int idxKids)
{
    sqlite3_stmt* stmt;
    
    int row = 0;
    
    char* sql = (char*)"SELECT last_insert_rowid()";
    
    sqlite3_prepare(m_lmsDBManage->getDB(), sql, strlen(sql)+1, &stmt, NULL);
    
    int s;
    
    s = sqlite3_step(stmt);
    
    if (s == SQLITE_ROW) {
        row = sqlite3_column_int(stmt, 0);
        
        sqlite3_reset( stmt );
        
        assert( sqlite3_finalize(stmt) == SQLITE_OK);
    } else if (s == SQLITE_DONE) {
        printf("done or no data in CJLMSProgress\n");
        
        sqlite3_reset( stmt );
        
        assert( sqlite3_finalize(stmt) == SQLITE_OK);
    } else {
        printf("db select fail. rc : %d, err : %s in CJLMSProgress\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
    }
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "PRAGMA synchronous=OFF;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "BEGIN;", NULL, NULL, NULL) == SQLITE_OK);
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), UPDATE_KEY, strlen(UPDATE_KEY)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return false;
    
    std::string tempKey = key;
    
    std::stringstream index;
    index << row;
    tempKey.append(index.str());
    tempKey.append("_");
    std::stringstream streamIdxKids;
    streamIdxKids << idxKids;
    tempKey.append(streamIdxKids.str());
    
    sqlite3_bind_text( stmt, 1, tempKey.c_str(), tempKey.size(), NULL );
    sqlite3_bind_int( stmt, 2, kidsId);
    sqlite3_bind_int( stmt, 3, contentId);
    sqlite3_bind_int( stmt, 4, menuNum);
    
    sqlite3_step(stmt);
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return true;
}