 

#include "../include/CJCameraInterface.h" 
#include "CJ_CameraIos.h"
#include "CJDefines.h"


static CJCameraInterface * s_pInstance = 0;
static CJ_CameraIos *cameraIOS = NULL;

CJCameraInterface::CJCameraInterface()
{
    isShowPreview = false;
    cameraIOS = NULL;
    cameraIOS = nil;
}

CJCameraInterface::~CJCameraInterface()
{

}

CJCameraInterface* CJCameraInterface::getInstance()
{
    if (! s_pInstance)
    {
        s_pInstance = new CJCameraInterface();
    }

    return s_pInstance;
}

void CJCameraInterface::setGallerySession()
{
    if(cameraIOS == NULL)
        cameraIOS = [[CJ_CameraIos alloc] init];

    [cameraIOS setGallerySession];
}

bool CJCameraInterface::getGallerySession()
{
    if(cameraIOS == NULL)
        cameraIOS = [[CJ_CameraIos alloc] init];

    return [cameraIOS getGallerySession];
}

void CJCameraInterface::saveToPhotoLibraryWithFileName(std::string strFileName)
{
    if(cameraIOS == NULL)
        cameraIOS = [[CJ_CameraIos alloc] init];
    
    [cameraIOS saveToPhotoLibraryWithFileName:[NSString stringWithUTF8String:strFileName.c_str()]];
    [cameraIOS release];
    cameraIOS = nil;
}

void  CJCameraInterface::showCameraPreview(std::string frameImgPath, int direction, int x, int y, int width, int height)
{
    if(cameraIOS == NULL)
    {
        cameraIOS = [[CJ_CameraIos alloc] init];
    }
    
    s_pInstance->isShowPreview = true;
    [cameraIOS ShowCamera:frameImgPath.c_str() camType:direction Posx:x Posy:y width:width height:height];
}

void  CJCameraInterface::takePicture()
{
//    [cameraIOS captuerCamera];
}

void CJCameraInterface::startRecording(std::string contentPath)
{
    if(cameraIOS == NULL)
    {
        cameraIOS = [[CJ_CameraIos alloc] init];
    }
    
    s_pInstance->isShowPreview = true;
    [cameraIOS startRecording:contentPath.c_str()];
}

void CJCameraInterface::stopRecording()
{
    
    if(cameraIOS!=NULL)
    {
        [cameraIOS stopRecording];
    }
}

void CJCameraInterface::removeCameraView()
{
    CJCameraInterface::getInstance()->isShowPreview = false;
    if(cameraIOS !=NULL)
    {
        NSLog(@"CJCameraInterface::removeCameraView===============CALL");
        [cameraIOS setDeleteCamera];
        [cameraIOS release];
        cameraIOS = NULL;
        
    }

}


void CJCameraInterface::onVideolRecordingCallBack(const char*fileName)
{
    CCString *tempfileName = CCString::create(fileName);
    CCLog("CallBack fileName = %s",fileName);
    CCNotificationCenter::sharedNotificationCenter()->postNotification(CJNOTIFICATION_VIDEO_RECORDING_FINISHCALL, tempfileName);

    
}
void CJCameraInterface::onCameraCaptureCallBack(const char*fileName)
{
    CCString *tempfileName = CCString::create(fileName);
    CCLog("CallBack fileName = %s",fileName);
    CCNotificationCenter::sharedNotificationCenter()->postNotification(CJNOTIFICATION_PICTURE_FINISHCALL, tempfileName);
    
}

bool CJCameraInterface::isShowCameraPreview()
{
    return isShowPreview;
}


void CJCameraInterface::moveToCameraView(int x, int y)
{
    [cameraIOS moveToCameraView:x positionY:y];
}
