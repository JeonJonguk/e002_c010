//
//  THUserDefault.h
//  Think
//
//  Created by pureye4u BX on 12. 7. 16..
//  Copyright CJ Educations 2012. All rights reserved.
//

#ifndef Think_THUserDefault_h
#define Think_THUserDefault_h

#include "../Support/json/value.h"
#include <string>

class THUserDefault
{
public:
	static THUserDefault *getCurrentUserDefault();
	
	THUserDefault();
	virtual ~THUserDefault();
	
	virtual bool init();
	virtual bool initWithFile(const char *pszFileName);
	
	virtual bool hasValueForKey(const char *pszKey);
	
	virtual std::string getStringForKey(const char *pszKey);
	virtual void setStringForKey(const char *pszKey, const char *pszValue, bool bWithSave = false);
	
	virtual bool getBoolForKey(const char *pszKey);
	virtual void setBoolForKey(const char *pszKey, bool bValue, bool bWithSave = false);
	
	virtual int getIntegerForKey(const char *pszKey);
	virtual void setIntegerForKey(const char *pszKey, int iValue, bool bWithSave = false);
	
	virtual double getDoubleForKey(const char *pszKey);
	virtual void setDoubleForKey(const char *pszKey, double dValue, bool bWithSave = false);
	
	virtual unsigned int getUnsignedIntegerForKey(const char *pszKey);
	virtual void setUnsignedIntegerForKey(const char *pszKey, unsigned int uiValue, bool bWithSave = false);
	
private:
	
	Json::Value m_tUserDefaultData;
	std::string m_sDefaultFileName;
	
	bool m_bIsChanged;
	
	virtual bool save();
	virtual bool load();
	
};

#endif
