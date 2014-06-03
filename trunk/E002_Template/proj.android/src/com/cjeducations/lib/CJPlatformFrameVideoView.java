package com.cjeducations.lib;
 
import java.io.FileInputStream;

import android.app.Activity;
import android.content.Context; 
import android.media.MediaPlayer; 
import android.media.MediaPlayer.OnCompletionListener; 
import android.os.Environment;
import android.util.AttributeSet;  
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceHolder.Callback;
import android.view.SurfaceView; 

public class CJPlatformFrameVideoView extends SurfaceView implements Callback 
{ 
    private SurfaceHolder holder = null;
    
    private Context context;
    private Activity activity;
   
    private MediaPlayer mPlayer;
    private String mPath;
    private int mCurrentPosition;
    private boolean isPaused;
    
    public void init()
    {
        holder = getHolder();
        holder.addCallback(this);  
    }
 
    public CJPlatformFrameVideoView(Context context, AttributeSet attr) {
        super(context, attr);
        init();
    }
    
    public void setVideoPath(String path)
    {
    	mPath = path;
    }
    
    public void onPause()
    {  
    	if(mPlayer != null)
		{ 
    		isPaused = true; 
			mCurrentPosition = mPlayer.getCurrentPosition(); 
			mPlayer.pause();
		}
    }
    
    public void onResume()
    { 
    	if(mPlayer != null)
		{  
			mPlayer.seekTo(mCurrentPosition);
			mPlayer.start();
		}
    }
    
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height)
    { 
    }
 
    public void surfaceCreated(SurfaceHolder holder)  
    {   
    	mPlayer = new MediaPlayer();
    		
    	try 
   		{ 
   			FileInputStream fs = new FileInputStream(CJPlatformFileManager.getSavePathToSDCard(mPath));
   			mPlayer.setDataSource(fs.getFD());
    			
   			mPlayer.setDisplay(holder);
   			mPlayer.prepare(); 
    	}
    	catch ( Exception e) 
   		{
   		 	e.printStackTrace();
   		}
    		
   		mPlayer.setOnCompletionListener(new OnCompletionListener() 
    	{
    		public void onCompletion(MediaPlayer arg0) 
   			{
   				frameVideoFinishCall();
   			}
   		});
   		
   		if(isPaused)
   		{ 
   			mPlayer.seekTo(mCurrentPosition);
   		}
   		
		mPlayer.start();
		isPaused = false;
    }
 
    public void surfaceDestroyed(SurfaceHolder holder) 
    {  
    	if(mPlayer != null)
    	{
    		mPlayer.release();
    		mPlayer = null;
    	}
    }
  
	private native void frameVideoFinishCall();
}