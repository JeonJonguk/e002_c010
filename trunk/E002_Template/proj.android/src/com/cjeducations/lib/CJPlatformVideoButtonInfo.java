package com.cjeducations.lib;

public class CJPlatformVideoButtonInfo {
	
	String filePath; 
	float x;
	float y;
	int tag;
	
	public CJPlatformVideoButtonInfo()
	{
	}
	
	public CJPlatformVideoButtonInfo(String filePath, float x, float y, int tag) 
	{
	 	this.filePath = filePath;
		this.x = x;
		this.y = y;
		this.tag = tag;
	}
}
