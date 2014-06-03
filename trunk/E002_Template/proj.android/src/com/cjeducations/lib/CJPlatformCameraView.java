package com.cjeducations.lib;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;
import java.util.Locale;
 
import android.app.Activity;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Path;
import android.graphics.RectF;
import android.hardware.Camera;
import android.hardware.Camera.CameraInfo;
import android.hardware.Camera.Size;
import android.media.CamcorderProfile;
import android.media.MediaRecorder;
import android.os.Environment;
import android.util.AttributeSet;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceHolder.Callback;
import android.view.SurfaceView;

public class CJPlatformCameraView extends SurfaceView implements Callback 
{
	private static int FRONT_DIRECTION = 0;
	private static int REAR_DIRECTION = 1;
	
    private Camera camera = null;
    private SurfaceHolder holder = null;
    private int direction = 0;
    private String pictureName;
    private Context context;
    private Activity activity;
    private int cameraId = 0;
    static int rotation = 0;
    private static int cameraFixedSize = 640;
    private MediaRecorder mRecorder = null;
    private String mRecordeFileName;
    private boolean mIsShowPreivew;
    private boolean mIsRecording;
    
    public void init()
    {
        holder = getHolder();
        holder.addCallback(this); 
    }
 
    public CJPlatformCameraView(Context context, int direction, Activity activity) {
         super(context);
         this.context = context;
         this.direction = direction;
         this.activity = activity;
         rotation = activity.getWindowManager().getDefaultDisplay().getRotation();
         init();
    }
 
    public CJPlatformCameraView(Context context, AttributeSet attr) {
        super(context, attr);
        this.context = context;
        init();
    }
    
    public void changeCameraOrientation()
    { 
        int currentRotation = ((Activity)context).getWindowManager().getDefaultDisplay().getRotation();
        if(currentRotation != rotation)
        {
	    	//camera.stopPreview();
	    	setCameraDisplayOrientation(context, cameraId, camera);
        }
    }
    
    public static void setCameraDisplayOrientation(Context activity, int cameraId, android.hardware.Camera camera) 
    { 
        android.hardware.Camera.CameraInfo info = new android.hardware.Camera.CameraInfo();
        android.hardware.Camera.getCameraInfo(cameraId, info);
        rotation = ((Activity)activity).getWindowManager().getDefaultDisplay().getRotation();
        int degrees = 0;
        switch (rotation) 
        {
            case Surface.ROTATION_0: degrees = 0; break;
            case Surface.ROTATION_90: degrees = 90; break;
            case Surface.ROTATION_180: degrees = 180; break;
            case Surface.ROTATION_270: degrees = 270; break;
        }

        int result;
        if (info.facing == Camera.CameraInfo.CAMERA_FACING_FRONT) 
        {
            result = (info.orientation + degrees) % 360;
            result = (360 - result) % 360;  // compensate the mirror
        } 
        else // back-facing 
        {  
            result = (info.orientation - degrees + 360) % 360;
        }
        
        try {
        	 if(camera != null)
             	camera.setDisplayOrientation(result);
		} catch (Exception e) {
			e.printStackTrace();
		}
       

    }
    
    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height)
    { 
    	cameraSetting();
    }
 
    @Override
    public void surfaceCreated(SurfaceHolder holder)  
    {
    	startCamera();
    }
 
    @Override
    public void surfaceDestroyed(SurfaceHolder holder) 
    {
    	if(mRecorder != null)
    	{
    		mRecorder.release();
    		mRecorder = null;
    	}
    	
        if(camera != null) 
        { 
            camera.release(); 
            camera = null;
        }
    }
 
    
    public void takePicture()
    {
		if(camera != null)
		{
			try
			{
				//For auto focusing 
				camera.autoFocus(new Camera.AutoFocusCallback() {
					@Override
					public void onAutoFocus(boolean success, Camera camera) { 
						camera.takePicture(mShutterCallback, rawC, jpegC);
					}
				});
			}
			catch(Exception e){
				e.printStackTrace();
			}
		}
    }
    
    public void initRecording(String filePath)
    { 
    	if(mRecorder != null)
    	{
    		mRecorder.release();
    		mRecorder  = null;
    	}
    	
    	mRecorder = new MediaRecorder();
    
    	if(camera == null)
    	{ 
    		return;
    	} 
    	 
    	mRecordeFileName = filePath;
    	
    	camera.unlock();
    	 
    	mRecorder.setCamera(camera);
    	mRecorder.setPreviewDisplay(holder.getSurface());
    	mRecorder.setVideoSource(MediaRecorder.VideoSource.CAMERA);
    	mRecorder.setAudioSource(MediaRecorder.AudioSource.MIC);
    	mRecorder.setProfile(CamcorderProfile.get(CamcorderProfile.QUALITY_HIGH));
    	mRecorder.setVideoSize(640, 480);    	    	
    	mRecorder.setMaxDuration(120000);
    	mRecorder.setMaxFileSize(0);
    	
    	try 
    	{	
    		setRecordingStatus(true);
    		
    		mRecorder.setOutputFile(CJPlatformFileManager.getSavePathToSDCard(mRecordeFileName));
        	mRecorder.prepare();
        	mRecorder.start();
        	
		} catch (Exception e) {
			e.printStackTrace();
		}
    	
    }
    
    public void stopRecording()
    {
    	if(mRecorder != null)
    	{
    		try {
    			setRecordingStatus(false);
    			videoRecordingFinishCall(mRecordeFileName);
    			
    			mRecorder.stop();
            	mRecorder.release();
            	
            	//closeCamera(); 
            	
			} catch (Exception e) {
				e.printStackTrace();
			}
    	}
    }
    
    public void setRecordingStatus(boolean isRecording)
    {
    	mIsRecording = isRecording;
    }
    
    public boolean getRecordingStatus()
    {
    	return mIsRecording;
    }
    
    public void startPreview() 
    {
    	mIsShowPreivew = true;
    	
    	if(camera != null)
    	{
    		camera.startPreview();
    	}
    	else
    	{
    		startCamera();
    	}
    	deleteFile();
    }
    
    public void switchCamera()
    {
		if(camera != null)
		{
			closeCamera();
			
			if(direction == FRONT_DIRECTION)
			{
				direction = REAR_DIRECTION;
				startCamera();
				cameraSetting();
			}
			else
			{
				direction = FRONT_DIRECTION;
				startCamera();
				cameraSetting();
			}
		}
    }
    
    public void setShowPreview(boolean isShow)
    {
    	mIsShowPreivew = isShow;
    }
    
    public boolean isShowPreview()
    {
    	return mIsShowPreivew;
    }
    
    private void startCamera()
    {
        int numberOfCameras = Camera.getNumberOfCameras();
        CameraInfo cameraInfo = new CameraInfo();

        for(int i=0; i < numberOfCameras; i++) 
        {
            Camera.getCameraInfo(i, cameraInfo);
            
            if(direction == FRONT_DIRECTION)
            {
	            if(cameraInfo.facing == CameraInfo.CAMERA_FACING_FRONT)
	            {
	                cameraId = i;
	            }
            }
            else
            {
            	if(cameraInfo.facing == CameraInfo.CAMERA_FACING_BACK)
	            {
	                cameraId = i;
	            }
            }
        }
  
        synchronized (this) 
        {
        	camera = Camera.open(cameraId);

            try{
                camera.setPreviewDisplay(holder);
                
            }catch(IOException e){
                e.printStackTrace();
                camera.release();
                camera = null;
            }
		}
    }
    
    private void closeCamera() 
    {
    	if(camera!=null)
    	{
    		mIsShowPreivew = false;
			camera.stopPreview(); 
			camera.release();
			camera = null; 
    	}
    	
    	CJPlatformHelper.removeCameraView();
    }
    
    private void cameraSetting()
    {
        if(camera != null) 
        { 
            Camera.Parameters params = camera.getParameters();
            Camera.Size size;
            int cameraParam = 0;
            
            List<Camera.Size>previewSizeList = params.getSupportedPreviewSizes();
            
            int listSize = previewSizeList.size();
            Size previewWidth;
            
            for(int i= 0; i < listSize; i++)
            {
            	previewWidth = previewSizeList.get(i);
            	if(previewWidth.width == cameraFixedSize)
            	{
            		cameraParam = i;
            	}
            }
            
        	size = params.getSupportedPreviewSizes().get(cameraParam); //640, 480
           	
            params.setPreviewSize(size.width, size.height);
            camera.setParameters(params);
            camera.startPreview();
             
        }
    }

    public void deleteFile() //If user selects retake, it delete saved file.
    {
    	if(pictureName != null)
    	{
    		File delFile = new File(pictureName);
	    	delFile.delete();
    	}
    }
    
	Camera.PictureCallback rawC = new Camera.PictureCallback() 
	{
		@Override
		public void onPictureTaken(byte[] data, Camera camera) {
		}
	};
	
    Camera.PictureCallback jpegC = new Camera.PictureCallback() 
    {
		@Override
		public void onPictureTaken(byte[] data, Camera camera) 
		{
			//Save a picture
			File sd = Environment.getExternalStorageDirectory();
			
			long captureDate = System.currentTimeMillis();
			Date today = new Date(captureDate);
			SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd-HH_mm_ss" , Locale.KOREA);
			String dTime = formatter.format(today);
			
			FileOutputStream outStream = null;
			try{
				pictureName = String.format(sd+"/CJEducations/%s.jpg", dTime);
				outStream = new FileOutputStream(pictureName);
				outStream.write(data);
				outStream.close();
				outStream = null;
			}
			catch(Exception e){
				e.printStackTrace();
			}
			
			//Send msg to Cocos2D-X 
			pictureFinishCall(pictureName);
		}
	};
	
	Camera.ShutterCallback mShutterCallback = new Camera.ShutterCallback() {
		@Override
		public void onShutter() {
		}
	};

	private native void pictureFinishCall(String picPath);
	private native void videoRecordingFinishCall(String recPath);
}