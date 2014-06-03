//
//  THResourceUtils.h
//  Think
//
//  Created by pureye4u BX on 12. 6. 13..
//  Copyright CJ Educations 2012. All rights reserved.
//

#ifndef Think_THResourceUtils_h
#define Think_THResourceUtils_h

#include "THDownloadDelegate.h"
#include "cocos2d.h"
#include "../Support/json/json.h"

// Structures

// Content data structure
typedef struct THPackageAppContentData
{
	int ID;
	std::string no;
	std::string versionString;
	int version;
	int sequence;
    std::string name; 
	int reads;
	std::string price;
	bool embeded;
	bool paid;
	std::string productID;
//#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	std::string resourceDir;
//#endif
}THPackageAppContentData;

// Group structure
// For split by level tabs
typedef struct THPackageAppGroupData
{
	int ID;
	int sequence;
	std::string tabImageNormal;
	std::string tabImageSelected;
	std::string titleImage;
	std::string promotionImage;
	std::vector<std::string> mainImages;
	std::vector<THPackageAppContentData> contents;
}THPackageAppGroupData;

// Root data
typedef struct THPackageAppData
{
	int ID;
	std::string bundleID;
	int version;
	std::string versionString;
    std::string name;
    std::string title;
	std::string description;
	std::vector<THPackageAppGroupData> groups;
}THPackageAppData;

// Download info
// Load information like filename, url, size ... before the download.
typedef struct THDownloadInfo
{
	int status;
	long fileSize;
	std::string fileName;
	std::string url;
	std::string description;
}THDownloadInfo;

// Download state
typedef enum
{
	THDownloadStateNone,
	THDownloadStateReady,
	THDownloadStateProgress,
	THDownloadStateExtract,
	THDownloadStatePause,
}THDownloadState;

class THResourceUtils : public cocos2d::CCObject, THDownloadDelegate
{
public:
	// Class const
	static const int CONTENT_STATUS_NONE = 0;
	static const int CONTENT_STATUS_PURCHASED = 1;
	static const int CONTENT_STATUS_DOWNLOADED = 2;
	
	static const int CONTENT_STATUS_KEY_PURCHASED = 1;
	static const int CONTENT_STATUS_KEY_DOWNLOADED = 2;
	
	// Class methods
	static THResourceUtils *getCurrentUtils();
	static void destroy();
	static bool getHasResource(int appID, int appVer, int contentID, int contentVer);
	static const char *getResourceDirectory(int appID, int appVer, int contentID, int contentVer);
	static const char *getResourceDirectory(int appID, int appVer, int contentID, int contentVer, std::string resourceDir);
	static const char *getResourceDirectory(int appID, int appVer, int contentID);
	static const char *getResourcePath(int appID, int appVer, int contentID, int contentVer);
	static const char *getResourcePath(int appID, int appVer, int contentID, int contentVer, std::string resourceDir);
	static const char *getResourcePath(int appID, int appVer, int contentID);
	
	static void *runGetDownloadInfo(void *);

	// Member methods
	// Initializer
	THResourceUtils();
	~THResourceUtils();
	
	virtual bool init();
	virtual bool initWithFilePath(const char *filePath);
	
	// Getter & Setter
	virtual THDownloadDelegate *getDelegate();
	virtual void setDelegate(THDownloadDelegate *delegate);
	
//	virtual int getAppID();
//	virtual int getAppVersion();
	virtual THPackageAppData getData();
	virtual std::vector<THPackageAppContentData> getContentDataBySeq(int groupID = 0);
	virtual THPackageAppContentData getDownloadingContentData();
	virtual THPackageAppGroupData getCurrentGroupData();
	virtual int getCurrentContentVersion(int contentID);
	
	virtual bool getHasResourceForContent(int contentID, int contentVer = 0);
	virtual const char *getResourcePath(int contentID, int contentVer = 0);

	virtual bool removeContent(int contentID);
	virtual bool getIsDownloading(int contentID);
	virtual bool getHasDownloading();
	virtual int getDownloadingContentID();
	virtual void setDefaultContent(int contentID, int contentVer = 0);
//	virtual void setDefaultGroup(int groupIndex);
	virtual const char *getDefaultResourcePath();
	virtual int getGroupIndexForContentID(int contentID);
	virtual int getContentStatusFromCurrentContent();
	virtual int getContentStatusFromContentID(int contentID, int contentVersion);
	virtual bool getPurchasedStatusValueFromCurrentContent();
	virtual bool getDownloadedStatusValueFromCurrentContent();
	//shchoi add
	virtual std::string getResDirFromContentID(int contentID, int contentVersion);

	virtual bool getStatusValueFromCurrentContent(int status);
	virtual bool getStatusValueFromContentID(int contentID, int contentVersion, int status);
	virtual bool setStatusValueFromCurrentContent(int status, bool value);
	virtual bool setStatusValueFromContentID(int contentID, int contentVersion, int status, bool value);
	virtual bool setPurchasedStatusValueFromProductID(const char *productID);

    virtual int  getStatusVersionFromContentID(int contentID);
    virtual bool setStatusVersionFromContentID(int contentID, int contentVersion);
    
	virtual std::vector<std::string> getAllProductID();
	virtual std::string getCurrentLanguageCode();
	
	// Actions
	virtual void startDownloadUsingThread(int contentID, int contentVer = 0);
	virtual void startDownload(int contentID, int contentVer = 0);
	virtual void stopDownload(int contentID);
	virtual void pause();
	virtual void resume();
	
	// Delegate methods
	virtual void begin();
	virtual void setStatus(int type);
	virtual void setProgress(double current);
	virtual void end();
	virtual void error(int type, const char *description);
	
	
	virtual void hndUpdateProgress();
	
private:
	// Private members
	THDownloadDelegate *m_delegate;
	int m_currentGroupIndex;
	int m_currentContentID;
	int m_currentContentVersion;
	//shchoi add
	std::string m_currentResourceDir;
	std::string m_currentDownloadFileName;
	std::string m_currentDownloadURL;
	std::string m_currentDownloadPath;
	long m_currentDownloadSize;
	int m_downloadState;
	double m_currentProgress;
	std::vector<std::string> m_allProductID;
	
	int m_currentErrorType;
	int m_currentDownloadStatus;
	std::string m_currentErrorDescription;
	THPackageAppData m_data;
	//shchoi, move to Here!
	THPackageAppContentData contentData;

	Json::Value m_statusData;
	
	std::string m_currentLanguagCode;
	
	std::string m_authKey;
	std::string m_url;
	std::string m_userAgent;
	std::string m_transactionId;
	std::string m_interfaceId;
	std::string m_interfaceVer;
	std::string m_requestTime;

	// Private class methods
	static size_t writeString(void *contents, size_t size, size_t nmemb, void *userp);
	
	// Private member methods
	std::string loadDownloadInfo(int contentID, int contentVer);
	THDownloadInfo parseDownloadInfo(const char *downloadInfo);
	virtual int indexOfContentIDFromProductID(const char *productID);
	bool loadStatusData();
	bool updateStatusData();
	
	virtual void hndDownloadEnded();
	virtual void hndDownloadError();
	virtual void hndStatusUpdated();
	
	virtual void checkDownloadInfoThread();
	virtual void completeGetDownloadInfo(const char *pszDownloadInfo);
	
};

#endif
