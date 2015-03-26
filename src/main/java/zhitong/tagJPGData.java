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
public class tagJPGData extends Structure<tagJPGData, tagJPGData.ByValue, tagJPGData.ByReference > {
	/** \u8bbe\u5907\u53e5\u67c4 */
	public Pointer pDeviceHandle;
	/** \u8bbe\u5907IP */
	public byte[] ucDeviceIP = new byte[16];
	/** \u4e00\u5e27\u5b9e\u65f6JPG\u6d41\u6570\u636e */
	public Pointer pucImage;
	/** \u4e00\u5e27\u5b9e\u65f6JPG\u6d41\u6570\u636e\u957f\u5ea6 */
	public int uiImageLen;
	/** \u4e00\u5e27\u5b9e\u65f6JPG\u6d41\u5bbd\u5ea6 */
	public short usImageWidth;
	/** \u4e00\u5e27\u5b9e\u65f6JPG\u6d41\u9ad8\u5ea6 */
	public short usImageHeight;
	public short usLeft;
	public short usRight;
	public short usTop;
	public short usBottom;
	public tagJPGData() {
		super();
	}
	protected List<? > getFieldOrder() {
		return Arrays.asList("pDeviceHandle", "ucDeviceIP", "pucImage", "uiImageLen", "usImageWidth", "usImageHeight", "usLeft", "usRight", "usTop", "usBottom");
	}
	public tagJPGData(Pointer peer) {
		super(peer);
	}
	protected ByReference newByReference() { return new ByReference(); }
	protected ByValue newByValue() { return new ByValue(); }
	protected tagJPGData newInstance() { return new tagJPGData(); }
	public static tagJPGData[] newArray(int arrayLength) {
		return Structure.newArray(tagJPGData.class, arrayLength);
	}
	public static class ByReference extends tagJPGData implements Structure.ByReference {
		
	};
	public static class ByValue extends tagJPGData implements Structure.ByValue {
		
	};
}
