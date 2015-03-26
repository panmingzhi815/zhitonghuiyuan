package com.donglu.card.hardware.zhitonghuiyuan.struct;


import com.sun.jna.Structure;
import com.sun.jna.ptr.IntByReference;

public class TagJPGData extends Structure {

	//TODO 这里我也觉得是个疑问
	//原接口中定义的是void *, 所以应该是Pointer, 但是用IntByReference不知道会不会有什么问题
	//虽然理论上来说所有的Pointer都是一样的。
	public IntByReference pDeviceHandle;
	public byte ucDeviceIP[] = new byte[100];
	
	//TODO 在接口中这个定义的是unsigned char *
	//这里定义成byte[]肯定是不对的，应该定义成Pointer吧？
	public byte pucImage[] = new byte[2048];
	
	public int uiImageLen;
	
	//下面的应该都不对，原借口中都定义的是short, 所以这里也应该是short.
	public int usImageWidth;
	public int usImageHeight;
	public int usLeft;
	public int usRight;
	public int usTop;
	public int usBottom;
	
}
