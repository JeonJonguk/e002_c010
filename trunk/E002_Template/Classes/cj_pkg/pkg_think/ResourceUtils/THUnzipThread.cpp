//
//  THUnzipThread.cpp
//  ithink
//
//  Created by pureMini on 13. 1. 14..
//
//

#include "THUnzipThread.h"
#include "../Basic/THStringUtil.h"
#include "../Basic/THFileUtil.h"
#include "support/zip_support/unzip.h"
#include "cocos2d.h"
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <sys/xattr.h>
#endif


THUnzipThread::THUnzipThread(int num)
{
	m_num = num;
	m_live = false;
}

THUnzipThread::~THUnzipThread()
{
//	cocos2d::CCLog("THUnzipThread::~THUnzipThread()");
	m_live = false;
	m_delegate = NULL;
	m_filePath.clear();
	m_destPath.clear();
}

void THUnzipThread::unzip(const char *pszFilePath, const char *pszDestPath, THThreadDelegate *pDelegate)
{
	m_filePath = pszFilePath;
	m_destPath = pszDestPath;
	m_delegate = pDelegate;
	
	this->start();
}

int THUnzipThread::run()
{
	m_live = true;
	
	// Unzip
	unzFile zipfile = cocos2d::unzOpen(m_filePath.c_str());
	if(zipfile == NULL)
	{
//		cocos2d::CCLog("%s: not found\n", m_filePath.c_str());
		
		if(m_delegate != NULL)
		{
			m_delegate->error(0, "File not found");
			m_delegate = NULL;
		}
		return false;
	}
	
	cocos2d::unz_global_info global_info;
	if(unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
	{
//		cocos2d::CCLog("Could not read file global info\n");
		cocos2d::unzClose(zipfile);
		if(m_delegate != NULL)
		{
			m_delegate->error(0, "Could not read file global info");
			m_delegate = NULL;
		}
		return false;
	}
	
	uLong i;
	
	// Prepare dir
	std::vector<std::string> dirs = THStringUtil::split(m_destPath.c_str(), '/');
	std::string dir = THFileUtil::getWriteablePath();
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//shchoi, 2012.10.09, change path to 'root' for Android
	for(i = 0; i < dirs.size(); i++)
	{
		dir.append(dirs[i].c_str());
		
		if(!THFileUtil::existFile(dir.c_str()))
		{
			mkdir(dir.c_str(), 0777);
		}
		dir.append("/");
	}
	
	// Add skip backup attribute to item at URL
	const char *attrName = "com.apple.MobileBackup";
	u_int8_t attrValue = 1;
	
	int result = setxattr(dir.c_str(), attrName, &attrValue, sizeof(attrValue), 0, 0);
	if(result != 0)
	{
		printf("Could not ad skip backup attribute to item at URL");
		return false;
	}
#endif
	
	char read_buffer[8192];
	
	for(i = 0; i < global_info.number_entry; ++i)
	{
//		cocos2d::CCLog("%d - is live? %d\n", i, m_live);
		
		if(!m_live)
		{
			return 0;
		}
		
		cocos2d::unz_file_info file_info;
		char filename[512];
		if(unzGetCurrentFileInfo(zipfile, &file_info, filename, 512, NULL, 0, NULL, 0) != UNZ_OK)
		{
//			cocos2d::CCLog("Could not read file info\n");
			if(m_delegate != NULL)
			{
				m_delegate->error(0, "Could not read file info");
				m_delegate = NULL;
			}
			return 0;
		}
		
		std::string destFilePath = dir.c_str();
		destFilePath.append(filename);
		
		const size_t filename_length = strlen(destFilePath.c_str());
		if(destFilePath.at(filename_length - 1) == '/')
		{
			if(destFilePath.find("__MACOSX") == -1)
			{
				mkdir(destFilePath.c_str(), 0777);
			}
		}
		else
		{
			if(destFilePath.find("__MACOSX") == -1)
			{
				if(cocos2d::unzOpenCurrentFile(zipfile) != UNZ_OK)
				{
//					cocos2d::CCLog("Could not open file\n");
					cocos2d::unzClose(zipfile);
					if(m_delegate != NULL)
					{
						m_delegate->error(0, "Could not open file");
						m_delegate = NULL;
					}
					return 0;
				}
				
				FILE *out = fopen(destFilePath.c_str(), "wb");
				if(out == NULL)
				{
//					cocos2d::CCLog("Could not open destination file\n");
					cocos2d::unzCloseCurrentFile(zipfile);
					cocos2d::unzClose(zipfile);
					if(m_delegate != NULL)
					{
						m_delegate->error(0, "Could not open destination file");
						m_delegate = NULL;
					}
					return 0;
				}
				
				int error = UNZ_OK;
				do
				{
					error = cocos2d::unzReadCurrentFile(zipfile, read_buffer, 8192);
					if(error < 0)
					{
//						cocos2d::CCLog("Error %d\n", error);
						cocos2d::unzCloseCurrentFile(zipfile);
						cocos2d::unzClose(zipfile);
						if(m_delegate != NULL)
						{
							m_delegate->error(0, "Extracting file error");
							m_delegate = NULL;
						}
						return 0;
					}
					
					if(error > 0)
					{
//						cocos2d::CCLog("write is live? %d\n", m_live);
						if(!m_live)
						{
							return 0;
						}
						fwrite(read_buffer, error, 1, out);
					}
				}while(error > 0);
				
				fclose(out);
			}
		}
		
		cocos2d::unzCloseCurrentFile(zipfile);
		
		if((i + 1) < global_info.number_entry)
		{
			if(cocos2d::unzGoToNextFile(zipfile) != UNZ_OK)
			{
//				cocos2d::CCLog("Could not read next file\n");
				cocos2d::unzClose(zipfile);
				if(m_delegate != NULL)
				{
					m_delegate->error(0, "Could not read next file");
					m_delegate = NULL;
				}
				return 0;
			}
		}
	}
	
	cocos2d::unzClose(zipfile);
	
//	cocos2d::CCLog("remove is live? %d\n", m_live);
	if(!m_live)
	{
		return 0;
	}
	
//	cocos2d::CCLog("Delete file %s", m_filePath.c_str());
//	if(remove(m_filePath.c_str()) == -1)
//	{
//		cocos2d::CCLog("Delete downloaded zip file failed\n");
//		if(m_delegate != NULL)
//		{
//			m_delegate->error(0, "Delete zip file error");
//			m_delegate = NULL;
//		}
//		return 0;
//	}
//	cocos2d::CCLog("end is live? %d\n", m_live);
	if(!m_live)
	{
		return 0;
	}
	
	m_delegate->end();
	m_delegate = NULL;
	
	return 1;
}

void THUnzipThread::stop()
{
	printf("stop %d\n", m_num);
	m_live = false;
}

void THUnzipThread::cleanup()
{
	printf("THUnzipThread::cleanup()");
	m_filePath.clear();
	m_destPath.clear();
	m_delegate = NULL;
}