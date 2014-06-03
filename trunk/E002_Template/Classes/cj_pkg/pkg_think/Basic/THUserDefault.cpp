//
//  THUserDefault.cpp
//  Think
//
//  Created by pureye4u BX on 12. 7. 16..
//  Copyright CJ Educations 2012. All rights reserved.
//

#include "THUserDefault.h"
#include "THFileUtil.h"
#include "../Support/json/reader.h"
#include "../Support/json/writer.h"

static const char *DEFAULT_FILE_NAME = "THUserDefault";

THUserDefault *s_pCurrentUserDefault = NULL;

THUserDefault::THUserDefault()
{
}

THUserDefault::~THUserDefault()
{
	if(m_bIsChanged)
	{
		this->save();
	}
}

THUserDefault *THUserDefault::getCurrentUserDefault()
{
	if(!s_pCurrentUserDefault)
	{
		s_pCurrentUserDefault = new THUserDefault();
		s_pCurrentUserDefault->init();
	}
	
	return s_pCurrentUserDefault;
}

bool THUserDefault::init()
{
	// Initialize
	if(m_sDefaultFileName.compare("") == 0)
	{
		m_sDefaultFileName = DEFAULT_FILE_NAME;
	}
	
	
	return false;
}

bool THUserDefault::initWithFile(const char *pszFileName)
{
	m_sDefaultFileName = pszFileName;
		
	return this->init();
}

bool THUserDefault::hasValueForKey(const char *pszKey)
{
	if(m_tUserDefaultData == 0)
	{
		return false;
	}
	
	return m_tUserDefaultData.isMember(pszKey);
}

std::string THUserDefault::getStringForKey(const char *pszKey)
{
	std::string sRet;
	if(m_tUserDefaultData == 0)
	{
		return sRet;
	}
	
	if(!m_tUserDefaultData.isMember(pszKey))
	{
		return sRet;
	}
	
	Json::Value value = m_tUserDefaultData.get(pszKey, "UTF-8");
	if(value.isString())
	{
		sRet = value.asString();
	}
	
	return sRet;
}

void THUserDefault::setStringForKey(const char *pszKey, const char *pszValue, bool bWithSave)
{
	if(m_tUserDefaultData == 0)
	{
		m_tUserDefaultData = Json::Value();
	}
	
	if(m_tUserDefaultData.isMember(pszKey))
	{
		Json::Value value = m_tUserDefaultData.get(pszKey, "UTF-8");
		if(value.isString())
		{
			if(value.asString().compare(pszValue) == 0)
			{
				// Value for key is same
				return;
			}
		}
		else
		{
			// Already registered this key other type
			return;
		}
	}
	
	m_tUserDefaultData[pszKey] = pszValue;
	m_bIsChanged = true;
	
	if(bWithSave)
	{
		this->save();
	}
}

bool THUserDefault::getBoolForKey(const char *pszKey)
{
	if(m_tUserDefaultData == 0)
	{
		return false;
	}
	
	if(!m_tUserDefaultData.isMember(pszKey))
	{
		return false;
	}
	
	Json::Value value = m_tUserDefaultData.get(pszKey, "UTF-8");
	if(!value.isBool())
	{
		return false;
	}
	
	return value.asBool();
}

void THUserDefault::setBoolForKey(const char *pszKey, bool bValue, bool bWithSave)
{
	if(m_tUserDefaultData == 0)
	{
		m_tUserDefaultData = Json::Value();
	}
	
	if(m_tUserDefaultData.isMember(pszKey))
	{
		Json::Value value = m_tUserDefaultData.get(pszKey, "UTF-8");
		if(value.isBool())
		{
			if(value.asBool() == bValue)
			{
				// Value for key is same
				return;
			}
		}
		else
		{
			// Already registered this key other type
			return;
		}
	}
	
	m_tUserDefaultData[pszKey] = bValue;
	m_bIsChanged = true;
	
	if(bWithSave)
	{
		this->save();
	}
}

int THUserDefault::getIntegerForKey(const char *pszKey)
{
	if(m_tUserDefaultData == 0)
	{
		return 0;
	}
	
	if(!m_tUserDefaultData.isMember(pszKey))
	{
		return 0;
	}
	
	Json::Value value = m_tUserDefaultData.get(pszKey, "UTF-8");
	if(!value.isInt())
	{
		return 0;
	}
	
	return value.asInt();
}

void THUserDefault::setIntegerForKey(const char *pszKey, int iValue, bool bWithSave)
{
	if(m_tUserDefaultData == 0)
	{
		m_tUserDefaultData = Json::Value();
	}
	
	if(m_tUserDefaultData.isMember(pszKey))
	{
		Json::Value value = m_tUserDefaultData.get(pszKey, "UTF-8");
		if(value.isInt())
		{
			if(value.asInt() == iValue)
			{
				// Value for key is same
				return;
			}
		}
		else
		{
			// Already registered this key other type
			return;
		}
	}
	
	m_tUserDefaultData[pszKey] = iValue;
	m_bIsChanged = true;
	
	if(bWithSave)
	{
		this->save();
	}
}

double THUserDefault::getDoubleForKey(const char *pszKey)
{
	if(m_tUserDefaultData == 0)
	{
		return 0;
	}
	
	if(!m_tUserDefaultData.isMember(pszKey))
	{
		return 0;
	}
	
	Json::Value value = m_tUserDefaultData.get(pszKey, "UTF-8");
	if(!value.isDouble())
	{
		return 0;
	}
	
	return value.asDouble();
}

void THUserDefault::setDoubleForKey(const char *pszKey, double dValue, bool bWithSave)
{
	if(m_tUserDefaultData == 0)
	{
		m_tUserDefaultData = Json::Value();
	}
	
	if(m_tUserDefaultData.isMember(pszKey))
	{
		Json::Value value = m_tUserDefaultData.get(pszKey, "UTF-8");
		if(value.isDouble())
		{
			if(value.asDouble() == dValue)
			{
				// Value for key is same
				return;
			}
		}
		else
		{
			// Already registered this key other type
			return;
		}
	}
	
	m_tUserDefaultData[pszKey] = dValue;
	m_bIsChanged = true;
	
	if(bWithSave)
	{
		this->save();
	}
}

unsigned int THUserDefault::getUnsignedIntegerForKey(const char *pszKey)
{
	if(m_tUserDefaultData == 0)
	{
		return 0;
	}
	
	if(!m_tUserDefaultData.isMember(pszKey))
	{
		return 0;
	}
	
	Json::Value value = m_tUserDefaultData.get(pszKey, "UTF-8");
	if(!value.isUInt())
	{
		return 0;
	}
	
	return value.asUInt();
}

void THUserDefault::setUnsignedIntegerForKey(const char *pszKey, unsigned int iValue, bool bWithSave)
{
	if(m_tUserDefaultData == 0)
	{
		m_tUserDefaultData = Json::Value();
	}
	
	if(m_tUserDefaultData.isMember(pszKey))
	{
		Json::Value value = m_tUserDefaultData.get(pszKey, "UTF-8");
		if(value.isUInt())
		{
			if(value.asUInt() == iValue)
			{
				// Value for key is same
				return;
			}
		}
		else
		{
			// Already registered this key other type
			return;
		}
	}
	
	m_tUserDefaultData[pszKey] = iValue;
	m_bIsChanged = true;
	
	if(bWithSave)
	{
		this->save();
	}
}

bool THUserDefault::load()
{
	std::string sPath = THFileUtil::getWriteablePath();
	sPath.append(m_sDefaultFileName.c_str());
	if(!THFileUtil::existFile(sPath.c_str()))
	{
		return false;
	}
	
	std::string sUserDefaultStr = THFileUtil::readFromFile(sPath.c_str());
	
	Json::Reader jsonReader;
	bool bIsParsed = jsonReader.parse(sUserDefaultStr.c_str(), m_tUserDefaultData);
	if(!bIsParsed)
	{
		m_tUserDefaultData = 0;
		return false;
	}
	
	return true;
}

bool THUserDefault::save()
{
	if(!m_bIsChanged)
	{
		return false;
	}
	
	Json::FastWriter jsonWriter;
	std::string sOutputConfig = jsonWriter.write(m_tUserDefaultData);
	std::string sOutPath = THFileUtil::getWriteablePath();
	sOutPath.append(m_sDefaultFileName.c_str());
	bool bIsWrote = THFileUtil::writeToFile(sOutPath.c_str(), sOutputConfig.c_str(), sOutputConfig.length());
	if(bIsWrote)
	{
		m_bIsChanged = false;
		return true;
	}
	
	return false;
}