Attribute VB_Name = "ModuleLPRSDK"
'强制声明控制，用于模块的最开始位置
Option Explicit


'********************************************静态加载，接口函数声明*****************************************'初始化
Public Declare Function LPR_Init Lib "LPRSDK.dll" (ByVal hWnd As Long, ByVal pUserData As Long, ByVal fucDeviceInfo As Long, ByVal fucStatus As Long, ByVal fucVehicleData As Long, ByVal fucJPGStream As Long) As Long
'退出
Public Declare Function LPR_Quit Lib "LPRSDK.dll" () As Long
'扫描设备
Public Declare Function LPR_ScanDevice Lib "LPRSDK.dll" () As Long

'连接设备
Public Declare Function LPR_ConnectCamera Lib "LPRSDK.dll" (ByVal chIP As String, ByRef pHandle As Long) As Long
'断开设备
Public Declare Function LPR_DisconnectCamera Lib "LPRSDK.dll" (ByVal pHandle As Long) As Long

'模拟触发
Public Declare Function LPR_Capture Lib "LPRSDK.dll" (ByVal pHandle As Long) As Long
'阻塞模拟触发
Public Declare Function LPR_CaptureEx Lib "LPRSDK.dll" (ByVal pHandle As Long, ByVal nTimeout As Long) As Long
'检测状态
Public Declare Function LPR_CheckStatus Lib "LPRSDK.dll" (ByVal pHandle As Long, ByRef pStatus As DEVICE_STATUS) As Long
'设备校时
Public Declare Function LPR_AdjustTime Lib "LPRSDK.dll" (ByVal pHandle As Long, ByVal dwTimeMs As Double) As Long
'获取版本信息
Public Declare Function LPR_GetAllVersion Lib "LPRSDK.dll" (ByVal pHandle As Long, ByRef pVerInfo As VersionInfo) As Long
'是否写日志
Public Declare Function LPR_IsWriteLog Lib "LPRSDK.dll" (ByVal bWriteLog As Boolean) As Long
'是否启用NTP校时
Public Declare Function LPR_NTPEnable Lib "LPRSDK.dll" (ByVal pHandle As Long, ByVal bNTP As Boolean, ByVal pchNTPSeverIP As String) As Long

'修改网络参数
Public Declare Function LPR_SetNetParams Lib "LPRSDK.dll" (ByVal pHandle As Long, ByRef OldParams As NetParams, ByRef NewParams As NetParams) As Long


'********************************************自定义类型*****************************************************
Public Type ConnectedDevInfo
    strIP As String                     '设备IP
    pDevHandle As Long                  '设备句柄
End Type

'定义用于维护已连接设备的数组，暂且只支持连接3台设备
Global connectedDev As ConnectedDevInfo


'网络参数
Public Type NetParams
    ucDeviceIP(15) As Byte          '设备IP
    ucMaskIP(15) As Byte            '子网掩码
    ucGateIP(15) As Byte            '默认网关
    ucMac(5) As Byte                'MAC地址，未使用
End Type


'设备信息
Public Type DeviceInfo
    DeviceNetInfo As NetParams          '网络参数
    ucMac(5) As Byte                    'MAC地址
    ucDeviceVersion As String * 255     '设备版本
    ucConnectNum As Byte                '连接数
End Type


'用户类型
Public Enum USER_TYPE
    NORMAL_USER = 0                 '正常用户
    UNKNOWN_USER = 1                '未授权用户
End Enum

'触发模式
Public Enum DEVICE_TRIGGERMODE
    UNKNOWN_TRIGGER_MODE = 0        '未知
    VIDEO_TRIGGER_MODE = 1          '视频
    LINE_TRIGGER_MODE = 2           '线圈
    SOFT_TRIGGER_MODE = 3           '模拟
End Enum

'车牌颜色
Public Enum PLATE_COLOR
    NON_PLATE = 0                   '未知车牌颜色
    BLUE_COLOR = 1                  '蓝色
    WHITE_COLOR = 2                 '白色
    BLACK_COLOR = 3                 '黑色
    YELLOW_COLOR = 4                '黄色
End Enum

'抓拍数据
Public Type VehicleData
    PDEVICEHANDLE As Long               '设备句柄
    usSerialNO As Integer               '序列号
    ucDeviceIP(15) As Byte              '设备IP
    ui32DeviceID As Long                '设备ID
    ui32UserType As USER_TYPE           '用户类型，0 正常用户，1 未授权用户，其他值保留
    ui32Brightness As Long              '亮度值
    triggermode As DEVICE_TRIGGERMODE   '触发模式，1 视频 2 线圈 3 模拟 0 未知 ，其他值保留
    ai8UserDefineInfo(254) As Byte      '用户自定义信息
    ucTime(7) As Byte                   '时间，年（减掉后的年份）、月、日、时、分、秒、毫秒（占两个字节）
    ucPlate(15) As Byte                 '车牌号
    plateColor As PLATE_COLOR           '车牌颜色
    
    pucBigImage As Long                 '抓拍大图数据
    uiBigImageLen As Long               '抓拍大图数据长度
    usBigImageWidth As Integer          '抓拍大图宽度
    usBigImageHeight As Integer         '抓拍大图高度
    
    pucCIFImage As Long                 '抓拍CIF数据
    uiCIFImageLen As Long               '抓拍CIF数据长度
    usCIFImageWidth As Integer          '抓拍CIF宽度
    usCIFImageHeight As Integer         '抓拍CIF高度
    
    pucPlateImage As Long               '抓拍CIF数据
    uiPlateImageLen As Long             '抓拍CIF数据长度
    usPlateImageWidth As Integer        '抓拍CIF宽度
    usPlateImageHeight As Integer       '抓拍CIF高度
End Type


'设备状态
Public Enum DEVICE_STATUS
    CONNECT_SUCCESS = 0                 '连接成功
    CREATE_ERROR = 1                    '生成句柄错误
    CONNECT_ERROR = 2                   '连接错误
    ABNORMALNET_ERROR = 3               '网络异常错误
    DEVICE_RESET = 4                    '设备复位
End Enum


'版本信息
Public Type VersionInfo
    ucMainVer(254) As Byte           '主版本
    ucDSPVer(254) As Byte            '次版本
    ucMCUVer(254) As Byte            'MCU版本
    ucOCRVer(254) As Byte            '识别算法版本
    ucEPROMVer(254) As Byte          'EEPROM版本号
End Type
  
  
  
  


'创建路径目录
Public Sub CreateDirectory(ByVal strPath As String)
    Dim fsoTest As New FileSystemObject
    Dim folder1 As Folder
    Dim sExistPath As String
    Dim s As String
    Dim i As Integer
    
   
   If Dir(strPath, vbDirectory) = "" Then
        For i = 1 To Len(strPath)
            s = Mid(strPath, i, 1)
            If s = "\" Then
                sExistPath = Mid(strPath, 1, i)
                If Dir(sExistPath, vbDirectory) = "" Then
                    MkDir sExistPath
                End If
            End If
        Next
    End If
End Sub


'抓拍数据回调
Public Sub fucTriggerData(ByVal pUserData As Long, ByRef pData As VehicleData)
    Dim strTemp() As Byte
    Dim byteBigImg() As Byte
    Dim byteCifImg() As Byte
    Dim bytePlateImg() As Byte

    Dim strPath, strBigPath, strCifPath, strPlatePath, strIP, strPlate As String
    
    '取设备IP
    strTemp = Space$(30)
    CopyMemory VarPtr(strTemp(0)), VarPtr(pData.ucDeviceIP(0)), 16
    strIP = StrConv(strTemp, vbUnicode)
    'MsgBox strIP
    
    '取车牌号
    CopyMemory VarPtr(strTemp(0)), VarPtr(pData.ucPlate(0)), 16
    strPlate = StrConv(strTemp, vbUnicode)
    
    FormMain.LabelIP.Caption = strPlate                '由于回调传的车牌号码尾部有许多其他不可见字符，通过控件标题赋值的方式可以消除，暂时未想到更好的方法
    strPlate = FormMain.LabelIP.Caption
    FormMain.LabelIP.Caption = ""
    
    'MsgBox strPlate

    'Dim i As Integer
    'Dim str As String
    'For i = 1 To Len(strIP)
        'str = Mid(strIP, i, 1)
        'MsgBox str
    'Next i
    
    '大图
    Dim nBigLen As Long
    nBigLen = pData.uiBigImageLen
    If nBigLen > 0 And pData.pucBigImage <> 0 Then
        '创建数据存储目录
        strPath = App.Path + "\Data" + "\大图\" + Format(Now, "YYYYMMDD") + "\"
        '创建目录
        CreateDirectory strPath
        
        
        strBigPath = strPath + Format(Now, "YYYYMMDDHHmmss") + "(" + strPlate + ").jpg"
        ReDim byteBigImg(nBigLen + 1)
        CopyMemory VarPtr(byteBigImg(0)), pData.pucBigImage, nBigLen
        
        '打开文件
        Open strBigPath For Binary As #4
        '从指定位置写入，默认当前位置
        Put #4, 1, byteBigImg
        '关闭文件
        Close #4
    End If
    
    'CIF图
    Dim nCifLen As Long
    nCifLen = pData.uiCIFImageLen
    If nCifLen > 0 And pData.pucCIFImage <> 0 Then
        '创建数据存储目录
        strPath = App.Path + "\Data" + "\CIF图\" + Format(Now, "YYYYMMDD") + "\"
        '创建目录
        CreateDirectory strPath
        
        
        strCifPath = strPath + Format(Now, "YYYYMMDDHHmmss") + "(" + strPlate + ").jpg"
        ReDim byteCifImg(nCifLen + 1)
        CopyMemory VarPtr(byteCifImg(0)), pData.pucCIFImage, nCifLen
        
        '打开文件
        Open strCifPath For Binary As #4
        '从指定位置写入，默认当前位置
        Put #4, 1, byteCifImg
        '关闭文件
        Close #4
    End If
    
    '车牌图
    Dim nPlateLen As Long
    nPlateLen = pData.uiPlateImageLen
    If nPlateLen > 0 And pData.pucPlateImage <> 0 Then
        '创建数据存储目录
        strPath = App.Path + "\Data" + "\车牌图\" + Format(Now, "YYYYMMDD") + "\"
        '创建目录
        CreateDirectory strPath
        
        
        strPlatePath = strPath + Format(Now, "YYYYMMDDHHmmss") + "(" + strPlate + ").jpg"
        ReDim bytePlateImg(nPlateLen + 1)
        CopyMemory VarPtr(bytePlateImg(0)), pData.pucPlateImage, nPlateLen
        
        '打开文件
        Open strPlatePath For Binary As #4
        '从指定位置写入，默认当前位置
        Put #4, 1, bytePlateImg
        '关闭文件
        Close #4
    End If
    
    
    '界面显示数据
    FormMain.ImageBig.Picture = LoadPicture(strBigPath)
    FormMain.ImageCif.Picture = LoadPicture(strCifPath)
    FormMain.ImagePlate.Picture = LoadPicture(strPlatePath)
    
    
    Dim nColor As Integer
    nColor = pData.plateColor
    
    If nColor = BLUE_COLOR Then             '蓝色
        FormMain.LabelPlateNo.BackColor = &HFF0000
    ElseIf nColor = WHITE_COLOR Then        '白色
        FormMain.LabelPlateNo.BackColor = &HFFFFFF
    ElseIf nColor = BLACK_COLOR Then        '黑色
        FormMain.LabelPlateNo.BackColor = &H0&
    ElseIf nColor = YELLOW_COLOR Then       '黄色
        FormMain.LabelPlateNo.BackColor = &HFFFF&
    Else                                    '未知车牌颜色
        FormMain.LabelPlateNo.BackColor = &H8000000F
    End If
     FormMain.LabelPlateNo.Caption = strPlate
End Sub





'********************************************回调函数*******************************************************
'设备信息
Public Sub fucDeviceInfo(ByVal pUserData As Long, ByRef pDeviceInfo As DeviceInfo)
    Dim strIP, strGate, strMask, strMac As String
    Dim i As Integer
    Dim strTemIP As String
    
    Dim byteIP(15) As Byte
    Dim byteGate(15) As Byte
    Dim byteMask(15) As Byte
    Dim byteMAC(5) As Byte
    
    Erase byteIP
    Erase byteGate
    Erase byteMask
    Erase byteMAC
    
    'Dim byteIP() As Byte
    'Dim byteGate() As Byte
    'Dim byteMask() As Byte
    'Dim byteMAC() As Byte
    'byteIP = Space$(16)
    'byteGate = Space$(16)
    'byteMask = Space$(16)
    'byteMAC = Space$(6)
    
    CopyMemory VarPtr(byteIP(0)), VarPtr(pDeviceInfo.DeviceNetInfo.ucDeviceIP(0)), 16
    strIP = StrConv(byteIP, vbUnicode)
    'MsgBox strIP
    
    CopyMemory VarPtr(byteMask(0)), VarPtr(pDeviceInfo.DeviceNetInfo.ucMaskIP(0)), 16
    strMask = StrConv(byteMask, vbUnicode)
    'MsgBox strMask
    
    
    CopyMemory VarPtr(byteGate(0)), VarPtr(pDeviceInfo.DeviceNetInfo.ucGateIP(0)), 16
    strGate = StrConv(byteGate, vbUnicode)
    'MsgBox strGate
    
    
    CopyMemory VarPtr(byteMAC(0)), VarPtr(pDeviceInfo.ucMac(0)), 6
    Dim temps As String
    strMac = ""
    For i = 0 To 5
        temps = Right("0" & Hex(byteMAC(i)), 2)
        strMac = strMac & temps
    Next i
    'MsgBox strMac
    
    
    '已经存在，则不再添加，仅修改其它信息即可
    FormMain.LabelIP.Caption = strIP                '由于回调传的设备IP字节数和从列表视图获取的设备IP始终不等，暂时采用该方法处理
    strTemIP = FormMain.LabelIP.Caption
    FormMain.LabelIP.Caption = ""
    
    Dim temIP As String
    For i = 1 To FormMain.ListViewDevList.ListItems.Count
        temIP = FormMain.ListViewDevList.ListItems(i).Text
        
        If temIP = strTemIP Then
            'MsgBox "等", 0, "提示"
            FormMain.ListViewDevList.ListItems(i).ListSubItems(1) = strMask
            FormMain.ListViewDevList.ListItems(i).ListSubItems(2) = strGate
            FormMain.ListViewDevList.ListItems(i).ListSubItems(3) = strMac
            Exit Sub
        Else
            'MsgBox "不等", 0, "提示"
            'MsgBox "strIPLen = " + CStr(Len(strIP)), 0, "提示"
            'MsgBox "temIPLen = " + CStr(Len(temIP)), 0, "提示"
              
        End If
    Next i
    
    
    Dim itemX As ListItem
    Set itemX = FormMain.ListViewDevList.ListItems.Add
    itemX.Text = strIP                      '第一行第一列
    itemX.SubItems(1) = strMask             '第二列
    itemX.SubItems(2) = strGate             '第三列
    itemX.SubItems(3) = strMac              '第四列
End Sub



