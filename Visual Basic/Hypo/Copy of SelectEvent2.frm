VERSION 5.00
Begin VB.Form SelectEvent 
   BackColor       =   &H00C0E0FF&
   ClientHeight    =   11115
   ClientLeft      =   60
   ClientTop       =   60
   ClientWidth     =   15240
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   11115
   ScaleWidth      =   15240
   StartUpPosition =   3  'Windows Default
   WindowState     =   2  'Maximized
   Begin VB.CommandButton cmdLecDown 
      Height          =   735
      Left            =   14040
      Picture         =   "SelectEvent2.frx":0000
      Style           =   1  'Graphical
      TabIndex        =   20
      Top             =   9240
      Width           =   855
   End
   Begin VB.CommandButton cmdLecUp 
      DisabledPicture =   "SelectEvent2.frx":06C2
      Height          =   735
      Left            =   14040
      Picture         =   "SelectEvent2.frx":0D84
      Style           =   1  'Graphical
      TabIndex        =   19
      Top             =   6840
      Width           =   855
   End
   Begin VB.CommandButton cmdLecRoom 
      Caption         =   "Command4"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   18
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Index           =   0
      Left            =   11400
      TabIndex        =   18
      Top             =   6840
      Width           =   2295
   End
   Begin VB.CommandButton cmdLecEnd 
      Caption         =   "Command3"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   18
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Index           =   0
      Left            =   9480
      TabIndex        =   17
      Top             =   6840
      Width           =   1935
   End
   Begin VB.CommandButton cmdLecStart 
      Caption         =   "Command2"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   18
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Index           =   0
      Left            =   7560
      TabIndex        =   16
      Top             =   6840
      Width           =   1935
   End
   Begin VB.CommandButton cmdLecTitel 
      Caption         =   "Command1"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   18
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Index           =   0
      Left            =   720
      TabIndex        =   15
      Top             =   6840
      Width           =   6975
   End
   Begin VB.CommandButton cmdEventDown 
      Height          =   735
      Left            =   14040
      Picture         =   "SelectEvent2.frx":1446
      Style           =   1  'Graphical
      TabIndex        =   9
      Top             =   3960
      Width           =   855
   End
   Begin VB.CommandButton cmdEventUp 
      DisabledPicture =   "SelectEvent2.frx":1B08
      Height          =   735
      Left            =   14040
      Picture         =   "SelectEvent2.frx":21CA
      Style           =   1  'Graphical
      TabIndex        =   8
      Top             =   1800
      Width           =   855
   End
   Begin VB.CommandButton cmdEventEnd 
      Caption         =   "Command3"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   20.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Index           =   0
      Left            =   10920
      TabIndex        =   7
      Top             =   1800
      Width           =   2775
   End
   Begin VB.CommandButton cmdEventStart 
      Caption         =   "Command2"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   20.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Index           =   0
      Left            =   8160
      TabIndex        =   6
      Top             =   1800
      Width           =   2775
   End
   Begin VB.CommandButton cmdEventTitel 
      Caption         =   "Command1"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   20.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Index           =   0
      Left            =   720
      TabIndex        =   5
      Top             =   1800
      Width           =   7455
   End
   Begin VB.CommandButton cmdShowPath 
      Caption         =   "Prikaži put do  sobe"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   24
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   2640
      TabIndex        =   1
      Top             =   10080
      Width           =   5175
   End
   Begin VB.CommandButton cmdEnd 
      Caption         =   "Kraj"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   24
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   9000
      TabIndex        =   0
      Top             =   10080
      Width           =   3015
   End
   Begin VB.Label labLecRoom 
      Alignment       =   2  'Center
      BackColor       =   &H00808000&
      Caption         =   "Soba"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   18
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   11520
      TabIndex        =   14
      Top             =   6000
      Width           =   2175
   End
   Begin VB.Label labLecTitel 
      Alignment       =   2  'Center
      BackColor       =   &H00808000&
      Caption         =   "Naziv lekcije"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   18
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   720
      TabIndex        =   13
      Top             =   6000
      Width           =   6855
   End
   Begin VB.Label labLecStart 
      Alignment       =   2  'Center
      BackColor       =   &H00808000&
      Caption         =   "Vrijeme poèetka"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   18
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   7560
      TabIndex        =   12
      Top             =   6000
      Width           =   1935
   End
   Begin VB.Label labLecEnd 
      Alignment       =   2  'Center
      BackColor       =   &H00808000&
      Caption         =   "Vrijeme završetka"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   18
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   9480
      TabIndex        =   11
      Top             =   6000
      Width           =   2055
   End
   Begin VB.Label Label1 
      BackColor       =   &H00C0E0FF&
      Caption         =   "Odaberite dogaðaj"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   26.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   120
      TabIndex        =   10
      Top             =   120
      Width           =   5655
   End
   Begin VB.Label labEventEnd 
      Alignment       =   2  'Center
      BackColor       =   &H00808000&
      Caption         =   "Datum završetka"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   18
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   10800
      TabIndex        =   4
      Top             =   1080
      Width           =   2895
   End
   Begin VB.Label labEventStart 
      Alignment       =   2  'Center
      BackColor       =   &H00808000&
      Caption         =   "Datum poèetka"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   18
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   7920
      TabIndex        =   3
      Top             =   1080
      Width           =   2895
   End
   Begin VB.Label labEventTitel 
      Alignment       =   2  'Center
      BackColor       =   &H00808000&
      Caption         =   "Naziv dogaðaja"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   18
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   720
      TabIndex        =   2
      Top             =   1080
      Width           =   7215
   End
End
Attribute VB_Name = "SelectEvent"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Base 0
Option Explicit

Dim arrEventNbr(100) As Integer
Dim arrEventTitel(100) As String
Dim arrStartDate(100) As String
Dim arrEndDate(100) As String
Dim TotalEventNum As Integer

Dim clsSelEvent As New Selector
Dim clsSelStartDate As New Selector
Dim clsSelEndDate As New Selector

Dim SelectedEvent As Integer

Private Sub Form_Load()
    
    Call SetLabel(cmdShowPath, "ShowPath")
    Call SetLabel(cmdEnd, "End")
    
    cmdShowPath.Enabled = False
    
    Call SetLabel(labEventTitel, "EventTitel")
    Call SetLabel(labEventStart, "StartDate")
    Call SetLabel(labEventEnd, "EndDate")
    
    Call SetLabel(labLecTitel, "LectureDesc")
    Call SetLabel(labLecStart, "StartTime")
    Call SetLabel(labLecEnd, "EndTime")
    Call SetLabel(labLecRoom, "Room")

    Dim cnn1 As adodb.Connection
    Set cnn1 = New adodb.Connection
    
    cnn1.ConnectionString = "DSN=Hypo"
    cnn1.Open
    
    Dim rs1 As New adodb.Recordset
    
    rs1.ActiveConnection = cnn1
    rs1.Source = "SELECT * FROM event WHERE date_from<" & AccessDate(Date) & " AND date_until>" & AccessDate(Date)
    rs1.CursorType = adOpenStatic
    rs1.CursorLocation = adUseClient
    rs1.LockType = adLockBatchOptimistic
    rs1.CacheSize = 10
    rs1.MaxRecords = 1000
    rs1.Open
    
    Dim I As Integer
    I = 1
    Do While Not rs1.EOF
        arrEventNbr(I) = rs1.Fields(0)
        arrEventTitel(I) = rs1.Fields(1)
        
        arrStartDate(I) = rs1.Fields(3)
        arrEndDate(I) = rs1.Fields(4)
        
        I = I + 1
        rs1.MoveNext
    Loop
    TotalEventNum = I
    
    Call clsSelEvent.InitializeButtons(4, I - 1, 1, arrEventTitel, cmdEventTitel)
    Call clsSelStartDate.InitializeButtons(4, I - 1, 1, arrStartDate, cmdEventStart)
    Call clsSelEndDate.InitializeButtons(4, I - 1, 1, arrEndDate, cmdEventEnd)
    
    rs1.Close
    cnn1.Close
End Sub

Private Sub cmdShowPath_Click()
    Dim RoomStr As String
    
    ShowPath.Show
    RoomStr = GridLecture.Columns(3).Value
    
    ShowPath.DrawPath (RoomStr)
    
    Unload Me
End Sub

Private Sub cmdEnd_Click()
    Unload Me
End Sub

Private Sub cmdEventEnd_Click(index As Integer)
    Call GetLectures(index)
End Sub

Private Sub cmdEventStart_Click(index As Integer)
    Call GetLectures(index)
End Sub

Private Sub cmdEventTitel_Click(index As Integer)
    Call GetLectures(index)
End Sub

Private Sub cmdEventUp_Click()
    Call clsSelEvent.MoveUp
    Call clsSelStartDate.MoveUp
    Call clsSelEndDate.MoveUp
End Sub

Private Sub cmdEventDown_Click()
    Call clsSelEvent.MoveDown
    Call clsSelStartDate.MoveDown
    Call clsSelEndDate.MoveDown
End Sub

Public Sub GetLectures(index As Integer)
    Dim str_lang As String
    
    Select Case Lang
        Case "GB"
            str_lang = "lec_eng"
        Case "IT"
            str_lang = "lec_ita"
        Case "AT"
            str_lang = "lec_aus"
        Case "HR"
            str_lang = "lec_cro"
        Case "SL"
            str_lang = "lec_slo"
    End Select

    Dim cnn1 As adodb.Connection
    Set cnn1 = New adodb.Connection
    
    cnn1.ConnectionString = "DSN=Hypo"
    cnn1.Open
    
    Dim rs1 As New adodb.Recordset
    
    rs1.ActiveConnection = cnn1
    rs1.Source = "SELECT * FROM lecture WHERE date_from<" & AccessDate(Date) & " AND date_until>" & AccessDate(Date)
    rs1.CursorType = adOpenStatic
    rs1.CursorLocation = adUseClient
    rs1.LockType = adLockBatchOptimistic
    rs1.CacheSize = 10
    rs1.MaxRecords = 1000
    rs1.Open
    
    Dim I As Integer
    I = 1
    Do While Not rs1.EOF
        arrEventNbr(I) = rs1.Fields(0)
        arrEventTitel(I) = rs1.Fields(1)
        
        arrStartDate(I) = rs1.Fields(3)
        arrEndDate(I) = rs1.Fields(4)
        
        I = I + 1
        rs1.MoveNext
    Loop
    TotalEventNum = I
End Sub
