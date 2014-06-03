//
//  THDevice.h
//  Think
//
//  Created by pureye4u BX on 12. 8. 22..
//  Copyright CJ Educations 2012. All rights reserved.
//

#ifndef Think_THDevice_h
#define Think_THDevice_h

class THDevice
{
public:
	
	// Informations
	static const char *getSystemVersion();
	static bool getIsDebug();
	static const char *getUUID();
	
	// File path
	static const char *getResourceDirectory();
	static const char *getApplicationCacheDirectory();
	static const char *getDocumentDirectory();
	static const char *getTempDirectory();
	
	// Storage
	static long long getFreeSpace();
	
	// Network connection
	static bool getIsNetworkConnected();
    static int  getWifiStrength();
	
	// Navigate to URL by web browser
	static void navigateToURL(const char *URL);
	
	// Only for ios
	static bool getIsSimulator();
	static bool addSkipBackupAttributeToItemAtPath(const char *path);
	static bool addSkipBackupAttributeToItemAtURL(const char *destination);
	
};

#endif
