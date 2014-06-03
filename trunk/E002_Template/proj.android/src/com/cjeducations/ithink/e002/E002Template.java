/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
 
package com.cjeducations.ithink.e002;
 
 
 
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import com.cjeducations.activity.CJPackageActivity;
import com.cjeducations.ithink.e002.c010.R;
 
import android.app.Activity;
import android.app.Dialog;
import android.content.Context;  
import android.content.DialogInterface;
import android.content.DialogInterface.OnKeyListener;
import android.os.Bundle;  
import android.util.DisplayMetrics;
import android.view.Gravity;
import android.view.KeyEvent;
import android.widget.FrameLayout;
import android.widget.TextView;

public class E002Template extends CJPackageActivity{

	public static final String TAG_CAMERAVIEW = "CAMERA_LAYOUT";
	public static final String TAG_FRAMEVIDEOVIEW = "FRAME_VIDEO_LAYOUT";
	
	private static final int SURFACE_DEFAULT_WIDTH_SIZE = 1024;
	private static final int SURFACE_DEFAULT_HEIGHT_SIZE = 768;
	private static final int THINKLE_TAB_HEIGHT_SIZE = 720;
 	
	@SuppressWarnings("static-access")
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);

		setWinSize(); 
	}		
	
	 public Cocos2dxGLSurfaceView onCreateView() {
	    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
	    	// E002Template should create stencil buffer
	    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
	    	
	    	return glSurfaceView;
	    }
	 
	private void setWinSize()
	{
		DisplayMetrics displayMetrics = new DisplayMetrics();
		getWindowManager().getDefaultDisplay().getMetrics(displayMetrics); 
		
		int deviceHeight = displayMetrics.heightPixels;
 	
		FrameLayout.LayoutParams params = (FrameLayout.LayoutParams)mMainLayout.getLayoutParams();
 	 
		if(deviceHeight == THINKLE_TAB_HEIGHT_SIZE)
		{
			params.topMargin = -((SURFACE_DEFAULT_HEIGHT_SIZE - deviceHeight) / 2);
		
			params.height = SURFACE_DEFAULT_HEIGHT_SIZE;   
			params.width = SURFACE_DEFAULT_WIDTH_SIZE;
		}
		else
		{
			
			float rate = (float)deviceHeight / (float)SURFACE_DEFAULT_HEIGHT_SIZE; 
			params.height = deviceHeight; 
			float result = SURFACE_DEFAULT_WIDTH_SIZE * rate; 
			params.width = (int)result;
		}
	
        params.gravity = Gravity.CENTER_HORIZONTAL;
        
		mMainLayout.setLayoutParams(params);
	}
	
	protected void onResume() 
	{
		super.onResume();  
		
		if(mCameraView != null && mCameraView.getRecordingStatus())
		{
			OnPauseVideoRecording();
		}
	}
 
	protected void onPause() 
	{ 
		super.onPause();  
	}
 
 
	
	public void narrationFinishedCallback(final String path)
	{
		runOnGLThread(new Runnable() {
			
			@Override
			public void run() {  
				NarrationFinished(path);
				
			}
		});
	}
	
	public void recordedVoicePlayFinishedCallback()
	{
		runOnGLThread(new Runnable() {
			
			@Override
			public void run() {  
				RecordedVoicePlayFinished();
				
			}
		});
	}
	
	public void showFullLoading(Context context, String message) {
        
		Dialog sFullLoadingDialog;
		
        sFullLoadingDialog = new Dialog(context,android.R.style.Theme_Translucent_NoTitleBar );
        sFullLoadingDialog.setContentView(R.layout.common_full_loading);
        TextView msg = (TextView) sFullLoadingDialog.findViewById(R.id.text);
        
        if(message!=null)
            msg.setText(message);
        
        sFullLoadingDialog.setOnKeyListener(new OnKeyListener() {
            public boolean onKey(DialogInterface dialog, int keyCode, KeyEvent event) {
                if(keyCode==KeyEvent.KEYCODE_BACK)
                {   //listner.onClick(KEY_CANCEL);
                }
                return false;
            }
        });
        
        if (context != null && ((Activity)context).isFinishing() == false)
			sFullLoadingDialog.show(); 
    }
     
    private native void NarrationFinished(String path);
    private native void RecordedVoicePlayFinished();
    private native void OnPauseVideoRecording();

}


