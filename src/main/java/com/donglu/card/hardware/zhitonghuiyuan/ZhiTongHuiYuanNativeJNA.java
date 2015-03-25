package com.donglu.card.hardware.zhitonghuiyuan;

import com.donglu.card.hardware.zhitonghuiyuan.callback.DeviceInfoCallback;
import com.donglu.card.hardware.zhitonghuiyuan.callback.DeviceStatusCallback;
import com.donglu.card.hardware.zhitonghuiyuan.callback.JPGStreamCallBack;
import com.donglu.card.hardware.zhitonghuiyuan.callback.VehicleDataCallback;
import com.sun.jna.Library;
import com.sun.jna.Pointer;
import com.sun.jna.platform.win32.WinDef.HWND;
import com.sun.jna.ptr.IntByReference;

public interface ZhiTongHuiYuanNativeJNA extends Library {

	int LPR_Init(HWND hWndHandle, Pointer pUserData, DeviceInfoCallback deviceInfoCallback, DeviceStatusCallback deviceStatusCallback, VehicleDataCallback vehicleDataCallback,
		JPGStreamCallBack jpgStreamCallBack);
	
	int LPR_ConnectCamera(String pchDeviceIP,IntByReference hwnd);
	
	int LPR_DisconnectCamera(IntByReference hwnd);
	
	int LPR_Capture(IntByReference hwnd);
	
	int LPR_Quit();

}
