//
//  CJLMSKidsContent.cpp
//  S001_Template
//
//  Created by Soonho Hong on 12. 10. 24..
//
//

#include "CJLMSKidsContent.h"
#include "CJLMSDefines.h"

// DEFINE QUERY
#define CREATE_TABLE            "CREATE TABLE IF NOT EXISTS tblKidsContent (oidKidsContent INTEGER PRIMARY KEY  NOT NULL  DEFAULT (0) ,oidPKGKids INTEGER NOT NULL  DEFAULT (0) ,oidContentId INTEGER NOT NULL  DEFAULT (0) ,nCount INTEGER NOT NULL  DEFAULT (0) ,nGrade INTEGER NOT NULL  DEFAULT (-1) ,nUpdateId INTEGER NOT NULL  DEFAULT (0) ,dtStartDate DATETIME NOT NULL  DEFAULT (CURRENT_DATE) ,dtEndDate DATETIME NOT NULL  DEFAULT (CURRENT_DATE) ,strKey VARCHAR);"
#define INSERT_COLUMN           "INSERT INTO tblKidsContent (oidPKGKids,oidContentId,dtStartDate,dtEndDate) VALUES (?,?,?,?)"
#define SELECT_KIDSCONTENT1     "SELECT * FROM tblKidsContent WHERE oidPKGKids = ? AND oidContentId = ?"
#define SELECT_KIDSCONTENT2     "SELECT * FROM tblKidsContent WHERE oidPKGKids = ? AND oidContentId = ?"
#define SELECT_ALLKIDSCONTENT   "SELECT * FROM tblKidsContent WHERE oidPKGKids = ? AND nUpdateId = 0"
#define SELECT_KEY              "SELECT strKey FROM tblKidsContent WHERE oidPKGKids = ? AND oidContentId = ?"
#define SELECT_COUNT            "SELECT nCount FROM tblKidsContent WHERE oidPKGKids = ? AND oidContentId = ?"
#define UPDATE_COUNT            "UPDATE tblKidsContent SET nCount = ? WHERE  oidPKGKids = ? AND oidContentId = ?"
#define UPDATE_GRADE            "UPDATE tblKidsContent SET nGrade = ? WHERE  oidPKGKids = ? AND oidContentId = ?"
#define UPDATE_STARTDATE        "UPDATE tblKidsContent SET dtStartDate = ? WHERE  oidPKGKids = ? AND oidContentId = ?"
#define UPDATE_ENDDATE          "UPDATE tblKidsContent SET dtEndDate = ? WHERE  oidPKGKids = ? AND oidContentId = ?"
#define UPDATE_UPDATEID         "UPDATE tblKidsContent SET nUpdateId = ? WHERE  oidPKGKids = ? AND oidContentId = ?"
#define UPDATE_KEY              "UPDATE tblKidsContent SET strKey = ? WHERE  oidPKGKids = ? AND oidContentId = ?"




#pragma mark - base func
CJLMSKidsContent::CJLMSKidsContent()
{
    
}

CJLMSKidsContent::CJLMSKidsContent(CJLMSDBManage *pLmsDBManage)
{
    m_lmsDBManage = pLmsDBManage;
}

CJLMSKidsContent::~CJLMSKidsContent()
{
    m_lmsDBManage = NULL;
}

CJLMSKidsContent* CJLMSKidsContent::create(CJLMSDBManage *pLmsDBManage)
{
    CJLMSKidsContent *ret = new CJLMSKidsContent(pLmsDBManage);
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

bool CJLMSKidsContent::init()
{
    char    *szErrMsg = NULL;
    int     rc = sqlite3_exec(m_lmsDBManage->getDB(), CREATE_TABLE, NULL, NULL, &szErrMsg);
    
    if(rc != SQLITE_OK)
    {
        printf("db error message (kidscontent) : %s\n", szErrMsg);
        sqlite3_close(m_lmsDBManage->getDB());
        
        return false;
    }
    
    return true;
}





#pragma mark - manage func
KidsContent CJLMSKidsContent::selectKidsContent(int kidsId, int contentId)
{
    KidsContent data;
    data.iKidsContentId     = INT_DEFAULT;
    data.iKidsId            = INT_DEFAULT;
    data.iContentId         = INT_DEFAULT;;
    data.nCount             = INT_DEFAULT;
    data.nGrade             = INT_DEFAULT;
    data.iUpdateId          = INT_DEFAULT;
    data.szStartDate        = "";
    data.szEndDate          = "";
    data.szKey              = "";
    
    sqlite3_stmt* stmt;
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_KIDSCONTENT1, strlen(SELECT_KIDSCONTENT1)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return data;
    
    sqlite3_bind_int( stmt, 1, kidsId);
    sqlite3_bind_int( stmt, 2, contentId);
    
    int s;
    
    s = sqlite3_step(stmt);
    
    if (s == SQLITE_ROW) {
        data.iKidsContentId         = sqlite3_column_int(stmt, 0);
        data.iKidsId                = sqlite3_column_int(stmt, 1);
        data.iContentId             = sqlite3_column_int(stmt, 2);
        data.nCount                 = sqlite3_column_int(stmt, 3);
        data.nGrade                 = sqlite3_column_int(stmt, 4);
        data.iUpdateId              = sqlite3_column_int(stmt, 5);
        data.szStartDate.append((char*)sqlite3_column_text(stmt, 6));
        data.szEndDate.append((char*)sqlite3_column_text(stmt, 7));
        data.szKey.append((char*)sqlite3_column_text(stmt, 8));
    } else if (s == SQLITE_DONE) {
        data.iKidsContentId = DB_ERROR;   // error code
        printf("done or no data in CJLMSKidsContent\n");
    } else {
        data.iKidsContentId = DB_ERROR;   // error code
        printf("db select fail. rc : %d, err : %s in CJLMSKidsContent\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
    }
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return data;
}

std::vector<KidsContent>* CJLMSKidsContent::selectKidsContents(int kidsId)
{
    std::vector<KidsContent> *kidsContents = new std::vector<KidsContent>();
    
    sqlite3_stmt* stmt;
    std::string query = "select * from tblKidsContent where nCount >= 1 AND oidPKGKids= ? order by  oidContentId asc";
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), query.c_str(), query.size(), &stmt, NULL );
    if( rst != SQLITE_OK ) return false;
    
    sqlite3_bind_int( stmt, 1, kidsId);
    
    while (1) {
        int s;
        
        s = sqlite3_step(stmt);
        
        if (s == SQLITE_ROW) {
            KidsContent data;
            
            data.iKidsContentId         = sqlite3_column_int(stmt, 0);
            data.iKidsId                = sqlite3_column_int(stmt, 1);
            data.iContentId             = sqlite3_column_int(stmt, 2);
            data.nCount                 = sqlite3_column_int(stmt, 3);
            data.nGrade                 = sqlite3_column_int(stmt, 4);
            data.iUpdateId              = sqlite3_column_int(stmt, 5);
            data.szStartDate.append((char*)sqlite3_column_text(stmt, 6));
            data.szEndDate.append((char*)sqlite3_column_text(stmt, 7));
            data.szKey.append((char*)sqlite3_column_text(stmt, 8));
            
            kidsContents->push_back(data);
        } else if (s == SQLITE_DONE) {
            printf("done or no data in CJLMSKidsContent\n");
            sqlite3_reset( stmt );
            
            assert( sqlite3_finalize(stmt) == SQLITE_OK);
            break;
        } else {
            printf("db select fail. rc : %d, err : %s in CJLMSKidsContent\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
            break;
        }
    }
    
    return kidsContents;
}

std::vector<KidsContent>* CJLMSKidsContent::selectUpdateKidsContent(int kidsId)
{
    std::vector<KidsContent> *kidsContents = new std::vector<KidsContent>();
    
    sqlite3_stmt* stmt;
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_ALLKIDSCONTENT, strlen(SELECT_ALLKIDSCONTENT)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return false;
    
    sqlite3_bind_int( stmt, 1, kidsId);
    
    while (1) {
        int s;
        
        s = sqlite3_step(stmt);
        
        if (s == SQLITE_ROW) {
            KidsContent data;
            
            data.iKidsContentId         = sqlite3_column_int(stmt, 0);
            data.iKidsId                = sqlite3_column_int(stmt, 1);
            data.iContentId             = sqlite3_column_int(stmt, 2);
            data.nCount                 = sqlite3_column_int(stmt, 3);
            data.nGrade                 = sqlite3_column_int(stmt, 4);
            data.iUpdateId              = sqlite3_column_int(stmt, 5);
            data.szStartDate.append((char*)sqlite3_column_text(stmt, 6));
            data.szEndDate.append((char*)sqlite3_column_text(stmt, 7));
            data.szKey.append((char*)sqlite3_column_text(stmt, 8));
            
            kidsContents->push_back(data);
        } else if (s == SQLITE_DONE) {
            printf("done or no data in CJLMSKidsContent\n");
            sqlite3_reset( stmt );
            
            assert( sqlite3_finalize(stmt) == SQLITE_OK);
            break;
        } else {
            printf("db select fail. rc : %d, err : %s in CJLMSKidsContent\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
            break;
        }
    }
    
    return kidsContents;
}



std::string CJLMSKidsContent::selectKey(int kidsId, int contentId)
{
    std::string key;
    
    sqlite3_stmt* stmt;
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_KEY, strlen(SELECT_KEY)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return false;
    
    sqlite3_bind_int( stmt, 1, kidsId);
    sqlite3_bind_int( stmt, 2, contentId);
    
    int s;
    
    s = sqlite3_step(stmt);
    
    if (s == SQLITE_ROW) {
        key.append((char*)sqlite3_column_text(stmt, 0));
    } else if (s == SQLITE_DONE) {
        printf("done or no data in CJLMSKidsContent\n");
        std::stringstream intValue;
        intValue << DB_ERROR;
        key.append("no data ");
        key.append(intValue.str());
    } else {
        printf("db select fail. rc : %d, err : %s in CJLMSKidsContent\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
        std::stringstream intValue;
        intValue << DB_ERROR;
        key.append(("db select fail "));
        key.append(intValue.str());
    }
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return key;
}

int CJLMSKidsContent::selectCount(int kidsId, int contentId)
{
    int count = 0;
    
    sqlite3_stmt* stmt;
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_COUNT, strlen(SELECT_COUNT)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return false;
    
    sqlite3_bind_int( stmt, 1, kidsId);
    sqlite3_bind_int( stmt, 2, contentId);
    
    int s;
    
    s = sqlite3_step(stmt);
    
    if (s == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    } else if (s == SQLITE_DONE) {
        printf("done or no data in CJLMSKidsContent\n");
        count = DB_ERROR;
    } else {
        printf("db select fail. rc : %d, err : %s in CJLMSKidsContent\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
        count = DB_ERROR;
    }
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return count;
}

bool CJLMSKidsContent::updateCount(int kidsId, int contentId, int cnt)
{
    sqlite3_stmt* stmt;
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "PRAGMA synchronous=OFF;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "BEGIN;", NULL, NULL, NULL) == SQLITE_OK);
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), UPDATE_COUNT, strlen(UPDATE_COUNT)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return false;
    
    sqlite3_bind_int( stmt, 1, cnt);
    sqlite3_bind_int( stmt, 2, kidsId);
    sqlite3_bind_int( stmt, 3, contentId);
    
    sqlite3_step(stmt);
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    this->updateUpdateId(kidsId, contentId, 0);   // when update value, change update id (v1.0.2)
    
    return true;
}

bool CJLMSKidsContent::updateGrade(int kidsId, int contentId, int grade)
{
    sqlite3_stmt* stmt;
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "PRAGMA synchronous=OFF;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "BEGIN;", NULL, NULL, NULL) == SQLITE_OK);
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), UPDATE_GRADE, strlen(UPDATE_GRADE)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return false;
    
    sqlite3_bind_int( stmt, 1, grade);
    sqlite3_bind_int( stmt, 2, kidsId);
    sqlite3_bind_int( stmt, 3, contentId);
    
    sqlite3_step(stmt);
    sqlite3_reset( stmt );
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    this->updateUpdateId(kidsId, contentId, 0);   // when update value, change update id (v1.0.2)
    
    return true;
}

bool CJLMSKidsContent::updateEndDate(int kidsId, int contentId, std::string date)
{
    sqlite3_stmt* stmt;
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "PRAGMA synchronous=OFF;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "BEGIN;", NULL, NULL, NULL) == SQLITE_OK);
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), UPDATE_ENDDATE, strlen(UPDATE_ENDDATE)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return false;
    
    sqlite3_bind_text( stmt, 1, date.c_str(), date.size(), NULL );
    sqlite3_bind_int( stmt, 2, kidsId);
    sqlite3_bind_int( stmt, 3, contentId);
    
    sqlite3_step(stmt);
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    this->updateUpdateId(kidsId, contentId, 0);   // when update value, change update id (v1.0.2)
    
    return true;
}

bool CJLMSKidsContent::updateStartDate(int kidsId, int contentId, std::string date)
{
    sqlite3_stmt* stmt;

    assert( sqlite3_exec(m_lmsDBManage->getDB(), "PRAGMA synchronous=OFF;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "BEGIN;", NULL, NULL, NULL) == SQLITE_OK);

    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), UPDATE_STARTDATE, strlen(UPDATE_STARTDATE)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return false;

    sqlite3_bind_text( stmt, 1, date.c_str(), date.size(), NULL );
    sqlite3_bind_int( stmt, 2, kidsId);
    sqlite3_bind_int( stmt, 3, contentId);

    sqlite3_step(stmt);

    sqlite3_reset( stmt );

    assert( sqlite3_exec(m_lmsDBManage->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_finalize(stmt) == SQLITE_OK);

    return true;
}

bool CJLMSKidsContent::updateUpdateId(int kidsId, int contentId, int updateId)
{
    sqlite3_stmt* stmt;
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "PRAGMA synchronous=OFF;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "BEGIN;", NULL, NULL, NULL) == SQLITE_OK);
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), UPDATE_UPDATEID, strlen(UPDATE_UPDATEID)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return false;
    
    sqlite3_bind_int( stmt, 1, updateId);
    sqlite3_bind_int( stmt, 2, kidsId);
    sqlite3_bind_int( stmt, 3, contentId);
    
    sqlite3_step(stmt);
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return true;
}

bool CJLMSKidsContent::insertKidsContent(KidsContent info, int idxKids)
{
    if (this->selectCount(info.iKidsId, info.iContentId) !=  DB_ERROR) return true;
    
    sqlite3_stmt* stmt;
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "PRAGMA synchronous=OFF;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "BEGIN;", NULL, NULL, NULL) == SQLITE_OK);
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), INSERT_COLUMN, strlen(INSERT_COLUMN)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return false;
    
    sqlite3_bind_int( stmt, 1, info.iKidsId);
    sqlite3_bind_int( stmt, 2, info.iContentId);
    sqlite3_bind_text( stmt, 3, info.szStartDate.c_str(), info.szStartDate.size(), NULL );
    sqlite3_bind_text( stmt, 4, info.szEndDate.c_str(), info.szEndDate.size(), NULL );
    
    sqlite3_step(stmt);
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    this->updateKey(info.iKidsId, info.iContentId, info.szKey, idxKids);
    
    return true;
}

#pragma mark - private func

bool CJLMSKidsContent::updateKey(int kidsId, int contentId, std::string key, int idxKids)
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
        printf("done or no data in CJLMSKidsContent\n");
        sqlite3_reset( stmt );
        
        assert( sqlite3_finalize(stmt) == SQLITE_OK);
    } else {
        printf("db select fail. rc : %d, err : %s in CJLMSKidsContent\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
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
    
    sqlite3_step(stmt);
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return true;
}