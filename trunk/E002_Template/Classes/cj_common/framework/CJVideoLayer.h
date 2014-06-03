//
//  CJVideoLayer.h
//  E002_Template
//
//  Created by Jeong.YJ on 2014. 1. 9..
//
//

#ifndef E002_Template_CJVideoLayer_h
#define E002_Template_CJVideoLayer_h

#include "cocos2d.h"
#include "CJLayer.h"

using namespace cocos2d;

class CJVideoLayer : public CJLayer {
private:
    std::string mIntroVideoFileName;
     
public:
    ~CJVideoLayer();
    CJVideoLayer();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit(); 
    
    virtual void onViewLoad();
    virtual void onViewLoaded();
    
    CREATE_FUNC(CJVideoLayer);
    
    virtual void onVideoFinishedCallback();
    
    void addButtonVideo(std::string btnPath, int x, int y, int tag);
    virtual void setVideoPath(std::string fileName);
    void playVideo();
    
    virtual void onVideoBtnTouchCallback(CCObject* tag);
};

#endif
