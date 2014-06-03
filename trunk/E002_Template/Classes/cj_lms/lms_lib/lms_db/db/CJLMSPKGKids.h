//
//  CJLMSPKGKids.h
//  S001_Template
//
//  Created by Soonho Hong on 12. 10. 24..
//
//

#ifndef CJLMSPKGKids_h
#define CJLMSPKGKids_h

#pragma once

#include "CJLMSStruct.h"
#include "CJLMSDBManage.h"

/**
 * @author CJEducations
 * @brief manage tblPKGKids class (add selectUpdatePKGKids, updateUpdateId func)
 * @version v1.0.3
 * @date 2012. 11. 26
 * @since v1.0.0
 */
class CJLMSPKGKids
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
    CJLMSPKGKids();
    CJLMSPKGKids(CJLMSDBManage *pLmsDBManage);
    
    /**
     * @author CJEducations
     * @brief Destructor
     * @version v1.0.0
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    ~CJLMSPKGKids();
    
    static CJLMSPKGKids* create(CJLMSDBManage *pLmsDBManage);
    bool   init();
    
    /**
     * @author CJEducations
     * @brief select kids id from tblPKGKids
     * @version v1.0.0
     * @param PKGCode : package code name (std::string)
     * @return kids Id (int)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    int selectKidsId(std::string PKGCode, int idxKids);
    
    /**
     * @author CJEducations
     * @brief select PKG kids list from tblPKGKids
     * @version v1.0.0
     * @return kids list (std::vector<KidsInfo>*)
     * @date 2012. 11. 26
     * @since v1.0.3
     */
    std::vector<KidsInfo>* selectUpdatePKGKids(int idxKids);
    
    KidsInfo selectPKGKids(int idxKids, std::string packageCode);

    /**
     * @author CJEducations
     * @brief select stage from tblPKGKids
     * @version v1.0.0
     * @param kidsId : kids id (int)
     * @return stage value (int)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    int selectStage(int kidsId);
    
    /**
     * @author CJEducations
     * @brief update stage value in tblPKGKids
     * @version v1.0.0
     * @param kidsId : kids id (int)
     * @param stage : stage value (int)
     * @return update query return value (bool)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    bool updateStage(int kidsId, int stage);
    
    /**
     * @author CJEducations
     * @brief update iUpdateId value in tblPKGKids
     * @version v1.0.0
     * @param kidsId : kids id (int)
     * @param updateId : iUpdateId value (int)
     * @return update query return value (bool)
     * @date 2012. 11. 28
     * @since v1.0.3
     */
    bool updateUpdateId(int kidsId, int updateId);
    
    bool updateStartDate(int kidsId, std::string startDate);

    /**
     * @author CJEducations
     * @brief insert row in tblPKGKids (change param)
     * @version v1.0.2
     * @param info : info struct value (KidsInfo)
     * @return insert query return value (bool)
     * @date 2012. 11. 22
     * @since v1.0.0
     */
    bool insertKids(KidsInfo info, int idxKids);
};

#endif
