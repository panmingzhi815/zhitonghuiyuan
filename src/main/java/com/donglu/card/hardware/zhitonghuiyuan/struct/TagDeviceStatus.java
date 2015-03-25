package com.donglu.card.hardware.zhitonghuiyuan.struct;

import com.sun.jna.Structure;
import com.sun.jna.ptr.IntByReference;

public class TagDeviceStatus extends Structure {

	public IntByReference pHandle;
	public byte ucDeviceIP[] = new byte[100];
	public int status;
}
