package com.donglu.card.hardware.zhitonghuiyuan.struct;


import com.sun.jna.Structure;

public class TagNetParams extends Structure {

	public String ucDeviceIP;
	public String ucMaskIP;
	public String ucGateIP;
	public String ucMac;

	public static class ByReference extends TagNetParams implements Structure.ByReference {
	}

	public static class ByValue extends TagNetParams implements Structure.ByValue {
	}
}
