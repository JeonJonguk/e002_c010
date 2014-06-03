//
//  CJLMSKidsContent.h
//  S001_Template
//
//  Created by Soonho Hong on 12. 10. 24..
//
//

#ifndef CJLMSKidsContent_h
#define CJLMSKidsContent_h

#pragma once

#include "CJLMSStruct.h"
#include "CJLMSDBManage.h"

/**
 * @author CJEducations
 * @brief manage tblKidsContent class (add selectUpdateKidsContent func)
 * @version v1.0.2
 * @date 2012. 11. 26
 * @since v1.0.0
 */
class CJLMSKidsContent
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
    CJLMSKidsContent();
    CJLMSKidsContent(CJLMSDBManage *pLmsDBManage);
    
    /**
     * @author CJEducations
     * @brief Destructor
     * @version v1.0.0
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    ~CJLMSKidsContent();
    
    static CJLMSKidsContent* create(CJLMSDBManage *pLmsDBManage);
    bool   init();

    
    /**
     * @author CJEducations
     * @brief select kidscontent info from tblKidsContent
     * @version v1.0.0
     * @param kidsId : kids id (int)
     * @param contentId : content id (int)
     * @return kids content struct value (KidsContent)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    KidsContent selectKidsContent(int kidsId, int contentId);
    std::vector<KidsContent>* selectKidsContents(int kidsId);
    
//    KidsContent selectKidsContent(int kidsId, std::string PKGCode);
    
    /**
     * @author CJEducations
     * @brief select kidscontent info list from tblKidsContent
     * @version v1.0.0
     * @param kidsId : kids id (int)
     * @return kids content struct list value (std::vector<KidsContent>*)
     * @date 2012. 11. 26
     * @since v1.0.2
     */
    std::vector<KidsContent>* selectUpdateKidsContent(int kidsId);
    
    /**
     * @author CJEducations
     * @brief select strKey value from tblKidsContent
     * @version v1.0.0
     * @param kidsId : kids id (int)
     * @param contentId : content id (int)
     * @return strKey value (std::string)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    std::string selectKey(int kidsId, int contentId);
    
    /**
     * @author CJEducations
     * @brief select strKey value from tblKidsContent
     * @version v1.0.0
     * @param kidsId : kids id (int)
     * @param contentId : content id (int)
     * @return nCount value (int)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    int selectCount(int kidsId, int contentId);
    
    /**
     * @author CJEducations
     * @brief update nCount value in tblKidsContent
     * @version v1.0.0
     * @param kidsId : kids id (int)
     * @param contentId : content id (int)
     * @param cnt : nCount value (int)
     * @return update query return value (bool)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    bool updateCount(int kidsId, int contentId, int cnt);
    
    /**
     * @author CJEducations
     * @brief update nGrade value in tblKidsContent
     * @version v1.0.0
     * @param kidsId : kids id (int)
     * @param contentId : content id (int)
     * @param grade : nGrade value (int)
     * @return update query return value (bool)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    bool updateGrade(int kidsId, int contentId, int grade);
    
    /**
     * @author CJEducations
     * @brief update dtEndDate value in tblKidsContent (add date param)
     * @version v1.0.1
     * @param kidsId : kids id (int)
     * @param contentId : content id (int)
     * @param date : current date string (std::string)
     * @return update query return value (bool)
     * @date 2012. 11. 22
     * @since v1.0.0
     */
    bool updateEndDate(int kidsId, int contentId, std::string date);
    
    bool updateStartDate(int kidsId, int contentId, std::string date);

    /**
     * @author CJEducations
     * @brief update iUpdateId value in tblKidsContent
     * @version v1.0.0
     * @param kidsId : kids id (int)
     * @param contentId : content id (int)
     * @param updateId : iUpdateId value (int)
     * @return update query return value (bool)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    bool updateUpdateId(int kidsId, int contentId, int updateId);
    
    /**
     * @author CJEducations
     * @brief insert row in tblKidsContent (change param)
     * @version v1.0.1
     * @param info : kids content struct (KidsContent)
     * @return insert query return value (bool)
     * @date 2012. 11. 22
     * @since v1.0.0
     */
    bool insertKidsContent(KidsContent info, int idxKids);
    
private:
    /**
     * @author CJEducations
     * @brief update strKey value in tblKidsContent - update after insert query progress (auto)
     * @version v1.0.0
     * @param kidsId : kids id (int)
     * @param contentId : content id (int)
     * @param key : strKey value (std::string)
     * @return update query return value (bool)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    bool updateKey(int kidsId, int contentId, std::string key, int idxKids);
};

#endif
