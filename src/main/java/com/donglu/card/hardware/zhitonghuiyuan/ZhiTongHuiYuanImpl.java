package com.donglu.card.hardware.zhitonghuiyuan;

import java.io.File;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.TimeUnit;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.donglu.card.hardware.zhitonghuiyuan.callback.DeviceInfoCallback;
import com.donglu.card.hardware.zhitonghuiyuan.callback.DeviceStatusCallback;
import com.donglu.card.hardware.zhitonghuiyuan.callback.JPGStreamCallBack;
import com.donglu.card.hardware.zhitonghuiyuan.callback.VehicleDataCallback;
import com.donglu.card.hardware.zhitonghuiyuan.struct.TagDeviceInfo;
import com.donglu.card.hardware.zhitonghuiyuan.struct.TagDeviceStatus;
import com.donglu.card.hardware.zhitonghuiyuan.struct.TagJPGData;
import com.donglu.card.hardware.zhitonghuiyuan.struct.TagVehicleData;
import com.sun.jna.Native;
import com.sun.jna.NativeLibrary;
import com.sun.jna.Pointer;
import com.sun.jna.ptr.IntByReference;

public class ZhiTongHuiYuanImpl implements ZhiTongHuiYuan {

	private static final Logger LOGGER = LoggerFactory.getLogger(ZhiTongHuiYuanImpl.class);
	private static final String LIBRARY_NAME = "LPRSDK";
	private static final ZhiTongHuiYuanNativeJNA HvDevice;
	private static final Map<String,IntByReference> pointerMap = new HashMap<String,IntByReference>();

	static {
		System.setProperty("jna.encoding", "GB2312");
		String path = System.getProperty("user.dir") + File.separator + "native";
		NativeLibrary.addSearchPath(LIBRARY_NAME, path);
		HvDevice = (ZhiTongHuiYuanNativeJNA) Native.loadLibrary(LIBRARY_NAME, ZhiTongHuiYuanNativeJNA.class);
	}

	public int openDevice(String ip,VehicleDataCallback dataCallback) {
		LOGGER.info("打开智通慧眼设备：{}",ip);
		
		int result = 0;
		try{
			DeviceInfoCallback deviceInfoCallback = new DeviceInfoCallback() {
				
				public void invoke(Pointer pUserData, TagDeviceInfo tagDeviceInfo) {
					LOGGER.info("DeviceInfoCallback invoke");
				}
			};
			DeviceStatusCallback deviceStatusCallback = new DeviceStatusCallback() {
				
				public void invoke(Pointer pUserData, TagDeviceStatus pStatus) {
					LOGGER.info("DeviceStatusCallback invoke");
				}
			};
			JPGStreamCallBack jpgStreamCallBack = new JPGStreamCallBack() {
				
				public void invoke(Pointer pUserData, TagJPGData pJPGData) {
					LOGGER.info("JPGStreamCallBack invoke");
				}
			};
			int lpr_Init = HvDevice.LPR_Init(null,Pointer.NULL, deviceInfoCallback, deviceStatusCallback, dataCallback, jpgStreamCallBack);
			LOGGER.info("初始化智通慧眼设备：{} 返回状态:{}",ip,lpr_Init);
			IntByReference hwnd = new IntByReference(0);
			result = HvDevice.LPR_ConnectCamera(ip, hwnd);
			pointerMap.put(ip, hwnd);
			LOGGER.info("连接智通慧眼设备：{} 返回状态:{}",ip,result);
		}catch(Exception e){
			LOGGER.error("打开智通慧眼设备发生异常",e);
		}
		return result;
	}

	public int closeDevice() {
		LOGGER.info("准备关闭智通慧眼设备");
		
		int result = 0;
		Set<String> keySet = pointerMap.keySet();
		for (String string : keySet) {
			int lpr_DisconnectCamera = HvDevice.LPR_DisconnectCamera(pointerMap.get(string));
			LOGGER.info("断开智通慧眼设备：{},返回状态为：{}",string,lpr_DisconnectCamera);
		}
		result = HvDevice.LPR_Quit();
		LOGGER.info("释放智通慧眼动态库返回状态:{}",result);
		return result;
	}

	public int tiggerDevice(String ip) {
		LOGGER.info("手动触发智通慧眼设备：{}",ip);
		
		int result = 0;
		try{
			if(pointerMap.get(ip) != null){			
				result = HvDevice.LPR_Capture(pointerMap.get(ip));
				LOGGER.info("手动触发智通慧眼设备：{} 返回状态:{}",ip,result);
			}
		}catch(Exception e){
			LOGGER.error("手动触发智通慧眼设备：{} 发生异常:{}",ip,e.getMessage());
		}
		return result;
	}
	
	public static void main(String[] args) {
		ZhiTongHuiYuan zhiTongHuiYuan = new ZhiTongHuiYuanImpl();
		zhiTongHuiYuan.openDevice(args[0], new VehicleDataCallback() {
			
			public void invoke(Pointer pUserData, TagVehicleData pData) {
				LOGGER.info("收到车牌识别仪{} 车牌结果{}",pData.ucDeviceIP,pData.ucPlate);
			}
		});
		
		for (int i = 0; i < 500; i++) {
			try {
				TimeUnit.SECONDS.sleep(5);
				zhiTongHuiYuan.tiggerDevice(args[0]);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

}
