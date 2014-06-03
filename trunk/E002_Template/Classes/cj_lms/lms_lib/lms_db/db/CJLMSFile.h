//
//  CJLMSFile.h
//  S001_Template
//
//  Created by Soonho Hong on 12. 10. 24..
//
//

#ifndef CJLMSFile_h
#define CJLMSFile_h

#pragma once

#include "CJLMSStruct.h"
#include "CJLMSDBManage.h"

/**
 * @author CJEducations
 * @brief manage tblFile class
 * @version v1.0.1
 * @date 2012. 11. 19
 * @since v1.0.0
 */
class CJLMSFile
{
private:
    CJLMSDBManage       *m_lmsDBManage;
    
public:
    /**
     * @author CJEducations
     * @brief Constructor
     * @version v1.0.0
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    CJLMSFile();
    CJLMSFile(CJLMSDBManage *pLmsDBManage);
    
    /**
     * @author CJEducations
     * @brief Destructor
     * @version v1.0.0
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    ~CJLMSFile();
    
    static CJLMSFile* create(CJLMSDBManage *pLmsDBManage);
    bool   init();

    
    /**
     * @author CJEducations
     * @brief results from one kind of content, sorted by date
     * @version v1.0.0
     * @param contentId : content id (int)
     * @param gubun : gubun index (int)
     * @return ResFile list - order last date 4 value (vector<ResFile>)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    std::vector<ResFile>* selectContentFile(int contentId, int gubun, int idxKids);
    ResFile selectFileWithMenuID(int contentId, int gubun, int idxKids, int menuId);
    
    std::vector<ResFile>* selectRemoveFile(int contentId, int gubun, int idxKids);
    std::vector<ResFile>* selectRemoveFile(int contentId, int gubun, int idxKids, int menuId);
    /**
     * @author CJEducations
     * @brief results from different types of content, sorted by date
     * @version v1.0.0
     * @param gubun : gubun index (int)
     * @return ResFile list - order last date value (vector<ResFile>)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    std::vector<ResFile>* selectPackageFile(int gubun, int idxKids);
    
    /**
     * @author CJEducations
     * @brief select path in tblFile (add menuNum param)
     * @version v1.0.1
     * @param contentId : content id (int)
     * @param menuNum : content menu number (int)
     * @param gubun : gubun index (int)
     * @return resource path (std::string)
     * @date 2012. 11. 19
     * @since v1.0.0
     */
    std::string selectPath(int contentId, int menuNum, int gubun, int idxKids);
    
    std::string selectCurrentPath(int idxKids);
    
    /**
     * @author CJEducations
     * @brief update kind value in tblFile
     * @version v1.0.0
     * @param fileId : file id (int)
     * @param kind : kind value (int)
     * @return update query return value (bool)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    bool updateKind(int fileId, int kind);
    
    /**
     * @author CJEducations
     * @brief insert row in tblFile
     * @version v1.0.0
     * @param data : ResFile struct value (ResFile)
     * @return insert query return value (bool)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    bool insertFile(ResFile data);

    bool deleteFile(ResFile data);
};

#endif
