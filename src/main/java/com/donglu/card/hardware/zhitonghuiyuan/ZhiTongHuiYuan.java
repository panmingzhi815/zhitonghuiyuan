package com.donglu.card.hardware.zhitonghuiyuan;

import zhitong.ZhitongLibrary;

public interface ZhiTongHuiYuan {

	/**
	 * 关闭所有设备监控，释放动态库
	 * @return 0为成功，其他为异常
	 */
	public int closeDevice();

	/**
	 * 手动触发车牌识别仪抓拍
	 * @param ip 待触发的车牌识别设备
	 * @return 0为成功，其他为异常
	 */
	public int tiggerDevice(String ip);

	/**
	 * 开始监听车牌识别设备
	 * @param ip 设备ip
	 * @param dataCallback 结里回调信息
	 * @return 0为成功，其他为异常
	 */
	public int openDevice(String ip, ZhitongLibrary.VehicleDataCallback dataCallback);
}
