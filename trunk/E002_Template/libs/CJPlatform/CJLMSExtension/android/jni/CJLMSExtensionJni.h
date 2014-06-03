//
//  CJLMSExtensionJni.h
//  S001_Template
//
//  Created by Soonho Hong on 12. 11. 8..
//
//

#ifndef __CJLMSExtensionJni__
#define __CJLMSExtensionJni__

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
    extern void finishRecoveryJNI();
    extern void callCertificationJNI();
    extern bool getNetworkStateJNI();
	extern void callYoutubeJNI(const char* youtubeId);
    extern long compareDateJNI(const char* startDate);
    
    
    extern int getWifiStrengthJNI();
    
    
    // ------------------ //
    // download data func //
    // ------------------ //

    /**
     * @author CJEducations
     * @brief get authkey for server
     * @version v1.0.0
     * @return auth key value (std::string)
     * @date 2012. 11. 28
     * @since v1.0.8
     */
    extern std::string getAuthKeyJNI();

    /**
     * @author CJEducations
     * @brief get redirect url for serve
     * @version v1.0.0
     * @return url value (std::string)
     * @date 2012. 11. 28
     * @since v1.0.8
     */
    extern std::string getURLJNI();

    /**
     * @author CJEducations
     * @brief get useragent for server
     * @version v1.0.0
     * @return useragent value (std::string)
     * @date 2012. 11. 28
     * @since v1.0.8
     */
    extern std::string getUserAgentJNI();

    /**
     * @author CJEducations
     * @brief get transaction id for server
     * @version v1.0.0
     * @return transaction id value (std::string)
     * @date 2012. 11. 28
     * @since v1.0.8
     */
    extern std::string getTransactionIdJNI();

    /**
     * @author CJEducations
     * @brief get interface id for server
     * @version v1.0.0
     * @return interface id value (std::string)
     * @date 2012. 11. 28
     * @since v1.0.8
     */
    extern std::string getInterfaceIdJNI();

    /**
     * @author CJEducations
     * @brief get interface version for server
     * @version v1.0.0
     * @return interface version value (std::string)
     * @date 2012. 11. 28
     * @since v1.0.8
     */
    extern std::string getInterfaceVerJNI();

    /**
     * @author CJEducations
     * @brief get request time for server
     * @version v1.0.0
     * @return request time value (std::string)
     * @date 2012. 11. 28
     * @since v1.0.8
     */
    extern std::string getRequestTimeJNI();

    // ------------------ //
    // file system method //
    // ------------------ //
    
    extern long long getFileSizeJNI(const char* path);
    extern bool checkSDCardAvailableJNI();
    extern long long getFreeSpaceJNI();
    extern void checkStorageSizeJNI();
    extern bool removeSaveFileJNI(const char* path);
    
    // ----------------------- //
    // get account info method //
    // ----------------------- //
    
    /**
     * @author CJEducations
     * @brief get current child id on android device
     * @version v1.0.0
     * @return child id string value (std::string)
     * @date 2012. 11. 28
     * @since v1.0.2
     */
    extern std::string getChildIdJNI();
    
    /**
     * @author CJEducations
     * @brief get current child name on android device
     * @version v1.0.0
     * @return child name string value (std::string)
     * @date 2012. 11. 28
     * @since v1.0.2
     */
    extern std::string getChildNameJNI();
    
    /**
     * @author CJEducations
     * @brief get current child birth day on android device
     * @version v1.0.0
     * @return child birth day string value (std::string)
     * @date 2012. 12. 27
     * @since v1.0.4
     */
    extern std::string getChildBirthJNI();
    
    /**
     * @author CJEducations
     * @brief get current child image on android device
     * @version v1.0.0
     * @return child image string value (std::string)
     * @date 2012. 11. 28
     * @since v1.0.2
     */
    extern std::string getChildImageJNI();
    
    // --------------- //
    // set mail method //
    // --------------- //
    
    extern void setMailFileJNI(const char* path);
    extern void setMailTitleJNI(const char* title);
    
    // ---------------- //
    // init list method //
    // ---------------- //
    
    /**
     * @author CJEducations
     * @brief link Cocos2dxActivity class's initStepList func in android project
     * @version v1.0.0
     * @date 2012. 11. 27
     * @since v1.0.1
     */
    extern void initStepListJNI();
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's initContentList func in android project
     * @version v1.0.0
     * @date 2012. 11. 27
     * @since v1.0.1
     */
    extern void initContentListJNI();
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's initLearnList func in android project
     * @version v1.0.0
     * @date 2012. 11. 27
     * @since v1.0.1
     */
    extern void initLearnListJNI();
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's initGradeList func in android project
     * @version v1.0.0
     * @date 2012. 12. 17
     * @since v1.0.3
     */
    extern void initGradeListJNI();
    
    // ------------------ //
    // init struct method //
    // ------------------ //
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's initStep func in android project
     * @version v1.0.0
     * @date 2012. 11. 27
     * @since v1.0.1
     */
    extern void initStepJNI();
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's initContent func in android project
     * @version v1.0.0
     * @date 2012. 11. 27
     * @since v1.0.1
     */
    extern void initContentJNI();
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's initLearn func in android project
     * @version v1.0.0
     * @date 2012. 11. 27
     * @since v1.0.1
     */
    extern void initLearnJNI();
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's initGrade func in android project
     * @version v1.0.0
     * @date 2012. 12. 17
     * @since v1.0.3
     */
    extern void initGradeJNI();
    
    // --------------- //
    // add list method //
    // --------------- //
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's addStep func in android project
     * @version v1.0.0
     * @date 2012. 11. 27
     * @since v1.0.1
     */
    extern void addStepJNI();
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's addContent func in android project
     * @version v1.0.0
     * @date 2012. 11. 27
     * @since v1.0.1
     */
    extern void addContentJNI();
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's addLearn func in android project
     * @version v1.0.0
     * @date 2012. 11. 27
     * @since v1.0.1
     */
    extern void addLearnJNI(unsigned int childID);
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's addGrade func in android project
     * @version v1.0.0
     * @date 2012. 12. 17
     * @since v1.0.3
     */
    extern void addGradeJNI();
    
    // ---------------------- //
    // set step struct method //
    // ---------------------- //
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's setStepCount func in android project
     * @version v1.0.0
     * @date 2012. 11. 27
     * @since v1.0.1
     */
    extern void setStepCountJNI(unsigned int nCount);
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's setStepKey func in android project
     * @version v1.0.0
     * @date 2012. 11. 27
     * @since v1.0.1
     */
    extern void setStepKeyJNI(const char* szKey);
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's setStepStartDate func in android project
     * @version v1.0.0
     * @date 2012. 11. 27
     * @since v1.0.1
     */
    extern void setStepStartDateJNI(const char* szStartDate);
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's setStepEndDate func in android project
     * @version v1.0.0
     * @date 2012. 11. 27
     * @since v1.0.1
     */
    extern void setStepEndDateJNI(const char* szEndDate);
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's setStepExtra func in android project
     * @version v1.0.0
     * @date 2012. 11. 27
     * @since v1.0.1
     */
    extern void setStepExtraJNI(const char* szExtra);
    
    // ------------------------- //
    // set content struct method //
    // ------------------------- //
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's setContentCode func in android project
     * @version v1.0.0
     * @date 2012. 11. 27
     * @since v1.0.1
     */
    extern void setContentCodeJNI(const char* szContentCode);
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's setContentGrade func in android project (remove param)
     * @version v1.0.1
     * @date 2012. 12. 17
     * @since v1.0.1
     */
    extern void setContentGradeJNI();
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's setContentExtra func in android project
     * @version v1.0.0
     * @date 2012. 11. 27
     * @since v1.0.1
     */
    extern void setContentExtraJNI(const char* szExtra);
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's setContentList func in android project
     * @version v1.0.0
     * @date 2012. 11. 27
     * @since v1.0.1
     */
    extern void setContentListJNI();
    
    // ----------------------- //
    // set learn struct method //
    // ----------------------- //
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's setLearnPKGName func in android project
     * @version v1.0.0
     * @date 2012. 11. 27
     * @since v1.0.1
     */
    extern void setLearnPKGNameJNI(const char* szPKGName);
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's setLearnCompleteDate func in android project
     * @version v1.0.0
     * @date 2012. 11. 27
     * @since v1.0.1
     */
    extern void setLearnCompleteDateJNI(const char* szCompleteDate);
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's setLearnList func in android project
     * @version v1.0.0
     * @date 2012. 11. 27
     * @since v1.0.1
     */
    extern void setLearnListJNI();
    
    // ----------------------- //
    // set grade struct method //
    // ----------------------- //
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's setGrade func in android project
     * @version v1.0.0
     * @date 2012. 12. 17
     * @since v1.0.3
     */
    extern void setGradeJNI(unsigned int iGrade);
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's setGradeDate func in android project
     * @version v1.0.0
     * @date 2012. 12. 17
     * @since v1.0.3
     */
    extern void setGradeDateJNI(const char* szWriteDate);
    
    extern void setGradeExtraJNI(const char* szExtra);
    
    // --------------------- //
    // send to server method //
    // --------------------- //
    
    /**
     * @author CJEducations
     * @brief link cocos2dxActivity class's sendLMSCenter func in android project
     * @version v1.0.0
     * @date 2012. 11. 27
     * @since v1.0.1
     */
    extern unsigned int sendLMSCenterJNI();
    
    extern unsigned int sendMailJNI(const char* text);
    
    // ----------------- //
    // get string method //
    // ----------------- //
    
    /**
     * @author CJEducations
     * @brief get current date&time on android device
     * @version v1.0.0
     * @return date&time string value (std::string)
     * @date 2012. 11. 20
     * @since v1.0.0
     */
    extern std::string getDeviceDateTimeJNI();
    
    /**
     * @author CJEducations
     * @brief get complete date&time on android device
     * @version v1.0.0
     * @param packageIndex : package define number (unsigned int)
     * @return date&time string value (std::string)
     * @date 2012. 11. 20
     * @since v1.0.0
     */
    extern std::string getTargetDateTimeJNI(unsigned int packageIndex);
    
    extern std::string getDiffDateJNI(const char* date, int days);
    
    extern void showThinkleStoreJNI();
    extern void showBrowserJNI(const char *szUrl);
    
	extern void endCJJNI();
}

#endif
