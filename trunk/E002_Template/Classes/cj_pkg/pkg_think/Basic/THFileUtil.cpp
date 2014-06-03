//
//  THFileUtil.cpp
//  Think
//
//  Created by pureye4u BX on 12. 8. 22..
//  Copyright CJ Educations 2012. All rights reserved.
//

#include "THFileUtil.h"
#include "THDevice.h"
#include "THStringUtil.h"

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include "CCFileUtils.h"
#include "support/zip_support/unzip.h"

static std::string s_writeablePath = "";

// Return is file exists
bool THFileUtil::existFile(const char* fileName)
{
	if(!fileName)
	{
		return false;
	}
	
	std::string fullPath(fileName);
	
	if(!fileName)
	{
		return false;
	}
	
	do
	{
		FILE *fp = fopen(fileName, "r");
		if(fp != NULL)
		{
			fclose(fp);
			return true;
		}
	}
	while(0);
	
	return false;
}

// Read a file
std::string THFileUtil::readFromFile(const char *fileName)
{
	FILE *fp = fopen(fileName, "r");
	if(fp == NULL)
	{
		return NULL;
	}
	
	fseek(fp, 0, SEEK_END);
	size_t size = ftell(fp);
	
	char *buffer = new char[size];
	rewind(fp);
	fread(buffer, sizeof(char), size, fp);
	fclose(fp);
	std::string str = buffer;
	delete[] buffer;
	
	return str;
}

// Write a file
bool THFileUtil::writeToFile(const char *fileName, const char *buffer, int length)
{
	FILE *fp = fopen(fileName, "wb");
	if(fp == NULL)
	{
		return false;
	}
	
	fwrite(buffer, 1, length, fp);
	fclose(fp);
	
	return true;
}

// Remove directory and files
bool THFileUtil::removeDirectory(const char *dirPath)
{
	std::string orgPath = dirPath;
//	printf("##### removeDirectory: (%s)\n", dirPath);
	DIR *dir;
	struct dirent *entry;
	char path[PATH_MAX];
	
	if(path == NULL)
	{
//		printf("##### path == NULL\n");
		return false;
	}
	dir = opendir(dirPath);
	if(dir == NULL)
	{
		perror("Error opendir()");
		return false;
	}
	
	while((entry = readdir(dir)) != NULL)
	{
//		printf("##### > %s\n", entry->d_name);
		if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, ".."))
		{
			snprintf(path, (size_t)PATH_MAX, "%s/%s", dirPath, entry->d_name);
//			printf("##### == %s\n", path);
			if(entry->d_type == DT_DIR)
			{
				removeDirectory(path);
			}
			else
			{
				unlink(path);
			}
		}
	}
	closedir(dir);
	
//	printf("##### rmdir(%s)\n", orgPath.c_str());
	rmdir(orgPath.c_str());
	
	return true;
}

// Get writeable path
const char *THFileUtil::getWriteablePath()
{
	if(s_writeablePath.compare("") == 0)
	{
		s_writeablePath = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath();
#if (CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
        std::string::iterator iter = s_writeablePath.begin();
        size_t pos = s_writeablePath.find("files/");
        iter+=pos;
        s_writeablePath.erase(iter, s_writeablePath.end());
#endif

//		s_writeablePath = THDevice::getApplicationCacheDirectory();
//		s_writeablePath = THDevice::getDocumentDirectory();
	}
	
	return s_writeablePath.c_str();
}

// Unzip file to destination
void THFileUtil::unzip(const char *filePath, const char *destPath)
{
	// Unzip
	unzFile zipfile = cocos2d::unzOpen(filePath);
	if(zipfile == NULL)
	{
		printf("%s: not found\n", filePath);
		
		return;
	}
	
	cocos2d::unz_global_info global_info;
	if(unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
	{
		printf("Could not read file global info\n");
		cocos2d::unzClose(zipfile);
		
		return;
	}
	
	uLong i;
	
	// Prepare dir
	std::vector<std::string> dirs = THStringUtil::split(destPath, '/');
	std::string dir = THFileUtil::getWriteablePath();
	
	char read_buffer[8192];
	
	for(i = 0; i < global_info.number_entry; ++i)
	{
		cocos2d::unz_file_info file_info;
		char filename[512];
		if(unzGetCurrentFileInfo(zipfile, &file_info, filename, 512, NULL, 0, NULL, 0) != UNZ_OK)
		{
			printf("Could not read file info\n");
			return;
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
					printf("Could not open file\n");
					cocos2d::unzClose(zipfile);
					return;
				}
				
				FILE *out = fopen(destFilePath.c_str(), "wb");
				if(out == NULL)
				{
					printf("Could not open destination file\n");
					cocos2d::unzCloseCurrentFile(zipfile);
					cocos2d::unzClose(zipfile);
					return;
				}
				
				int error = UNZ_OK;
				do
				{
					error = cocos2d::unzReadCurrentFile(zipfile, read_buffer, 8192);
					if(error < 0)
					{
						printf("Error %d\n", error);
						cocos2d::unzCloseCurrentFile(zipfile);
						cocos2d::unzClose(zipfile);
						return;
					}
					
					if(error > 0)
					{
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
				printf("Could not read next file\n");
				cocos2d::unzClose(zipfile);
				return;
			}
		}
	}
	
	cocos2d::unzClose(zipfile);
	
	
	printf("Delete file %s", filePath);
	if(remove(filePath) == -1)
	{
		printf("Delete downloaded zip file failed\n");
		return;
	}
}
