//
//  CJLMSProgress.h
//  S001_Template
//
//  Created by Soonho Hong on 12. 10. 24..
//
//

#ifndef CJLMSProgress_h
#define CJLMSProgress_h

#pragma once

#include "CJLMSStruct.h"
#include "CJLMSDBManage.h"

/**
 * @author CJEducations
 * @brief manage tblProgress class (add selectUpdateProgress func)
 * @version v1.0.2
 * @date 2012. 11. 28
 * @since v1.0.0
 */
class CJLMSProgress
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
    CJLMSProgress();
    CJLMSProgress(CJLMSDBManage *pLmsDBManage);
    
    
    /**
     * @author CJEducations
     * @brief Destructor
     * @version v1.0.0
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    ~CJLMSProgress();
    
    static CJLMSProgress* create(CJLMSDBManage *pLmsDBManage);
    bool   init();
    
    /**
     * @author CJEducations
     * @brief select progress info from tblProgress
     * @version v1.0.0
     * @param kidsId : kids id (int)
     * @param contentId : content id (int)
     * @return Progress list (vector<Progress>)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    std::vector<Progress>* selectProgressList(int kidsId, int contentId);
    
    /**
     * @author CJEducations
     * @brief select progress info from tblProgress for LMSCenter
     * @version v1.0.0
     * @param kidsId : kids id (int)
     * @param contentId : content id (int)
     * @return Progress list (vector<Progress>)
     * @date 2012. 11. 28
     * @since v1.0.2
     */
    std::vector<Progress>* selectUpdateProgress(int kidsId, int contentId);
    
    /**
     * @author CJEducations
     * @brief select progress info from tblProgress
     * @version v1.0.0
     * @param kidsId : kids id (int)
     * @param contentId : content id (int)
     * @param munuNum : menu number index (int)
     * @return Progress struct value (Progress)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    Progress selectProgress(int kidsId, int contentId, int munuNum);
    
    bool isExistProgress(std::string key);

    /**
     * @author CJEducations
     * @brief select strKey value from tblProgress
     * @version v1.0.0
     * @param kidsId : kids id (int)
     * @param contentId : content id (int)
     * @param munuNum : menu number index (int)
     * @return strKey value (std::string)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    std::string selectKey(int kidsId, int contentId, int menuNum);
    
    /**
     * @author CJEducations
     * @brief update nCount value in tblProgress
     * @version v1.0.0
     * @param kidsId : kids id (int)
     * @param contentId : content id (int)
     * @param munuNum : menu number index (int)
     * @return update query return value (bool)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    bool updateCount(int kidsId, int contentId, int menuNum);
    
    bool updateCount(int kidsId, int contentId, int menuNum, int count);

    /**
     * @author CJEducations
     * @brief update dtEndDate value in tblProgress (change param)
     * @version v1.0.1
     * @param data : progress struct value (Progress)
     * @return update query return value (bool)
     * @date 2012. 11. 22
     * @since v1.0.0
     */
    bool updateEndDate(Progress data);
    
    /**
     * @author CJEducations
     * @brief update iUpdateId value in tblProgress
     * @version v1.0.0
     * @param kidsId : kids id (int)
     * @param contentId : content id (int)
     * @param munuNum : menu number index (int)
     * @param updateId : iUpdateId value (int)
     * @return update query return value (bool)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    bool updateUpdateId(int kidsId, int contentId, int menuNum, int updateId);
    
    /**
     * @author CJEducations
     * @brief insert row in tblProgress (remove getdate func)
     * @version v1.0.1
     * @param data : progress struct value (Progress)
     * @return insert query return value (bool)
     * @date 2012. 11. 22
     * @since v1.0.0
     */
    bool insertProgress(Progress data, int idxKids);
    
    bool insertProgressWithCount(Progress data, int count);

private:
    /**
     * @author CJEducations
     * @brief update strKey value in tblProgress - update after insert query progress (auto)
     * @version v1.0.0
     * @param kidsId : kids id (int)
     * @param contentId : content id (int)
     * @param munuNum : menu number index (int)
     * @param key : strKey value (std::string)
     * @return update query return value (bool)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    bool updateKey(int kidsId, int contentId, int menuNum, std::string key, int idxKids);
};

#endif
