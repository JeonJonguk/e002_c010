//
//  CJLMSContent.cpp
//  S001_Template
//
//  Created by Soonho Hong on 12. 10. 24..
//
//

#include "CJLMSContent.h"
#include "CJLMSDefines.h"

// DEFINE QUERY
//#define CREATE_TABLE        "CREATE TABLE IF NOT EXISTS tblContent (oidContentId INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , nLevel INTEGER NOT NULL  DEFAULT 0, nMenuCount INTEGER NOT NULL  DEFAULT 0, strPKGCode VARCHAR NOT NULL  DEFAULT '', strContentCode VARCHAR NOT NULL  DEFAULT '', strTitle VARCHAR NOT NULL  DEFAULT '', strDescription VARCHAR NOT NULL  DEFAULT '', strImagePath VARCHAR NOT NULL  DEFAULT '');"
//#define DROP_TABLE       	"DROP TABLE tblContent"
#define SELECT_CONTENT1     "SELECT * FROM tblContent WHERE oidContentId = ?"
#define SELECT_CONTENT2     "SELECT * FROM tblContent WHERE strPKGCode = ? AND nLevel = ?"
#define SELECT_CONTENT3     "SELECT * FROM tblContent WHERE strPKGCode = ? AND strContentCode = ?"
#define SELECT_CONTENTLIST  "SELECT * FROM (SELECT * FROM tblContent ORDER BY nLevel ASC) WHERE strPKGCode = ?"
#define SELECT_CONTENTID    "SELECT oidContentId FROM tblContent WHERE strPKGCode = ? AND strContentCode = ?"
#define SELECT_CONTENT    	"SELECT * FROM tblContent"



#pragma mark - base func
CJLMSContent::CJLMSContent()
{
    
}

CJLMSContent::CJLMSContent(CJLMSDBManage *pLmsDBManage)
{
    m_lmsDBManage = pLmsDBManage;
}

CJLMSContent::~CJLMSContent()
{
    
}

CJLMSContent* CJLMSContent::create(CJLMSDBManage *pLmsDBManage)
{
    CJLMSContent *ret = new CJLMSContent(pLmsDBManage);
    if(NULL != ret)
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

int CJLMSContent::getContentCount()
{
	sqlite3_stmt* stmt;

	int cnt = 0;

	int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_CONTENT, strlen(SELECT_CONTENT)+1, &stmt, NULL );
	if( rst != SQLITE_OK ) return cnt;

	while (1) {
		int s;

		s = sqlite3_step(stmt);

		if (s == SQLITE_ROW) {
			cnt++;
		} else if (s == SQLITE_DONE) {
			printf("done or end data in CJLMSContent\n");
			break;
		} else {
			printf("db select fail. rc : %d, err : %s in CJLMSContent\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
			break;
		}
	}

	sqlite3_reset( stmt );

	assert( sqlite3_finalize(stmt) == SQLITE_OK);

	return cnt;
}




#pragma mark - manage func
Content CJLMSContent::selectContent(int contentId)
{
    Content data;
    
    data.bNull = true;
    
    sqlite3_stmt* stmt;
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_CONTENT1, strlen(SELECT_CONTENT1)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return data;
    
    sqlite3_bind_int( stmt, 1, contentId);
    
    int s;
    
    s = sqlite3_step(stmt);
    
    if (s == SQLITE_ROW) {
        data.bNull              = false;
        data.iContentId         = sqlite3_column_int(stmt, 0);
        data.iStage             = sqlite3_column_int(stmt, 1);
        data.nMenuCount         = sqlite3_column_int(stmt, 2);
        data.szPKGCode.append((char*)sqlite3_column_text(stmt, 3));
        data.szContentCode.append((char*)sqlite3_column_text(stmt, 4));
        data.szTitle.append((char*)sqlite3_column_text(stmt, 5));
        data.szDescription.append((char*)sqlite3_column_text(stmt, 6));
        data.szGalleryTitle.append((char*)sqlite3_column_text(stmt, 7));
        data.szGalleryDesc.append((char*)sqlite3_column_text(stmt, 8));
    } else if (s == SQLITE_DONE) {
        printf("done or no data in CJLMSContent\n");
    } else {
        printf("db select fail. rc : %d, err : %s in CJLMSContent\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
    }
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return data;
}

Content CJLMSContent::selectContent(std::string PKGCode, int iStage)
{
    Content data;
    
    data.bNull = true;
    
    sqlite3_stmt* stmt;
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_CONTENT2, strlen(SELECT_CONTENT2)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return data;
    
    sqlite3_bind_text( stmt, 1, PKGCode.c_str(), PKGCode.size(), NULL );
    sqlite3_bind_int( stmt, 2, iStage);
    
    int s;
    
    s = sqlite3_step(stmt);
    
    if (s == SQLITE_ROW) {
        data.bNull              = false;
        data.iContentId         = sqlite3_column_int(stmt, 0);
        data.iStage             = sqlite3_column_int(stmt, 1);
        data.nMenuCount         = sqlite3_column_int(stmt, 2);
        data.szPKGCode.append((char*)sqlite3_column_text(stmt, 3));
        data.szContentCode.append((char*)sqlite3_column_text(stmt, 4));
        data.szTitle.append((char*)sqlite3_column_text(stmt, 5));
        data.szDescription.append((char*)sqlite3_column_text(stmt, 6));
        data.szGalleryTitle.append((char*)sqlite3_column_text(stmt, 7));
        data.szGalleryDesc.append((char*)sqlite3_column_text(stmt, 8));
    } else if (s == SQLITE_DONE) {
        printf("done or no data in CJLMSContent\n");
    } else {
        printf("db select fail. rc : %d, err : %s in CJLMSContent\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
    }
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return data;
}

Content CJLMSContent::selectContent(std::string PKGCode, std::string contentCode)
{
    Content data;
    sqlite3_stmt* stmt;
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_CONTENT3, strlen(SELECT_CONTENT3)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return data;
    
    sqlite3_bind_text( stmt, 1, PKGCode.c_str(), PKGCode.size(), NULL );
    sqlite3_bind_text( stmt, 2, contentCode.c_str(), contentCode.size(), NULL );
    
    int s;
    
    s = sqlite3_step(stmt);
    if (s == SQLITE_ROW) {
        data.bNull              = false;
        data.iContentId         = sqlite3_column_int(stmt, 0);
        data.iStage             = sqlite3_column_int(stmt, 1);
        data.nMenuCount         = sqlite3_column_int(stmt, 2);
        data.szPKGCode.append((char*)sqlite3_column_text(stmt, 3));
        data.szContentCode.append((char*)sqlite3_column_text(stmt, 4));
        data.szTitle.append((char*)sqlite3_column_text(stmt, 5));
        data.szDescription.append((char*)sqlite3_column_text(stmt, 6));
        data.szGalleryTitle.append((char*)sqlite3_column_text(stmt, 7));
        data.szGalleryDesc.append((char*)sqlite3_column_text(stmt, 8));
    } else if (s == SQLITE_DONE) {
        printf("done or no data in CJLMSContent\n");
    } else {
        printf("db select fail. rc : %d, err : %s in CJLMSContent\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
    }
    
    sqlite3_reset( stmt );
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return data;
}

int CJLMSContent::selectContentId(std::string PKGCode, std::string contentCode)
{
    int id = 0;
    
    sqlite3_stmt* stmt;
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_CONTENTID, strlen(SELECT_CONTENTID)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return false;
    
    sqlite3_bind_text( stmt, 1, PKGCode.c_str(), PKGCode.size(), NULL );
    sqlite3_bind_text( stmt, 2, contentCode.c_str(), contentCode.size(), NULL );
    
    int s;
    
    s = sqlite3_step(stmt);
    
    if (s == SQLITE_ROW) {
        id = sqlite3_column_int(stmt, 0);
    } else if (s == SQLITE_DONE) {
        printf("done or no data in CJLMSContent\n");
        id = DB_ERROR;
    } else {
        printf("db select fail. rc : %d, err : %s in CJLMSContent\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
        id = DB_ERROR;
    }
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return id;
}
