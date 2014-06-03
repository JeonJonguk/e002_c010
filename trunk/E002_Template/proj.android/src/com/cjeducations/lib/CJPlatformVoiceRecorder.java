package com.cjeducations.lib;
  

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import com.cjeducations.ithink.e002.E002Template;

import android.content.Context;   
import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaPlayer;
import android.media.MediaRecorder;
import android.os.AsyncTask;
import android.os.Environment;
import android.os.Handler;
import android.os.Looper;
import android.os.Message; 
import android.util.Log;
import android.widget.Toast;

public class CJPlatformVoiceRecorder 
{
	private String RECORDING_FILE_NAME = "tmp_speak_record.3gp";
	
	private Recorder mRecorder = null;
	//private MediaRecorder mRecorder;
	private MediaPlayer mPlayer = null;
	
	private Context mContext;
	private double mDecibel;
	
    public CJPlatformVoiceRecorder(Context context) 
    {
         mContext = context;
    }
        
    public void recVoiceRecording(final String filePath)
    { 
    	Handler mHandler = new Handler(Looper.getMainLooper());
 
		mHandler.post(new Runnable() {
			@Override
			public void run() {
				
				if( mRecorder == null )
				{
					
					if(filePath != null && !filePath.equals(""))
					{
						RECORDING_FILE_NAME = filePath;
					}
					else
					{
						RECORDING_FILE_NAME = "tmp_speak_record.3gp";
					}
					
					mRecorder = new Recorder(CJPlatformFileManager.getSavePathToSDCard(RECORDING_FILE_NAME));
					mRecorder.execute();
				}
			}
		});
    }
    
    public void stopVoiceRecording()
    {
    	if(mRecorder!=null)
		{
    		mRecorder.stopRecording();
    		mRecorder = null;
		}
    }
 
    public void pauseVoiceRecording()
    {
    	if(mRecorder!=null)
		{
    		if(mRecorder.isRecording())
    		{
    			mRecorder.setRecordingPause(true);
    		}
		}
    }
    
    public void resumeVoiceRecording()
    {
    	if(mRecorder!=null)
		{
    		if(mRecorder.isRecording())
    		{
    			mRecorder.setRecordingPause(false);
    		}
		}
    }
    
    public void playRecordedVoice(String filePath)
    {
    	if(mPlayer == null)
    		mPlayer = new MediaPlayer();
    	 
    	try 
    	{
    		if(filePath != null && !filePath.equals(""))
    		{
    			RECORDING_FILE_NAME = filePath;
    		}
    		else
    		{
    			RECORDING_FILE_NAME = "tmp_speak_record.3gp";
    		}
    		
    		FileInputStream fs = new FileInputStream(CJPlatformFileManager.getSavePathToSDCard(RECORDING_FILE_NAME)); 
			mPlayer.setDataSource(fs.getFD());
 
    		mPlayer.prepare();

    	} catch (Exception e) {
			e.printStackTrace();
		}
    
    	mPlayer.setVolume(1.0f, 1.0f);
    	mPlayer.start();
    	
    	mPlayer.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
			 
			public void onCompletion(MediaPlayer mp) {
				stopRecordedVoice();
			}
		});
    }
    
    public void pauseRecordedVoice()
    {
    	if(mPlayer != null)
    	{
    		//Log.e("record", "pauseRecordedVoice");
    		mPlayer.pause();
    	}
    }
    
    public void resumeRecordedVoice()
    {
    	if(mPlayer != null)
    	{
    		//Log.e("record", "resumeRecordedVoice");
    		mPlayer.start();
    	}
    }
    
    public void stopRecordedVoice()
    {
    	if(mPlayer == null)
    		return;
    	 
    	((E002Template)mContext).recordedVoicePlayFinishedCallback();
    	
    	mPlayer.stop();
    	mPlayer.release();
    	mPlayer = null;
    }
    
    public double getAmplitude()
	{
//		System.out.println("start decibel");
//		if (mRecorder != null)
//		{
//			// referance 
//			// http://www.rqna.net/qna/kwqhhp-what-does-androids-getmaxamplitude-function-for-the-mediarecorder-actually-give-me.html
//			int x = mRecorder.getMaxAmplitude();
//			double x2 = x;
//			double db = (20 * Math.log10(x2 / 0.1)); 
//			return db;
//		}
		return 0;
	}
 
    public  double getAmplitudeText()
    {
    	return mDecibel;
    }
    
    Handler mHandler = new Handler()
	{
		public void handleMessage(Message msg) { 
			super.handleMessage(msg);
			 
			mDecibel = getAmplitude();
			 
			if(mDecibel > 109.0)
			{
				Toast.makeText(mContext, "Recording", Toast.LENGTH_SHORT).show();
			}
			
			sendEmptyMessageDelayed(0, 500);
		}
	};
}

class Recorder  extends AsyncTask<Void, Void, Void>
{
	// For audio record options
	private final int RECORDER_AUDIO_ENCODING = AudioFormat.ENCODING_PCM_16BIT;  
	private final int RECORDER_CHANNELS 	  = AudioFormat.CHANNEL_IN_MONO; 
	private final int WAVE_CHANNEL_MONO   = 1;
	private final int HEADER_SIZE 		  = 0x2c;
	private final int RECORDER_BPP 		  = 16;
	private final int RECORDER_SAMPLERATE = 0xac44;
	private final int BUFFER_SIZE;
 
	private AudioRecord mAudioRecord;
	private boolean 	mIsRecording;
	private boolean 	mIsRecordingPause;
	private static String 		mRecordingFile;
	private static String 		mTempFile;

	private int mAudioLen = 0;
	
	// For checking recording time
	long startTime;
	private final int MIN_RECORDING_TIME = 2000;
	private final int MAX_RECORDING_TIME = 10000;
	
	// For calculate Db
	private final float MAX_16_BIT = 32768;
	private final float FUDGE = 0.6f;
 
	public Recorder(String filePath) 
	{
		super();
		
		mRecordingFile  = filePath;
		mTempFile		= filePath+".bak";
		
		BUFFER_SIZE  = AudioRecord.getMinBufferSize(RECORDER_SAMPLERATE, RECORDER_CHANNELS, RECORDER_AUDIO_ENCODING);
		mIsRecording = false;
		mIsRecordingPause = false;
	}
 
	boolean isRecording()
	{
		return mIsRecording;
	}
	
	void setRecordingPause(boolean isPause)
	{
		mIsRecordingPause = isPause;
	}
	
	@Override
	protected Void doInBackground(Void... params) {
		
		mAudioRecord = new AudioRecord(MediaRecorder.AudioSource.MIC, RECORDER_SAMPLERATE, RECORDER_CHANNELS,RECORDER_AUDIO_ENCODING, BUFFER_SIZE);
		mAudioRecord.startRecording();
		mIsRecording = true; 
		startTime = System.currentTimeMillis();
		writeAudioDataToFile();
		
		return null;
	}

	 private void writeAudioDataToFile()
	 {  
		 BufferedInputStream  mBIStream = null;
		 BufferedOutputStream mBOStream = null;
		byte[] buffer = new byte[BUFFER_SIZE];
		short[] sdata = new short[BUFFER_SIZE/2];
		
		File waveFile = new File(mRecordingFile);
		File tempFile = new File(mTempFile);
			  
		try {
			mBOStream = new BufferedOutputStream(new FileOutputStream(tempFile));
		} catch (FileNotFoundException e1) {
			e1.printStackTrace();
		}
	  
		int read = 0;
		int len = 0;
		if (null != mBOStream) 
		{
			try {
				while (mIsRecording && mAudioRecord!=null) {
					read = mAudioRecord.read(sdata, 0, BUFFER_SIZE/2);
					if (AudioRecord.ERROR_INVALID_OPERATION != read) 
					{
						byte[] bt = new byte[BUFFER_SIZE];
						for(int i=0; i<read ; i++){
							byte[] temp = shortToByte(sdata[i]);
							bt[i+i] = temp[0];
							bt[i+i+1] = temp[1];
						}
							
							if(!mIsRecordingPause)
							{
								mBOStream.write(bt);
							}
					}
				}

				mBOStream.flush();
				mBOStream.close();
				mAudioLen = (int)tempFile.length();
				mBIStream = new BufferedInputStream(new FileInputStream(tempFile));
				mBOStream = new BufferedOutputStream(new FileOutputStream(waveFile));
				mBOStream.write(getFileHeader());
				len = HEADER_SIZE;
				while ((read = mBIStream.read(buffer)) != -1) {	    	    	
					mBOStream.write(buffer);    	    	
				}
				mBOStream.flush();
		    mBIStream.close();
		    mBOStream.close();
			} catch (IOException e1) {
				e1.printStackTrace();
			}
		}
	}
	 
	 public boolean getIsOnRecording(){
		 return mIsRecording;
	 }
 
	 public byte[] shortToByte(short sh) {
		 byte data[] = new byte[2];
		 data[0] = (byte) ((sh) & 0xff);
		 data[1] = (byte) ((sh >> 8) & 0xff);		 
		
		 return data;
	 }
	 
	 public short byteToShort(byte[] bt) {
		 short result = 0;
		 result += ((bt[0] & 0xff) << (8));
		 result += ((bt[1] & 0xff));
		 return result;
	 }
	 
	private byte[] getFileHeader() {
		byte[] header = new byte[HEADER_SIZE];
		int totalDataLen = mAudioLen + 40;
		long byteRate = RECORDER_BPP * RECORDER_SAMPLERATE * WAVE_CHANNEL_MONO/8;
		header[0] = 'R';  // RIFF/WAVE header
		header[1] = 'I';
		header[2] = 'F';
		header[3] = 'F';
		header[4] = (byte) (totalDataLen & 0xff);
		header[5] = (byte) ((totalDataLen >> 8) & 0xff);
		header[6] = (byte) ((totalDataLen >> 16) & 0xff);
		header[7] = (byte) ((totalDataLen >> 24) & 0xff);
		header[8] = 'W';
		header[9] = 'A';
		header[10] = 'V';
		header[11] = 'E';
		header[12] = 'f';  // 'fmt ' chunk
		header[13] = 'm';
		header[14] = 't';
		header[15] = ' ';
		header[16] = 16;  // 4 bytes: size of 'fmt ' chunk
		header[17] = 0;
		header[18] = 0;
		header[19] = 0;
		header[20] = (byte)1;  
		header[21] = 0;
		header[22] =  WAVE_CHANNEL_MONO;
		header[23] = 0;
		header[24] = (byte) (RECORDER_SAMPLERATE & 0xff);
		header[25] = (byte) ((RECORDER_SAMPLERATE >> 8) & 0xff);
		header[26] = (byte) ((RECORDER_SAMPLERATE >> 16) & 0xff);
		header[27] = (byte) ((RECORDER_SAMPLERATE >> 24) & 0xff);
		header[28] = (byte) (byteRate & 0xff);
		header[29] = (byte) ((byteRate >> 8) & 0xff);
		header[30] = (byte) ((byteRate >> 16) & 0xff);
		header[31] = (byte) ((byteRate >> 24) & 0xff);
		header[32] = (byte) RECORDER_BPP * WAVE_CHANNEL_MONO/8;  // block align
		header[33] = 0;
		header[34] = RECORDER_BPP;  // bits per sample
		header[35] = 0;
		header[36] = 'd';
		header[37] = 'a';
		header[38] = 't';
		header[39] = 'a';
		header[40] = (byte)(mAudioLen & 0xff);
		header[41] = (byte)((mAudioLen >> 8) & 0xff);
		header[42] = (byte)((mAudioLen >> 16) & 0xff);
		header[43] = (byte)((mAudioLen >> 24) & 0xff);
		return header;
	}
 

	public void stopRecording() 
	{
		if (null != mAudioRecord) {
			mIsRecording = false;
			mAudioRecord.stop();
			mAudioRecord.release();
			mAudioRecord = null;
		}
		Log.e("record", "recordStop");
	}	
}