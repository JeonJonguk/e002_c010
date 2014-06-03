//
//  THFileUtil.h
//  Think
//
//  Created by pureye4u BX on 12. 8. 22..
//  Copyright CJ Educations 2012. All rights reserved.
//

#ifndef Think_THFileUtil_h
#define Think_THFileUtil_h

#include <string>

class THFileUtil
{
public:
	static bool existFile(const char* fileName);
	static std::string readFromFile(const char *fileName);
	static bool writeToFile(const char *fileName, const char *buffer, int length);
	static bool removeDirectory(const char* dirPath);
	static const char *getWriteablePath();
	static void unzip(const char *filePath, const char *destPath);
	
};

#endif
