
package com.cjeducations.lib;
    
import java.util.ArrayList;

import com.cjeducations.ithink.e002.c010.R;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent; 
import android.content.IntentFilter;
import android.content.res.AssetFileDescriptor;  
import android.graphics.Bitmap;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener; 
import android.media.MediaPlayer.OnPreparedListener;  
import android.os.Bundle;   
import android.os.Handler;
import android.os.Message; 
import android.os.PowerManager;
import android.os.PowerManager.WakeLock;
import android.util.DisplayMetrics;
import android.util.Log; 
import android.view.Display;
import android.view.KeyEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.view.ViewTreeObserver;
import android.view.WindowManager;
import android.widget.ImageView; 
import android.widget.RelativeLayout; 
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.TextView;
import android.widget.RelativeLayout.LayoutParams; 
import android.widget.SeekBar;


public class CJPlatformVideo extends Activity {
	
	private static Context mContext;
	
	private static final int DATA_FOLDER_ACCESS_TYPE = 0; 
	private static final int ASSERTS_ACCESS_TYPE = 1;
	
	private static final int CONTROLLER_VISIBLE_MSG = 100; 
	private static final int TIME_AND_SEEKBAR_CONTROL_MSG = 101;
	private static final int PAUSE_VIDEO_FOR_VISIBLE_MSG = 102;
	 	
	private static final String SCREEN_OFF_ACTION_NAME = "android.intent.action.SCREEN_OFF";
	private static final String SCREEN_ON_ACTION_NAME = "android.intent.action.SCREEN_ON";
	
	private MediaPlayer mPlayer;
	
	private Boolean isMovieComplete;
	private int mCurrentTime;

	static Context helper;
	private Thread mThread;

	private int mCurrentAccessType;
	
	//View
	private RelativeLayout mLayout;
	private ImageView mPlayBtn;
	//private ImageView mIndexBtn, mSkipBtn;
	private SeekBar mSeekBar;
	private TextView mPlayTime;
	private TextView mFullTime;
	private ImageView mSeekBarBG;
	
	private boolean mIsVisibleController;
	private boolean mIsIntroMovie;
	
	private String mFilePath;
	private ArrayList<ImageView> mArrButton = new ArrayList<ImageView>();
	
	private int mCurrentPosition;
	
	private boolean isFirstSurfaceCreate;
	private SurfaceHolder mHolder;
	private SurfaceView mSurfaceView;
	private boolean mIsPlaying;
	 
	private Dialog mDialog;
	private boolean mIsScreenOff;
	
	
	public void addButton(final CJPlatformVideoButtonInfo btnInfo) 
	{
		final ImageView btn = new ImageView(mContext);
		btn.setVisibility(View.INVISIBLE);
		mArrButton.add(btn); 
					
		CJPlatformFileManager.setImgThroughFileCheck(mContext, btnInfo.filePath, btn);
 
		Bitmap img = CJPlatformFileManager.getBitmap(mContext, btnInfo.filePath);
 		
		RelativeLayout.LayoutParams params = new RelativeLayout.LayoutParams(CJPlatformDisplayUtil.PixelFromSurface(mContext, img.getWidth(), null, true),
				CJPlatformDisplayUtil.PixelFromSurface(mContext, img.getHeight(), null, false)); 
		
		params.setMargins((int)CJPlatformDisplayUtil.PixelFromSurface(mContext, (int)btnInfo.x, null, true), CJPlatformDisplayUtil.PixelFromSurface(mContext, (int)btnInfo.y, null, false), 0, 0);

		btn.setLayoutParams(params); 
 	
		mLayout.addView(btn);
 
		btn.setOnClickListener(new View.OnClickListener() {

			public void onClick(View v) 
			{
				videoBtnCallBack(btnInfo.tag);
			}
		});
	}

	private Handler mHandler = new Handler(){
		public void handleMessage(Message msg)
		{
			super.handleMessage(msg);
			switch (msg.what) 
			{
			case CONTROLLER_VISIBLE_MSG:
				mPlayBtn.setAlpha(255);
//				mIndexBtn.setAlpha(255);
//				mSkipBtn.setAlpha(255);
				mSeekBar.setAlpha(255);
				mSeekBarBG.setAlpha(255);
				setVisibleOnController(); 
				break;   
			case TIME_AND_SEEKBAR_CONTROL_MSG:
				updatePlayTimeText();
				updateSeekProgress();
				mHandler.sendEmptyMessageDelayed(TIME_AND_SEEKBAR_CONTROL_MSG, 100);
				break; 
			case PAUSE_VIDEO_FOR_VISIBLE_MSG:
				mPlayer.pause();
				break; 
			default:
				break;
			}
		}
	};
	
	public void pauseVideo() 
	{   
		if(mPlayer != null)
		{
			mIsPlaying = false;
			mCurrentPosition = mPlayer.getCurrentPosition();

			mPlayer.pause();
		}

		mPlayBtn.setImageResource(R.drawable.cjplatform_video_btn_play);
		
		mHandler.removeMessages(CONTROLLER_VISIBLE_MSG);
	}

	public void resumeVideo() 
	{ 
		if(mPlayer != null)
		{	  
			mIsPlaying = true;
			mPlayer.start();
		}
			
		mHandler.sendEmptyMessageDelayed(CONTROLLER_VISIBLE_MSG, 3000);
		mPlayBtn.setImageResource(R.drawable.cjplatform_video_btn_pause);
	}

	public void stopVideo() {
		videoFinished();
		finish();
	}
	
	private OnClickListener mVideoClickListener = new OnClickListener() {
		
		public void onClick(View v) 
		{
			if(mIsIntroMovie)
				stopVideo();
			else
				setVisibleOnController();
		}
	};
	
	private OnClickListener mPlayBtnClickListener = new OnClickListener() {
		
		public void onClick(View v) 
		{
			controlVideoPlayer();
		}
	};
	
//	private OnClickListener mIndexBtnClickListener = new OnClickListener() {
//			
//			public void onClick(View v) 
//			{
//				videoIndexCallBack();
//			}
//		};
//		
//	private OnClickListener mSkipBtnClickListener = new OnClickListener() {
//			
//			public void onClick(View v) 
//			{
//				stopVideo();
//			}
//	};
	
	private OnSeekBarChangeListener mSeekBarChangeListener = new OnSeekBarChangeListener() {
		
		Boolean isTouch =false;
		
		public void onStopTrackingTouch(SeekBar seekBar) {
			isTouch = false;
			
			if(mIsVisibleController && mPlayer.isPlaying())
			{
				mHandler.sendEmptyMessageDelayed(CONTROLLER_VISIBLE_MSG, 3000);
			}
		}
		
		public void onStartTrackingTouch(SeekBar seekBar) {
			mHandler.removeMessages(CONTROLLER_VISIBLE_MSG);
			isTouch = true;
		}
		
		public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
			if(isTouch)
			{ 
				mPlayer.seekTo(progress);
			}
		}
	};
	
	SurfaceHolder.Callback mCallBack = new SurfaceHolder.Callback() {
		
		public void surfaceDestroyed(SurfaceHolder holder) 
		{	 
			mPlayer.stop();
			mPlayer.release();
			mPlayer = null;
		}
		
	 	public void surfaceCreated(SurfaceHolder holder) 
	 	{    
	 		if(mPlayer == null)
	 			mPlayer = new MediaPlayer();
	 		
	 		if(mCurrentAccessType == ASSERTS_ACCESS_TYPE)
	 		{
	 			AssetFileDescriptor afd = null;
		 		
				try 
				{ 
					afd = getResources().getAssets().openFd(mFilePath);
					mPlayer.setDataSource(afd.getFileDescriptor(), afd.getStartOffset(), afd.getLength());

				} 
				catch (Exception e)  
				{
					e.printStackTrace();
				} 
				
	 		}
	 		else
	 		{
	 			try {
	 				mPlayer.setDataSource(mFilePath);
				} catch (Exception e) {
					e.printStackTrace();
				}
	 			
	 		}
 			
			try 
			{
				mPlayer.setDisplay(holder);
				mPlayer.prepare(); 
				
				mPlayer.setOnPreparedListener(new OnPreparedListener() {
					 
					public void onPrepared(MediaPlayer mp) {
						mSeekBar.setMax(mPlayer.getDuration()); 
						mFullTime.setText(getTimeToString(mPlayer.getDuration()));
					}
				});
			}
			catch ( Exception e) 
			{
			 	e.printStackTrace();
			}
			
			mPlayer.setOnCompletionListener(new OnCompletionListener() {
				@Override
				public void onCompletion(MediaPlayer arg0) {
					isMovieComplete = true;
					videoFinished();
					finish();
				}
			});
			
			if(isFirstSurfaceCreate)
	 		{
	 			isFirstSurfaceCreate = false;
	 		}
			else
			{
				if(mCurrentPosition > 2000)
					mPlayer.seekTo(mCurrentPosition - 2000);
				
				if(mPlayer != null && !mIsPlaying)
				{ 
					mPlayer.start();
					mHandler.sendEmptyMessageDelayed(PAUSE_VIDEO_FOR_VISIBLE_MSG, 300);
					return;
				}
			}
			
			setVideoSize((float)mPlayer.getVideoWidth(),(float)mPlayer.getVideoHeight());
			
			mIsPlaying = true;
			mPlayer.start();
		}
		
	 	public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) 
	 	{	 
		}
	};
 
 	
 	private void setVideoSize(float width, float height)
 	{
 		//Display display = ((WindowManager)getSystemService(WINDOW_SERVICE)).getDefaultDisplay();
 		DisplayMetrics metrics = getResources().getDisplayMetrics();
 		
 		float displayWidth = metrics.widthPixels;
 		float displayHeight = metrics.heightPixels;
 		
 		//thinkle tab
 		//displayHeight = 768;
 		
 		try {
 			if(width == 0 || height == 0)
 			{
 				videoFinished();
 			}
 			else if(width > height)
 	 		{ 
 	 			float rate = (float) (displayWidth / width);  
 	 			
 	 			float tempHeight = height * rate; 
 	 			if(tempHeight > displayHeight)
 	 			{ 
 	 				float heightRate = displayHeight / tempHeight; 
 	 				mHolder.setFixedSize((int)(displayWidth * heightRate), (int)displayHeight);
 	 			}
 	 			else
 	 				mHolder.setFixedSize((int)displayWidth, (int) (height * rate));
 	 		}
 	 		else
 	 		{
 	 			float rate = displayHeight / height;
 	 			
 	 			float tempWidht = width * rate;
 	 			
 	 			if(tempWidht > displayWidth)
 	 			{
 	 				float widthRate = displayWidth / tempWidht;
 	 				mHolder.setFixedSize((int) displayWidth, (int) (displayHeight * widthRate));
 	 			}
 	 			else
 	 				mHolder.setFixedSize((int) (width * rate), (int) displayHeight);
 	 		}
		} catch (Exception e) {
			e.printStackTrace();
		}
 		
 	}
 	
	private void controlVideoPlayer()
	{
		if(mPlayer.isPlaying())
			pauseVideo();
		else
			resumeVideo();
	}
	
	private void setVisibleOnController()
	{
		//setTouchListener();
		
		if(mIsVisibleController)
 		{ 
 			mPlayBtn.setVisibility(View.INVISIBLE);
// 			mIndexBtn.setVisibility(View.INVISIBLE);
// 			mSkipBtn.setVisibility(View.INVISIBLE);
 			mSeekBar.setVisibility(View.INVISIBLE);
 			mPlayTime.setVisibility(View.INVISIBLE);
 		 	mFullTime.setVisibility(View.INVISIBLE);
 			mSeekBarBG.setVisibility(View.INVISIBLE); 
 		 	
 		 	for (int i = 0; i < mArrButton.size(); i++) 
 		 	{
 		 		mArrButton.get(i).setVisibility(View.INVISIBLE);
			}
 		 	
 			mIsVisibleController = false;
 			
 			mHandler.removeMessages(CONTROLLER_VISIBLE_MSG);
 			mHandler.removeMessages(TIME_AND_SEEKBAR_CONTROL_MSG);
 		}
 		else
 		{  
 			mPlayBtn.setVisibility(View.VISIBLE);
// 			mIndexBtn.setVisibility(View.VISIBLE);
// 			mSkipBtn.setVisibility(View.VISIBLE);
 			mSeekBar.setVisibility(View.VISIBLE);
 			mPlayTime.setVisibility(View.INVISIBLE);
 			mFullTime.setVisibility(View.INVISIBLE);
 			mSeekBarBG.setVisibility(View.VISIBLE);
 			
 			for (int i = 0; i < mArrButton.size(); i++) 
 		 	{
 		 		mArrButton.get(i).setVisibility(View.VISIBLE);
			}
 			
 			mIsVisibleController = true;
 			
 			mHandler.sendEmptyMessageDelayed(CONTROLLER_VISIBLE_MSG, 3000);
 			mHandler.sendEmptyMessage(TIME_AND_SEEKBAR_CONTROL_MSG);
 		}
	}
	
	private void setType()
	{
		if(mFilePath != null && mFilePath.startsWith("/")) 
		{
			mCurrentAccessType = DATA_FOLDER_ACCESS_TYPE;
		}
		else
		{
			mCurrentAccessType = ASSERTS_ACCESS_TYPE;
		}
		 
		Log.d("CJPlatformVideo", "mCurrentAccessType = "+ mCurrentAccessType);
	}
	
	private void setVideoInfo()
	{
		mLayout = (RelativeLayout)findViewById(R.id.layout);
		
		mSurfaceView = new SurfaceView(this);
		mHolder = mSurfaceView.getHolder();
 
		mHolder.addCallback(mCallBack);
		mHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
			
		LayoutParams lp = new LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
		lp.addRule(RelativeLayout.CENTER_IN_PARENT);
	
		mSurfaceView.setLayoutParams(lp);
			
		mLayout.addView(mSurfaceView);
 		
		mPlayBtn = (ImageView)findViewById(R.id.play_btn);
		mPlayBtn.bringToFront();
		mPlayBtn.setAlpha(0);
				
		mSeekBarBG = (ImageView)findViewById(R.id.seekbar_bg);
		mSeekBarBG.bringToFront();
		mSeekBarBG.setAlpha(0);
		
		mSeekBar = (SeekBar)findViewById(R.id.seek_bar);
		mSeekBar.bringToFront();
		mSeekBar.setAlpha(0);
		
		mPlayTime = (TextView)findViewById(R.id.play_time);
		mPlayTime.bringToFront();
		
		mFullTime = (TextView)findViewById(R.id.max_time);
		mFullTime.bringToFront();
			 
		setTouchListener();
	}
	
	private void setTouchListener()
	{
		mLayout.setOnClickListener(mVideoClickListener);
		mPlayBtn.setOnClickListener(mPlayBtnClickListener);
		mSeekBar.setOnSeekBarChangeListener(mSeekBarChangeListener);
	}
	
	private String getTimeToString(int duration)
	{
		int time = duration / 1000;
		
		StringBuffer buf = new StringBuffer();
		
		int minutes = time % 3600;
		int seconds = minutes % 60;
		minutes = minutes / 60;
		 
		buf.append(String.format("%02d", minutes));
		buf.append(":");
		buf.append(String.format("%02d", seconds));
		
		return buf.toString();
	}
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState); 
		
		mContext = this;  
 
		CJPlatformHelper.setVideoInstance(this);
		
		isMovieComplete = false;
		isFirstSurfaceCreate = true;
		
		setContentView(R.layout.cjplatform_video_layout);
				
		final Intent intent = getIntent();
		mFilePath = intent.getStringExtra("VIDEO_FILEPATH");
		
		if(intent.getBooleanExtra("CONTROLLER_VISIBLE", true))
		{
			mIsIntroMovie = false;
		}
		else
		{
			mIsIntroMovie = true;
		}
		
		setType();
		
		setVideoInfo(); 
		
		if(mIsIntroMovie)
		{
			mLayout.setOnClickListener(mVideoClickListener);
			mIsVisibleController = false;
		}
		else
		{
			mIsVisibleController = true;
			//mHandler.sendEmptyMessageDelayed(CONTROLLER_VISIBLE_MSG, 700);
			mHandler.sendEmptyMessage(CONTROLLER_VISIBLE_MSG);
		}
	}
 
	protected void onResume() 
	{ 
		super.onResume(); 
	}
 
	protected void onPause() 
	{ 
		super.onPause();  
		pauseVideo();
	}
 
	private void updateSeekProgress()
	{ 
		mSeekBar.setProgress(getCurrentPosition()); 
	}
	private void updatePlayTimeText()
	{
		mPlayTime.setText(getTimeToString(getCurrentPosition()));
	}
	
	private int getCurrentPosition()
	{
		int position = 0;
		 
		if(mPlayer != null)
			position = mPlayer.getCurrentPosition();
		
		return position;
	}
	
	private native void videoFinished();
	private native void videoBtnCallBack(int tag);
	private native void videoIndexCallBack();
	
	 @Override
	    public boolean dispatchKeyEvent(KeyEvent event) 
		{
			if(event.getKeyCode() == KeyEvent.KEYCODE_BACK )
			{
				if(event.getAction()== KeyEvent.ACTION_UP) {
					mDialog = new AlertDialog.Builder(this)
	                .setTitle(getString(R.string.endalert_title))
	                .setMessage(getString(R.string.endalert_msg))
	                .setCancelable(false)
	                .setPositiveButton(getString(R.string.btn_yes),
	                                   new DialogInterface.OnClickListener()
	                                   {
	                    public void onClick(DialogInterface dialog, int whichButton)
	                    {
	                    	Intent intent = new Intent("RESULT_OK");
	                    	setResult(CJPlatformHelper.PLAY_VIDEO_ACTIVITY, intent);
	                    	finish();
	                    }
	                })
	                .setNegativeButton(getString(R.string.btn_no),
	                                   new DialogInterface.OnClickListener() {
	                    @Override
	                    public void onClick(DialogInterface dialog, int which)
	                    {
	                        dialog.dismiss();
	                    }
	                }).create();
	                
					mDialog.show();
	            }
	            return false;
	        }
			else
			{ 
	        	return super.dispatchKeyEvent(event); 
	        }
		}
}
