VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmVisor 
   Caption         =   "QC Binary"
   ClientHeight    =   2175
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6975
   LinkTopic       =   "Form1"
   ScaleHeight     =   2175
   ScaleWidth      =   6975
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox Text1 
      Height          =   285
      Left            =   840
      TabIndex        =   8
      Text            =   "1"
      Top             =   1560
      Width           =   375
   End
   Begin VB.CommandButton Command3 
      Caption         =   "&Send"
      Height          =   495
      Left            =   4320
      TabIndex        =   5
      Top             =   1560
      Width           =   1215
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   3720
      Top             =   1560
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      DefaultExt      =   "tga"
   End
   Begin VB.CommandButton Command2 
      Caption         =   "&Quit"
      Height          =   495
      Left            =   5640
      TabIndex        =   3
      Top             =   1560
      Width           =   1215
   End
   Begin VB.Frame RCX 
      Caption         =   " RCX "
      Height          =   1335
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   6735
      Begin VB.CommandButton Command1 
         Caption         =   "&Load"
         Height          =   495
         Left            =   120
         TabIndex        =   2
         Top             =   240
         Width           =   1215
      End
      Begin MSComctlLib.ProgressBar ProgressBar1 
         Height          =   135
         Left            =   120
         TabIndex        =   4
         Top             =   960
         Width           =   6495
         _ExtentX        =   11456
         _ExtentY        =   238
         _Version        =   393216
         Appearance      =   1
      End
      Begin VB.Label Label2 
         Caption         =   "..."
         Height          =   255
         Left            =   5400
         TabIndex        =   6
         Top             =   360
         Width           =   1215
      End
      Begin VB.Label Label1 
         Caption         =   "..."
         Height          =   255
         Left            =   1440
         TabIndex        =   1
         Top             =   360
         Width           =   1215
      End
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   3000
      Top             =   1560
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
      BaudRate        =   2400
   End
   Begin VB.Label Label3 
      Caption         =   "COM Port"
      Height          =   255
      Left            =   120
      TabIndex        =   7
      Top             =   1560
      Width           =   855
   End
End
Attribute VB_Name = "frmVisor"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Type Targa
    dummy1 As Integer
    type As Byte
    dummy2(8) As Byte
    dx As Integer
    dy As Integer
    planes As Byte
    dummy3 As Byte
End Type


Private Sub Command1_Click()
    Dim data() As Byte
    Dim header As Targa
    Dim x As Integer, y As Integer, i As Integer, j As Integer
    Dim nonfine As Integer
        
    CommonDialog1.ShowSave
    Open CommonDialog1.FileName For Binary Access Write As #1
        
    MSComm1.CommPort = 1
    MSComm1.InputLen = 0
    MSComm1.InputMode = comInputModeBinary
    MSComm1.PortOpen = True
    
    ' ******************* Header
    MSComm1.Output = "k"
    Do While MSComm1.InBufferCount < 3
        DoEvents
    Loop
    data = MSComm1.Input
    x = data(1)
    y = data(2)
    
    ' ********************* Scrivi l'header
    header.planes = 24
    header.type = 2
    header.dx = x
    header.dy = y
    Put #1, , header
    
    Label1 = "Dim: " & x & "x" & y
    ' ******************** data
    For j = 0 To y - 1
        ProgressBar1.Value = (j + 1) * 100 / y
        Label2 = "" & j & "/" & (y - 1)
        MSComm1.Output = "k"
        If j = y - 1 Then
            nonfine = 0
        Else
            nonfine = 1
        End If
        Do While MSComm1.InBufferCount < x + nonfine
            DoEvents
        Loop
        data = MSComm1.Input
        For i = 0 To x + nonfine - 2
            Put #1, , data(i + 1)
            Put #1, , data(i + 1)
            Put #1, , data(i + 1)
        Next i
    Next j
    MSComm1.Output = "k"
    Label1 = "Ok."
    MsgBox "Image written to disk"
    MSComm1.PortOpen = False
    Close #1
End Sub


Private Sub Command2_Click()
    Unload Me
End Sub

Private Sub Command3_Click()
    MSComm1.PortOpen = True
    MSComm1.Output = "k"
    MSComm1.PortOpen = False
End Sub

Private Sub Text1_Change()
    MSComm1.CommPort = Text1
End Sub
