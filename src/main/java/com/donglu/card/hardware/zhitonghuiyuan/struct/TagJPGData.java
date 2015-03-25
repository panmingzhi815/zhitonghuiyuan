package com.donglu.card.hardware.zhitonghuiyuan.struct;


import com.sun.jna.Structure;
import com.sun.jna.ptr.IntByReference;

public class TagJPGData extends Structure {

	public IntByReference pDeviceHandle;
	public String ucDeviceIP;
	public String pucImage;
	public Integer uiImageLen;
	public Short usImageWidth;
	public Short usImageHeight;
	public Short usLeft;
	public Short usRight;
	public Short usTop;
	public Short usBottom;
	
}
