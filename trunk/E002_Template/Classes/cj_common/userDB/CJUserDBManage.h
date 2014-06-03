//
//  CJUserDBManage.h
//  S001_Template
//
//  Created by Soonho Hong on 12. 10. 24..
//
//

#ifndef CJUserDBManage_h
#define CJUserDBManage_h

#pragma once
#include "sqlite3.h"
#include <sstream>
#include <vector>
#include <assert.h>
#define DB_USER_NAME            "userData.sqlite"
/**
 * @author CJEducations
 * @brief db file manage class (modify open, setWritePath func)
 * @version v1.0.4
 * @date 2012. 11. 28
 * @since v1.0.0
 */
class CJUserDBManage
{
public:
    /**
     * @author CJEducations
     * @brief Constructor
     * @version v1.0.0
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    CJUserDBManage();
    
    /**
     * @author CJEducations
     * @brief Destructor
     * @version v1.0.0
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    ~CJUserDBManage();
    
    /**
     * @author CJEducations
     * @brief singleton interface constructor func
     * @version v1.0.0
     * @return construct class (CJUserDBManage)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    static CJUserDBManage* sharedInstance();
    
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
     * @brief get db object for db manage class
     * @version v1.0.0
     * @return db object (sqlite)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    sqlite3* getDB();
    /**
     * @author CJEducations
     * @brief open db file (remove param)
     * @version v1.0.1
     * @return open process return value (bool)
     * @date 2012. 11. 29
     * @since v1.0.0
     */
    bool open(int platform);
    /**
     * @author CJEducations
     * @brief close db file
     * @version v1.0.0
     * @return close process return value (bool)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    bool close();

    
private:
    /**
     * @brief retry index value
     */
    int busyRetryTimeout;
    
    sqlite3* m_db;
};

#endif
