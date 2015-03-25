package com.donglu.card.hardware.zhitonghuiyuan.struct;


import com.sun.jna.Structure;
import com.sun.jna.ptr.IntByReference;

public class TagJPGData extends Structure {

	public IntByReference pDeviceHandle;
	public byte ucDeviceIP[] = new byte[100];
	public byte pucImage[] = new byte[2048];
	public int uiImageLen;
	public int usImageWidth;
	public int usImageHeight;
	public int usLeft;
	public int usRight;
	public int usTop;
	public int usBottom;
	
}
