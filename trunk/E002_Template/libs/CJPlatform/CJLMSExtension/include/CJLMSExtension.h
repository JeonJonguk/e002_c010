//
//  CJLMSExtension.h
//  S001_Template
//
//  Created by Soonho Hong on 12. 11. 8..
//
//

#ifndef CJLMSExtension_h
#define CJLMSExtension_h

#include <stddef.h>
#include <sstream>

namespace LMSExtension {
    /**
     * @author CJEducations
     * @brief platform extension lib for lms (add download func)
     * @version v1.0.8
     * @date 2013. 04. 17
     * @since v1.0.0
     */
    class CJLMSExtension
    {
    public:
        CJLMSExtension();
        ~CJLMSExtension();
        
        static CJLMSExtension* sharedInstance();
        
        static void releaseInstance();
        
        /**
         * @author CJEducations
         * @brief get hidden cjeducations's directory path
         * @version v1.0.0
         * @date 2013. 04. 16
         * @since v1.0.7
         */
        std::string getDBPath();
        
        /**
         * @author CJEducations
         * @brief call certifications popup - call luncher's intent
         * @version v1.0.0
         * @date 2013. 04. 16
         * @since v1.0.7
         */
        void callCertification();
        
        void callYoutube(const char* youtubeId);
        
        long compareDate(const char* startDate);
		
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
        std::string getAuthKey();
        
        /**
         * @author CJEducations
         * @brief get redirect url for server
         * @version v1.0.0
         * @return url value (std::string)
         * @date 2012. 11. 28
         * @since v1.0.8
         */
        std::string getURL();
        
        /**
         * @author CJEducations
         * @brief get useragent for server
         * @version v1.0.0
         * @return useragent value (std::string)
         * @date 2012. 11. 28
         * @since v1.0.8
         */
        std::string getUserAgent();
        
        /**
         * @author CJEducations
         * @brief get transaction id for server
         * @version v1.0.0
         * @return transaction id value (std::string)
         * @date 2012. 11. 28
         * @since v1.0.8
         */
        std::string getTransactionId();
        
        /**
         * @author CJEducations
         * @brief get interface id for server
         * @version v1.0.0
         * @return interface id value (std::string)
         * @date 2012. 11. 28
         * @since v1.0.8
         */
        std::string getInterfaceId();
        
        /**
         * @author CJEducations
         * @brief get interface version for server
         * @version v1.0.0
         * @return interface version value (std::string)
         * @date 2012. 11. 28
         * @since v1.0.8
         */
        std::string getInterfaceVer();
        
        /**
         * @author CJEducations
         * @brief get request time for server
         * @version v1.0.0
         * @return request time value (std::string)
         * @date 2012. 11. 28
         * @since v1.0.8
         */
        std::string getRequestTime();
        
        bool getNetworkState();
        int getWifiStrength();
        
        // ------------------ //
        // file system method //
        // ------------------ //
        
        long long getFileSize(const char* path);
        
        bool checkSDCardAvailable();
        
        long long getFreeSpace();
        
        /**
         * @author CJEducations
         * @brief check sdcard's memory size
         * @version v1.0.0
         * @date 2013. 02. 22
         * @since v1.0.6
         */
        void checkStorageSize();
        
        /**
         * @author CJEducations
         * @brief remove gallery image file in sdcard
         * @version v1.0.0
         * @param path : gallery image path (const char*)
         * @date 2013. 02. 22
         * @since v1.0.6
         */
        bool removeSaveFile(const char* path);
        
        // ----------------------- //
        // get account info method //
        // ----------------------- //
        
        /**
         * @author CJEducations
         * @brief get current child id in java class
         * @version v1.0.0
         * @return child id string value (std::string)
         * @date 2012. 11. 28
         * @since v1.0.2
         */
        std::string getChildId();
        
        /**
         * @author CJEducations
         * @brief get current child name in java class
         * @version v1.0.0
         * @return child name string value (std::string)
         * @date 2012. 11. 28
         * @since v1.0.2
         */
        std::string getChildName();
        
        /**
         * @author CJEducations
         * @brief get current child birth day in java class
         * @version v1.0.0
         * @return child birth day string value (std::string)
         * @date 2012. 12. 27
         * @since v1.0.4
         */
        std::string getChildBirth();
        
        /**
         * @author CJEducations
         * @brief get current child image in java class
         * @version v1.0.0
         * @return child image string value (std::string)
         * @date 2012. 11. 28
         * @since v1.0.2
         */
        std::string getChildImage();
        
        // ---------------- //
        // set mail method //
        // ---------------- //
        
        /**
         * @author CJEducations
         * @brief set mail data (gallery image)
         * @version v1.0.0
         * @param path : gallery image path (const char*)
         * @date 2013. 02. 18
         * @since v1.0.5
         */
        void setMailFile(const char* path);
        
        /**
         * @author CJEducations
         * @brief set mail data (mail title)
         * @version v1.0.0
         * @param title : title string (const char*)
         * @date 2013. 02. 18
         * @since v1.0.5
         */
        void setMailTitle(const char* title);
        
        // ---------------- //
        // init list method //
        // ---------------- //
        
        /**
         * @author CJEducations
         * @brief init step list in java class
         * @version v1.0.0
         * @date 2012. 11. 27
         * @since v1.0.1
         */
        void initStepList();
        
        /**
         * @author CJEducations
         * @brief init content list in java class
         * @version v1.0.0
         * @date 2012. 11. 27
         * @since v1.0.1
         */
        void initContentList();
        
        /**
         * @author CJEducations
         * @brief init learn list in java class
         * @version v1.0.0
         * @date 2012. 11. 27
         * @since v1.0.1
         */
        void initLearnList();
        
        /**
         * @author CJEducations
         * @brief init grade list in java class
         * @version v1.0.0
         * @date 2012. 12. 17
         * @since v1.0.3
         */
        void initGradeList();
        
        // ------------------ //
        // init struct method //
        // ------------------ //
        
        /**
         * @author CJEducations
         * @brief init step struct in java class
         * @version v1.0.0
         * @date 2012. 11. 27
         * @since v1.0.1
         */
        void initStep();
        
        /**
         * @author CJEducations
         * @brief init content struct in java class
         * @version v1.0.0
         * @date 2012. 11. 27
         * @since v1.0.1
         */
        void initContent();
        
        /**
         * @author CJEducations
         * @brief init learn struct in java class
         * @version v1.0.0
         * @date 2012. 11. 27
         * @since v1.0.1
         */
        void initLearn();
        
        /**
         * @author CJEducations
         * @brief init grade struct in java class
         * @version v1.0.0
         * @date 2012. 12. 17
         * @since v1.0.3
         */
        void initGrade();
        
        // --------------- //
        // add list method //
        // --------------- //
        
        /**
         * @author CJEducations
         * @brief add step struct to step list in java class
         * @version v1.0.0
         * @date 2012. 11. 27
         * @since v1.0.1
         */
        void addStep();
        
        /**
         * @author CJEducations
         * @brief add content struct to step list in java class
         * @version v1.0.0
         * @date 2012. 11. 27
         * @since v1.0.1
         */
        void addContent();
        
        /**
         * @author CJEducations
         * @brief add learn struct to step list in java class
         * @version v1.0.0
         * @date 2012. 11. 27
         * @since v1.0.1
         */
        void addLearn(unsigned int childID);
        
        /**
         * @author CJEducations
         * @brief add grade struct to step list in java class
         * @version v1.0.0
         * @date 2012. 12. 17
         * @since v1.0.3
         */
        void addGrade();
        
        // ---------------------- //
        // set step struct method //
        // ---------------------- //
        
        /**
         * @author CJEducations
         * @brief set step class in java class
         * @param nCount : progress struct's nCount value
         * @version v1.0.0
         * @date 2012. 11. 27
         * @since v1.0.1
         */
        void setStepCount(unsigned int nCount);
        
        /**
         * @author CJEducations
         * @brief set step class in java class
         * @param szKey : progress struct's szKey value
         * @version v1.0.0
         * @date 2012. 11. 27
         * @since v1.0.1
         */
        void setStepKey(const char* szKey);
        
        /**
         * @author CJEducations
         * @brief set step class in java class
         * @param szStartDate : progress struct's szStartDate value
         * @version v1.0.0
         * @date 2012. 11. 27
         * @since v1.0.1
         */
        void setStepStartDate(const char* szStartDate);
        
        /**
         * @author CJEducations
         * @brief set step class in java class
         * @param szEndDate : progress struct's szEndDate value
         * @version v1.0.0
         * @date 2012. 11. 27
         * @since v1.0.1
         */
        void setStepEndDate(const char* szEndDate);
        
        /**
         * @author CJEducations
         * @brief set step class in java class - not use yet
         * @param szExtra : progress struct's extra value
         * @version v1.0.0
         * @date 2012. 11. 27
         * @since v1.0.1
         */
        void setStepExtra(const char* szExtra);
        
        // ------------------------- //
        // set content struct method //
        // ------------------------- //
        
        /**
         * @author CJEducations
         * @brief set content class in java class
         * @param szContentCode : content struct's szContentCode value
         * @version v1.0.0
         * @date 2012. 11. 27
         * @since v1.0.1
         */
        void setContentCode(const char* szContentCode);
        
        /**
         * @author CJEducations
         * @brief set content class in java class (remove param)
         * @param iGrade : kidscontent struct's iGrade value
         * @version v1.0.1
         * @date 2012. 12. 17
         * @since v1.0.1
         */
        void setContentGrade();
        
        /**
         * @author CJEducations
         * @brief set content class in java class - not use yet
         * @param szExtra : kidscontent struct's szExtra value
         * @version v1.0.0
         * @date 2012. 11. 27
         * @since v1.0.1
         */
        void setContentExtra(const char* szExtra);
        
        /**
         * @author CJEducations
         * @brief set step list to content class in java class
         * @version v1.0.0
         * @date 2012. 11. 27
         * @since v1.0.1
         */
        void setContentList();
        
        // ----------------------- //
        // set learn struct method //
        // ----------------------- //
        
        /**
         * @author CJEducations
         * @brief set learn class in java class
         * @param szPKGName : kidsinfo struct's szPKGName value
         * @version v1.0.0
         * @date 2012. 11. 27
         * @since v1.0.1
         */
        void setLearnPKGName(const char* szPKGName);
        
        /**
         * @author CJEducations
         * @brief set learn class in java class
         * @param szCompleteDate : kidsinfo struct's szCompleteDate value
         * @version v1.0.0
         * @date 2012. 11. 27
         * @since v1.0.1
         */
        void setLearnCompleteDate(const char* szCompleteDate);
        
        /**
         * @author CJEducations
         * @brief set content list to learn class in java class
         * @version v1.0.0
         * @date 2012. 11. 27
         * @since v1.0.1
         */
        void setLearnList();
        
        // ----------------------- //
        // set grade struct method //
        // ----------------------- //
        
        /**
         * @author CJEducations
         * @brief set grade class in java class
         * @param iGrade : grade struct's iGrade value
         * @version v1.0.0
         * @date 2012. 12. 17
         * @since v1.0.3
         */
        void setGrade(unsigned int iGrade);
        
        /**
         * @author CJEducations
         * @brief set grade class in java class
         * @param szWriteDate : grade struct's szWriteDate value
         * @version v1.0.0
         * @date 2012. 12. 17
         * @since v1.0.3
         */
        void setGradeDate(const char* szWriteDate);
        
        void setGradeExtra(const char* szExtra);
        
        // --------------------- //
        // send to server method //
        // --------------------- //
        
        /**
         * @author CJEducations
         * @brief send data to LMSCenter in java class
         * @version v1.0.0
         * @date 2012. 11. 27
         * @since v1.0.1
         */
        unsigned int sendLMSCenter();
        
        /**
         * @author CJEducations
         * @brief send mail to server in java code
         * @version v1.0.0
         * @param text : html data in mail (const char*)
         * @date 2013. 02. 18
         * @since v1.0.5
         */
        unsigned int sendMail(const char* text);
        
        // ----------------- //
        // get string method //
        // ----------------- //
        
        /**
         * @author CJEducations
         * @brief get device current date&time - ios, android
         * @version v1.0.0
         * @return current date&time (std::string)
         * @date 2012. 11. 20
         * @since v1.0.0
         */
        std::string getDeviceDateTime();
        
        /**
         * @author CJEducations
         * @brief complete date&time according package app - ios, android
         * @version v1.0.0
         * @param packageIndex : package number (int)
         * @return complete date&time (std::string)
         * @date 2012. 11. 20
         * @since v1.0.0
         */
        std::string getTargetDateTime(unsigned int packageIndex);
        
        std::string getDiffDate(const char* date, int days);
        
        
        void showThinkleStore();
        void showBrowser(const char *szUrl);
    };
}

#endif
