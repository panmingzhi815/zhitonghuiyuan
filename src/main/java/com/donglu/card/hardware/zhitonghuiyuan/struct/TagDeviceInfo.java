package com.donglu.card.hardware.zhitonghuiyuan.struct;

import com.sun.jna.Structure;

public class TagDeviceInfo extends Structure {
	
	public TagNetParams.ByValue DeviceNetInfo=new TagNetParams.ByValue();
	public byte ucMAC[] = new byte[100];
	public byte ucDeviceVersion[] = new byte[100];
	public String ucConnectNum;
	
}
