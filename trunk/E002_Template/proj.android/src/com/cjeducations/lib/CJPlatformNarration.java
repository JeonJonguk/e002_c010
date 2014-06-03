
package com.cjeducations.lib;
 
import java.util.ArrayList;

import com.cjeducations.ithink.e002.E002Template;

import android.content.Context; 
import android.media.MediaPlayer;
import android.util.Log; 

public class CJPlatformNarration {
	// ===========================================================
	// Constants
	// ===========================================================

	private static final String TAG = CJPlatformNarration.class.getSimpleName();

	// ===========================================================
	// Fields
	// ===========================================================

	private final Context mContext;
	private ArrayList<CJMediaPlayer> mArrMediaPlayer;
	private float mLeftVolume;
	private float mRightVolume; 

	private ArrayList<CJMediaPlayer> mArrPausedNarration;
	
	// ===========================================================
	// Constructors
	// ===========================================================

	public CJPlatformNarration(final Context pContext) 
	{
		this.mContext = pContext;
		this.initData();
	}

	// ===========================================================
	// Getter & Setter
	// ===========================================================

	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================

	// ===========================================================
	// Methods
	// ===========================================================

	public void preloadNarration(final String pPath) 
	{
		if (this.mArrMediaPlayer.size() > 0) 
		{
			boolean existNarration = false;
			
			for (int i = 0; i < mArrMediaPlayer.size(); i++) 
			{
				if(pPath.equals(mArrMediaPlayer.get(i).getPath()))
				{
					existNarration = true;
				}
			}
			
			if(existNarration)
			{
				return;
			}
			else
			{
				CJMediaPlayer player = new CJMediaPlayer();
				player.setPath(pPath); 
				player.setPlayer(createMediaplayer(pPath)); 
				
				mArrMediaPlayer.add(player);
			}
				
		}
		else
		{
			CJMediaPlayer player = new CJMediaPlayer();
			player.setPath(pPath); 
			player.setPlayer(createMediaplayer(pPath));
			
			mArrMediaPlayer.add(player);
		}
	}

	public void playNarration(final String pPath, final boolean isLoop) 
	{
		if (this.mArrMediaPlayer.size() > 0) 
		{
			boolean existNarration = false;
			
			for (int i = 0; i < mArrMediaPlayer.size(); i++) 
			{
				if(pPath.equals(mArrMediaPlayer.get(i).getPath()))
				{
					existNarration = true;
					
					if(mArrMediaPlayer.get(i).getPlayer() != null)
					{
						try { 
							mArrMediaPlayer.get(i).getPlayer().stop();
							mArrMediaPlayer.get(i).getPlayer().setLooping(isLoop);
							
							mArrMediaPlayer.get(i).getPlayer().prepare();
							mArrMediaPlayer.get(i).getPlayer().seekTo(0);
							mArrMediaPlayer.get(i).getPlayer().start();

							mArrMediaPlayer.get(i).setPause(false);
						}
						catch (Exception e) {
							Log.e(CJPlatformNarration.TAG, "playNarration: error state");
							e.printStackTrace();
						}
					}
					
					
					return;
				}
			}
			
			if(existNarration)
			{
				return;
			}
			else
			{
				CJMediaPlayer player = new CJMediaPlayer();
				player.setPath(pPath); 
				player.setPlayer(createMediaplayer(pPath));
				
				mArrMediaPlayer.add(player);
				
				try { 
					player.getPlayer().stop();
					
					player.getPlayer().setLooping(isLoop);
					player.getPlayer().prepare();
					player.getPlayer().seekTo(0);
					player.getPlayer().start();

					player.setPause(false);
				}
				catch (Exception e) {
					Log.e(CJPlatformNarration.TAG, "playNarration: error state");
					e.printStackTrace();
				}
			}	
		}
		else
		{
			CJMediaPlayer player = new CJMediaPlayer();
			player.setPath(pPath); 
			player.setPlayer(createMediaplayer(pPath));
			
			mArrMediaPlayer.add(player);
			
			try {
				
				if(player.getPlayer() != null)
				{ 
					player.getPlayer().stop();
					
					player.getPlayer().setLooping(isLoop);
					
					player.getPlayer().prepare();
					player.getPlayer().seekTo(0);
					player.getPlayer().start();

					player.setPause(false);
				}
			}
			catch (Exception e) {
				Log.e(CJPlatformNarration.TAG, "playNarration: error state");
				e.printStackTrace();
			}
		}
	}

	public void playAllNarration(final boolean isLoop) 
	{
		if (this.mArrMediaPlayer.size() > 0) 
		{
			for (int i = 0; i < mArrMediaPlayer.size(); i++) 
			{
				if(mArrMediaPlayer.get(i).getPlayer() != null)
				{
					try { 
						mArrMediaPlayer.get(i).getPlayer().stop();

						mArrMediaPlayer.get(i).getPlayer().setLooping(isLoop);

						mArrMediaPlayer.get(i).getPlayer().prepare();
						mArrMediaPlayer.get(i).getPlayer().seekTo(0);
						mArrMediaPlayer.get(i).getPlayer().start();

						mArrMediaPlayer.get(i).setPause(false);
					}
					catch (Exception e) {
						Log.e(CJPlatformNarration.TAG, "playAllNarration: error state");
						e.printStackTrace();
					}
				}
			} 				
		}
	}
	
	public void stopAllNarration() 
	{
		if (this.mArrMediaPlayer.size() > 0) 
		{
			for (int i = 0; i < mArrMediaPlayer.size(); i++) 
			{
				try {
					if(mArrMediaPlayer.get(i).getPlayer().isPlaying())
					{
						mArrMediaPlayer.get(i).getPlayer().stop();
						mArrMediaPlayer.get(i).setPause(false);
					}
				} 
				catch (Exception e) {
					Log.e(CJPlatformNarration.TAG, "stopAllNarration: error state");
					e.printStackTrace();
				}
				
			} 				
		}
	}
	
	public void removeAllNarration() 
	{
		end();
	}
	
	public void stopNarration(final String pPath) 
	{
		if (this.mArrMediaPlayer.size() > 0) 
		{
			if(pPath != null)
			{
				for (int i = 0; i < mArrMediaPlayer.size(); i++) 
				{
					try {
						
						if(pPath.equals(mArrMediaPlayer.get(i).getPath()))
						{  
							mArrMediaPlayer.get(i).getPlayer().stop();
							mArrMediaPlayer.get(i).getPlayer().release();
							
							CJMediaPlayer temp = mArrMediaPlayer.get(i);
							temp.setPlayer(null);
							
							mArrMediaPlayer.remove(i);
							temp = null;
							 
							return;
						}
						
					} catch (Exception e) {
						Log.e(CJPlatformNarration.TAG, "stopNarration: error state");
						e.printStackTrace();
					}
					
				}
			}
		}
		 
		// should set the state, if not, the following sequence will be error
		// play -> pause -> stop -> resume
	}

	public void pauseAllNarration() 
	{
		if (this.mArrMediaPlayer.size() > 0) 
		{
			for (int i = 0; i < mArrMediaPlayer.size(); i++) 
			{		 
				if(!mArrMediaPlayer.get(i).isPause())
				{
					try {
						mArrMediaPlayer.get(i).getPlayer().pause();
						mArrMediaPlayer.get(i).setPause(true);
					} catch (Exception e) {
						Log.e(CJPlatformNarration.TAG, "pauseAllNarration: error state");
						e.printStackTrace();
					}
					
				}
			}
		}
	}
	
	public void pauseNarration(final String pPath) 
	{
		if (this.mArrMediaPlayer.size() > 0) 
		{
			if(pPath != null)
			{
				for (int i = 0; i < mArrMediaPlayer.size(); i++) 
				{
					if(pPath.equals(mArrMediaPlayer.get(i).getPath()))
					{
						if(!mArrMediaPlayer.get(i).isPause())
						{
							try {
								mArrMediaPlayer.get(i).getPlayer().pause();
								mArrMediaPlayer.get(i).setPause(true);
							} catch (Exception e) {
								Log.e(CJPlatformNarration.TAG, "pauseNarration: error state");
								e.printStackTrace();
							}
							
						}
					}
				}
			}
		}
	}

	public void resumeAllNarration() 
	{
		if (this.mArrMediaPlayer.size() > 0) 
		{
			for (int i = 0; i < mArrMediaPlayer.size(); i++) 
			{			 
				if(mArrMediaPlayer.get(i).isPause())
				{
					try {
						mArrMediaPlayer.get(i).getPlayer().start();
						mArrMediaPlayer.get(i).setPause(false);
					} catch (Exception e) {
						Log.e(CJPlatformNarration.TAG, "resumeAllNarration: error state");
						e.printStackTrace();
					}
					
				}
			}
		}
	}
	
	public void resumeNarration(final String pPath) 
	{
		if (this.mArrMediaPlayer.size() > 0) 
		{
			if(pPath != null)
			{
				for (int i = 0; i < mArrMediaPlayer.size(); i++) 
				{
					if(pPath.equals(mArrMediaPlayer.get(i).getPath()))
					{
						if(mArrMediaPlayer.get(i).isPause())
						{
							try {
								mArrMediaPlayer.get(i).getPlayer().start();
								mArrMediaPlayer.get(i).setPause(false);
							} catch (Exception e) {
								Log.e(CJPlatformNarration.TAG, "resumeNarration: error state");
								e.printStackTrace();
							}
							
						}
					}
				}
			}
		}
	}

	public int getNarrationTime(final String pPath)
	{
		if (this.mArrMediaPlayer.size() > 0) 
		{ 
			if(pPath != null)
			{ 
				boolean existFile = false;
				
				for (int i = 0; i < mArrMediaPlayer.size(); i++) 
				{
                    if(pPath.equals(mArrMediaPlayer.get(i).getPath()))
					{
                    	existFile = true;
                    	
                        try
                        {
                            if(mArrMediaPlayer.get(i) != null && mArrMediaPlayer.get(i).getPlayer() != null)
                                return mArrMediaPlayer.get(i).getPlayer().getDuration();
                            else
                            {
                            	CJMediaPlayer player = new CJMediaPlayer();
                				player.setPath(pPath); 
                				player.setPlayer(createMediaplayer(pPath)); 
                			 
                				int time = player.getPlayer().getDuration();
                				
                				player.getPlayer().release();
    	            			player = null;
    	            			
                            	return time;
                            }
                        }
                        catch(Exception e)
                        {
                            e.printStackTrace();
                        }
                        
					}
                   
				}
				
				if(!existFile)
				{      
	                 try {
	                	 	CJMediaPlayer player = new CJMediaPlayer();
	                	 	player.setPath(pPath); 
	            			player.setPlayer(createMediaplayer(pPath)); 
	            			 
	            			int time = player.getPlayer().getDuration();
	            			
	            			player.getPlayer().release();
	            			player = null;
	            			
	                       	return time;
	                        	
						} catch (Exception e) {
							e.printStackTrace();
						}                
				}
			}
		}
		else
		{
			 try {
         	 	CJMediaPlayer player = new CJMediaPlayer();
         	 	player.setPath(pPath); 
     			player.setPlayer(createMediaplayer(pPath)); 
     			 
     			int time = player.getPlayer().getDuration();
     			
     			player.getPlayer().release();
     			player = null;
     			
                	return time;
                 	
				} catch (Exception e) {
					e.printStackTrace();
				}  
		}

		return 0;
	}
	
	public int getCurrentPosition(final String pPath)
	{ 
		if (this.mArrMediaPlayer.size() > 0) 
		{ 
			if(pPath != null)
			{ 
				for (int i = 0; i < mArrMediaPlayer.size(); i++) 
				{ 
					if(pPath.equals(mArrMediaPlayer.get(i).getPath()))
					{
                        try
                        {
                            if(mArrMediaPlayer.get(i) != null && mArrMediaPlayer.get(i).getPlayer() != null)
                                return mArrMediaPlayer.get(i).getPlayer().getCurrentPosition();
                            else
                                return -1;
                        }
                        catch(Exception e)
                        {
                            e.printStackTrace();
                        }
                        
					}
				}
			}
		}
		
		return 0;
	}
	
	public boolean isNarrationPlaying() 
	{
		boolean ret = false;

		if (this.mArrMediaPlayer.size() > 0) 
		{
			for (int i = 0; i < mArrMediaPlayer.size(); i++) 
			{
				if(mArrMediaPlayer.get(i).getPlayer().isPlaying())
					ret = true;
			} 
		}
		else
		{
			ret = false;
		}
		 
		return ret;
	}
	
	public void pauseToPlayingNarration() 
	{

		if (this.mArrMediaPlayer.size() > 0) 
		{
			try {
				for (int i = 0; i < mArrMediaPlayer.size(); i++) 
				{
					if(mArrMediaPlayer.get(i).getPlayer() != null && mArrMediaPlayer.get(i).getPlayer().isPlaying())
					{
						mArrMediaPlayer.get(i).getPlayer().pause();
						mArrMediaPlayer.get(i).setPause(true);
						mArrPausedNarration.add(mArrMediaPlayer.get(i));
					}
					
				} 
			} catch (Exception e) {
				// TODO: handle exception
				e.printStackTrace();
			}
			
		}
	}
	
	public void resumePausedNarration() 
	{

		if (this.mArrPausedNarration.size() > 0) 
		{
			try {
				
				for (int i = 0; i < mArrPausedNarration.size(); i++) 
				{
					if(mArrMediaPlayer.get(i).getPlayer() != null )
						mArrPausedNarration.get(i).getPlayer().start();
					mArrPausedNarration.get(i).setPause(false);
				}
				mArrPausedNarration.clear();
				
			} catch (Exception e) {
				// TODO: handle exception
				e.printStackTrace();
			}
		}
	}
	

	public void end() 
	{ 	
		if (this.mArrMediaPlayer.size() > 0) 
		{ 
			for (int i = 0; i < mArrMediaPlayer.size(); i++) 
			{
				try {
					if(mArrMediaPlayer.get(i).getPlayer() != null)
					{	
						mArrMediaPlayer.get(i).getPlayer().release();
						mArrMediaPlayer.get(i).setPlayer(null);
					}
				} catch (Exception e) {
					e.printStackTrace();
				}
			}  
			mArrMediaPlayer.clear(); 
		} 
		 
	}

	public float getNarrationMainVolume() 
	{ 
		return (this.mLeftVolume + this.mRightVolume) / 2;
	}
	
	public void setNarrationMainVolume(float pVolume) 
	{
		if (pVolume < 0.0f) {
			pVolume = 0.0f;
		}

		if (pVolume > 1.0f) {
			pVolume = 1.0f;
		}

		this.mLeftVolume = this.mRightVolume = pVolume;
		
		if (this.mArrMediaPlayer.size() > 0) 
		{
			for (int i = 0; i < mArrMediaPlayer.size(); i++) 
			{
				if(mArrMediaPlayer.get(i).getPlayer() != null)
				{
					try {
						mArrMediaPlayer.get(i).getPlayer().setVolume(mLeftVolume, mRightVolume);
					} catch (Exception e) {
						// TODO: handle exception
						e.printStackTrace();
					}
				}
				
			} 
		}
	}

	public void setNarrationVolume(float pVolume) 
	{
		
		if (pVolume < 0.0f) {
			mLeftVolume = 0.0f;
		}
		else if (pVolume > 1.0f) {
			mRightVolume = 1.0f;
		}
		else
		{
			mLeftVolume = pVolume;
		}
	}
	
	private void initData() 
	{ 
		this.mLeftVolume = 1.0f;
		this.mRightVolume = 1.0f;
		mArrMediaPlayer = new ArrayList<CJMediaPlayer>();
		mArrPausedNarration = new ArrayList<CJMediaPlayer>();
	}

	/**
	 * create mediaplayer for music
	 * 
	 * @param pPath
	 *            the pPath relative to assets
	 * @return
	 */
	private MediaPlayer createMediaplayer(final String pPath) {
		MediaPlayer mediaPlayer = new MediaPlayer();
		Log.d(TAG, pPath);
		try {
			mediaPlayer = CJPlatformFileManager.setMediaPlayerFile(mContext, mediaPlayer, pPath);
			mediaPlayer.prepare();

			mediaPlayer.setVolume(this.mLeftVolume, this.mRightVolume);
			
			mediaPlayer.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
				
				public void onCompletion(MediaPlayer mp) {
					completeNarration(pPath);
				}
			});
			
		} catch (final Exception e) {
			mediaPlayer = null;
			Log.e(CJPlatformNarration.TAG, "error: " + e.getMessage(), e);
		}

		return mediaPlayer;
	}

	private void completeNarration(String path)
	{ 
		stopNarration(path);
		((E002Template)mContext).narrationFinishedCallback(path);
	}
	
	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================
	
	class CJMediaPlayer
	{
		private MediaPlayer player; 	
		private String path;
		private boolean isPause; 
		private float volume;
		
		// ===========================================================
		// Getter & Setter
		// ===========================================================
		public MediaPlayer getPlayer() {
			return player;
		}
		public void setPlayer(MediaPlayer player) {
			this.player = player;
		}
		public boolean isPause() {
			return isPause;
		}
		public void setPause(boolean isPause) {
			this.isPause = isPause;
		}
		public String getPath() {
			return path;
		}
		public void setPath(String path) {
			this.path = path;
		}
		public float getVolume() {
			return volume;
		}
		public void setVolume(float volume) {
			this.volume = volume;
		}
		
	}
}
