//
//  CJLMSGrade.h
//  S001_Template
//
//  Created by Soonho Hong on 12. 10. 24..
//
//

#ifndef CJLMSGrade_h
#define CJLMSGrade_h

#pragma once

#include "CJLMSStruct.h"
#include "CJLMSDBManage.h"

/**
 * @author CJEducations
 * @brief manage tblGrade class (add selectUpdateGrade func)
 * @version v1.0.2
 * @date 2012. 12. 17
 * @since v1.0.0
 */
class CJLMSGrade
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
    CJLMSGrade();
    CJLMSGrade(CJLMSDBManage *pLmsDBManage);    
    
    /**
     * @author CJEducations
     * @brief Destructor
     * @version v1.0.0
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    ~CJLMSGrade();
    
    static CJLMSGrade* create(CJLMSDBManage *pLmsDBManage);
    bool   init();
    
    /**
     * @author CJEducations
     * @brief select grade info from tblGrade
     * @version v1.0.0
     * @param kidsId : kids id (int)
     * @param contentId : content id (int)
     * @return Grade list - order last date value (vector<Grade>)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    std::vector<Grade>* selectGrade(int kidsId, int contentId, int questionId);
    
    /**
     * @author CJEducations
     * @brief select grade info from tblProgress for LMSCenter
     * @version v1.0.0
     * @param kidsId : kids id (int)
     * @param contentId : content id (int)
     * @return Grade list (vector<Grade>)
     * @date 2012. 12. 17
     * @since v1.0.2
     */
    std::vector<Grade>* selectUpdateGrade(int kidsId, int contentId);
    
    /**
     * @author CJEducations
     * @brief select strKey value from tblGrade
     * @version v1.0.0
     * @param gradeId : grade id (int)
     * @return strKey value (std::string)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    std::string selectKey(int gradeId);
    
    /**
     * @author CJEducations
     * @brief update iUpdateId value in tblGrade
     * @version v1.0.0
     * @param gradeId : grade id (int)
     * @param updateId : update index id (int)
     * @return update query return value (bool)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    bool updateUpdateId(int gradeId, int updateId);
    
    /**
     * @author CJEducations
     * @brief insert row in tblGrade (remove getdate func)
     * @version v1.0.1
     * @param data : Grade struct value (Grade)
     * @return insert query return value (bool)
     * @date 2012. 11. 22
     * @since v1.0.0
     */
    bool insertGrade(Grade data, int idxKids);
    
private:
    /**
     * @author CJEducations
     * @brief update strKey value in tblGrade - update after insert query progress (auto)
     * @version v1.0.0
     * @param key : strKey value (std::string)
     * @return update query return value (bool)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    bool updateKey(std::string key, int idxKids);
};

#endif
