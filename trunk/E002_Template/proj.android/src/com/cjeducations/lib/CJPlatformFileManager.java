package com.cjeducations.lib;

import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;

import android.content.Context;
import android.content.res.AssetFileDescriptor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.Drawable;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Environment;
import android.widget.ImageView;

public class CJPlatformFileManager {
	
	public static boolean existFile(String filePath)
	{
		File file = new File(filePath);
		
		if(file.exists())
		{
			return true;
		}
		
		return false;
	}

	public static void setImgThroughFileCheck(Context context, String filePath, ImageView view)
	{
		if(filePath != null && filePath.startsWith("/"))
		{
			File file = new File(filePath);
			view.setImageURI(Uri.parse(file.getAbsolutePath()));
		}
		else
		{
			Drawable img = null;
			InputStream is = null;
		 	
			try {
				is = context.getResources().getAssets().open(filePath);
				img = Drawable.createFromStream(is, null);
			} catch (Exception e) {
				e.printStackTrace();
			}
			
			view.setImageDrawable(img);
		}
	}
	
	public static Bitmap getBitmap(Context context, String filePath)
	{
		if(filePath != null && filePath.startsWith("/"))
		{
			File file = new File(filePath);
			
			if(file.exists())
			{
				Bitmap img = BitmapFactory.decodeFile(file.getAbsolutePath());
				
				return img;
			}
		}
		else
		{
			InputStream is = null;
		 	
			try {
				is = context.getResources().getAssets().open(filePath);
				
				Bitmap img = BitmapFactory.decodeStream(is);
				
				return img;
				
			} catch (Exception e) {
				e.printStackTrace();
			}			
		}
		
		return null;
	}
	
	public static MediaPlayer setMediaPlayerFile(Context context, MediaPlayer player, String filePath)
	{
		if(filePath.startsWith("/"))
		{
			try {
				final FileInputStream fis = new FileInputStream(filePath);
				player.setDataSource(fis.getFD());
				fis.close();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		else
		{
			try {
				final AssetFileDescriptor assetFileDescritor = context.getAssets().openFd(filePath);
				player.setDataSource(assetFileDescritor.getFileDescriptor(), assetFileDescritor.getStartOffset(), assetFileDescritor.getLength());

			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		
		return player;
	}
	
	public static String getSavePathToSDCard(String filePath)
	{
		String sdCardPath = Environment.getExternalStorageDirectory()+"/CJEducations/ithink.e001/files";
		
		File file = new File(sdCardPath);
		
		if(!file.exists())
		{
			file.mkdirs();
		}
		
		return sdCardPath + "/" + filePath;
	}
	
	public static String getSavePathToPackage(Context context, String filePath)
	{
		String packagePath = "/data/data/" + context.getPackageName() + "/files";
		
		File file = new File(packagePath);
		
		if(!file.exists())
		{
			file.mkdirs();
		}
		
		return packagePath + "/" + filePath;
	}
}
