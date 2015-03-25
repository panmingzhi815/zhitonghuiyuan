package com.donglu.card.hardware.zhitonghuiyuan.callback;

import com.donglu.card.hardware.zhitonghuiyuan.struct.TagJPGData;
import com.sun.jna.Pointer;
import com.sun.jna.win32.StdCallLibrary.StdCallCallback;

/**
 * @author panmingzhi
 * @createTime 2015年3月24日
 * @content 图片流回调
 */
public interface JPGStreamCallBack  extends StdCallCallback{

	void invoke(Pointer pUserData, TagJPGData pJPGData);
	
}
