package zhitong;
import com.ochafik.lang.jnaerator.runtime.Structure;
import com.sun.jna.Pointer;
import java.util.Arrays;
import java.util.List;
/**
 * This file was autogenerated by <a href="http://jnaerator.googlecode.com/">JNAerator</a>,<br>
 * a tool written by <a href="http://ochafik.com/">Olivier Chafik</a> that <a href="http://code.google.com/p/jnaerator/wiki/CreditsAndLicense">uses a few opensource projects.</a>.<br>
 * For help, please visit <a href="http://nativelibs4java.googlecode.com/">NativeLibs4Java</a> , <a href="http://rococoa.dev.java.net/">Rococoa</a>, or <a href="http://jna.dev.java.net/">JNA</a>.
 */
public class tagVehicleData extends Structure<tagVehicleData, tagVehicleData.ByValue, tagVehicleData.ByReference > {
	/** \u8bbe\u5907\u53e5\u67c4 */
	public Pointer pDeviceHandle;
	/** \u5e8f\u5217\u53f7 */
	public short usSerialNO;
	/** \u8bbe\u5907IP */
	public byte[] ucDeviceIP = new byte[16];
	/** \u8bbe\u5907ID */
	public int ui32DeviceID;
	/**
	 * @see USER_TYPE<br>
	 * \u8868\u793a\u7528\u6237\u7c7b\u578b:0 \u6b63\u5e38\u7528\u6237\uff0c1 \u672a\u6388\u6743\u7528\u6237\uff0c\u5176\u4ed6\u503c\u4fdd\u7559
	 */
	public int ui32UserType;
	/** \u4eae\u5ea6\u503c */
	public int ui32Brightness;
	/**
	 * @see DEVICE_TRIGGERMODE<br>
	 * \u89e6\u53d1\u7c7b\u578b:1 \u89c6\u9891 2 \u7ebf\u5708 3 \u6a21\u62df 0 \u672a\u77e5 \uff0c\u5176\u4ed6\u503c\u4fdd\u7559
	 */
	public int triggermode;
	/** \u7528\u6237\u81ea\u5b9a\u4e49\u4fe1\u606f */
	public byte[] ai8UserDefineInfo = new byte[255];
	/** \u65f6\u95f4\uff0c\u5e74\uff08\u51cf\u6389\u540e\u7684\u5e74\u4efd\uff09\u3001\u6708\u3001\u65e5\u3001\u65f6\u3001\u5206\u3001\u79d2\u3001\u6beb\u79d2\uff08\u5360\u4e24\u4e2a\u5b57\u8282\uff09 */
	public byte[] ucTime = new byte[8];
	/** \u8f66\u724c\u53f7\u7801 */
	public byte[] ucPlate = new byte[16];
	/**
	 * @see PLATE_COLOR<br>
	 * \u8f66\u724c\u989c\u8272
	 */
	public int PlateColor;
	/** \u6293\u62cd\u5927\u56fe\u6570\u636e */
	public Pointer pucBigImage;
	/** \u6293\u62cd\u5927\u56fe\u6570\u636e\u957f\u5ea6 */
	public int uiBigImageLen;
	/** \u6293\u62cd\u5927\u56fe\u5bbd\u5ea6 */
	public short usBigImageWidth;
	/** \u6293\u62cd\u5927\u56fe\u9ad8\u5ea6 */
	public short usBigImageHeight;
	/** \u6293\u62cdCIF\u56fe\u6570\u636e */
	public Pointer pucCIFImage;
	/** \u6293\u62cdCIF\u56fe\u6570\u636e\u957f\u5ea6 */
	public int uiCIFImageLen;
	/** \u6293\u62cdCIF\u56fe\u5bbd\u5ea6 */
	public short usCIFImageWidth;
	/** \u6293\u62cdCIF\u56fe\u9ad8\u5ea6 */
	public short usCIFImageHeight;
	/** \u6293\u62cd\u8f66\u724c\u56fe\u6570\u636e */
	public Pointer pucPlateImage;
	/** \u6293\u62cd\u8f66\u724c\u56fe\u6570\u636e\u957f\u5ea6 */
	public int uiPlateImageLen;
	/** \u6293\u62cd\u8f66\u724c\u56fe\u5bbd\u5ea6 */
	public short usPlateImageWidth;
	/** \u6293\u62cd\u8f66\u724c\u56fe\u9ad8\u5ea6 */
	public short usPlateImageHeight;
	public tagVehicleData() {
		super();
	}
	protected List<? > getFieldOrder() {
		return Arrays.asList("pDeviceHandle", "usSerialNO", "ucDeviceIP", "ui32DeviceID", "ui32UserType", "ui32Brightness", "triggermode", "ai8UserDefineInfo", "ucTime", "ucPlate", "PlateColor", "pucBigImage", "uiBigImageLen", "usBigImageWidth", "usBigImageHeight", "pucCIFImage", "uiCIFImageLen", "usCIFImageWidth", "usCIFImageHeight", "pucPlateImage", "uiPlateImageLen", "usPlateImageWidth", "usPlateImageHeight");
	}
	public tagVehicleData(Pointer peer) {
		super(peer);
	}
	protected ByReference newByReference() { return new ByReference(); }
	protected ByValue newByValue() { return new ByValue(); }
	protected tagVehicleData newInstance() { return new tagVehicleData(); }
	public static tagVehicleData[] newArray(int arrayLength) {
		return Structure.newArray(tagVehicleData.class, arrayLength);
	}
	public static class ByReference extends tagVehicleData implements Structure.ByReference {
		
	};
	public static class ByValue extends tagVehicleData implements Structure.ByValue {
		
	};
}
