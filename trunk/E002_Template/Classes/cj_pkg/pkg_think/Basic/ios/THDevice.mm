//
//  THDevice.cpp
//  Think
//
//  Created by pureye4u BX on 12. 8. 22..
//  Copyright CJ Educations 2012. All rights reserved.
//

#include "THDevice.h"
#include "THUserDefault.h"
#include "THFileUtil.h"
#include "THStringUtil.h"
#include "CJLMSExtension.h"
#include <string>
#include <sys/stat.h>
#include <netinet/in.h>
#include <SystemConfiguration/SCNetworkReachability.h>
#include <uuid/uuid.h>
#include <sys/xattr.h>

static const bool DEBUGMODE = true;

static std::string s_deviceOS = "";

const char *THDevice::getSystemVersion()
{
	if(s_deviceOS.empty())
	{
		NSString *deviceOS = [[UIDevice currentDevice] systemVersion];
		s_deviceOS = [deviceOS cStringUsingEncoding:NSUTF8StringEncoding];
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
		uuid_t uuid;
		uuid_generate_random(uuid);
		char s[37];
		uuid_unparse(uuid, s);
		uuidString = s;
		
		THUserDefault::getCurrentUserDefault()->setStringForKey("TH_uuid", uuidString.c_str(), true);
	}
	
	return uuidString.c_str();
}

const char *THDevice::getResourceDirectory()
{
	NSString *path = [[NSBundle mainBundle] resourcePath];
	path = [path stringByAppendingString:@"/"];
	
	return [path cStringUsingEncoding:NSUTF8StringEncoding];
}

const char *THDevice::getApplicationCacheDirectory()
{
	NSString *path = [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) objectAtIndex:0];
	path = [path stringByAppendingString:@"/"];
	
	return [path cStringUsingEncoding:NSUTF8StringEncoding];
}

const char *THDevice::getDocumentDirectory()
{
	NSString *path = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
	path = [path stringByAppendingString:@"/"];
	
	return [path cStringUsingEncoding:NSUTF8StringEncoding];
}

const char *THDevice::getTempDirectory()
{
	NSString *path = NSTemporaryDirectory();
	
	return [path cStringUsingEncoding:NSUTF8StringEncoding];
}

long long THDevice::getFreeSpace()
{
	return [[[[NSFileManager defaultManager] attributesOfFileSystemForPath:NSHomeDirectory() error:NULL] objectForKey:NSFileSystemFreeSize] longLongValue];
}

// Return device is connected in network
bool THDevice::getIsNetworkConnected()
{
	struct sockaddr_in zeroAddress;
	bzero(&zeroAddress, sizeof(zeroAddress));
	zeroAddress.sin_len = sizeof(zeroAddress);
	zeroAddress.sin_family = AF_INET;
	
	SCNetworkReachabilityRef defaultRouteReachability = SCNetworkReachabilityCreateWithAddress(NULL, (struct sockaddr *)&zeroAddress);
	SCNetworkReachabilityFlags flags;
	bool didRetrieveFlags = SCNetworkReachabilityGetFlags(defaultRouteReachability, &flags);
	CFRelease(defaultRouteReachability);
	if(!didRetrieveFlags)
	{
		return false;
	}
	
	bool isReachable = flags & kSCNetworkFlagsReachable;
	bool needsConnection = flags & kSCNetworkFlagsConnectionRequired;
	
	return (isReachable && !needsConnection);
}

int THDevice::getWifiStrength()
{
    return LMSExtension::CJLMSExtension::sharedInstance()->getWifiStrength();
}

void THDevice::navigateToURL(const char *URL)
{
	[[UIApplication sharedApplication] openURL:[NSURL URLWithString:[NSString stringWithCString:URL encoding:NSUTF8StringEncoding]]];
}

bool THDevice::getIsSimulator()
{
	return [[[[UIDevice currentDevice] model] lowercaseString] rangeOfString:@"simulator"].location != NSNotFound;
}

bool THDevice::addSkipBackupAttributeToItemAtPath(const char *path)
{
	// Add skip backup attribute to item at URL
	NSString *verString = [NSString stringWithCString:THDevice::getSystemVersion() encoding:NSUTF8StringEncoding];
	NSNumberFormatter *formatter = [[NSNumberFormatter alloc] init];
	[formatter setNumberStyle:NSNumberFormatterDecimalStyle];
	NSNumber *verNum = [formatter numberFromString:verString];
	
	//	NSLog(@"%f", [verNum floatValue]);
	
	if([verNum floatValue] > 5.0f)
	{
		assert(THFileUtil::existFile(path));
		
		const char *attrName = "com.apple.MobileBackup";
		u_int8_t attrValue = 1;
		
		int result = setxattr(path, attrName, &attrValue, sizeof(attrValue), 0, 0);
		if(result != 0)
		{
			printf("Could not ad skip backup attribute to item at URL\n");
			return false;
		}
		return true;
	}
	
	return true;
}

bool THDevice::addSkipBackupAttributeToItemAtURL(const char *destination)
{
	// Add skip backup attribute to item at URL
	NSString *URLString = [NSString stringWithCString:destination encoding:NSUTF8StringEncoding];
	NSString *path = [NSString stringWithFormat:@"%@/%@", [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject], URLString];
	NSURL *URL = [NSURL fileURLWithPath:path];
	
	std::vector<std::string> reversions = THStringUtil::split(THDevice::getSystemVersion(), '.');
	int majorVer = 0;
	int minorVer = 0;
	int maintenanceVer = 0;
	
	if(reversions.size() > 0)
	{
		majorVer = std::atof(reversions[0].c_str());
	}
	if(reversions.size() > 1)
	{
		minorVer = std::atof(reversions[1].c_str());
	}
	if(reversions.size() > 2)
	{
		maintenanceVer = std::atof(reversions[2].c_str());
	}
	
	if(majorVer >= 5)
	{
		if(minorVer >= 1)
		{
			assert([[NSFileManager defaultManager] fileExistsAtPath:[URL path]]);
			
			NSError *error = nil;
			BOOL success = [URL setResourceValue:[NSNumber numberWithBool:YES] forKey:NSURLIsExcludedFromBackupKey error:&error];
			
			if(!success)
			{
				NSLog(@"Error excludeung %@ from backup %@", [URL lastPathComponent], error);
				return false;
			}
			
			return true;
		}
		else
		{
			if(maintenanceVer >= 1)
			{
				assert([[NSFileManager defaultManager] fileExistsAtPath:[URL path]]);
				
				const char *filePath = [[URL path] fileSystemRepresentation];
				const char *attrName = "com.apple.MobileBackup";
				u_int8_t attrValue = 1;
				
				int result = setxattr(filePath, attrName, &attrValue, sizeof(attrValue), 0, 0);
				if(result != 0)
				{
					printf("Could not ad skip backup attribute to item at URL\n");
					return false;
				}
				return true;
			}
		}
	}
	
	return true;
}