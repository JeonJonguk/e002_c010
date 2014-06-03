//
//  CJ_Camera.m
//  S001-C130
//
//  Created by SangSeong Lee on 6/10/13.
//  Copyright (c) 2013 CJ Educations. All rights reserved.
//

#import "CJ_CameraIos.h"
#import "CJCameraInterface.h"
#import "EAGLView.h"
#import "AppController.h"

//extern "C" void CJ_CameraCallBack(const char* fileName);
CJ_CameraIos *m_cameraInstance = nil;;
@interface CJ_CameraIos (FileOutputDelegate) <AVCaptureFileOutputRecordingDelegate>
@end

@implementation CJ_CameraIos
@synthesize  _session;
@synthesize _movieFileOutput;
@synthesize _captureVideoPreviewLayer;
@synthesize _cameraOverlayView;

- (AVCaptureConnection *)connectionWithMediaType:(NSString *)mediaType fromConnections:(NSArray *)connections
{
	for ( AVCaptureConnection *connection in connections ) {
		for ( AVCaptureInputPort *port in [connection inputPorts] ) {
			if ( [[port mediaType] isEqual:mediaType] ) {
				return connection;
			}
		}
	}
	return nil;
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}
- (CJ_CameraIos*)setShowCameraFrame
{
    if(m_cameraInstance==nil)
    {
        m_cameraInstance  = [[CJ_CameraIos alloc]init];
        
        bEnableGallerySession = false;
        
    }
    return m_cameraInstance;
}
- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
}





- (void)setGallerySession
{
    ALAssetsLibrary *library = [[ALAssetsLibrary alloc] init];
    
    // if iOS7 availeable.
    if([library respondsToSelector:@selector(writeImageDataToSavedPhotosAlbum:metadata:completionBlock:)])
    {
        [library writeImageDataToSavedPhotosAlbum:nil metadata:nil completionBlock:^(NSURL *assetURL, NSError *error) {
            if(nil == error)
                bEnableGallerySession = true;
            else
                bEnableGallerySession = false;
        }];
    }
    else
    {
        bEnableGallerySession = true;
    }
    
    [library release];
}

- (BOOL)getGallerySession
{
    return bEnableGallerySession;
}

- (void)saveToPhotoLibraryWithFileName:(NSString *)fileName
{
    UIImage *image = [UIImage imageWithContentsOfFile:fileName];
    UIImageWriteToSavedPhotosAlbum(image, nil, nil, nil);
}

-(void)ShowCamera : (const char*)strFrame camType:(int)type Posx: (int) posx Posy: (int) posy width:(int) width height: (int) height
{

    posx = posx*[AppController getScaleValue] + [AppController getLetterBoxPositionX];
    posy = posy*[AppController getScaleValue];
    width = width*[AppController getScaleValue];
    height = height*[AppController getScaleValue];
    
    [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(didRotateFromInterfaceOrientation:) name:UIDeviceOrientationDidChangeNotification object:nil];

    [[AVAudioSession sharedInstance] setCategory: AVAudioSessionCategoryPlayback error: nil];
    UInt32 doSetProperty = 1;
    
    AudioSessionSetProperty (kAudioSessionProperty_OverrideCategoryMixWithOthers, sizeof(doSetProperty), &doSetProperty);
    
    [[AVAudioSession sharedInstance] setActive: YES error: nil];
    UIWindow* window = [ [UIApplication sharedApplication] keyWindow];
    
    UIView * rootView = [[window subviews] objectAtIndex:0];
    _cameraOverlayView = [[UIView alloc]init];
    [_cameraOverlayView setFrame:CGRectMake(posx, posy, width, height)];
    [_cameraOverlayView setBackgroundColor:[UIColor clearColor]];
    [self.view addSubview:_cameraOverlayView];
    
    [rootView addSubview:self.view];

    AVCaptureSession *_preViewSession = [[AVCaptureSession alloc] init];
    _preViewSession.sessionPreset = AVCaptureSessionPresetMedium;


    AVCaptureDevice *videoDevice = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
    for (AVCaptureDevice *cam in [AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo])
    {
        if (cam.position == AVCaptureDevicePositionFront)
            videoDevice = cam;
    }
    caputureInput = [[AVCaptureDeviceInput alloc]initWithDevice:videoDevice error:nil];
    
    if(_preViewSession)
    {
        if(captureVideoPreviewLayer.session)
            NSLog(@"Error");
       
        captureVideoPreviewLayer = [[AVCaptureVideoPreviewLayer alloc] initWithSession:_preViewSession];
        captureVideoPreviewLayer.videoGravity = AVLayerVideoGravityResizeAspectFill;
        captureVideoPreviewLayer.frame = _cameraOverlayView.bounds;
        [captureVideoPreviewLayer.session beginConfiguration];
        [captureVideoPreviewLayer.session addInput:caputureInput];
        [_cameraOverlayView.layer addSublayer:captureVideoPreviewLayer];
        [captureVideoPreviewLayer.session commitConfiguration];
        [captureVideoPreviewLayer.session startRunning];
        [self checkCameraRotation:captureVideoPreviewLayer];
        
    }
    [_preViewSession release];
    _preViewSession = nil;
    [self initWithCameraFrame:strFrame Posx:posx Posy:posy width:width height:height];

}
-  (void)initWithCameraFrame:(const char*)fileName Posx: (int) posx Posy: (int) posy width:(int) width height: (int) height
{
    
    NSString *filePath = [NSString stringWithUTF8String:fileName];
    NSString* path = [[NSBundle mainBundle] pathForResource: filePath ofType: nil inDirectory:nil];
    NSData *imageData =     [NSData dataWithContentsOfFile:path];
    _tempImageView = [[[UIImageView alloc]init]autorelease];
    if ([[NSFileManager defaultManager] fileExistsAtPath:path])
    {
        
        UIImage *tempImage = [[UIImage alloc]initWithData:imageData];
        [_tempImageView setImage:tempImage];
        [_tempImageView setFrame:CGRectMake(posx,posy, width,height)];
        [tempImage release];
    }

    [self.view addSubview:_tempImageView];
    [self.view bringSubviewToFront:_tempImageView];
    
    
    
}

//-(void)captuerCamera
//{
//    
//}

- (void)  startRecording:(const char*)savefilename
{
// http://stackoverflow.com/questions/11079726/how-to-handle-autorotation-in-avcapturevideopreviewlayer
//    돌리는건너가해
    [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(didRotateFromInterfaceOrientation:) name:UIDeviceOrientationDidChangeNotification object:nil];
    
//    UIWindow* window = [ [UIApplication sharedApplication] keyWindow];
////    UIViewController* rootCtrl = window.rootViewController;
////    UIView *rootView = rootCtrl.view;
//    UIView * rootView = [[window subviews] objectAtIndex:0];
//    
//    _cameraOverlayView = [[UIView alloc]init];
//    [_cameraOverlayView setFrame:CGRectMake(posx, posy, width, height)];
//    [_cameraOverlayView setBackgroundColor:[UIColor clearColor]];
//    [self.view addSubview:_cameraOverlayView];
//    [rootView addSubview:self.view];
//    [rootView bringSubviewToFront:self.view];


    _saveMovieName =[[NSString stringWithUTF8String:savefilename]copy];
    [self initSetCaptureSession];
//    [self initWithCameraFrame:filePath Posx:posx Posy:posy width:width height:height];

}

- (void) stopRecording
{
    

//    [self setDeleteCamera];
    if(captureVideoPreviewLayer.session != nil)
    {
        NSLog(@"========session stop ========CALL");
        [movieFileOutput stopRecording];
        [captureVideoPreviewLayer.session stopRunning];
        [captureVideoPreviewLayer.session removeInput:videoInput];
        [captureVideoPreviewLayer.session removeInput:audioInput];
        [captureVideoPreviewLayer.session removeOutput:movieFileOutput];
        [movieFileOutput release];
        [videoInput release];
        [audioInput release];
//        [captureVideoPreviewLayer.session release];
//        captureVideoPreviewLayer.session = nil;

    }
    


}
- (void)setDeleteCamera
{

//    if(_preViewSession)
//    {
//        [_preViewSession release];
//        _preViewSession = nil;
//    }
    
    int totalCount = [[self.view subviews]count];
    for (int i = 0 ; i < totalCount; i++)
    {
        NSLog(@"%@",[[self.view subviews]objectAtIndex:0]);
        [[[self.view subviews]objectAtIndex:0]removeFromSuperview];
    }
    if(captureVideoPreviewLayer)
    {
        [captureVideoPreviewLayer removeAllAnimations];
        [captureVideoPreviewLayer removeFromSuperlayer];
        [captureVideoPreviewLayer release];
        captureVideoPreviewLayer = nil;
    }
    if(_cameraOverlayView)
    {
        [_cameraOverlayView.layer removeFromSuperlayer];
        [_cameraOverlayView removeFromSuperview];
        [_cameraOverlayView release];
        _cameraOverlayView = nil;
    }
//    [self.view removeFromSuperview];
}
- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
#pragma mark - Save Functions
- (NSString *) findUniqueSavePath:(NSString*)contentsType
{
	NSString *path = nil;
    NSString *extension = nil;
    
    if([contentsType isEqualToString:@"IMAGE"])
    {
        extension = @"PNG";
        path = [NSString stringWithFormat:@"%@/Documents/%@%@", NSHomeDirectory(), contentsType,_saveFileName];
    }
    else
    {
        extension = @"mp3";
        path = [NSString stringWithFormat:@"%@/Documents/%@", NSHomeDirectory(), _saveMovieName];
    }



	
	return path;
}
- (BOOL) saveImageToDocument:(NSDictionary*)info
{
//    // Set Image from Dictionary
//    UIImage *image = [info objectForKey:UIImagePickerControllerOriginalImage];
//    
//    // Save Image to Documents Folder
//    NSString *path = [self findUniqueSavePath:@"IMAGE"];
//    
//    [UIImagePNGRepresentation(image) writeToFile:[self findUniqueSavePath:@"IMAGE"] atomically:YES];
//    CJCameraInterface::getInstance()->onCameraCaptureCallBack([path UTF8String]);
    return false;
}


// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    
    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
    
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskLandscape;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation
{
    [self checkCameraRotation:captureVideoPreviewLayer];
    
}
//
//
//- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
//{
//
//    return true;
//}
//- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation
//{
//
//}
- (void)initSetCaptureSession
{

    [[AVAudioSession sharedInstance] setCategory: AVAudioSessionCategoryPlayback error: nil];
    UInt32 doSetProperty = 1;
    
    AudioSessionSetProperty (kAudioSessionProperty_OverrideCategoryMixWithOthers, sizeof(doSetProperty), &doSetProperty);
    
    [[AVAudioSession sharedInstance] setActive: YES error: nil];
    



    
    AVCaptureSession *session = [[AVCaptureSession alloc] init];
    session.sessionPreset = AVCaptureSessionPresetMedium;

    CALayer *viewLayer = _cameraOverlayView.layer;
    NSLog(@"viewLayer = %@", viewLayer);
    NSLog(@"session = %@", session);
    
    if(session)
    {
        captureVideoPreviewLayer = [[AVCaptureVideoPreviewLayer alloc] initWithSession:session];
        captureVideoPreviewLayer.videoGravity = AVLayerVideoGravityResizeAspectFill;
        captureVideoPreviewLayer.frame = _cameraOverlayView.bounds;
        [captureVideoPreviewLayer.session beginConfiguration];



        NSError *error = nil;

        AVCaptureDevice *videoDevice = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
        for (AVCaptureDevice *cam in [AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo])
        {
            if (cam.position == AVCaptureDevicePositionFront)
                videoDevice = cam;
        }
        videoInput = [[AVCaptureDeviceInput alloc]initWithDevice:videoDevice error:nil];


        AVCaptureDevice *audioDevice = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeAudio];
        NSArray *devices = [AVCaptureDevice devicesWithMediaType:AVMediaTypeAudio];
        if ([devices count] > 0) {
            audioDevice = [devices objectAtIndex:0];
        }
        audioInput = [[AVCaptureDeviceInput alloc]initWithDevice:audioDevice error:nil];

        if(error)
        {
            NSLog(@"error = %@",error );
            
        }
        [_cameraOverlayView.layer addSublayer:captureVideoPreviewLayer];
        
        
        movieFileOutput = [[AVCaptureMovieFileOutput alloc] init];
        NSString *outputpathofmovie = [self findUniqueSavePath:@"MOVIE"];
        NSLog(@"outputpathofmovie = %@",outputpathofmovie);
        NSURL *outputURL = [[NSURL alloc] initFileURLWithPath:outputpathofmovie];
        NSFileManager *fileManager = [NSFileManager defaultManager];
        if ( [fileManager fileExistsAtPath:outputpathofmovie] )
        {
            NSError *error;
            if ( [fileManager removeItemAtPath:outputpathofmovie error:&error] == NO )
            {
                NSLog(@"%@", error);
                // Error - handle if required
            }
        }        
        if([captureVideoPreviewLayer.session canAddInput:audioInput])
            [captureVideoPreviewLayer.session addInput:audioInput];
        
        if([captureVideoPreviewLayer.session canAddInput:videoInput])
            [captureVideoPreviewLayer.session addInput:videoInput];
        
        [captureVideoPreviewLayer.session addOutput:movieFileOutput];
        [captureVideoPreviewLayer.session commitConfiguration];
        [captureVideoPreviewLayer.session startRunning];
        [movieFileOutput connections];
        AVCaptureConnection *videoConnection = [self connectionWithMediaType:AVMediaTypeVideo fromConnections:[movieFileOutput connections]];


        [videoConnection setVideoOrientation: [[UIApplication sharedApplication] statusBarOrientation] ];
        [movieFileOutput startRecordingToOutputFileURL:outputURL recordingDelegate:self];
        [self checkCameraRotation:captureVideoPreviewLayer];

    }
    [session release];
    session = nil;

}

- (void)captureOutput:(AVCaptureFileOutput *)captureOutput didStartRecordingToOutputFileAtURL:(NSURL *)fileURL fromConnections:(NSArray *)connections
{
    NSLog(@"fileURL = %@",fileURL);
}

- (void)captureOutput:(AVCaptureFileOutput *)captureOutput didFinishRecordingToOutputFileAtURL:(NSURL *)outputFileURL fromConnections:(NSArray *)connections error:(NSError *)error
{
    NSLog(@"fileURL = %@",outputFileURL);
    BOOL recordedSuccessfully = YES;
    if ( [error code] != noErr )
    {
        id value = [[error userInfo] objectForKey:AVErrorRecordingSuccessfullyFinishedKey];
        if ( value ) recordedSuccessfully = [value boolValue];
    }

    if ( recordedSuccessfully )
    {
        ALAssetsLibrary *library = [[ALAssetsLibrary alloc] init];
        if ( [library videoAtPathIsCompatibleWithSavedPhotosAlbum:outputFileURL] )
        {
            [library writeVideoAtPathToSavedPhotosAlbum:outputFileURL completionBlock:^(NSURL *assetURL, NSError *error) {
                if ( error )
                {
                    
                }
            }];
        }
        
        CJCameraInterface::getInstance()->onVideolRecordingCallBack([_saveMovieName UTF8String]);
    }

}

- (void)checkCameraRotation:(AVCaptureVideoPreviewLayer*)capturePreview
{
    
    if (capturePreview)
    {
        switch ([[UIApplication sharedApplication] statusBarOrientation])
        {
            case UIInterfaceOrientationLandscapeRight:
                [capturePreview.connection setVideoOrientation:AVCaptureVideoOrientationLandscapeRight];
                break;
            case UIInterfaceOrientationLandscapeLeft:
                [capturePreview.connection setVideoOrientation:AVCaptureVideoOrientationLandscapeLeft];
                break;

        }
        
    }
}


- (void)moveToCameraView:(int)x positionY:(int)y
{
    
    x = x * [AppController getScaleValue] + [AppController getLetterBoxPositionX];
    y = y * [AppController getScaleValue];
    
    CGSize originSize = _cameraOverlayView.bounds.size;
    [_cameraOverlayView setFrame:CGRectMake(x, y, originSize.width, originSize.height)];
    [_tempImageView setFrame:CGRectMake(x, y, originSize.width, originSize.height)];
}


- (void)dealloc
{
    
	[_session release];
    [super dealloc];

}


@end

