//
//  THResourceUtils.cpp
//  Think
//
//  Created by pureye4u BX on 12. 6. 13..
//  Copyright CJ Educations 2012. All rights reserved.
//

#include "THResourceUtils.h"
#include "THDownloadThread.h"
#include "THDownloadStatus.h"
#include "../Basic/THStringUtil.h"
#include "../Basic/THUserDefault.h"
#include "../Basic/THFileUtil.h"
#include "../Basic/THDevice.h"
#include "../Basic/THLocalizer.h"

#include "../Support/json/value.h"
#include <stdio.h>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <curl/curl.h>
#else
#include "platform/third_party/android/prebuilt/libcurl/include/curl/curl.h"
#endif

#include "CJLMSExtension.h"

using namespace LMSExtension;

const char *RESOURCE_FILE_DATA_PATH =							"pkg_common/json";
const char *RESOURCE_FILE_IMAGE_PATH =							"PKG/img/main";
const char *RESOURCE_FILE_NAME =								"resourceinfo";
const char *RESOURCE_FILE_KEY_FOR_APP_ID =						"appID";
const char *RESOURCE_FILE_KEY_FOR_APP_BUNDLE_ID =				"appBundleID";
const char *RESOURCE_FILE_KEY_FOR_APP_VERSION =					"appVersion";
const char *RESOURCE_FILE_KEY_FOR_APP_VERSION_STRING =			"appVersionString";
const char *RESOURCE_FILE_KEY_FOR_APP_NAME =					"appName";
const char *RESOURCE_FILE_KEY_FOR_APP_TITLE =					"appTitle";
const char *RESOURCE_FILE_KEY_FOR_APP_DESC =					"appDescription";

const char *RESOURCE_FILE_KEY_FOR_APP_GROUPS =					"appGroups";
const char *RESOURCE_FILE_KEY_FOR_GRP_ID =						"groupID";
const char *RESOURCE_FILE_KEY_FOR_GRP_SEQUENCE =				"groupSequence";
const char *RESOURCE_FILE_KEY_FOR_GRP_TAB_IMAGE_NORMAL =		"groupTabImageNormal";
const char *RESOURCE_FILE_KEY_FOR_GRP_TAB_IMAGE_SELECTED =		"groupTabImageSelected";
const char *RESOURCE_FILE_KEY_FOR_GRP_CONTENTS =				"groupContents";
const char *RESOURCE_FILE_KEY_FOR_CONTENT_ID =					"contentID";
const char *RESOURCE_FILE_KEY_FOR_CONTENT_NO =					"contentNo";
const char *RESOURCE_FILE_KEY_FOR_CONTENT_VERSION =				"contentVersion";
const char *RESOURCE_FILE_KEY_FOR_CONTENT_VERSION_STRING =		"contentVersionString";
const char *RESOURCE_FILE_KEY_FOR_CONTENT_SEQUENCE =			"contentSequence";
const char *RESOURCE_FILE_KEY_FOR_CONTENT_NAME =				"contentName";
const char *RESOURCE_FILE_KEY_FOR_CONTENT_RES_DIR =				"contentDirectory";
const char *RESOURCE_FILE_KEY_FOR_CONTENT_EMBEDED =				"contentEmbeded";
const char *RESOURCE_FILE_KEY_FOR_CONTENT_PAID =				"contentPaid";
const char *RESOURCE_FILE_KEY_FOR_CONTENT_PURCHASED =			"contentPurchased";
const char *RESOURCE_FILE_KEY_FOR_CONTENT_DOWNLOADED =			"contentDownloaded";
const char *RESOURCE_FILE_KEY_FOR_CONTENT_PRODUCT_ID =			"contentProductID";
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
const char *RESOURCE_FILE_KEY_FOR_CONTENT_RESOURCE_DIRECTORY =	"contentDirectory";
#endif

const char *RESOURCE_DIRECTORY_NAME_ROOT =						"ResourceUtils";
const char *RESOURCE_DIRECTORY_NAME_APP_SEPARATOR =				"A";
const char *RESOURCE_DIRECTORY_NAME_CONTENT_SEPARATOR =			"C";
const char *RESOURCE_DIRECTORY_NAME_VERSION_SEPARATOR =			"_";
const char *RESOURCE_DOWNLOAD_PROTOCOL =						"http://";
const char *RESOURCE_DOWNLOAD_HOST =							"dev-mps.thinkle.net:10100";
const char *RESOURCE_DOWNLOAD_URI =								"/TGW/IS/mobileInterface/IF-TGW-IS-THINKLE-007";

const char *RESOURCE_STATUS_FILE_NAME =							"downloadstatus";

static int t_contentID;
static int t_contentVer;
static std::string t_downloadInfoBuffer;
static int t_downloadInfoFlag = 0;

enum
{
	kDownloadInfoStatusNone,
	kDownloadInfoStatusSuccess,
	kDownloadInfoStatusError,
};

using namespace cocos2d;

////////// Class properties

// Static download thread
static THDownloadThread *s_downloadThread = NULL;

// Singleton shared current util
static THResourceUtils *s_currentResourceUtils = NULL;



////////// Class methods

// Shared current util getter
THResourceUtils *THResourceUtils::getCurrentUtils()
{
	// If there is no instance
	if(s_currentResourceUtils == NULL)
	{
		// Create new one
		s_currentResourceUtils = new THResourceUtils();
		s_currentResourceUtils->init();
	}

	return s_currentResourceUtils;
}

void THResourceUtils::destroy()
{
	if(s_currentResourceUtils != NULL)
	{
		s_currentResourceUtils->release();
		s_currentResourceUtils = NULL;
	}
}

// Return resource availablity for content and version
bool THResourceUtils::getHasResource(int appID, int appVer, int contentID, int contentVer)
{
	std::string path = THStringUtil::format("%s%s", THFileUtil::getWriteablePath(), THResourceUtils::getResourceDirectory(appID, appVer, contentID, contentVer));
	return THFileUtil::existFile(path.c_str());
}

// Return resource directory hierarchy for content and version
const char *THResourceUtils::getResourceDirectory(int appID, int appVer, int contentID, int contentVer)
{
    THPackageAppGroupData group = THResourceUtils::getCurrentUtils()->getCurrentGroupData();
    std::vector<THPackageAppContentData> datas = group.contents;
    
    std::string strResDir = "";
    for(int i=0; i<datas.size(); i++)
    {
        if(contentID == datas.at(i).ID)
        {
            strResDir = datas.at(i).resourceDir;
            break;
        }
    }
    
    return strResDir.c_str();
}

//shchoi, add for Android resource folder
const char *THResourceUtils::getResourceDirectory(int appID, int appVer, int contentID, int contentVer, std::string resourceDir)
{
	return resourceDir.c_str();
}


const char *THResourceUtils::getResourceDirectory(int appID, int appVer, int contentID)
{
	std::string path = THStringUtil::format("%s/%s%d/%s%d", RESOURCE_DIRECTORY_NAME_ROOT, RESOURCE_DIRECTORY_NAME_APP_SEPARATOR, appID, RESOURCE_DIRECTORY_NAME_CONTENT_SEPARATOR, contentID);
	return path.c_str();
}

// Return full resource directory path for content and version
const char *THResourceUtils::getResourcePath(int appID, int appVer, int contentID, int contentVer)
{
	std::string path = THStringUtil::format("%s%s", THFileUtil::getWriteablePath(), THResourceUtils::getResourceDirectory(appID, appVer, contentID, contentVer));
	if(THFileUtil::existFile(path.c_str()))
	{
		return path.c_str();
	}
	return NULL;
}

// Return full resource directory path for content and version, shchoi add for Android
const char *THResourceUtils::getResourcePath(int appID, int appVer, int contentID, int contentVer, std::string resourceDir)
{
	std::string path = THStringUtil::format("%s%s", THFileUtil::getWriteablePath(), THResourceUtils::getResourceDirectory(appID, appVer, contentID, contentVer, resourceDir));
	if(THFileUtil::existFile(path.c_str()))
	{
		return path.c_str();
	}
	return NULL;
}

// Return full resource directory path for content
const char *THResourceUtils::getResourcePath(int appID, int appVer, int contentID)
{
	std::string path = THStringUtil::format("%s%s", THFileUtil::getWriteablePath(), THResourceUtils::getResourceDirectory(appID, appVer, contentID));

	if(THFileUtil::existFile(path.c_str()))
	{
		return path.c_str();
	}
	return NULL;
}

// Write string static method for CURL get downloadInfo JSON
size_t THResourceUtils::writeString(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string *)userp)->append((char *)contents, size *nmemb);
	return size *nmemb;
}

////////// Member methods

THResourceUtils::THResourceUtils()
{

}

THResourceUtils::~THResourceUtils()
{
	m_allProductID.clear();
	m_statusData.clear();
}

// Initializer
bool THResourceUtils::init()
{
	m_currentDownloadStatus = THDownloadStatusNone;
	m_currentLanguagCode = THLocalizer::getCurrentLocalizer()->getLanguageCode();

	std::string defaultFileName = THStringUtil::format("%s/%s.json", RESOURCE_FILE_DATA_PATH, RESOURCE_FILE_NAME);
	defaultFileName = THLocalizer::getCurrentLocalizer()->withLocaleString(defaultFileName.c_str());
    
    /*
     * cocos2dx v2.1.4 deplicated CCFileUtils::fullPathFromRelativePath()
     * CCFileUtils::fullPathFromRelativePath() is not thread-safe, it use autorelease().
     *
     * std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(defaultFileName.c_str());
     */
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(defaultFileName.c_str());

	return this->initWithFilePath(fullPath.c_str());
}

// Initializer with plist file path
bool THResourceUtils::initWithFilePath(const char *filePath)
{
	// Initialize properties
	m_currentGroupIndex = -1;
	m_currentContentID = -1;
	m_currentContentVersion = -1;
	m_currentDownloadFileName = "";
	m_currentDownloadURL = "";
	m_currentDownloadPath = "";
	m_downloadState = THDownloadStateNone;
	m_allProductID = std::vector<std::string>();

	// Check download status file
	bool hasStatusFile = this->loadStatusData();

	// Read resourceInfo JSON
	unsigned long nSize = 0;
	unsigned char* pBuffer =
			cocos2d::CCFileUtils::sharedFileUtils()->getFileData(
					filePath,
					"rb",
					&nSize
			);
	std::string resourceInfo(reinterpret_cast<const char *>(pBuffer), nSize);

    // Add LeeYJ, Memory leak.
    CC_SAFE_DELETE_ARRAY(pBuffer);
    
	// Parse JSON
	Json::Reader jsonReader;
	Json::Value resourceInfoJson;
	bool bParseingSuccessful = jsonReader.parse(resourceInfo, resourceInfoJson);
	if(!bParseingSuccessful)
	{
//		CCLog("Error: Cannot parse JSON \"%s\"", resourceInfo.c_str());
		return false;
	}

	std::string key;
	std::string temp;
	int l;

	// Get "appID" object
	key = RESOURCE_FILE_KEY_FOR_APP_ID;
	if(!resourceInfoJson.isMember(key))
	{
//		CCLog("%s JSON does not have a %s element", filePath, key.c_str());
		return false;
	}
	m_data.ID = resourceInfoJson.get(key, "UTF-8").asInt();

	// Get "appBundleID" object
	key = RESOURCE_FILE_KEY_FOR_APP_BUNDLE_ID;
	if(!resourceInfoJson.isMember(key))
	{
//		CCLog("%s JSON does not have a %s element", filePath, key.c_str());
		return false;
	}
	m_data.bundleID = resourceInfoJson.get(key, "UTF-8").asString();

	// Get "appVersion" object
	key = RESOURCE_FILE_KEY_FOR_APP_VERSION;
	if(!resourceInfoJson.isMember(key))
	{
//		CCLog("%s JSON does not have a %s element", filePath, key.c_str());
		return false;
	}
	m_data.version = resourceInfoJson.get(key, "UTF-8").asInt();

	// Get "appVersionString" object
	key = RESOURCE_FILE_KEY_FOR_APP_VERSION_STRING;
	if(!resourceInfoJson.isMember(key))
	{
//		CCLog("%s JSON does not have a %s element", filePath, key.c_str());
		return false;
	}
	m_data.versionString = resourceInfoJson.get(key, "UTF-8").asString();
    
    // Get "appName" object
	key = RESOURCE_FILE_KEY_FOR_APP_NAME;
	if(!resourceInfoJson.isMember(key))
	{
//		CCLog("%s JSON does not have a %s element", filePath, key.c_str());
		return false;
	}
	m_data.name = resourceInfoJson.get(key, "UTF-8").asString();
    
    // Get "appTitle" object
	key = RESOURCE_FILE_KEY_FOR_APP_TITLE;
	if(!resourceInfoJson.isMember(key))
	{
//		CCLog("%s JSON does not have a %s element", filePath, key.c_str());
		return false;
	}
	m_data.title = resourceInfoJson.get(key, "UTF-8").asString();
	
	// Get "appDescription" object
	key = RESOURCE_FILE_KEY_FOR_APP_DESC;
	if(!resourceInfoJson.isMember(key))
	{
//		CCLog("%s JSON does not have a %s element", filePath, key.c_str());
		return false;
	}
	m_data.description = resourceInfoJson.get(key, "UTF-8").asString();

	// Get "appGroups" array
	key = RESOURCE_FILE_KEY_FOR_APP_GROUPS;
	if(!resourceInfoJson.isMember(key))
	{
//		CCLog("%s JSON does not have a %s element", filePath, key.c_str());
		return false;
	}

	Json::Value groupsJson = resourceInfoJson.get(key, "UTF-8");
	if(!groupsJson)
	{
//		CCLog("Parse error: %s is null", key.c_str());
		return false;
	}

	l = groupsJson.size();

	if(l)
	{
		if(!hasStatusFile)
		{
			//			Json::Value statusContents(Json::arrayValue);
			m_statusData["contents"] = Json::Value(Json::arrayValue);
		}

		for(int i = 0; i < l; i++)
		{
			// Group data
			THPackageAppGroupData groupData;

			// Get "groupID" object
			key = RESOURCE_FILE_KEY_FOR_GRP_ID;
			if(groupsJson[i].isMember(key))
			{
				groupData.ID = groupsJson[i].get(key, "UTF-8").asInt();
			}
			else
			{
//				CCLog("%s JSON group[%d] does not have a %s element", filePath, i, key.c_str());
			}

			// Get "groupSequence" object
			key = RESOURCE_FILE_KEY_FOR_GRP_SEQUENCE;
			if(groupsJson[i].isMember(key))
			{
				groupData.sequence = groupsJson[i].get(key, "UTF-8").asInt();
			}
			else
			{
//				CCLog("%s JSON group[%d] does not have a %s element", filePath, i, key.c_str());
			}

			// Get "groupTabImageNormal" object
			key = RESOURCE_FILE_KEY_FOR_GRP_TAB_IMAGE_NORMAL;
			if(groupsJson[i].isMember(key))
			{
				temp = groupsJson[i].get(key, "UTF-8").asString();
				groupData.tabImageNormal = temp.empty() ? temp : THStringUtil::format("%s/%s", RESOURCE_FILE_IMAGE_PATH, temp.c_str());
				//				groupData.tabImageNormal = groupsJson[i].get(key, "UTF-8").asString();
			}
			else
			{
//				CCLog("%s JSON group[%d] does not have a %s element", filePath, i, key.c_str());
			}

			// Get "groupTabImageSelected" object
			key = RESOURCE_FILE_KEY_FOR_GRP_TAB_IMAGE_SELECTED;
			if(groupsJson[i].isMember(key))
			{
				temp = groupsJson[i].get(key, "UTF-8").asString();
				groupData.tabImageSelected = temp.empty() ? temp : THStringUtil::format("%s/%s", RESOURCE_FILE_IMAGE_PATH, temp.c_str());
				//				groupData.tabImageSelected = groupsJson[i].get(key, "UTF-8").asString();
			}
			else
			{
//				CCLog("%s JSON group[%d] does not have a %s element", filePath, i, key.c_str());
			}

			// Get "groupContents" array
			key = RESOURCE_FILE_KEY_FOR_GRP_CONTENTS;
			if(groupsJson[i].isMember(key))
			{
				Json::Value groupContentsJson = groupsJson[i].get(key, "UTF-8");
				if(!!groupContentsJson)
				{
					int m = groupContentsJson.size();

					if(m)
					{
						for(int j = 0; j < m; j++)
						{
							// Content data
							//							THPackageAppContentData contentData;
							Json::Value statusContent;

							// Status json
							if(!hasStatusFile)
							{
								statusContent = Json::Value();
							}

							// Get "contentID" object
							key = RESOURCE_FILE_KEY_FOR_CONTENT_ID;
							if(groupContentsJson[j].isMember(key))
							{
								contentData.ID = groupContentsJson[j].get(key, "UTF-8").asInt();
								if(!hasStatusFile)
								{
									statusContent[key] = contentData.ID;
								}
							}
							else
							{
//								CCLog("%s JSON group[%d]->content[%d] does not have a %s element", filePath, i, j, key.c_str());
							}

							// Get "contentNo" object
							key = RESOURCE_FILE_KEY_FOR_CONTENT_NO;
							if(groupContentsJson[j].isMember(key))
							{
								contentData.no = groupContentsJson[j].get(key, "UTF-8").asString();
							}
							else
							{
//								CCLog("%s JSON group[%d]->content[%d] does not have a %s element", filePath, i, j, key.c_str());
							}

							// Get "contentVersionString" object
							key = RESOURCE_FILE_KEY_FOR_CONTENT_VERSION_STRING;
							if(groupContentsJson[j].isMember(key))
							{
								contentData.versionString = groupContentsJson[j].get(key, "UTF-8").asString();
							}
							else
							{
//								CCLog("%s JSON group[%d]->content[%d] does not have a %s element", filePath, i, j, key.c_str());
							}

							// Get "contentVersion" object
							key = RESOURCE_FILE_KEY_FOR_CONTENT_VERSION;
							if(groupContentsJson[j].isMember(key))
							{
								contentData.version = groupContentsJson[j].get(key, "UTF-8").asInt();
								if(!hasStatusFile)
								{
									statusContent[key] = contentData.version;
								}
							}
							else
							{
//								CCLog("%s JSON group[%d]->content[%d] does not have a %s element", filePath, i, j, key.c_str());
							}

							// Get "contentSequence" object
							key = RESOURCE_FILE_KEY_FOR_CONTENT_SEQUENCE;
							if(groupContentsJson[j].isMember(key))
							{
								contentData.sequence = groupContentsJson[j].get(key, "UTF-8").asInt();
								if(!hasStatusFile)
								{
									statusContent[key] = contentData.sequence;
								}
							}
							else
							{
//								CCLog("%s JSON group[%d]->content[%d] does not have a %s element", filePath, i, j, key.c_str());
							}
                            
                            // Get "contentName" object
							key = RESOURCE_FILE_KEY_FOR_CONTENT_NAME;
							if(groupContentsJson[j].isMember(key))
							{
								contentData.name = groupContentsJson[j].get(key, "UTF-8").asString();
							}
							else
							{
//								CCLog("%s JSON group[%d]->content[%d] does not have a %s element", filePath, i, j, key.c_str());
							}

							// Get "contentDirectory" object
							key = RESOURCE_FILE_KEY_FOR_CONTENT_RES_DIR;
							if(groupContentsJson[j].isMember(key))
							{
								contentData.resourceDir = groupContentsJson[j].get(key, "UTF-8").asString();
							}
							else
							{
//								CCLog("%s JSON group[%d]->content[%d] does not have a %s element", filePath, i, j, key.c_str());
							}

							// Get "contentEmbeded" object
							key = RESOURCE_FILE_KEY_FOR_CONTENT_EMBEDED;
							if(groupContentsJson[j].isMember(key))
							{
								contentData.embeded = groupContentsJson[j].get(key, "UTF-8").asBool();
								if(!hasStatusFile)
								{
									statusContent[key] = contentData.embeded;
									statusContent[RESOURCE_FILE_KEY_FOR_CONTENT_DOWNLOADED] = contentData.embeded;
								}
							}
							else
							{
//								CCLog("%s JSON group[%d]->content[%d] does not have a %s element", filePath, i, j, key.c_str());
							}

							// Get "contentPaid" object
							key = RESOURCE_FILE_KEY_FOR_CONTENT_PAID;
							if(groupContentsJson[j].isMember(key))
							{
								contentData.paid = groupContentsJson[j].get(key, "UTF-8").asBool();
								if(!hasStatusFile)
								{
									statusContent[key] = contentData.paid;

									if(contentData.paid)
									{
										int contentID = contentData.ID;
										int contentVer = contentData.version;
										std::string filePath = THFileUtil::getWriteablePath();
										std::string folderName = THResourceUtils::getCurrentUtils()->getResDirFromContentID(contentID, contentVer);
										filePath.append(folderName);
                                        filePath.append(contentData.resourceDir);
										filePath.append(".zip");

										//										filePath = CCFileUtils::fullPathFromRelativePath("PKG/h001_c010.zip");
                                        
//                                        CCLog("%s", filePath.c_str());

										if(THFileUtil::existFile(filePath.c_str()))
										{
											statusContent[RESOURCE_FILE_KEY_FOR_CONTENT_PURCHASED] = true;
										}
										else
										{
											statusContent[RESOURCE_FILE_KEY_FOR_CONTENT_PURCHASED] = false;
										}
									}
									else
									{
										statusContent[RESOURCE_FILE_KEY_FOR_CONTENT_PURCHASED] = true;
									}
								}
							}
							else
							{
//								CCLog("%s JSON group[%d]->content[%d] does not have a %s element", filePath, i, j, key.c_str());
							}

							// Get "contentProductID" object
							key = RESOURCE_FILE_KEY_FOR_CONTENT_PRODUCT_ID;
							if(groupContentsJson[j].isMember(key))
							{
								contentData.productID = groupContentsJson[j].get(key, "UTF-8").asString();
								m_allProductID.push_back(contentData.productID);
							}
							else
							{
//								CCLog("%s JSON group[%d]->content[%d] does not have a %s element", filePath, i, j, key.c_str());
							}

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
							// Get "contentDirectory" object
							key = RESOURCE_FILE_KEY_FOR_CONTENT_RESOURCE_DIRECTORY;
							if(groupContentsJson[j].isMember(key))
							{
								contentData.resourceDir = groupContentsJson[j].get(key, "UTF-8").asString();
								m_allProductID.push_back(contentData.resourceDir);
							}
							else
							{
//								CCLog("%s JSON group[%d]->content[%d] does not have a %s element", filePath, i, j, key.c_str());
							}
#endif

							m_statusData["contents"].append(statusContent);

							// Push content data
							groupData.contents.push_back(contentData);
						}
					}
					else
					{
//						CCLog("No group contents");
					}
				}
				else
				{
//					CCLog("Parse error: %s is null", key.c_str());
				}

			}
			else
			{
//				CCLog("%s JSON group[%d] does not have a %s element", filePath, i, key.c_str());
			}

			// Push group data
			m_data.groups.push_back(groupData);
		}
	}
	else
	{
//		CCLog("No groups");
	}

	//	CCLog("%s", m_statusData.toStyledString().c_str());
	if(!hasStatusFile)
	{
		this->updateStatusData();
	}

	m_currentGroupIndex = 0;
	m_downloadState = THDownloadStateReady;

	return true;
}

// Getter delegate
THDownloadDelegate *THResourceUtils::getDelegate()
{
	return m_delegate;
}

// Setter delegate
void THResourceUtils::setDelegate(THDownloadDelegate *delegate)
{
	m_delegate = delegate;
}

// Get data
THPackageAppData THResourceUtils::getData()
{
	return m_data;
}

// Get content data sorted by sequence
std::vector<THPackageAppContentData> THResourceUtils::getContentDataBySeq(int groupID)
{
	std::vector<THPackageAppContentData> ret;
	int l = m_data.groups.size();

	if(l && groupID < l)
	{
		for(int i = 0; i < l; i++)
		{
			int m =m_data.groups[i].contents.size();
			for(int j = 0; j < m; j++)
			{
				ret.push_back(m_data.groups[i].contents[j]);
			}
		}
		l = ret.size();

		if(l)
		{
			int i;
			int j;
			THPackageAppContentData temp;

			// Sort data
			for(i = 0; i < l - 1; i++)
			{
				for(j = i +1; j < l; j++)
				{
					if(ret[i].sequence > ret[j].sequence)
					{
						temp = ret[i];
						ret[i] = ret[j];
						ret[j] = temp;
					}
				}
			}
		}
	}

	return ret;
}

// Get current group data
THPackageAppGroupData THResourceUtils::getCurrentGroupData()
{
	//	CCLog("%d", m_currentGroupIndex);
	return m_data.groups[m_currentGroupIndex];
}

// Get current downloading content data
THPackageAppContentData THResourceUtils::getDownloadingContentData()
{
	THPackageAppContentData data;
	if(m_currentContentID >= 0)
	{
		int l = m_data.groups.size();
		for(int i = 0; i < l; i++)
		{
			int m = m_data.groups[i].contents.size();
			for(int j = 0 ; j < m; j++)
			{
				if(m_data.groups[i].contents[j].ID == m_currentContentID)
				{
					data = m_data.groups[i].contents[j];
					break;
				}
			}
		}
	}
	return data;
}

// Getter current content version
int THResourceUtils::getCurrentContentVersion(int contentID)
{
	int version = 0;
	int l = m_data.groups.size();
	for(int i = 0; i < l; i++)
	{
		int m = m_data.groups[i].contents.size();
		for(int j = 0 ; j < m; j++)
		{
			if(m_data.groups[i].contents[j].ID == contentID)
			{
				version = m_data.groups[i].contents[j].version;
				break;
			}
		}
	}

	return version;
}

// Return resource availablity for content and version in current app
bool THResourceUtils::getHasResourceForContent(int contentID, int contentVer)
{
	if(!contentVer)
	{
		contentVer = this->getCurrentContentVersion(contentID);
	}

	//	return THResourceUtils::getHasResource(m_data.ID, m_data.version, contentID, contentVer);
	return this->getStatusValueFromContentID(contentID, contentVer, CONTENT_STATUS_KEY_DOWNLOADED);
}

// Return full resource directory path for content and version in current app
const char *THResourceUtils::getResourcePath(int contentID, int contentVer)
{
	if(!contentVer)
	{
		contentVer = this->getCurrentContentVersion(contentID);
	}

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	return THResourceUtils::getResourcePath(m_data.ID, m_data.version, contentID, contentVer);
#else
	return THResourceUtils::getResourcePath(m_data.ID, m_data.version, contentID, contentVer, m_currentResourceDir);
#endif
}

bool THResourceUtils::removeContent(int contentID)
{
    const char* dirPath = THResourceUtils::getCurrentUtils()->getResourcePath(contentID);
    if(!THFileUtil::existFile(dirPath))
	{
		int contentVer = THResourceUtils::getCurrentUtils()->getCurrentContentVersion(contentID);
		std::string filePath = THFileUtil::getWriteablePath();
		std::string folderName = THResourceUtils::getCurrentUtils()->getResDirFromContentID(contentID, contentVer);
		filePath.append(folderName);
		filePath.append(".zip");

        /*
         * cocos2dx v2.1.4 deplicated CCFileUtils::fullPathFromRelativePath()
         * CCFileUtils::fullPathFromRelativePath() is not thread-safe, it use autorelease().
         *
         * filePath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("PKG/h001_c010.zip");
         */
//		filePath = CCFileUtils::sharedFileUtils()->fullPathForFilename("PKG/h001_c010.zip");
        
		if(!THFileUtil::existFile(filePath.c_str()))
		{
			return false;
		}

		if(remove(filePath.c_str()) == -1)
		{
			return false;
		}

		return true;
	}

	THFileUtil::removeDirectory(dirPath);
	return true;
}

// Start download for content and version in current app
void THResourceUtils::startDownload(int contentID, int contentVer)
{
	//	CCLog("================= startDownload %d.%d", contentID, contentVer);
	if(!contentVer)
	{
		contentVer = this->getCurrentContentVersion(contentID);
	}

	if(this->getHasResourceForContent(contentID, contentVer))
	{
		//		CCLog("NO:");
		return;
	}

	m_currentContentID = contentID;
	m_currentContentVersion = contentVer;

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	std::string destinationPath = THResourceUtils::getResourceDirectory(m_data.ID, m_data.version, m_currentContentID, m_currentContentVersion);
#else
	std::string destinationPath = THResourceUtils::getResourceDirectory(m_data.ID, m_data.version, m_currentContentID, m_currentContentVersion, contentData.resourceDir);
#endif

	std::string downloadInfoString = this->loadDownloadInfo(m_currentContentID, m_currentContentVersion);
	CCLog("===================== Download info string JSON");
	CCLog("%s", downloadInfoString.c_str());
	CCLog("=====================");

	struct THDownloadInfo downloadInfo = this->parseDownloadInfo(downloadInfoString.c_str());

	if(downloadInfo.status == kDownloadInfoStatusSuccess)
	{
		if(downloadInfo.fileSize)
		{
			float requireSpace = downloadInfo.fileSize * 3.0f;
			//			CCLog("================= require / free : %lld / %lld", (unsigned long long)requireSpace, THDevice::getFreeSpace());
			if(THDevice::getIsSimulator() || THDevice::getFreeSpace() > (unsigned long long)requireSpace)
			{
				m_currentDownloadFileName = downloadInfo.fileName;
				m_currentDownloadURL = downloadInfo.url;
				m_currentDownloadPath = destinationPath;
				m_currentDownloadSize = downloadInfo.fileSize;
				CCLog("Download: %s",  downloadInfo.url.c_str());

				if(THFileUtil::existFile(destinationPath.c_str()))
				{
					THFileUtil::removeDirectory(destinationPath.c_str());
				}

				s_downloadThread = THDownloadThread::getCurrentThread();
				//				s_downloadThread = new THDownloadThread();
				s_downloadThread->download(
						downloadInfo.fileName.c_str(),
						0,
						0,
						downloadInfo.url.c_str(),
						destinationPath.c_str(),
						this
				);
				//				s_downloadThread->join();

				m_downloadState = THDownloadStateProgress;
			}
			else
			{
				//				CCLog("================= no free space");
				this->error(THDownloadStatusSpaceError, "No free space");
			}
		}
		else
		{
			this->error(THDownloadStatusNetworkError, "File size error");
			//			m_delegate->error(0, "File size error");
		}
	}
	else
	{
		this->error(THDownloadStatusNetworkError, downloadInfo.description.c_str());
		//		m_delegate->error(0, downloadInfo.description.c_str());
	}

}


void *THResourceUtils::runGetDownloadInfo(void *data)
{
	CCLog("void *THResourceUtils::runGetDownloadInfo(void *data) >>>>> begin RUN");
	//	int contentID = *((int *)data);

	t_downloadInfoBuffer = THResourceUtils::getCurrentUtils()->loadDownloadInfo(t_contentID, t_contentVer);

	CCLog("%s", t_downloadInfoBuffer.c_str());
	CCLog("Load finished %d %d", t_contentID, t_contentVer);

	//	t_contentID = -1;
	//	t_contentVer = -1;
	//	t_downloadInfoBuffer.clear();
	t_downloadInfoFlag = 0;

	CCLog("Thread will terminate");

    pthread_exit(0);
    
	CCLog("void *THResourceUtils::runGetDownloadInfo(void *data) >>>>> finish RUN");
}

void THResourceUtils::startDownloadUsingThread(int contentID, int contentVer)
{
	if(!contentVer)
	{
		contentVer = this->getCurrentContentVersion(contentID);
	}

	if(this->getHasResourceForContent(contentID, contentVer))
	{
		return;
	}

	m_currentContentID = contentID;
	m_currentContentVersion = contentVer;

	m_authKey = CJLMSExtension::sharedInstance()->getAuthKey();
	m_url = CJLMSExtension::sharedInstance()->getURL();
	m_userAgent = CJLMSExtension::sharedInstance()->getUserAgent();
	m_transactionId = CJLMSExtension::sharedInstance()->getTransactionId();
	m_interfaceId = CJLMSExtension::sharedInstance()->getInterfaceId();
	m_interfaceVer = CJLMSExtension::sharedInstance()->getInterfaceVer();
	m_requestTime = CJLMSExtension::sharedInstance()->getRequestTime();

	// Prepare thread
	pthread_t p_thread;
	int thr_id;

	t_contentID = contentID;
	t_contentVer = contentVer;
	t_downloadInfoBuffer.clear();
	t_downloadInfoFlag = 1;

	thr_id = pthread_create(&p_thread, NULL, THResourceUtils::runGetDownloadInfo, NULL);
	CCLog("Thread id %d", thr_id);
	if(thr_id < 0)
	{
		perror("thread create error : ");

		t_contentID = -1;
		t_contentVer = -1;
		t_downloadInfoBuffer.clear();
		t_downloadInfoFlag = 0;

		this->error(0, "Thread create error");

		return;
	}
	pthread_detach(p_thread);

	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(THResourceUtils::checkDownloadInfoThread), this, 1.0f, false);
}

void THResourceUtils::checkDownloadInfoThread()
{
	CCLog("void THResourceUtils::checkDownloadInfoThread() >>>>> check Thread flag : %d", t_downloadInfoFlag);
	if(t_downloadInfoFlag == 0)
	{
		CCLog("Stop check Thread flag");
		CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(THResourceUtils::checkDownloadInfoThread), this);
		this->completeGetDownloadInfo(t_downloadInfoBuffer.c_str());

		t_contentID = -1;
		t_contentVer = -1;
		t_downloadInfoBuffer.clear();
		t_downloadInfoFlag = 0;
	}
}

void THResourceUtils::completeGetDownloadInfo(const char *pszDownloadInfo)
{
	std::string downloadInfoString = pszDownloadInfo;

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	std::string destinationPath = THResourceUtils::getResourceDirectory(m_data.ID, m_data.version, m_currentContentID, m_currentContentVersion);
#else
	std::string destinationPath = THResourceUtils::getResourceDirectory(m_data.ID, m_data.version, m_currentContentID, m_currentContentVersion, contentData.resourceDir);
#endif

	CCLog("===================== Download info string JSON");
	CCLog("%s", downloadInfoString.c_str());
	CCLog("=====================");

	struct THDownloadInfo downloadInfo = this->parseDownloadInfo(downloadInfoString.c_str());

	if(downloadInfo.status == kDownloadInfoStatusSuccess)
	{
		if(downloadInfo.fileSize)
		{
			float requireSpace = downloadInfo.fileSize * 3.0f;
			//			CCLog("================= require / free : %lld / %lld", (unsigned long long)requireSpace, THDevice::getFreeSpace());
			if(THDevice::getIsSimulator() || THDevice::getFreeSpace() > (unsigned long long)requireSpace)
			{
				m_currentDownloadFileName = downloadInfo.fileName;
				m_currentDownloadURL = downloadInfo.url;
				m_currentDownloadPath = destinationPath;
				m_currentDownloadSize = downloadInfo.fileSize;
				CCLog("Download: %s",  downloadInfo.url.c_str());

				if(THFileUtil::existFile(destinationPath.c_str()))
				{
					THFileUtil::removeDirectory(destinationPath.c_str());
				}

				s_downloadThread = THDownloadThread::getCurrentThread();
				//				s_downloadThread = new THDownloadThread();


				std::string resourceZipName = "";
				resourceZipName.append(downloadInfo.fileName);
				resourceZipName.append(".res");
                

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                std::string resourcePath = resourceZipName;
#else
                std::string resourcePath = "files/"+resourceZipName;
#endif

				s_downloadThread->download(
						resourceZipName.c_str(),
						CJLMSExtension::sharedInstance()->getFileSize(
								resourcePath.c_str()
						),
						downloadInfo.fileSize,
						downloadInfo.url.c_str(),
						destinationPath.c_str(),
						this
				);
				//				s_downloadThread->join();

				m_downloadState = THDownloadStateProgress;
			}
			else
			{
				//				CCLog("================= no free space");
				this->error(THDownloadStatusSpaceError, "No free space");
			}
		}
		else
		{
			this->error(THDownloadStatusNetworkError, "File size error");
			//			m_delegate->error(0, "File size error");
		}
	}
	else
	{
		this->error(THDownloadStatusNetworkError, downloadInfo.description.c_str());
		//		m_delegate->error(0, downloadInfo.description.c_str());
	}
}

// Load download inf form API
std::string THResourceUtils::loadDownloadInfo(int contentID, int contentVer)
{
	std::string buffer;

	// Get JSON
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if(curl)
	{
		std::string URL = m_url;

		THPackageAppContentData contentData = this->getDownloadingContentData();

		std::string *postFields = new std::string();
		postFields->append("{'header':{'comTrId':'");
		postFields->append(m_transactionId.c_str());
		postFields->append("', 'comInterfaceId':'");
		postFields->append(m_interfaceId.c_str());
		postFields->append("', 'comInterfaceVersion':'");
		postFields->append(m_interfaceVer.c_str());
		postFields->append("', 'comRequestDate':'");
		postFields->append(m_requestTime.c_str());
		postFields->append("'}, 'body':[{'appKeyTp':'");
		postFields->append("2001");													// Android pad: 2001, Android phone: 2000, iPhone: 1000, iPad: 1001
		postFields->append("', 'appTpKey':'");
		postFields->append(m_data.bundleID.c_str());								// App key
		postFields->append("', 'appContentsInqTp':'");
		postFields->append("1000");													// Single: 1000, All: 9999
		postFields->append("', 'appContentsNo':'");
		postFields->append(contentData.no.c_str());								// Content uniq number
		postFields->append("', 'appContentsVer':'");
		postFields->append(THStringUtil::format("%d", contentData.version).c_str());								// Content version
		postFields->append("', 'reqDate':'");
		postFields->append(m_requestTime.c_str());
		postFields->append("'}]}");

		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "Host: dev-mps.thinkle.net:10100");
		headers = curl_slist_append(headers, "User-agent: AND;4.1.1 ;720x1024 ;KR ;  ; ;00:0a:eb:68:7f:ee ;ITP-R208W;THINKWARE ;9999 ;1;;json");
		headers = curl_slist_append(headers, "Accept-language: ko-KR");
		headers = curl_slist_append(headers, "Accept-encoding: gzip, deflate");
		headers = curl_slist_append(headers, "Cookie: WMONID=mW8Z0nAmN70");
		headers = curl_slist_append(headers, "Connection: keep-alive");
		headers = curl_slist_append(headers, "Content-Type: application/json");
		headers = curl_slist_append(headers, THStringUtil::format("X-Cookie: %s", m_authKey.c_str()).c_str());
        
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);                    // Request header 추가
		curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());                       // Requset target server url
		curl_easy_setopt(curl, CURLOPT_POST, 1);                                // TRUE - send POST , FALSE - did't send POST
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields->c_str());        // POST datas
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeString);             // SUCCESS callback
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);                            //
    
        
        // Add LeeYJ, Add Network condition exception.
//        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30);                            // All performance cURL connect timeout.
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 5);                     // Response timeout to send request.
//        curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 0);                  // cURL low speed limit (bytes per second)
//        curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 10);                      // cURL continue time limit of low speed limit
        
		res = curl_easy_perform(curl);

        
        
        
//        resCode 28 = Request Timeout
        CCLog("CURL ERROR -----------------------------------------------------------");
        CCLog("%d - %s", res, curl_easy_strerror(res));
        CCLog("CURL ERROR -----------------------------------------------------------");

        
		curl_slist_free_all(headers);
		curl_easy_cleanup(curl);
        
        // Add LeeYJ, Memory leak.
        delete postFields;
	}

	CCLog("%s", buffer.c_str());

	return buffer;
}

// Load status JSON
bool THResourceUtils::loadStatusData()
{
	Json::Reader jsonReader;

	// Check download status file
	std::string inPath = THFileUtil::getWriteablePath();
	inPath.append(RESOURCE_STATUS_FILE_NAME);
	inPath.append(".json");
	bool hasStatusFile = THFileUtil::existFile(inPath.c_str());
	if(hasStatusFile)
	{
		std::string statusFileString = THFileUtil::readFromFile(inPath.c_str());
		hasStatusFile = jsonReader.parse(statusFileString, m_statusData);

		if(hasStatusFile)
		{
			//			CCLog("### Read from file");
		}
	}

	return hasStatusFile;
}

// Update status JSON
bool THResourceUtils::updateStatusData()
{
	if(!!m_statusData)
	{
		Json::FastWriter jsonWriter;
		std::string outputConfig = jsonWriter.write(m_statusData);
		std::string outPath = THFileUtil::getWriteablePath();
		outPath.append(RESOURCE_STATUS_FILE_NAME);
		outPath.append(".json");
		bool isWrited = THFileUtil::writeToFile(outPath.c_str(), outputConfig.c_str(), outputConfig.length());
		if(isWrited)
		{
			//			CCLog("### Write to file");
			return true;
		}
	}
	return false;
}

// Parsing download info from JSON string
THDownloadInfo THResourceUtils::parseDownloadInfo(const char *downloadInfo)
{
	struct THDownloadInfo ret;
	ret.status = kDownloadInfoStatusNone;

	// Parse to JSON
	Json::Reader jsonReader;
	Json::Value downloadInfoJson;
	bool bParseingSuccessful = jsonReader.parse(downloadInfo, downloadInfoJson);
	if(!bParseingSuccessful)
	{
		printf("JSON parsing failed.\n");
		//		m_delegate->error(0, "JSON failed.");
		ret.status = kDownloadInfoStatusError;
		ret.description = "JSON failed.";
		return ret;
	}

	if(!downloadInfoJson.isMember("body"))
	{
		ret.status = kDownloadInfoStatusError;
		ret.description = "JSON failed.";
		return ret;
	}

	int i = 0;
	Json::Value bodyJson = downloadInfoJson["body"][i];

	if(!bodyJson.isMember("rsltTp"))
	{
		ret.status = kDownloadInfoStatusError;
		ret.description = "JSON failed.";
		return ret;
	}

	//	std::string bodyString = downloadInfoJson["body"].toStyledString();
	//	printf("1=========\n%s\n", bodyString.c_str());
	//	bodyString = bodyString.substr(1, bodyString.size() - 1);
	//	bodyString = THStringUtil::replaceAll(bodyString, "]", "");

	//	printf("2=========\n%s\n", bodyString.c_str());

	//	Json::Value bodyJson;
	//	jsonReader.parse(bodyString, bodyJson);

	//	printf("3=========\n%s\n", bodyJson.toStyledString().c_str());

	std::string resultCode = bodyJson["rsltTp"].asString();
	//	printf("r===== %s\n", resultCode.c_str());

	if(resultCode.compare("R1000"))
	{
		printf("result code error.\n");
		ret.status = kDownloadInfoStatusError;
		ret.description = "result code error.";
		return ret;
	}

	if(!bodyJson.isMember("appContentsList"))
	{
		ret.status = kDownloadInfoStatusError;
		ret.description = "JSON failed.";
		return ret;
	}

	std::string currentContentsVerStr = this->getDownloadingContentData().versionString;
	Json::Value list = bodyJson["appContentsList"];
	for(int i = 0; i < list.size(); i++)
	{
		if(list[i].isMember("appContentsVer"))
		{
//			CCLog("========== VER: %s =? %s", list[i].get("appContentsVer", "UTF-8").asString().c_str(), currentContentsVerStr.c_str());
			if(!list[i].get("appContentsVer", "UTF-8").asString().compare(currentContentsVerStr))
				//			if(atoi(list[i].get("appContentsVer", "UTF-8").asString().c_str()) == m_currentContentVersion)
				//			if(atoi(list[i].get("appContentsVer", "UTF-8").asString().c_str()) == 100)
			{
				if(!list[i].isMember("appContentsSize"))
				{
					ret.status = kDownloadInfoStatusError;
					ret.description = "JSON failed.";
					return ret;
				}

				ret.fileSize = atol(list[i].get("appContentsSize", "UTF-8").asString().c_str());

				if(!list[i].isMember("appContentsDownAppUrl"))
				{
					ret.status = kDownloadInfoStatusError;
					ret.description = "JSON failed.";
					return ret;
				}

				ret.url = list[i].get("appContentsDownAppUrl", "UTF-8").asString();


				// sh_hong
				if(!list[i].isMember("appContentsNo"))
				{
					ret.status = kDownloadInfoStatusError;
					ret.description = "JSON failed.";
					return ret;
				}
				ret.fileName = list[i].get("appContentsNo", "UTF-8").asString();

				//				printf("===== last / : %d\n", (int)ret.url.find_last_of("/"));
				//				ret.fileName = ret.url.substr((ret.url.find_last_of("/") + 1));
				//				if(ret.fileName.size() > 50)
				//				{
				//					ret.fileName = "download.resource";
				//				}


				ret.status = kDownloadInfoStatusSuccess;
				//				printf("====== %s\n", ret.fileName.c_str());
				break;
			}
		}
	}

	//	if(!downloadInfoJson.isMember("resultCode"))
	//	{
	//		ret.status = kDownloadInfoStatusError;
	//		ret.description = "JSON failed.";
	//		return ret;
	//	}
	//
	//	std::string resultCode = downloadInfoJson.get("resultCode", "UTF-8").asString();
	//
	//	if(resultCode.compare("S0000"))
	//	{
	//		printf("result code error.\n");
	//		ret.status = kDownloadInfoStatusError;
	//		ret.description = "result code error.";
	//		return ret;
	//	}
	//
	//	if(!downloadInfoJson.isMember("data"))
	//	{
	//		printf("data is not member\n");
	//		ret.status = kDownloadInfoStatusError;
	//		ret.description = "data is not member.";
	//		return ret;
	//	}
	//
	//	downloadInfoJson = downloadInfoJson["data"];
	//
	//	if(downloadInfoJson.isMember("fileSize"))
	//	{
	//		ret.fileSize = downloadInfoJson.get("fileSize", "UTF-8").asInt();
	//	}
	//
	//	if(downloadInfoJson.isMember("fileName"))
	//	{
	//		ret.fileName = downloadInfoJson.get("fileName", "UTF-8").asString();
	//	}
	//
	//	if(downloadInfoJson.isMember("url"))
	//	{
	//		ret.url = downloadInfoJson.get("url", "UTF-8").asString();
	//	}


	return ret;
}

int THResourceUtils::indexOfContentIDFromProductID(const char *productID)
{
	int l = m_data.groups.size();
	for(int i = 0; i < l; i++)
	{
		int m = m_data.groups[i].contents.size();
		for(int j = 0; j < m; j++)
		{
			if(m_data.groups[i].contents[j].productID.compare(productID) == 0)
			{
				return m_data.groups[i].contents[j].ID;
			}
		}
	}

	return -1;
}

/*
// Download finish handler
void ResourceUtils::hndFinish(bool finished)
{
	if(finished)
	{
		m_delegate->end();
	}
	else
	{
		m_delegate->error(0, "Download error");
	}
}
 */

// Stop download
void THResourceUtils::stopDownload(int contentID)
{
	if(m_downloadState == THDownloadStateProgress || m_downloadState == THDownloadStateExtract)
	{
		if(s_downloadThread != NULL)
		{
			//			THDownloadThread::destroy();
			//			s_downloadThread->clear();
			//			delete s_downloadThread;
			//			s_downloadThread = NULL;
		}
		m_downloadState = THDownloadStateReady;
	}
}

// Pause download
void THResourceUtils::pause()
{
	//	printf("===== THResourceUtils::pause()");
	if(m_downloadState == THDownloadStateProgress || m_downloadState == THDownloadStateExtract)
	{
		//		printf(" - run\n");
		s_downloadThread->pause();
		//		pthread_exit(s_downloadThread);
		//		THDownloadThread::destroy();
		//		s_downloadThread->join();

		m_downloadState = THDownloadStatePause;
	}
}

// Resume download
void THResourceUtils::resume()
{
	//	printf("===== THResourceUtils::resume()");
	if(m_downloadState == THDownloadStatePause)
	{
		s_downloadThread->play();
		m_downloadState = THDownloadStateProgress;
		//		if(s_downloadThread != NULL)
		//		{
		//			printf(" - run\n");
		//			s_downloadThread->play();
		//			m_downloadState = THDownloadStateProgress;
		////			s_downloadThread->join();
		////			s_downloadThread->run();
		//		}

		//		float requireSpace = m_currentDownloadSize * 3.0f;
		//		if(THDevice::getFreeSpace() > (unsigned long)requireSpace)
		//		{
		//			printf(" - run\n");
		//			s_downloadThread = THDownloadThread::getCurrentThread();
		////			s_downloadThread = new THDownloadThread();
		//			s_downloadThread->download(m_currentDownloadFileName.c_str(), m_currentDownloadURL.c_str(), m_currentDownloadPath.c_str(), this);
		//
		//			m_downloadState = THDownloadStateProgress;
		//		}
		//		else
		//		{
		//			this->error(THDownloadStatusSpaceError, "No free space");
		//		}
	}
}

// Return that is downloading
bool THResourceUtils::getIsDownloading(int contentID)
{
	return m_downloadState == THDownloadStateProgress || m_downloadState == THDownloadStateExtract;
}

bool THResourceUtils::getHasDownloading()
{
	return (m_downloadState == THDownloadStateProgress ||
			m_downloadState == THDownloadStateExtract ||
			m_downloadState == THDownloadStatePause);
}

// Return contentID, if is downloading
int THResourceUtils::getDownloadingContentID()
{
	return m_currentContentID;
}

void THResourceUtils::setDefaultContent(int contentID, int contentVer)
{
	//	CCLog("setDefaultContent %d %d", contentID, contentVer);
	m_currentResourceDir = getResDirFromContentID(contentID, contentVer);
	m_currentContentID = contentID;
	m_currentContentVersion = contentVer;
	//	m_currentGroupIndex = this->getGroupIndexForContentID(contentID);
}

const char *THResourceUtils::getDefaultResourcePath()
{
	if(m_currentContentID < 0 || m_currentContentVersion < 0)
	{
		return "";
	}

	return this->getResourcePath(m_currentContentID, m_currentContentVersion);
}

int THResourceUtils::getGroupIndexForContentID(int contentID)
{
	int l = m_data.groups.size();
	for(int i = 0; i < l; i++)
	{
		int m = m_data.groups[i].contents.size();
		for(int j = 0 ; j < m; j++)
		{
			if(m_data.groups[i].contents[j].ID == contentID)
			{
				return i;
			}
		}
	}

	return -1;
}

int THResourceUtils::getContentStatusFromCurrentContent()
{
	return this->getContentStatusFromContentID(m_currentContentID, m_currentContentVersion);
}

int THResourceUtils::getContentStatusFromContentID(int contentID, int contentVersion)
{
	int l = m_statusData["contents"].size();
	if(l)
	{
		for(int i = 0; i < l; i++)
		{
			if(m_statusData["contents"][i].isMember(RESOURCE_FILE_KEY_FOR_CONTENT_ID) &&
					m_statusData["contents"][i].get(RESOURCE_FILE_KEY_FOR_CONTENT_ID, "UTF-8").asInt() == contentID &&
					m_statusData["contents"][i].get(RESOURCE_FILE_KEY_FOR_CONTENT_VERSION, "UTF-8").asInt() == contentVersion)
			{
				bool purchased = false;
				bool downloaded = false;

				if(m_statusData["contents"][i].isMember(RESOURCE_FILE_KEY_FOR_CONTENT_PURCHASED))
				{
					purchased = m_statusData["contents"][i].get(RESOURCE_FILE_KEY_FOR_CONTENT_PURCHASED, "UTF-8").asBool();
				}

				if(m_statusData["contents"][i].isMember(RESOURCE_FILE_KEY_FOR_CONTENT_DOWNLOADED))
				{
					downloaded = m_statusData["contents"][i].get(RESOURCE_FILE_KEY_FOR_CONTENT_DOWNLOADED, "UTF-8").asBool();
				}

				//shchoi, modify ? -> if..else ...........why do NOT act with "?"?
				//				return purchased ? (downloaded ? CONTENT_STATUS_DOWNLOADED : CONTENT_STATUS_PURCHASED) : CONTENT_STATUS_NONE;

				if(downloaded)
				{
					if(purchased)
					{
						return CONTENT_STATUS_DOWNLOADED;
					}
					else
					{
						return CONTENT_STATUS_NONE;
					}
				}
				else
				{
					if(purchased)
					{
						return CONTENT_STATUS_PURCHASED;
					}
					else
					{
						return CONTENT_STATUS_NONE;
					}
				}
			}
		}
	}
	return CONTENT_STATUS_NONE;
}

bool THResourceUtils::getPurchasedStatusValueFromCurrentContent()
{
	return this->getStatusValueFromCurrentContent(CONTENT_STATUS_KEY_PURCHASED);
}

bool THResourceUtils::getDownloadedStatusValueFromCurrentContent()
{
	return this->getStatusValueFromCurrentContent(CONTENT_STATUS_KEY_DOWNLOADED);
}

bool THResourceUtils::getStatusValueFromCurrentContent(int status)
{
	return this->getStatusValueFromContentID(m_currentContentID, m_currentContentVersion, status);
}

bool THResourceUtils::getStatusValueFromContentID(int contentID, int contentVersion, int status)
{
	std::string key;
	bool defaultValue;
	switch(status)
	{
	case CONTENT_STATUS_KEY_PURCHASED:
		key = RESOURCE_FILE_KEY_FOR_CONTENT_PURCHASED;
		defaultValue = false;
		break;
	case CONTENT_STATUS_KEY_DOWNLOADED:
		key = RESOURCE_FILE_KEY_FOR_CONTENT_DOWNLOADED;
		defaultValue = false;
		break;
	default:
		return defaultValue;
	}

	int l = m_statusData["contents"].size();
	if(l)
	{
		for(int i = 0; i < l; i++)
		{
            if(m_statusData["contents"][i].isMember(RESOURCE_FILE_KEY_FOR_CONTENT_ID) &&
			   m_statusData["contents"][i].isMember(RESOURCE_FILE_KEY_FOR_CONTENT_VERSION) &&
			   m_statusData["contents"][i].get(RESOURCE_FILE_KEY_FOR_CONTENT_ID, "UTF-8").asInt() == contentID &&
               m_statusData["contents"][i].get(RESOURCE_FILE_KEY_FOR_CONTENT_VERSION, "UTF-8").asInt() == contentVersion)
            {
				if(m_statusData["contents"][i].isMember(key))
				{
					return m_statusData["contents"][i].get(key, "UTF-8").asBool();
				}

				return defaultValue;
			}
		}
	}

	return defaultValue;
}

int THResourceUtils::getStatusVersionFromContentID(int contentID)
{
    int version = -1;
    
    int l = m_statusData["contents"].size();
    if(l)
    {
        for(int i = 0; i < l; i++)
        {
            if(m_statusData["contents"][i].isMember(RESOURCE_FILE_KEY_FOR_CONTENT_ID) &&
               m_statusData["contents"][i].get(RESOURCE_FILE_KEY_FOR_CONTENT_ID, "UTF-8").asInt() == contentID)
            {
                if(m_statusData["contents"][i].isMember(RESOURCE_FILE_KEY_FOR_CONTENT_VERSION))
                {
                    return m_statusData["contents"][i].get(RESOURCE_FILE_KEY_FOR_CONTENT_VERSION, "UTF-8").asInt();
                }
                
                return version;
            }
        }
    }
    
    return version;
}

bool THResourceUtils::setStatusVersionFromContentID(int contentID, int contentVersion)
{
    int l = m_statusData["contents"].size();
	if(l)
	{
		for(int i = 0; i < l; i++)
		{
			if(m_statusData["contents"][i].isMember(RESOURCE_FILE_KEY_FOR_CONTENT_ID) &&
			   m_statusData["contents"][i].get(RESOURCE_FILE_KEY_FOR_CONTENT_ID, "UTF-8").asInt() == contentID)
			{
				m_statusData["contents"][i][RESOURCE_FILE_KEY_FOR_CONTENT_VERSION] = contentVersion;
				this->updateStatusData();
                
				return true;
			}
		}
	}
    
	return false;
}

//shchoi, add For getting contents Directory
std::string THResourceUtils::getResDirFromContentID(int contentID, int contentVersion)
{
	std::string resourceDir = "";
	int l = m_data.groups.size();
	for(int i = 0; i < l; i++)
	{
		int m = m_data.groups[i].contents.size();
		for(int j = 0 ; j < m; j++)
		{
			if(m_data.groups[i].contents[j].ID == contentID)
			{
				resourceDir = m_data.groups[i].contents[j].resourceDir;
				break;
			}
		}
	}
	return resourceDir;
}



bool THResourceUtils::setStatusValueFromCurrentContent(int status, bool value)
{
	return this->setStatusValueFromContentID(m_currentContentID, m_currentContentVersion, status, value);
}

bool THResourceUtils::setStatusValueFromContentID(int contentID, int contentVersion, int status, bool value)
{
	std::string key;
	switch(status)
	{
	case CONTENT_STATUS_KEY_PURCHASED:
		key = RESOURCE_FILE_KEY_FOR_CONTENT_PURCHASED;
		break;
	case CONTENT_STATUS_KEY_DOWNLOADED:
		key = RESOURCE_FILE_KEY_FOR_CONTENT_DOWNLOADED;
		break;
	default:
		return false;
	}

	int l = m_statusData["contents"].size();
	if(l)
	{
		for(int i = 0; i < l; i++)
		{
//            CCLog("index : %d =>  %d // %d==%d // %d==%d",
//                  i,
//                  m_statusData["contents"][i].isMember(RESOURCE_FILE_KEY_FOR_CONTENT_ID),
//                  m_statusData["contents"][i].get(RESOURCE_FILE_KEY_FOR_CONTENT_ID, "UTF-8").asInt(),
//                  contentID,
//                  m_statusData["contents"][i].get(RESOURCE_FILE_KEY_FOR_CONTENT_VERSION, "UTF-8").asInt(),
//                  contentVersion);
            if(m_statusData["contents"][i].isMember(RESOURCE_FILE_KEY_FOR_CONTENT_ID) &&
			   m_statusData["contents"][i].isMember(RESOURCE_FILE_KEY_FOR_CONTENT_VERSION) &&
			   m_statusData["contents"][i].get(RESOURCE_FILE_KEY_FOR_CONTENT_ID, "UTF-8").asInt() == contentID)
            
//			if(m_statusData["contents"][i].isMember(RESOURCE_FILE_KEY_FOR_CONTENT_ID) &&
//					m_statusData["contents"][i].get(RESOURCE_FILE_KEY_FOR_CONTENT_ID, "UTF-8").asInt() == contentID &&
//					m_statusData["contents"][i].get(RESOURCE_FILE_KEY_FOR_CONTENT_VERSION, "UTF-8").asInt() == contentVersion)
			{
				m_statusData["contents"][i][key] = value;
				this->updateStatusData();

				return true;
			}
		}
	}

	return false;
}

std::vector<std::string> THResourceUtils::getAllProductID()
{
	return m_allProductID;
}

std::string THResourceUtils::getCurrentLanguageCode()
{
	return m_currentLanguagCode;
}

bool THResourceUtils::setPurchasedStatusValueFromProductID(const char *productID)
{
	int idx = this->indexOfContentIDFromProductID(productID);
	if(idx >= 0)
	{
		this->setStatusValueFromContentID(idx, this->getCurrentContentVersion(idx), CONTENT_STATUS_KEY_PURCHASED, true);

		return true;
	}

	return false;
}

void THResourceUtils::begin()
{
	m_currentProgress = 0;
	if(m_delegate)	
	{
		m_delegate->begin();
	}
    
    CCLog("=========== THResourceUtils::begin ==");
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(THResourceUtils::hndUpdateProgress), this, 0.0f, false);
}

void THResourceUtils::setStatus(int type)
{
	if(m_currentDownloadStatus != type)
	{
		m_currentDownloadStatus = type;
//		CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(THResourceUtils::hndStatusUpdated), this, 0.0f, false);
        
        CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(THResourceUtils::hndStatusUpdated));
        CCDirector::sharedDirector()->getRunningScene()->runAction(callFunc);
	}
}

void THResourceUtils::setProgress(double current)
{
	m_currentProgress = current;
}

void THResourceUtils::end()
{
//	CCLog("========== THResourceUtils::end");
	if(s_downloadThread != NULL)
	{
		//		CCLog("========== THResourceUtils::end if");
		//		THDownloadThread::destroy();
		//		s_downloadThread->clear();
		//		delete s_downloadThread;
		//		s_downloadThread = NULL;
	}
	//	CCDirector::sharedDirector()->getScheduler()->unscheduleAllSelectorsForTarget(this);
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(THResourceUtils::hndUpdateProgress), this);

	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(THResourceUtils::hndDownloadEnded), this, 0.0, false);
}

void THResourceUtils::hndDownloadEnded()
{
	bool update = false;
	if(this->setStatusValueFromCurrentContent(CONTENT_STATUS_KEY_PURCHASED, true))
	{
		update = true;;
		//		this->updateStatusData();
	}
	if(this->setStatusValueFromCurrentContent(CONTENT_STATUS_KEY_DOWNLOADED, true))
	{
        this->setStatusVersionFromContentID(m_currentContentID, m_currentContentVersion);
		update = true;
		//		this->updateStatusData();
	}

	if(update)
	{
		this->updateStatusData();
	}

	m_downloadState = THDownloadStateReady;
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(THResourceUtils::hndDownloadEnded), this);
	m_delegate->end();
}

void THResourceUtils::error(int type, const char *description)
{
	//	CCLog("THResourceUtils::error");
	if(s_downloadThread != NULL)
	{
		//		THDownloadThread::destroy();
		//		s_downloadThread->clear();
		//		delete s_downloadThread;
		//		s_downloadThread = NULL;
	}

	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(THResourceUtils::hndUpdateProgress), this);

	m_currentErrorType = type;
	m_currentErrorDescription = description;

	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(THResourceUtils::hndDownloadError), this, 0.0, false);
}

void THResourceUtils::hndDownloadError()
{
	//	CCLog("THResourceUtils::hndDownloadError");
	m_downloadState = THDownloadStateReady;
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(THResourceUtils::hndDownloadError), this);

	if(m_delegate)	
	{
		//		CCLog("THResourceUtils::hndDownloadError to delegate %d", m_currentErrorType);
		m_delegate->error(m_currentErrorType, m_currentErrorDescription.c_str());
	}
}

void THResourceUtils::hndUpdateProgress()
{
	if(m_delegate)
	{
		m_delegate->setProgress(m_currentProgress);
	}
	else
	{
		this->stopDownload(m_currentContentID);
	}
}

void THResourceUtils::hndStatusUpdated()
{
//	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(THResourceUtils::hndStatusUpdated), this);

	if(m_delegate)	
	{
		m_delegate->setStatus(m_currentDownloadStatus);
	}
}

