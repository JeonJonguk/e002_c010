//
//  THLocalizer.cpp
//  Think
//
//  Created by pureye4u BX on 12. 7. 18..
//  Copyright CJ Educations 2012. All rights reserved.
//

#include "THLocalizer.h"
#include "THUserDefault.h"
#include "THFileUtil.h"
#include "THStringUtil.h"
#include "../Support/json/reader.h"

#include "CCFileUtils.h"

// Singleton localizer
THLocalizer *s_pCurrentLocalizer = NULL;

// Constructor
THLocalizer::THLocalizer():
						m_tLocalizeData(0)
{

}

// Destructor
THLocalizer::~THLocalizer()
{

}

void THLocalizer::destroy()
{
	if(s_pCurrentLocalizer != NULL)
	{
		delete s_pCurrentLocalizer;
		s_pCurrentLocalizer = NULL;
	}
}

// Get singleton localizer
THLocalizer *THLocalizer::getCurrentLocalizer()
{
	if(!s_pCurrentLocalizer)
	{
		s_pCurrentLocalizer = new THLocalizer();
		s_pCurrentLocalizer->init();
	}

	return s_pCurrentLocalizer;
}

// Initializer
bool THLocalizer::init()
{
	// Load language file
	if(!this->load())
	{
		return false;
	}

	return true;
}

// Load local file "text_[LanguageCode].json"
bool THLocalizer::load()
{
	// Load file
	std::string fileName = this->withLocaleString("pkg_common/json/text.json");

    /*
     * cocos2dx v2.1.4 deplicated CCFileUtils::fullPathFromRelativePath()
     * CCFileUtils::fullPathFromRelativePath() is not thread-safe, it use autorelease().
     *
     * std::string path = cocos2d::CCFileUtils::sharedFileUtils()->
     * fullPathFromRelativePath(fileName.c_str());
     */
    std::string path = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName.c_str());
    
    

	// When localization file is not exists
//	if(!THFileUtil::existFile(path.c_str()))
//	{
//		return false;
//	}
    // in android, doesn't work.

	unsigned long nSize = 0;
	unsigned char* pBuffer =
			cocos2d::CCFileUtils::sharedFileUtils()->getFileData(
					path.c_str(),
					"rb",
					&nSize
			);

	// Parse user default file
	std::string textString(reinterpret_cast<const char *>(pBuffer), nSize);
    
    // Add LeeYJ, Memory leak.
    CC_SAFE_DELETE_ARRAY(pBuffer);
    
	Json::Reader jsonReader;
	bool isParsed = jsonReader.parse(textString.c_str(), m_tLocalizeData);
	if(!isParsed)
	{
		m_tLocalizeData = 0;
		return false;
	}

	return true;
}

// Check has string localize value for key
bool THLocalizer::hasStringForKey(const char *key)
{
	if(m_tLocalizeData == 0)
	{
		return false;
	}

	return m_tLocalizeData.isMember(key);
}

// Get localized string
std::string THLocalizer::getStringForKey(const char *key)
{
	if(m_tLocalizeData == 0)
	{
		return key;
	}

	if(!m_tLocalizeData.isMember(key))
	{
		return key;
	}

	return m_tLocalizeData.get(key, "UTF-8").asString();
}

// Add locale string after input string
std::string THLocalizer::withLocaleString(const char *input)
{
	std::string output = "";
	std::vector<std::string> split = THStringUtil::split(input, '.');
	int l = split.size();
	if(l > 1)
	{
		l--;
		for(int i = 0; i < l; i++)
		{
			output.append(split[i]);
		}

		output.append("@");
		output.append(this->getLanguageCode());
		output.append(".");
		output.append(split[l]);
	}

	return output;
}

// Get language code
std::string THLocalizer::getLanguageCode()
{
	return "ko";

	// Load user default value for "lang" key
	std::string langString = THUserDefault::getCurrentUserDefault()->getStringForKey("lang");

	// Default language code "en"
	std::string langCode = "en";

	// Switch language code (now have only Korean to ko)
	if(langString.compare("Korean") == 0)
	{
		langCode = "ko";
	}

	return langCode;
}

// Set language code
bool THLocalizer::setLanguageCode(const char *code)
{
	//	printf("##### set lang code: %s", code);
	std::string codeString = code;
	if(codeString.compare("en") == 0)
	{
		THUserDefault::getCurrentUserDefault()->setStringForKey("lang", "English");
		this->load();

		return true;
	}
	else if(codeString.compare("ko") == 0)
	{
		THUserDefault::getCurrentUserDefault()->setStringForKey("lang", "Korean");
		this->load();

		return true;
	}

	return false;
}

// Set locale from system user default language setting
void THLocalizer::setLocaleFromSystemLanguage()
{
	std::string langCode = THUserDefault::getCurrentUserDefault()->getStringForKey("AppleLanguages");
	this->setLanguageCode(langCode.c_str());
}


