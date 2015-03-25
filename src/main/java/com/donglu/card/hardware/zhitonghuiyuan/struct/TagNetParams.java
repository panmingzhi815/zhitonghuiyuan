package com.donglu.card.hardware.zhitonghuiyuan.struct;


import com.sun.jna.Structure;

public class TagNetParams extends Structure {

	public byte ucDeviceIP[] = new byte[100];
	public byte ucMaskIP[] = new byte[100];
	public byte ucGateIP[] = new byte[100];
	public byte ucMac[] = new byte[100];

	public static class ByReference extends TagNetParams implements Structure.ByReference {
	}

	public static class ByValue extends TagNetParams implements Structure.ByValue {
	}
}
