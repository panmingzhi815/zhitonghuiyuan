package com.donglu.card.hardware.zhitonghuiyuan.struct;

import com.sun.jna.Structure;

public class TagDeviceInfo extends Structure {
	public TagNetParams.ByValue DeviceNetInfo=new TagNetParams.ByValue();
	public String ucMAC;
	public String ucDeviceVersion;
	public String ucConnectNum;
}
