package com.donglu.card.hardware.zhitonghuiyuan.callback;

import com.donglu.card.hardware.zhitonghuiyuan.struct.TagDeviceStatus;
import com.sun.jna.Pointer;
import com.sun.jna.win32.StdCallLibrary.StdCallCallback;

/**
 * @author panmingzhi
 * @createTime 2015年3月24日
 * @content 设备状态回调
 */
public interface DeviceStatusCallback  extends StdCallCallback{

	void invoke(Pointer pUserData, TagDeviceStatus pStatus);
	
}
