//
//  CJLMSGrade.cpp
//  S001_Template
//
//  Created by Soonho Hong on 12. 10. 24..
//
//

#include "CJLMSGrade.h"
#include "CJLMSDefines.h"

// DEFINE QUERY
#define CREATE_TABLE            "CREATE TABLE IF NOT EXISTS tblGrade (oidGrade INTEGER PRIMARY KEY  NOT NULL  DEFAULT (0) ,oidPKGKids INTEGER NOT NULL  DEFAULT (0) ,oidContentId INTEGER NOT NULL  DEFAULT (0) ,nGrade INTEGER NOT NULL  DEFAULT (0) ,nUpdateId INTEGER NOT NULL  DEFAULT (0) ,nQuestionId INTEGER NOT NULL  DEFAULT (0), dtWriteDate DATETIME NOT NULL  DEFAULT (CURRENT_DATE) ,strKey VARCHAR, strEtc1 VARCHAR);"

#define INSERT_COLUMN           "INSERT INTO tblGrade (oidPKGKids,oidContentId,nGrade,nQuestionId,dtWriteDate, strKey, strEtc1) VALUES (?,?,?,?,?,?,?)"
//#define SELECT_GRADE            "SELECT * FROM tblGrade WHERE oidPKGKids = ? AND oidContentId = ? AND nQuestionId = ? ORDER BY oidGrade DESC"
#define SELECT_GRADE            "SELECT * FROM tblGrade WHERE oidPKGKids = ? AND oidContentId = ? AND nQuestionId = ? ORDER BY dtWriteDate DESC"
#define SELECT_UPDATEGRADE      "SELECT * FROM tblGrade WHERE oidPKGKids = ? AND oidContentId = ? AND nUpdateId = 0 ORDER BY oidGrade DESC"
#define SELECT_KEY              "SELECT strKey FROM tblGrade WHERE oidGrade = ?"
#define UPDATE_UPDATEID         "UPDATE tblGrade SET nUpdateId = ? WHERE  oidGrade = ?"
#define UPDATE_KEY              "UPDATE tblGrade SET strKey = ? WHERE  oidGrade = ?"



#pragma mark - base func
CJLMSGrade::CJLMSGrade()
{

}

CJLMSGrade::CJLMSGrade(CJLMSDBManage *pLmsDBManage)
{
    m_lmsDBManage = pLmsDBManage;
}

CJLMSGrade::~CJLMSGrade()
{
    m_lmsDBManage = NULL;
}

CJLMSGrade* CJLMSGrade::create(CJLMSDBManage *pLmsDBManage)
{
    CJLMSGrade *ret = new CJLMSGrade(pLmsDBManage);
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

bool CJLMSGrade::init()
{
    char    *szErrMsg = NULL;
    int     rc = sqlite3_exec(m_lmsDBManage->getDB(), CREATE_TABLE, NULL, NULL, &szErrMsg);
    
    if(rc != SQLITE_OK)
    {
        printf("db error message (grade) : %s\n", szErrMsg);
        sqlite3_close(m_lmsDBManage->getDB());
        
        return false;
    }
    
    return true;
}




#pragma mark - manage func
std::vector<Grade>* CJLMSGrade::selectGrade(int kidsId, int contentId, int questionId)
{
    std::vector<Grade> *grades = new std::vector<Grade>();
    
    sqlite3_stmt* stmt;
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_GRADE, strlen(SELECT_GRADE)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return grades;
    
    sqlite3_bind_int( stmt, 1, kidsId);
    sqlite3_bind_int( stmt, 2, contentId);
    sqlite3_bind_int( stmt, 3, questionId);
    
    while (1) {
        int s;
        
        s = sqlite3_step(stmt);
        
        if (s == SQLITE_ROW) {
            Grade data;
            
            data.iGradeId               = sqlite3_column_int(stmt, 0);
            data.iKidsId                = sqlite3_column_int(stmt, 1);
            data.iContentId             = sqlite3_column_int(stmt, 2);
            data.nGrade                 = sqlite3_column_int(stmt, 3);
            data.iUpdateId              = sqlite3_column_int(stmt, 4);
            data.szWriteDate.append((char*)sqlite3_column_text(stmt, 5));
            data.szKey.append((char*)sqlite3_column_text(stmt, 6));
            data.nQNum    		        = sqlite3_column_int(stmt, 7);
            data.szExtra1.append((char*)sqlite3_column_text(stmt, 8));
            
            grades->push_back(data);
        } else if (s == SQLITE_DONE) {
            printf("done or no data in CJLMSGrade\n");
            sqlite3_reset( stmt );

            assert( sqlite3_finalize(stmt) == SQLITE_OK);
            break;
        } else {
            printf("db select fail. rc : %d, err : %s in CJLMSGrade\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
            break;
        }
    }
    
    return grades;
}

std::vector<Grade>* CJLMSGrade::selectUpdateGrade(int kidsId, int contentId)
{
    std::vector<Grade> *grades = new std::vector<Grade>();
    
    sqlite3_stmt* stmt;
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_UPDATEGRADE, strlen(SELECT_UPDATEGRADE)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return grades;
    
    sqlite3_bind_int( stmt, 1, kidsId);
    sqlite3_bind_int( stmt, 2, contentId);
    
    while (1) {
        int s;
        
        s = sqlite3_step(stmt);
        
        if (s == SQLITE_ROW) {
            Grade data;
            
            data.iGradeId               = sqlite3_column_int(stmt, 0);
            data.iKidsId                = sqlite3_column_int(stmt, 1);
            data.iContentId             = sqlite3_column_int(stmt, 2);
            data.nGrade                 = sqlite3_column_int(stmt, 3);
            data.iUpdateId              = sqlite3_column_int(stmt, 4);
            data.szWriteDate.append((char*)sqlite3_column_text(stmt, 5));
            data.szKey.append((char*)sqlite3_column_text(stmt, 6));
            data.nQNum              	= sqlite3_column_int(stmt, 7);
            data.szExtra1.append((char*)sqlite3_column_text(stmt, 8));
            
            grades->push_back(data);
        } else if (s == SQLITE_DONE) {
            printf("done or no data in CJLMSGrade\n");
            sqlite3_reset( stmt );
            
            assert( sqlite3_finalize(stmt) == SQLITE_OK);
            break;
        } else {
            printf("db select fail. rc : %d, err : %s in CJLMSGrade\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
            break;
        }
    }
    
    return grades;
}

std::string CJLMSGrade::selectKey(int gradeId)
{
    std::string key;
    
    sqlite3_stmt* stmt;
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_KEY, strlen(SELECT_KEY)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return false;
    
    sqlite3_bind_int( stmt, 1, gradeId);
    
    int s;
    
    s = sqlite3_step(stmt);
    
    if (s == SQLITE_ROW) {
        key.append((char*)sqlite3_column_text(stmt, 0));
    } else if (s == SQLITE_DONE) {
        printf("done or no data in CJLMSGrade\n");
        std::stringstream intValue;
        intValue << DB_ERROR;
        key.append("no data ");
        key.append(intValue.str());
    } else {
        printf("db select fail. rc : %d, err : %s in CJLMSGrade\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
        std::stringstream intValue;
        intValue << DB_ERROR;
        key.append(("db select fail "));
        key.append(intValue.str());
    }
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return key;
}

bool CJLMSGrade::updateUpdateId(int gradeId, int updateId)
{
    sqlite3_stmt* stmt;
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "PRAGMA synchronous=OFF;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "BEGIN;", NULL, NULL, NULL) == SQLITE_OK);
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), UPDATE_UPDATEID, strlen(UPDATE_UPDATEID)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return false;
    
    sqlite3_bind_int( stmt, 1, updateId);
    sqlite3_bind_int( stmt, 2, gradeId);
    
    sqlite3_step(stmt);
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return true;
}

bool CJLMSGrade::insertGrade(Grade data, int idxKids)
{
    sqlite3_stmt* stmt;
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "PRAGMA synchronous=OFF;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "BEGIN;", NULL, NULL, NULL) == SQLITE_OK);
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), INSERT_COLUMN, strlen(INSERT_COLUMN)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return false;
    
    sqlite3_bind_int( stmt, 1, data.iKidsId);
    sqlite3_bind_int( stmt, 2, data.iContentId);
    sqlite3_bind_int( stmt, 3, data.nGrade);
    sqlite3_bind_int( stmt, 4, data.nQNum);
    sqlite3_bind_text( stmt, 5, data.szWriteDate.c_str(), data.szWriteDate.size(), NULL );
    sqlite3_bind_text( stmt, 6, data.szKey.c_str(), data.szKey.size(), NULL );
    sqlite3_bind_text( stmt, 7, data.szExtra1.c_str(), data.szExtra1.size(), NULL);
    
    sqlite3_step(stmt);
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    this->updateKey(data.szKey, idxKids);
    
    return true;
}

#pragma mark - private func

bool CJLMSGrade::updateKey(std::string key, int idxKids)
{
    sqlite3_stmt* stmt;
    
    int row = 0;
    
    char* sql = (char*)"SELECT last_insert_rowid()";
    
    sqlite3_prepare(m_lmsDBManage->getDB(), sql, strlen(sql)+1, &stmt, NULL);
    
    int s;
    
    s = sqlite3_step(stmt);
    
    if (s == SQLITE_ROW) {
        row = sqlite3_column_int(stmt, 0);;
        sqlite3_reset( stmt );
        
        assert( sqlite3_finalize(stmt) == SQLITE_OK);
    } else if (s == SQLITE_DONE) {
        printf("done or no data in CJLMSGrade\n");
        sqlite3_reset( stmt );
        
        assert( sqlite3_finalize(stmt) == SQLITE_OK);
    } else {
        printf("db select fail. rc : %d, err : %s in CJLMSGrade\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
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
    sqlite3_bind_int( stmt, 2, row);
    
    sqlite3_step(stmt);
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return true;
}
