package com.cjeducations.lib;

import android.app.Activity;
import android.content.Context;
import android.util.DisplayMetrics;
import android.widget.MediaController;
import android.widget.VideoView;

public class CJPlatformVideoView extends VideoView {
	
	Context mContext;
	
	public CJPlatformVideoView(Context context) {	
		super(context);
		mContext = context;
	}

	@Override
	protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
		DisplayMetrics displayMetrics = new DisplayMetrics();
		((Activity)mContext).getWindowManager().getDefaultDisplay().getMetrics(displayMetrics);
		int deviceWidth = displayMetrics.widthPixels;
		int deviceHeight = displayMetrics.heightPixels;
		setMeasuredDimension(deviceWidth, deviceHeight);
	}
}