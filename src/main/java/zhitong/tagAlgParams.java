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
public class tagAlgParams extends Structure<tagAlgParams, tagAlgParams.ByValue, tagAlgParams.ByReference > {
	/**
	 * @see TRIGGER_MODE<br>
	 * \u7ebf\u5708\u89e6\u53d1\u6216\u89c6\u9891\u89e6\u53d1
	 */
	public int TriggerMode;
	/** \u68c0\u6d4b\u533a\u57df\u5de6\u8fb9\u754c */
	public short usLeft;
	/** \u68c0\u6d4b\u533a\u57df\u4e0a\u8fb9\u754c */
	public short usTop;
	/** \u68c0\u6d4b\u533a\u57df\u53f3\u8fb9\u754c */
	public short usRight;
	/** \u68c0\u6d4b\u533a\u57df\u4e0b\u8fb9\u754c */
	public short usBottom;
	/**
	 * @see MAINDIRECT<br>
	 * \u4e3b\u884c\u65b9\u5411\uff1a\u5de6\u4e0a\uff0c\u5de6\u4e0b\uff0c\u53f3\u4e0a\uff0c\u53f3\u4e0b
	 */
	public int MainDirect;
	/** \u662f\u5426\u6293\u62cd\u9006\u884c */
	public byte bGetOppEn;
	public tagAlgParams() {
		super();
	}
	protected List<? > getFieldOrder() {
		return Arrays.asList("TriggerMode", "usLeft", "usTop", "usRight", "usBottom", "MainDirect", "bGetOppEn");
	}
	public tagAlgParams(int TriggerMode, short usLeft, short usTop, short usRight, short usBottom, int MainDirect, byte bGetOppEn) {
		super();
		this.TriggerMode = TriggerMode;
		this.usLeft = usLeft;
		this.usTop = usTop;
		this.usRight = usRight;
		this.usBottom = usBottom;
		this.MainDirect = MainDirect;
		this.bGetOppEn = bGetOppEn;
	}
	public tagAlgParams(Pointer peer) {
		super(peer);
	}
	protected ByReference newByReference() { return new ByReference(); }
	protected ByValue newByValue() { return new ByValue(); }
	protected tagAlgParams newInstance() { return new tagAlgParams(); }
	public static tagAlgParams[] newArray(int arrayLength) {
		return Structure.newArray(tagAlgParams.class, arrayLength);
	}
	public static class ByReference extends tagAlgParams implements Structure.ByReference {
		
	};
	public static class ByValue extends tagAlgParams implements Structure.ByValue {
		
	};
}
