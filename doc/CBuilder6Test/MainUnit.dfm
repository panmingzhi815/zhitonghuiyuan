object Form1: TForm1
  Left = -21
  Top = 74
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #27979#35797
  ClientHeight = 652
  ClientWidth = 1011
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
  object lbl1: TLabel
    Left = 620
    Top = 463
    Width = 46
    Height = 13
    Caption = #35774#22791'IP    '
  end
  object lbl2: TLabel
    Left = 620
    Top = 488
    Width = 60
    Height = 13
    Caption = #23376#32593#25513#30721'    '
  end
  object lbl3: TLabel
    Left = 620
    Top = 510
    Width = 57
    Height = 13
    Caption = #40664#35748#32593#20851'   '
  end
  object Label1: TLabel
    Left = 602
    Top = 423
    Width = 77
    Height = 13
    Caption = 'NTP'#26381#21153#22120'IP   '
  end
  object GroupBox1: TGroupBox
    Left = 6
    Top = 2
    Width = 563
    Height = 304
    Caption = #22823#22270
    TabOrder = 0
    object imgBigImg: TImage
      Left = 0
      Top = 16
      Width = 562
      Height = 287
      Center = True
      Stretch = True
    end
  end
  object GroupBox2: TGroupBox
    Left = 6
    Top = 313
    Width = 563
    Height = 248
    Caption = 'CIF'#22270
    TabOrder = 1
    object imgCIFImg: TImage
      Left = 0
      Top = 15
      Width = 562
      Height = 232
      Center = True
      Stretch = True
    end
  end
  object GroupBox3: TGroupBox
    Left = 6
    Top = 568
    Width = 281
    Height = 82
    Caption = #36710#29260#22270
    TabOrder = 2
    object imgPlateImg: TImage
      Left = 1
      Top = 14
      Width = 279
      Height = 67
      Center = True
      Stretch = True
    end
  end
  object GroupBox4: TGroupBox
    Left = 288
    Top = 568
    Width = 281
    Height = 82
    Caption = #36710#29260#21495
    TabOrder = 3
    object pnlPlateNo: TPanel
      Left = 1
      Top = 14
      Width = 279
      Height = 67
      TabOrder = 0
    end
  end
  object GroupBox5: TGroupBox
    Left = 574
    Top = 2
    Width = 432
    Height = 149
    Caption = #35774#22791#21015#34920
    TabOrder = 4
    object lvDevList: TListView
      Left = 9
      Top = 16
      Width = 413
      Height = 123
      Columns = <>
      TabOrder = 0
    end
  end
  object GroupBox6: TGroupBox
    Left = 574
    Top = 158
    Width = 432
    Height = 148
    Caption = #24050#36830#25509#35774#22791
    TabOrder = 5
    object tvConnectDev: TTreeView
      Left = 9
      Top = 16
      Width = 413
      Height = 123
      Indent = 19
      TabOrder = 0
      OnClick = tvConnectDevClick
    end
  end
  object btnInit: TButton
    Left = 621
    Top = 328
    Width = 75
    Height = 23
    Caption = #21021#22987#21270
    TabOrder = 6
    OnClick = btnInitClick
  end
  object btnQuit: TButton
    Left = 704
    Top = 328
    Width = 74
    Height = 23
    Caption = #36864#20986
    TabOrder = 7
    OnClick = btnQuitClick
  end
  object btnScanDev: TButton
    Left = 812
    Top = 328
    Width = 157
    Height = 23
    Caption = #25195#25551#35774#22791
    TabOrder = 8
    OnClick = btnScanDevClick
  end
  object btnConn: TButton
    Left = 812
    Top = 359
    Width = 74
    Height = 23
    Caption = #36830#25509#35774#22791
    TabOrder = 9
    OnClick = btnConnClick
  end
  object btnDisConn: TButton
    Left = 895
    Top = 359
    Width = 74
    Height = 23
    Caption = #26029#24320#35774#22791
    TabOrder = 10
    OnClick = btnDisConnClick
  end
  object btnTrigger: TButton
    Left = 812
    Top = 390
    Width = 157
    Height = 23
    Caption = #27169#25311#35302#21457
    TabOrder = 11
    OnClick = btnTriggerClick
  end
  object btnBlockTrigger: TButton
    Left = 812
    Top = 421
    Width = 157
    Height = 23
    Caption = #38459#22622#27169#25311#35302#21457
    TabOrder = 12
    OnClick = btnBlockTriggerClick
  end
  object btnStatus: TButton
    Left = 812
    Top = 516
    Width = 157
    Height = 23
    Caption = #26816#27979#29366#24577
    TabOrder = 13
    OnClick = btnStatusClick
  end
  object btnNativeJustTime: TButton
    Left = 812
    Top = 547
    Width = 157
    Height = 23
    Caption = #26412#22320#31995#32479#26102#38388#26657#26102
    TabOrder = 14
    OnClick = btnNativeJustTimeClick
  end
  object edtStatus: TEdit
    Left = 812
    Top = 497
    Width = 158
    Height = 21
    TabOrder = 15
  end
  object chkWriteLog: TCheckBox
    Left = 629
    Top = 369
    Width = 65
    Height = 15
    Caption = #20889#26085#24535'   '
    TabOrder = 16
    OnClick = chkWriteLogClick
  end
  object chkNTPJustTime: TCheckBox
    Left = 681
    Top = 401
    Width = 72
    Height = 15
    Caption = 'NTP'#26657#26102
    TabOrder = 17
    OnClick = chkNTPJustTimeClick
  end
  object btnGetVersionInfo: TButton
    Left = 617
    Top = 609
    Width = 355
    Height = 23
    Caption = #33719#21462#29256#26412#20449#24687
    TabOrder = 18
    OnClick = btnGetVersionInfoClick
  end
  object edtVersionInfo: TEdit
    Left = 617
    Top = 591
    Width = 355
    Height = 21
    TabOrder = 19
  end
  object edtMask: TEdit
    Left = 681
    Top = 482
    Width = 96
    Height = 21
    TabOrder = 20
  end
  object edtDevIP: TEdit
    Left = 681
    Top = 459
    Width = 96
    Height = 21
    TabOrder = 21
  end
  object edtGate: TEdit
    Left = 681
    Top = 505
    Width = 96
    Height = 21
    TabOrder = 22
  end
  object btnModify: TButton
    Left = 681
    Top = 526
    Width = 95
    Height = 23
    Caption = #20462#25913
    TabOrder = 23
    OnClick = btnModifyClick
  end
  object edtNTPIP: TEdit
    Left = 681
    Top = 419
    Width = 96
    Height = 21
    TabOrder = 24
  end
end
