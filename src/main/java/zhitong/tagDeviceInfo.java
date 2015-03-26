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
public class tagDeviceInfo extends Structure<tagDeviceInfo, tagDeviceInfo.ByValue, tagDeviceInfo.ByReference > {
	/** \u8bbe\u5907\u7f51\u7edc\u4fe1\u606f\u53c2\u6570 */
	public tagNetParams DeviceNetInfo;
	/** MAC\u5730\u5740 */
	public byte[] ucMAC = new byte[6];
	/** \u8bbe\u5907\u7248\u672c\u4fe1\u606f */
	public byte[] ucDeviceVersion = new byte[255];
	/** \u7528\u6237\u8fde\u63a5\u6570 */
	public byte ucConnectNum;
	public tagDeviceInfo() {
		super();
	}
	protected List<? > getFieldOrder() {
		return Arrays.asList("DeviceNetInfo", "ucMAC", "ucDeviceVersion", "ucConnectNum");
	}
	public tagDeviceInfo(tagNetParams DeviceNetInfo, byte ucMAC[], byte ucDeviceVersion[], byte ucConnectNum) {
		super();
		this.DeviceNetInfo = DeviceNetInfo;
		if ((ucMAC.length != this.ucMAC.length)) 
			throw new IllegalArgumentException("Wrong array size !");
		this.ucMAC = ucMAC;
		if ((ucDeviceVersion.length != this.ucDeviceVersion.length)) 
			throw new IllegalArgumentException("Wrong array size !");
		this.ucDeviceVersion = ucDeviceVersion;
		this.ucConnectNum = ucConnectNum;
	}
	public tagDeviceInfo(Pointer peer) {
		super(peer);
	}
	protected ByReference newByReference() { return new ByReference(); }
	protected ByValue newByValue() { return new ByValue(); }
	protected tagDeviceInfo newInstance() { return new tagDeviceInfo(); }
	public static tagDeviceInfo[] newArray(int arrayLength) {
		return Structure.newArray(tagDeviceInfo.class, arrayLength);
	}
	public static class ByReference extends tagDeviceInfo implements Structure.ByReference {
		
	};
	public static class ByValue extends tagDeviceInfo implements Structure.ByValue {
		
	};
}
