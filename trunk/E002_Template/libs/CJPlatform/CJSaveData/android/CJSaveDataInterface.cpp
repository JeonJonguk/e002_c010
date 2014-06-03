//
//  CJSaveDataInterface.cpp
//  S001_Template
//
//  Created by Soonho Hong on 12. 11. 8..
//
//

#include "CJSaveDataInterface.h"
#include "jni/CJSaveDataInterfaceJni.h"


static CJSaveDataInterface * s_pInstance = 0;

CJSaveDataInterface::CJSaveDataInterface()
{
    
}

CJSaveDataInterface::~CJSaveDataInterface()
{

}

CJSaveDataInterface* CJSaveDataInterface::sharedInstance()
{
    if (! s_pInstance)
    {
        s_pInstance = new CJSaveDataInterface();
    }
    
    return s_pInstance;
}

void CJSaveDataInterface::releaseInstance()
{
//    endCJJNI();
}

std::string CJSaveDataInterface::saveAssetImageData(const char* key)
{
    return getAssetImagePathJNI(key);
}

void CJSaveDataInterface::createBaseDir()
{
    createBaseDirJNI();
}

std::string CJSaveDataInterface::getHiddenDirPath()
{
    return getHiddenDirPathJNI();
}

std::string CJSaveDataInterface::getResourceDirPath(const char *szProjectIdenty)
{
    return getResourceDirPathJNI(szProjectIdenty);
}
