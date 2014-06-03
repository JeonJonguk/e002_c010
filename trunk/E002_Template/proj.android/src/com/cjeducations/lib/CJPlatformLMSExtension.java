package com.cjeducations.lib;

import java.net.URI;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;
import java.util.ListIterator;
import java.util.StringTokenizer;

import android.app.Activity;
import android.app.ActivityManager;
import android.app.AlertDialog;
import android.app.ActivityManager.RunningAppProcessInfo;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.drm.DrmStore.Action;
import android.net.Uri;
import android.os.Build;
import android.os.RemoteException;
import android.text.InputFilter.LengthFilter;
import android.util.Log;

import com.cjedu.thinkle.lms.openapi.Account;
import com.cjedu.thinkle.lms.openapi.Child;
import com.cjedu.thinkle.lms.openapi.Content;
import com.cjedu.thinkle.lms.openapi.Grade;
import com.cjedu.thinkle.lms.openapi.LMSCenter;
import com.cjedu.thinkle.lms.openapi.Learn;
import com.cjedu.thinkle.lms.openapi.Step;
import com.cjedu.thinkle.lms.openapi.mail.MailPdu;
import com.cjeducations.ithink.e002.c010.R;

/**
 * @author CJEducations
 * @brief LMSCenter lib manage class (change jar file)
 * @version v1.0.3
 * @date 2012. 11. 28
 * @since v1.0.0
 */
public class CJPlatformLMSExtension {
	// package index value
	private static final int PN_HAN1 = 1;
	private static final int PN_HAN2 = 2;
	private static final int PN_SAGO = 3;
	private static final int PN_ENG1 = 4;
	
	// LMSCenter ContentProvider
	private static LMSCenter 		_lms;
	
	// LMSCenter's class list
	private static List<Step> 		_steps 		= null;
	private static List<Content> 	_contents	= null;
	private static List<Learn>		_learns		= null;
	private static List<Grade>		_grades		= null;	

	// LMSCenter's class
	private static Step 			_step;
	private static Content 			_content;
	private static Learn 			_learn;
	private static Grade			_grade;
	
	private static Account			_account;
	
	private static Context 			_context;
	
	private static String 			_file;
	private static String 			_subject;
	
	/**
	 * @author CJEducations
	 * @brief when start app, start service and construct list
	 * @param context : Cocos2dxActivity's context
	 * @version v1.0.0
	 * @date 2012.11. 26
	 * @since v1.0.0
	 */
	public static void start(Context context){
		_context = context;
		
		_lms = new LMSCenter(context);
		_lms.bindService();	// start service
		
		// construct lms class List
		_steps = new ArrayList<Step>();
		_contents = new ArrayList<Content>();
		_learns = new ArrayList<Learn>();
		_grades = new ArrayList<Grade>();
	}
	
	/***************************************************/
	/***** shchoi, It`s getter of HTTP Information *****/
	/***************************************************/
    public static String getAuthKey()
    {
    	String authKey = "";
		try {
			authKey = _lms.getCMSTransInfo().getAuthKey();
		} catch (RemoteException e) {
			e.printStackTrace();
		}
    	return authKey;
    }
	
    public static String getURL()
    {
    	String url = "";
    	try {
    		url = _lms.getCMSTransInfo().getComReqUrl();
    	} catch (RemoteException e) {
    		e.printStackTrace();
    	}
    	return url;
    }
    
    public static String getUserAgent()
    {
    	String userAgent = "";
    	try {
    		userAgent = _lms.getCMSTransInfo().getUserAgent();
    	} catch (RemoteException e) {
    		e.printStackTrace();
    	}
    	return userAgent;
    }
    
    public static String getTransactionId()
    {
    	String trId = "";
    	try {
    		trId = _lms.getCMSTransInfo().getComTrId();
    	} catch (RemoteException e) {
    		e.printStackTrace();
    	}
    	return trId;
    }
    
    public static String getInterfaceId()
    {
    	String interfaceId = "";
    	try {
    		interfaceId = _lms.getCMSTransInfo().getComIFId();
    	} catch (RemoteException e) {
    		e.printStackTrace();
    	}
    	return interfaceId;
    }
    
    public static String getInterfaceVer()
    {
    	String interfaceVer = "";
    	try {
    		interfaceVer = _lms.getCMSTransInfo().getComIFVer();
    	} catch (RemoteException e) {
    		e.printStackTrace();
    	}
    	return interfaceVer;
    }
    
    public static String getRequestTime()
    {
    	String rqTime = "";
    	try {
    		rqTime = _lms.getCMSTransInfo().getComReqDate();
    	} catch (RemoteException e) {
    		e.printStackTrace();
    	}
    	return rqTime;
    }
    /************************/
    /** end "HTTP" request **/
    /************************/
    
    
	public static void setAccount()
	{
		int rt = LMSCenter.ERROR_APP_CERTIFICATION;
		try {
			_account =  _lms.getAccount();
		} catch (RemoteException e) {
			//Log.e("get account process exeption message : ", e.toString());
			//Log.e("get account process exeption message : ", "get account fail.");
			e.printStackTrace();
		}
		
		if (_account == null) {
			_account = new Account();
			Child nullchild = new Child();
			nullchild.setChildId("-1");
			_account.setUsedChild(nullchild);
			
			new AlertDialog.Builder(_context)
			.setMessage(_context.getResources().getString(R.string.app_text))
			.setPositiveButton(_context.getResources().getString(R.string.app_ok), new DialogInterface.OnClickListener() {
				@Override
				public void onClick(DialogInterface dialog, int which) {
					((Activity)_context).finish(); 
					requestKillProcess(_context);
				}
			})
			.setCancelable(false)
			.show();
		} else {
			try {
				/*
				 * check your app version, change comment below line
				 * 1 - developer version no request registry
				 * 2 - registry on thinkle store
				 */
				// 1. test version
				rt = _lms.checkAppRegistry(_context.getPackageName(), false);
				// 2. release version
//				rt = _lms.checkAppRegistry(_context.getPackageName(), true);
			} catch (RemoteException e) {
				//Log.e("check reg process exeption message : ", e.toString());
				//Log.e("check reg process exeption message : ", "app registry auth fail.");
				e.printStackTrace();
			}
			
			if (rt == LMSCenter.ERROR_APP_CERTIFICATION) {
				new AlertDialog.Builder(_context)
				.setMessage(_context.getResources().getString(R.string.coupon_text))
				.setPositiveButton(_context.getResources().getString(R.string.app_ok), new DialogInterface.OnClickListener() {
					@Override
					public void onClick(DialogInterface dialog, int which) {
						Intent intent = new Intent("com.cjedu.thinkle.store.intent.action.COUPON");
						intent.addFlags(32);
						_context.startActivity(intent);
						
						((Activity)_context).finish();
						requestKillProcess(_context);
					}
				})
				.setCancelable(false)
				.show();
			}
			//Log.e("lmsextension", "account : "+_account.getUsedChild().toString()+", reg : "+rt);
		}
	}
	
	public static void requestKillProcess(final Context context){
		//#1. first check api level.
		int sdkVersion = Integer.parseInt(Build.VERSION.SDK);
		if (sdkVersion < 8){
			//#2. if we can use restartPackage method, just use it.
			ActivityManager am = (ActivityManager) context.getSystemService(Context.ACTIVITY_SERVICE);
			am.restartPackage(_context.getPackageName());
		}else{
			//#3. else, we should use killBackgroundProcesses method.
			new Thread(new Runnable() {
				// @Override
				public void run() {
					ActivityManager am = (ActivityManager) context.getSystemService(Context.ACTIVITY_SERVICE);
					String name = _context.getApplicationInfo().processName;

					//pooling the current application process importance information.
					while(true){
						List<RunningAppProcessInfo> list = am.getRunningAppProcesses();
						for(RunningAppProcessInfo i : list){
							if(i.processName.equals(name) == true){
								//#4. kill the process,
								//only if current application importance is less than IMPORTANCE_BACKGROUND
								if(i.importance >= RunningAppProcessInfo.IMPORTANCE_BACKGROUND)
									am.restartPackage(_context.getPackageName());    //simple wrapper of killBackgrounProcess
								else
									Thread.yield();
								break;
							}
						}
					}
				}
			}, "Process Killer").start();
		}
	}
	
	/**
	 * @author CJEducations
	 * @brief when end app, end service
	 * @version v1.0.0
	 * @date 2012.11. 26
	 * @since v1.0.0
	 */
	public static void end(){
		_lms.unbindService();
	}
	
	// ----------------------- //
    // get account info method //
    // ----------------------- //
	
	/**
	 * @author CJEducations
	 * @brief current used child id from luncher
	 * @version v1.0.0
	 * @return current used child id (String)
	 * @date 2012.11. 28
	 * @since v1.0.2
	 */
	public static String getChildId(){
//		//Log.e("lmsextension", "child id : "+_account.getUsedChild().getChildId());
		return _account.getUsedChild().getChildId();
	}
	
	/**
	 * @author CJEducations
	 * @brief current used child name from luncher
	 * @version v1.0.0
	 * @return current used child name (String)
	 * @date 2012.11. 28
	 * @since v1.0.2
	 */
	public static String getChildName(){
//		//Log.e("lmsextension", "child name : "+_account.getUsedChild().getChildName());
		return _account.getUsedChild().getChildName();
	}
	
	/**
	 * @author CJEducations
	 * @brief current used child birth day from luncher
	 * @version v1.0.0
	 * @return current used child birth day (String)
	 * @date 2012.12. 27
	 * @since v1.0.4
	 */
	public static String getChildBirth(){
		String date = _account.getUsedChild().getBirthday();
		StringTokenizer st = new StringTokenizer(date, ".");
		Calendar cal = Calendar.getInstance();
		cal.set(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken())
				, Integer.parseInt(st.nextToken()));
		
		long dateCount = (((System.currentTimeMillis()-cal.getTimeInMillis())/(1000*60*60*24))/30)+1;
		
		date = new String(String.valueOf(dateCount));
		return date;
	}
	/**
	 * @author CJEducations
	 * @brief current used child picture path from luncher
	 * @version v1.0.0
	 * @return current used child picture path (String)
	 * @date 2012.11. 28
	 * @since v1.0.2
	 */
	public static String getChildImage(){
		//Log.e("lmsextension", "child image : "+_account.getUsedChild().getImagePath());
		return _account.getUsedChild().getImagePath();
	}
	
	// --------------- //
    // set mail method //
    // --------------- //
	
	public static void setMailFile(String path){
    	_file = path;
    }
	
	public static void setMailTitle(String title){
		_subject = title;
	}
	
	// ---------------- //
    // init list method //
    // ---------------- //
	
	/**
	 * @author CJEducations
	 * @brief init _steps list
	 * @version v1.0.0
	 * @date 2012.11. 26
	 * @since v1.0.0
	 */
	public static void initStepList(){
		if(_steps == null)
			_steps = new ArrayList<Step>();
		
		_steps.clear();
	}
	
	/**
	 * @author CJEducations
	 * @brief init _contents list
	 * @version v1.0.0
	 * @date 2012.11. 26
	 * @since v1.0.0
	 */
	public static void initContentList(){
		if(_contents == null)
			_contents = new ArrayList<Content>();
		
		_contents.clear();
	}
	
	/**
	 * @author CJEducations
	 * @brief init _learns list
	 * @version v1.0.0
	 * @date 2012.11. 26
	 * @since v1.0.0
	 */
	public static void initLearnList(){
		if(_learns == null)
			_learns = new ArrayList<Learn>();
		
		_learns.clear();
	}
	
	/**
	 * @author CJEducations
	 * @brief init _grades list
	 * @version v1.0.0
	 * @date 2012.11. 26
	 * @since v1.0.0
	 */
	public static void initGradeList(){
		if(_grades == null)
			_grades = new ArrayList<Grade>();
		
		_grades.clear();
	}
	
	// ------------------ //
    // init struct method //
    // ------------------ //
	
	/**
	 * @author CJEducations
	 * @brief init _step class
	 * @version v1.0.0
	 * @date 2012.11. 26
	 * @since v1.0.0
	 */
	public static void initStep(){
		_step = new Step();
	}
	
	/**
	 * @author CJEducations
	 * @brief init _step class
	 * @version v1.0.0
	 * @date 2012.11. 26
	 * @since v1.0.0
	 */
	public static void initContent(){
		_content = new Content();
	}
	
	/**
	 * @author CJEducations
	 * @brief init _learn class
	 * @version v1.0.0
	 * @date 2012.11. 26
	 * @since v1.0.0
	 */
	public static void initLearn(){
		_learn = new Learn();
	}
	
	/**
	 * @author CJEducations
	 * @brief init _grade class
	 * @version v1.0.0
	 * @date 2012.12. 17
	 * @since v1.0.3
	 */
	public static void initGrade(){
		_grade = new Grade();
	}
	
	// --------------- //
    // add list method //
    // --------------- //

	/**
	 * @author CJEducations
	 * @brief add _step class to _steps list
	 * @version v1.0.0
	 * @date 2012.11. 26
	 * @since v1.0.0
	 */
	public static void addStep(){
		_steps.add(_step);
	}
	
	/**
	 * @author CJEducations
	 * @brief add _content class to _contents list
	 * @version v1.0.0
	 * @date 2012.11. 26
	 * @since v1.0.0
	 */
	public static void addContent(){
		_contents.add(_content);
	}
	
	/**
	 * @author CJEducations
	 * @brief add _learn class to _learns list (remove _lms.getAccount() code)
	 * @version v1.0.1
	 * @date 2012.11. 28
	 * @since v1.0.0
	 */
	public static void addLearn(int childID){
		_learn.setChildId(""+childID);
		
		_learns.add(_learn);
	}
	
	/**
	 * @author CJEducations
	 * @brief add _grade class to _grades list
	 * @version v1.0.0
	 * @date 2012.12. 17
	 * @since v1.0.3
	 */
	public static void addGrade(){
		Log.e("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!addGrade", ""+_grades.size());
		_grades.add(_grade);
		Log.e("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!addGrade", ""+_grades.size());
	}
	
	// ---------------------- //
    // set step struct method //
    // ---------------------- //
    
	/**
     * @author CJEducations
     * @brief set Circle value in Step class
     * @param nCount : Progress Table's nCount value (int)
     * @version v1.0.0
     * @date 2012.11. 27
     * @since v1.0.1
     */
    public static void setStepCount(int nCount){
    	_step.setCircle(nCount);
    }
    
    /**
     * @author CJEducations
     * @brief set Code value in Step class
     * @param szKey : Progress Table's szKey value (String)
     * @version v1.0.0
     * @date 2012.11. 27
     * @since v1.0.1
     */
    public static void setStepKey(String szKey){
    	_step.setCode(szKey);
    }
    
    /**
     * @author CJEducations
     * @brief set StartDate value in Step class
     * @param szStartDate : Progress Table's szStartDate value (String)
     * @version v1.0.0
     * @date 2012.11. 27
     * @since v1.0.1
     */
    public static void setStepStartDate(String szStartDate){
    	_step.setStartDate(changeDateFormat(szStartDate, true));
    }
    
    /**
     * @author CJEducations
     * @brief set EndDate value in Step class
     * @param szEndDate : Progress Table's szEndDate value (String)
     * @version v1.0.0
     * @date 2012.11. 27
     * @since v1.0.1
     */
    public static void setStepEndDate(String szEndDate){
    	_step.setEndDate(changeDateFormat(szEndDate, true));
    }
    
    /**
     * @author CJEducations
     * @brief set Extra value in Step class
     * @param szExtra : Progress Table's szExtra value (String)
     * @version v1.0.0
     * @date 2012.11. 27
     * @since v1.0.1
     */
    public static void setStepExtra(String szExtra){
    	_step.setExtra(szExtra);
    }
    
    // ------------------------- //
    // set content class method  //
    // ------------------------- //
    
    /**
     * @author CJEducations
     * @brief set Code value in Content class
     * @param szContentCode : Content Table's szContentCode value (String)
     * @version v1.0.0
     * @date 2012.11. 27
     * @since v1.0.1
     */
    public static void setContentCode(String szContentCode){
    	_content.setCode(szContentCode);
    }
    
    /**
     * @author CJEducations
     * @brief set Grade value in Content class (remove param)
     * @param iGrade : KidsContent Table's iGrade value (int)
     * @version v1.0.1
     * @date 2012.12. 17
     * @since v1.0.1
     */
    public static void setContentGrade(){
    	
    	Log.e("!!!!!!!!!!!!!!!!!!!!!!!!!!!!! setcontentgrade", ""+_grades.size());
    	_content.setGrade(_grades);
    }
    
    /**
     * @author CJEducations
     * @brief set Extra value in Content class
     * @param szExtra : KidsContent Table's szExtra value (String)
     * @version v1.0.0
     * @date 2012.11. 27
     * @since v1.0.1
     */
    public static void setContentExtra(String szExtra){
    	_content.setExtra(szExtra);
    }
    
    /**
     * @author CJEducations
     * @brief set Step value in Content class
     * @version v1.0.0
     * @date 2012.11. 27
     * @since v1.0.1
     */
    public static void setContentList(){
    	_content.setStep(_steps);
    }
    
    // ----------------------- //
    // set learn class method  //
    // ----------------------- //
    
    /**
     * @author CJEducations
     * @brief set PackageName value in Learn class
     * @param szPKGName : PKGKids Table's szPKGName value (String)
     * @version v1.0.0
     * @date 2012.11. 27
     * @since v1.0.1
     */
    public static void setLearnPKGName(String szPKGName){
    	_learn.setPackageName(_context.getPackageName());
    }
    
    /**
     * @author CJEducations
     * @brief set GoldTime value in Learn class
     * @param szCompleteDate : PKGKids Table's szCompleteDate value (String)
     * @version v1.0.0
     * @date 2012.11. 27
     * @since v1.0.1
     */
    public static void setLearnCompleteDate(String szCompleteDate){
    	_learn.setGoalDate(changeDateFormat(szCompleteDate, false));
    }
    
    /**
     * @author CJEducations
     * @brief set Content value in Learn class
     * @version v1.0.0
     * @date 2012.11. 27
     * @since v1.0.1
     */
    public static void setLearnList(){
    	_learn.setContent(_contents);
    }
    
    // ---------------------- //
    // set grade class method //
    // ---------------------- //
	
    /**
     * @author CJEducations
     * @brief set grade value in Grade class
     * @version v1.0.0
     * @date 2012.12. 17
     * @since v1.0.3
     */
    public static void setGrade(int grade){
    	_grade.setGrade(grade);
    }
    
    /**
     * @author CJEducations
     * @brief set grade date value in Grade class
     * @version v1.0.0
     * @date 2012.12. 17
     * @since v1.0.3
     */
    public static void setGradeDate(String szWriteDate){
    	_grade.setGradeDate(changeDateFormat(szWriteDate, true));
    }
    
    public static void setGradeExtra(String szExtra){
    	_grade.setExtra(szExtra);
    }
    
    // --------------------- //
    // send to server method //
    // --------------------- //
	
    /**
     * @author CJEducations
     * @brief send DB Data to LMSCenter Server (return result int value)
     * @version v1.0.1
     * @date 2012.11. 28
     * @since v1.0.0
     */
	public static int send(){
		int rt = 0;
		
		try {
			rt = _lms.send(_learns);
		} catch (RemoteException e) {
			Log.e("lms send process exeption message : ", e.toString());
			e.printStackTrace();
		}
		
		switch (rt) {
		case LMSCenter.ERROR_BAD_VALUE:
			Log.e("lms send process message : ", "error bad value");
			break;
		case LMSCenter.ERROR_BIND:
			Log.e("lms send process message : ", "error bind");
			break;
		case LMSCenter.ERROR_DATA_INVALID:
			Log.e("lms send process message : ", "error data invalid");
			break;
		case LMSCenter.ERROR_MEMORY_LACK:
			Log.e("lms send process message : ", "error memory lick");
			break;
		case LMSCenter.ERROR_UNKNOWN:
			Log.e("lms send process message : ", "error unknown");
			break;
		case LMSCenter.SUCCESS:
			Log.e("lms send process message : ", "success " + _learns.toString());
			Log.e("lms send process message : ", "success");
			break;
		default:
			break;
		}
		
		_steps.clear();
		_contents.clear();
		_grades.clear();
		_learns.clear();
		
		return rt;
	}
	
	public static int sendMail(String desc)
	{
		int rt = 0;
		MailPdu mail = new MailPdu();
		
		List<String> to = new ArrayList<String>();
		List<String> cc = new ArrayList<String>();
		List<String> bcc = new ArrayList<String>();
		List<String> file = new ArrayList<String>();
		
		to.add(_account.getAccountId());
		cc.add(_account.getAccountId());
		bcc.add(_account.getAccountId());
		file.add(_file);
		
		Log.e("lms send process message : ", "constructor string []"+_file);
		
		// set mail setting data
		//Log.e("lms child id : ", _account.getUsedChild().getChildId());
		mail.setChildId(_account.getUsedChild().getChildId());
		//Log.e("lms to : ", to.toString());
		mail.setToAddress(to);
		//Log.e("lms cc : ", cc.toString());
		mail.setCcAddress(cc);
		//Log.e("lms bcc : ", bcc.toString());
		mail.setBccAddress(bcc);
		//Log.e("lms from : ", _account.getAccountId());
		mail.setFrom(_account.getAccountId());
		//Log.e("lms file : ", file.toString());
		mail.setAttachFile(file);
		mail.setMessage(desc);
		mail.setSubject(_subject);
		mail.setPackageName(_context.getPackageName());
		
		Log.e("lms send process message : ", "set mail data");
		
		try {
			Log.e("lms send process message : ", "send mail");
			rt = _lms.sendMail(mail);
		} catch (RemoteException e) {
			Log.e("lms send process exeption message : ", e.toString());
			e.printStackTrace();
		}
		
		switch (rt) {
		case LMSCenter.ERROR_BAD_VALUE:
			Log.e("lms send process message : ", "error bad value");
			break;
		case LMSCenter.ERROR_BIND:
			Log.e("lms send process message : ", "error bind");
			break;
		case LMSCenter.ERROR_DATA_INVALID:
			Log.e("lms send process message : ", "error data invalid");
			break;
		case LMSCenter.ERROR_MEMORY_LACK:
			Log.e("lms send process message : ", "error memory lick");
			break;
		case LMSCenter.ERROR_UNKNOWN:
			Log.e("lms send process message : ", "error unknown");
			break;
		case LMSCenter.SUCCESS:
			Log.e("lms send process message : ", "success");
			break;
		default:
			break;
		}
		
		return rt;
	}
	
	// ----------------- //
    // get string method //
    // ----------------- //
	
	/**
     * @author CJEducations
     * @brief send current date&time to cocos2dx - CJLMSIterface file
     * @version v1.0.0
     * @date 2012.11. 26
     * @since v1.0.0
     */
	public static String getDeviceDateTime(){
		return android.text.format.DateFormat
				.format("yyyy_MM_dd_kk_mm_ss", System.currentTimeMillis()).toString();
	}

	/**
     * @author CJEducations
     * @brief send complete date&time to cocos2dx - CJLMSIterface file
     * @version v1.0.0
     * @date 2012.11. 26
     * @since v1.0.0
     */
	public static String getTargetDateTime(int packageIndex){
		long addTimeVal = 0;

		switch (packageIndex) {
		case PN_HAN1:
			addTimeVal = 112;    // complete date val
			break;
		case PN_HAN2:
			addTimeVal = 112;    // complete date val
			break;
		case PN_SAGO:
			addTimeVal = 112;     // complete date val
			break;
		case PN_ENG1:
			addTimeVal = 14*7;     // complete date val
			break;
		default:
			break;
		}
		
		// calc second value (milliseconds)
		long completeTime = System.currentTimeMillis() + addTimeVal*24*60*60*1000;	
		
		return android.text.format.DateFormat
				.format("yyyy_MM_dd_kk_mm_ss", completeTime).toString();
	}
	
	private static String changeDateFormat(String date, boolean isTime)
	{
		String server ="";
		if (isTime) {
			server = date.split("_")[0]+"-"+date.split("_")[1]+"-"+date.split("_")[2]
					+" "+date.split("_")[3]+":"+date.split("_")[4]+":"+date.split("_")[5];
		} else {
			server = date.split("_")[0]+"-"+date.split("_")[1]+"-"+date.split("_")[2];
		}
		
		return server;
	}
	
	public static String getDiffDate(String date, int days)
	{
		long addTimeVal = days;
		SimpleDateFormat formatter = new SimpleDateFormat("yyyy_MM_dd_kk_mm_ss");
		
		Date tDate = null;
		
		try {
			tDate = formatter.parse(date);
		} catch (ParseException e) {
			e.printStackTrace();
		}
		
		long diff = tDate.getTime() + addTimeVal*24*60*60*1000;
		
		return android.text.format.DateFormat
				.format("yyyy_MM_dd_kk_mm_ss", diff).toString();
	}
	
	
	public static void showThinkleStore()
	{
//		Intent intent = new Intent("com.cjedu.thinkle.store.intent.action.STORE");
//		_context.startActivity(intent);

		Intent intent = _context.getPackageManager().getLaunchIntentForPackage("com.cjedu.thinkle.store");
		intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		_context.startActivity(intent);
	}
	
	public static void showBrowser(String strURL)
	{
		Uri uri = Uri.parse(strURL);
		Intent intent = new Intent(Intent.ACTION_VIEW, uri);
		
		_context.startActivity(intent);
	}
}
