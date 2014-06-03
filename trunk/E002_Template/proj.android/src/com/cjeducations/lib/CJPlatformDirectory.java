package com.cjeducations.lib;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.cjeducations.ithink.e002.E002Template;

import android.content.Context;
import android.content.res.AssetManager;
import android.os.Environment;
import android.widget.Toast;

/*
 * rename java file name to CJSaveData -> CJDirectory by soono
 */

public class CJPlatformDirectory 
{
	private static E002Template mPackageActivity;
	private static Context mFileContext;
	private static CJPlatformDirectory mSaveDataInstance;


	public CJPlatformDirectory(Context context)
	{
		mFileContext = context;
		mPackageActivity = (E002Template)mFileContext;
		mSaveDataInstance = mPackageActivity.getSaveDataInstance();

	}
	public boolean assetExists(AssetManager assets, String name) {

		try {

			// using File to extract path / filename
			// alternatively use name.lastIndexOf("/") to extract the path


			File f = new File(name);
			String parent = f.getParent();
			if (parent == null) parent = "";
			String fileName = f.getName();
			// now use path to list all files
			String[] assetList = assets.list(parent);
			if (assetList != null && assetList.length > 0) {
				for (String item : assetList) {

					if (fileName.equals(item))
					{

						return true;
					}
				}
			}
		} catch (IOException e) {
			// Log.w(TAG, e); // enable to log errors
		}
		return false;
	}
	public static String SaveAssetImageSave(String pPath)
	{

		String filePath = pPath;

		File file = new File(filePath);
		if(!file.isDirectory())
			file.mkdir();
		return filePath;

	}
	//    public static String SaveAssetRecSave(String pPath)
	//    {
	//    	
	//    }
	//   public static boolean fileExsitCheck(String pPath)
	//   {
	//	   m_cocos2dActivity = (Cocos2dxActivity) mFileContext;
	//		m_FileUtil = m_cocos2dActivity.getFileUtilInstance();
	//		
	////		int startIndex = pPath.lastIndexOf("/") + 1;
	////    	String fileName = pPath.substring(startIndex);
	//    	Log.e("fileExsitCheck",pPath);
	//    	boolean isExsitFile = m_FileUtil.assetExists(m_cocos2dActivity.getResources().getAssets(),  pPath);
	//    	Log.e("fileExsitCheck after",pPath);
	//    	if(!isExsitFile)
	//    	{
	//    		File file = new File(pPath);
	//    		if(file.exists())
	//    		{
	//    			isExsitFile = true;
	//    			
	//    		}
	//    	}
	//	   return isExsitFile;
	//   }
	private void testFunction(ArrayList<String> LeftList , ArrayList<String>RightList)
	{
		ArrayList<String> tempList = new ArrayList<String>();
		int InsertCount = LeftList.size() - 1;
		for(int i= RightList.size() - 1 ; i >=0 ;i --)
		{
			for(int j = 0 ; j < LeftList.size();j++)
			{
				if(RightList.get(i) == LeftList.get(j))
				{
					tempList.add(InsertCount, LeftList.get(j));
					LeftList.remove(j);
					InsertCount --;
				}
			}
		}
		if(InsertCount !=0)
			tempList.addAll(LeftList);
		
	}
	
	public static void createBaseDir()
	{
		// sh_hong, make folder code
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

			File _projdir = new File(_cjdir+"/"+mPackageActivity.getPackageName()); 
			if( !_projdir.exists() )  // check project hidden path exist. 
				// doesn't exist save path make dir.				
				_projdir.mkdirs();

//			File projdir = new File(cjdir+"/"+mPackageActivity.getPackageName()); 
//			if( !projdir.exists() )  // check project path exist. 
//				// doesn't exist save path make dir.				
//				projdir.mkdirs();

			File dbfile = new File(_projdir+"/lms.sqlite"); 
			if( !dbfile.exists() )  { // check db file path exist. 
				// doesn't exist copy asset db default file.				
				InputStream is = null;
				FileOutputStream fos = null;

				try {
					is = mPackageActivity.getAssets().open("pkg_common/lms.sqlite");
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

		} else { // can't access sdcard.
//			Toast.makeText(m_cocos2dActivity, "can't connect SD Card.", Toast.LENGTH_SHORT).show();
		}
	}
	
	public static String getHiddenDirPath()
	{
		String path = android.os.Environment.getExternalStorageDirectory()
				.getAbsolutePath();

		File _cjdir = new File(path+"/.CJEducations"); 
		if( !_cjdir.exists() )  // check base hidden path exist. 
			// doesn't exist save path make dir.				
			_cjdir.mkdirs();

		File _projdir = new File(_cjdir+"/"+mPackageActivity.getPackageName()); 
		if( !_projdir.exists() )  // check project hidden path exist. 
			// doesn't exist save path make dir.				
			_projdir.mkdirs();
		
		return _projdir.toString();
	}
	
	public static String getResourceDirPath(String strProjectIdenty)
	{
		String path = android.os.Environment.getExternalStorageDirectory()
				.getAbsolutePath();

		File cjdir = new File(path+"/CJEducations"); 
		if( !cjdir.exists() )  // check base hidden path exist. 
			// doesn't exist save path make dir.				
			cjdir.mkdirs();

		File projdir = new File(cjdir+"/ithink."+strProjectIdenty); 
		if( !projdir.exists() )  // check project hidden path exist. 
			// doesn't exist save path make dir.				
			projdir.mkdirs();
		
		return projdir.toString();
	}

	public static void end(){

	}
}
