package com.donglu.card.hardware.zhitonghuiyuan;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.Arrays;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.graphics.ImageData;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;

import zhitong.ZhitongLibrary;
import zhitong.ZhitongLibrary.DeviceInfoCallback;
import zhitong.ZhitongLibrary.DeviceStatusCallback;
import zhitong.ZhitongLibrary.JPGStreamCallBack;
import zhitong.ZhitongLibrary.VehicleDataCallback;
import zhitong.tagDeviceInfo;
import zhitong.tagDeviceStatus;
import zhitong.tagJPGData;
import zhitong.tagVehicleData;

import com.sun.jna.Memory;
import com.sun.jna.Pointer;
import com.sun.jna.ptr.PointerByReference;

import org.eclipse.wb.swt.SWTResourceManager;


public class AppUI {
	
	static{
		System.setProperty("jna.encoding", "GB2312");
	}

	protected Shell shell;
	private Text text;
	private Text text_1;
	private DeviceInfoCallback deviceInfoCallback;
	private JPGStreamCallBack jpgStreamCallBack;
	private DeviceStatusCallback deviceStatusCallback;
	private VehicleDataCallback dataCallback;
	private PointerByReference pHandle;
	private Text text_2;
	private Label lblNewLabel_1;
	private Label lblNewLabel;

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
		shell.setSize(450, 618);
		shell.setText("智通慧眼动态库调用步骤");
		shell.setLayout(new GridLayout(3, false));
		
		Label lblip = new Label(shell, SWT.NONE);
		lblip.setText("设备ip:");
		
		text = new Text(shell, SWT.BORDER);
		text.setText("192.168.5.115");
		GridData gd_text = new GridData(SWT.FILL, SWT.CENTER, false, false, 1, 1);
		gd_text.widthHint = 100;
		text.setLayoutData(gd_text);
		
		lblNewLabel = new Label(shell, SWT.BORDER);
		lblNewLabel.setForeground(SWTResourceManager.getColor(SWT.COLOR_WIDGET_DARK_SHADOW));
		lblNewLabel.setBackground(SWTResourceManager.getColor(SWT.COLOR_GRAY));
		lblNewLabel.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false, 1, 4));
		
		Label label = new Label(shell, SWT.NONE);
		label.setText("第一步：");
		
		Button button = new Button(shell, SWT.NONE);
		GridData gd_button = new GridData(SWT.CENTER, SWT.CENTER, false, false, 1, 1);
		gd_button.widthHint = 80;
		button.setLayoutData(gd_button);
		button.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				clickInit();
			}
		});
		button.setText("初始化");
		
		Label label_1 = new Label(shell, SWT.NONE);
		label_1.setText("第二步：");
		
		Button btnNewButton = new Button(shell, SWT.NONE);
		GridData gd_btnNewButton = new GridData(SWT.CENTER, SWT.CENTER, false, false, 1, 1);
		gd_btnNewButton.widthHint = 80;
		btnNewButton.setLayoutData(gd_btnNewButton);
		btnNewButton.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				clickConn();
			}
		});
		btnNewButton.setText("连接设备");
		
		Label label_2 = new Label(shell, SWT.NONE);
		label_2.setText("第三步：");
		
		Button button_1 = new Button(shell, SWT.NONE);
		GridData gd_button_1 = new GridData(SWT.CENTER, SWT.CENTER, false, false, 1, 1);
		gd_button_1.widthHint = 80;
		button_1.setLayoutData(gd_button_1);
		button_1.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				clickCapture();
			}
		});
		button_1.setText("触发抓拍");
		
		Label label_3 = new Label(shell, SWT.NONE);
		label_3.setLayoutData(new GridData(SWT.RIGHT, SWT.CENTER, false, false, 1, 1));
		label_3.setText("抓拍车牌：");
		
		text_2 = new Text(shell, SWT.BORDER);
		GridData gd_text_2 = new GridData(SWT.LEFT, SWT.CENTER, false, false, 1, 1);
		gd_text_2.heightHint = 60;
		gd_text_2.widthHint = 100;
		text_2.setLayoutData(gd_text_2);
		
		lblNewLabel_1 = new Label(shell, SWT.NONE);
		lblNewLabel_1.setBackground(SWTResourceManager.getColor(SWT.COLOR_GRAY));
		GridData gd_lblNewLabel_1 = new GridData(SWT.LEFT, SWT.FILL, false, false, 1, 1);
		gd_lblNewLabel_1.widthHint = 150;
		gd_lblNewLabel_1.heightHint = 60;
		lblNewLabel_1.setLayoutData(gd_lblNewLabel_1);
		
		text_1 = new Text(shell, SWT.BORDER | SWT.WRAP | SWT.V_SCROLL | SWT.MULTI);
		text_1.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 3, 1));
	}

	protected void clickCapture() {
		String ip = text.getText().trim();
		int lpr_Capture = ZhitongLibrary.INSTANCE.LPR_Capture(pHandle.getValue());
		text_1.append("手动触发设备"+ip+"返回结果:"+lpr_Capture+"\n");
	}

	protected void clickConn() {
		String ip = text.getText().trim();
		pHandle = new PointerByReference();
		ByteBuffer sendBuffer = ByteBuffer.wrap(ip.getBytes());
		int lpr_ConnectCamera = ZhitongLibrary.INSTANCE.LPR_ConnectCamera(sendBuffer,pHandle);
		text_1.append("连接设备"+ip+"返回结果:"+lpr_ConnectCamera+"\n");
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
				final String ip = new String(pData.ucDeviceIP).trim();
				final String ucPlate = new String(pData.ucPlate).trim();
				long id = System.currentTimeMillis();
				final Path pathFrom_big = Paths.get(ip, id+"-big.jpg");  
				try {
					byte[] byteArray = pData.pucBigImage.getByteArray(0, pData.uiBigImageLen);
					System.out.println(Arrays.toString(byteArray));
					Files.write(pathFrom_big, byteArray, StandardOpenOption.CREATE);
				} catch (IOException e) {
					e.printStackTrace();
				}
				
				final Path pathFrom_cifi = Paths.get(ip, id+"-cifi.jpg");  
				try {
					byte[] byteArray = pData.pucCIFImage.getByteArray(0, pData.uiCIFImageLen);
					System.out.println(Arrays.toString(byteArray));
					Files.write(pathFrom_cifi, byteArray, StandardOpenOption.CREATE);
				} catch (IOException e) {
					e.printStackTrace();
				}
				
				final Path pathFrom_plate = Paths.get(ip, id+"-plate.jpg");  
				try {
					byte[] byteArray = pData.pucPlateImage.getByteArray(0, pData.uiPlateImageLen);
					System.out.println(Arrays.toString(byteArray));
					Files.write(pathFrom_plate, byteArray, StandardOpenOption.CREATE);
				} catch (IOException e) {
					e.printStackTrace();
				}
				
				shell.getDisplay().asyncExec(new Runnable() {
					public void run(){
						text_1.append(String.format("己有车牌信息回调 ip:%s",ip));
						text_1.append("\n");
						text_1.append(String.format("己有车牌信息回调 车牌:%s", ucPlate));
						text_1.append("\n");
						text_2.setText(ucPlate);
						
						//第次必须进行资源释放
						if(lblNewLabel.getImage() != null && !lblNewLabel.getImage().isDisposed()){
							lblNewLabel.getImage().dispose();
						}
						if(lblNewLabel_1.getImage() != null && !lblNewLabel_1.getImage().isDisposed()){
							lblNewLabel_1.getImage().dispose();
						}
						lblNewLabel.setImage(null);
						lblNewLabel_1.setImage(null);
						
						if(pData.uiBigImageLen != 0){
							
							Image image = new Image(shell.getDisplay(), pathFrom_big.toFile().getAbsolutePath());
							ImageData scaledTo = image.getImageData().scaledTo(pData.usBigImageWidth, pData.usBigImageHeight);
							Image image2 = new Image(shell.getDisplay(), scaledTo);
							lblNewLabel.setImage(image2);
							image.dispose();
						}
							
						if(pData.uiPlateImageLen != 0){
							Image image = new Image(shell.getDisplay(), pathFrom_plate.toFile().getAbsolutePath());
							ImageData scaledTo = image.getImageData().scaledTo(pData.usPlateImageWidth, pData.usPlateImageHeight);
							Image image2 = new Image(shell.getDisplay(), scaledTo);
							lblNewLabel_1.setImage(image2);
							image.dispose();
						}
					}
				});
				
			}
		};
		Memory m = new Memory(102400);
		Pointer share = m.share(0);
		ZhitongLibrary.INSTANCE.LPR_IsWriteLog((byte)1);
		int lpr_Init2 = ZhitongLibrary.INSTANCE.LPR_Init(null, share, deviceInfoCallback, deviceStatusCallback, dataCallback, jpgStreamCallBack);
		text_1.append("初始化返回结果:"+lpr_Init2+"\n");
	}
}
