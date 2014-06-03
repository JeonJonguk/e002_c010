 

#ifndef __CJFlatform__CJVideoInterface__
#define __CJFlatform__CJVideoInterface__

//#define KTAGNONEVIDEO 0         //no interaction, no controller
//#define KTAGNONSKIPVIDEO 1      //no controller, touch skip
//#define KTAGNATIVEVIDEO 2       //native controller
//#define KTAGNATIVESECONDVIDEO 3 //second native controller
//#define KTAGCJVIDEO 4           //cj custom controller video
//#define KTAGCJNOTOUCHFRAME 5    //no interaction, frame video


#include <vector>
#include "cocos2d.h" 
#include "CJDefines.h"
 

USING_NS_CC;

class CJVideoInterface
{
public:
    
    CJVideoInterface();
    ~CJVideoInterface();
  
    static CJVideoInterface* getInstance();
    
    void    playVideo(std::string filePath, bool isControllerVisible);
    void    stopVideo();
    void    pauseVideo();
    void    resumeVideo();
    void    addVideoBtn(std::string btnPath, float x, float y, int tag);
    
    void    playFrameVideo(std::string frameImgPath, std::string contentPath, int x,int y,int width,int height);
    void    removeFrameVideo();
    
    //only ios exist
    void    onButtonTouch(int tag);
    
    std::string fullPathFromRelativePath(std::string relativePath);
};

#endif /* defined(__CJTemplate__CJAudioEngine__) */

