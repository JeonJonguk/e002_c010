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
package com.cjeducations.activity;

import java.io.File;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.ActivityInfo;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.Uri;
import android.net.wifi.SupplicantState;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.os.StatFs;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.OrientationEventListener;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.ImageView;

import com.cjedu.thinkle.lms.openapi.ServiceBindListener;

import com.cjeducations.ithink.e002.c010.R;
import com.cjeducations.lib.CJPlatformCameraView;
import com.cjeducations.lib.CJPlatformDirectory;
import com.cjeducations.lib.CJPlatformFileManager;
import com.cjeducations.lib.CJPlatformFrameVideoView;
import com.cjeducations.lib.CJPlatformFrameViewInfo;
import com.cjeducations.lib.CJPlatformHelper;
import com.cjeducations.lib.CJPlatformLMSExtension;

public abstract class CJPackageActivity extends Cocos2dxActivity implements
		ServiceBindListener {
	// //////////////////////////////////////////////////////////////////////
	//
	// TAG
	//
	// //////////////////////////////////////////////////////////////////////
	private static final int CERTIFICATION_SUCCESS = -1;
	private static final int CERTIFICATION_FAIL = 0;
	private static final int HANDLER_CALL_YOUTUBE = 1;
	private static final int HANDLER_LOW_STORAGE_SIZE = 2;
	private static final int HANDLER_AVAILABLE_SDCARD = 3;

	private static final int PROGRESS_BEFORE = -1;
	private static final int PROGRESS_CURRENT = 0;
	private static final int PROGRESS_AFTER = 1;

	public static final String TAG_CAMERAVIEW = "CAMERA_LAYOUT";
	public static final String TAG_FRAMEVIDEOVIEW = "FRAME_VIDEO_LAYOUT";

	// //////////////////////////////////////////////////////////////////////
	//
	// Member variable.
	//
	// //////////////////////////////////////////////////////////////////////
	private static Handler handler;
	private static String uriPath;
	private static boolean isPopup;
	private static int mWifiStrength = -1;

	// //////////////////////////////////////////////////////////////////////
	//
	// Member Instance.
	//
	// //////////////////////////////////////////////////////////////////////
	private static CJPackageActivity sPackageActivity = null;
	private CJPlatformDirectory mDirectory = null;

	protected CJPlatformFrameViewInfo mCurrentCameraInfo = null;
	protected OrientationEventListener mOrientationEventListener = null;
	protected CJPlatformCameraView mCameraView = null;
	protected FrameLayout mMainLayout = null;

	// //////////////////////////////////////////////////////////////////////
	//
	// Activity LIFE CYCLE.
	//
	// //////////////////////////////////////////////////////////////////////
	@SuppressWarnings("static-access")
	@Override
	protected void onCreate(final Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		sPackageActivity = this;
		isPopup = false;

		// CJPlatform directory initialize.
		mDirectory = new CJPlatformDirectory(this);
		mDirectory.createBaseDir();

		// Get layout info.
		ViewGroup root = (ViewGroup) findViewById(android.R.id.content);
		mMainLayout = (FrameLayout) root.getChildAt(0);
		// set screen
		mMainLayout.setKeepScreenOn(true);
		// set dependency layout.
		this.setThinkleTabDependencyLayout();

		CJPlatformHelper.init(this);
		mOrientationEventListener = new OrientationEventListener(this) {
			@Override
			public void onOrientationChanged(int orientation) {
				if (mCameraView != null)
					mCameraView.changeCameraOrientation();
			}
		};

		// Make handlers.
		this.makeHandler();
		// App start (Init LMS datas after Get user account info from THINKLE
		// Server)
		this.appStart();
		// Regist app receviers.
		this.registCertificationReceiver();
		this.registWifiStrengthReceiver();
	}

	@Override
	protected void onResume() {
		super.onResume();
		CJPlatformHelper.resumeVoiceRecording();
		CJPlatformHelper.resumeFrameVideo();

		this.setOrientation();
	}

	@Override
	protected void onPause() {
		super.onPause();
		CJPlatformHelper.pauseVoiceRecording();
		CJPlatformHelper.pauseFrameVideo();
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();

		this.unregistCertificationReceiver();
		this.unregistWifiStrengthReceiver();

		appEnd();
	}

	@Override
	public void onServiceBind(int arg0) {
		CJPlatformLMSExtension.setAccount();
	}

	protected void onActivityResult(int requestCode, int resultCode, Intent data) {

		super.onActivityResult(requestCode, resultCode, data);

		if (requestCode == CJPlatformHelper.PLAY_VIDEO_ACTIVITY) {
			if (data != null && data.getAction().equals("RESULT_OK")) {
				finish();
				System.exit(0);
			}
		}
	}

	private void setOrientation() {
		if (android.provider.Settings.System.getInt(getContentResolver(),
				android.provider.Settings.System.ACCELEROMETER_ROTATION, 0) == 0) {
			setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
		} else {
			setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR_LANDSCAPE);
		}
	}

	private void makeHandler() {
		handler = new Handler() {
			public void handleMessage(Message msg) {
				Dialog dialog = null;
				switch (msg.what) {
				case HANDLER_CALL_YOUTUBE:
					StringBuilder sb = new StringBuilder("vnd.youtube:");
					sb.append(uriPath);
					Uri uri = Uri.parse(sb.toString());
					Intent it = new Intent(Intent.ACTION_VIEW, uri);
					it.putExtra("VIDEO_ID", uriPath);
					it.putExtra("force_fullscreen", true);
					startActivity(it);
					break;
				// show low storage size alert dialog
				case HANDLER_LOW_STORAGE_SIZE:
					dialog = new AlertDialog.Builder(CJPackageActivity.this)
							.setCancelable(false)
							.setTitle(getString(R.string.low_storage_title))
							.setMessage(getString(R.string.low_storage_desc))
							.setPositiveButton(getString(R.string.app_ok),
									new DialogInterface.OnClickListener() {
										public void onClick(
												DialogInterface dialog,
												int whichButton) {
											finish();
											System.exit(0);
										}
									}).create();

					dialog.show();
					break;
				// show available sdcard alert dialog
				case HANDLER_AVAILABLE_SDCARD:
					dialog = new AlertDialog.Builder(CJPackageActivity.this)
							.setCancelable(false)
							.setTitle(getString(R.string.disable_storage_title))
							.setMessage(
									getString(R.string.disable_storage_desc))
							.setPositiveButton(getString(R.string.app_ok),
									new DialogInterface.OnClickListener() {
										public void onClick(
												DialogInterface dialog,
												int whichButton) {
											finish();
											System.exit(0);
										}
									}).create();

					dialog.show();
					break;
				}
			}
		};
	}

	private void setThinkleTabDependencyLayout() {
		ViewGroup root = (ViewGroup) findViewById(android.R.id.content);
		FrameLayout layout = (FrameLayout) root.getChildAt(0);

		FrameLayout.LayoutParams params = (FrameLayout.LayoutParams) layout
				.getLayoutParams();
		params.topMargin = -24;
		params.height = 768;
		layout.setLayoutParams(params);
	}

	public CJPlatformDirectory getSaveDataInstance() {
		return mDirectory;
	}

	// //////////////////////////////////////////////////////////////////////
	//
	// CERTIFICATION.
	//
	// //////////////////////////////////////////////////////////////////////
	private void registCertificationReceiver() {
		IntentFilter certificationIntentFilter = new IntentFilter();
		certificationIntentFilter.addAction(getApplication().getPackageName());
		registerReceiver(mCertificationReceiver, certificationIntentFilter);
	}

	private void unregistCertificationReceiver() {
		unregisterReceiver(mCertificationReceiver);
	}

	private BroadcastReceiver mCertificationReceiver = new BroadcastReceiver() {
		@Override
		public void onReceive(Context context, Intent intent) {
			// password BroadCast
			int result = intent.getIntExtra("result", 1);
			if (result == CERTIFICATION_FAIL)// Cancel
			{
				certificationCall(CERTIFICATION_FAIL);
			} else if (result == CERTIFICATION_SUCCESS)// Confirm
			{
				certificationCall(CERTIFICATION_SUCCESS);
			}
		}
	};

	// shchoi, It calls Android parent`s password screen.
	public static void callCertification() {
		Intent intent = new Intent(
				"com.cjedu.thinkle.manager.intent.action.CERTIFICATION");
		intent.putExtra("return", sPackageActivity.getPackageName());
		intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK
				| Intent.FLAG_ACTIVITY_CLEAR_TOP
				| Intent.FLAG_ACTIVITY_SINGLE_TOP
				| Intent.FLAG_ACTIVITY_MULTIPLE_TASK);
		intent.addFlags(32);
		sPackageActivity.startActivity(intent);
	}

	private native void certificationCall(int status);

	// //////////////////////////////////////////////////////////////////////
	//
	// WIFI.
	//
	// //////////////////////////////////////////////////////////////////////
	private void registWifiStrengthReceiver() {
		IntentFilter wifiIntentFilter = new IntentFilter(
				WifiManager.RSSI_CHANGED_ACTION);
		wifiIntentFilter.addAction(WifiManager.NETWORK_STATE_CHANGED_ACTION);
		registerReceiver(mWifiStrengthReceiver, wifiIntentFilter);
	}

	private void unregistWifiStrengthReceiver() {
		unregisterReceiver(mWifiStrengthReceiver);
	}

	private BroadcastReceiver mWifiStrengthReceiver = new BroadcastReceiver() {
		@Override
		public void onReceive(Context context, Intent intent) {
			if (WifiManager.RSSI_CHANGED_ACTION.equals(intent.getAction()))
				;
			{
				WifiManager wifiManager = (WifiManager) getSystemService(Context.WIFI_SERVICE);
				WifiInfo wifiInfo = wifiManager.getConnectionInfo();

				if (null != wifiInfo) {
					if (wifiInfo.getSSID() != null
							&& wifiInfo.getBSSID() != null
							&& SupplicantState.COMPLETED == wifiInfo
									.getSupplicantState()
							&& wifiInfo.getIpAddress() != 0) {
						int wifiStrengthLevel = wifiManager
								.calculateSignalLevel(wifiInfo.getRssi(), 10);
						mWifiStrength = wifiStrengthLevel;
					} else {
						mWifiStrength = -1;
					}
				}
			}
		}
	};

	// //////////////////////////////////////////////////////////////////////
	//
	// STORAGE ALERT
	//
	// //////////////////////////////////////////////////////////////////////
	// check storage size
	public static void checkStorageSize() {
		// sh_hong, check sdcard disk size
		StatFs stat = new StatFs(Environment.getExternalStorageDirectory()
				.getPath());
		long bytesAvailable = (long) stat.getFreeBlocks()
				* (long) stat.getBlockSize();
		if (bytesAvailable < 10000000L) {
			if (!isPopup) {
				isPopup = true;
				handler.sendEmptyMessage(HANDLER_LOW_STORAGE_SIZE);
			}
		}
	}

	// check sdcard available
	public static boolean checkSDCardAvailable() {
		boolean ret = false;

		String str = Environment.getExternalStorageState();
		if (!str.equals(Environment.MEDIA_MOUNTED)) {
			handler.sendEmptyMessage(HANDLER_AVAILABLE_SDCARD);
			ret = false;
		} else {
			ret = true;
		}

		return ret;
	}

	// //////////////////////////////////////////////////////////////////////
	//
	// Android BACKKEY dispatch
	//
	// //////////////////////////////////////////////////////////////////////
	@Override
	public boolean dispatchKeyEvent(KeyEvent event) {
		if (event.getKeyCode() == KeyEvent.KEYCODE_BACK) {
			if (event.getAction() == KeyEvent.ACTION_UP) {
				Dialog dialog = new AlertDialog.Builder(this)
						.setCancelable(false)
						.setTitle(getString(R.string.endalert_title))
						.setMessage(getString(R.string.endalert_msg))
						.setPositiveButton(getString(R.string.btn_yes),
								new DialogInterface.OnClickListener() {
									public void onClick(DialogInterface dialog,
											int whichButton) {

										finish();
										System.exit(0);
									}
								})
						.setNegativeButton(getString(R.string.btn_no),
								new DialogInterface.OnClickListener() {
									@Override
									public void onClick(DialogInterface dialog,
											int which) {

										dialog.dismiss();
										dialog = null;
									}
								}).create();

				dialog.show();

			}
			return false;

		} else {
			return super.dispatchKeyEvent(event);
		}
	}

	// //////////////////////////////////////////////////////////////////////
	//
	// HELPER
	//
	// //////////////////////////////////////////////////////////////////////
	public static long compareDate(String startDate) {
		SimpleDateFormat dformat = new SimpleDateFormat("yyyy_MM_dd_kk_mm_ss");

		Date compareDateVal = new Date();
		try {
			compareDateVal = dformat.parse(startDate);
		} catch (ParseException e) {
			e.printStackTrace();
		}

		Date currentDate = new Date(System.currentTimeMillis());

		long progressLevel = (currentDate.getTime() - compareDateVal.getTime())
				/ (7 * 24 * 60 * 60 * 1000);

		if (progressLevel > 19) {
			progressLevel = 19;
		}
		if (progressLevel < 0) {
			progressLevel = 0;
		}

		return progressLevel;
	}

	public static void callYoutube(String youtubeId) {
		uriPath = youtubeId;

		handler.sendEmptyMessage(HANDLER_CALL_YOUTUBE);
	}

	public static boolean getNetworkState() {
		ConnectivityManager cManager;
		NetworkInfo mobile;
		NetworkInfo wifi;

		cManager = (ConnectivityManager) sPackageActivity
				.getSystemService(Context.CONNECTIVITY_SERVICE);
		mobile = cManager.getNetworkInfo(ConnectivityManager.TYPE_MOBILE);
		wifi = cManager.getNetworkInfo(ConnectivityManager.TYPE_WIFI);

		if (mobile.isConnected() || wifi.isConnected()) {
			return true;
		} else {
			return false;
		}
	}

	public static int getWifiStrength() {
		return mWifiStrength;
	}

	public static void showThinkleStore() {
		CJPlatformLMSExtension.showThinkleStore();
	}

	public static void showBrowser(String strURL) {
		CJPlatformLMSExtension.showBrowser(strURL);
	}

	public static void setMailFile(String path) {
		CJPlatformLMSExtension.setMailFile(path);
	}

	public static void setMailTitle(String title) {
		CJPlatformLMSExtension.setMailTitle(title);
	}

	// shchoi, It`s for download
	public static String getAuthKey() {
		return CJPlatformLMSExtension.getAuthKey();
	}

	public static String getURL() {
		return CJPlatformLMSExtension.getURL();
	}

	public static String getUserAgent() {
		return CJPlatformLMSExtension.getUserAgent();
	}

	public static String getTransactionId() {
		return CJPlatformLMSExtension.getTransactionId();
	}

	public static String getInterfaceId() {
		return CJPlatformLMSExtension.getInterfaceId();
	}

	public static String getInterfaceVer() {
		return CJPlatformLMSExtension.getInterfaceVer();
	}

	public static String getRequestTime() {
		return CJPlatformLMSExtension.getRequestTime();
	}

	/*--------------------------------*/
	/* File System Methods by sh_hong */
	/*--------------------------------*/
	public static long getFileSize(String path) {
		String zipPath = Environment.getDataDirectory().getPath();
		File f = new File(zipPath + "/data/"
				+ sPackageActivity.getPackageName() + "/" + path);
		// Log.e("", zipPath + "/data/" + myActivity.getPackageName() + "/" +
		// path);
		// Log.e("", ""+f.length());
		return f.length();
	}

	public static long getFreeSpace() {
		// sh_hong, get internal disk size
		StatFs stat = new StatFs(Environment.getDataDirectory().getPath());
		return (long) stat.getFreeBlocks() * (long) stat.getBlockSize();
	}

	public static void checkSDCard() {
		// sh_hong, check sdcard disk size
		StatFs stat = new StatFs(Environment.getExternalStorageDirectory()
				.getPath());
		long bytesAvailable = (long) stat.getFreeBlocks()
				* (long) stat.getBlockSize();
		if (bytesAvailable < 20000000L) {
			handler.sendEmptyMessage(HANDLER_LOW_STORAGE_SIZE);
		}
	}

	public static boolean removeSaveFile(String path) {
		File file = new File(path);
		return file.delete();
	}

	/*--------------------------------*/
	/* CAMERA */
	/*--------------------------------*/
	public void addCameraPreviewView(CJPlatformFrameViewInfo info) {
		if (mCameraView != null && mCameraView.isShowPreview()) {
			return;
		}

		LayoutInflater inflater = (LayoutInflater) getSystemService(Context.LAYOUT_INFLATER_SERVICE);

		FrameLayout cameraLayout = (FrameLayout) inflater.inflate(
				R.layout.cjplatform_camera_layout, null);
		cameraLayout.setTag(TAG_CAMERAVIEW);
		mCameraView = (CJPlatformCameraView) cameraLayout
				.findViewById(R.id.camera_layout);
		ImageView frameView = (ImageView) cameraLayout
				.findViewById(R.id.camera_frame);

		mCurrentCameraInfo = info;

		FrameLayout.LayoutParams params = (FrameLayout.LayoutParams) mCameraView
				.getLayoutParams();
		params.width = info.width;
		params.height = info.height;
		params.setMargins(info.x, info.y, 0, 0);

		mCameraView.setLayoutParams(params);

		mMainLayout.addView(cameraLayout);
		mCameraView.setZOrderMediaOverlay(true);

		CJPlatformFileManager.setImgThroughFileCheck(this, info.frameImgPath,
				frameView);

		frameView.setLayoutParams(params);

		CJPlatformHelper.setCameraViewInstane(mCameraView);
		mCameraView.setShowPreview(true);
		mCameraView.setRecordingStatus(false);

		mOrientationEventListener.enable();
	}

	public void moveCameraView(int x, int y) {
		for (int i = 0; i < mMainLayout.getChildCount(); i++) {
			if (mMainLayout.getChildAt(i).getTag() != null
					&& mMainLayout.getChildAt(i).getTag()
							.equals(TAG_CAMERAVIEW)) {
				FrameLayout cameraLayout = (FrameLayout) mMainLayout
						.getChildAt(i);

				for (int j = 0; j < cameraLayout.getChildCount(); j++) {
					FrameLayout.LayoutParams params = (FrameLayout.LayoutParams) mCameraView
							.getLayoutParams();
					params.width = mCurrentCameraInfo.width;
					params.height = mCurrentCameraInfo.height;
					params.setMargins(x, y, 0, 0);
					cameraLayout.getChildAt(j).setLayoutParams(params);
				}
			}
		}
	}

	public void removeSurfaceView(String tag) {
		for (int i = 0; i < mMainLayout.getChildCount(); i++) {
			if (mMainLayout.getChildAt(i).getTag() != null
					&& mMainLayout.getChildAt(i).getTag().equals(tag)) {
				if (tag.equals(TAG_CAMERAVIEW)) {
					mCameraView = null;
					mOrientationEventListener.disable();
				}

				mMainLayout.removeViewAt(i);
			}
		}
	}

	public void startRecording(String recordingPath) {
		if (mCameraView != null && mCameraView.isShowPreview()) {
			if (recordingPath != null && !recordingPath.equals("")) {
				mCameraView.initRecording(recordingPath);
			}
		}
	}

	/*--------------------------------*/
	/* Video */
	/*--------------------------------*/
	public void addFrameVideoView(CJPlatformFrameViewInfo info) {
		LayoutInflater inflater = (LayoutInflater) getSystemService(Context.LAYOUT_INFLATER_SERVICE);

		FrameLayout frameVideoLayout = (FrameLayout) inflater.inflate(
				R.layout.cjplatform_framevideo_layout, null);
		CJPlatformFrameVideoView frameVideoView = (CJPlatformFrameVideoView) frameVideoLayout
				.findViewById(R.id.video_layout);
		ImageView frameView = (ImageView) frameVideoLayout
				.findViewById(R.id.video_frame);

		FrameLayout.LayoutParams params = (FrameLayout.LayoutParams) frameVideoView
				.getLayoutParams();
		params.width = info.width;
		params.height = info.height;
		params.setMargins(info.x, info.y, 0, 0);

		frameVideoView.setLayoutParams(params);
		frameVideoLayout.setTag(TAG_FRAMEVIDEOVIEW);

		mMainLayout.addView(frameVideoLayout);
		frameVideoView.setZOrderMediaOverlay(true);
		frameVideoView.setVideoPath(info.contentPath);

		CJPlatformFileManager.setImgThroughFileCheck(this, info.frameImgPath,
				frameView);

		frameView.setLayoutParams(params);

		CJPlatformHelper.setFrameVideoViewInstane(frameVideoView);
	}

	// //////////////////////////////////////////////////////////////////////
	//
	// LMS by sh_hong
	//
	// //////////////////////////////////////////////////////////////////////
	/**
	 * @author CJEducations
	 * @brief start package app - call onCreate
	 * @version v1.0.0
	 * @date 2012.11. 26
	 * @since v1.0.1
	 */
	public static void appStart() {
		CJPlatformLMSExtension.start(sPackageActivity);
	}

	/**
	 * @author CJEducations
	 * @brief end package app - call onDestroy
	 * @version v1.0.0
	 * @date 2012.11. 26
	 * @since v1.0.1
	 */
	public static void appEnd() {
		CJPlatformLMSExtension.end();
	}

	/**
	 * @author CJEducations
	 * @brief get current used child id - jni link method
	 * @version v1.0.0
	 * @return current used child id (String)
	 * @date 2012.11. 28
	 * @since v1.0.2
	 */
	public static String getChildId() {
		return CJPlatformLMSExtension.getChildId();
	}

	/**
	 * @author CJEducations
	 * @brief get current used child name - jni link method
	 * @version v1.0.0
	 * @return current used child name (String)
	 * @date 2012.11. 28
	 * @since v1.0.2
	 */
	public static String getChildName() {
		return CJPlatformLMSExtension.getChildName();
	}

	/**
	 * @author CJEducations
	 * @brief get current used child birth day - jni link method
	 * @version v1.0.0
	 * @return current used child birth day (String)
	 * @date 2012.12. 27
	 * @since v1.0.5
	 */
	public static String getChildBirth() {
		return CJPlatformLMSExtension.getChildBirth();
	}

	/**
	 * @author CJEducations
	 * @brief get current used child picture path - jni link method
	 * @version v1.0.0
	 * @return current used child picture path (String)
	 * @date 2012.11. 28
	 * @since v1.0.2
	 */
	public static String getChildImage() {
		return CJPlatformLMSExtension.getChildImage();
	}

	// ---------------- //
	// init list method //
	// ---------------- //

	/**
	 * @author CJEducations
	 * @brief init Step class list - jni link method
	 * @version v1.0.0
	 * @date 2012.11. 26
	 * @since v1.0.1
	 */
	public static void initStepList() {
		CJPlatformLMSExtension.initStepList();
	}

	/**
	 * @author CJEducations
	 * @brief init Content class list - jni link method
	 * @version v1.0.0
	 * @date 2012.11. 26
	 * @since v1.0.1
	 */
	public static void initContentList() {
		CJPlatformLMSExtension.initContentList();
	}

	/**
	 * @author CJEducations
	 * @brief init Learn class list - jni link method
	 * @version v1.0.0
	 * @date 2012.11. 26
	 * @since v1.0.1
	 */
	public static void initLearnList() {
		CJPlatformLMSExtension.initLearnList();
	}

	/**
	 * @author CJEducations
	 * @brief init Grade class list - jni link method
	 * @version v1.0.0
	 * @date 2012.12. 17
	 * @since v1.0.4
	 */
	public static void initGradeList() {
		CJPlatformLMSExtension.initLearnList();
	}

	// ------------------ //
	// init struct method //
	// ------------------ //

	/**
	 * @author CJEducations
	 * @brief init Step static variable - jni link method
	 * @version v1.0.0
	 * @date 2012.11. 26
	 * @since v1.0.1
	 */
	public static void initStep() {
		CJPlatformLMSExtension.initStep();
	}

	/**
	 * @author CJEducations
	 * @brief init Content static variable - jni link method
	 * @version v1.0.0
	 * @date 2012.11. 26
	 * @since v1.0.1
	 */
	public static void initContent() {
		CJPlatformLMSExtension.initContent();
	}

	/**
	 * @author CJEducations
	 * @brief init Learn static variable - jni link method
	 * @version v1.0.0
	 * @date 2012.11. 26
	 * @since v1.0.1
	 */
	public static void initLearn() {
		CJPlatformLMSExtension.initLearn();
	}

	/**
	 * @author CJEducations
	 * @brief init Grade static variable - jni link method
	 * @version v1.0.0
	 * @date 2012.12. 17
	 * @since v1.0.4
	 */
	public static void initGrade() {
		CJPlatformLMSExtension.initGrade();
	}

	// --------------- //
	// add list method //
	// --------------- //

	/**
	 * @author CJEducations
	 * @brief add Step static variable - jni link method
	 * @version v1.0.0
	 * @date 2012.11. 26
	 * @since v1.0.1
	 */
	public static void addStep() {
		CJPlatformLMSExtension.addStep();
	}

	/**
	 * @author CJEducations
	 * @brief add Content static variable - jni link method
	 * @version v1.0.0
	 * @date 2012.11. 26
	 * @since v1.0.1
	 */
	public static void addContent() {
		CJPlatformLMSExtension.addContent();
	}

	/**
	 * @author CJEducations
	 * @brief add Learn static variable - jni link method
	 * @version v1.0.0
	 * @date 2012.11. 26
	 * @since v1.0.1
	 */
	public static void addLearn(int childID) {
		CJPlatformLMSExtension.addLearn(childID);
	}

	/**
	 * @author CJEducations
	 * @brief add Grade static variable - jni link method
	 * @version v1.0.0
	 * @date 2012.12. 17
	 * @since v1.0.4
	 */
	public static void addGrade() {
		CJPlatformLMSExtension.addGrade();
	}

	// ---------------------- //
	// set step struct method //
	// ---------------------- //

	/**
	 * @author CJEducations
	 * @brief link CJLMSExtension's setStep func - jni link method
	 * @param nCount
	 *            : Progress Table's nCount value (int)
	 * @version v1.0.0
	 * @date 2012.11. 27
	 * @since v1.0.2
	 */
	public static void setStepCount(int nCount) {
		CJPlatformLMSExtension.setStepCount(nCount);
	}

	/**
	 * @author CJEducations
	 * @brief link CJLMSExtension's setStepKey func - jni link method
	 * @param szKey
	 *            : Progress Table's szKey value (String)
	 * @version v1.0.0
	 * @date 2012.11. 27
	 * @since v1.0.2
	 */
	public static void setStepKey(String szKey) {
		CJPlatformLMSExtension.setStepKey(szKey);
	}

	/**
	 * @author CJEducations
	 * @brief link CJLMSExtension's setStepStartDate func - jni link method
	 * @param szStartDate
	 *            : Progress Table's szStartDate value (String)
	 * @version v1.0.0
	 * @date 2012.11. 27
	 * @since v1.0.2
	 */
	public static void setStepStartDate(String szStartDate) {
		CJPlatformLMSExtension.setStepStartDate(szStartDate);
	}

	/**
	 * @author CJEducations
	 * @brief link CJLMSExtension's setStepEndDate func - jni link method
	 * @param szEndDate
	 *            : Progress Table's szEndDate value (String)
	 * @version v1.0.0
	 * @date 2012.11. 27
	 * @since v1.0.2
	 */
	public static void setStepEndDate(String szEndDate) {
		CJPlatformLMSExtension.setStepEndDate(szEndDate);
	}

	/**
	 * @author CJEducations
	 * @brief link CJLMSExtension's setStepExtra func - jni link method
	 * @param szExtra
	 *            : Progress Table's szExtra value (String)
	 * @version v1.0.0
	 * @date 2012.11. 27
	 * @since v1.0.2
	 */
	public static void setStepExtra(String szExtra) {
		CJPlatformLMSExtension.setStepExtra(szExtra);
	}

	/**
	 * @author CJEducations
	 * @brief link CJLMSExtension's setContentCode func - jni link method
	 * @param szContentCode
	 *            : Content Table's szContentCode value (String)
	 * @version v1.0.0
	 * @date 2012.11. 27
	 * @since v1.0.2
	 */
	public static void setContentCode(String szContentCode) {
		CJPlatformLMSExtension.setContentCode(szContentCode);
	}

	/**
	 * @author CJEducations
	 * @brief link CJLMSExtension's setContentGrade func - jni link method
	 *        (remove param)
	 * @param iGrade
	 *            : KidsContent Table's iGrade value (int)
	 * @version v1.0.1
	 * @date 2012.12. 17
	 * @since v1.0.2
	 */
	public static void setContentGrade() {
		CJPlatformLMSExtension.setContentGrade();
	}

	/**
	 * @author CJEducations
	 * @brief link CJLMSExtension's setContentExtra func - jni link method
	 * @param szExtra
	 *            : KidsContent Table's szExtra value (String)
	 * @version v1.0.0
	 * @date 2012.11. 27
	 * @since v1.0.2
	 */
	public static void setContentExtra(String szExtra) {
		CJPlatformLMSExtension.setContentExtra(szExtra);
	}

	/**
	 * @author CJEducations
	 * @brief link CJLMSExtension's setContentList func - jni link method
	 * @version v1.0.0
	 * @date 2012.11. 27
	 * @since v1.0.2
	 */
	public static void setContentList() {
		CJPlatformLMSExtension.setContentList();
	}

	/**
	 * @author CJEducations
	 * @brief link CJLMSExtension's setLearnPKGName func - jni link method
	 * @param szPKGName
	 *            : PKGKids Table's szPKGName value (String)
	 * @version v1.0.0
	 * @date 2012.11. 27
	 * @since v1.0.2
	 */
	public static void setLearnPKGName(String szPKGName) {
		CJPlatformLMSExtension.setLearnPKGName(szPKGName);
	}

	/**
	 * @author CJEducations
	 * @brief link CJLMSExtension's setLearnCompleteDate func - jni link method
	 * @param szCompleteDate
	 *            : PKGKids Table's szCompleteDate value (String)
	 * @version v1.0.0
	 * @date 2012.11. 27
	 * @since v1.0.2
	 */
	public static void setLearnCompleteDate(String szCompleteDate) {
		CJPlatformLMSExtension.setLearnCompleteDate(szCompleteDate);
	}

	/**
	 * @author CJEducations
	 * @brief link CJLMSExtension's setLearnList func - jni link method
	 * @version v1.0.0
	 * @date 2012.11. 27
	 * @since v1.0.2
	 */
	public static void setLearnList() {
		CJPlatformLMSExtension.setLearnList();
	}

	/**
	 * @author CJEducations
	 * @brief link CJLMSExtension's setGrade func - jni link method
	 * @param szPKGName
	 *            : PKGKids Table's szPKGName value (String)
	 * @version v1.0.0
	 * @date 2012.12. 17
	 * @since v1.0.4
	 */
	public static void setGrade(int grade) {
		CJPlatformLMSExtension.setGrade(grade);
	}

	/**
	 * @author CJEducations
	 * @brief link CJLMSExtension's setGradeDate func - jni link method
	 * @param szPKGName
	 *            : PKGKids Table's szPKGName value (String)
	 * @version v1.0.0
	 * @date 2012.12. 17
	 * @since v1.0.4
	 */
	public static void setGradeDate(String szWriteDate) {
		CJPlatformLMSExtension.setGradeDate(szWriteDate);
	}

	public static void setGradeExtra(String szExtra) {
		CJPlatformLMSExtension.setGradeExtra(szExtra);
	}

	/**
	 * @author CJEducations
	 * @brief send lms data to LMSCenter - jni link method (return result int
	 *        value)
	 * @version v1.0.1
	 * @date 2012.11. 28
	 * @since v1.0.1
	 */
	public static int sendLMSCenter() {
		return CJPlatformLMSExtension.send();
	}

	public static int sendMail(String desc) {
		return CJPlatformLMSExtension.sendMail(desc);
	}

	/**
	 * @author CJEducations
	 * @brief get current date&time - jni link method
	 * @version v1.0.0
	 * @return date&time string value (String)
	 * @date 2012.11. 19
	 * @since v1.0.0
	 */
	public static String getDeviceDateTime() {
		return CJPlatformLMSExtension.getDeviceDateTime();
	}

	/**
	 * @author CJEducations
	 * @brief get complete date&time - jni link method
	 * @version v1.0.0
	 * @return date&time string value (String)
	 * @date 2012.11. 19
	 * @since v1.0.0
	 */
	public static String getTargetDateTime(int packageIndex) {
		return CJPlatformLMSExtension.getTargetDateTime(packageIndex);
	}

	static {
		System.loadLibrary("cocos2dcpp");
	}
}
