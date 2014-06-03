//
//  CJLMSFile.cpp
//  S001_Template
//
//  Created by Soonho Hong on 12. 10. 24..
//
//

#include "CJLMSFile.h"
#include "CJLMSDefines.h"

// DEFINE QUERY
#define CREATE_TABLE            "CREATE TABLE IF NOT EXISTS tblFile (oidFile INTEGER PRIMARY KEY  NOT NULL  DEFAULT (0) ,idxKids INTEGER NOT NULL  DEFAULT (0) ,oidContentId INTEGER NOT NULL  DEFAULT (0) ,nMenuNum INTEGER NOT NULL  DEFAULT (0) ,nKind INTEGER NOT NULL  DEFAULT (0) ,nGubun INTEGER NOT NULL  DEFAULT (1) ,dtWriteDate DATETIME NOT NULL  DEFAULT (CURRENT_DATE) ,strPath VARCHAR, strEtc1 TEXT, strEtc2 TEXT);"
#define INSERT_COLUMN           "INSERT INTO tblFile (idxKids,oidContentId,nMenuNum,nGubun,dtWriteDate,strPath,strEtc1,strEtc2) VALUES (?,?,?,?,?,?,?,?)"
#define DELETE_COLUMN           "DELETE FROM tblFile WHERE oidFile = ?"
#define SELECT_FILE 			"SELECT * FROM (SELECT * FROM tblFile ORDER BY dtWriteDate DESC) WHERE nKind = 0 AND nGubun = 1 AND idxKids = ? LIMIT 1"
#define SELECT_FILEWITHMENUID   "SELECT nMenuNum, strPath, strEtc1, strEtc2 FROM (SELECT * FROM tblFile ORDER BY dtWriteDate DESC) WHERE oidContentId = ? AND nGubun = ? AND idxKids = ? AND nMenuNum = ?"

#define SELECT_CONTENTLIST      "SELECT * FROM (SELECT * FROM tblFile ORDER BY dtWriteDate DESC) WHERE oidContentId = ? AND nGubun = ? AND idxKids = ? LIMIT 5"
#define SELECT_REMOVELIST	    "SELECT oidFile, strPath FROM (SELECT * FROM tblFile ORDER BY dtWriteDate DESC) WHERE oidContentId = ? AND nGubun = ? AND idxKids = ?"
#define SELECT_REMOVELIST2	    "SELECT oidFile, strPath, strEtc1 FROM (SELECT * FROM tblFile ORDER BY dtWriteDate DESC) WHERE oidContentId = ? AND nGubun = ? AND idxKids = ? AND nMenuNum = ?"
#define SELECT_PACKAGELIST      "SELECT * FROM tblFile WHERE idxKids = ? AND nGubun = ? GROUP BY oidContentId ORDER BY dtWriteDate ASC"
#define SELECT_PATH             "SELECT strPath FROM (SELECT * FROM tblFile ORDER BY dtWriteDate DESC) WHERE oidContentId = ? AND nMenuNum = ? AND nGubun = ? AND idxKids = ? LIMIT 1"
#define UPDATE_KIND             "UPDATE tblFile SET nKind = ? WHERE oidFile = ?"



#pragma mark - manage func
CJLMSFile::CJLMSFile()
{
    
}

CJLMSFile::CJLMSFile(CJLMSDBManage *pLmsDBManage)
{
    m_lmsDBManage = pLmsDBManage;
}

CJLMSFile::~CJLMSFile()
{
    m_lmsDBManage = NULL;
}

CJLMSFile* CJLMSFile::create(CJLMSDBManage *pLmsDBManage)
{
    CJLMSFile *ret = new CJLMSFile(pLmsDBManage);
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

bool CJLMSFile::init()
{
    char    *szErrMsg = NULL;
    int     rc = sqlite3_exec(m_lmsDBManage->getDB(), CREATE_TABLE, NULL, NULL, &szErrMsg);
    
    if(rc != SQLITE_OK)
    {
        printf("db error message (file) : %s\n", szErrMsg);
        sqlite3_close(m_lmsDBManage->getDB());
        
        return false;
    }
    
    return true;
}




#pragma mark - base func
std::vector<ResFile>* CJLMSFile::selectContentFile(int contentId, int gubun, int idxKids)
{
    std::vector<ResFile> *files = new std::vector<ResFile>();
    
    sqlite3_stmt* stmt;
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_CONTENTLIST, strlen(SELECT_CONTENTLIST)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return files;
    
    sqlite3_bind_int( stmt, 1, contentId);
    sqlite3_bind_int( stmt, 2, gubun);
    sqlite3_bind_int( stmt, 3, idxKids);
    
    while (1) {
        int s;
        
        s = sqlite3_step(stmt);
        
        if (s == SQLITE_ROW) {
            ResFile data;

            data.iFileId                = sqlite3_column_int(stmt, 0);
            data.idxKids                = sqlite3_column_int(stmt, 1);
            data.iContentId             = sqlite3_column_int(stmt, 2);
            data.iMenuNum               = sqlite3_column_int(stmt, 3);
            data.iKind                  = sqlite3_column_int(stmt, 4);
            data.iGubun                 = sqlite3_column_int(stmt, 5);
            data.szWriteDate.append((char*)sqlite3_column_text(stmt, 6));
            data.szPath.append((char*)sqlite3_column_text(stmt, 7));
            
            files->push_back(data);
            
        } else if (s == SQLITE_DONE) {
            printf("done or end data in CJLMSFile\n");
            break;
        } else {
            printf("db select fail. rc : %d, err : %s in CJLMSFile\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
            break;
        }
    }
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return files;
}

ResFile CJLMSFile::selectFileWithMenuID(int contentId, int gubun, int idxKids, int menuId) {
    ResFile file;
    
    sqlite3_stmt* stmt;
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_FILEWITHMENUID, strlen(SELECT_FILEWITHMENUID)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return file;
    
    sqlite3_bind_int( stmt, 1, contentId);
    sqlite3_bind_int( stmt, 2, gubun);
    sqlite3_bind_int( stmt, 3, idxKids);
    sqlite3_bind_int( stmt, 4, menuId);
    
    int s;
    s = sqlite3_step(stmt);
    if (s == SQLITE_ROW) {
        file.iMenuNum = sqlite3_column_int(stmt, 0);
        file.szPath.append((char*)sqlite3_column_text(stmt, 1));
        file.szExtend1.append((char*)sqlite3_column_text(stmt, 2));
        file.szExtend2.append((char*)sqlite3_column_text(stmt, 3));
        
    } else if (s == SQLITE_DONE) {
        file.iMenuNum = -1;
        file.szPath = "";
        file.szExtend1 = "";
        file.szExtend2 = "";
        printf("done or end data in CJLMSFile\n");
    } else {
        printf("db select fail. rc : %d, err : %s in CJLMSFile\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
    }
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return file;

}

std::vector<ResFile>* CJLMSFile::selectRemoveFile(int contentId, int gubun, int idxKids)
{
    std::vector<ResFile> *files = new std::vector<ResFile>();

    sqlite3_stmt* stmt;

    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_REMOVELIST, strlen(SELECT_REMOVELIST)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return files;

    sqlite3_bind_int( stmt, 1, contentId);
    sqlite3_bind_int( stmt, 2, gubun);
    sqlite3_bind_int( stmt, 3, idxKids);

    while (1) {
        int s;

        s = sqlite3_step(stmt);

        if (s == SQLITE_ROW) {
            ResFile data;

            data.iFileId = sqlite3_column_int(stmt, 0);
            data.szPath.append((char*)sqlite3_column_text(stmt, 1));

            files->push_back(data);

        } else if (s == SQLITE_DONE) {
            printf("done or end data in CJLMSFile\n");
            break;
        } else {
            printf("db select fail. rc : %d, err : %s in CJLMSFile\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
            break;
        }
    }

    sqlite3_reset( stmt );

    assert( sqlite3_finalize(stmt) == SQLITE_OK);

    return files;
}


std::vector<ResFile>* CJLMSFile::selectRemoveFile(int contentId, int gubun, int idxKids, int menuId)
{
    std::vector<ResFile> *files = new std::vector<ResFile>();
    
    sqlite3_stmt* stmt;
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_REMOVELIST2, strlen(SELECT_REMOVELIST2)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return files;
    
    sqlite3_bind_int( stmt, 1, contentId);
    sqlite3_bind_int( stmt, 2, gubun);
    sqlite3_bind_int( stmt, 3, idxKids);
    sqlite3_bind_int( stmt, 4, menuId);
    
    while (1) {
        int s;
        
        s = sqlite3_step(stmt);
        
        if (s == SQLITE_ROW) {
            ResFile data;
            
            data.iFileId = sqlite3_column_int(stmt, 0);
            data.szPath.append((char*)sqlite3_column_text(stmt, 1));
            data.szExtend1.append((char*)sqlite3_column_text(stmt, 2));
            
            files->push_back(data);
            
        } else if (s == SQLITE_DONE) {
            printf("done or end data in CJLMSFile\n");
            break;
        } else {
            printf("db select fail. rc : %d, err : %s in CJLMSFile\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
            break;
        }
    }
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return files;
}



std::vector<ResFile>* CJLMSFile::selectPackageFile(int gubun, int idxKids)
{
    std::vector<ResFile> *files = new std::vector<ResFile>();
    
    sqlite3_stmt* stmt;
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_PACKAGELIST, strlen(SELECT_PACKAGELIST)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return files;
    
    sqlite3_bind_int(stmt, 1, idxKids);
    sqlite3_bind_int( stmt, 2, gubun);
    
    while (1) {
        int s;
        
        s = sqlite3_step(stmt);
        
        if (s == SQLITE_ROW) {
            ResFile data;
            
            data.iFileId                = sqlite3_column_int(stmt, 0);
            data.idxKids                = sqlite3_column_int(stmt, 1);
            data.iContentId             = sqlite3_column_int(stmt, 2);
            data.iMenuNum               = sqlite3_column_int(stmt, 3);
            data.iKind                  = sqlite3_column_int(stmt, 4);
            data.iGubun                 = sqlite3_column_int(stmt, 5);
            data.szWriteDate.append((char*)sqlite3_column_text(stmt, 6));
            data.szPath.append((char*)sqlite3_column_text(stmt, 7));
            
            files->push_back(data);
        } else if (s == SQLITE_DONE) {
            printf("done or end data in CJLMSFile\n");
            break;
        } else {
            printf("db select fail. rc : %d, err : %s in CJLMSFile\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
            break;
        }
    }
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return files;
}

std::string CJLMSFile::selectPath(int contentId, int menuNum, int gubun, int idxKids)
{
    std::string path;
    
    sqlite3_stmt* stmt;
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_PATH, strlen(SELECT_PATH)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return path;
    
    sqlite3_bind_int( stmt, 1, contentId);
    sqlite3_bind_int( stmt, 2, menuNum);
    sqlite3_bind_int( stmt, 3, gubun);
    sqlite3_bind_int( stmt, 4, idxKids);
    
    int s;
    
    s = sqlite3_step(stmt);
    
    if (s == SQLITE_ROW) {
        path.append((char*)sqlite3_column_text(stmt, 0));
    } else if (s == SQLITE_DONE) {
        printf("done or end data in CJLMSFile\n");
    } else {
        printf("db select fail. rc : %d, err : %s in CJLMSFile\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
    }
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return path;
}

std::string CJLMSFile::selectCurrentPath(int idxKids)
{
    std::string path;
    
    sqlite3_stmt* stmt;
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_FILE, strlen(SELECT_FILE)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return path;
    
    sqlite3_bind_int( stmt, 1, idxKids);
    
    int s;
    
    s = sqlite3_step(stmt);
    
    if (s == SQLITE_ROW) {
        path.append((char*)sqlite3_column_text(stmt, 0));
    } else if (s == SQLITE_DONE) {
        printf("done or end data in CJLMSFile\n");
    } else {
        printf("db select fail. rc : %d, err : %s in CJLMSFile\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
    }
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return path;
}

bool CJLMSFile::updateKind(int fileId, int kind)
{
    sqlite3_stmt* stmt;
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "PRAGMA synchronous=OFF;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "BEGIN;", NULL, NULL, NULL) == SQLITE_OK);
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), UPDATE_KIND, strlen(UPDATE_KIND)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return false;
    
    
    sqlite3_bind_int( stmt, 1, kind);
    sqlite3_bind_int( stmt, 2, fileId);
    
    sqlite3_step(stmt);
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return true;
}

bool CJLMSFile::insertFile(ResFile data)
{
    sqlite3_stmt* stmt;
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "PRAGMA synchronous=OFF;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "BEGIN;", NULL, NULL, NULL) == SQLITE_OK);
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), INSERT_COLUMN, strlen(INSERT_COLUMN)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return false;
    
    sqlite3_bind_int( stmt, 1, data.idxKids);
    sqlite3_bind_int( stmt, 2, data.iContentId);
    sqlite3_bind_int( stmt, 3, data.iMenuNum);
    sqlite3_bind_int( stmt, 4, data.iGubun);
    sqlite3_bind_text( stmt, 5, data.szWriteDate.c_str(), data.szWriteDate.size(), NULL );
    sqlite3_bind_text( stmt, 6, data.szPath.c_str(), data.szPath.size(), NULL );
    sqlite3_bind_text( stmt, 7, data.szExtend1.c_str(), data.szExtend1.size(), NULL );
    sqlite3_bind_text( stmt, 8, data.szExtend2.c_str(), data.szExtend2.size(), NULL );
    
    
    sqlite3_step(stmt);
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return true;
}

bool CJLMSFile::deleteFile(ResFile data)
{
    sqlite3_stmt* stmt;

    assert( sqlite3_exec(m_lmsDBManage->getDB(), "PRAGMA synchronous=OFF;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_exec(m_lmsDBManage->getDB(), "BEGIN;", NULL, NULL, NULL) == SQLITE_OK);

    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), DELETE_COLUMN, strlen(DELETE_COLUMN)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return false;

    sqlite3_bind_int( stmt, 1, data.iFileId);

    sqlite3_step(stmt);

    sqlite3_reset( stmt );

    assert( sqlite3_exec(m_lmsDBManage->getDB(), "COMMIT;", NULL, NULL, NULL) == SQLITE_OK);
    assert( sqlite3_finalize(stmt) == SQLITE_OK);

    return true;
}
