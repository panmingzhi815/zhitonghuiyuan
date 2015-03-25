unit MainUnit;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, ComCtrls, Jpeg, CommCtrl;


// 网络参数
type
     PNetParams = ^NetParams;
     NetParams = record
        ucDeviceIP :array[0..15] of Byte;
        ucMaskIP :array[0..15] of Byte;
        ucGateIP :array[0..15] of Byte;
        ucMac :array[0..5] of Byte;
end;

// 设备信息
type
    PDevInfo = ^DeviceInfo;         // 定义结构体指针
    DeviceInfo = record
        DeviceNetInfo :NetParams;
        ucMAC :array[0..5] of Byte;
        ucDeviceVersion :array[0..254] of Byte;
        ucConnectNum :Byte;
end;

// 已连接设备
type
    PMaintainInfo = ^MaintainInfo;         // 定义结构体指针
    MaintainInfo = record
        hHandle :Pointer;
        ucIP :array[0..15]of Byte;
end;

type USER_TYPE = (NORMAL_USER, UNKNOWN_USER);
type DEVICE_TRIGGERMODE = (UNKNOWN_TRIGGER_MODE, VIDEO_TRIGGER_MODE, LINE_TRIGGER_MODE, SOFT_TRIGGER_MODE);
type PLATE_COLOR = (NON_PLATE, BLUE_COLOR, WHITE_COLOR, BLACK_COLOR, YELLOW_COLOR);


// 抓拍数据
type
    PVehicleData = ^VehicleData;
    VehicleData = record
        pDeviceHandle :Pointer;                     // 设备句柄
        usSerialNO :Word;                           // 序列号
        ucDeviceIP :array[0..15] of Byte;           // 设备IP
	    ui32DeviceID :Cardinal;				        // 设备ID
        ui32UserType :Cardinal;			            // 表示用户类型:0 正常用户，1 未授权用户，其他值保留
        ui32Brightness :Cardinal;			        // 亮度值
        triggermode :Cardinal;	                    // 触发类型:1 视频 2 线圈 3 模拟 0 未知 ，其他值保留
        ai8UserDefineInfo :array[0..254] of Byte;	// 用户自定义信息
	    ucTime :array[0..7] of Byte;                // 时间，年（减掉后的年份）、月、日、时、分、秒、毫秒（占两个字节）
	    ucPlate :array[0..15] of Byte;              // 车牌号码
        PlateColor :Cardinal;                       // 车牌颜色
	    pucBigImage :PChar;                         // 抓拍大图数据
	    uiBigImageLen :Cardinal;                    // 抓拍大图数据长度
	    usBigImageWidth :Word;                      // 抓拍大图宽度
	    usBigImageHeight :Word;                     // 抓拍大图高度
	    pucCIFImage :PChar;                         // 抓拍CIF图数据
	    uiCIFImageLen :Cardinal;                    // 抓拍CIF图数据长度
	    usCIFImageWidth :Word;                      // 抓拍CIF图宽度
	    usCIFImageHeight :Word;                     // 抓拍CIF图高度
	    pucPlateImage :PChar;                       // 抓拍车牌图数据
	    uiPlateImageLen :Cardinal;                  // 抓拍车牌图数据长度
        usPlateImageWidth :Word;                    // 抓拍车牌图宽度
	    usPlateImageHeight :Word;                   // 抓拍车牌图高度
end;

// 设备状态
type DeviceStatus = (CONNECT_SUCCESS, CREATE_ERROR, CONNECT_ERROR, ABNORMALNET_ERROR, DEVICE_RESET);
PDeviceStatus = ^DeviceStatus;

// 版本信息
type
    PVersionInfo = ^VersionInfo;
    VersionInfo = record
        ucMainVer :array[0..254] of Byte;
        ucDSPVer :array[0..254] of Byte;
        ucMCUVer :array[0..254] of Byte;
        ucOCRVer :array[0..254] of Byte;
        ucEPROMVer :array[0..254] of Byte;
end;




     // 动态库接口声明
     // function有返回值，procedure无返回值
Type
    LPR_Init = function(hWnd :THandle; pUserData :Pointer; fucDeviceInfo :PDevInfo; fucStatus:Pointer; fucVehicleData :PVehicleData; fucJPGStream :Pointer):Cardinal;stdcall;
    LPR_Quit = function():Cardinal;stdcall;
    LPR_ScanDevice = function():Cardinal;stdcall;
    LPR_ConnectCamera = function(pchDeviceIP :pchar; pHandle :Pointer):Cardinal;stdcall;
    LPR_DisconnectCamera = function(pHandle :Pointer):Cardinal;stdcall;
    LPR_Capture = function(pHandle :Pointer):Cardinal;stdcall;
    LPR_CaptureEx = function(pHandle :Pointer; nTimeout :Cardinal):Cardinal;stdcall;
    LPR_IsWriteLog = function(bWriteLog :Boolean):Cardinal;stdcall;
    LPR_CheckStatus = function(pHandle :Pointer; pConnStatus :PDeviceStatus):Cardinal;stdcall;
    LPR_AdjustTime = function(pHandle :Pointer; dwTimeMs :Int64):Cardinal;stdcall;
    LPR_NTPEnable = function(pHandle :Pointer; bNTP :Boolean; pchNTPSeverIP :pchar):Cardinal;stdcall;
    LPR_GetAllVersion = function(pHandle :Pointer; pVerInfo :PVersionInfo):Cardinal;stdcall;
    LPR_SetNetParams = function(pHandle :Pointer; OldParams :PNetParams; NewParams :PNetParams):Cardinal;stdcall;

type
    TForm1 = class(TForm)
    GroupBox3: TGroupBox;
    ImagePlate: TImage;
    GroupBox2: TGroupBox;
    ImageBig: TImage;
    GroupBox1: TGroupBox;
    ImageCif: TImage;
    GroupBox4: TGroupBox;
    GroupBox5: TGroupBox;
    ListViewDevList: TListView;
    GroupBox6: TGroupBox;
    ButtonInitSDK: TButton;
    ButtonQuitSDK: TButton;
    ButtonScanDev: TButton;
    ButtonConnectDev: TButton;
    ButtonDisConnectDev: TButton;
    TreeViewConnectedDev: TTreeView;
    ButtonTrigger: TButton;
    ButtonBlockTrigger: TButton;
    PlateNo: TPanel;
    chkWriteLog: TCheckBox;
    edtStatusInfo: TEdit;
    btnCheckStatus: TButton;
    btnAdjustTime: TButton;
    chkEnableNTP: TCheckBox;
    edtDSPMain: TEdit;
    btnGetVersionInfo: TButton;
    edtIP: TEdit;
    edtMask: TEdit;
    edtGate: TEdit;
    btnSetup: TButton;
    lblIP: TLabel;
    lblMask: TLabel;
    lblGate: TLabel;
    edtNTPIP: TEdit;
    Label1: TLabel;



    procedure FormCreate(Sender: TObject);
    procedure ButtonInitSDKClick(Sender: TObject);
    procedure ButtonQuitSDKClick(Sender: TObject);
    procedure ButtonScanDevClick(Sender: TObject);
    procedure ButtonConnectDevClick(Sender: TObject);
    procedure ButtonDisConnectDevClick(Sender: TObject);
    procedure ButtonTriggerClick(Sender: TObject);
    procedure ButtonBlockTriggerClick(Sender: TObject);
    procedure chkWriteLogClick(Sender: TObject);
    procedure btnCheckStatusClick(Sender: TObject);
    procedure btnAdjustTimeClick(Sender: TObject);
    procedure chkEnableNTPClick(Sender: TObject);
    procedure btnGetVersionInfoClick(Sender: TObject);
    procedure TreeViewConnectedDevClick(Sender: TObject);
    procedure btnSetupClick(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }

    // 创建目录
    function CreateDirectoryRecurrent(path:String):boolean;
    // 显示车牌号码
    procedure ShowPlate(strPlate:String; nColor:integer);

  end;


var
  Form1 :TForm1;

  strImagePath :string;
  hHandle :THandle;
  devList :TList;


   // 大图
  iBigImageLen :Cardinal;
  byteBigImage :array[0..102399] of Byte;
  // CIF图
  iCifImageLen :Cardinal;
  byteCifImage :array[0..102399] of Byte;
  // 车牌图
  iPlateImageLen :integer;
  bytePlateImage :array[0..5119] of Byte;
  // 车牌
  cPlate :array[0..63] of char;
  
  Init :LPR_Init;
  Quit :LPR_Quit;
  ScanDev :LPR_ScanDevice;
  ConnectCamera :LPR_ConnectCamera;
  DisconnectCamera :LPR_DisconnectCamera;
  Capture :LPR_Capture;
  CaptureEx :LPR_CaptureEx;
  WriteLog :LPR_IsWriteLog;
  CheckStatus :LPR_CheckStatus;
  AdjustTime :LPR_AdjustTime;
  NTPEnable :LPR_NTPEnable;
  GetAllVersion :LPR_GetAllVersion;
  SetNetParams :LPR_SetNetParams;

implementation
        
{$R *.dfm}

procedure TForm1.FormCreate(Sender: TObject);
begin
    // 装载动态库
    hHandle := LoadLibrary('LPRSDK.dll');
    @Init := nil;
    @Quit := nil;
    @ScanDev := nil;
    @ConnectCamera := nil;
    @Capture := nil;
    @CaptureEx := nil;
    @DisconnectCamera := nil;
    @WriteLog := nil;
    @CheckStatus := nil;
    @AdjustTime := nil;
    @NTPEnable := nil;
    @GetAllVersion :=nil;
    @SetNetParams :=nil;

    if(hHandle<>0) then begin
        @Init := GetProcAddress(hHandle, 'LPR_Init');
        @Quit := GetProcAddress(hHandle, 'LPR_Quit');
        @ScanDev := GetProcAddress(hHandle, 'LPR_ScanDevice');
        @ConnectCamera := GetProcAddress(hHandle, 'LPR_ConnectCamera');
        @Capture := GetProcAddress(hHandle, 'LPR_Capture');
        @CaptureEx := GetProcAddress(hHandle, 'LPR_CaptureEx');
        @DisconnectCamera := GetProcAddress(hHandle, 'LPR_DisconnectCamera');
        @WriteLog := GetProcAddress(hHandle, 'LPR_IsWriteLog');
        @CheckStatus := GetProcAddress(hHandle, 'LPR_CheckStatus');
        @AdjustTime := GetProcAddress(hHandle, 'LPR_AdjustTime');
        @NTPEnable := GetProcAddress(hHandle, 'LPR_NTPEnable');
        @GetAllVersion := GetProcAddress(hHandle, 'LPR_GetAllVersion');
        @SetNetParams := GetProcAddress(hHandle, 'LPR_SetNetParams');

        if((@Init = nil) or (@ScanDev = nil)) or (@Quit = nil) or (@ConnectCamera = nil) or(@Capture = nil) or (@CaptureEx = nil)
        or (@DisconnectCamera = nil) or (@WriteLog = nil) or (@CheckStatus = nil) or (@AdjustTime = nil) or (@NTPEnable = nil)
        or (@GetAllVersion = nil) or (@SetNetParams = nil) then
        begin
            ShowMessage('获取接口函数失败');
            Application.Terminate();
        end
        end
    else
    begin
        ShowMessage('装载动态库成功');
        Application.Terminate();
     end;

    // 初始化设备列表
    ListViewDevList.Clear;
    ListViewDevList.Columns.Add;
    ListViewDevList.Columns.Add;
    ListViewDevList.Columns.Add;
    ListViewDevList.Columns.Add;
    ListViewDevList.Columns.Items[0].Caption:='设备IP';
    ListViewDevList.Columns.Items[0].Width:=100;
    ListViewDevList.Columns.Items[1].Caption:='子网掩码';
    ListViewDevList.Columns.Items[1].Width:=100;
    ListViewDevList.Columns.Items[2].Caption:='默认网关';
    ListViewDevList.Columns.Items[2].Width:=200;
    ListViewDevList.Columns.Items[3].Caption:='MAC地址';
    ListViewDevList.Columns.Items[3].Width:=200;
    ListViewDevList.ViewStyle := vsreport;
    ListViewDevList.GridLines := true;

    SetWindowLong(TreeViewConnectedDev.Handle, GWL_STYLE, GetWindowLong(TreeViewConnectedDev.Handle, GWL_STYLE) or $00000100);

    devList := TList.Create;
    strImagePath := ExtractFilePath(Application.ExeName);
end;

procedure TForm1.ShowPlate(strPlate:String; nColor:integer);
begin
    PlateNo.Caption := strPlate;

    case nColor of
        0:          // 未知
        begin
            PlateNo.Color := clBtnFace;
            PlateNo.Font.Color := clBlack;
        end;
        1:          // 蓝色
        begin
            PlateNo.Color := clBlue;
            PlateNo.Font.Color := clWhite;
         end;
        2:          // 白色
        begin
            PlateNo.Color := clWhite;
            PlateNo.Font.Color := clBlack;
        end;
        3:          // 黑色
        begin
                PlateNo.Color := clBlack;
                PlateNo.Font.Color := clWhite;
        end;
        4:          // 黄色
        begin
            PlateNo.Color := clYellow;
            PlateNo.Font.Color := clBlack;
        end;
        else        // 未知
            PlateNo.Color := clBtnFace;
            PlateNo.Font.Color := clBlack;
        end;
end;

// 创建目录
function TForm1.CreateDirectoryRecurrent(path:String):boolean;
var
  i : Integer;
  s : String;
begin
	if not DirectoryExists(path) then
	begin
		for i := 1 to Length(path) do
		begin
      if path[i] = '\' then
      begin
        s := Copy(path, 1, i);
			  if not DirectoryExists(path) then
  			begin
          s := Copy(path, 1, i);
		  		Result := CreateDirectory(PChar(s), nil);
  			end;
      end;  
		end;
	end;
	Result := True;
end;



// 设备状态回调函数
procedure DeviceStatusCallback(pUserData:Pointer; pStatus:Pointer);stdcall;
begin

end;

// 设备信息回调函数，说明：var pDeviceInfo :DeviceInfo定义为指针参数
procedure DeviceInfoCallback(pUserData:Pointer; pDeviceInfo :PDevInfo);stdcall;
var
    strIP :String;
    strMask :String;
    strGate :String;
    strMAC :string;
    i: integer;
    nCount: integer;
begin
    strIP := StrPas(@pDeviceInfo^.DeviceNetInfo.ucDeviceIP[0]);
    strMask := StrPas(@pDeviceInfo^.DeviceNetInfo.ucMaskIP[0]);
    strGate := StrPas(@pDeviceInfo^.DeviceNetInfo.ucGateIP[0]);
    strMAC := Format('%.2x-%.2x-%.2x-%.2x-%.2x-%.2x', [pDeviceInfo^.ucMac[0],
    pDeviceInfo^.ucMac[1],
    pDeviceInfo^.ucMac[2],
    pDeviceInfo^.ucMac[3],
    pDeviceInfo^.ucMac[4],
    pDeviceInfo^.ucMac[5]]);

    nCount :=  Form1.ListViewDevList.Items.Count - 1;
    for i := 0 to nCount do
    begin
        if(Form1.ListViewDevList.Items[i].Caption = strIP) then
        begin
            Form1.ListViewDevList.Items[i].Subitems.strings[0] := strMask;
            Form1.ListViewDevList.Items[i].Subitems.strings[1] := strGate;
            Form1.ListViewDevList.Items[i].Subitems.strings[2] := strMAC;
            Exit;
        end;
    end;

    with Form1.ListViewDevList.items.add do
    begin
        Caption := strIP;
        SubItems.Add(strMask);
        SubItems.Add(strGate);
        SubItems.Add(strMAC);
    end;
end;

// 抓拍数据回调函数
procedure VehicleDataCallback(pUserData:Pointer; pData:PVehicleData);stdcall;
var
    dt :TDateTime;
    sPath :String;
    strInfo :String;
    strIP :String;
    i :Cardinal;
    pCamHandle :Pointer;
    bFlag :BOOL;
    strBigFile, strCifFile, strPlateFile, strPlateNoFile :String;
    fl :file;
    nRes :Cardinal;
    strPlate :String;
    nColor :integer;
    nValue :Cardinal;
    pDev :PMaintainInfo;
begin
    zeromemory(@byteBigImage[0],102400);
    zeromemory(@byteCifImage[0],102400);
    zeromemory(@bytePlateImage[0],5120);
    zeromemory(@cPlate[0], 64);


    // 查找设备IP
    if Form1.TreeViewConnectedDev.Selected = nil then Exit;

    for i := 0 to devList.count - 1 do
    begin
        pDev := devList.Items[i];
        strInfo := StrPas(@pDev^.ucIP);
        if(Form1.TreeViewConnectedDev.Selected.Text = strInfo) then
        begin
            pCamHandle := pDev^.hHandle;
            if(pData^.pDeviceHandle = pCamHandle) then
            begin
                bFlag := True;
                strIP := strInfo;
                break;
            end;
        end;
    end;

    if(bFlag <> True) then Exit;

    strPlate := StrPas(@pData^.ucPlate[0]);
    nColor := pData^.PlateColor;
    dt := now();

    // 大图
    sPath := strImagePath + strIP +'\大图\' + FormatDateTime('yyyymmdd', dt) + '\';
    Form1.CreateDirectoryRecurrent(sPath);
    strBigFile := Format('%s%s(%s).jpg', [sPath, FormatDateTime('hhmmss', dt), strPlate]);
    if((pData^.pucBigImage <> nil) and (pData^.uiBigImageLen > 0)) then
    begin
        copymemory(@byteBigImage, pData^.pucBigImage, pData^.uiBigImageLen);
        AssignFile(fl, strBigFile);
        Rewrite(fl, 1);
        BlockWrite(fl, byteBigImage , pData^.uiBigImageLen, nRes);
        CloseFile(fl);

        // 界面显示
        if FileExists(strBigFile) then
        begin
            Form1.ImageBig.Picture.LoadFromFile(strBigFile);
        end;
    end;

    // CIF图
    sPath := strImagePath + strIP +'\CIF图\' + FormatDateTime('yyyymmdd', dt) + '\';
    Form1.CreateDirectoryRecurrent(sPath);
    strCifFile := Format('%s%s(%s).jpg', [sPath, FormatDateTime('hhmmss',dt), strPlate]);
    if((pData^.pucCIFImage <> nil) and (pData^.uiCIFImageLen > 0)) then
    begin
        copymemory(@byteCifImage, pData^.pucCIFImage, pData^.uiCIFImageLen);
        AssignFile(fl, strCifFile);
        Rewrite(fl, 1);
        BlockWrite(fl, byteCifImage , pData^.uiCIFImageLen, nRes);
        CloseFile(fl);

        // 界面显示
        if FileExists(strCifFile) then
        begin
            Form1.ImageCif.Picture.LoadFromFile(strCifFile);
        end;
    end;

    // 车牌图
    sPath := strImagePath + strIP +'\车牌图\' + FormatDateTime('yyyymmdd', dt) + '\';
    Form1.CreateDirectoryRecurrent(sPath);
    strPlateFile := Format('%s%s(%s).jpg', [sPath, FormatDateTime('hhmmss',dt), strPlate]);
    if((pData^.pucPlateImage <> nil) and (pData^.uiPlateImageLen > 0)) then
    begin
        copymemory(@bytePlateImage, pData^.pucPlateImage, pData^.uiPlateImageLen);
        AssignFile(fl, strPlateFile);
        Rewrite(fl, 1);
        BlockWrite(fl, bytePlateImage , pData^.uiPlateImageLen, nRes);
        CloseFile(fl);

        // 界面显示
        if FileExists(strPlateFile) then
        begin
            Form1.ImagePlate.Picture.LoadFromFile(strPlateFile);
        end;
    end;

    // 车牌号码显示
    Form1.ShowPlate(strPlate, nColor);
end;

// 实时视频回调函数
procedure JPGStreamCallBack(pUserData:Pointer; pJPGData:Pointer);stdcall;
begin

end;




// 1、初始化SDK
procedure TForm1.ButtonInitSDKClick(Sender: TObject);
var
    myhandle:Cardinal;
    nRes:Cardinal;
    strInfo:String;
begin
    myhandle:=0;
    nRes := Init(myhandle, NIl, @DeviceInfoCallback,  @DeviceStatusCallback,  @VehicleDataCallback,  @JPGStreamCallBack);
    strInfo := inttostr(nRes);
    if nRes <> 0 then ShowMessage('返回值 = ' + strInfo)
    else ShowMessage('初始化成功');
end;

// 2、退出SDK
procedure TForm1.ButtonQuitSDKClick(Sender: TObject);
var
    nRes:Cardinal;
    strInfo:String;
    i :Cardinal;
    pDev :PMaintainInfo;
begin
    // 清空
    TreeViewConnectedDev.Items.Clear;

    if(devList.count <> 0) then
    begin
        for i := 0 to devList.count - 1 do
        begin
            pDev := devList.Items[i];
            if(pDev <> nil) then
            begin
                if(pDev^.hHandle <> nil) then
                begin
                    DisconnectCamera(pDev^.hHandle);
                end;
                Dispose(pDev);
                pDev := nil;
            end;
        end;
        //devList.Free;
    end;


    nRes := Quit();
    strInfo := inttostr(nRes);
    if nRes <> 0 then ShowMessage('返回值 = ' + strInfo)
    else ShowMessage('退出成功');
end;

// 3、扫描设备
procedure TForm1.ButtonScanDevClick(Sender: TObject);
var
    nRes:Cardinal;
    strInfo:string;
begin
    ListViewDevList.Clear;
    nRes := ScanDev();
    if(nRes <> 0) then
    begin
        strInfo := inttostr(nRes);
        ShowMessage('返回值 = ' + strInfo);
    end;
end;

// 4、连接设备
procedure TForm1.ButtonConnectDevClick(Sender: TObject);
var
    strInfo :String;
    strValue :String;
    pCamHandle :Pointer;
    nRes :Cardinal;
    i :Cardinal;
    pDev :PMaintainInfo;
begin
    pDev := nil;
    
    // 获取当前选中项IP地址
    if(ListViewDevList.SelCount > 0) then
    begin
        strInfo := ListViewDevList.Selected.Caption;
        nRes := ConnectCamera(Pchar(strInfo), @pCamHandle);
        if(nRes <> 0) then
        begin
            strValue := inttostr(nRes);
            ShowMessage('返回值 = ' + strValue);
            Exit;
        end
        else
        begin
            New(pDev);
            pDev^.hHandle := pCamHandle;
            StrCopy(@pDev^.ucIP, PChar(strInfo));
            devList.Add(pDev);
        end;

        TreeViewConnectedDev.Items.Add(nil, strInfo);
    end;
end;

// 5、断开设备
procedure TForm1.ButtonDisConnectDevClick(Sender: TObject);
var
    nNodes :Cardinal;
    strIP :String;
    strListIP :String;
    i :Integer;
    j :Integer;
    nRes :Cardinal;
    strValue :String;
    pDev :PMaintainInfo;
begin
    // 获取当前选中项IP
    nNodes := TreeViewConnectedDev.SelectionCount;
    for i := 0 to nNodes - 1 do
    begin
          strIP := TreeViewConnectedDev.Selections[i].Text;

        for j := 0 to devList.count - 1 do
        begin
            pDev := devList.Items[j];
            strListIP := StrPas(@pDev^.ucIP);
            if(strIP = strListIP) then
            begin
                nRes := DisconnectCamera(pDev^.hHandle);
                if(nRes <> 0) then
                begin
                    strValue := inttostr(nRes);
                    ShowMessage('返回值 = ' + strValue);
                    Exit;
                end
                else
                begin
                    if pDev <> nil then
                        Dispose(pDev);
                    pDev := nil;
                    devList.Delete(j);
                    TreeViewConnectedDev.Items.Delete(TreeViewConnectedDev.Selections[i]);
                end;
            end;
        end;

    end;
end;

procedure TForm1.ButtonTriggerClick(Sender: TObject);
var
    nRes :Cardinal;
    strValue :String;
    i :Cardinal;
    strIP :String;
    TVI: TTVItem;
    pDev :PMaintainInfo;
begin
    if TreeViewConnectedDev.Selected = nil then Exit;
    TVI.mask := TVIF_STATE;
    TVI.hItem := TreeViewConnectedDev.Selected.ItemId;
    TreeView_GetItem(TreeViewConnectedDev.Handle, TVI);
    if TVI.state and $2000 <> $2000 then        // 复选框没有选中
    begin
        Exit;
    end;

    // 查找设备IP
    if Form1.TreeViewConnectedDev.Selected = nil then Exit;
    for i := 0 to devList.count - 1 do
    begin
        pDev := devList.Items[i];
        strIP := StrPas(@pDev^.ucIP);
        if(TreeViewConnectedDev.Selected.Text = strIP) then
        begin
            if pDev^.hHandle <> nil then
            begin
                nRes := Capture(pDev^.hHandle);
                if(nRes <> 0) then
                begin
                    strValue := inttostr(nRes);
                    ShowMessage('返回值 = ' + strValue);
                    Exit;
                end;
            end;
        end;
    end;
end;

procedure TForm1.ButtonBlockTriggerClick(Sender: TObject);
var
    nRes :Cardinal;
    strValue :String;
    i :Cardinal;
    strIP :String;
    TVI: TTVItem;
    pDev :PMaintainInfo;
begin
    if TreeViewConnectedDev.Selected = nil then Exit;

    TVI.mask := TVIF_STATE;
    TVI.hItem := TreeViewConnectedDev.Selected.ItemId;
    TreeView_GetItem(TreeViewConnectedDev.Handle, TVI);
    if TVI.state and $2000 <> $2000 then
    begin
        Exit;
    end;

    for i := 0 to devList.count - 1 do
    begin
          pDev := devList.Items[i];

        strIP := StrPas(@pDev^.ucIP);
        if(TreeViewConnectedDev.Selected.Text = strIP) then
        begin
            if pDev^.hHandle <> nil then
            begin
                nRes := CaptureEx(pDev^.hHandle, 200);
                if(nRes <> 0) then
                begin
                    strValue := inttostr(nRes);
                    ShowMessage('返回值 = ' + strValue);
                    Exit;
                end;
            end;
        end;
    end;
end;

procedure TForm1.chkWriteLogClick(Sender: TObject);
begin
    if(chkWriteLog.Checked) then
        WriteLog(True)
    else
        WriteLog(False);
end;

procedure TForm1.btnCheckStatusClick(Sender: TObject);
var
    pCamHandle :Pointer;
    nRes :Cardinal;
    strValue :String;
    i :Cardinal;
    strIP :String;
    devStatus :DeviceStatus;
    strInfo :String;
    nStatus :Integer;
    TVI: TTVItem;
    pDev :PMaintainInfo;
begin
    if TreeViewConnectedDev.Selected = nil then Exit;

    TVI.mask := TVIF_STATE;
    TVI.hItem := TreeViewConnectedDev.Selected.ItemId;
    TreeView_GetItem(TreeViewConnectedDev.Handle, TVI);

    if TVI.state and $2000 <> $2000 then
    begin
        edtStatusInfo.Text := '请在设备IP前打上对勾';
        Exit;
    end;

    for i := 0 to devList.count - 1 do
    begin
        pDev := devList.Items[i];
        strIP := StrPas(@pDev^.ucIP);
        if(TreeViewConnectedDev.Selected.Text = strIP) then
        begin
            pCamHandle := pDev^.hHandle;
            nRes := CheckStatus(pCamHandle, @devStatus);
            if(nRes <> 0) then
            begin
               strValue := inttostr(nRes);
                ShowMessage('返回值 = ' + strValue);
                Exit;
            end
            else
            begin
               if(devStatus = CONNECT_SUCCESS) then strInfo := '连接成功'
               else if(devStatus = CREATE_ERROR) then strInfo := '生成句柄错误'
               else if(devStatus = CONNECT_ERROR) then strInfo := '连接错误'
               else if(devStatus = ABNORMALNET_ERROR) then strInfo := '网络异常错误'
               else if(devStatus = DEVICE_RESET) then strInfo := '设备复位';

               edtStatusInfo.Text := strInfo;
            end;
        end;
    end;
end;

procedure TForm1.btnAdjustTimeClick(Sender: TObject);
var
    pCamHandle :Pointer;
    nRes :Cardinal;
    strValue :String;
    i :Cardinal;
    strIP :String;
    devStatus :DeviceStatus;
    strInfo :String;
    nStatus :Integer;
    TVI: TTVItem;
    pDev :PMaintainInfo;
begin
    if TreeViewConnectedDev.Selected = nil then Exit;

    TVI.mask := TVIF_STATE;
    TVI.hItem := TreeViewConnectedDev.Selected.ItemId;
    TreeView_GetItem(TreeViewConnectedDev.Handle, TVI);

    if TVI.state and $2000 <> $2000 then
    begin
        edtStatusInfo.Text := '请在设备IP前打上对勾';
        Exit;
    end;

    for i := 0 to devList.count - 1 do
    begin
        pDev := devList.Items[i];
        strIP := StrPas(@pDev^.ucIP);
        if(TreeViewConnectedDev.Selected.Text = strIP) then
        begin
            pCamHandle := pDev^.hHandle;
            nRes := AdjustTime(pCamHandle, 0);
            if(nRes <> 0) then
            begin
               strValue := inttostr(nRes);
               ShowMessage('返回值 = ' + strValue);
               Exit;
            end
            else  ShowMessage('校时成功');
        end;
    end;
end;

procedure TForm1.chkEnableNTPClick(Sender: TObject);
var
    pCamHandle :Pointer;
    nRes :Cardinal;
    strValue :String;
    i :Cardinal;
    strIP :String;
    devStatus :DeviceStatus;
    strInfo :String;
    nStatus :Integer;
    TVI: TTVItem;
    bEnable :Boolean;
    pDev :PMaintainInfo;

begin
    if TreeViewConnectedDev.Selected = nil then Exit;

    if edtNTPIP.Text = '' then
    begin
        ShowMessage('NTP服务器IP错误');
        Exit;
    end;

    TVI.mask := TVIF_STATE;
    TVI.hItem := TreeViewConnectedDev.Selected.ItemId;
    TreeView_GetItem(TreeViewConnectedDev.Handle, TVI);

    if TVI.state and $2000 <> $2000 then
    begin
        edtStatusInfo.Text := '请在设备IP前打上对勾';
        Exit;
    end;

    if(chkEnableNTP.Checked) then
        bEnable := True
    else
        bEnable := False;

    for i := 0 to devList.count - 1 do
    begin
        pDev := devList.Items[i];
        strIP := StrPas(@pDev^.ucIP);
        if(TreeViewConnectedDev.Selected.Text = strIP) then
        begin
            pCamHandle := pDev^.hHandle;
            nRes := NTPEnable(pCamHandle, bEnable, PChar(edtNTPIP.Text));
            if(nRes <> 0) then
            begin
               strValue := inttostr(nRes);
                ShowMessage('返回值 = ' + strValue);
                Exit;
            end
            else  ShowMessage('设置NTP校时是否启用成功');
        end;
    end;
end;

procedure TForm1.btnGetVersionInfoClick(Sender: TObject);
var
    pCamHandle :Pointer;
    nRes :Cardinal;
    strValue :String;
    i :Cardinal;
    strIP :String;
    verInfo :VersionInfo;
    strInfo :String;
    nStatus :Integer;
    TVI: TTVItem;
    pDev :PMaintainInfo;
begin
    if TreeViewConnectedDev.Selected = nil then Exit;

    TVI.mask := TVIF_STATE;
    TVI.hItem := TreeViewConnectedDev.Selected.ItemId;
    TreeView_GetItem(TreeViewConnectedDev.Handle, TVI);

    if TVI.state and $2000 <> $2000 then
    begin
        edtStatusInfo.Text := '请在设备IP前打上对勾';
        Exit;
    end;

    for i := 0 to devList.count - 1 do
    begin
        pDev := devList.Items[i];
        strIP := StrPas(@pDev^.ucIP);
        if(TreeViewConnectedDev.Selected.Text = strIP) then
        begin
            pCamHandle := pDev^.hHandle;
            nRes := GetAllVersion(pCamHandle, @verInfo);
            if(nRes <> 0) then
            begin
               strValue := inttostr(nRes);
                ShowMessage('返回值 = ' + strValue);
                Exit;
            end
            else
            begin
               strInfo := 'DSP主版本(' + StrPas(@verInfo.ucMainVer[0]) + ')' +
               'DSP子版本(' + StrPas(@verInfo.ucDSPVer[0]) + ')' +
               '单片机版本(' + StrPas(@verInfo.ucMCUVer[0]) + ')' +
               '识别库版本(' + StrPas(@verInfo.ucOCRVer[0]) + ')' +
               'EEPROM版本(' + StrPas(@verInfo.ucEPROMVer[0]) + ')';

               edtDSPMain.Text := strInfo;
            end;
        end;
    end;
end;

procedure TForm1.TreeViewConnectedDevClick(Sender: TObject);
var
    pCamHandle :Pointer;
    nRes :Cardinal;
    strValue :String;
    i :Cardinal;
    j :Cardinal;
    strIP :String;
    verInfo :VersionInfo;
    strInfo :String;
    nStatus :Integer;
    TVI: TTVItem;
    nCount :Integer;
begin
    if TreeViewConnectedDev.Selected = nil then Exit;

    TVI.mask := TVIF_STATE;
    TVI.hItem := TreeViewConnectedDev.Selected.ItemId;
    TreeView_GetItem(TreeViewConnectedDev.Handle, TVI);

    if TVI.state and $2000 <> $2000 then
    begin
        edtIP.Text := '';
        edtMask.Text := '';
        edtGate.Text := '';
        //edtMAC.Text := '';
        Exit;
    end;

   nCount :=  ListViewDevList.Items.Count - 1;
    for i := 0 to nCount do
    begin
        if(ListViewDevList.Items[i].Caption = TreeViewConnectedDev.Selected.Text) then
        begin
            edtIP.Text := ListViewDevList.Items[i].Caption;
            edtMask.Text := ListViewDevList.Items[i].Subitems.strings[0];
            edtGate.Text := ListViewDevList.Items[i].Subitems.strings[1];
            //edtMAC.Text := ListViewDevList.Items[i].Subitems.strings[2];

            Exit;
        end;
    end;
end;

procedure TForm1.btnSetupClick(Sender: TObject);
var
    pCamHandle :Pointer;
    nRes :Cardinal;
    strValue :string;
    i, j :Cardinal;
    strTempIP :String;
    verInfo :VersionInfo;
    strIP, strMask, strGate, strMAC :string;
    oldParams, newParams :NetParams;
    strInfo :string;
    pDev :PMaintainInfo;
begin
    strIP := edtIP.Text;
    strMask := edtMask.Text;
    strGate := edtGate.Text;
    //strMAC := edtMAC.Text;

    FillChar(newParams.ucDeviceIP, SizeOf(newParams.ucDeviceIP), Ord(' '));
    Move(strIP[1], newParams.ucDeviceIP[0], SizeOf(newParams.ucDeviceIP));
    FillChar(newParams.ucMaskIP, SizeOf(newParams.ucMaskIP), Ord(' '));
    Move(strMask[1], newParams.ucMaskIP[0], SizeOf(newParams.ucMaskIP));
    FillChar(newParams.ucGateIP, SizeOf(newParams.ucGateIP), Ord(' '));
    Move(strGate[1], newParams.ucGateIP[0], SizeOf(newParams.ucGateIP));

    //Delete(strMAC, 3, 1);
    //Delete(strMAC, 5, 1);
    //Delete(strMAC, 7, 1);
    //Delete(strMAC, 9, 1);
    //Delete(strMAC, 11, 1);

    //FillChar(newParams.ucMac, SizeOf(newParams.ucMac), Ord(' '));
    //HexToBin(PChar(strMAC), @newParams.ucMac[0], 6);

    for i := 0 to devList.count - 1 do
    begin
        pDev := devList.Items[i];
        strTempIP := StrPas(@pDev^.ucIP);
        if(TreeViewConnectedDev.Selected.Text = strTempIP) then
        begin
            pCamHandle := pDev^.hHandle;
            nRes := SetNetParams(pCamHandle, @oldParams, @newParams);
            if(nRes <> 0) then
            begin
                strValue := inttostr(nRes);
                ShowMessage('返回值 = ' + strValue);
                Exit;
            end
            else ShowMessage('设置网络参数成功');
        end;
    end;
end;

// 释放动态库
procedure TForm1.FormDestroy(Sender: TObject);
begin
    if(hHandle<>0) then FreeLibrary(hHandle);
end;

end.
