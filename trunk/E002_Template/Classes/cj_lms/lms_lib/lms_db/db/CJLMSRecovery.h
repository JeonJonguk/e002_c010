//
//  CJLMSRecovery.h
//  S001-C000
//
//  Created by Soonho Hong on 13. 7. 2..
//  Copyright (c) 2013 CJ Educations. All rights reserved.
//

#ifndef __S001_C000__CJLMSRecovery__
#define __S001_C000__CJLMSRecovery__

#include "cocos2d.h"
#include "THResourceUtils.h"

USING_NS_CC;

class CJLMSRecovery
{
private:
    
public:
    static int startRecovery(std::string strRecoveryDataPath);
    
private:
    static int _getContentStage(std::string strContentCode);
    
    static bool _parseJson(const std::string &rDoucument, Json::Value &rJsonValue);
    static Json::Value _parseElement(Json::Value &rRootJsonValue, std::string strKey);
    static std::string _getJsonString(Json::Value jsonData, std::string strKey);
    static int _getJsonInteger(Json::Value jsonData, std::string strKey);
};

#endif /* defined(__S001_C000__CJLMSRecovery__) */
