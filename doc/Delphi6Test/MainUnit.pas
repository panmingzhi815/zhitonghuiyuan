unit MainUnit;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, ComCtrls, Jpeg, CommCtrl;


// �������
type
     PNetParams = ^NetParams;
     NetParams = record
        ucDeviceIP :array[0..15] of Byte;
        ucMaskIP :array[0..15] of Byte;
        ucGateIP :array[0..15] of Byte;
        ucMac :array[0..5] of Byte;
end;

// �豸��Ϣ
type
    PDevInfo = ^DeviceInfo;         // ����ṹ��ָ��
    DeviceInfo = record
        DeviceNetInfo :NetParams;
        ucMAC :array[0..5] of Byte;
        ucDeviceVersion :array[0..254] of Byte;
        ucConnectNum :Byte;
end;

// �������豸
type
    PMaintainInfo = ^MaintainInfo;         // ����ṹ��ָ��
    MaintainInfo = record
        hHandle :Pointer;
        ucIP :array[0..15]of Byte;
end;

type USER_TYPE = (NORMAL_USER, UNKNOWN_USER);
type DEVICE_TRIGGERMODE = (UNKNOWN_TRIGGER_MODE, VIDEO_TRIGGER_MODE, LINE_TRIGGER_MODE, SOFT_TRIGGER_MODE);
type PLATE_COLOR = (NON_PLATE, BLUE_COLOR, WHITE_COLOR, BLACK_COLOR, YELLOW_COLOR);


// ץ������
type
    PVehicleData = ^VehicleData;
    VehicleData = record
        pDeviceHandle :Pointer;                     // �豸���
        usSerialNO :Word;                           // ���к�
        ucDeviceIP :array[0..15] of Byte;           // �豸IP
	    ui32DeviceID :Cardinal;				        // �豸ID
        ui32UserType :Cardinal;			            // ��ʾ�û�����:0 �����û���1 δ��Ȩ�û�������ֵ����
        ui32Brightness :Cardinal;			        // ����ֵ
        triggermode :Cardinal;	                    // ��������:1 ��Ƶ 2 ��Ȧ 3 ģ�� 0 δ֪ ������ֵ����
        ai8UserDefineInfo :array[0..254] of Byte;	// �û��Զ�����Ϣ
	    ucTime :array[0..7] of Byte;                // ʱ�䣬�꣨���������ݣ����¡��ա�ʱ���֡��롢���루ռ�����ֽڣ�
	    ucPlate :array[0..15] of Byte;              // ���ƺ���
        PlateColor :Cardinal;                       // ������ɫ
	    pucBigImage :PChar;                         // ץ�Ĵ�ͼ����
	    uiBigImageLen :Cardinal;                    // ץ�Ĵ�ͼ���ݳ���
	    usBigImageWidth :Word;                      // ץ�Ĵ�ͼ���
	    usBigImageHeight :Word;                     // ץ�Ĵ�ͼ�߶�
	    pucCIFImage :PChar;                         // ץ��CIFͼ����
	    uiCIFImageLen :Cardinal;                    // ץ��CIFͼ���ݳ���
	    usCIFImageWidth :Word;                      // ץ��CIFͼ���
	    usCIFImageHeight :Word;                     // ץ��CIFͼ�߶�
	    pucPlateImage :PChar;                       // ץ�ĳ���ͼ����
	    uiPlateImageLen :Cardinal;                  // ץ�ĳ���ͼ���ݳ���
        usPlateImageWidth :Word;                    // ץ�ĳ���ͼ���
	    usPlateImageHeight :Word;                   // ץ�ĳ���ͼ�߶�
end;

// �豸״̬
type DeviceStatus = (CONNECT_SUCCESS, CREATE_ERROR, CONNECT_ERROR, ABNORMALNET_ERROR, DEVICE_RESET);
PDeviceStatus = ^DeviceStatus;

// �汾��Ϣ
type
    PVersionInfo = ^VersionInfo;
    VersionInfo = record
        ucMainVer :array[0..254] of Byte;
        ucDSPVer :array[0..254] of Byte;
        ucMCUVer :array[0..254] of Byte;
        ucOCRVer :array[0..254] of Byte;
        ucEPROMVer :array[0..254] of Byte;
end;




     // ��̬��ӿ�����
     // function�з���ֵ��procedure�޷���ֵ
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

    // ����Ŀ¼
    function CreateDirectoryRecurrent(path:String):boolean;
    // ��ʾ���ƺ���
    procedure ShowPlate(strPlate:String; nColor:integer);

  end;


var
  Form1 :TForm1;

  strImagePath :string;
  hHandle :THandle;
  devList :TList;


   // ��ͼ
  iBigImageLen :Cardinal;
  byteBigImage :array[0..102399] of Byte;
  // CIFͼ
  iCifImageLen :Cardinal;
  byteCifImage :array[0..102399] of Byte;
  // ����ͼ
  iPlateImageLen :integer;
  bytePlateImage :array[0..5119] of Byte;
  // ����
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
    // װ�ض�̬��
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
            ShowMessage('��ȡ�ӿں���ʧ��');
            Application.Terminate();
        end
        end
    else
    begin
        ShowMessage('װ�ض�̬��ɹ�');
        Application.Terminate();
     end;

    // ��ʼ���豸�б�
    ListViewDevList.Clear;
    ListViewDevList.Columns.Add;
    ListViewDevList.Columns.Add;
    ListViewDevList.Columns.Add;
    ListViewDevList.Columns.Add;
    ListViewDevList.Columns.Items[0].Caption:='�豸IP';
    ListViewDevList.Columns.Items[0].Width:=100;
    ListViewDevList.Columns.Items[1].Caption:='��������';
    ListViewDevList.Columns.Items[1].Width:=100;
    ListViewDevList.Columns.Items[2].Caption:='Ĭ������';
    ListViewDevList.Columns.Items[2].Width:=200;
    ListViewDevList.Columns.Items[3].Caption:='MAC��ַ';
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
        0:          // δ֪
        begin
            PlateNo.Color := clBtnFace;
            PlateNo.Font.Color := clBlack;
        end;
        1:          // ��ɫ
        begin
            PlateNo.Color := clBlue;
            PlateNo.Font.Color := clWhite;
         end;
        2:          // ��ɫ
        begin
            PlateNo.Color := clWhite;
            PlateNo.Font.Color := clBlack;
        end;
        3:          // ��ɫ
        begin
                PlateNo.Color := clBlack;
                PlateNo.Font.Color := clWhite;
        end;
        4:          // ��ɫ
        begin
            PlateNo.Color := clYellow;
            PlateNo.Font.Color := clBlack;
        end;
        else        // δ֪
            PlateNo.Color := clBtnFace;
            PlateNo.Font.Color := clBlack;
        end;
end;

// ����Ŀ¼
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



// �豸״̬�ص�����
procedure DeviceStatusCallback(pUserData:Pointer; pStatus:Pointer);stdcall;
begin

end;

// �豸��Ϣ�ص�������˵����var pDeviceInfo :DeviceInfo����Ϊָ�����
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

// ץ�����ݻص�����
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


    // �����豸IP
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

    // ��ͼ
    sPath := strImagePath + strIP +'\��ͼ\' + FormatDateTime('yyyymmdd', dt) + '\';
    Form1.CreateDirectoryRecurrent(sPath);
    strBigFile := Format('%s%s(%s).jpg', [sPath, FormatDateTime('hhmmss', dt), strPlate]);
    if((pData^.pucBigImage <> nil) and (pData^.uiBigImageLen > 0)) then
    begin
        copymemory(@byteBigImage, pData^.pucBigImage, pData^.uiBigImageLen);
        AssignFile(fl, strBigFile);
        Rewrite(fl, 1);
        BlockWrite(fl, byteBigImage , pData^.uiBigImageLen, nRes);
        CloseFile(fl);

        // ������ʾ
        if FileExists(strBigFile) then
        begin
            Form1.ImageBig.Picture.LoadFromFile(strBigFile);
        end;
    end;

    // CIFͼ
    sPath := strImagePath + strIP +'\CIFͼ\' + FormatDateTime('yyyymmdd', dt) + '\';
    Form1.CreateDirectoryRecurrent(sPath);
    strCifFile := Format('%s%s(%s).jpg', [sPath, FormatDateTime('hhmmss',dt), strPlate]);
    if((pData^.pucCIFImage <> nil) and (pData^.uiCIFImageLen > 0)) then
    begin
        copymemory(@byteCifImage, pData^.pucCIFImage, pData^.uiCIFImageLen);
        AssignFile(fl, strCifFile);
        Rewrite(fl, 1);
        BlockWrite(fl, byteCifImage , pData^.uiCIFImageLen, nRes);
        CloseFile(fl);

        // ������ʾ
        if FileExists(strCifFile) then
        begin
            Form1.ImageCif.Picture.LoadFromFile(strCifFile);
        end;
    end;

    // ����ͼ
    sPath := strImagePath + strIP +'\����ͼ\' + FormatDateTime('yyyymmdd', dt) + '\';
    Form1.CreateDirectoryRecurrent(sPath);
    strPlateFile := Format('%s%s(%s).jpg', [sPath, FormatDateTime('hhmmss',dt), strPlate]);
    if((pData^.pucPlateImage <> nil) and (pData^.uiPlateImageLen > 0)) then
    begin
        copymemory(@bytePlateImage, pData^.pucPlateImage, pData^.uiPlateImageLen);
        AssignFile(fl, strPlateFile);
        Rewrite(fl, 1);
        BlockWrite(fl, bytePlateImage , pData^.uiPlateImageLen, nRes);
        CloseFile(fl);

        // ������ʾ
        if FileExists(strPlateFile) then
        begin
            Form1.ImagePlate.Picture.LoadFromFile(strPlateFile);
        end;
    end;

    // ���ƺ�����ʾ
    Form1.ShowPlate(strPlate, nColor);
end;

// ʵʱ��Ƶ�ص�����
procedure JPGStreamCallBack(pUserData:Pointer; pJPGData:Pointer);stdcall;
begin

end;




// 1����ʼ��SDK
procedure TForm1.ButtonInitSDKClick(Sender: TObject);
var
    myhandle:Cardinal;
    nRes:Cardinal;
    strInfo:String;
begin
    myhandle:=0;
    nRes := Init(myhandle, NIl, @DeviceInfoCallback,  @DeviceStatusCallback,  @VehicleDataCallback,  @JPGStreamCallBack);
    strInfo := inttostr(nRes);
    if nRes <> 0 then ShowMessage('����ֵ = ' + strInfo)
    else ShowMessage('��ʼ���ɹ�');
end;

// 2���˳�SDK
procedure TForm1.ButtonQuitSDKClick(Sender: TObject);
var
    nRes:Cardinal;
    strInfo:String;
    i :Cardinal;
    pDev :PMaintainInfo;
begin
    // ���
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
    if nRes <> 0 then ShowMessage('����ֵ = ' + strInfo)
    else ShowMessage('�˳��ɹ�');
end;

// 3��ɨ���豸
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
        ShowMessage('����ֵ = ' + strInfo);
    end;
end;

// 4�������豸
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
    
    // ��ȡ��ǰѡ����IP��ַ
    if(ListViewDevList.SelCount > 0) then
    begin
        strInfo := ListViewDevList.Selected.Caption;
        nRes := ConnectCamera(Pchar(strInfo), @pCamHandle);
        if(nRes <> 0) then
        begin
            strValue := inttostr(nRes);
            ShowMessage('����ֵ = ' + strValue);
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

// 5���Ͽ��豸
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
    // ��ȡ��ǰѡ����IP
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
                    ShowMessage('����ֵ = ' + strValue);
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
    if TVI.state and $2000 <> $2000 then        // ��ѡ��û��ѡ��
    begin
        Exit;
    end;

    // �����豸IP
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
                    ShowMessage('����ֵ = ' + strValue);
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
                    ShowMessage('����ֵ = ' + strValue);
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
        edtStatusInfo.Text := '�����豸IPǰ���϶Թ�';
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
                ShowMessage('����ֵ = ' + strValue);
                Exit;
            end
            else
            begin
               if(devStatus = CONNECT_SUCCESS) then strInfo := '���ӳɹ�'
               else if(devStatus = CREATE_ERROR) then strInfo := '���ɾ������'
               else if(devStatus = CONNECT_ERROR) then strInfo := '���Ӵ���'
               else if(devStatus = ABNORMALNET_ERROR) then strInfo := '�����쳣����'
               else if(devStatus = DEVICE_RESET) then strInfo := '�豸��λ';

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
        edtStatusInfo.Text := '�����豸IPǰ���϶Թ�';
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
               ShowMessage('����ֵ = ' + strValue);
               Exit;
            end
            else  ShowMessage('Уʱ�ɹ�');
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
        ShowMessage('NTP������IP����');
        Exit;
    end;

    TVI.mask := TVIF_STATE;
    TVI.hItem := TreeViewConnectedDev.Selected.ItemId;
    TreeView_GetItem(TreeViewConnectedDev.Handle, TVI);

    if TVI.state and $2000 <> $2000 then
    begin
        edtStatusInfo.Text := '�����豸IPǰ���϶Թ�';
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
                ShowMessage('����ֵ = ' + strValue);
                Exit;
            end
            else  ShowMessage('����NTPУʱ�Ƿ����óɹ�');
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
        edtStatusInfo.Text := '�����豸IPǰ���϶Թ�';
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
                ShowMessage('����ֵ = ' + strValue);
                Exit;
            end
            else
            begin
               strInfo := 'DSP���汾(' + StrPas(@verInfo.ucMainVer[0]) + ')' +
               'DSP�Ӱ汾(' + StrPas(@verInfo.ucDSPVer[0]) + ')' +
               '��Ƭ���汾(' + StrPas(@verInfo.ucMCUVer[0]) + ')' +
               'ʶ���汾(' + StrPas(@verInfo.ucOCRVer[0]) + ')' +
               'EEPROM�汾(' + StrPas(@verInfo.ucEPROMVer[0]) + ')';

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
                ShowMessage('����ֵ = ' + strValue);
                Exit;
            end
            else ShowMessage('������������ɹ�');
        end;
    end;
end;

// �ͷŶ�̬��
procedure TForm1.FormDestroy(Sender: TObject);
begin
    if(hHandle<>0) then FreeLibrary(hHandle);
end;

end.
