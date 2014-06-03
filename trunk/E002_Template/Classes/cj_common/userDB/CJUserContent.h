//
//  CJUserContent.h
//  S001_Template
//
//  Created by Soonho Hong on 12. 10. 24..
//
//

#ifndef CJUserContent_h
#define CJUserContent_h

#pragma once
#include "sqlite3.h"
#include <sstream>
#include <vector>
#include <assert.h>
// DEFINE QUERY
#define CREATE_TABLE        "CREATE TABLE IF NOT EXISTS userdatatable (oidContentId INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL ,  strKeyValue VARCHAR NOT NULL  DEFAULT '', strSaveValue VARCHAR NOT NULL  DEFAULT '');"
#define DROP_TABLE       	"DROP TABLE userdatatable"
#define SELECT_CONTENT1     "SELECT * FROM userdatatable WHERE strKeyValue = ?"
#define INSERT_COLUMN       "INSERT INTO userdatatable (strKeyValue,strSaveValue) VALUES (?,?)"
#define UPDATE_COLUMN       "UPDATE userdatatable SET strSaveValue = ? WHERE strKeyValue = ?"

/**
 * @author CJEducations
 * @brief manage tblContent class (add selectContentList func)
 * @version v1.0.1
 * @date 2012. 11. 29
 * @since v1.0.0
 */
typedef struct UserInforTable InforTable;

struct UserInforTable
{
    int iAutoKey;
    std::string strKeyValue;
    std::string strSaveValue;
};
class CJUserContent
{

public:
    /**
     * @author CJEducations
     * @brief Constructor
     * @version v1.0.0
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    CJUserContent();
    
    /**
     * @author CJEducations
     * @brief Destructor
     * @version v1.0.0
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    ~CJUserContent();
    
    /**
     * @author CJEducations
     * @brief singleton interface constructor func
     * @version v1.0.0
     * @return construct class (CJUserContent)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    static CJUserContent* sharedInstance();
    
    /**
     * @author CJEducations
     * @brief singleton interface realease func
     * @version v1.0.0
     * @date 2012. 10. 24
     * @since v1.0.0
     */
    static void releaseInstance();


    
    /**
     * @author CJEducations
     * @brief select content id from tblContent
     * @version v1.0.0
     * @param PKGCode : package code name (std::string)
     * @param contentCode : content code name (std::string)
     * @return content id (int)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    std::string  selectContent(std::string);
    bool insertFile(std::string keyValue , std::string strData);
    bool updateFile(std::string keyValue , std::string strData);
    bool createTable();
    bool dropTable();
};

#endif
