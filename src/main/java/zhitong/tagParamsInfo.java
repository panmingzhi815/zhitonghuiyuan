package zhitong;
import com.sun.jna.Pointer;
import com.sun.jna.Structure;
import java.util.Arrays;
import java.util.List;
/**
 * This file was autogenerated by <a href="http://jnaerator.googlecode.com/">JNAerator</a>,<br>
 * a tool written by <a href="http://ochafik.com/">Olivier Chafik</a> that <a href="http://code.google.com/p/jnaerator/wiki/CreditsAndLicense">uses a few opensource projects.</a>.<br>
 * For help, please visit <a href="http://nativelibs4java.googlecode.com/">NativeLibs4Java</a> , <a href="http://rococoa.dev.java.net/">Rococoa</a>, or <a href="http://jna.dev.java.net/">JNA</a>.
 */
public class tagParamsInfo extends Structure {
	/** \u4e3b\u6307\u4ee4 */
	public byte ucMainCmd;
	/** \u6b21\u6307\u4ee4 */
	public byte ucSubCmd;
	/** \u662f\u5426\u6709\u5bf9\u8c61\u53f7 */
	public byte bHasObject;
	/** \u5bf9\u8c61\u53f7 */
	public byte ucObject;
	/** \u547d\u4ee4\u7c7b\u578b\uff0c\u8bfb\u6216\u8005\u5199 */
	public byte ucCmdType;
	/** \u547d\u4ee4\u957f\u5ea6 */
	public short usCmdLen;
	/**
	 * \u547d\u4ee4\u5185\u5bb9<br>
	 * C type : unsigned char[512]
	 */
	public byte[] ucCmd = new byte[512];
	public tagParamsInfo() {
		super();
	}
	protected List<? > getFieldOrder() {
		return Arrays.asList("ucMainCmd", "ucSubCmd", "bHasObject", "ucObject", "ucCmdType", "usCmdLen", "ucCmd");
	}
	/**
	 * @param ucMainCmd \u4e3b\u6307\u4ee4<br>
	 * @param ucSubCmd \u6b21\u6307\u4ee4<br>
	 * @param bHasObject \u662f\u5426\u6709\u5bf9\u8c61\u53f7<br>
	 * @param ucObject \u5bf9\u8c61\u53f7<br>
	 * @param ucCmdType \u547d\u4ee4\u7c7b\u578b\uff0c\u8bfb\u6216\u8005\u5199<br>
	 * @param usCmdLen \u547d\u4ee4\u957f\u5ea6<br>
	 * @param ucCmd \u547d\u4ee4\u5185\u5bb9<br>
	 * C type : unsigned char[512]
	 */
	public tagParamsInfo(byte ucMainCmd, byte ucSubCmd, byte bHasObject, byte ucObject, byte ucCmdType, short usCmdLen, byte ucCmd[]) {
		super();
		this.ucMainCmd = ucMainCmd;
		this.ucSubCmd = ucSubCmd;
		this.bHasObject = bHasObject;
		this.ucObject = ucObject;
		this.ucCmdType = ucCmdType;
		this.usCmdLen = usCmdLen;
		if ((ucCmd.length != this.ucCmd.length)) 
			throw new IllegalArgumentException("Wrong array size !");
		this.ucCmd = ucCmd;
	}
	public tagParamsInfo(Pointer peer) {
		super(peer);
	}
	public static class ByReference extends tagParamsInfo implements Structure.ByReference {
		
	};
	public static class ByValue extends tagParamsInfo implements Structure.ByValue {
		
	};
}