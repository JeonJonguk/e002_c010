//
//  CJLMSRecovery.cpp
//  S001-C000
//
//  Created by Soonho Hong on 13. 7. 2..
//  Copyright (c) 2013 CJ Educations. All rights reserved.
//

#include "CJLMSRecovery.h"

#include "CJLMSDefines.h"
#include "CJLMSExtension.h"
#include "CJLMSUtil.h"

#include "THStringUtil.h"
#include "THResourceUtils.h"

#include "CJLMSRecoveryInterface.h"


using namespace LMSExtension;


#define RC_SUCCESS    		0
#define RC_ERROR_PARSE    	-1
#define RC_ERROR_NODATA    	-2
#define RC_ERROR_WRONGKEY  	-3


const char* contentCodeArray[17] =
{
    "c010", "c020", "c030", "c040", "c050", "c150",
    "c060", "c070", "c080", "c090", "c160",
    "c100", "c110", "c120", "c130", "c140", "c170"
};




int CJLMSRecovery::startRecovery(std::string strRecoveryDataPath)
{
    CJLMSRecoveryInterface::getInstance();
    
    std::vector<std::string> recoveryDataPath   = THStringUtil::split(strRecoveryDataPath.c_str(), '_');
    if(0 >= recoveryDataPath.size())            return RC_ERROR_NODATA;
    
    std::string strPKGCode                      = kProjName_SoundPhonics2;
    int         maxStage                        = 17;
    
    for(int recoveryDataIdx=0; recoveryDataIdx<recoveryDataPath.size(); recoveryDataIdx++)
    {
        unsigned long jsonSize          = 0;
        unsigned char *jsonBuffer       = CCFileUtils::sharedFileUtils()->getFileData(recoveryDataPath.at(recoveryDataIdx).c_str(),
                                                                                  "rb",
                                                                                  &jsonSize);
        std::string recoveryJsonData(reinterpret_cast<const char *>(jsonBuffer), jsonSize);
        
        Json::Value rootJsonValue;
        if(true == CJLMSRecovery::_parseJson(recoveryJsonData, rootJsonValue))
        {
            if(true == CJLMSRecovery::_parseElement(rootJsonValue, "learns").isNull())  return false;
            Json::Value learnsJsonValues = CJLMSRecovery::_parseElement(rootJsonValue, "learns");
            
            for(int learnsIdx=0; learnsIdx<learnsJsonValues.size(); learnsIdx++)
            {
                if(-1 == CJLMSRecovery::_getJsonInteger(learnsJsonValues[learnsIdx], "childid") &&
                   true == CJLMSRecovery::_getJsonString(learnsJsonValues[learnsIdx], "goaldate").empty())
                    return RC_ERROR_NODATA;

                Json::Value leanrsJsonValue = learnsJsonValues[learnsIdx];
                int childID                 = CJLMSRecovery::_getJsonInteger(leanrsJsonValue, "childid");
                std::string strDate         = CJLMSRecovery::_getJsonString(leanrsJsonValue, "goaldate");
                std::string strStart        = CJLMSExtension::sharedInstance()->getDiffDate(CJLMSUtil::getLMSDate(strDate).c_str(), -(14*7));
                std::string strEnd          = CJLMSUtil::getLMSDate(strDate);
                CJLMSRecoveryInterface::getInstance()->startPackage(maxStage, strPKGCode, childID, strStart, strEnd);
                CCLog("------------------------------------ Learns Json Value");
                CCLog("maxStage                 : %d", maxStage);
                CCLog("strPKGCode               : %s", strPKGCode.c_str());
                CCLog("childID                  : %d", childID);
                CCLog("strStart                 : %s", strStart.c_str());
                CCLog("strEnd                   : %s", strEnd.c_str());
                CCLog("------------------------------------------------------");

                
                
                if(true == CJLMSRecovery::_parseElement(leanrsJsonValue, "contents").isNull())  return RC_ERROR_PARSE;
                Json::Value contentJsonValues = CJLMSRecovery::_parseElement(leanrsJsonValue, "contents");
                
                for(int contentJsonIdx=0; contentJsonIdx<contentJsonValues.size(); contentJsonIdx++)
                {
                    if(true == CJLMSRecovery::_getJsonString(contentJsonValues[contentJsonIdx], "code").empty() &&
                       true == CJLMSRecovery::_getJsonString(contentJsonValues[contentJsonIdx], "extra").empty())
                        return RC_ERROR_NODATA;
                    
                    Json::Value contentJsonValue    = contentJsonValues[contentJsonIdx];
                    std::string strContentStart     = strStart;
                    std::string strContentEnd       = CJLMSExtension::sharedInstance()->getDeviceDateTime();
                    std::string strContentCode      = CJLMSRecovery::_getJsonString(contentJsonValue, "code");
                    std::string strContentExtra     = CJLMSRecovery::_getJsonString(contentJsonValue, "extra");
                    CJLMSRecoveryInterface::getInstance()->startContent(strContentCode, strContentStart, strContentEnd);
                    CCLog("------------------------------------ Content Json Value");
                    CCLog("   strContentCode            : %s", strContentCode.c_str());
                    CCLog("   strContentStart           : %s", strContentStart.c_str());
                    CCLog("   strContentEnd             : %s", strContentEnd.c_str());
                    CCLog("   strContentExtra           : %s", strContentExtra.c_str());
                    CCLog("------------------------------------------------------");
                    

                    
                    if(true == CJLMSRecovery::_parseElement(contentJsonValue, "steps").isNull()) return RC_ERROR_PARSE;
                    Json::Value progressJsonValues = CJLMSRecovery::_parseElement(contentJsonValue, "steps");
                    
                    for(int progressJsonIdx=0; progressJsonIdx<progressJsonValues.size(); progressJsonIdx++)
                    {
                        if(true == CJLMSRecovery::_getJsonString(progressJsonValues[progressJsonIdx], "startdate").empty() &&
                           true == CJLMSRecovery::_getJsonString(progressJsonValues[progressJsonIdx], "enddate").empty() &&
                           true == CJLMSRecovery::_getJsonString(progressJsonValues[progressJsonIdx], "code").empty() &&
                           true == CJLMSRecovery::_getJsonString(progressJsonValues[progressJsonIdx], "extra").empty() &&
                           -1 == CJLMSRecovery::_getJsonInteger(progressJsonValues[progressJsonIdx], "circle"))
                            return RC_ERROR_NODATA;
                        
                        Json::Value progressJsonValue   = progressJsonValues[progressJsonIdx];
                        std::string strProgressStart    = CJLMSUtil::getLMSDate(CJLMSRecovery::_getJsonString(progressJsonValue, "startdate"));
                        std::string strProgressEnd      = CJLMSUtil::getLMSDate(CJLMSRecovery::_getJsonString(progressJsonValue, "enddate"));
                        std::string strProgressCode     = CJLMSRecovery::_getJsonString(progressJsonValue, "code");
                        std::string strProgressExtra    = CJLMSRecovery::_getJsonString(progressJsonValue, "extra");
                        int         progressCount       = CJLMSRecovery::_getJsonInteger(progressJsonValue, "circle");
                        int         progressMenuNumber  = -1;

                        Json::Value progressExtraJsonValue;
                        if(true == CJLMSRecovery::_parseJson(strProgressExtra, progressExtraJsonValue))
                            progressMenuNumber          = CJLMSRecovery::_getJsonInteger(progressExtraJsonValue, "menuNum");
                        else
                            return RC_ERROR_PARSE;

                        if(!strProgressStart.empty() && !strProgressEnd.empty() && !strProgressCode.empty() && progressCount>0 && progressMenuNumber>0)
                            CJLMSRecoveryInterface::getInstance()->setContentProgress(progressMenuNumber, progressCount, strProgressCode,
                                                                                      strProgressStart, strProgressEnd);
                        CCLog("------------------------------------ Progress Json Value");
                        CCLog("      progressMenuNumber             : %d", progressMenuNumber);
                        CCLog("      progressCount                  : %d", progressCount);
                        CCLog("      strProgressStart               : %s", strProgressStart.c_str());
                        CCLog("      strProgressEnd                 : %s", strProgressEnd.c_str());
                        CCLog("      strProgressCode                : %s", strProgressCode.c_str());
                        CCLog("------------------------------------------------------");
                    }
                    
                    
                    if(true == CJLMSRecovery::_parseElement(contentJsonValue, "grades").isNull())   return RC_ERROR_PARSE;
                    Json::Value gradeJsonValues = CJLMSRecovery::_parseElement(contentJsonValue, "grades");
                    
                    for(int gradeJsonIdx=0; gradeJsonIdx<gradeJsonValues.size(); gradeJsonIdx++)
                    {
                        if(true == CJLMSRecovery::_getJsonString(gradeJsonValues[gradeJsonIdx], "gradedate").empty() &&
                           true == CJLMSRecovery::_getJsonString(gradeJsonValues[gradeJsonIdx], "extra").empty())
                            return RC_ERROR_NODATA;
                        
                        Json::Value gradeJsonValue  = gradeJsonValues[gradeJsonIdx];
                        std::string strGradeDate    = CJLMSUtil::getLMSDate(CJLMSRecovery::_getJsonString(gradeJsonValue, "gradedate"));
                        std::string strGradeExtra   = CJLMSRecovery::_getJsonString(gradeJsonValue, "extra");
                        CJLMSRecoveryInterface::getInstance()->setContentGrade(strGradeExtra, strGradeDate);
                        CCLog("------------------------------------ Grade Json Value");
                        CCLog("      strGradeExtra                  : %s", strGradeExtra.c_str());
                        CCLog("      strGradeDate                   : %s", strGradeDate.c_str());
                        CCLog("------------------------------------------------------");
                    }
                    CJLMSRecoveryInterface::getInstance()->endContent();
                }
                CJLMSRecoveryInterface::getInstance()->endPackage();
            }
        }
        else
        {
            CJLMSRecoveryInterface::release();
            return RC_ERROR_PARSE;
        }
    }
    
    CJLMSRecoveryInterface::release();
    return RC_SUCCESS;
}


int CJLMSRecovery::_getContentStage(std::string strContentCode)
{
    for (int i = 0; i < 20; i++) {
        if (!strContentCode.compare(contentCodeArray[i])) {
            return i+1;
        }
    }
    
    return -1;
}

bool CJLMSRecovery::_parseJson(const std::string &rDoucument, Json::Value &rJsonValue)
{
    Json::Reader jsonReader;
    
    if(true == jsonReader.parse(rDoucument, rJsonValue))
    {
        CCLog("JSON Parsing SUCCESS.");
        return true;
    }
    else
    {
        CCLog("JSON Parsing FAIL.");
        return false;
    }
}

Json::Value CJLMSRecovery::_parseElement(Json::Value &rRootJsonValue, std::string strKey)
{
    if(true == rRootJsonValue.isMember(strKey))
    {
        CCLog("JSON Element Parsing SUCCESS. (key = %s)", strKey.c_str());
        
        Json::Value elementJsonValue = rRootJsonValue.get(strKey, "UTF-8");
        return elementJsonValue;
    }
    else
    {
        CCLog("JSON Element Parsing FAIL. (key = %s)", strKey.c_str());
        return NULL;
    }
}

std::string CJLMSRecovery::_getJsonString(Json::Value jsonData, std::string strKey)
{
    if(true == jsonData.isMember(strKey))
    {
        return jsonData.get(strKey, "UTF-8").asString();
    }
    else
    {
        CCLog("Not found key %s", strKey.c_str());
        return NULL;
    }
}

int CJLMSRecovery::_getJsonInteger(Json::Value jsonData, std::string strKey)
{
    if(false == CJLMSRecovery::_getJsonString(jsonData, strKey).empty())
    {
        std::string strResult = CJLMSRecovery::_getJsonString(jsonData, strKey);
        return CCString::createWithFormat("%s", strResult.c_str())->intValue();
    }
    else
    {
        return -1;
    }
}






#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "Jni.h"
extern "C"
{
    int Java_com_cjeducations_ithink_e001_RecoveryReceiver_recoveryCall(JNIEnv *env, jobject thisobj, jstring path)
    {
        std::string ret;
        if(path)
        {
            const char* temp = (char*)env->GetStringUTFChars(path, NULL);
            ret = temp;
        }
        else
        {
            ret = "error_data";
        }
        
        return CJLMSRecovery::startRecovery(ret);
    }
}
#endif  // CC_PLATFORM_ANDROID
