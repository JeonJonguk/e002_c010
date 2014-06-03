//
//  CJLMSExtensionJni.h
//  S001_Template
//
//  Created by Soonho Hong on 12. 11. 8..
//
//

#ifndef __CJSaveDataInterfaceJni__
#define __CJSaveDataInterfaceJni__

#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

/**
 * @author CJEducations
 * @brief cjextension jni class for android (add getChildBirthJNI func)
 * @version v1.0.4
 * @date 2012. 12. 27
 * @since v1.0.0
 */
extern "C"
{
    extern std::string getStringForKeyJNI(const char* key);
    extern std::string getAssetImagePathJNI(const char* pName);
    extern void createBaseDirJNI();
    extern std::string getHiddenDirPathJNI();
    extern std::string getResourceDirPathJNI(const char *szProjectIdenty);
}

#endif
