Attribute VB_Name = "ModuleInfo"
Option Explicit

Public Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (ByVal pDest As Any, ByVal pSrc As Any, ByVal ByteLen As Long)
