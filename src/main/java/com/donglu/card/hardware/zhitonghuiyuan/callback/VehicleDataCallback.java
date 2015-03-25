package com.donglu.card.hardware.zhitonghuiyuan.callback;

import com.donglu.card.hardware.zhitonghuiyuan.struct.TagVehicleData;
import com.sun.jna.Pointer;
import com.sun.jna.win32.StdCallLibrary.StdCallCallback;

/**
 * @author panmingzhi
 * @createTime 2015年3月24日
 * @content 车牌信息回调
 */
public interface VehicleDataCallback extends StdCallCallback {
	
	void invoke(Pointer pUserData, TagVehicleData pData);
	
}
