
package com.cjeducations.lib;

import com.cjeducations.ithink.e002.E002Template;

import android.app.Activity;
import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.Intent;
import android.media.AudioManager;
import android.net.Uri;
import android.os.Handler;
import android.os.Message;  
import android.util.Log;

public class CJPlatformHelper {
	 
	// ===========================================================
	// Fields
	// ===========================================================
	public static final int PLAY_VIDEO_ACTIVITY = 100; 
	
	private static final int ADD_VIDEO_BTN_MSG = 101;
	private static final int SHOW_CAMERA_PREVIEW_MSG = 102;
	private static final int MOVE_TO_CAMERA_VIEW_MSG = 103;
	private static final int REMOVE_CAMERA_VIEW_MSG = 104;
	private static final int PLAY_FRAME_VIDEO_MSG = 105;
	private static final int REMOVE_FRAME_VIDEO_VIEW_MSG = 106;
	private static final int VOICE_RECORDING_INIT_MSG = 107;
	private static final int VOICE_RECORDING_PAUSE_MSG = 108;
	private static final int VOICE_RECORDING_RESUME_MSG = 109;
	private static final int FRAME_VIDEO_RECORDING_MSG = 110;
	private static final int PLAY_RECORDED_VOICE_MSG = 111; 
			
	private static CJPlatformNarration mNarrationInstance;
	private static CJPlatformVideo mVideoInstance;
	private static CJPlatformCameraView mCameraViewInstance;
	private static CJPlatformFrameVideoView mFrameVideoViewInstance;
	private static CJPlatformVoiceRecorder mVoiceRecorderInstance;
	
 	private static Context sContext = null;
 
	// ===========================================================
	// Constructors
	// ===========================================================

	public static void init(final Context pContext) 
	{
		CJPlatformHelper.sContext = pContext;
		CJPlatformHelper.mNarrationInstance = new CJPlatformNarration(pContext);
	}
	
	// ===========================================================
	// Set Inastance
	// ===========================================================
	
	public static void setVideoInstance(CJPlatformVideo video)
	{
		mVideoInstance = video;
	}
	
	public static void setCameraViewInstane(CJPlatformCameraView view)
	{
		mCameraViewInstance = view;
	}
	
	public static void setFrameVideoViewInstane(CJPlatformFrameVideoView view)
	{
		mFrameVideoViewInstance = view;
	}

	// ===========================================================
	// Methods
	// ===========================================================

	public static int getDeviceVolume()
	{
		AudioManager am = (AudioManager)sContext.getSystemService(Context.AUDIO_SERVICE);
		int st = AudioManager.STREAM_MUSIC;
		
		return am.getStreamVolume(st);
	}
	
	// ===========================================================
	// Narration
	// ===========================================================
	public static void preloadNarration(final String pPath) 
	{ 
		 CJPlatformHelper.mNarrationInstance.preloadNarration(pPath);
	}

	public static void playNarration(final String pPath, final boolean isLoop) 
	{ 
		 CJPlatformHelper.mNarrationInstance.playNarration(pPath, isLoop);
	}

	public static void playAllNarration(final boolean isLoop) 
	{ 
		CJPlatformHelper.mNarrationInstance.playAllNarration(isLoop);
	}
	
	public static void stopAllNarration() 
	{
		CJPlatformHelper.mNarrationInstance.stopAllNarration();
	}
	
	public static void removeAllNarration() 
	{
		CJPlatformHelper.mNarrationInstance.removeAllNarration();
	}
	
	public static void stopNarration(final String pPath) 
	{
		CJPlatformHelper.mNarrationInstance.stopNarration(pPath);
	}

	public static void pauseAllNarration() 
	{
		CJPlatformHelper.mNarrationInstance.pauseAllNarration();
	}
	
	public static void pauseNarration(final String pPath) 
	{
		CJPlatformHelper.mNarrationInstance.pauseNarration(pPath);
	}

	public static void resumeAllNarration() 
	{
		CJPlatformHelper.mNarrationInstance.resumeAllNarration();
	}
	
	public static void resumeNarration(final String pPath) 
	{
		CJPlatformHelper.mNarrationInstance.resumeNarration(pPath);
	}

	public static void pauseToPlayingNarration() 
	{
		CJPlatformHelper.mNarrationInstance.pauseToPlayingNarration();
	}
	
	public static void resumePausedNarration() 
	{
		CJPlatformHelper.mNarrationInstance.resumePausedNarration();
	}
	
	public static int getCurrentPosition(final String pPath)
	{
		return CJPlatformHelper.mNarrationInstance.getCurrentPosition(pPath);
	}
	
	public static boolean isNarrationPlaying() 
	{
		return CJPlatformHelper.mNarrationInstance.isNarrationPlaying();
	}

	public static void narrationEnd() 
	{
		CJPlatformHelper.mNarrationInstance.end();
	}

	public static float getNarrationMainVolume() 
	{ 
		return CJPlatformHelper.mNarrationInstance.getNarrationMainVolume();
	}
	
	public static void setNarrationMainVolume(float pVolume) 
	{
		CJPlatformHelper.mNarrationInstance.setNarrationMainVolume(pVolume);
	}

	public static void setNarrationVolume(float pVolume) 
	{
		CJPlatformHelper.mNarrationInstance.setNarrationVolume(pVolume);
	}
	
	public static int getNarrationTime(final String path)
	{
		return CJPlatformHelper.mNarrationInstance.getNarrationTime(path);
	}
	 
	public static void end() 
	{
		CJPlatformHelper.mNarrationInstance.end();
	}

	///////////
	// Video //
	///////////
	public static void playVideo(String filePath, boolean isControllerVisible) 
	{
		Intent intent = new Intent(CJPlatformHelper.sContext, CJPlatformVideo.class);
		intent.putExtra("VIDEO_FILEPATH", filePath);
		intent.putExtra("CONTROLLER_VISIBLE", isControllerVisible);
		
		((Activity)CJPlatformHelper.sContext).startActivityForResult(intent, PLAY_VIDEO_ACTIVITY);
	}

	public static void pauseVideo()
	{ 
		mVideoInstance.pauseVideo();
	}
	
	public static void resumeVideo() 
	{
		mVideoInstance.resumeVideo();
	}

	public static void stopVideo() 
	{
		mVideoInstance.stopVideo();
	}
	
	public static void addVideoBtn(final String filePath, final float x, final float y,final int tag) 
	{ 
		CJPlatformVideoButtonInfo btnInfo = new CJPlatformVideoButtonInfo(filePath, x, y, tag);
		
		Message msg = new Message();
		msg.what = ADD_VIDEO_BTN_MSG;
		msg.obj = btnInfo;
		
		mHandler.sendMessageDelayed(msg, 500);
	}
	
	public static void playFrameVideo(final String frameImgPath, final String contentPath, final int x, final int y, final int width, final int height)
	{
		CJPlatformFrameViewInfo info = new CJPlatformFrameViewInfo(frameImgPath, contentPath, x, y, width, height);
		
		Message msg = new Message();
		msg.what = PLAY_FRAME_VIDEO_MSG;
		msg.obj = info;
		
		mHandler.sendMessage(msg);
	}
	
	public static void pauseFrameVideo()
	{
		if(mFrameVideoViewInstance != null)
			mFrameVideoViewInstance.onPause();
	}
	
	public static void resumeFrameVideo()
	{
		if(mFrameVideoViewInstance != null)
			mFrameVideoViewInstance.onResume();
	}
	
	public static void removeFrameVideoView()
	{
		mHandler.sendEmptyMessage(REMOVE_FRAME_VIDEO_VIEW_MSG);
	}
	
	///////////
	// Camera //
	///////////
	public static void showCameraPreview(final String frameImgPath, final int direction, final int x, final int y, final int width, final int height)
	{
		CJPlatformFrameViewInfo info = new CJPlatformFrameViewInfo(frameImgPath, direction, x, y, width, height);
		
		Message msg = new Message();
		msg.what = SHOW_CAMERA_PREVIEW_MSG;
		msg.obj = info;
		
		mHandler.sendMessage(msg);  
	}

	public static void takePicture()
	{ 
		mCameraViewInstance.takePicture();
	}

	public static void startRecording(final String contentPath)
	{		
		
		Message msg = new Message();
		msg.what = FRAME_VIDEO_RECORDING_MSG;
		msg.obj = contentPath;
		
		mHandler.sendMessage(msg);
	}
	
	public static void stopCameraRecording()
	{ 
	    mCameraViewInstance.stopRecording(); 
	}
	
	public static void removeCameraView()
	{
		mHandler.sendEmptyMessage(REMOVE_CAMERA_VIEW_MSG);
	}
	
	public static void moveToCameraView(int x, int y)
	{
		Message msg = new Message();
		msg.arg1 = x;
		msg.arg2 = y;
		msg.what = MOVE_TO_CAMERA_VIEW_MSG;
		
		mHandler.sendMessage(msg);		 
	}
	
	public static boolean isShowPreivew()
	{ 
		return mCameraViewInstance.isShowPreview();
	}
	
	// =================================================== 
	// Voice Recorder 
	// ===================================================
	public static void recVoiceRecording(String filePath)
	{
		Message msg = new Message();
		msg.obj = filePath;
		msg.what = VOICE_RECORDING_INIT_MSG;
		
		mHandler.sendMessage(msg);
	}
	
	public static void pauseVoiceRecording()
	{  
		mHandler.sendEmptyMessage(VOICE_RECORDING_PAUSE_MSG);
	}
	
	public static void resumeVoiceRecording()
	{  
		mHandler.sendEmptyMessage(VOICE_RECORDING_RESUME_MSG);
	}
	
	public static void stopVoiceRecording()
	{ 
		if(mVoiceRecorderInstance != null)
			mVoiceRecorderInstance.stopVoiceRecording();
	}
	
	public static void playRecordedVoice(String filePath)
	{
		Message msg = new Message();
		msg.obj = filePath;
		msg.what = PLAY_RECORDED_VOICE_MSG;
		
		mHandler.sendMessage(msg);
	}
	
	public static void pauseRecordedVoice()
	{  
		if(mVoiceRecorderInstance != null)
		{ 
			mVoiceRecorderInstance.pauseRecordedVoice();
		}
			
	}
	
	public static void resumeRecordedVoice()
	{ 
		if(mVoiceRecorderInstance != null)
		{ 
			mVoiceRecorderInstance.resumeRecordedVoice();
		}
	}
	
	public static void stopRecordedVoice()
	{
		if(mVoiceRecorderInstance != null)
			mVoiceRecorderInstance.stopRecordedVoice();
	}
	
	// ======================================================
	// Uri Connection 
	// ======================================================
	
	public static void showBrowser(String uriPath)
	{	
		Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse(uriPath));
        try
        {
        	CJPlatformHelper.sContext.startActivity(intent);

        }
        catch ( ActivityNotFoundException e )
        {
        	e.printStackTrace();
        }
	}
 
	// ======================================================
	// Handler 
	// ======================================================
	static Handler mHandler = new Handler()
	{
		public void handleMessage(Message msg) { 
			super.handleMessage(msg);
			
			switch (msg.what) 
			{
				case ADD_VIDEO_BTN_MSG:
					if(mVideoInstance != null)
						mVideoInstance.addButton((CJPlatformVideoButtonInfo)msg.obj);
				break;
				case SHOW_CAMERA_PREVIEW_MSG:
					((E002Template)sContext).addCameraPreviewView((CJPlatformFrameViewInfo)msg.obj);
				break;
				case FRAME_VIDEO_RECORDING_MSG:
					((E002Template)sContext).startRecording((String)msg.obj);
				break;
				case PLAY_FRAME_VIDEO_MSG:
					((E002Template)sContext).addFrameVideoView((CJPlatformFrameViewInfo)msg.obj);
				break;
				case REMOVE_CAMERA_VIEW_MSG:
					((E002Template)sContext).removeSurfaceView(E002Template.TAG_CAMERAVIEW);
				break;
				case REMOVE_FRAME_VIDEO_VIEW_MSG:
					((E002Template)sContext).removeSurfaceView(E002Template.TAG_FRAMEVIDEOVIEW);
				break;
				case VOICE_RECORDING_INIT_MSG: 
					mVoiceRecorderInstance = new CJPlatformVoiceRecorder(sContext);
					mVoiceRecorderInstance.recVoiceRecording((String)msg.obj);
				break;
				case VOICE_RECORDING_PAUSE_MSG:  
					if(mVoiceRecorderInstance != null)
						mVoiceRecorderInstance.pauseVoiceRecording();
				break;
				case VOICE_RECORDING_RESUME_MSG:  
					if(mVoiceRecorderInstance != null)
						mVoiceRecorderInstance.resumeVoiceRecording();
				break;
				case MOVE_TO_CAMERA_VIEW_MSG:  
					((E002Template)sContext).moveCameraView(msg.arg1, msg.arg2);  
					break; 
				case PLAY_RECORDED_VOICE_MSG:  
					if(mVoiceRecorderInstance == null)
					{
						mVoiceRecorderInstance = new CJPlatformVoiceRecorder(sContext);
					}
					mVoiceRecorderInstance.playRecordedVoice((String)msg.obj);  
					break;  
			default:
				break;
			}
		}
	}; 
}
