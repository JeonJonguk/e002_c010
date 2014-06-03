package com.cjeducations.lib;

public class CJPlatformFrameViewInfo {
	
	public String frameImgPath; 
	public String contentPath;
	public int direction;
	public int x;
	public int y;
	public int width;
	public int height;
	
	public CJPlatformFrameViewInfo()
	{
	}

	public CJPlatformFrameViewInfo(String frameImgPath, int direction, int x,
			int y, int width, int height) {
		super();
		this.frameImgPath = frameImgPath;
		this.direction = direction;
		this.x = x;
		this.y = y;
		this.width = width;
		this.height = height;
	}
	
	public CJPlatformFrameViewInfo(String frameImgPath, String contentPath, int x,
			int y, int width, int height) {
		super();
		this.frameImgPath = frameImgPath;
		this.contentPath = contentPath; 
		this.x = x;
		this.y = y;
		this.width = width;
		this.height = height;
	}
	 
}
