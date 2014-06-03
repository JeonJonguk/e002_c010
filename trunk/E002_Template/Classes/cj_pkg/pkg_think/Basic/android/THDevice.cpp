

#include "THDevice.h"
#include "THFileUtil.h"
#include "THUserDefault.h"
#include "cocos2d.h"
#include <sys/stat.h>
#include <string>

#include "CJLMSExtension.h"

using namespace LMSExtension;

static const bool DEBUGMODE = true;

static std::string s_deviceOS = "";

const char *THDevice::getSystemVersion()
{
	if(s_deviceOS.empty())
	{
		s_deviceOS = "todo__detect_os_information";
	}
	
	return s_deviceOS.c_str();
}

bool THDevice::getIsDebug()
{
	return DEBUGMODE;
}

// Return device token; Create UUID once and save to local file. It can be same ID until application removed from the device.
const char *THDevice::getUUID()
{
	std::string uuidString;
	if(THUserDefault::getCurrentUserDefault()->hasValueForKey("TH_uuid"))
	{
		uuidString = THUserDefault::getCurrentUserDefault()->getStringForKey("TH_uuid");
	}
	else
	{
		uuidString = "todo__create_uuid";
		
		THUserDefault::getCurrentUserDefault()->setStringForKey("TH_uuid", uuidString.c_str(), true);
	}
	
	return uuidString.c_str();
}

using namespace cocos2d;

const char *THDevice::getResourceDirectory()
{
	return cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename("/").c_str();
}

const char *THDevice::getApplicationCacheDirectory()
{
	std::string sPath = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath();
	sPath.append("cache/");
	if(!THFileUtil::existFile(sPath.c_str()))
	{
		mkdir(sPath.c_str(), 0777);
	}
	return sPath.c_str();
}

const char *THDevice::getDocumentDirectory()
{
	std::string sPath = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath();
	sPath.append("documents/");
	if(!THFileUtil::existFile(sPath.c_str()))
	{
		mkdir(sPath.c_str(), 0777);
	}
	return sPath.c_str();
}

const char *THDevice::getTempDirectory()
{
	std::string sPath = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath();
	sPath.append("temp/");
	if(!THFileUtil::existFile(sPath.c_str()))
	{
		mkdir(sPath.c_str(), 0777);
	}
	return sPath.c_str();
}

long long THDevice::getFreeSpace()
{
	// Todo get free space
    long long ret = CJLMSExtension::sharedInstance()->getFreeSpace();
//    cocos2d::CCLog("free space : %lld, %lli", ret, ret);
	return ret;
}

// Return device is connected in network
bool THDevice::getIsNetworkConnected()
{
	// Todo get is network connected
    bool ret = CJLMSExtension::sharedInstance()->getNetworkState();
//    cocos2d::CCLog("available network : %d", ret);
	return ret;
}

int THDevice::getWifiStrength()
{
    return LMSExtension::CJLMSExtension::sharedInstance()->getWifiStrength();
}

void THDevice::navigateToURL(const char *URL)
{
	// Todo navigate url with browser
}

bool THDevice::getIsSimulator()
{
	return false;
}

bool THDevice::addSkipBackupAttributeToItemAtPath(const char *path)
{
	return true;
}

bool THDevice::addSkipBackupAttributeToItemAtURL(const char *destination)
{
	return true;
}
