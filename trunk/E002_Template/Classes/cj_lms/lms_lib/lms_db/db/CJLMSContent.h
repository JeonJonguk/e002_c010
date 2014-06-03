//
//  CJLMSContent.h
//  S001_Template
//
//  Created by Soonho Hong on 12. 10. 24..
//
//

#ifndef CJLMSContent_h
#define CJLMSContent_h

#pragma once

#include "CJLMSStruct.h"
#include "CJLMSDBManage.h"

/**
 * @author CJEducations
 * @brief manage tblContent class (add selectContentList func)
 * @version v1.0.1
 * @date 2012. 11. 29
 * @since v1.0.0
 */
class CJLMSContent
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
    CJLMSContent();
    CJLMSContent(CJLMSDBManage *pLmsDBManage);
    
    
    /**
     * @author CJEducations
     * @brief Destructor
     * @version v1.0.0
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    ~CJLMSContent();
    
    static CJLMSContent* create(CJLMSDBManage *pLmsDBManage);

    
    /**
     * @author CJEducations
     * @brief select content info from tblContent
     * @version v1.0.0
     * @param contentId : content id value (int)
     * @return content struct value (Content)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    Content selectContent(int contentId);
    
    /**
     * @author CJEducations
     * @brief select content info from tblContent
     * @version v1.0.0
     * @param contentId : content id value (int)
     * @return content struct value (Content)
     * @date 2012. 11. 06
     * @since v1.0.0
     */
    Content selectContent(std::string PKGCode, int iStage);
    Content selectContent(std::string PKGCode, std::string contentCode);
    
    /**
     * @author CJEducations
     * @brief select content list order by package code info from tblContent
     * @version v1.0.0
     * @param PKGCode : package code value (std::string)
     * @return content struct list value (std::vector<Content>*)
     * @date 2012. 11. 29
     * @since v1.0.1
     */
//    std::vector<Content>* selectContentList(std::string PKGCode);
    
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
    int selectContentId(std::string PKGCode, std::string contentCode);

    
    int getContentCount();
};

#endif
