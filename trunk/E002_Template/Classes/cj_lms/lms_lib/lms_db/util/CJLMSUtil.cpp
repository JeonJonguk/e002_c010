//
//  CJLMSUtil.cpp
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 21..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#include "CJLMSUtil.h"
#include "THStringUtil.h"

using namespace cocos2d;


std::string CJLMSUtil::getJsonString(cocos2d::CCDictionary* v_list)
{
    std::string ret = "{";
    std::string valueFormat = "\"[__key__]\":\"[__value__]\"";
    
    CCArray* keyArray = v_list->allKeys();
    
    for (int var = 0; var < v_list->count(); var++) {
        std::string key = ((CCString*)keyArray->objectAtIndex(var))->m_sString;
        std::string value = ((CCString*)v_list->valueForKey(key))->m_sString;
        std::string rowString = valueFormat;
        
        rowString = THStringUtil::replaceAll(
                                             THStringUtil::replaceAll(
                                                                      rowString,
                                                                      "[__key__]",
                                                                      key
                                                                      ),
                                             "[__value__]",
                                             value
                                             );
        
        if (var < v_list->count() - 1)
            rowString.append(",");
		ret.append(rowString);
    }
    
    ret.append("}");
    
    return ret;
}


std::string CJLMSUtil::getJsonString(cocos2d::CCArray* v_list, std::string strKey)
{
    std::string ret = CCString::createWithFormat("{\"%s\":[", strKey.c_str())->getCString();
    std::string valueFormat = "\"[__key__]\":\"[__value__]\"";
    
    for(int arrIdx=0; arrIdx<v_list->count(); arrIdx++)
    {
        ret.append("{");
        CCDictionary *item = (CCDictionary *)v_list->objectAtIndex(arrIdx);
        CCArray* keyArray  = item->allKeys();

        for (int var = 0; var < v_list->count(); var++) {
            std::string key = ((CCString *)keyArray->objectAtIndex(var))->m_sString;
            std::string value = ((CCString *)item->valueForKey(key))->m_sString;
            std::string rowString = valueFormat;
            
            rowString = THStringUtil::replaceAll(
                                                 THStringUtil::replaceAll(
                                                                          rowString,
                                                                          "[__key__]",
                                                                          key
                                                                          ),
                                                 "[__value__]",
                                                 value
                                                 );
            
            if (var < v_list->count() - 1)
                rowString.append(",");
            ret.append(rowString);
        }
        
        if(arrIdx+1<v_list->count())
        {
            ret.append("},");
        }
        else
        {
            ret.append("}");
        }
    }
    
    ret.append("]}");
    return ret;
}

std::string CJLMSUtil::getPrepareKey(int iKidsID,
                                     std::string strPKGCode,
                                     std::string strContentCode,
                                     std::string strTableName)
{
    std::stringstream intValue;
	intValue << iKidsID;
	std::string string = intValue.str();
	string.append("_");
	string.append(strPKGCode);
	string.append("_");
	string.append(strContentCode);
	string.append("_");
	string.append(strTableName);
	string.append("_");
    
	return string;
}

std::string CJLMSUtil::getLMSDate(std::string strServerDate)
{
    std::vector<std::string> dotStrings = THStringUtil::split(strServerDate.c_str(), '.');
	std::vector<std::string> baseStrings = THStringUtil::split(dotStrings.at(0).c_str(), ' ');
	std::vector<std::string> dateStrings = THStringUtil::split(baseStrings.at(0).c_str(), '-');
	std::vector<std::string> timeStrings = THStringUtil::split(baseStrings.at(1).c_str(), ':');
    
	std::string retString = "";
    
	for (int i = 0; i < dateStrings.size(); i++) {
		retString.append(dateStrings.at(i));
		retString.append("_");
	}
	for (int i = 0; i < timeStrings.size(); i++) {
		retString.append(timeStrings.at(i));
		if (i < timeStrings.size() - 1) {
			retString.append("_");
		}
	}
    
	return retString;
}

std::string CJLMSUtil::getFormatString(std::string strFormat, ...)
{
    std::string str;
    
    va_list ap;
    va_start(ap, strFormat);

    char* pBuf = (char*)malloc(1024*100);
    if (pBuf != NULL)
    {
        vsnprintf(pBuf, 1024*100, strFormat.c_str(), ap);
        str = pBuf;
        free(pBuf);
    }
    
    va_end(ap);

    return str;
}

