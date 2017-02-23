VERSION 5.00
Begin VB.Form SelectLanguage 
   BackColor       =   &H00C0E0FF&
   ClientHeight    =   11115
   ClientLeft      =   60
   ClientTop       =   60
   ClientWidth     =   15240
   ControlBox      =   0   'False
   FillColor       =   &H00FFC0C0&
   LinkTopic       =   "Form1"
   ScaleHeight     =   11115
   ScaleWidth      =   15240
   StartUpPosition =   3  'Windows-Standard
   WindowState     =   2  'Maximiert
   Begin VB.Timer Timer1 
      Interval        =   1000
      Left            =   1080
      Top             =   1920
   End
   Begin VB.CommandButton PickSloLang 
      Caption         =   "Slovenski"
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   35.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   975
      Left            =   6240
      TabIndex        =   5
      Top             =   9360
      Width           =   8000
   End
   Begin VB.CommandButton PickCroLang 
      Caption         =   "Hrvatski"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   35.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   975
      Left            =   5400
      TabIndex        =   4
      Top             =   7680
      Width           =   8000
   End
   Begin VB.CommandButton PickItaLang 
      Caption         =   "Italiano"
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   35.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   975
      Left            =   4560
      TabIndex        =   3
      Top             =   6000
      Width           =   8000
   End
   Begin VB.CommandButton PickAusLang 
      Caption         =   "Deutsch"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   35.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   975
      Left            =   3720
      TabIndex        =   2
      Top             =   4320
      Width           =   8000
   End
   Begin VB.CommandButton PickEngLang 
      BackColor       =   &H0000FFFF&
      Caption         =   "English"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   35.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   975
      Left            =   2880
      MaskColor       =   &H00C0E0FF&
      TabIndex        =   1
      Top             =   2640
      Width           =   8000
   End
   Begin VB.Image Image5 
      Height          =   960
      Left            =   3720
      Picture         =   "SelectLanguage.frx":0000
      Top             =   9360
      Width           =   1920
   End
   Begin VB.Image Image4 
      Height          =   960
      Left            =   2880
      Picture         =   "SelectLanguage.frx":0513
      Top             =   7680
      Width           =   1920
   End
   Begin VB.Image Image3 
      Height          =   960
      Left            =   2040
      Picture         =   "SelectLanguage.frx":0A9A
      Top             =   6000
      Width           =   1920
   End
   Begin VB.Image Image2 
      Height          =   960
      Left            =   360
      Picture         =   "SelectLanguage.frx":0F8F
      Top             =   2640
      Width           =   1920
   End
   Begin VB.Image Image1 
      Height          =   960
      Left            =   1200
      Picture         =   "SelectLanguage.frx":163E
      Top             =   4320
      Width           =   1935
   End
   Begin VB.Label LabelAut 
      BackColor       =   &H00C0E0FF&
      Caption         =   "Sprache auswählen"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   30
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   735
      Left            =   4320
      TabIndex        =   9
      Top             =   700
      Width           =   4695
   End
   Begin VB.Label LabelSlo 
      BackColor       =   &H00C0E0FF&
      Caption         =   "Odaberite jezik"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   30
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   735
      Left            =   18420
      TabIndex        =   8
      Top             =   700
      Width           =   3855
   End
   Begin VB.Label LabelIta 
      BackColor       =   &H00C0E0FF&
      Caption         =   "Selezionare la lingua"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   30
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   855
      Left            =   9240
      TabIndex        =   7
      Top             =   700
      Width           =   5055
   End
   Begin VB.Label LabelCro 
      BackColor       =   &H00C0E0FF&
      Caption         =   "Odaberite jezik"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   30
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   855
      Left            =   14520
      TabIndex        =   6
      Top             =   700
      Width           =   3735
   End
   Begin VB.Label LabelEng 
      BackColor       =   &H00C0E0FF&
      Caption         =   "Select language"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   30
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   855
      Left            =   240
      TabIndex        =   0
      Top             =   700
      Width           =   3780
   End
End
Attribute VB_Name = "SelectLanguage"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Command1_Click()
    Unload Me
End Sub

Private Sub Form_Activate()
    Timer1.Enabled = True
End Sub

Private Sub Form_Load()
    Timer1.Enabled = True
    Timer1.Interval = 50
        
    cnn.ConnectionString = "DSN=Hypo;"
    cnn.Open
    
    Set cnnLing = New adodb.Connection
    cnnLing.ConnectionString = "DSN=Hypo"
    cnnLing.CursorLocation = adUseClient
    cnnLing.Open
    
    ' Open command object
    Set cmdGetLabel = New adodb.Command
    
    cmdGetLabel.ActiveConnection = cnnLing
    cmdGetLabel.CommandText = "SELECT label FROM labels WHERE language_nbr=? AND name_nbr=?"
    cmdGetLabel.CommandType = adCmdText
    
    Set prmGetLabelLang = cmdGetLabel.CreateParameter(, adBSTR, adParamInput, 4)
    prmGetLabelLang.Value = "IT"
    cmdGetLabel.Parameters.Append prmGetLabelLang
    
    Set prmGetLabelLabID = cmdGetLabel.CreateParameter(, adBSTR, adParamInput, 35)
    prmGetLabelLabID.Value = ""
    cmdGetLabel.Parameters.Append prmGetLabelLabID
    
    Call InitData
    
    ' open table 'Room' from databse and get data about employees
    cnnRoom.ConnectionString = "DSN=Hypo;"
    cnnRoom.Open
    
    rstRoom.ActiveConnection = cnnRoom
    rstRoom.Source = "SELECT * FROM Room"
    rstRoom.CursorType = adOpenStatic
    rstRoom.CursorLocation = adUseClient
    rstRoom.LockType = adLockBatchOptimistic
    rstRoom.CacheSize = 10
    rstRoom.MaxRecords = 1000
    rstRoom.Open
End Sub

Private Sub PickEngLang_Click()
    Lang = "GB"
    Timer1.Enabled = False
    ActionSelection.Show
End Sub

Private Sub PickAusLang_Click()
    Lang = "AT"
    Timer1.Enabled = False
    ActionSelection.Show
End Sub

Private Sub PickItaLang_Click()
    Lang = "IT"
    Timer1.Enabled = False
    ActionSelection.Show
End Sub

Private Sub PickCroLang_Click()
    Lang = "HR"
    Timer1.Enabled = False
    ActionSelection.Show
End Sub

Private Sub PickSloLang_Click()
    Lang = "SL"
    Timer1.Enabled = False
    ActionSelection.Show
End Sub

Private Sub Timer1_Timer()
    Dim Step As Integer
    Step = 50
    
    LabelEng.Left = LabelEng.Left - Step
    LabelAut.Left = LabelAut.Left - Step
    LabelIta.Left = LabelIta.Left - Step
    LabelCro.Left = LabelCro.Left - Step
    LabelSlo.Left = LabelSlo.Left - Step
    
    If LabelEng.Left < -LabelEng.Width Then
        LabelEng.Left = LabelSlo.Left + LabelSlo.Width + 300
    End If
    If LabelAut.Left < -LabelAut.Width Then
        LabelAut.Left = LabelEng.Left + LabelEng.Width + 300
    End If
    If LabelIta.Left < -LabelIta.Width Then
        LabelIta.Left = LabelAut.Left + LabelAut.Width + 300
    End If
    If LabelCro.Left < -LabelCro.Width Then
        LabelCro.Left = LabelIta.Left + LabelIta.Width + 300
    End If
    If LabelSlo.Left < -LabelSlo.Width Then
        LabelSlo.Left = LabelCro.Left + LabelCro.Width + 300
    End If
End Sub
