/*
 *  CJUtils.h
 *
 *
 *  Created by Dongjin Park on 12. 10. 4..
 *  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
 */


#ifndef CJ_COMMON_MANAGEMENT_CLASS_H
#define CJ_COMMON_MANAGEMENT_CLASS_H

 
#define CJ_DEBUGMODE true // true(1):show log , false(0):hide log

#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>

#include "cocos2d.h" 
#include "CJLMSContentInterface.h"

USING_NS_CC;
using namespace std;



class CJUtils
{
    
private:
    
    std::string m_rootPath;                 // '/mnt/sdcard/' or 'asset/' or '/data/data/'
    std::string m_contentID;                // contents id (e001_c000)
    std::string m_resourcePath;             // 'm_rootPath' + 'm_contentID'
    std::string m_commonResourcePath;       // for common resource (asset)
    std::string m_language;                 // current language
    bool _bIsPopupStatus;
    
public:
    CJUtils();
    ~CJUtils();
    
    
    static CJUtils* getInstance();
    static void     releaseInstance();


    void            setRootPath(std::string tempPath);
    std::string     getRootPath();
    void            setContentID(std::string tempID);
    std::string     getContentID();
    std::string     getResourcePath();
    void            setCommonResourcePath(std::string commonPath);
    std::string     getCommonResourcePath();
    int             getKidId();
    std::string     getFontPath();
    void            setLanguage(std::string language);
    std::string     getLanguage();
    
    //set the userdefalut key value that contentID is added.
    void            setUserDefaultBoolForKey(std::string pKey , bool value);
    void            setUserDefaultIntegerForKey(std::string pKey , int value);
    void            setUserDefaultFloatForKey(std::string pKey , float value);
    void            setUserDefaultStringForKey(std::string pKey , std::string value);
    void            setUserDefaultDoubleForKey(std::string pKey , double value);
    

    // get the userdefalut key value that contentID is added.
    bool            getUserDefaultBoolForKey(std::string pKey);
    int             getUserDefaultIntegerForKey(std::string pKey);
    float           getUserDefaultFloatForKey(std::string pKey);
    std::string     getUserDefaultStringForKey(std::string pKey);
    double          getUserDefaultDoubleForKey(std::string pKey);
    
    
    // get file path
    std::string     addContentIDPrefix(std::string strTemp);
    std::string     getFilePath(std::string strFileName);
    std::string     getFilePath(std::string strFolderName, std::string strFileName, bool isDifferentLanguage = false);
    std::string     getCommonFilePath(std::string strFileName);
    std::string     getCommonFilePath(std::string strFolderName, std::string strFileName);

    
    // Lms control
//    void setLmsStart(std::string menuStr);
//    void setLmsEnd();
//    void setLmsSendPoint(std::string , int , std::vector<int>);
    static void setLmsMenuEnd(int iMenuValue);
    static std::string getLMSFileName(int iMenuID, eFileType eFileType,
                                      std::string strExtend1 = "", std::string strExtend2 = "");
    static bool saveLMSFile();
    
    // AppDelegate control
    void resignActive();
    void becomeActive();
    void enterBackground();
    void enterForeground();
    
    // string control
    static std::string getStringMerge(std::string str1, std::string str2);
    static std::string getStringMerge(std::string str1, int nNumber);
    static std::string getStringMerge(std::string str1, int nNumber, std::string str2);
    static std::string getStringFormatInteger(std::string format, int nInteger);
    static std::string getStringFormatString(std::string format, std::string str);
    static std::string stringTokenizer(std::string sentence, std::string tok, bool first);
    static std::string stringTokenizer(std::string sentence, std::string tok, int index);
    
    // touch bound
    static bool containRect(CCLayer* layer, CCNode* node, CCPoint touch);
    static bool containRect(CCLayer* layer, CCNode* node, CCPoint touch, float band);
    static bool containPointWithBand(CCPoint targetPoint, CCPoint touch, float bandSize);
    static bool hitTestPoint(CCNode* pNode, const CCPoint& pos, bool bCenter);
    static bool hitTestObjects(CCNode* pNode1, CCNode* pNode2);
    static CCRect rect(CCNode* pNode);
    
    // position control
    static void setPositionForParent(CCNode* parent, CCNode* child);
    static void setAnchorPointForPosition(CCNode* node, CCPoint anchor);
    static void setTransformCenterPosition(CCNode* node, CCPoint center);
    static CCPoint getTransformCenterPoint(CCPoint origin, CCPoint center);
    
    // make random
    static float    randomFloat(float low, float hi);
    static int      randomInteger(int low, int hi);
    static int      randomIntegerWithoutValue(unsigned int nMax, unsigned int nWithoutValue);
    static bool     randomBoolean();
    static int*     randomIntegerArr(const unsigned nMax);
    static float    roundValue(float value, int pos);

    
    // @author  YoungJin Lee
    // @brief	performSelector
    static void performSelector(cocos2d::CCObject *pTarget,
                                cocos2d::SEL_CallFunc aSelector,
                                float afterDelay = 0.0f,
                                int tag = 0);
    static void performSelector(cocos2d::CCObject *pTarget,
                                cocos2d::SEL_CallFuncND aSelector,
                                void *pObject,
                                float afterDelay = 0.0f,
                                int tag = 0);
    static void performSelectorCancel(cocos2d::CCObject *pTarget,
                                      int tag);

    
    //CCAction
    static void stopAllAnimations(CCNode *node);
    static void pauseAllAnimations(CCNode *node);
    static void resumeAllAnimations(CCNode *node);
    static void removeAllchildren(CCNode *node);
    
    static void fadeInAllchildren(CCNode* pNode, float duration);
    static void fadeOutAllchildren(CCNode* pNode, float duration);
    
    // @author  YoungJin Lee
    // @brief	actions
    static CCActionInterval* getSeqAction(int nRepeatCount,
                                          float fSeqTime,
                                          std::string strSeqImageName, ...);
    static CCActionInterval* getSeqAction(int nRepeatCount,
                                          float fSeqTime,
                                          CCObject *pCallbackTarget,
                                          SEL_CallFunc aCallbackSelector,
                                          std::string strSeqImageName, ...);
    
    
    static CCAnimate* getAnimation(float fFrameDelay, std::string strSeqImageName, ...);
    
    static CCActionInterval* getAnimations(int nRepeatCount,
                                           float fSeqTime,
                                           CCAnimate *pAnimation, ...);
    static CCActionInterval* getAnimations(int nRepeatCount,
                                           float fSeqTime,
                                           CCObject *pCallbackTarget,
                                           SEL_CallFunc aCallbackSelector,
                                           CCAnimate *pAnimation, ...);

    
    //for popup
    void setPopupStatus(bool pPopupStatus) {_bIsPopupStatus = pPopupStatus;};
    bool isPopupStatus(){return _bIsPopupStatus;};

    
};

void CJDialog(const char*);
void CJLog(const char * pszFormat, ...) CC_FORMAT_PRINTF(1, 2);




#endif