//
//  CJLMSUtil.h
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 21..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#ifndef __SoundPhonics__CJLMSUtil__
#define __SoundPhonics__CJLMSUtil__

#include "cocos2d.h"

class CJLMSUtil
{
public:
    static std::string getJsonString(cocos2d::CCDictionary* v_list);
    static std::string getJsonString(cocos2d::CCArray* v_list, std::string strKey);
    
    static std::string getPrepareKey(int iKidsID,
                                     std::string strPKGCode,
                                     std::string strContentCode,
                                     std::string strTableName);

    static std::string getLMSDate(std::string strServerDate);
    
    static std::string getFormatString(std::string strFormat, ...);
};

#endif /* defined(__SoundPhonics__CJLMSUtil__) */
