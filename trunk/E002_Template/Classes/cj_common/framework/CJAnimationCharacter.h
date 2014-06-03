//
//  CJAnimationCharacter.h
//  E002_Template
//
//  Created by Jeong.YJ on 2014. 2. 17..
//
//

#ifndef E002_Template_CJAnimationCharacter_h
#define E002_Template_CJAnimationCharacter_h

#include "CJLayer.h"
#include "CJAnimationManager.h"


class CJAnimationCharacter
{
private:
    std::vector<const char*> *mFailKeys;
    std::vector<const char*> *mSuccessKeys;
    
    const char* mLoopingKey;
    
    CJAnimation *_mCurrentAnimation;
    
    int mFailCount;
    int mSuccessCount;
    int mZorder;
    
    std::string mDataKey;
    
    CJAnimationManager *mAnimationManager;
    
    void _setFails();
    void _setSuccess(const char* key, ...);
    
public:
    ~CJAnimationCharacter();
    CJAnimationCharacter(CJAnimationManager *manager, std::string dataKey);
    
    void setFails(const char* key, ...);
    void setSuccess(const char* key, ...);
    void setLooping(const char* key);
    
    CJAnimation* showFails();
    CJAnimation* showSuccess();
    CJAnimation* showLooping();
    CJAnimation* getCurrentAnimationCharacter();
    
    std::vector<const char*>* getAllKeys();
    std::vector<const char*>* getFailKeys();
    std::vector<const char*>* getSuccessKeys();
    
    CCSprite* getSprite(const char* spriteName);
    
    void setZorder(int zOrder);

};


#endif
