VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.1#0"; "MSCOMCTL.OCX"
Begin VB.Form FormMain 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "����"
   ClientHeight    =   9675
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   15255
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   9675
   ScaleWidth      =   15255
   StartUpPosition =   3  '����ȱʡ
   Begin VB.TextBox TextGate 
      Height          =   390
      Left            =   10200
      TabIndex        =   32
      Top             =   7680
      Width           =   1575
   End
   Begin VB.TextBox TextMask 
      Height          =   390
      Left            =   10200
      TabIndex        =   31
      Top             =   7320
      Width           =   1575
   End
   Begin VB.TextBox TextIP 
      Height          =   390
      Left            =   10200
      TabIndex        =   30
      Top             =   6960
      Width           =   1575
   End
   Begin VB.CheckBox CheckStartNTP 
      Caption         =   "����NTPУʱ"
      Height          =   255
      Left            =   10200
      TabIndex        =   29
      Top             =   6000
      Width           =   1335
   End
   Begin VB.TextBox TextNTPIP 
      Height          =   390
      Left            =   10200
      TabIndex        =   28
      Top             =   6360
      Width           =   1575
   End
   Begin VB.TextBox TextVerInfo 
      Height          =   390
      Left            =   9240
      TabIndex        =   27
      Top             =   8760
      Width           =   5535
   End
   Begin VB.TextBox TextStatusInfo 
      Height          =   390
      Left            =   12240
      TabIndex        =   26
      Top             =   7320
      Width           =   2535
   End
   Begin VB.CommandButton CommandModify 
      Caption         =   "�޸�"
      Height          =   375
      Index           =   10
      Left            =   10200
      TabIndex        =   23
      Top             =   8040
      Width           =   1575
   End
   Begin VB.CheckBox CheckWriteLog 
      Caption         =   "д��־ "
      Height          =   255
      Left            =   9240
      TabIndex        =   18
      Top             =   5640
      Width           =   975
   End
   Begin VB.CommandButton CommandVersionInfo 
      Caption         =   "��ȡ�汾��Ϣ"
      Height          =   375
      Index           =   9
      Left            =   9240
      TabIndex        =   17
      Top             =   9120
      Width           =   5535
   End
   Begin VB.CommandButton CommandJustTime 
      Caption         =   "����ϵͳʱ��Уʱ"
      Height          =   375
      Index           =   8
      Left            =   12240
      TabIndex        =   16
      Top             =   8160
      Width           =   2535
   End
   Begin VB.CommandButton CommandStatus 
      Caption         =   "���״̬"
      Height          =   375
      Index           =   7
      Left            =   12240
      TabIndex        =   15
      Top             =   7680
      Width           =   2535
   End
   Begin VB.CommandButton CommandBlockTrigger 
      Caption         =   "����ģ�ⴥ��"
      Height          =   375
      Index           =   6
      Left            =   12240
      TabIndex        =   14
      Top             =   6480
      Width           =   2535
   End
   Begin VB.CommandButton CommandTrigger 
      Caption         =   "ģ�ⴥ��"
      Height          =   375
      Index           =   5
      Left            =   12240
      TabIndex        =   13
      Top             =   6000
      Width           =   2535
   End
   Begin VB.CommandButton CommandScanDev 
      Caption         =   "ɨ���豸"
      Height          =   375
      Index           =   4
      Left            =   12240
      TabIndex        =   12
      Top             =   4800
      Width           =   2535
   End
   Begin VB.CommandButton CommandDisConnect 
      Caption         =   "�Ͽ��豸"
      Height          =   375
      Index           =   3
      Left            =   13560
      TabIndex        =   11
      Top             =   5280
      Width           =   1215
   End
   Begin VB.CommandButton CommandConnectDev 
      Caption         =   "�����豸"
      Height          =   375
      Index           =   2
      Left            =   12240
      TabIndex        =   10
      Top             =   5280
      Width           =   1215
   End
   Begin VB.CommandButton CommandQuit 
      Caption         =   "�˳�"
      Height          =   375
      Index           =   1
      Left            =   10560
      TabIndex        =   9
      Top             =   4800
      Width           =   1215
   End
   Begin VB.CommandButton CommandInit 
      Caption         =   "��ʼ��"
      Height          =   375
      Index           =   0
      Left            =   9240
      TabIndex        =   8
      Top             =   4800
      Width           =   1215
   End
   Begin VB.Frame Frame6 
      Caption         =   "�����豸"
      Height          =   2055
      Left            =   8640
      TabIndex        =   5
      Top             =   2520
      Width           =   6495
      Begin MSComctlLib.TreeView TreeViewConnectedDev 
         Height          =   1695
         Left            =   120
         TabIndex        =   7
         Top             =   240
         Width           =   6255
         _ExtentX        =   11033
         _ExtentY        =   2990
         _Version        =   393217
         LabelEdit       =   1
         Style           =   7
         Checkboxes      =   -1  'True
         Appearance      =   1
      End
   End
   Begin VB.Frame Frame5 
      Caption         =   "�豸�б�"
      Height          =   2415
      Left            =   8640
      TabIndex        =   4
      Top             =   0
      Width           =   6495
      Begin MSComctlLib.ListView ListViewDevList 
         Height          =   2055
         Left            =   120
         TabIndex        =   6
         Top             =   240
         Width           =   6255
         _ExtentX        =   11033
         _ExtentY        =   3625
         View            =   3
         LabelWrap       =   -1  'True
         HideSelection   =   -1  'True
         _Version        =   393217
         ForeColor       =   -2147483640
         BackColor       =   -2147483643
         BorderStyle     =   1
         Appearance      =   1
         NumItems        =   0
      End
   End
   Begin VB.Frame Frame3 
      Caption         =   "����ͼ"
      Height          =   1095
      Left            =   120
      TabIndex        =   3
      Top             =   8520
      Width           =   4095
      Begin VB.Image ImagePlate 
         Height          =   735
         Left            =   120
         Stretch         =   -1  'True
         Top             =   240
         Width           =   3855
      End
   End
   Begin VB.Frame Frame4 
      Caption         =   "���ƺ�"
      Height          =   1095
      Left            =   4320
      TabIndex        =   2
      Top             =   8520
      Width           =   4215
      Begin VB.Label LabelPlateNo 
         Alignment       =   2  'Center
         Height          =   825
         Left            =   120
         TabIndex        =   25
         Top             =   240
         Width           =   4065
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "CIFͼ"
      Height          =   3735
      Left            =   120
      TabIndex        =   1
      Top             =   4680
      Width           =   8415
      Begin VB.Image ImageCif 
         Height          =   3375
         Left            =   120
         Stretch         =   -1  'True
         Top             =   240
         Width           =   8175
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "��ͼ"
      Height          =   4575
      Left            =   120
      TabIndex        =   0
      Top             =   0
      Width           =   8415
      Begin VB.Image ImageBig 
         Height          =   4215
         Left            =   120
         Stretch         =   -1  'True
         Top             =   240
         Width           =   8175
      End
   End
   Begin VB.Label LabelIP 
      Height          =   135
      Left            =   8640
      TabIndex        =   24
      Top             =   8400
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "Ĭ������"
      Height          =   255
      Index           =   1
      Left            =   9360
      TabIndex        =   22
      Top             =   7800
      Width           =   735
   End
   Begin VB.Label Label3 
      Caption         =   "��������"
      Height          =   255
      Left            =   9360
      TabIndex        =   21
      Top             =   7440
      Width           =   735
   End
   Begin VB.Label Label2 
      Caption         =   "�豸IP"
      Height          =   255
      Left            =   9360
      TabIndex        =   20
      Top             =   7080
      Width           =   615
   End
   Begin VB.Label Label1 
      Caption         =   "NTP������IP"
      Height          =   255
      Index           =   0
      Left            =   9120
      TabIndex        =   19
      Top             =   6480
      Width           =   1095
   End
End
Attribute VB_Name = "FormMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False


'����NTPУʱ
Private Sub CheckStartNTP_Click()
    Dim nRes As Long
    
    If TextNTPIP.Text = "" Then
        MsgBox "NTP������IP����Ϊ��", 0, "��ʾ"
        Exit Sub
     End If
    
    nRes = LPR_NTPEnable(connectedDev.pDevHandle, CheckStartNTP.Value, TextNTPIP.Text)
    If nRes <> 0 Then MsgBox "�����Ƿ�����NTPУʱʧ�ܣ�����ֵ = " + CStr(nRes), 0, "��ʾ"
End Sub


'д��־
Private Sub CheckWriteLog_Click()
    Dim nRes As Long
    
    nRes = LPR_IsWriteLog(CheckWriteLog.Value)
    If nRes <> 0 Then MsgBox "�����Ƿ�д��־ʧ�ܣ�����ֵ = " + CStr(nRes), 0, "��ʾ"
End Sub


'����ģ�ⴥ��
Private Sub CommandBlockTrigger_Click(Index As Integer)
    If TreeViewConnectedDev.Nodes.Count = 0 Or TreeViewConnectedDev.SelectedItem Is Nothing Then Exit Sub

    If TreeViewConnectedDev.SelectedItem.Checked = True Then
        Dim nRes As Long
        nRes = LPR_CaptureEx(connectedDev.pDevHandle, 1000)
        If nRes <> 0 Then MsgBox "����ģ�ⴥ��ʧ�ܣ�����ֵ = " + CStr(nRes), 0, "��ʾ"
    End If
End Sub

'�����豸
Private Sub CommandConnectDev_Click(Index As Integer)
    Dim nRes As Long
    
    If ListViewDevList.ListItems.Count = 0 Then Exit Sub
    
    
     '��ȡ�������豸IP
    Dim temIP As String
    temIP = ListViewDevList.SelectedItem.Text
    'MsgBox temIP
    Dim hDevHandle As Long
    
    Dim bFlag As Boolean
    bFlag = False
    
    nRes = LPR_ConnectCamera(temIP, hDevHandle)
    If nRes = 0 Then
        bFlag = True
    Else
        '����ǰ��ִ�����¶Ͽ�
         nRes = LPR_DisconnectCamera(connectedDev.pDevHandle)
         
        '����б������нڵ�
        TreeViewConnectedDev.Nodes.Clear
        MsgBox "����ʧ�ܣ�����ֵ = " + CStr(nRes), 0, "��ʾ"
    End If
    
    If bFlag = True Then
        If TreeViewConnectedDev.Nodes.Count <> 0 Then nRes = LPR_DisconnectCamera(connectedDev.pDevHandle)
        '����б������нڵ�
        TreeViewConnectedDev.Nodes.Clear
        '�����б�����
        Dim Nodeindex As Node
        Set Nodeindex = TreeViewConnectedDev.Nodes.Add(, , "connected", temIP)
       
       
        connectedDev.strIP = temIP
        connectedDev.pDevHandle = hDevHandle
    End If
End Sub


'�Ͽ�����
Private Sub CommandDisConnect_Click(Index As Integer)
    If TreeViewConnectedDev.Nodes.Count = 0 Then Exit Sub
    
    Dim nRes As Long
    nRes = LPR_DisconnectCamera(connectedDev.pDevHandle)
    If nRes <> 0 Then
        MsgBox "�Ͽ�����ʧ�ܣ�����ֵ = " + CStr(nRes), 0, "��ʾ"
    Else
        TreeViewConnectedDev.Nodes.Clear
    End If
End Sub


'��ʼ��
Private Sub CommandInit_Click(Index As Integer)
    Dim nRes As Long
    nRes = LPR_Init(Me.hWnd, 0, AddressOf fucDeviceInfo, 0, AddressOf fucTriggerData, 0)
    If nRes = 0 Then
        MsgBox "��ʼ���ɹ�", 0, "��ʾ"
    Else
        MsgBox "��ʼ��ʧ�ܣ�����ֵ = " + CStr(nRes), 0, "��ʾ"
    End If
End Sub


'�˳�
Private Sub CommandQuit_Click(Index As Integer)
    Dim nRes As Long
    
    CommandDisConnect_Click 0
    ListViewDevList.ListItems.Clear
    
    
    nRes = LPR_Quit()
    If nRes = 0 Then
        MsgBox "�˳��ɹ�", 0, "��ʾ"
    Else
        MsgBox "�˳�ʧ�ܣ�����ֵ = " + CStr(nRes), 0, "��ʾ"
     End If
End Sub

'ɨ���豸
Private Sub CommandScanDev_Click(Index As Integer)
    Dim nRes As Long
    ListViewDevList.ListItems.Clear
    nRes = LPR_ScanDevice()
    If nRes <> 0 Then MsgBox "ɨ��ʧ�ܣ�����ֵ = " + CStr(nRes), 0, "��ʾ"
End Sub

'����豸״̬
Private Sub CommandStatus_Click(Index As Integer)
    Dim nRes As Long
    Dim nStatus As DEVICE_STATUS
    
    nRes = LPR_CheckStatus(connectedDev.pDevHandle, nStatus)
    If nRes <> 0 Then
        MsgBox "���״̬ʧ�ܣ�����ֵ = " + CStr(nRes), 0, "��ʾ"
    Else
        If nStatus = CONNECT_SUCCESS Then
            TextStatusInfo.Text = "���ӳɹ�"
        ElseIf nStatus = CREATE_ERROR Then
            TextStatusInfo.Text = "���ɾ������"
        ElseIf nStatus = CONNECT_ERROR Then
            TextStatusInfo.Text = "���Ӵ���"
        ElseIf nStatus = ABNORMALNET_ERROR Then
            TextStatusInfo.Text = "�����쳣����"
        ElseIf nStatus = DEVICE_RESET Then
            TextStatusInfo.Text = "�豸��λ"
        End If
    End If
End Sub

'Уʱ
Private Sub CommandJustTime_Click(Index As Integer)
    Dim nRes As Long

    nRes = LPR_AdjustTime(connectedDev.pDevHandle, 0)
    If nRes <> 0 Then
        MsgBox "Уʱʧ�ܣ�����ֵ = " + CStr(nRes), 0, "��ʾ"
    Else
        MsgBox "Уʱ�ɹ�", 0, "��ʾ"
    End If
End Sub

'ģ�ⴥ��
Private Sub CommandTrigger_Click(Index As Integer)
    If TreeViewConnectedDev.Nodes.Count = 0 Or TreeViewConnectedDev.SelectedItem Is Nothing Then Exit Sub
    
    If TreeViewConnectedDev.SelectedItem.Checked = True Then
        Dim nRes As Long
        nRes = LPR_Capture(connectedDev.pDevHandle)
        If nRes <> 0 Then MsgBox "ģ�ⴥ��ʧ�ܣ�����ֵ = " + CStr(nRes), 0, "��ʾ"
    End If
End Sub

'��ȡ�汾��Ϣ
Private Sub CommandVersionInfo_Click(Index As Integer)
    Dim nRes As Long
    Dim verInfo As VersionInfo
    Dim ucMainVer() As Byte           '���汾
    Dim ucDSPVer() As Byte            '�ΰ汾
    Dim ucMCUVer() As Byte            'MCU�汾
    Dim ucOCRVer() As Byte            'ʶ���㷨�汾
    Dim ucEPROMVer()  As Byte         'EEPROM�汾��
    
    Dim strMainVer, strDSPVer, strMCUVer, strOCRVer, strEPROMVer As String
    

    nRes = LPR_GetAllVersion(connectedDev.pDevHandle, verInfo)
    If nRes <> 0 Then
        MsgBox "��ȡ�汾��Ϣʧ�ܣ�����ֵ = " + CStr(nRes), 0, "��ʾ"
    Else
        ucMainVer = Space$(255)
        CopyMemory VarPtr(ucMainVer(0)), VarPtr(verInfo.ucMainVer(0)), 255
        strMainVer = "DSP���汾��" + StrConv(ucMainVer, vbUnicode)
        'MsgBox strMainVer
        LabelIP.Caption = strMainVer
        strMainVer = LabelIP.Caption
       
        
        ucDSPVer = Space$(255)
        CopyMemory VarPtr(ucDSPVer(0)), VarPtr(verInfo.ucDSPVer(0)), 255
        strDSPVer = "DSP�ΰ汾��" + StrConv(ucDSPVer, vbUnicode)
        'MsgBox strDSPVer
        LabelIP.Caption = strDSPVer
        strDSPVer = LabelIP.Caption
        
        ucMCUVer = Space$(255)
        CopyMemory VarPtr(ucMCUVer(0)), VarPtr(verInfo.ucMCUVer(0)), 255
        strMCUVer = "MCU�汾��" + StrConv(ucMCUVer, vbUnicode)
        'MsgBox strMCUVer
        LabelIP.Caption = strMCUVer
        strMCUVer = LabelIP.Caption
         
        ucOCRVer = Space$(255)
        CopyMemory VarPtr(ucOCRVer(0)), VarPtr(verInfo.ucOCRVer(0)), 255
        strOCRVer = "OCR�汾��" + StrConv(ucOCRVer, vbUnicode)
        'MsgBox strOCRVer
        LabelIP.Caption = strOCRVer
        strOCRVer = LabelIP.Caption
         
         
        ucEPROMVer = Space$(255)
        CopyMemory VarPtr(ucEPROMVer(0)), VarPtr(verInfo.ucEPROMVer(0)), 255
        strEPROMVer = "EPROM�汾��" + StrConv(ucEPROMVer, vbUnicode)
        'MsgBox strEPROMVer
        LabelIP.Caption = strEPROMVer
        strEPROMVer = LabelIP.Caption
        LabelIP.Caption = ""
            
        TextVerInfo.Text = strMainVer + strDSPVer + strMCUVer + strOCRVer + strEPROMVer
    End If
End Sub

Private Sub Form_Load()
    ListViewDevList.ListItems.Clear                 '����б�
    ListViewDevList.ColumnHeaders.Clear             '����б�ͷ
    ListViewDevList.view = lvwReport                '�����б���ʾ��ʽ
    ListViewDevList.GridLines = True                '��ʾ������
    ListViewDevList.LabelEdit = lvwManual           '��ֹ��ǩ�༭
    ListViewDevList.FullRowSelect = True            'ѡ������


    ListViewDevList.ColumnHeaders.Add , , "�豸IP", 1600
    ListViewDevList.ColumnHeaders.Add , , "��������", 1600
    ListViewDevList.ColumnHeaders.Add , , "Ĭ������", 1600
    ListViewDevList.ColumnHeaders.Add , , "MAC��ַ", 2000
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Dim nRes As Long
    
    CommandDisConnect_Click 0
    ListViewDevList.ListItems.Clear
    LPR_Quit

End Sub


Private Sub TreeViewConnectedDev_NodeClick(ByVal Node As MSComctlLib.Node)
    Dim strTreeIP, strGate, strMask, strMac As String
    
    strTreeIP = Node.Text
    
    Dim i As Integer
    Dim strListIP As String
    For i = 1 To ListViewDevList.ListItems.Count
        strListIP = ListViewDevList.ListItems(i).Text
        
        If strListIP = strTreeIP Then
            'MsgBox "��", 0, "��ʾ"
            TextIP.Text = strListIP
            TextMask.Text = FormMain.ListViewDevList.ListItems(i).ListSubItems(1)
            TextGate.Text = FormMain.ListViewDevList.ListItems(i).ListSubItems(2)
            'TextMAC.Text = FormMain.ListViewDevList.ListItems(i).ListSubItems(3)
            Exit Sub
        End If
    Next i
End Sub

'�޸��������
Private Sub CommandModify_Click(Index As Integer)
    Dim oldNet As NetParams
    Dim newNet As NetParams
    Dim tlen As Long
    Dim nLen As Integer
    
   
    Dim nRes As Long
    Dim strIP, strGate, strMask, strMac As String
    Dim temByte() As Byte
    
    
    nLen = Len(TextIP.Text)
    strIP = StrConv(TextIP.Text, vbFromUnicode)
    'ReDim temByte(nLen)
    'temByte = vbNullString
    temByte() = strIP
    'Erase newNet.ucDeviceIP
    CopyMemory VarPtr(newNet.ucDeviceIP(0)), VarPtr(temByte(0)), nLen
    
    nLen = Len(TextMask.Text)
    strMask = StrConv(TextMask.Text, vbFromUnicode)
    'ReDim temByte(nLen)
    'temByte = vbNullString
    temByte() = strMask
    'Erase newNet.ucMaskIP
    CopyMemory VarPtr(newNet.ucMaskIP(0)), VarPtr(temByte(0)), nLen
    Dim i As Long

    nLen = Len(TextGate.Text)
    strGate = StrConv(TextGate.Text, vbFromUnicode)
    'ReDim temByte(nLen)
    'temByte = vbNullString
    temByte() = strGate
    'Erase newNet.ucGateIP
    CopyMemory VarPtr(newNet.ucGateIP(0)), VarPtr(temByte(0)), nLen
    
    
    'strMac = TextMAC.Text
    'Dim iLoop As Integer
    'Dim bResult() As Byte
    'ReDim bResult(Len(strMac) \ 2 - 1)
    'For iLoop = 0 To Len(strMac) \ 2 - 1
    '    bResult(iLoop) = Val("&H" & Mid(strMac, iLoop * 2 + 1, 2))
    'Next iLoop
    'CopyMemory VarPtr(newNet.ucMac(0)), VarPtr(bResult(0)), 12
    

    
    nRes = LPR_SetNetParams(connectedDev.pDevHandle, oldNet, newNet)
    If nRes <> 0 Then
        MsgBox "�޸��������ʧ�ܣ�����ֵ = " + CStr(nRes), 0, "��ʾ"
    Else
        MsgBox "�޸���������ɹ� ", 0, "��ʾ"
    End If
End Sub

