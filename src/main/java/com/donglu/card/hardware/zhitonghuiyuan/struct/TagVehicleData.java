package com.donglu.card.hardware.zhitonghuiyuan.struct;

import com.sun.jna.Structure;
import com.sun.jna.ptr.IntByReference;

public class TagVehicleData extends Structure {

	public static interface PLATE_COLOR {
		public static final int NON_PLATE = 0;// 未知车牌颜色
		public static final int BLUE_COLOR = 1;// 蓝色
		public static final int WHITE_COLOR = 2;// 白色
		public static final int BLACK_COLOR = 3;// 黑色
		public static final int YELLOW_COLOR = 4;// 黄色
	}

	public static interface DEVICE_TRIGGERMODE {
		public static final int UNKNOWN_TRIGGER_MODE = 0; // 未知
		public static final int VIDEO_TRIGGER_MODE = 1; // 视频
		public static final int LINE_TRIGGER_MODE = 2; // 线圈
		public static final int SOFT_TRIGGER_MODE = 3;// 模拟
	}

	public static interface USER_TYPE {
		public static final int NORMAL_USER = 0; // 正常用户
		public static final int UNKNOWN_USER = 1;// 未授权用户
	}

	public IntByReference pDeviceHandle;// 设备句柄
	public int usSerialNO;// 序列号
	public String ucDeviceIP;// 设备IP
	public int ui32DeviceID;// 设备ID

	public USER_TYPE ui32UserType;// 表示用户类型:0 正常用户，1 未授权用户，其他值保留
	public int ui32Brightness;// 亮度值
	public DEVICE_TRIGGERMODE triggermode;// 触发类型:1 视频 2 线圈 3 模拟 0 未知 ，其他值保留
	public String ai8UserDefineInfo;
	public String ucTime;// 时间，年（减掉后的年份）、月、日、时、分、秒、毫秒（占两个字节）
	public String ucPlate;// 车牌号码
	public PLATE_COLOR PlateColor;// 车牌颜色

	public byte pucBigImage[] = new byte[2048];// 抓拍大图数据
	public int uiBigImageLen;// 抓拍大图数据长度
	public int usBigImageWidth;// 抓拍大图宽度
	public int usBigImageHeight;// 抓拍大图高度

	public byte pucCIFImage[] = new byte[1024];// 抓拍CIF图数据
	public int uiCIFImageLen;// 抓拍CIF图数据长度
	public int usCIFImageWidth;// 抓拍CIF图宽度
	public int usCIFImageHeight;// 抓拍CIF图高度

	public byte pucPlateImage[] = new byte[1024];// 抓拍车牌图数据
	public int uiPlateImageLen;// 抓拍车牌图数据长度
	public int usPlateImageWidth;// 抓拍车牌图宽度
	public int usPlateImageHeight;// 抓拍车牌图高度

}
