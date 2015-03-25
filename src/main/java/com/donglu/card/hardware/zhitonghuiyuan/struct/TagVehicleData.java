package com.donglu.card.hardware.zhitonghuiyuan.struct;

import com.sun.jna.Pointer;
import com.sun.jna.Structure;

public class TagVehicleData extends Structure {

	public Pointer pDeviceHandle;//设备句柄
    public Short usSerialNO;//序列号
    public String ucDeviceIP;//设备IP
    public Integer ui32DeviceID;//设备ID
  
    public Integer ui32UserType;//表示用户类型:0 正常用户，1 未授权用户，其他值保留
    public Integer ui32Brightness;//亮度值
    public Integer triggermode;//触发类型:1 视频 2 线圈 3 模拟 0 未知 ，其他值保留
    public String ai8UserDefineInfo;
    public String ucTime;//时间，年（减掉后的年份）、月、日、时、分、秒、毫秒（占两个字节）
    public String ucPlate;//车牌号码
    public Integer PlateColor;//车牌颜色

    public Pointer pucBigImage;//抓拍大图数据
    public Integer uiBigImageLen;//抓拍大图数据长度
    public Short usBigImageWidth;//抓拍大图宽度
    public Short usBigImageHeight;//抓拍大图高度

    public Pointer pucCIFImage;//抓拍CIF图数据
    public Integer uiCIFImageLen;//抓拍CIF图数据长度
    public Short usCIFImageWidth;//抓拍CIF图宽度
    public Short usCIFImageHeight;//抓拍CIF图高度

    public Pointer pucPlateImage;//抓拍车牌图数据
    public Integer uiPlateImageLen;//抓拍车牌图数据长度
    public Short usPlateImageWidth;//抓拍车牌图宽度
    public Short usPlateImageHeight;//抓拍车牌图高度
	
}
