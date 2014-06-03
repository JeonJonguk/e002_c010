//
//  CJLMSQuestion.h
//  S001-C130
//
//  Created by Soonho Hong on 13. 4. 8..
//  Copyright (c) 2013 CJ Educations. All rights reserved.
//

#ifndef __S001_C130__CJLMSQuestion__
#define __S001_C130__CJLMSQuestion__

#include "CJLMSStruct.h"
#include "CJLMSDBManage.h"

class CJLMSQuestion
{
private:
    CJLMSDBManage       *m_lmsDBManage;
    
public:
    CJLMSQuestion();
    CJLMSQuestion(CJLMSDBManage *pLmsDBManage);
    ~CJLMSQuestion();
    
    static CJLMSQuestion* create(CJLMSDBManage *pLmsDBManage);

    Question selectContent(int questionId);

    Question selectContent(std::string contentCode, int menuNum, int questionIndex);
};

#endif /* defined(__S001_C130__CJLMSQuestion__) */
