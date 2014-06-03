//
//  E001_Base_P000_Intro.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 5. 31..
//
//

#ifndef E002_Base_Video_h
#define E002_Base_Video_h


#include "cocos2d.h"
#include "CJVideoLayer.h"


using namespace cocos2d;

namespace
{
    enum {
        kTagIndexBtn = 101,
        kTagSkipBtn = 102,
        kTagNoramlType = 103,
        kTagSongType = 104,
    };
}



class E002_Base_VideoLayer : public CJVideoLayer {

private:
    int mVideoType;
    
public:
    ~E002_Base_VideoLayer();
    E002_Base_VideoLayer();

    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual void onViewLoad();
    virtual void onViewLoaded();
     
    virtual void onVideoFinishedCallback();
    
    void setVideoPath(std::string fileName, int type = kTagNoramlType);
    
    void onVideoBtnTouchCallback(CCObject* tag);
    
    void onVideoBtnTouch(CCObject* tag);
    
    virtual void onIndexBtnTouch(); 
    
};


#endif
