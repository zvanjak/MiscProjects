VERSION 5.00
Begin VB.Form SelectRoom 
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
   Begin VB.CommandButton cmdSelFloor 
      Caption         =   "4. floor"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   20.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Index           =   4
      Left            =   11040
      TabIndex        =   11
      Top             =   6840
      Width           =   3855
   End
   Begin VB.CommandButton cmdSelFloor 
      Caption         =   "3. floor"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   20.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Index           =   3
      Left            =   11040
      TabIndex        =   10
      Top             =   5520
      Width           =   3855
   End
   Begin VB.CommandButton cmdSelFloor 
      Caption         =   "2. floor"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   20.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Index           =   2
      Left            =   11040
      TabIndex        =   9
      Top             =   4320
      Width           =   3855
   End
   Begin VB.CommandButton cmdSelFloor 
      Caption         =   "1. floor"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   20.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Index           =   1
      Left            =   11040
      TabIndex        =   8
      Top             =   3120
      Width           =   3855
   End
   Begin VB.CommandButton cmdSelFloor 
      Caption         =   "0. floor"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   20.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Index           =   0
      Left            =   11040
      TabIndex        =   7
      Top             =   1920
      Width           =   3855
   End
   Begin VB.CommandButton cmdRoomDown 
      Height          =   735
      Left            =   9480
      Picture         =   "SelectRoom.frx":0000
      Style           =   1  'Graphical
      TabIndex        =   5
      Top             =   8520
      Width           =   855
   End
   Begin VB.CommandButton cmdRoomUp 
      DisabledPicture =   "SelectRoom.frx":06C2
      Height          =   735
      Left            =   9480
      Picture         =   "SelectRoom.frx":0D84
      Style           =   1  'Graphical
      TabIndex        =   4
      Top             =   1920
      Width           =   855
   End
   Begin VB.CommandButton cmdRoom 
      BeginProperty Font 
         Name            =   "Courier New"
         Size            =   20.25
         Charset         =   238
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Index           =   0
      Left            =   720
      TabIndex        =   2
      Top             =   1920
      Width           =   8175
   End
   Begin VB.CommandButton cmdShowPath 
      Caption         =   "Show Path"
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
      Left            =   1800
      TabIndex        =   1
      Top             =   9960
      Width           =   5295
   End
   Begin VB.CommandButton cmdEnd 
      Caption         =   "End"
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
      Left            =   8520
      TabIndex        =   0
      Top             =   9960
      Width           =   3975
   End
   Begin VB.Label Label2 
      BackColor       =   &H00808000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "         Room number                Floor"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   21.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   720
      TabIndex        =   6
      Top             =   1200
      Width           =   8175
   End
   Begin VB.Label Label1 
      BackColor       =   &H00C0E0FF&
      Caption         =   "Odaberite sobu"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   24
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   240
      TabIndex        =   3
      Top             =   360
      Width           =   4815
   End
End
Attribute VB_Name = "SelectRoom"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim clsSelRoom As New Selector

Dim arrRoomNum(500) As String
Dim arrRoomFloor(500) As Integer
Dim arrRoomLabels(500) As String
Dim TotalRoomNum As Integer

Dim arrFloorIndStartAt(5) As Integer

Dim SelRoom As Integer

Private Sub Form_Load()
    Call SetLabel(cmdEnd, "End")
    Call SetLabel(cmdShowPath, "ShowPath")
    
    Dim cnn1 As adodb.Connection
    Set cnn1 = New adodb.Connection
    
    cnn1.ConnectionString = "DSN=Hypo"
    cnn1.Open
    
    Dim rs1 As New adodb.Recordset
    
    rs1.ActiveConnection = cnn1
    rs1.Source = "SELECT room_nbr,floor FROM room ORDER BY floor,room_nbr"
    
    rs1.CursorType = adOpenStatic
    rs1.CursorLocation = adUseClient
    rs1.LockType = adLockBatchOptimistic
    rs1.CacheSize = 10
    rs1.MaxRecords = 1000
    rs1.Open
    
    Dim nLenRoom As Integer
    For i = 0 To 4
        arrFloorIndStartAt(i) = -1
    Next i
    
    i = 1
    Do While Not rs1.EOF
        arrRoomNum(i) = rs1.Fields(0)
        nLenRoom = Len(arrRoomNum(i))
        
        arrRoomFloor(i) = rs1.Fields(1)
        ' kad se prvi put pojavi soba na tom katu
        ' u ovom polju ce se zapamtiti kod kojeg indeksa sobe se to pojavilo
        If (arrFloorIndStartAt(arrRoomFloor(i)) = -1) Then
            arrFloorIndStartAt(arrRoomFloor(i)) = i
        End If
        
        
        If nLenRoom > 5 Then
            arrRoomLabels(i) = arrRoomNum(i) & Left("               ", 15 - (nLenRoom - 5)) & arrRoomFloor(i)
        Else
            arrRoomLabels(i) = arrRoomNum(i) & "               " & arrRoomFloor(i)
        End If
        i = i + 1
        
        rs1.MoveNext
    Loop
    TotalRoomNum = i
    
    Call clsSelRoom.InitializeButtons(10, i - 1, 1, arrRoomLabels, cmdRoom)
    
    rs1.Close
    cnn1.Close
    
    SelRoom = -1
    
    cmdShowPath.Enabled = False
End Sub

Private Sub cmdRoom_Click(Index As Integer)
    SelRoom = Index + clsSelRoom.GetStartIndex() - 1
    
    cmdShowPath.Enabled = True
End Sub

Private Sub cmdRoomDown_Click()
    Call clsSelRoom.MoveDown
    cmdShowPath.Enabled = False
End Sub

Private Sub cmdRoomUp_Click()
    Call clsSelRoom.MoveUp
    cmdShowPath.Enabled = False
End Sub

Private Sub cmdShowPath_Click()
    Dim RoomStr As String
    
    If SelRoom <> -1 Then
        ShowPath.Show
        RoomStr = arrRoomNum(SelRoom)
    
        ShowPath.DrawPath (RoomStr)
    
        Unload Me
    End If
End Sub

Private Sub cmdEnd_Click()
    Unload Me
End Sub

Private Sub cmdSelFloor_Click(Index As Integer)
    ' treba skociti na index-ti kat
    clsSelRoom.SetStart (arrFloorIndStartAt(Index))
    cmdShowPath.Enabled = False
End Sub


