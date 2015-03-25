package com.donglu.card.hardware.zhitonghuiyuan.struct;

import com.sun.jna.Structure;
import com.sun.jna.ptr.IntByReference;

public class TagVehicleData extends Structure {

	public IntByReference pDeviceHandle;// 设备句柄
	public int usSerialNO;// 序列号
	public char ucDeviceIP[] = new char[50];// 设备IP
	public int ui32DeviceID;// 设备ID

	public int ui32UserType;// 表示用户类型:0 正常用户，1 未授权用户，其他值保留
	public int ui32Brightness;// 亮度值
	public int triggermode;// 触发类型:1 视频 2 线圈 3 模拟 0 未知 ，其他值保留
	public char ai8UserDefineInfo[] = new char[100];
	public char ucTime[] = new char[100];// 时间，年（减掉后的年份）、月、日、时、分、秒、毫秒（占两个字节）
	public char ucPlate[] = new char[100];// 车牌号码
	public int PlateColor;// 车牌颜色

	public String pucBigImage;// 抓拍大图数据
	public int uiBigImageLen;// 抓拍大图数据长度
	public int usBigImageWidth;// 抓拍大图宽度
	public int usBigImageHeight;// 抓拍大图高度

	public String pucCIFImage;// 抓拍CIF图数据
	public int uiCIFImageLen;// 抓拍CIF图数据长度
	public int usCIFImageWidth;// 抓拍CIF图宽度
	public int usCIFImageHeight;// 抓拍CIF图高度

	public String pucPlateImage;// 抓拍车牌图数据
	public int uiPlateImageLen;// 抓拍车牌图数据长度
	public int usPlateImageWidth;// 抓拍车牌图宽度
	public int usPlateImageHeight;// 抓拍车牌图高度

}
