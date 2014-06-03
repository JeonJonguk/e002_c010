package com.cjeducations.lib;

import android.content.Context;
import android.util.DisplayMetrics;
import android.util.Log;
import android.util.TypedValue;
import android.widget.FrameLayout;

public class CJPlatformDisplayUtil
{
	private static final int SURFACE_DEFAULT_WIDTH_SIZE = 1024;
	private static final int SURFACE_DEFAULT_HEIGHT_SIZE = 768;

	public static int DPFromPixel(Context context, int pixel)
	{
		DisplayMetrics metrics = context.getResources().getDisplayMetrics();
		float dp = pixel/(metrics.densityDpi / 160f);
		return (int)dp;
	}
	
	public static int DpToPixel(Context context, int DP)
	{
		float px = TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, DP, context.getResources().getDisplayMetrics());
		
		return (int)px;
	}
	
	public static int PixelFromSurface(Context context, int pixel, FrameLayout surfaceLayout, boolean isWidth)
	{
		if(surfaceLayout == null)
		{
			surfaceLayout = new FrameLayout(context);
			surfaceLayout.setX(0);
		}
		
		DisplayMetrics metrics = context.getResources().getDisplayMetrics();
		
		float ratio = 0;
		
		if(metrics.heightPixels <= SURFACE_DEFAULT_HEIGHT_SIZE)
		{
			if(isWidth)
				ratio = ((float)metrics.widthPixels - (surfaceLayout.getX() * 2)) / (float)SURFACE_DEFAULT_WIDTH_SIZE;
			else
			{	
				return pixel; 
			}
		}
		else
		{
			if(isWidth)
				ratio = ((float)metrics.widthPixels - (surfaceLayout.getX() * 2)) / (float)SURFACE_DEFAULT_WIDTH_SIZE;
			else
				ratio = (float)metrics.heightPixels / (float)SURFACE_DEFAULT_HEIGHT_SIZE;
		}
		
		return (int)(pixel * ratio);
	}
}
