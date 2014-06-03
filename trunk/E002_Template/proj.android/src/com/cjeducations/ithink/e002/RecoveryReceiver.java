package com.cjeducations.ithink.e002;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

import com.cjeducations.lib.CJPlatformLMSExtension;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Environment;
import android.util.Log;

public class RecoveryReceiver extends BroadcastReceiver {
	
	private native int recoveryCall(String path);
	
	static String[] temp;
//	static Context m_context;

	@Override
	public void onReceive(Context context, Intent intent) {
		if (intent.getAction().equals("com.cjeducations.ithink.e001.RECOVERY")) {
			
			String str = Environment.getExternalStorageState();
			if ( str.equals(Environment.MEDIA_MOUNTED)) {
				String path = android.os.Environment.getExternalStorageDirectory()
						.getAbsolutePath();

				File _cjdir = new File(path+"/.CJEducations"); 
				if( !_cjdir.exists() )  // check base hidden path exist. 
					// doesn't exist save path make dir.				
					_cjdir.mkdirs();

				File cjdir = new File(path+"/CJEducations"); 
				if( !cjdir.exists() )  // check base file path exist. 
					// doesn't exist save path make dir.				
					cjdir.mkdirs();

				File _projdir = new File(_cjdir+"/"+context.getPackageName()); 
				if( !_projdir.exists() )  // check project hidden path exist. 
					// doesn't exist save path make dir.				
					_projdir.mkdirs();

				File projdir = new File(cjdir+"/"+context.getPackageName()); 
				if( !projdir.exists() )  // check project path exist. 
					// doesn't exist save path make dir.				
					projdir.mkdirs();

				File dbfile = new File(_projdir+"/lms.sqlite"); 
				if( dbfile.exists() )  { // check db file path exist. 
					// doesn't exist copy asset db default file.
					dbfile.delete();
				}
				
				InputStream is = null;
				FileOutputStream fos = null;
				
				try {
					is = context.getAssets().open("pkg_common/lms.sqlite");
					int size = is.available();
					byte[] buffer = new byte[size];
					File outfile = new File(dbfile.toString());
					fos = new FileOutputStream(outfile);
					for (int c = is.read(buffer); c != -1; c = is.read(buffer)){
						fos.write(buffer, 0, c);
					}
					is.close();
					fos.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
			
			String retString = "";
			temp = intent.getStringArrayExtra("files");
			for (int i = 0; i < temp.length; i++) {
				retString += temp[i];
				if (i < temp.length - 1) {
					retString += "_";
				}
			}
			
			System.load(context.getApplicationInfo().dataDir + "/lib/libgame.so");
			
			int ret = recoveryCall(retString);
			
			Intent recoveryIntent = new Intent("com.cjedu.thinkle.helper.RECOVERY_RESULT");
			recoveryIntent.putExtra("pkg", "com.cjeducations.ithink.e001");
			recoveryIntent.putExtra("files", temp);
			recoveryIntent.putExtra("result", ret);
			recoveryIntent.addFlags(32);
			context.sendBroadcast(recoveryIntent);
			Log.e("", "send finish recovery broadcast");
			
			System.exit(0);

//			m_context = context.getApplicationContext();
		}
	}
	
	public static String getDeviceDateTime()
	{
		return CJPlatformLMSExtension.getDeviceDateTime();
	}
	
	public static String getDiffDate(String date, int days)
	{
		return CJPlatformLMSExtension.getDiffDate(date, days);
	}
}
