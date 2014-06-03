//
//  CJLMSExtension.h
//  S001_Template
//
//  Created by Soonho Hong on 12. 11. 8..
//
//

#ifndef CJSaveDataInterface_h
#define CJSaveDataInterface_h

#include <stddef.h>
#include <sstream>

class CJSaveDataInterface
{
public:
    CJSaveDataInterface();
    ~CJSaveDataInterface();
    
    static CJSaveDataInterface* sharedInstance();
    
    static void releaseInstance();
    
    std::string saveAssetImageData(const char* key);
    
    // create hidden & resource folder, and copy default db file
    void createBaseDir();
    
    // return hidden folder path in sdcard
    std::string getHiddenDirPath();
    
    // return resource folder path in sdcard
    std::string getResourceDirPath(const char *szProjectIdenty);


};

#endif
