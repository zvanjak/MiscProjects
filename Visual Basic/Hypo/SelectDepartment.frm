VERSION 5.00
Begin VB.Form SelectDepartment 
   BackColor       =   &H00C0E0FF&
   ClientHeight    =   11325
   ClientLeft      =   60
   ClientTop       =   60
   ClientWidth     =   15240
   ControlBox      =   0   'False
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   11325
   ScaleWidth      =   15240
   StartUpPosition =   3  'Windows Default
   WindowState     =   2  'Maximized
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   30000
      Left            =   7320
      Top             =   360
   End
   Begin VB.CommandButton cmdKeyEmp 
      Caption         =   "A"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   21.75
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Index           =   0
      Left            =   10560
      TabIndex        =   11
      Top             =   5640
      Width           =   615
   End
   Begin VB.CommandButton cmdKeyDep 
      Caption         =   "A"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   21.75
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   555
      Index           =   0
      Left            =   10560
      TabIndex        =   10
      Top             =   1200
      Width           =   615
   End
   Begin VB.CommandButton cmdDepDown 
      Height          =   735
      Left            =   8880
      Picture         =   "SelectDepartment.frx":0000
      Style           =   1  'Graphical
      TabIndex        =   9
      Top             =   2640
      Width           =   855
   End
   Begin VB.CommandButton cmdDepUp 
      DisabledPicture =   "SelectDepartment.frx":06C2
      Height          =   735
      Left            =   8880
      Picture         =   "SelectDepartment.frx":0D84
      Style           =   1  'Graphical
      TabIndex        =   8
      Top             =   1200
      Width           =   855
   End
   Begin VB.CommandButton cmdEmpDown 
      Height          =   735
      Left            =   8880
      Picture         =   "SelectDepartment.frx":1446
      Style           =   1  'Graphical
      TabIndex        =   7
      Top             =   8600
      Width           =   855
   End
   Begin VB.CommandButton cmdEmpUp 
      Height          =   735
      Left            =   8880
      Picture         =   "SelectDepartment.frx":1B08
      Style           =   1  'Graphical
      TabIndex        =   6
      Top             =   5640
      Width           =   855
   End
   Begin VB.CommandButton cmdEmp 
      BackColor       =   &H0080C0FF&
      Caption         =   "Command1"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   21.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Index           =   0
      Left            =   240
      MaskColor       =   &H0080FFFF&
      TabIndex        =   5
      Top             =   5640
      UseMaskColor    =   -1  'True
      Width           =   8295
   End
   Begin VB.CommandButton cmdDep 
      Caption         =   "Command1"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   21.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Index           =   0
      Left            =   240
      TabIndex        =   4
      Top             =   1200
      Width           =   8295
   End
   Begin VB.CommandButton SelDepShowPath 
      Caption         =   "Show path"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   36
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Left            =   1560
      TabIndex        =   3
      Top             =   10320
      Width           =   6975
   End
   Begin VB.CommandButton SelDepEnd 
      Caption         =   "Kraj"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   36
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Left            =   8880
      TabIndex        =   2
      Top             =   10320
      Width           =   3855
   End
   Begin VB.Label labFirstLetterDep 
      BackColor       =   &H00C0E0FF&
      Caption         =   "First letter of department name"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   10560
      TabIndex        =   13
      Top             =   480
      Width           =   4575
   End
   Begin VB.Label labFirstLetterEmp 
      BackColor       =   &H00C0E0FF&
      Caption         =   "First letter of surname"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   10560
      TabIndex        =   12
      Top             =   5040
      Width           =   4575
   End
   Begin VB.Label SelDepPickEmp 
      BackColor       =   &H00C0E0FF&
      Caption         =   "Odaberite zaposlenika"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   27.75
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   120
      TabIndex        =   1
      Top             =   4680
      Width           =   6495
   End
   Begin VB.Label SelDepPickDep 
      BackColor       =   &H00C0E0FF&
      Caption         =   "Odaberite odjel"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   27.75
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   6135
   End
End
Attribute VB_Name = "SelectDepartment"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Option Base 0

Dim RoomNum(100) As String

Dim arrEmpNames(100) As String
Dim CurrentEmpNum As Integer

Dim arrDepNames(100) As String
Dim arrDepNum(100) As Integer
Dim TotalDepNum As Integer

Dim SelectedRoom As String

Dim clsSelEmp As New Selector
Dim clsSelDep As New Selector


Private Sub Form_Load()
    Dim i As Integer
    Dim str_lang As String
    Dim str As String
    Dim arr(5) As String
    
    Call RestartTimer
    
    Call SetLabel(SelDepPickEmp, "SelDepPickEmp")
    Call SetLabel(SelDepPickDep, "SelDepPickDep")
    Call SetLabel(SelDepEnd, "End")
    Call SetLabel(SelDepShowPath, "ShowPath")
    Call SetLabel(labFirstLetterDep, "FirstLetterDep")
    Call SetLabel(labFirstLetterEmp, "FirstLetterEmp")
    
    SelDepShowPath.Enabled = False
    CurrentEmpNum = 0
    
    Select Case Lang
        Case "GB"
            str_lang = "dep_eng"
        Case "IT"
            str_lang = "dep_ita"
        Case "AT"
            str_lang = "dep_aus"
        Case "HR"
            str_lang = "dep_cro"
        Case "SL"
            str_lang = "dep_slo"
    End Select
    
'    DBListDep.ListField = str_lang
    
    arr(1) = " "
    arr(2) = " "
    arr(3) = " "
    arr(4) = " "
    arr(5) = " "
    Call clsSelEmp.InitializeButtons(5, 5, 1, arr, cmdEmp)
    
    Dim cnn1 As adodb.Connection
    Set cnn1 = New adodb.Connection
    
    cnn1.ConnectionString = "DSN=Hypo"
    cnn1.Open
    
    Dim rs1 As New adodb.Recordset
    
    rs1.ActiveConnection = cnn1
    rs1.Source = "SELECT dep_nbr," & str_lang & " FROM department ORDER BY " & str_lang
    
    rs1.CursorType = adOpenStatic
    rs1.CursorLocation = adUseClient
    rs1.LockType = adLockBatchOptimistic
    rs1.CacheSize = 10
    rs1.MaxRecords = 1000
    rs1.Open
    
    i = 1
    Do While Not rs1.EOF
        arrDepNum(i) = rs1.Fields(0)
        arrDepNames(i) = rs1.Fields(1)
        i = i + 1
        
        rs1.MoveNext
    Loop
    TotalDepNum = i
    
    Call clsSelDep.InitializeButtons(3, i - 1, 1, arrDepNames, cmdDep)
    
    SelDepShowPath.Enabled = False
    
    rs1.Close
    cnn1.Close
    
    str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    Call ShowScreenKeyboard(cmdKeyDep(0).Top, cmdKeyDep(0).Left, cmdKeyDep(0).Width, cmdKeyDep(0).Height, 100, 100, 6, str, cmdKeyDep)
    Call ShowScreenKeyboard(cmdKeyEmp(0).Top, cmdKeyEmp(0).Left, cmdKeyEmp(0).Width, cmdKeyEmp(0).Height, 100, 100, 6, str, cmdKeyEmp)
End Sub

Private Sub cmdDep_Click(Index As Integer)
    Dim indDep As Integer
    Dim cnn1 As adodb.Connection
    Dim rs1 As New adodb.Recordset
    
    Set cnn1 = New adodb.Connection
    cnn1.ConnectionString = "DSN=Hypo"
    cnn1.Open
    
    rs1.ActiveConnection = cnn1
    indDep = Index + clsSelDep.GetStartIndex - 1
    rs1.Source = "SELECT * FROM employee WHERE dep_nbr=" & arrDepNum(indDep) & " ORDER BY surname"
    
    rs1.CursorType = adOpenStatic
    rs1.CursorLocation = adUseClient
    rs1.LockType = adLockBatchOptimistic
    rs1.CacheSize = 10
    rs1.MaxRecords = 1000
    rs1.Open
    
    Dim i As Integer
    i = 1
    Do While Not rs1.EOF
        RoomNum(i) = rs1.Fields(7)  ' da zapamtimo tko je u kojoj sobi
        arrEmpNames(i) = rs1.Fields(1) & " " & rs1.Fields(2)
        i = i + 1
        
        rs1.MoveNext
    Loop
    CurrentEmpNum = i
    
    ' ukoliko nije bilo dovoljno (5) zaposlenika na tom odjelu, onda ostala mjesta popuni prazninama
    Dim j As Integer
    For j = i To 5
        arrEmpNames(j) = " "
    Next j
    
    Call clsSelEmp.ChangeCaptions(5, i - 1, 1, arrEmpNames, cmdEmp)
    
    SelDepShowPath.Enabled = False
    
    rs1.Close
    cnn1.Close
    
    Call RestartTimer
End Sub

Private Sub cmdEmp_Click(Index As Integer)
    Dim num As Integer
    
    If Index < CurrentEmpNum Then
        SelDepShowPath.Enabled = True
    
        num = Index + clsSelEmp.GetStartIndex() - 1
        SelectedRoom = RoomNum(num)
    End If
    
    Call RestartTimer
End Sub

Private Sub cmdDepDown_Click()
    Call clsSelDep.MoveDown
    
    SelDepShowPath.Enabled = False
    
    Call RestartTimer
End Sub

Private Sub cmdDepUp_Click()
    Call clsSelDep.MoveUp

    SelDepShowPath.Enabled = False

    Call RestartTimer
End Sub

Private Sub cmdEmpDown_Click()
    Call clsSelEmp.MoveDown

    SelDepShowPath.Enabled = False

    Call RestartTimer
End Sub

Private Sub cmdEmpUp_Click()
    Call clsSelEmp.MoveUp

    SelDepShowPath.Enabled = False

    Call RestartTimer
End Sub

Private Sub SelDepEnd_Click()
    Unload Me
End Sub

Private Sub SelDepShowPath_Click()
    ShowPath.Show
    ShowPath.DrawPath (SelectedRoom)
    
    Unload Me
End Sub

Private Sub cmdKeyDep_Click(Index As Integer)
    Dim i As Integer
    
    SelDepShowPath.Enabled = False
    For i = 1 To TotalDepNum
        If UCase(Mid(arrDepNames(i), 1, 1)) >= UCase(cmdKeyDep(Index).Caption) Then
            clsSelDep.SetStart (i)
            Call RestartTimer
            Exit Sub
        End If
    Next i

    Call RestartTimer
End Sub

Private Sub cmdKeyEmp_Click(Index As Integer)
    Dim i As Integer
    
    SelDepShowPath.Enabled = False
    For i = 1 To CurrentEmpNum
        If UCase(Mid(arrEmpNames(i), 1, 1)) >= UCase(cmdKeyEmp(Index).Caption) Then
            clsSelEmp.SetStart (i)
            Call RestartTimer
            Exit Sub
        End If
    Next i

    Call RestartTimer
End Sub

Private Sub Timer1_Timer()
    Unload Me
End Sub

Public Sub RestartTimer()
    Timer1.Enabled = False
    Timer1.Interval = TIMER_INT
    Timer1.Enabled = True
End Sub
