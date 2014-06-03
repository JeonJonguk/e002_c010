//
//  THDownloadThread.cpp
//  Think
//
//  Created by pureye4u BX on 12. 6. 14..
//  Copyright CJ Educations 2012. All rights reserved.
//

#include "THDownloadThread.h"
#include "THDownloadStatus.h"
#include "THStringUtil.h"
#include "THResourceUtils.h"
#include "THFileUtil.h"

#include "support/zip_support/unzip.h"
#include "cocos2d.h"
#include <stdio.h>
#include <sys/stat.h>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <sys/xattr.h>
#include <curl/curl.h>
#else
#include "platform/third_party/android/prebuilt/libcurl/include/curl/curl.h"
#endif

static THDownloadThread *s_currentThread = NULL;
static CURL *s_curl;
static FILE *s_fp;

//static pthread_mutex_t s_lock = PTHREAD_MUTEX_INITIALIZER;
//static pthread_cond_t s_cond = PTHREAD_COND_INITIALIZER;
static int s_play = 0;


typedef struct S_dl_byte_data
{
	double new_bytes_received;
	double existing_filesize;
} dl_byte_data, *pdl_byte_data;

static int dl_progress(pdl_byte_data pdata, double dltotal, double dlnow, double ultotal, double ulnow)
{
	if(dltotal && dlnow)
	{
		pdata->new_bytes_received = dlnow;
		dltotal += pdata->existing_filesize;
		dlnow += pdata->existing_filesize;
//		printf("===== dl:%3.0f%% total:%.0f received:%.0f\r", 100 * dlnow / dltotal, dltotal, dlnow);
		s_currentThread->progress(dlnow, dltotal);
		fflush(stdout);
	}
	
	return 0;
}

static size_t dl_write(void *buffer, size_t size, size_t nmemb, void *stream)
{
	return fwrite(buffer, size, nmemb, (FILE *)stream);
}

THDownloadThread *THDownloadThread::getCurrentThread()
{
	if(s_currentThread == NULL)
	{
		s_currentThread = new THDownloadThread();
	}
	
	return s_currentThread;
}

void THDownloadThread::destroy()
{
	if(s_currentThread != NULL)
	{
		s_currentThread->join();
		pthread_exit(NULL);
		delete s_currentThread;
		s_currentThread = NULL;
	}
}

static int hndProgress(void *ptr, double totalToDownload, double nowDownloaded, double totalToUpload, double nowUploaded)
{
	s_currentThread->progress(nowDownloaded, totalToDownload);
	
	return 0;
}

THDownloadThread::THDownloadThread(int num)
{
	m_num = num;
}

THDownloadThread::~THDownloadThread()
{
	m_delegate = NULL;
}

void THDownloadThread::download(const char *fileName, long long currentSize, long fullSize, const char *URL, const char *destination, THDownloadDelegate *delegate)
{
	m_pause = 0;
	m_total = 0;
	m_current = 0;
	m_current_add = (double)currentSize;
	m_currentSize = currentSize;
	m_fullSize = fullSize;
	m_checkWaiting = false;
	m_downloadCompleted = false;
	m_fileName = fileName;
	m_URL = URL;
	m_destination = destination;
	m_delegate = delegate;
	
	this->start();
//	this->play();
}

//void THDownloadThread::clear()
//{
//	m_total = 0;
//	m_current = 0;
//	m_fileName.clear();
//	m_URL.clear();
//	m_destination.clear();
//	m_delegate = NULL;
//}

void THDownloadThread::progress(double current, double total)
{
//	pthread_mutex_lock(&s_lock);
//	while(!s_play)
//	{
//		pthread_cond_wait(&s_cond, &s_lock);
//	}
//	pthread_mutex_unlock(&s_lock);
	
	if(m_total < 0.001)
	{
		m_total = total;
	}

	if(m_current < current + m_current_add)
	{
		if(m_checkWaiting)
		{
			m_delegate->setStatus(THDownloadStatusDownloading);
			m_checkWaiting = false;
		}

		m_current = current + m_current_add;
		m_total = total + m_current_add;

		int progress = MAX(0, (int)((m_current / m_total) * 100));
//		if(s_play)
//		{
//			printf("p: %d = %f / %f\n", progress, (float)m_current, (float)m_total);
//		}
		//	printf("#");
		m_delegate->setProgress(progress);
	}
	fflush(stdout);
}

static size_t writeString(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string *)userp)->append((char *)contents, size *nmemb);
	return size *nmemb;
}

int THDownloadThread::run()
{
	std::string masterPath = THFileUtil::getWriteablePath();
	std::string outfileName = masterPath;
	outfileName.append(m_fileName.c_str());
	
	int downloaded = this->startDownload(outfileName.c_str());
//	printf("===== finish retval: %d", downloaded);
	
	int retrycount = 0;
	if(downloaded < 0)
	{
		switch(downloaded)
		{
			default:
			case -5:
				while(downloaded < 0 && retrycount < 2)
				{
					downloaded = this->startDownload(outfileName.c_str());
					retrycount++;
				}
				if(downloaded < 0)
				{
//					printf("===== -5\n");
					m_delegate->error(THDownloadStatusNetworkError, "===== Resume download error");
					return downloaded;
				}
				break;
		}
	}
	m_downloadCompleted = true;

    
    
	THResourceUtils::getCurrentUtils()->removeContent(THResourceUtils::getCurrentUtils()->getDownloadingContentData().ID);
    this->unpackFile(outfileName.c_str());

	
	return 1;
}


int THDownloadThread::unpackFile(const char *fileName)
{
//	printf("===== UNpack: %s", fileName);
	
	// Unzip
	m_delegate->setStatus(THDownloadStatusInstalling);
	unzFile zipfile = cocos2d::unzOpen(fileName);
	if(zipfile == NULL)
	{
//		cocos2d::CCLog("%s: not found\n", fileName);
        remove(fileName);
		m_delegate->error(THDownloadStatusInstallError, "File not found");
		return false;
	}
	
	cocos2d::unz_global_info global_info;
	if(unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
	{
//		cocos2d::CCLog("Could not read file global info\n");
		cocos2d::unzClose(zipfile);
        remove(fileName);
		m_delegate->error(THDownloadStatusInstallError, "Could not read file global info");
		return false;
	}
	
	uLong i;
	
	// Prepare dir
	std::vector<std::string> dirs = THStringUtil::split(m_destination.c_str(), '/');
	std::string dir = THFileUtil::getWriteablePath();
	
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//	//shchoi, 2012.10.09, change path to 'root' for Android
//	for(i = 0; i < dirs.size(); i++)
//	{
//		dir.append(dirs[i].c_str());
//		
//		if(!THFileUtil::existFile(dir.c_str()))
//		{
//			mkdir(dir.c_str(), 0777);
//		}
//		dir.append("/");
//	}
//	
//	// Add skip backup attribute to item at URL
//	const char *attrName = "com.apple.MobileBackup";
//	u_int8_t attrValue = 1;
//	
//	int result = setxattr(dir.c_str(), attrName, &attrValue, sizeof(attrValue), 0, 0);
//	if(result != 0)
//	{
//		printf("Could not ad skip backup attribute to item at URL");
//		return false;
//	}
//#endif
	
	char read_buffer[8192];
	
	for(i = 0; i < global_info.number_entry; ++i)
	{
		cocos2d::unz_file_info file_info;
		char filename[512];
		if(unzGetCurrentFileInfo(zipfile, &file_info, filename, 512, NULL, 0, NULL, 0) != UNZ_OK)
		{
//			cocos2d::CCLog("Could not read file info\n");
            remove(fileName);
			m_delegate->error(THDownloadStatusInstallError, "Could not read file info");
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
                    remove(fileName);
					m_delegate->error(THDownloadStatusInstallError, "Could not open file");
					return 0;
				}
				
				FILE *out = fopen(destFilePath.c_str(), "wb");
				if(out == NULL)
				{
//					cocos2d::CCLog("Could not open destination file\n");
					cocos2d::unzCloseCurrentFile(zipfile);
					cocos2d::unzClose(zipfile);
                    remove(fileName);
					m_delegate->error(THDownloadStatusInstallError, "Could not open destination file");
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
                        remove(fileName);
						m_delegate->error(THDownloadStatusInstallError, "Extracting file error");
						return 0;
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
//				cocos2d::CCLog("Could not read next file\n");
				cocos2d::unzClose(zipfile);
                remove(fileName);
				m_delegate->error(THDownloadStatusInstallError, "Could not read next file");
				return 0;
			}
		}
	}
	
	cocos2d::unzClose(zipfile);
	
	if(remove(fileName) == -1)
	{
//		cocos2d::CCLog("Delete downloaded zip file failed\n");
		m_delegate->error(THDownloadStatusInstallError, "Delete zip file error");
		return 0;
	}
	
	m_delegate->end();
	
	return 1;
	
	
	
//	CURL *curl;
//	FILE *fp;
//	
//	int ret;
//	double dl_size;
//	long http_response;
//	
//	CURLcode res;
//	std::string masterPath = THFileUtil::getWriteablePath();
//	std::string outfileName = masterPath;
//	outfileName.append(m_fileName.c_str());
//	
//	
//	
//	long dl_lowspeed_bytes = 1000;
//	long dl_lowspeed_time = 10;
//	
//	struct stat st = {0};
//	if(stat(outfileName.c_str(), &st))
//	{
//		printf("===== st.st_size:[%ld]\n", (long)st.st_size);
//	}
//	
//	
//	curl_global_init(CURL_GLOBAL_DEFAULT);
//	s_curl = curl_easy_init();
//	if(s_curl)
//	{
//		s_fp = fopen(outfileName.c_str(), "wb");
//		
//		struct curl_slist *headers = NULL;
//		headers = curl_slist_append(headers, "User-Agent: FireFox");
//		curl_easy_setopt(s_curl, CURLOPT_HTTPHEADER, headers);
//		curl_easy_setopt(s_curl, CURLOPT_URL, m_URL.c_str());
//		curl_easy_setopt(s_curl, CURLOPT_VERBOSE, 1);
//		curl_easy_setopt(s_curl, CURLOPT_FOLLOWLOCATION, 1);
//		curl_easy_setopt(s_curl, CURLOPT_SSL_VERIFYPEER, 0);
//		curl_easy_setopt(s_curl, CURLOPT_SSL_VERIFYHOST, 0);
//		curl_easy_setopt(s_curl, CURLOPT_LOW_SPEED_LIMIT, dl_lowspeed_bytes);
//		curl_easy_setopt(s_curl, CURLOPT_LOW_SPEED_TIME, dl_lowspeed_time);
//		curl_easy_setopt(s_curl, CURLOPT_WRITEFUNCTION, fwrite);
//		curl_easy_setopt(s_curl, CURLOPT_WRITEDATA, s_fp);
////		curl_easy_setopt(s_curl, CURLOPT_RESUME_FROM, st.st_size);
//		curl_easy_setopt(s_curl, CURLOPT_NOPROGRESS, false);
//		curl_easy_setopt(s_curl, CURLOPT_PROGRESSFUNCTION, hndProgress);
//		
//		if(CURLE_OK != (res = curl_easy_perform(s_curl)))
//		{
//			printf("===== curl_retval:[%d]\n", res);
//			
//			switch((int)res)
//			{
//				case CURLE_WRITE_ERROR:
//					break;
//					
//				default:
//					ret = 0;
//			}
//			
//			curl_easy_getinfo(s_curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &dl_size);
//			printf("===== CURLINFO_CONTENT_LENGTH_DOWNLOAD:%f\n", dl_size);
//			
//			res = curl_easy_getinfo(s_curl, CURLINFO_RESPONSE_CODE, &http_response);
//			printf("===== CURLINFO_RESPONSE_CODE:%ld\n", http_response);
//			
//			switch(http_response)
//			{
//				case 0:
//					break;
//					
//				case 200:
//					break;
//					
//				case 206:
//				case 416:
//					printf("===== err 206 or 416\n");
//					break;
//					
//				default:
//					ret = 0;
//			}
//		}
//		else
//		{
//			printf("===== done\n");
//			ret = 2;
//		}
//		
//		if(s_fp)
//		{
//			fclose(s_fp);
//		}
//		
//		if(s_curl)
//		{
//			curl_slist_free_all(headers);
//			curl_easy_cleanup(s_curl);
//		}
//	}
//	
//	// Unzip
//	m_delegate->setStatus(THDownloadStatusInstalling);
//	unzFile zipfile = cocos2d::unzOpen(outfileName.c_str());
//	if(zipfile == NULL)
//	{
//		printf("%s: not found\n", outfileName.c_str());
//		m_delegate->error(0, "File not found");
//		return false;
//	}
//	
//	cocos2d::unz_global_info global_info;
//	if(unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
//	{
//		printf("Could not read file global info\n");
//		cocos2d::unzClose(zipfile);
//		m_delegate->error(0, "Could not read file global info");
//		return false;
//	}
//	
//	uLong i;
//	
//	// Prepare dir
//	std::vector<std::string> dirs = THStringUtil::split(m_destination.c_str(), '/');
//	std::string dir = masterPath.c_str();
//	
//	for(i = 0; i < dirs.size(); i++)
//	{
//		dir.append(dirs[i].c_str());
//		
//		if(!THFileUtil::existFile(dir.c_str()))
//		{
//			mkdir(dir.c_str(), 0777);
//		}
//		dir.append("/");
//	}
//	
//	// Add skip backup attribute to item at URL
//	const char *attrName = "com.apple.MobileBackup";
//	u_int8_t attrValue = 1;
//	
//	int result = setxattr(dir.c_str(), attrName, &attrValue, sizeof(attrValue), 0, 0);
//	if(result != 0)
//	{
//		printf("Could not ad skip backup attribute to item at URL");
//		return false;
//	}
//	
//	char read_buffer[8192];
//	
//	for(i = 0; i < global_info.number_entry; ++i)
//	{
//		cocos2d::unz_file_info file_info;
//		char filename[512];
//		if(unzGetCurrentFileInfo(zipfile, &file_info, filename, 512, NULL, 0, NULL, 0) != UNZ_OK)
//		{
//			printf("Could not read file info\n");
//			m_delegate->error(0, "Could not read file info");
//			return 0;
//		}
//		
//		std::string destFilePath = dir.c_str();
//		destFilePath.append(filename);
//		
//		const size_t filename_length = strlen(destFilePath.c_str());
//		if(destFilePath.at(filename_length - 1) == '/')
//		{
//			if(destFilePath.find("__MACOSX") == -1)
//			{
//				mkdir(destFilePath.c_str(), 0777);
//			}
//		}
//		else
//		{
//			if(destFilePath.find("__MACOSX") == -1)
//			{
//				if(cocos2d::unzOpenCurrentFile(zipfile) != UNZ_OK)
//				{
//					printf("Could not open file\n");
//					cocos2d::unzClose(zipfile);
//					m_delegate->error(0, "Could not open file");
//					return 0;
//				}
//				
//				FILE *out = fopen(destFilePath.c_str(), "wb");
//				if(out == NULL)
//				{
//					printf("Could not open destination file\n");
//					cocos2d::unzCloseCurrentFile(zipfile);
//					cocos2d::unzClose(zipfile);
//					m_delegate->error(0, "Could not open destination file");
//					return 0;
//				}
//				
//				int error = UNZ_OK;
//				do
//				{
//					error = cocos2d::unzReadCurrentFile(zipfile, read_buffer, 8192);
//					if(error < 0)
//					{
//						printf("Error %d\n", error);
//						cocos2d::unzCloseCurrentFile(zipfile);
//						cocos2d::unzClose(zipfile);
//						m_delegate->error(0, "Extracting file error");
//						return 0;
//					}
//					
//					if(error > 0)
//					{
//						fwrite(read_buffer, error, 1, out);
//					}
//				}while(error > 0);
//				
//				fclose(out);
//			}
//		}
//		
//		cocos2d::unzCloseCurrentFile(zipfile);
//		
//		if((i + 1) < global_info.number_entry)
//		{
//			if(cocos2d::unzGoToNextFile(zipfile) != UNZ_OK)
//			{
//				printf("Could not read next file\n");
//				cocos2d::unzClose(zipfile);
//				m_delegate->error(0, "Could not read next file");
//				return 0;
//			}
//		}
//	}
//	
//	cocos2d::unzClose(zipfile);
//	
//	if(remove(outfileName.c_str()) == -1)
//	{
//		printf("Delete downloaded zip file failed\n");
//		m_delegate->error(0, "Delete zip file error");
//		return 0;
//	}
//	
//	m_delegate->end();
//	
//	return 1;
}

int THDownloadThread::startDownload(const char *outfileName)
{
	// Download
	m_delegate->begin();
	printf("Download from: %s\n", m_URL.c_str());
	m_delegate->setStatus(THDownloadStatusDownloading);
	
//////////////////////////////////////////////////////////////////////////////////////////////////
	
//	CURL *curl;
//	FILE *fp;
	
	int ret;
	double dl_size;
	long http_response;
	
	CURLcode res;
	
	
	
	long dl_lowspeed_bytes = 1000;
	long dl_lowspeed_time = 5;
	
//	struct stat st = {0};
//	if(stat(outfileName, &st))
//	{
//		printf("===== st.st_size:[%ld]\n", (long)st.st_size);
//	}
	
	
	curl_global_init(CURL_GLOBAL_DEFAULT);
	s_curl = curl_easy_init();
	if(s_curl)
	{
		if (m_currentSize > 0) {
			s_fp = fopen(outfileName, "ab");
		} else {
			s_fp = fopen(outfileName, "wb");
		}

		//		m_current = 0;

		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "User-Agent: FireFox");
		if (m_currentSize > 0) {
			std::string range = "Range: bytes=";
			std::stringstream fileSize;
			fileSize << m_currentSize;
			range.append(fileSize.str());
			range.append("-");

			headers = curl_slist_append(headers, range.c_str());
		}
		curl_easy_setopt(s_curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(s_curl, CURLOPT_URL, m_URL.c_str());
		curl_easy_setopt(s_curl, CURLOPT_VERBOSE, 0);
		curl_easy_setopt(s_curl, CURLOPT_FOLLOWLOCATION, 1);
		curl_easy_setopt(s_curl, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(s_curl, CURLOPT_SSL_VERIFYHOST, 0);
		curl_easy_setopt(s_curl, CURLOPT_LOW_SPEED_LIMIT, dl_lowspeed_bytes);
		curl_easy_setopt(s_curl, CURLOPT_LOW_SPEED_TIME, dl_lowspeed_time);
		curl_easy_setopt(s_curl, CURLOPT_WRITEFUNCTION, fwrite);
		curl_easy_setopt(s_curl, CURLOPT_WRITEDATA, s_fp);
//		curl_easy_setopt(s_curl, CURLOPT_RESUME_FROM, st.st_size);
		curl_easy_setopt(s_curl, CURLOPT_NOPROGRESS, false);
		curl_easy_setopt(s_curl, CURLOPT_PROGRESSFUNCTION, hndProgress);
        curl_easy_setopt(s_curl, CURLOPT_NOSIGNAL, 1);

		curl_easy_pause(s_curl, CURLPAUSE_ALL);
		
		res = curl_easy_perform(s_curl);
		
		curl_easy_pause(s_curl, CURLPAUSE_CONT);
		
		if(CURLE_OK != res)
		{
//			printf("===== curl_retval:[%d]\n", res);
			
			switch((int)res)
			{
				case CURLE_WRITE_ERROR:
					break;
					
				default:
					ret = -1;
					break;
			}
			
			curl_easy_getinfo(s_curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &dl_size);
//			printf("===== CURLINFO_CONTENT_LENGTH_DOWNLOAD:%f\n", dl_size);
			
			res = curl_easy_getinfo(s_curl, CURLINFO_RESPONSE_CODE, &http_response);
//			printf("===== CURLINFO_RESPONSE_CODE:%ld\n", http_response);
			
			switch(http_response)
			{
				case 0:
					break;
					
				case 200:
					break;
					
				case 206:
				case 416:
//					printf("===== err 206 or 416\n");
					break;
					
				default:
					ret = -2;
					break;
			}
		}
		else
		{
//			printf("===== done\n");
			ret = 1;
		}
		
		if(s_fp)
		{
			fclose(s_fp);
		}
		
		if(s_curl)
		{
			curl_slist_free_all(headers);
			curl_easy_cleanup(s_curl);
		}
	}
	
	return ret;

	
	
//////////////////////////////////////////////////////////////////////////////////////////////////
	
	
//	CURLM *multi_handle;
////	CURL *curl;
////	FILE *fp;
//	CURLcode curl_retval;
//	int retval = 0;
//	int handle_count = 0;
//	double dl_bytes_remaining, dl_bytes_received;
//	dl_byte_data st_dldata = {0};
//	char curl_error_buf[CURL_ERROR_SIZE] = {"meh"};
//	
//	long dl_lowspeed_bytes = 1000;
//	long dl_lowspeed_time = 10;
//	
////	std::string masterPath = THFileUtil::getWriteablePath();
////	std::string outfileName = masterPath;
////	outfileName.append(m_fileName.c_str());
//	
//	struct stat st = {0};
//	
//	if(!(s_fp = fopen(outfileName, "ab")) || -1 == fstat(fileno(s_fp), &st))
//	{
//		return -1;
//	}
//	
//	if(curl_global_init(CURL_GLOBAL_DEFAULT))
//	{
//		return-2;
//	}
//	
//	if(!(multi_handle = curl_multi_init()))
//	{
//		return -3;
//	}
//	
//	if(!(s_curl = curl_easy_init()))
//	{
//		return -4;
//	}
//	
//	st_dldata.new_bytes_received = st_dldata.existing_filesize = st.st_size;
//	
//	
//	struct curl_slist *headers = NULL;
//	headers = curl_slist_append(headers, "User-Agent: FireFox");
//	curl_easy_setopt(s_curl, CURLOPT_HTTPHEADER, headers);
//	curl_easy_setopt(s_curl, CURLOPT_URL, m_URL.c_str());
////	curl_easy_setopt(s_curl, CURLOPT_VERBOSE, 1);
//	curl_easy_setopt(s_curl, CURLOPT_FOLLOWLOCATION, 1);
//	curl_easy_setopt(s_curl, CURLOPT_SSL_VERIFYPEER, 0);
//	curl_easy_setopt(s_curl, CURLOPT_SSL_VERIFYHOST, 0);
//	curl_easy_setopt(s_curl, CURLOPT_WRITEFUNCTION, dl_write);
//	curl_easy_setopt(s_curl, CURLOPT_PROGRESSFUNCTION, dl_progress);
//	curl_easy_setopt(s_curl, CURLOPT_PROGRESSDATA, &st_dldata);
//	curl_easy_setopt(s_curl, CURLOPT_NOPROGRESS, 0);
//	
//	curl_easy_setopt(s_curl, CURLOPT_LOW_SPEED_LIMIT, dl_lowspeed_bytes);
//	curl_easy_setopt(s_curl, CURLOPT_LOW_SPEED_TIME, dl_lowspeed_time);
//	
//	curl_easy_setopt(s_curl, CURLOPT_ERRORBUFFER, curl_error_buf);
//	
//	curl_easy_pause(s_curl, CURLPAUSE_ALL);
//	
//	do
//	{
//		if(st_dldata.new_bytes_received)
//		{
//			printf("===== resuming d/l..\n");
//			fflush(s_fp);
//			if(-1 == (retval = fstat(fileno(s_fp), &st)) || !(st_dldata.existing_filesize = st.st_size))
//			{
//				break;
//			}
//			printf("===== size:[%ld]\n", (long)st.st_size);
////			curl_easy_setopt(s_curl, CURLOPT_RESUME_FROM, (long)st.st_size);
//			st_dldata.new_bytes_received = 0;
//		}
//		printf("\n\n===== bytes already received:[%.0f]\n", st_dldata.existing_filesize);
//		
//		curl_multi_add_handle(multi_handle, s_curl);
//		
//		do
//		{
//			CURLMsg *pMsg;
//			int msgs_in_queue;
//			
//			while(CURLM_CALL_MULTI_PERFORM == curl_multi_perform(multi_handle, &handle_count));
//			
//			curl_easy_pause(s_curl, CURLPAUSE_CONT);
//			
//			while((pMsg = curl_multi_info_read(multi_handle, &msgs_in_queue)))
//			{
//				long http_response;
//				
//				printf("\n=====msgs_in_queue:[%d]\n", msgs_in_queue);
//				if(CURLMSG_DONE != pMsg->msg)
//				{
//					fprintf(stderr, "CURLMSG_DONE != pMsg->msg:[%d]\n", pMsg->msg);
//				}
//				else
//				{
//					printf("===== pMsg->data.result:[%d] meaning:[%s]\n", pMsg->data.result, curl_easy_strerror(pMsg->data.result));
//					if(CURLE_OK != pMsg->data.result)
//					{
//						printf("===== curl_error_buf:[%s]\n", curl_error_buf);
//					}
//					switch((int)pMsg->data.result)
//					{
//						case CURLE_OK:
//							printf("===== CURLE_OK: ");
//							curl_easy_getinfo(pMsg->easy_handle, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &dl_bytes_remaining);
//							curl_easy_getinfo(pMsg->easy_handle, CURLINFO_SIZE_DOWNLOAD, &dl_bytes_received);
//							if(dl_bytes_remaining == dl_bytes_received)
//							{
//								printf("===== our work is done here;)\n");
//								retval = 1;
//							}
//							else
//							{
//								printf("===== st_dldata.new_bytes_received[%f]\n", st_dldata.new_bytes_received);
//								printf("===== dl_bytes_received[%f] dl_bytes_remaining[%f]\n", dl_bytes_received, dl_bytes_remaining);
//								retval = dl_bytes_received < dl_bytes_remaining ? 0 : -5;
//							}
//							break;
//							
//						case CURLE_COULDNT_CONNECT:
//						case CURLE_OPERATION_TIMEDOUT:
//						case CURLE_COULDNT_RESOLVE_HOST:
//							printf("===== CURMESSAGE switch handle_count:[%d]\n", handle_count);
//							break;
//							
//						default:
//							printf("===== CURMESSAGE default\n");
//							handle_count = 0;
//							retval = -5;
//							
//					};
//					
//					curl_retval = curl_easy_getinfo(pMsg->easy_handle, CURLINFO_RESPONSE_CODE, &http_response);
//					printf("===== CURLINFO_RESPONSE_CODE HTTP:[%ld]\n", http_response);
//					switch(http_response)
//					{
//						case 0:
//						case 200:
//						case 206:
//							break;
//							
//						case 416:
//							printf("===== HTTP416: either the d/l is already complete or the http server cannot d/l a range\n");
//							retval = 2;
//							
//						default:
//							handle_count = 0;
//							retval = -6;
//					};
//				}
//			}
//			
//			if(handle_count)
//			{
//				fd_set fd_read = {0}, fd_write = {0}, fd_excep = {0};
//				struct timeval timeout = {5, 0};
//				int select_retval;
//				int fd_max;
//				
//				curl_multi_fdset(multi_handle, &fd_read, &fd_write, &fd_excep, &fd_max);
//				if(-1 == (select_retval = select(fd_max + 1, &fd_read, &fd_write, &fd_excep, &timeout)))
//				{
//					fprintf(stderr, "select error :(\n");
//					handle_count = 0;
//					retval = -7;
//					break;
//				}
//				else
//				{
//					//
//				}
//			}
//		}
//		while(handle_count);
//			
//		curl_multi_remove_handle(multi_handle, s_curl);
//		printf("===== continue from here?\n");
//		getchar();
//	}
//	while(retval == 0);
//	
//	curl_multi_cleanup(multi_handle);
//	curl_slist_free_all(headers);
//	curl_easy_cleanup(s_curl);
//	curl_global_cleanup();
//	if(s_fp)
//	{
//		fclose(s_fp);
//	}
//	
//	return retval;
//////////////////////////////////////////////////////////////////////////////////////////////////
}

void THDownloadThread::play()
{
	if(!m_downloadCompleted)
	{
//	printf("===== THDownloadThread::play()\n");
//	pthread_mutex_lock(&s_lock);
		s_play = 1;
		
		m_delegate->setStatus(THDownloadStatusWaitDownloading);
		m_checkWaiting = true;
		
		
		curl_easy_pause(s_curl, CURLPAUSE_CONT);
	}
//	long http_response;
//	CURLcode res;
//	
//	
//	res = curl_easy_pause(s_curl, CURLPAUSE_CONT);
//	
//	
//	if(CURLE_OK != res)
//	{
//		printf("===== CURL Resume ERROR curl_retval:[%d]\n", res);
//		
//		switch((int)res)
//		{
//			case CURLE_WRITE_ERROR:
//				break;
//				
//			default:
//				break;
//		}
//	
//		res = curl_easy_getinfo(s_curl, CURLINFO_RESPONSE_CODE, &http_response);
//		printf("===== CURLINFO_RESPONSE_CODE:%ld\n", http_response);
//		
//		switch(http_response)
//		{
//			case 0:
//				break;
//				
//			case 200:
//				break;
//				
//			case 206:
//			case 416:
//				printf("===== err 206 or 416\n");
//				break;
//				
//			default:
//				break;
//		}
//	}
//	else
//	{
//		printf("===== Continue");
//	}
	
//	printf("===== fp\n");
//	if(s_fp)
//	{
//		printf("===== fp live\n");
//	}
//	else
//	{
//		printf("===== fp death\n");
//	}
	
//	std::string masterPath = THFileUtil::getWriteablePath();
//	std::string outfileName = masterPath;
//	outfileName.append(m_fileName.c_str());
//	
//	struct stat st = {0};
//	
//	if(!(s_fp = fopen(outfileName.c_str(), "ab")) || -1 == fstat(fileno(s_fp), &st))
//	{
//		printf("===== fp error\n");
//	}
	
//	cocos2d::CCLog("===== fp: %s", s_fp);
//	printf("===== fp: %s", s_fp);
//	curl_easy_pause(s_curl, CURLPAUSE_CONT);

//	curl_easy_reset(s_curl);
//	if(s_curl)
//	{
//		FILE *fp;
//		CURLcode res;
//		std::string masterPath = THFileUtil::getWriteablePath();
//		std::string outfileName = masterPath;
//		outfileName.append(m_fileName.c_str());
//		
//		fp = fopen(outfileName.c_str(), "wb");
//		
//		struct curl_slist *headers = NULL;
//		headers = curl_slist_append(headers, "User-Agent: FireFox");
//		curl_easy_setopt(s_curl, CURLOPT_HTTPHEADER, headers);
//		curl_easy_setopt(s_curl, CURLOPT_URL, m_URL.c_str());
//		curl_easy_setopt(s_curl, CURLOPT_FOLLOWLOCATION, 1);
//		curl_easy_setopt(s_curl, CURLOPT_SSL_VERIFYPEER, 0);
//		curl_easy_setopt(s_curl, CURLOPT_SSL_VERIFYHOST, 0);
//		curl_easy_setopt(s_curl, CURLOPT_WRITEFUNCTION, fwrite);
//		curl_easy_setopt(s_curl, CURLOPT_WRITEDATA, fp);
//		curl_easy_setopt(s_curl, CURLOPT_NOPROGRESS, false);
//		curl_easy_setopt(s_curl, CURLOPT_PROGRESSFUNCTION, hndProgress);
//		
//		res = curl_easy_perform(s_curl);
//		
//		fclose(fp);
//		
//		curl_slist_free_all(headers);
//		curl_easy_cleanup(s_curl);
//	}
//	curl_easy_reset(s_curl);
//	pthread_cond_signal(&s_cond);
//	pthread_mutex_unlock(&s_lock);
}

void THDownloadThread::pause()
{
	//	pthread_mutex_lock(&s_lock);
	if(!m_downloadCompleted)
	{
		s_play = 0;
	
	
		curl_easy_pause(s_curl, CURLPAUSE_ALL);
	}
	
//	curl_easy_reset(s_curl);
//	
//	fclose(s_fp);
//	
//	curl_easy_cleanup(s_curl);
	
//	curl_easy_cleanup(s_curl);
//	pthread_mutex_unlock(&s_lock);
}

