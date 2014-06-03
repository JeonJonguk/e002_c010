 

#ifndef __CJFlatform__CJCameraInterface__
#define __CJFlatform__CJCameraInterface__

#include <vector>
#include "cocos2d.h" 
#include "CJDefines.h"
 

USING_NS_CC;

class CJCameraInterface
{
private:
    bool isShowPreview;
    
public:
     
    CJCameraInterface();
    ~CJCameraInterface();
  
    static CJCameraInterface* getInstance();
    
    void    setGallerySession();
    bool    getGallerySession();
    void    saveToPhotoLibraryWithFileName(std::string strFileName);
    
    
    void    showCameraPreview(std::string frameImgPath, int direction, int x, int y, int width, int height);
    void    takePicture();
    void    startRecording(std::string contentPath);
    void    stopRecording();
    void    removeCameraView();
    void    onVideolRecordingCallBack(const char*fileName);
    void    onCameraCaptureCallBack(const char*fileName);
    bool    isShowCameraPreview();
    void    moveToCameraView(int x, int y);
};

#endif  