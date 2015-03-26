Attribute VB_Name = "ModuleLPRSDK"
'ǿ���������ƣ�����ģ����ʼλ��
Option Explicit


'********************************************��̬���أ��ӿں�������*****************************************'��ʼ��
Public Declare Function LPR_Init Lib "LPRSDK.dll" (ByVal hWnd As Long, ByVal pUserData As Long, ByVal fucDeviceInfo As Long, ByVal fucStatus As Long, ByVal fucVehicleData As Long, ByVal fucJPGStream As Long) As Long
'�˳�
Public Declare Function LPR_Quit Lib "LPRSDK.dll" () As Long
'ɨ���豸
Public Declare Function LPR_ScanDevice Lib "LPRSDK.dll" () As Long

'�����豸
Public Declare Function LPR_ConnectCamera Lib "LPRSDK.dll" (ByVal chIP As String, ByRef pHandle As Long) As Long
'�Ͽ��豸
Public Declare Function LPR_DisconnectCamera Lib "LPRSDK.dll" (ByVal pHandle As Long) As Long

'ģ�ⴥ��
Public Declare Function LPR_Capture Lib "LPRSDK.dll" (ByVal pHandle As Long) As Long
'����ģ�ⴥ��
Public Declare Function LPR_CaptureEx Lib "LPRSDK.dll" (ByVal pHandle As Long, ByVal nTimeout As Long) As Long
'���״̬
Public Declare Function LPR_CheckStatus Lib "LPRSDK.dll" (ByVal pHandle As Long, ByRef pStatus As DEVICE_STATUS) As Long
'�豸Уʱ
Public Declare Function LPR_AdjustTime Lib "LPRSDK.dll" (ByVal pHandle As Long, ByVal dwTimeMs As Double) As Long
'��ȡ�汾��Ϣ
Public Declare Function LPR_GetAllVersion Lib "LPRSDK.dll" (ByVal pHandle As Long, ByRef pVerInfo As VersionInfo) As Long
'�Ƿ�д��־
Public Declare Function LPR_IsWriteLog Lib "LPRSDK.dll" (ByVal bWriteLog As Boolean) As Long
'�Ƿ�����NTPУʱ
Public Declare Function LPR_NTPEnable Lib "LPRSDK.dll" (ByVal pHandle As Long, ByVal bNTP As Boolean, ByVal pchNTPSeverIP As String) As Long

'�޸��������
Public Declare Function LPR_SetNetParams Lib "LPRSDK.dll" (ByVal pHandle As Long, ByRef OldParams As NetParams, ByRef NewParams As NetParams) As Long


'********************************************�Զ�������*****************************************************
Public Type ConnectedDevInfo
    strIP As String                     '�豸IP
    pDevHandle As Long                  '�豸���
End Type

'��������ά���������豸�����飬����ֻ֧������3̨�豸
Global connectedDev As ConnectedDevInfo


'�������
Public Type NetParams
    ucDeviceIP(15) As Byte          '�豸IP
    ucMaskIP(15) As Byte            '��������
    ucGateIP(15) As Byte            'Ĭ������
    ucMac(5) As Byte                'MAC��ַ��δʹ��
End Type


'�豸��Ϣ
Public Type DeviceInfo
    DeviceNetInfo As NetParams          '�������
    ucMac(5) As Byte                    'MAC��ַ
    ucDeviceVersion As String * 255     '�豸�汾
    ucConnectNum As Byte                '������
End Type


'�û�����
Public Enum USER_TYPE
    NORMAL_USER = 0                 '�����û�
    UNKNOWN_USER = 1                'δ��Ȩ�û�
End Enum

'����ģʽ
Public Enum DEVICE_TRIGGERMODE
    UNKNOWN_TRIGGER_MODE = 0        'δ֪
    VIDEO_TRIGGER_MODE = 1          '��Ƶ
    LINE_TRIGGER_MODE = 2           '��Ȧ
    SOFT_TRIGGER_MODE = 3           'ģ��
End Enum

'������ɫ
Public Enum PLATE_COLOR
    NON_PLATE = 0                   'δ֪������ɫ
    BLUE_COLOR = 1                  '��ɫ
    WHITE_COLOR = 2                 '��ɫ
    BLACK_COLOR = 3                 '��ɫ
    YELLOW_COLOR = 4                '��ɫ
End Enum

'ץ������
Public Type VehicleData
    PDEVICEHANDLE As Long               '�豸���
    usSerialNO As Integer               '���к�
    ucDeviceIP(15) As Byte              '�豸IP
    ui32DeviceID As Long                '�豸ID
    ui32UserType As USER_TYPE           '�û����ͣ�0 �����û���1 δ��Ȩ�û�������ֵ����
    ui32Brightness As Long              '����ֵ
    triggermode As DEVICE_TRIGGERMODE   '����ģʽ��1 ��Ƶ 2 ��Ȧ 3 ģ�� 0 δ֪ ������ֵ����
    ai8UserDefineInfo(254) As Byte      '�û��Զ�����Ϣ
    ucTime(7) As Byte                   'ʱ�䣬�꣨���������ݣ����¡��ա�ʱ���֡��롢���루ռ�����ֽڣ�
    ucPlate(15) As Byte                 '���ƺ�
    plateColor As PLATE_COLOR           '������ɫ
    
    pucBigImage As Long                 'ץ�Ĵ�ͼ����
    uiBigImageLen As Long               'ץ�Ĵ�ͼ���ݳ���
    usBigImageWidth As Integer          'ץ�Ĵ�ͼ���
    usBigImageHeight As Integer         'ץ�Ĵ�ͼ�߶�
    
    pucCIFImage As Long                 'ץ��CIF����
    uiCIFImageLen As Long               'ץ��CIF���ݳ���
    usCIFImageWidth As Integer          'ץ��CIF���
    usCIFImageHeight As Integer         'ץ��CIF�߶�
    
    pucPlateImage As Long               'ץ��CIF����
    uiPlateImageLen As Long             'ץ��CIF���ݳ���
    usPlateImageWidth As Integer        'ץ��CIF���
    usPlateImageHeight As Integer       'ץ��CIF�߶�
End Type


'�豸״̬
Public Enum DEVICE_STATUS
    CONNECT_SUCCESS = 0                 '���ӳɹ�
    CREATE_ERROR = 1                    '���ɾ������
    CONNECT_ERROR = 2                   '���Ӵ���
    ABNORMALNET_ERROR = 3               '�����쳣����
    DEVICE_RESET = 4                    '�豸��λ
End Enum


'�汾��Ϣ
Public Type VersionInfo
    ucMainVer(254) As Byte           '���汾
    ucDSPVer(254) As Byte            '�ΰ汾
    ucMCUVer(254) As Byte            'MCU�汾
    ucOCRVer(254) As Byte            'ʶ���㷨�汾
    ucEPROMVer(254) As Byte          'EEPROM�汾��
End Type
  
  
  
  


'����·��Ŀ¼
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


'ץ�����ݻص�
Public Sub fucTriggerData(ByVal pUserData As Long, ByRef pData As VehicleData)
    Dim strTemp() As Byte
    Dim byteBigImg() As Byte
    Dim byteCifImg() As Byte
    Dim bytePlateImg() As Byte

    Dim strPath, strBigPath, strCifPath, strPlatePath, strIP, strPlate As String
    
    'ȡ�豸IP
    strTemp = Space$(30)
    CopyMemory VarPtr(strTemp(0)), VarPtr(pData.ucDeviceIP(0)), 16
    strIP = StrConv(strTemp, vbUnicode)
    'MsgBox strIP
    
    'ȡ���ƺ�
    CopyMemory VarPtr(strTemp(0)), VarPtr(pData.ucPlate(0)), 16
    strPlate = StrConv(strTemp, vbUnicode)
    
    FormMain.LabelIP.Caption = strPlate                '���ڻص����ĳ��ƺ���β��������������ɼ��ַ���ͨ���ؼ����⸳ֵ�ķ�ʽ������������ʱδ�뵽���õķ���
    strPlate = FormMain.LabelIP.Caption
    FormMain.LabelIP.Caption = ""
    
    'MsgBox strPlate

    'Dim i As Integer
    'Dim str As String
    'For i = 1 To Len(strIP)
        'str = Mid(strIP, i, 1)
        'MsgBox str
    'Next i
    
    '��ͼ
    Dim nBigLen As Long
    nBigLen = pData.uiBigImageLen
    If nBigLen > 0 And pData.pucBigImage <> 0 Then
        '�������ݴ洢Ŀ¼
        strPath = App.Path + "\Data" + "\��ͼ\" + Format(Now, "YYYYMMDD") + "\"
        '����Ŀ¼
        CreateDirectory strPath
        
        
        strBigPath = strPath + Format(Now, "YYYYMMDDHHmmss") + "(" + strPlate + ").jpg"
        ReDim byteBigImg(nBigLen + 1)
        CopyMemory VarPtr(byteBigImg(0)), pData.pucBigImage, nBigLen
        
        '���ļ�
        Open strBigPath For Binary As #4
        '��ָ��λ��д�룬Ĭ�ϵ�ǰλ��
        Put #4, 1, byteBigImg
        '�ر��ļ�
        Close #4
    End If
    
    'CIFͼ
    Dim nCifLen As Long
    nCifLen = pData.uiCIFImageLen
    If nCifLen > 0 And pData.pucCIFImage <> 0 Then
        '�������ݴ洢Ŀ¼
        strPath = App.Path + "\Data" + "\CIFͼ\" + Format(Now, "YYYYMMDD") + "\"
        '����Ŀ¼
        CreateDirectory strPath
        
        
        strCifPath = strPath + Format(Now, "YYYYMMDDHHmmss") + "(" + strPlate + ").jpg"
        ReDim byteCifImg(nCifLen + 1)
        CopyMemory VarPtr(byteCifImg(0)), pData.pucCIFImage, nCifLen
        
        '���ļ�
        Open strCifPath For Binary As #4
        '��ָ��λ��д�룬Ĭ�ϵ�ǰλ��
        Put #4, 1, byteCifImg
        '�ر��ļ�
        Close #4
    End If
    
    '����ͼ
    Dim nPlateLen As Long
    nPlateLen = pData.uiPlateImageLen
    If nPlateLen > 0 And pData.pucPlateImage <> 0 Then
        '�������ݴ洢Ŀ¼
        strPath = App.Path + "\Data" + "\����ͼ\" + Format(Now, "YYYYMMDD") + "\"
        '����Ŀ¼
        CreateDirectory strPath
        
        
        strPlatePath = strPath + Format(Now, "YYYYMMDDHHmmss") + "(" + strPlate + ").jpg"
        ReDim bytePlateImg(nPlateLen + 1)
        CopyMemory VarPtr(bytePlateImg(0)), pData.pucPlateImage, nPlateLen
        
        '���ļ�
        Open strPlatePath For Binary As #4
        '��ָ��λ��д�룬Ĭ�ϵ�ǰλ��
        Put #4, 1, bytePlateImg
        '�ر��ļ�
        Close #4
    End If
    
    
    '������ʾ����
    FormMain.ImageBig.Picture = LoadPicture(strBigPath)
    FormMain.ImageCif.Picture = LoadPicture(strCifPath)
    FormMain.ImagePlate.Picture = LoadPicture(strPlatePath)
    
    
    Dim nColor As Integer
    nColor = pData.plateColor
    
    If nColor = BLUE_COLOR Then             '��ɫ
        FormMain.LabelPlateNo.BackColor = &HFF0000
    ElseIf nColor = WHITE_COLOR Then        '��ɫ
        FormMain.LabelPlateNo.BackColor = &HFFFFFF
    ElseIf nColor = BLACK_COLOR Then        '��ɫ
        FormMain.LabelPlateNo.BackColor = &H0&
    ElseIf nColor = YELLOW_COLOR Then       '��ɫ
        FormMain.LabelPlateNo.BackColor = &HFFFF&
    Else                                    'δ֪������ɫ
        FormMain.LabelPlateNo.BackColor = &H8000000F
    End If
     FormMain.LabelPlateNo.Caption = strPlate
End Sub





'********************************************�ص�����*******************************************************
'�豸��Ϣ
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
    
    
    '�Ѿ����ڣ�������ӣ����޸�������Ϣ����
    FormMain.LabelIP.Caption = strIP                '���ڻص������豸IP�ֽ����ʹ��б���ͼ��ȡ���豸IPʼ�ղ��ȣ���ʱ���ø÷�������
    strTemIP = FormMain.LabelIP.Caption
    FormMain.LabelIP.Caption = ""
    
    Dim temIP As String
    For i = 1 To FormMain.ListViewDevList.ListItems.Count
        temIP = FormMain.ListViewDevList.ListItems(i).Text
        
        If temIP = strTemIP Then
            'MsgBox "��", 0, "��ʾ"
            FormMain.ListViewDevList.ListItems(i).ListSubItems(1) = strMask
            FormMain.ListViewDevList.ListItems(i).ListSubItems(2) = strGate
            FormMain.ListViewDevList.ListItems(i).ListSubItems(3) = strMac
            Exit Sub
        Else
            'MsgBox "����", 0, "��ʾ"
            'MsgBox "strIPLen = " + CStr(Len(strIP)), 0, "��ʾ"
            'MsgBox "temIPLen = " + CStr(Len(temIP)), 0, "��ʾ"
              
        End If
    Next i
    
    
    Dim itemX As ListItem
    Set itemX = FormMain.ListViewDevList.ListItems.Add
    itemX.Text = strIP                      '��һ�е�һ��
    itemX.SubItems(1) = strMask             '�ڶ���
    itemX.SubItems(2) = strGate             '������
    itemX.SubItems(3) = strMac              '������
End Sub



