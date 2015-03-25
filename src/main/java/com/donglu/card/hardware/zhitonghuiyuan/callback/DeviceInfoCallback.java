package com.donglu.card.hardware.zhitonghuiyuan.callback;

import com.donglu.card.hardware.zhitonghuiyuan.struct.TagDeviceInfo;
import com.sun.jna.Pointer;
import com.sun.jna.win32.StdCallLibrary.StdCallCallback;

/**
 * @author panmingzhi
 * @createTime 2015年3月24日
 * @content 设备信息回调
 */
public interface DeviceInfoCallback extends StdCallCallback{
	
	void invoke(Pointer pUserData, TagDeviceInfo tagDeviceInfo);

}
