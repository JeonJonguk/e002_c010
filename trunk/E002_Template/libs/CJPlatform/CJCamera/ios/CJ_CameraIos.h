
#import <UIKit/UIKit.h>
#import <MobileCoreServices/MobileCoreServices.h>
#import <AVFoundation/AVFoundation.h>
#import <AssetsLibrary/AssetsLibrary.h>

@interface CJ_CameraIos : UIViewController  
{
    

    Boolean                     _isCameraDelete;
    UIView                      *_cameraOverlayView;
    UIImageView                 *_tempImageView;
    
    NSString                    *_saveFileName;
    NSString                    *_saveMovieName;


    AVCaptureFileOutput         *movieFileOutput;
    AVCaptureDeviceInput        *audioInput;
    AVCaptureDeviceInput        *videoInput;
    AVCaptureDeviceInput        *caputureInput;
    AVCaptureVideoPreviewLayer *captureVideoPreviewLayer;
    
    __block bool bEnableGallerySession;
}
@property(nonatomic , retain)AVCaptureSession *_session;
@property(nonatomic , retain)AVCaptureMovieFileOutput *_movieFileOutput;
@property(nonatomic , retain)AVCaptureVideoPreviewLayer *_captureVideoPreviewLayer;
@property(nonatomic , retain)UIView *_cameraOverlayView;

- (AVCaptureConnection *)connectionWithMediaType:(NSString *)mediaType fromConnections:(NSArray *)connections;
- (CJ_CameraIos*)setShowCameraFrame;

//- (void)captuerCamera;

- (void)setGallerySession;
- (BOOL)getGallerySession;

- (void)saveToPhotoLibraryWithFileName:(NSString *)fileName;

- (void)ShowCamera : (const char*)strFrame camType:(int)type Posx: (int) posx Posy: (int) posy width:(int) width height: (int) height;
- (void)startRecording:(const char*)savefilename;

- (void)initWithCameraFrame:(const char*)fileName Posx: (int) posx Posy: (int) posy width:(int) width height: (int) height;
- (void)checkCameraRotation:(AVCaptureVideoPreviewLayer*)capturePreview;
- (void)stopRecording;
- (void)setDeleteCamera;
- (BOOL)saveImageToDocument:(NSDictionary*)info;

- (void)initSetCaptureSession;
//- (void)startRecordingToOutputFileURL:(NSURL*)outputFileURL outputFileType:(NSString *)fileType recordingDelegate:(id<AVCaptureFileOutputRecordingDelegate>)delegate;
- (void)captureOutput:(AVCaptureFileOutput *)captureOutput didStartRecordingToOutputFileAtURL:(NSURL *)fileURL fromConnections:(NSArray *)connections;
- (void)captureOutput:(AVCaptureFileOutput *)captureOutput didFinishRecordingToOutputFileAtURL:(NSURL *)outputFileURL fromConnections:(NSArray *)connections error:(NSError *)error;

- (void)moveToCameraView:(int)x positionY:(int)y;



@end
