//
//  THLocalizer.h
//  Think
//
//  Created by pureye4u BX on 12. 7. 18..
//  Copyright CJ Educations 2012. All rights reserved.
//

#ifndef Think_THLocalizer_h
#define Think_THLocalizer_h

#include "../Support/json/value.h"
#include <string>

class THLocalizer
{
public:
	static void destroy();
	static THLocalizer *getCurrentLocalizer();
	
	THLocalizer();
	virtual ~THLocalizer();
	
	virtual bool init();
	virtual bool load();
	virtual bool hasStringForKey(const char *key);
	virtual std::string getStringForKey(const char *key);
	virtual std::string withLocaleString(const char *input);
	virtual std::string getLanguageCode();
	virtual bool setLanguageCode(const char *code);
	virtual void setLocaleFromSystemLanguage();
	
protected:
	Json::Value m_tLocalizeData;
	
};

#endif
