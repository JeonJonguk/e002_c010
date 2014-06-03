//
//  CJLMSPKGKids.cpp
//  S001_Template
//
//  Created by Soonho Hong on 12. 10. 24..
//
//

#include "CJLMSPKGKids.h"
#include "CJLMSDefines.h"

// DEFINE QUERY
#define CREATE_TABLE        "CREATE TABLE IF NOT EXISTS tblPKGKids (oidPKGKids INTEGER PRIMARY KEY  NOT NULL ,idxKids INTEGER NOT NULL  DEFAULT (0) ,nLevel INTEGER NOT NULL  DEFAULT (1) ,nTotalLevel INTEGER NOT NULL  DEFAULT (0) ,nUpdateId INTEGER NOT NULL  DEFAULT (0), dtWriteDate DATETIME NOT NULL  DEFAULT (CURRENT_DATE), dtTargetDate DATETIME NOT NULL  DEFAULT (CURRENT_DATE), strPKGCode VARCHAR NOT NULL  DEFAULT '');"
#define INSERT_COLUMN       "INSERT INTO tblPKGKids (idxKids,nLevel,nTotalLevel,dtWriteDate,dtTargetDate,strPKGCode) VALUES (?,?,?,?,?,?)"
#define SELECT_KIDSID       "SELECT oidPKGKids FROM tblPKGKids WHERE idxKids = ? AND strPKGCode = ?"
#define SELECT_PKGKIDS      "SELECT * FROM tblPKGKids WHERE idxKids = ? AND nUpdateId = 0"
#define SELECT_KIDSINFO     "SELECT * FROM tblPKGKids WHERE idxKids = ? AND strPKGCode = ?"
#define SELECT_STAGE        "SELECT nLevel FROM tblPKGKids WHERE oidPKGKids = ?"
#define UPDATE_STAGE        "UPDATE tblPKGKids SET nLevel = ? WHERE  oidPKGKids = ?"
#define UPDATE_STARTDATE    "UPDATE tblPKGKids SET dtWriteDate = ? WHERE  oidPKGKids = ?"
#define UPDATE_UPDATEID     "UPDATE tblPKGKids SET nUpdateId = ? WHERE  oidPKGKids = ?"


#pragma mark - base func
CJLMSPKGKids::CJLMSPKGKids()
{
    
}

CJLMSPKGKids::CJLMSPKGKids(CJLMSDBManage *pLmsDBManage)
{
    m_lmsDBManage = pLmsDBManage;
}


CJLMSPKGKids::~CJLMSPKGKids()
{
    m_lmsDBManage = NULL;
}

CJLMSPKGKids* CJLMSPKGKids::create(CJLMSDBManage *pLmsDBManage)
{
    CJLMSPKGKids *ret = new CJLMSPKGKids(pLmsDBManage);
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

bool CJLMSPKGKids::init()
{
    char    *szErrMsg = NULL;
    int     rc = sqlite3_exec(m_lmsDBManage->getDB(), CREATE_TABLE, NULL, NULL, &szErrMsg);
    
    if(rc != SQLITE_OK)
    {
        printf("db error message (pkgkids) : %s\n", szErrMsg);
        sqlite3_close(m_lmsDBManage->getDB());
        
        return false;
    }
    
    return true;
}




#pragma mark - manage func
int CJLMSPKGKids::selectKidsId(std::string PKGCode, int idxKids)
{
	int id = 0;

	sqlite3_stmt* stmt;

	int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_KIDSID, strlen(SELECT_KIDSID)+1, &stmt, NULL );
	if( rst != SQLITE_OK ) return false;

	sqlite3_bind_int( stmt, 1, idxKids);
	sqlite3_bind_text( stmt, 2, PKGCode.c_str(), PKGCode.size(), NULL );

	int s;

	s = sqlite3_step(stmt);

	if (s == SQLITE_ROW) {
		id = sqlite3_column_int(stmt, 0);
	} else if (s == SQLITE_DONE) {
		printf("done or no data in CJLMSPKGKids\n");
		id = DB_ERROR;
	} else {
		printf("db select fail. rc : %d, err : %s in CJLMSPKGKids\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
		id = DB_ERROR;
	}

	sqlite3_reset( stmt );

	assert( sqlite3_finalize(stmt) == SQLITE_OK);

	return id;
}

KidsInfo CJLMSPKGKids::selectPKGKids(int idxKids, std::string packageCode)
{
	KidsInfo kids;

	sqlite3_stmt* stmt;

	int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_KIDSINFO, strlen(SELECT_KIDSINFO)+1, &stmt, NULL );
	if( rst != SQLITE_OK ) return kids;

	sqlite3_bind_int( stmt, 1, idxKids);
	sqlite3_bind_text( stmt, 2, packageCode.c_str(), packageCode.size(), NULL );

	int s;

	s = sqlite3_step(stmt);

	if (s == SQLITE_ROW) {
		kids.iPKGKidsId             = sqlite3_column_int(stmt, 0);
		kids.iIdxKids             	= sqlite3_column_int(stmt, 1);
		kids.iStage                 = sqlite3_column_int(stmt, 2);
		kids.iTotalStage            = sqlite3_column_int(stmt, 3);
		kids.szWriteDate.append((char*)sqlite3_column_text(stmt, 5));
		kids.szCompleteDate.append((char*)sqlite3_column_text(stmt, 6));
		kids.szPKGCode.append((char*)sqlite3_column_text(stmt, 7));
	} else if (s == SQLITE_DONE) {
		printf("done or no data in CJLMSPKGKids\n");
	} else {
		printf("db select fail. rc : %d, err : %s in CJLMSPKGKids\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
	}

	sqlite3_reset( stmt );

	assert( sqlite3_finalize(stmt) == SQLITE_OK);

	return kids;
}

std::vector<KidsInfo>* CJLMSPKGKids::selectUpdatePKGKids(int idxKids)
{
	std::vector<KidsInfo> *kids = new std::vector<KidsInfo>();

	sqlite3_stmt* stmt;

	int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_PKGKIDS, strlen(SELECT_PKGKIDS)+1, &stmt, NULL );
	if( rst != SQLITE_OK ) {
		KidsInfo data;
		data.iPKGKidsId = DB_ERROR;
		kids->push_back(data);
		return kids;
	}

	sqlite3_bind_int( stmt, 1, idxKids);

	while (1) {
		int s;

		s = sqlite3_step(stmt);

		if (s == SQLITE_ROW) {
			KidsInfo data;

			data.iPKGKidsId             = sqlite3_column_int(stmt, 0);
			data.iIdxKids               = sqlite3_column_int(stmt, 1);
			data.iStage                 = sqlite3_column_int(stmt, 2);
			data.iTotalStage            = sqlite3_column_int(stmt, 3);
			data.szWriteDate.append((char*)sqlite3_column_text(stmt, 5));
			data.szCompleteDate.append((char*)sqlite3_column_text(stmt, 6));
			data.szPKGCode.append((char*)sqlite3_column_text(stmt, 7));

			kids->push_back(data);
		} else if (s == SQLITE_DONE) {
			printf("done or no data in CJLMSPKGKids\n");
			break;
		} else {
			printf("db select fail. rc : %d, err : %s in CJLMSPKGKids\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
			break;
		}
	}

	sqlite3_reset( stmt );

	assert( sqlite3_finalize(stmt) == SQLITE_OK);

	return kids;
}

int CJLMSPKGKids::selectStage(int kidsId)
{
	int stage = 1;

	sqlite3_stmt* stmt;

	int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_STAGE, strlen(SELECT_STAGE)+1, &stmt, NULL );
	if( rst != SQLITE_OK ) return false;

	sqlite3_bind_int( stmt, 1, kidsId);

	int s;

	s = sqlite3_step(stmt);

	if (s == SQLITE_ROW) {
		stage = sqlite3_column_int(stmt, 0);
	} else if (s == SQLITE_DONE) {
		printf("done or no data in CJLMSPKGKids\n");
		stage = DB_ERROR;
	} else {
		printf("db select fail. rc : %d, err : %s in CJLMSPKGKids\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
		stage = DB_ERROR;
	}

	sqlite3_reset( stmt );

	assert( sqlite3_finalize(stmt) == SQLITE_OK);

	return stage;
}

#include "cocos2d.h"
bool CJLMSPKGKids::updateStage(int kidsId, int stage)
{
	sqlite3_stmt* stmt;

	assert( sqlite3_exec(m_lmsDBManage->getDB(), "PRAGMA synchronous=OFF;", NULL, NULL, NULL) == SQLITE_OK);
	assert( sqlite3_exec(m_lmsDBManage->getDB(), "BEGIN;", NULL, NULL, NULL) == SQLITE_OK);

	int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), UPDATE_STAGE, strlen(UPDATE_STAGE)+1, &stmt, NULL );
	if( rst != SQLITE_OK ) return false;

	sqlite3_bind_int( stmt, 1, stage);
	sqlite3_bind_int( stmt, 2, kidsId);

	sqlite3_step(stmt);

	sqlite3_reset( stmt );

	assert( sqlite3_exec(m_lmsDBManage->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
	assert( sqlite3_finalize(stmt) == SQLITE_OK);

	this->updateUpdateId(kidsId, 0);  // when update value, change update id (v1.0.3)

	return true;
}

bool CJLMSPKGKids::updateUpdateId(int kidsId, int updateId)
{
	sqlite3_stmt* stmt;

	assert( sqlite3_exec(m_lmsDBManage->getDB(), "PRAGMA synchronous=OFF;", NULL, NULL, NULL) == SQLITE_OK);
	assert( sqlite3_exec(m_lmsDBManage->getDB(), "BEGIN;", NULL, NULL, NULL) == SQLITE_OK);

	int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), UPDATE_UPDATEID, strlen(UPDATE_UPDATEID)+1, &stmt, NULL );
	if( rst != SQLITE_OK ) return false;

	sqlite3_bind_int( stmt, 1, updateId);
	sqlite3_bind_int( stmt, 2, kidsId);

	sqlite3_step(stmt);

	sqlite3_reset( stmt );

	assert( sqlite3_exec(m_lmsDBManage->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
	assert( sqlite3_finalize(stmt) == SQLITE_OK);

	return true;
}

bool CJLMSPKGKids::updateStartDate(int kidsId, std::string startDate)
{
	sqlite3_stmt* stmt;

	assert( sqlite3_exec(m_lmsDBManage->getDB(), "PRAGMA synchronous=OFF;", NULL, NULL, NULL) == SQLITE_OK);
	assert( sqlite3_exec(m_lmsDBManage->getDB(), "BEGIN;", NULL, NULL, NULL) == SQLITE_OK);

	int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), UPDATE_STARTDATE, strlen(UPDATE_STARTDATE)+1, &stmt, NULL );
	if( rst != SQLITE_OK ) return false;

	sqlite3_bind_text( stmt, 1, startDate.c_str(), startDate.size(), NULL );
	sqlite3_bind_int( stmt, 2, kidsId);

	sqlite3_step(stmt);

	sqlite3_reset( stmt );

	assert( sqlite3_exec(m_lmsDBManage->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
	assert( sqlite3_finalize(stmt) == SQLITE_OK);

	return true;
}

bool CJLMSPKGKids::insertKids(KidsInfo info, int idxKids)
{
	if (this->selectKidsId(info.szPKGCode, idxKids) !=  DB_ERROR) return false;

	sqlite3_stmt* stmt;

	assert( sqlite3_exec(m_lmsDBManage->getDB(), "PRAGMA synchronous=OFF;", NULL, NULL, NULL) == SQLITE_OK);
	assert( sqlite3_exec(m_lmsDBManage->getDB(), "BEGIN;", NULL, NULL, NULL) == SQLITE_OK);

	int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), INSERT_COLUMN, strlen(INSERT_COLUMN)+1, &stmt, NULL );
	if( rst != SQLITE_OK ) return false;

	sqlite3_bind_int( stmt, 1, idxKids);
	sqlite3_bind_int( stmt, 2, 1);
	sqlite3_bind_int( stmt, 3, info.iTotalStage);
	sqlite3_bind_text( stmt, 4, info.szWriteDate.c_str(), info.szWriteDate.size(), NULL );
	sqlite3_bind_text( stmt, 5, info.szCompleteDate.c_str(), info.szCompleteDate.size(), NULL );
	sqlite3_bind_text( stmt, 6, info.szPKGCode.c_str(), info.szPKGCode.size(), NULL );

	sqlite3_step(stmt);

	sqlite3_reset( stmt );

	assert( sqlite3_exec(m_lmsDBManage->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
	assert( sqlite3_finalize(stmt) == SQLITE_OK);

	return true;
}
