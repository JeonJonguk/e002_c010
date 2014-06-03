#ifndef __CJ_ANIMATION_MANAGER_H__
#define __CJ_ANIMATION_MANAGER_H__

#include "cocos2d.h"

#include "CJUtils.h"
#include "CJMultimedia.h"

#include "CJAnimationParserDelegate.h"
#include "CJAnimationParser.h"


#include "CJParseThread.h"
#include "CJLoadingAnimation.h"

#include "CJFlashAnimationDelegate.h"

using namespace cocos2d;
using namespace CJFlash;

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

enum ParseType
{
	kParseTypeXML = 0,
	kParseTypeJSON,
};



struct CJAnimationFiles
{
    std::string                 sheetsName;
    std::string                 animationsName;
    std::string                 dataPoolKeyName;
    bool                        isFullPath;

    CJAnimationFiles(std::string sStr, std::string aStr, std::string kStr, bool bFullPath)
    {
        sheetsName = sStr;
        animationsName = aStr;
        dataPoolKeyName = kStr;
        isFullPath = bFullPath;
    }
    
    void setFiles(std::string sStr, std::string aStr, std::string kStr, bool bFullPath)
    {
        sheetsName = sStr;
        animationsName = aStr;
        dataPoolKeyName = kStr;
        isFullPath = bFullPath;
    }
};
    
    
    
class CJAnimationManager :  public CJAnimationParserDelegate, public CJFlashAnimationDelegate
{
    
public:

    typedef std::multimap<std::string, CJFlash::CJAnimationDataPool*>           STL_MULTIMAP_DATAPOOL;

private:
    
    CCNode*                                                                     m_pAnimationParent;
    CCNode*                                                                     m_pLoadingParent;

    std::vector<CJAnimationFiles>                                               m_animationFiles;
    ParseType                                                                   m_parseType;
    bool                                                                        m_bIsLoading;
    
    CJLoadingAnimation*                                                         m_loadingAnimation;
    
    
    
    STL_MULTIMAP_DATAPOOL                                                       m_stl_mmap_Datapool;
    
public:
    CJAnimationManager(void);
    ~CJAnimationManager(void);
    
public:
    
    void setAnimationFile(std::string sStr, std::string aStr, std::string kStr);
    void setAnimationCommonFile(std::string sStr, std::string aStr, std::string kStr);

    void setAnimationParent(CCNode* node);
    //void setAnimationParseType(ParseType pType);
    void setLoadingToParent(CCNode* parent);
    
    CCNode* getAnimationDelegate(){return m_pAnimationParent;}
    
    STL_MULTIMAP_DATAPOOL getAllDatapool();
    void setAllDatapool(std::multimap<std::string, CJFlash::CJAnimationDataPool*> allDatapool);
    
    void removeAllDatapool();
    
public:
    void         animationManagerParseStart();
    virtual void animationManagerParseComplete(){};     /* override me */
    
private:
    void _completeCallback();
    void _callFunctionWithDelay(cocos2d::SEL_CallFunc aSelector, float fDelayTime);
    
public:
    
    virtual void begin();
    virtual void parseThreadStartCallback();
	virtual void parseThreadEndCallback();
    virtual void end();
    void parseStart();
    
    
public:
    void createAllAnimations();
    void createAllAnimationsWithCommonPath();
    void createAnimationsInDataPool(std::string datapoolKey);
    void createAnimation(std::string datapoolKey, std::string animationName);
    void createAnimationAndSetKey(std::string datapoolKey, std::string animationName, std::string animationKey);
    
    
    CJAnimationDataPool*        getDataPoolByKey(std::string strKey);
    CJAnimation*                getAnimationByName(std::string datapoolKey, std::string animationName);
    CJAnimation*                getAnimationByKey(std::string datapoolKey, std::string animationKey);
    std::vector<CJAnimation*>*  getAllAnimationsByKey(std::string datapoolKey);
    
    
    void                        setAnimationKey(CJAnimation* animation, std::string animationKey);
    std::string                 getAnimationKey(CJAnimation* animation);
    void                        setAnimationKey(std::string datapoolKey, std::string animationName, std::string animationKey);
    std::string                 getAnimationKey(std::string datapoolKey, std::string animationName);
    
    
    int getDataPoolCount();
    int getAnimationCount(std::string datapoolKey);
    
public:
    /* override me */
    virtual void OnPlay(CJAnimation* pAnimation);
    virtual void OnStop(CJAnimation* pAnimation);
    virtual void OnLastFrame(CJAnimation* pAnimation);
    virtual void OnPause(CJAnimation* pAnimation);
    virtual void OnUpdate(CJAnimation* pAnimation);
    
    
public:
    
    void addNarrationOnFlashFrame(CJAnimation* animation, int pFrame, const char* pSoundPath);
    void addEffectOnFlashFrame(CJAnimation* animation, int pFrame, const char* pSoundPath);

    void addNarrationOnFlashFrameByName(std::string datapoolKey, std::string animationName, int pFrame, const char* pSoundPath);
    void addEffectOnFlashFrameByName(std::string datapoolKey, std::string animationName, int pFrame, const char* pSoundPath);
    
    static void onArriveAtParticularFrameNarr(CCNode* sender, SEL_CallFuncND pCallFunc, void *pUserData);
    static void onArriveAtParticularFrameEffect(CCNode* sender, SEL_CallFuncND pCallFunc, void *pUserData);

    
    CJAnimation* attachAnimation(std::string datapoolKey, std::string animationName, bool bIsCommonPath, CCNode* parent = NULL);

    void         playAnimation(CJAnimation* animation, int repeatCount, int depth, CCNode* parent = NULL);
    CJAnimation* playAnimation(std::string datapoolKey, std::string animationName, int repeatCount, int depth, CCNode* parent = NULL);
    CJAnimation* playAnimationByKey(std::string datapoolKey, std::string animationKey, int repeatCount, int depth, CCNode* parent = NULL);

    CJAnimation* playAnimationWithCommonPath(CJAnimation* animation, int repeatCount, int depth, CCNode* parent);
    CJAnimation* playAnimationWithCommonPath(std::string datapoolKey, std::string animationName, int repeatCount, int depth, CCNode* parent = NULL);
    CJAnimation* playAnimationWithCommonPathByKey(std::string datapoolKey, std::string animationKey, int repeatCount, int depth, CCNode* parent = NULL);

    void         playLoopingAnimation(CJAnimation* animation, int depth, CCNode* parent = NULL);
    CJAnimation* playLoopingAnimation(std::string datapoolKey, std::string animationName, int depth, CCNode* parent = NULL);
    CJAnimation* playLoopingAnimationByKey(std::string datapoolKey, std::string animationKey, int depth, CCNode* parent = NULL);

    
    void stopAnimation(CJAnimation* animation);
    void stopAnimation(std::string datapoolKey, std::string animationName);
    void stopAnimationByKey(std::string datapoolKey, std::string animationKey);

    void stopAllAnimationsInDataPool(CJAnimationDataPool* datapool);
    void stopAllAnimationsInDataPool(std::string datapoolKey);
    void stopAllAnimations();
    
    void pauseAnimation(CJAnimation* animation);
    void pauseAnimation(std::string datapoolKey, std::string animationName);
    void pauseAnimationByKey(std::string datapoolKey, std::string animationKey);
    void pauseAllAnimationsInDataPool(CJAnimationDataPool* datapool);
    void pauseAllAnimationsInDataPool(std::string datapoolKey);
    void pauseAllAnimations();
    
    void resumeAnimation(CJAnimation* animation);
    void resumeAnimation(std::string datapoolKey, std::string animationName);
    void resumeAnimationByKey(std::string datapoolKey, std::string animationKey);
    void resumeAllAnimationsInDataPool(CJAnimationDataPool* datapool);
    void resumeAllAnimationsInDataPool(std::string datapoolKey);
    void resumeAllAnimations();
    
    void removeAnimation(CJAnimation* animation, bool bClean = false);
    void removeAnimation(std::string datapoolKey, std::string animationName, bool bClean = false);
    void removeAnimationByKey(std::string datapoolKey, std::string animationName, bool bClean = false);
    void removeAllAnimationsInDataPool(CJAnimationDataPool* datapool, bool bClean = false);
    void removeAllAnimationsInDataPool(std::string datapoolKey, bool bClean = false);
    void removeAllAnimations(bool bClean = false);
    
    CJAnimation*    cleanAndNewAnimation(std::string datapoolKey, std::string animationName);
    CJAnimation*    cleanAndNewAnimationAndSetKey(std::string datapoolKey, std::string animationName, std::string animationKey);
    
    void            reorderFlashChildren(CJAnimation* animation);
    CJAnimation*    replaceAnimation(std::string oldDataPoolKey, std::string oldAnimationName, std::string newDataPoolKey, std::string newAnimationName, int repeatCount);
    
    
    // 스프라이트를 받아와서 처리.
    CCSprite*   getSpriteFromFlash(CJAnimation* animation, const char* spriteName);
    CCSprite*   getSpriteFromFlash(const char* dataPoolKey, const char* animationName, const char* spriteName);
    void        replaceFlashSpriteTexture(CCSprite* spriteInFlash, CCSprite* spriteForTexture);
    void        replaceFlashSpriteTextureRestore(CCSprite* spriteInFlash, CCSprite* spriteForTexture);
};


#endif //__CJ_ANIMATION_MANAGER_H__