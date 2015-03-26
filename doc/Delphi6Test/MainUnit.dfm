object Form1: TForm1
  Left = 47
  Top = 118
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #27979#35797
  ClientHeight = 653
  ClientWidth = 1013
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object ImagePlateNo: TImage
    Left = 0
    Top = 0
    Width = 1013
    Height = 653
    Align = alClient
    Stretch = True
  end
  object lblIP: TLabel
    Left = 613
    Top = 476
    Width = 46
    Height = 13
    Caption = #35774#22791'IP    '
  end
  object lblMask: TLabel
    Left = 613
    Top = 500
    Width = 60
    Height = 13
    Caption = #23376#32593#25513#30721'    '
  end
  object lblGate: TLabel
    Left = 613
    Top = 524
    Width = 57
    Height = 13
    Caption = #40664#35748#32593#20851'   '
  end
  object Label1: TLabel
    Left = 593
    Top = 427
    Width = 74
    Height = 13
    Caption = 'NTP'#26381#21153#22120'IP  '
  end
  object GroupBox3: TGroupBox
    Left = 5
    Top = 568
    Width = 282
    Height = 81
    Caption = #36710#29260#22270
    TabOrder = 0
    object ImagePlate: TImage
      Left = 2
      Top = 15
      Width = 278
      Height = 64
      Align = alClient
      Stretch = True
    end
  end
  object GroupBox2: TGroupBox
    Left = 5
    Top = 0
    Width = 568
    Height = 305
    Caption = #22823#22270
    TabOrder = 1
    object ImageBig: TImage
      Left = 2
      Top = 15
      Width = 564
      Height = 288
      Align = alClient
      AutoSize = True
      Center = True
      Stretch = True
    end
  end
  object GroupBox1: TGroupBox
    Left = 5
    Top = 312
    Width = 568
    Height = 249
    Caption = 'CIF'#22270
    TabOrder = 2
    object ImageCif: TImage
      Left = 2
      Top = 15
      Width = 564
      Height = 232
      Align = alClient
      Stretch = True
    end
  end
  object GroupBox4: TGroupBox
    Left = 288
    Top = 568
    Width = 285
    Height = 81
    Caption = #36710#29260#21495#30721
    TabOrder = 3
  end
  object GroupBox5: TGroupBox
    Left = 578
    Top = 0
    Width = 431
    Height = 153
    Caption = #35774#22791#21015#34920
    TabOrder = 4
    object ListViewDevList: TListView
      Left = 8
      Top = 16
      Width = 409
      Height = 129
      Columns = <>
      ReadOnly = True
      TabOrder = 0
      ViewStyle = vsReport
    end
  end
  object GroupBox6: TGroupBox
    Left = 578
    Top = 160
    Width = 431
    Height = 145
    Caption = #24050#36830#25509#35774#22791
    TabOrder = 5
  end
  object ButtonInitSDK: TButton
    Left = 615
    Top = 328
    Width = 79
    Height = 25
    Caption = #21021#22987#21270
    TabOrder = 6
    OnClick = ButtonInitSDKClick
  end
  object ButtonQuitSDK: TButton
    Left = 700
    Top = 328
    Width = 79
    Height = 25
    Caption = #36864#20986
    TabOrder = 7
    OnClick = ButtonQuitSDKClick
  end
  object ButtonScanDev: TButton
    Left = 819
    Top = 328
    Width = 163
    Height = 25
    Caption = #25195#25551#35774#22791
    TabOrder = 8
    OnClick = ButtonScanDevClick
  end
  object ButtonConnectDev: TButton
    Left = 819
    Top = 366
    Width = 79
    Height = 25
    Caption = #36830#25509#35774#22791
    TabOrder = 9
    OnClick = ButtonConnectDevClick
  end
  object ButtonDisConnectDev: TButton
    Left = 904
    Top = 366
    Width = 78
    Height = 25
    Caption = #26029#24320#35774#22791
    TabOrder = 10
    OnClick = ButtonDisConnectDevClick
  end
  object TreeViewConnectedDev: TTreeView
    Left = 586
    Top = 176
    Width = 415
    Height = 121
    Indent = 19
    ReadOnly = True
    TabOrder = 11
    OnClick = TreeViewConnectedDevClick
  end
  object ButtonTrigger: TButton
    Left = 819
    Top = 401
    Width = 163
    Height = 25
    Caption = #27169#25311#35302#21457
    TabOrder = 12
    OnClick = ButtonTriggerClick
  end
  object ButtonBlockTrigger: TButton
    Left = 819
    Top = 435
    Width = 163
    Height = 26
    Caption = #38459#22622#27169#25311#35302#21457
    TabOrder = 13
    OnClick = ButtonBlockTriggerClick
  end
  object PlateNo: TPanel
    Left = 289
    Top = 583
    Width = 283
    Height = 65
    Caption = #12289
    TabOrder = 14
  end
  object chkWriteLog: TCheckBox
    Left = 615
    Top = 376
    Width = 58
    Height = 25
    Caption = #20889#26085#24535
    TabOrder = 15
    OnClick = chkWriteLogClick
  end
  object edtStatusInfo: TEdit
    Left = 819
    Top = 484
    Width = 161
    Height = 21
    TabOrder = 16
  end
  object btnCheckStatus: TButton
    Left = 819
    Top = 505
    Width = 161
    Height = 25
    Caption = #26816#27979#29366#24577
    TabOrder = 17
    OnClick = btnCheckStatusClick
  end
  object btnAdjustTime: TButton
    Left = 819
    Top = 541
    Width = 161
    Height = 25
    Caption = #26412#22320#31995#32479#26102#38388#26657#26102
    TabOrder = 18
    OnClick = btnAdjustTimeClick
  end
  object chkEnableNTP: TCheckBox
    Left = 675
    Top = 406
    Width = 104
    Height = 13
    Caption = #21551#29992'NTP'#26657#26102
    TabOrder = 19
    OnClick = chkEnableNTPClick
  end
  object edtDSPMain: TEdit
    Left = 601
    Top = 588
    Width = 379
    Height = 21
    TabOrder = 20
  end
  object btnGetVersionInfo: TButton
    Left = 601
    Top = 609
    Width = 379
    Height = 25
    Caption = #33719#21462#29256#26412#20449#24687
    TabOrder = 21
    OnClick = btnGetVersionInfoClick
  end
  object edtIP: TEdit
    Left = 675
    Top = 472
    Width = 104
    Height = 21
    TabOrder = 22
  end
  object edtMask: TEdit
    Left = 675
    Top = 496
    Width = 104
    Height = 21
    TabOrder = 23
  end
  object edtGate: TEdit
    Left = 675
    Top = 520
    Width = 104
    Height = 21
    TabOrder = 24
  end
  object btnSetup: TButton
    Left = 675
    Top = 541
    Width = 103
    Height = 25
    Caption = #20462#25913
    TabOrder = 25
    OnClick = btnSetupClick
  end
  object edtNTPIP: TEdit
    Left = 675
    Top = 424
    Width = 104
    Height = 21
    TabOrder = 26
  end
end
