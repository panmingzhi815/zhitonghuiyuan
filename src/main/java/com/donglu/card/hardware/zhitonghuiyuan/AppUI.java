package com.donglu.card.hardware.zhitonghuiyuan;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.nio.ByteBuffer;
import java.nio.file.Files;
import java.nio.file.OpenOption;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Text;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;

import zhitong.ZhitongLibrary;
import zhitong.ZhitongLibrary.DeviceInfoCallback;
import zhitong.ZhitongLibrary.DeviceStatusCallback;
import zhitong.ZhitongLibrary.JPGStreamCallBack;
import zhitong.ZhitongLibrary.VehicleDataCallback;
import zhitong.tagDeviceInfo;
import zhitong.tagDeviceStatus;
import zhitong.tagJPGData;
import zhitong.tagVehicleData;

import com.sun.jna.Pointer;
import com.sun.jna.ptr.IntByReference;
import com.sun.jna.ptr.PointerByReference;


public class AppUI {

	protected Shell shell;
	private Text text;
	private Text text_1;
	private DeviceInfoCallback deviceInfoCallback;
	private JPGStreamCallBack jpgStreamCallBack;
	private DeviceStatusCallback deviceStatusCallback;
	private VehicleDataCallback dataCallback;
	private PointerByReference pHandle;

	/**
	 * Launch the application.
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			AppUI window = new AppUI();
			window.open();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * Open the window.
	 */
	public void open() {
		Display display = Display.getDefault();
		createContents();
		shell.open();
		shell.layout();
		Runtime.getRuntime().addShutdownHook(new Thread(new Runnable() {
			public void run() {
				ZhitongLibrary.INSTANCE.LPR_Quit();
			}
		}));
		while (!shell.isDisposed()) {
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
	}

	/**
	 * Create contents of the window.
	 */
	protected void createContents() {
		shell = new Shell();
		shell.setSize(450, 300);
		shell.setText("智通慧眼动态库调用步骤");
		shell.setLayout(new GridLayout(3, false));
		
		Label label = new Label(shell, SWT.NONE);
		label.setText("第一步：");
		
		Button button = new Button(shell, SWT.NONE);
		button.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				clickInit();
			}
		});
		button.setText("初始化");
		new Label(shell, SWT.NONE);
		
		Label label_1 = new Label(shell, SWT.NONE);
		label_1.setLayoutData(new GridData(SWT.RIGHT, SWT.CENTER, false, false, 1, 1));
		label_1.setText("第二步：");
		
		text = new Text(shell, SWT.BORDER);
		text.setText("192.168.5.115");
		GridData gd_text = new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1);
		gd_text.widthHint = 30;
		text.setLayoutData(gd_text);
		
		Button btnNewButton = new Button(shell, SWT.NONE);
		btnNewButton.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				clickConn();
			}
		});
		btnNewButton.setLayoutData(new GridData(SWT.LEFT, SWT.CENTER, true, false, 1, 1));
		btnNewButton.setText("连接设备");
		
		Label label_2 = new Label(shell, SWT.NONE);
		label_2.setText("第三步：");
		
		Button button_1 = new Button(shell, SWT.NONE);
		button_1.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				clickCapture();
			}
		});
		button_1.setText("触发抓拍");
		new Label(shell, SWT.NONE);
		
		text_1 = new Text(shell, SWT.BORDER | SWT.WRAP | SWT.MULTI);
		text_1.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 3, 1));
	}

	protected void clickCapture() {
		String ip = text.getText().trim();
		int lpr_Capture = ZhitongLibrary.INSTANCE.LPR_CaptureEx(pHandle.getValue(),2);
		text_1.append("手动触发设备"+ip+"返回结果:"+lpr_Capture+"\n");
	}

	protected void clickConn() {
		try {
			String ip = text.getText().trim();
			pHandle = new PointerByReference();
			ByteBuffer sendBuffer = ByteBuffer.wrap(ip.getBytes("UTF-8"));
			int lpr_ConnectCamera = ZhitongLibrary.INSTANCE.LPR_ConnectCamera(sendBuffer,pHandle);
			text_1.append("连接设备"+ip+"返回结果:"+lpr_ConnectCamera+"\n");
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	protected void clickInit() {
		deviceInfoCallback = new ZhitongLibrary.DeviceInfoCallback() {
			
			public void apply(Pointer pUserData, tagDeviceInfo pDeviceInfo) {
				// TODO Auto-generated method stub
				
			}
		};
		jpgStreamCallBack = new ZhitongLibrary.JPGStreamCallBack() {
			
			public void apply(Pointer pUserData, tagJPGData pJPGData) {
				// TODO Auto-generated method stub
				
			}
		};
		deviceStatusCallback = new ZhitongLibrary.DeviceStatusCallback() {
			
			public void apply(Pointer pUserData, tagDeviceStatus pStatus) {
				// TODO Auto-generated method stub
				
			}
		};
		dataCallback = new ZhitongLibrary.VehicleDataCallback() {
			
			public void apply(Pointer pUserData, final tagVehicleData pData) {
				shell.getDisplay().asyncExec(new Runnable() {
					public void run(){
						String ip = new String(pData.ucDeviceIP).trim();
						text_1.append(String.format("己有车牌信息回调 ip:%s",ip));
						text_1.append("\n");
						text_1.append(String.format("己有车牌信息回调 车牌:%s", new String(pData.ucPlate)));
						text_1.append("\n");
						Path pathFrom = Paths.get(ip, System.currentTimeMillis()+".jpg");  
						try {
							Files.write(pathFrom, pData.pucBigImage.getByteArray(0, pData.uiBigImageLen), StandardOpenOption.CREATE);
						} catch (IOException e) {
							e.printStackTrace();
						}
					}
				});
			}
		};
		ZhitongLibrary.INSTANCE.LPR_IsWriteLog((byte)1);
		int lpr_Init2 = ZhitongLibrary.INSTANCE.LPR_Init(null, Pointer.NULL, deviceInfoCallback, deviceStatusCallback, dataCallback, jpgStreamCallBack);
		text_1.append("初始化返回结果:"+lpr_Init2+"\n");
	}
}
