package com.donglu.card.hardware.zhitonghuiyuan;

import java.io.File;
import java.nio.ByteBuffer;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.TimeUnit;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import zhitong.ZhitongLibrary;
import zhitong.tagDeviceInfo;
import zhitong.tagDeviceStatus;
import zhitong.tagJPGData;
import zhitong.tagVehicleData;

import com.sun.jna.NativeLibrary;
import com.sun.jna.Pointer;
import com.sun.jna.ptr.PointerByReference;

public class ZhiTongHuiYuanImpl implements ZhiTongHuiYuan {

	private static final Logger LOGGER = LoggerFactory.getLogger(ZhiTongHuiYuanImpl.class);
	private static final String LIBRARY_NAME = "LPRSDK";
//	private static final ZhitongLibrary HvDevice;
	private static final Map<String,PointerByReference> pointerMap = new HashMap<String,PointerByReference>();

	static {
		System.setProperty("jna.encoding", "GB2312");
		String path = System.getProperty("user.dir") + File.separator + "native";
		NativeLibrary.addSearchPath(LIBRARY_NAME, path);
//		HvDevice = (ZhitongLibrary) Native.loadLibrary(LIBRARY_NAME, ZhitongLibrary.class);
	}

	public int openDevice(String ip,ZhitongLibrary.VehicleDataCallback dataCallback) {
		LOGGER.info("打开智通慧眼设备：{}",ip);
		
		int result = 0;
		try{
			zhitong.ZhitongLibrary.DeviceInfoCallback deviceInfoCallback = new ZhitongLibrary.DeviceInfoCallback() {
				
				public void apply(Pointer pUserData, tagDeviceInfo pDeviceInfo) {
					// TODO Auto-generated method stub
					
				}
			};
			zhitong.ZhitongLibrary.JPGStreamCallBack jpgStreamCallBack = new ZhitongLibrary.JPGStreamCallBack() {
				
				public void apply(Pointer pUserData, tagJPGData pJPGData) {
					// TODO Auto-generated method stub
					
				}
			};
			zhitong.ZhitongLibrary.DeviceStatusCallback deviceStatusCallback = new ZhitongLibrary.DeviceStatusCallback() {
				
				public void apply(Pointer pUserData, tagDeviceStatus pStatus) {
					// TODO Auto-generated method stub
					
				}
			};
			ZhitongLibrary.INSTANCE.LPR_IsWriteLog((byte)1);
			int lpr_Init2 = ZhitongLibrary.INSTANCE.LPR_Init(null, Pointer.NULL, deviceInfoCallback, deviceStatusCallback, dataCallback, jpgStreamCallBack);
			LOGGER.info("初始化智通慧眼设备：{} 返回状态:{}",ip,lpr_Init2);
			PointerByReference pHandle = new PointerByReference();

			LOGGER.info("PointerReference Pointer before call: " +pHandle.getPointer().toString());
			LOGGER.info("PointerReference Value before call: " +pHandle.getValue().toString());

			ByteBuffer sendBuffer=ByteBuffer.wrap(ip.getBytes("UTF-8"));
			result = ZhitongLibrary.INSTANCE.LPR_ConnectCamera(sendBuffer,pHandle);

			LOGGER.info("PointerReference Value after call: " +pHandle.getValue().toString());
			LOGGER.info("PointerReference Pointer after call: " +pHandle.getPointer().toString());

			pointerMap.put(ip, pHandle);

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
			int lpr_DisconnectCamera = ZhitongLibrary.INSTANCE.LPR_DisconnectCamera(pointerMap.get(string).getValue());
			LOGGER.info("断开智通慧眼设备：{},返回状态为：{}",string,lpr_DisconnectCamera);
		}
		ZhitongLibrary.INSTANCE.LPR_Quit();
		LOGGER.info("释放智通慧眼动态库");
		return result;
	}

	public int tiggerDevice(String ip) {
		LOGGER.info("手动触发智通慧眼设备：{}",ip);
		
		int result = 0;
		try{
			if(pointerMap.get(ip) != null){			
				result = ZhitongLibrary.INSTANCE.LPR_Capture(pointerMap.get(ip).getValue());
				LOGGER.info("手动触发智通慧眼设备：{} 返回状态:{}",ip,result);
			}
		}catch(Exception e){
			LOGGER.error("手动触发智通慧眼设备：{} 发生异常:{}",ip,e.getMessage());
		}
		return result;
	}
	
	public static void main(String[] args) {
		try{
			zhitong.ZhitongLibrary.VehicleDataCallback vehicleDataCallback2 = new ZhitongLibrary.VehicleDataCallback() {
				
				public void apply(Pointer pUserData, tagVehicleData pData) {
					LOGGER.info("收到车牌识别仪{} 车牌结果{}",pData.ucDeviceIP,pData.ucPlate);
				}
			};
			
			ZhiTongHuiYuan zhiTongHuiYuan = new ZhiTongHuiYuanImpl();
			zhiTongHuiYuan.openDevice(args[0], vehicleDataCallback2);
			
			for (int i = 0; i < 2; i++) {
				try {
					TimeUnit.SECONDS.sleep(10);
					zhiTongHuiYuan.tiggerDevice(args[0]);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}catch(Exception e){
			LOGGER.error("程序运行是发生异常",e);
		}
	}

}
