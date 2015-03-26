package zhitong;
import java.nio.ByteBuffer;
import java.nio.IntBuffer;

import com.ochafik.lang.jnaerator.runtime.LibraryExtractor;
import com.ochafik.lang.jnaerator.runtime.MangledFunctionMapper;
import com.sun.jna.Callback;
import com.sun.jna.Native;
import com.sun.jna.NativeLibrary;
import com.sun.jna.Pointer;
import com.sun.jna.platform.win32.WinDef.HWND;
import com.sun.jna.ptr.IntByReference;
import com.sun.jna.ptr.PointerByReference;
import com.sun.jna.win32.StdCallLibrary;
/**
 * JNA Wrapper for library <b>zhitong</b><br>
 * This file was autogenerated by <a href="http://jnaerator.googlecode.com/">JNAerator</a>,<br>
 * a tool written by <a href="http://ochafik.com/">Olivier Chafik</a> that <a href="http://code.google.com/p/jnaerator/wiki/CreditsAndLicense">uses a few opensource projects.</a>.<br>
 * For help, please visit <a href="http://nativelibs4java.googlecode.com/">NativeLibs4Java</a> , <a href="http://rococoa.dev.java.net/">Rococoa</a>, or <a href="http://jna.dev.java.net/">JNA</a>.
 */
public interface ZhitongLibrary extends StdCallLibrary {
	public static final String JNA_LIBRARY_NAME = LibraryExtractor.getLibraryPath("LPRSDK", true, ZhitongLibrary.class);
	public static final NativeLibrary JNA_NATIVE_LIB = NativeLibrary.getInstance(ZhitongLibrary.JNA_LIBRARY_NAME, MangledFunctionMapper.DEFAULT_OPTIONS);
	public static final ZhitongLibrary INSTANCE = (ZhitongLibrary)Native.loadLibrary(ZhitongLibrary.JNA_LIBRARY_NAME, ZhitongLibrary.class, MangledFunctionMapper.DEFAULT_OPTIONS);
	public static interface FEEKBACK_TYPE {
		public static final int RESULT_OK = 0;
		public static final int INIT_SUCCESS = 1;
		public static final int NO_INIT = 2;
		public static final int PARAMS_ERROR = 3;
		public static final int SOCKET_NULL = 4;
		public static final int THREAD_FAIL = 5;
		public static final int CREATE_FAIL = 6;
		public static final int SEND_FAIL = 7;
		public static final int NO_FIND_DEVICE = 8;
		public static final int DEVICE_OPENED = 9;
		public static final int DEVICE_DISCONNECT = 10;
		public static final int CONTORL_NOCONNECTION = 11;
		public static final int NO_RECEIVED_DATA = 12;
		public static final int OTHER_ERROR = 100;
		public static final int TIME_OUT = 209;
	};
	public static interface DEVICE_STATUS {
		public static final int CONNECT_SUCCESS = 0;
		public static final int CREATE_ERROR = 1;
		public static final int CONNECT_ERROR = 2;
		public static final int ABNORMALNET_ERROR = 3;
		public static final int DEVICE_RESET = 4;
	};
	public static interface PLATE_COLOR {
		public static final int NON_PLATE = 0;
		public static final int BLUE_COLOR = 1;
		public static final int WHITE_COLOR = 2;
		public static final int BLACK_COLOR = 3;
		public static final int YELLOW_COLOR = 4;
	};
	public static interface DEVICE_TRIGGERMODE {
		public static final int UNKNOWN_TRIGGER_MODE = 0;
		public static final int VIDEO_TRIGGER_MODE = 1;
		public static final int LINE_TRIGGER_MODE = 2;
		public static final int SOFT_TRIGGER_MODE = 3;
	};
	public static interface USER_TYPE {
		public static final int NORMAL_USER = 0;
		public static final int UNKNOWN_USER = 1;
	};
	public static interface SHUTTER_PARAMS {
		public static final int SHUTTER_50 = 6;
		public static final int SHUTTER_75 = 7;
		public static final int SHUTTER_100 = 8;
		public static final int SHUTTER_120 = 9;
		public static final int SHUTTER_150 = 10;
		public static final int SHUTTER_215 = 11;
		public static final int SHUTTER_300 = 12;
		public static final int SHUTTER_425 = 13;
		public static final int SHUTTER_600 = 14;
		public static final int SHUTTER_1000 = 15;
		public static final int SHUTTER_1250 = 16;
		public static final int SHUTTER_1750 = 17;
		public static final int SHUTTER_2500 = 18;
		public static final int SHUTTER_3500 = 19;
		public static final int SHUTTER_6000 = 20;
		public static final int SHUTTER_10000 = 21;
	};
	public static interface MAIN_CMD {
		public static final int SYSTEM_CMD = 0x00;
		public static final int LIGHT_CMD = 0x20;
		public static final int OSD_CMD = 0x30;
		public static final int EPLD_CMD = 0x60;
		public static final int LED_CMD = 0x70;
		public static final int CAMERA_CMD = 0x71;
		public static final int MOVE_CMD = 0x80;
		public static final int CAPTURE_DATA = 0xFF;
	};
	public static interface SYSTEM_SUBCMD {
		public static final int HEART_CMD = 0x00;
		public static final int VERSION_INFO = 0x04;
		public static final int IMAGE_QUALITY = 0x05;
		public static final int DEVICE_RESTART = 0x0C;
		public static final int RESTART_TIME = 0x0D;
		public static final int OCR_PARAMS = 0x16;
		public static final int SERIRAL_NO = 0x18;
		public static final int ALG_PARAMS = 0x1A;
		public static final int DEVICE_ID = 0x1B;
		public static final int DEVICE_CODE = 0x1C;
		public static final int AUTHOR_INFO = 0x1D;
		public static final int AUTHOR_VALIDTIME = 0x23;
		public static final int WORK_MODE = 0x1E;
		public static final int VERIFYTIME_MODE = 0x1F;
		public static final int NTP_SERVERIP = 0x20;
		public static final int NTP_TIMEOUT = 0x21;
	};
	public static interface VERSION_OBJECT {
		public static final int MAIN_VERSION = 0x00;
		public static final int DSP_SUBVERSION = 0x01;
		public static final int MCU_VERSION = 0x02;
		public static final int ALG_VERSION = 0x03;
		public static final int JPG_VERSION = 0x04;
		public static final int EEPROM_VERSION = 0x05;
	};
	public static interface IMAGE_QUALITY_OBJECT {
		public static final int BIG_IMAGE_QUALITY = 0x00;
		public static final int CIF_IMAGE_QUALITY = 0x01;
		public static final int PLATE_IMAGE_QUALITY = 0x02;
	};
	public static interface LIGHT_SUBCMD {
		public static final int LIGHT_MODE = 0x00;
		public static final int AUTOLIGHT_ENABLE = 0x01;
		public static final int SYSTEM_TIME = 0x02;
		public static final int LIGHT_PARAMS = 0x03;
		public static final int IMAGE_BRIGHTNESS = 0x07;
		public static final int CAMERA_CURSTATUS = 0x0A;
		public static final int CAMERA_PARAMS = 0x0B;
		public static final int CUR_LIGHTBASE = 0x0D;
		public static final int LIGHT_VALIDNUM = 0x0E;
		public static final int DAY_EXPOSURE_COMPENSATION = 0x0F;
		public static final int NIGHT_EXPOSURE_COMPENSATION = 0x10;
		public static final int REF_GAIN = 0x11;
		public static final int REF_BRIGHTNESS = 0x12;
	};
	public static interface LIGHT_MODE_VALUE {
		public static final int AUTO_LIGHT = 0x00;
		public static final int MIXED_LIGHT = 0x01;
	};
	public static interface CAMERA_CURSTATUS_PARAMS {
		public static final int SHUTTER_VALUE = 0x00;
		public static final int APARTURE_VALUE = 0x01;
		public static final int GAIN_VALUE = 0x02;
		public static final int VIEW_VALUE = 0x03;
		public static final int F_VALUE = 0x04;
		public static final int BRIGHT_NUM = 0x05;
		public static final int DARK_NUM = 0x06;
	};
	public static interface LED_SUBCMD {
		public static final int ENABLE_LED = 0x00;
		public static final int OPEN_CLOSE_BASE = 0x01;
		public static final int LED_BRIGHTNESS = 0x02;
		public static final int LED_STATUS = 0x03;
		public static final int LED_DELAY = 0x04;
	};
	public static interface OSD_SUBCMD {
		public static final int OSD_ENABLE = 0x0C;
		public static final int OSD_INFO = 0x0D;
	};
	public static interface CAMERA_CONTROL_CMD {
		public static final int POINT_EXPOSURE = 0x06;
		public static final int CAMERA_PHASE = 0x07;
	};
	public static interface OSD_ENABLE_OBJECT {
		public static final int OSD_TIME_ENABLE = 0x00;
		public static final int OSD_INFO_ENABLE = 0x03;
		public static final int OSD_PLATE_ENABLE = 0x04;
	};
	public static interface EPLD_SUBCMD {
		public static final int LINE_POLARITY = 0x01;
		public static final int CAMERA_MENU = 0x0A;
		public static final int VIEW_F = 0x0B;
	};
	public static interface VIEW_F_OBJECT {
		public static final int VIEW_OBJECT = 0x00;
		public static final int F_OBJECT = 0x01;
	};
	public static interface LED_STATUS_OBJECT {
		public static final int OPEN_BASE = 0x00;
		public static final int CLOSE_BASE = 0x01;
	};
	public static interface WORKMODE {
		public static final int NORMAL_WORKMODE = 0;
		public static final int VIDEO_EXPOSURE = 1;
	};
	public static interface MAINDIRECT {
		public static final int LEFT_TOP = 0;
		public static final int LEFT_BOTTOM = 1;
		public static final int RIGHT_TOP = 2;
		public static final int RIGHT_BOTTOM = 3;
		public static final int UNDECIDED = 4;
	};
	public static interface TRIGGER_MODE {
		public static final int LINE_TRIGGER = 0;
		public static final int VIDEO_TRIGGER = 2;
	};
	public static final int INVALID_HANLE = (int)0;
	public static final int IP_MAX_LEN = (int)16;
	public static final int MACADDR_LEN = (int)6;
	public static final int VERSION_LEN = (int)255;
	public static final int MAX_PLATE_LEN = (int)16;
	public static final int MAX_TIME_LEN = (int)8;
	public static final int AUTHORINFO_LEN = (int)100;
	public static final int SERIALNO_LEN = (int)20;
	public static final int FEEKMSG_MAX_LEN = (int)100;
	public static final int CMD_LEN = (int)512;
	public static final int CMD_READ = (int)0;
	public static final int CMD_WRITE = (int)1;
	public static final int ENABLE_FUNCTION = (int)1;
	public static final int DISABLE_FUNCTION = (int)0;
	public interface DeviceInfoCallback extends Callback {
		void apply(Pointer pUserData, tagDeviceInfo pDeviceInfo);
	};
	public interface DeviceStatusCallback extends Callback {
		void apply(Pointer pUserData, tagDeviceStatus pStatus);
	};
	public interface VehicleDataCallback extends Callback {
		void apply(Pointer pUserData, tagVehicleData pData);
	};
	public interface JPGStreamCallBack extends Callback {
		void apply(Pointer pUserData, tagJPGData pJPGData);
	};
	int LPR_IsWriteLog(byte bWriteLog);
	@Deprecated 
	int LPR_GetErrorMsg(int FeekCode, Pointer pchErrMsg);
	int LPR_GetErrorMsg(int FeekCode, ByteBuffer pchErrMsg);
	int LPR_Init(HWND hWnd, Pointer pUserData, ZhitongLibrary.DeviceInfoCallback fucDeviceInfo, ZhitongLibrary.DeviceStatusCallback fucStatus, ZhitongLibrary.VehicleDataCallback fucVehicleData, ZhitongLibrary.JPGStreamCallBack fucJPGStream);
	void LPR_Quit();
	int LPR_ScanDevice();
	int LPR_SetNetParams(Pointer pHandle, tagNetParams pOldParams, tagNetParams pNewParams);
	int LPR_ControlContent(tagOutputContent pContent);
	@Deprecated 
	int LPR_ConnectCamera(Pointer pchDeviceIP, PointerByReference pHandle);
	int LPR_ConnectCamera(ByteBuffer pchDeviceIP, PointerByReference pHandle);
	int LPR_DisconnectCamera(Pointer pHandle);
	int LPR_Capture(Pointer pHandle);
	int LPR_CaptureEx(Pointer pHandle, int nTimeout);
	@Deprecated 
	int LPR_CheckStatus(Pointer pHandle, IntByReference pConnStatus);
	int LPR_CheckStatus(Pointer pHandle, IntBuffer pConnStatus);
	int LPR_AdjustTime(Pointer pHandle, long dwTimeMs);
	@Deprecated 
	int LPR_NTPEnable(Pointer pHandle, byte bNTP, Pointer pchNTPSeverIP);
	int LPR_NTPEnable(Pointer pHandle, byte bNTP, ByteBuffer pchNTPSeverIP);
	int LPR_GetAllVersion(Pointer pHandle, tagVersionInfo pVerInfo);
}
