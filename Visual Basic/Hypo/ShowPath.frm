VERSION 5.00
Begin VB.Form ShowPath 
   BackColor       =   &H00C0E0FF&
   ClientHeight    =   11040
   ClientLeft      =   60
   ClientTop       =   60
   ClientWidth     =   15240
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   11040
   ScaleWidth      =   15240
   WindowState     =   2  'Maximized
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   30000
      Left            =   9240
      Top             =   1680
   End
   Begin VB.CommandButton cmdShowPathEnd 
      Caption         =   "End"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   27.75
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   975
      Left            =   9960
      TabIndex        =   8
      Top             =   9480
      Width           =   3375
   End
   Begin VB.Label labShowPathKioskToRoom 
      AutoSize        =   -1  'True
      BackColor       =   &H00C0E0FF&
      Caption         =   "Put od kioska do tražene sobe je prikazan na slici"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   17.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   390
      Left            =   120
      TabIndex        =   10
      Top             =   240
      Visible         =   0   'False
      Width           =   7395
   End
   Begin VB.Label labShowPathLiftToRoom 
      AutoSize        =   -1  'True
      BackColor       =   &H00C0E0FF&
      Caption         =   "Put od lifta do trazene sobe je prikazan na slici"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   17.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   390
      Left            =   120
      TabIndex        =   9
      Top             =   2040
      Visible         =   0   'False
      Width           =   6945
   End
   Begin VB.Label labShowPathWhenDone 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      BackColor       =   &H00C0E0FF&
      Caption         =   "When you are done, please, press this button"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   21.75
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   240
      TabIndex        =   7
      Top             =   9720
      Width           =   9135
   End
   Begin VB.Label labVerbInstructions2 
      BackColor       =   &H00C0E0FF&
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   13.5
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   120
      TabIndex        =   6
      Top             =   9000
      Width           =   13575
   End
   Begin VB.Label labShowPathDestPos 
      AutoSize        =   -1  'True
      BackColor       =   &H00C0E0FF&
      Caption         =   "Soba koju tražite se nalazi na"
      DataField       =   " "
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   17.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   390
      Left            =   120
      TabIndex        =   5
      Top             =   840
      Visible         =   0   'False
      Width           =   4395
   End
   Begin VB.Label labShowPathCurrPos 
      AutoSize        =   -1  'True
      BackColor       =   &H00C0E0FF&
      Caption         =   "Trenutno se nalazite na"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   17.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   390
      Left            =   120
      TabIndex        =   4
      Top             =   240
      Visible         =   0   'False
      Width           =   3525
   End
   Begin VB.Label labShowPathFloor2 
      AutoSize        =   -1  'True
      BackColor       =   &H00C0E0FF&
      Caption         =   ". kat"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   17.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   390
      Left            =   8520
      TabIndex        =   3
      Top             =   840
      Visible         =   0   'False
      Width           =   630
   End
   Begin VB.Label labShowPathFloor1 
      AutoSize        =   -1  'True
      BackColor       =   &H00C0E0FF&
      Caption         =   ". kat"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   17.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   390
      Left            =   9120
      TabIndex        =   2
      Top             =   240
      Visible         =   0   'False
      Width           =   630
   End
   Begin VB.Label labFloorNum2 
      AutoSize        =   -1  'True
      BackColor       =   &H00C0E0FF&
      Caption         =   "Label1"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   17.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   390
      Left            =   6960
      TabIndex        =   1
      Top             =   840
      Visible         =   0   'False
      Width           =   1020
   End
   Begin VB.Label labFloorNum1 
      AutoSize        =   -1  'True
      BackColor       =   &H00C0E0FF&
      Caption         =   "Label1"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   17.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   390
      Left            =   7560
      TabIndex        =   0
      Top             =   240
      Visible         =   0   'False
      Width           =   1020
   End
   Begin VB.Image Image2 
      BorderStyle     =   1  'Fixed Single
      Height          =   6120
      Left            =   0
      Top             =   2760
      Width           =   14175
   End
End
Attribute VB_Name = "ShowPath"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Const DIR_LEFT = 1
Const DIR_RIGHT = 2
Const DIR_STRAIGHT = 3
Const DIR_BACK = 4

Dim CustomerDirection As Single
    
Public Sub DrawPath(Room As String)
    Dim arrPath(100) As Integer
    Dim arrPath2(100) As Integer
    Dim NodeNum As Integer
    Dim NodeNum2 As Integer
    
    Dim i As Integer
    Dim PathLen As Single
    Dim SecFloorNum As Integer
    
    Dim x_src As Integer
    Dim y_src As Integer
    Dim x_dest As Integer
    Dim y_dest As Integer
    
    Timer1.Interval = TIMER_INT
    
    ShowPath.DrawWidth = 3
    
    CustomerDirection = ThisKioskDirection
    
    ' ucitavamo sliku kata nakojem se nalazi trazena soba
    SecFloorNum = GetFloorNumber(Room)
    Select Case SecFloorNum
        Case 0
            Image2.Picture = LoadPicture("C:\Hypo\Floor0_1.wmf")
        Case 1
            Image2.Picture = LoadPicture("C:\Hypo\Floor1_1.wmf")
        Case 2
            Image2.Picture = LoadPicture("C:\Hypo\Floor2_1.wmf")
        Case 3
            Image2.Picture = LoadPicture("C:\Hypo\Floor3_1.wmf")
        Case 4
            Image2.Picture = LoadPicture("C:\Hypo\Floor4_1.wmf")
            
    End Select
    
    If ThisKioskPos.Floor <> GetFloorNumber(Room) Then
        ' znaci da su trenutna pozicija i trazena soba na dva razlicita kata
        nStartPathNode = KioskNodeInd
        nEndPathNode = LiftNodeInd(ThisKioskPos.Floor)
       
        labShowPathFloor1.Visible = True
        labFloorNum1.Visible = True
        labShowPathCurrPos.Visible = True
        labShowPathFloor2.Visible = True
        labFloorNum2.Visible = True
        labShowPathDestPos.Visible = True
        
        labShowPathLiftToRoom.Visible = True
        
        labVerbInstructions2.Top = Image2.Top + Image2.Height
        labVerbInstructions2.Refresh
        
        PicWidth2 = Image2.Width
        PicHeight2 = Image2.Height
        
        labFloorNum1.Left = labShowPathCurrPos.Width + 300
        labFloorNum1.Caption = str(ThisKioskPos.Floor)
        
        labFloorNum2.Left = labShowPathDestPos.Width + 300
        labFloorNum2.Caption = str(SecFloorNum)
        
        labShowPathFloor1.Left = labFloorNum1.Left + labFloorNum1.Width + 300
        labShowPathFloor2.Left = labFloorNum2.Left + labFloorNum2.Width + 300
    
        Image2.Refresh
        
        ' na katu na kojem se nalazi soba, naci put od lifta do te sobe
        nStartPathNode = LiftNodeInd(SecFloorNum)
        nEndPathNode = GetRoomNodeNumber(Room, SecFloorNum)
    
        Call FindPath(nStartPathNode, nEndPathNode, SecFloorNum, arrPath2, NodeNum2, PathLen)
        
        ' naredbe koje ce iscrtati pokazivace na trenutnu i trazenu poziciju
'        x_src = arrPos(ThisKioskPos.Floor, arrPath(0)).X
'        y_src = arrPos(ThisKioskPos.Floor, arrPath(0)).Y
'        Line (labShowPathCurrPos.Left + labShowPathCurrPos.Width + 100, labShowPathCurrPos.Top + labShowPathCurrPos.Height / 2)-(x_src, y_src)
        
'        x_dest = arrPos(SecFloorNum, arrPath2(NodeNum2 - 1)).X
'        y_dest = arrPos(SecFloorNum, arrPath2(NodeNum2 - 1)).Y + Image1.Height + labVerbInstructions1.Height
'        Line (labShowPathDestPos.Left + labShowPathDestPos.Width + 100, labShowPathDestPos.Top + labShowPathCurrPos.Height / 2)-(x_dest, y_dest)
        
 '       Call DrawFunc(arrPath, ThisKioskPos.Floor, NodeNum, True)
        
        CustomerDirection = LiftDirection
        
        Call DrawFunc(arrPath2, SecFloorNum, NodeNum2, False)
    Else
        ' trazena soba se nalazi na istom katu na kojem i kiosk
        labFloorNum1.Caption = str(ThisKioskPos.Floor)
        
        nStartPathNode = KioskNodeInd
        nEndPathNode = GetRoomNodeNumber(Room, ThisKioskPos.Floor)
        
        labShowPathKioskToRoom.Visible = True
        Image2.Top = 1000
        Image2.Refresh
        
        Call FindPath(nStartPathNode, nEndPathNode, ThisKioskPos.Floor, arrPath, NodeNum, PathLen)
        
        labVerbInstructions2.Top = Image2.Top + Image2.Height
        labVerbInstructions2.Refresh
        
'        Line (labShowPathCurrPos.Left + labShowPathCurrPos.Width + 100, labShowPathCurrPos.Top + labShowPathCurrPos.Height / 2)-(100, 100)
        
        Call DrawFunc(arrPath, ThisKioskPos.Floor, NodeNum, True)
    End If
End Sub

Private Sub DrawFunc(arrPath() As Integer, Floor As Integer, NodeNum As Integer, UpperForm As Boolean)
    Dim X0 As Single
    Dim Y0 As Single
    Dim dx As Single
    Dim dy As Single
    
    Dim i As Integer
    Dim s As Integer
    Dim T As Long
    Dim y_bias As Single
    
    Dim PicWidth As Single
    Dim PicHeight As Single
    
    Dim Direction As Single
    Dim cmp As Integer

    Dim Start As Single
    Dim LineLen As Integer
    Dim EndInd As Integer
    
    PicWidth = Image2.Width
    PicHeight = Image2.Height
    y_bias = Image2.Top '+ labVerbInstructions1.Height
    
    For i = 0 To NodeNum - 2
        X0 = arrPos(Floor, arrPath(i)).X * PicWidth
        Y0 = y_bias + arrPos(Floor, arrPath(i)).Y * PicHeight
        
        dx = arrPos(Floor, arrPath(i + 1)).X * PicWidth - X0
        dy = y_bias + arrPos(Floor, arrPath(i + 1)).Y * PicHeight - Y0
        
        Direction = CalcDirection(dx, dy)
        
        cmp = CompareDirections(CustomerDirection, Direction)
        
        If cmp = DIR_LEFT Then
'            If UpperForm = True Then
'                labVerbInstructions1.Caption = labVerbInstructions1.Caption & GetLabel("TurnLeft") & ";  "
'            Else
                labVerbInstructions2.Caption = labVerbInstructions2.Caption & GetLabel("TurnLeft") & ";  "
                labVerbInstructions2.Refresh
'            End If
            
'            labVerbInstructions1.Refresh
        ElseIf cmp = DIR_RIGHT Then
'            If UpperForm = True Then
'                labVerbInstructions1.Caption = labVerbInstructions1.Caption & GetLabel("TurnRight") & ";  "
'            Else
                labVerbInstructions2.Caption = labVerbInstructions2.Caption & GetLabel("TurnRight") & ";  "
                labVerbInstructions2.Refresh
'            End If
            
'            labVerbInstructions1.Refresh
        ElseIf cmp = DIR_STRAIGHT Then
'            If UpperForm = True Then
'                labVerbInstructions1.Caption = labVerbInstructions1.Caption & GetLabel("StraightAhead") & ";  "
'            Else
                labVerbInstructions2.Caption = labVerbInstructions2.Caption & GetLabel("StraightAhead") & ";  "
                labVerbInstructions2.Refresh
'            End If
            
'            labVerbInstructions1.Refresh
        Else
'            If UpperForm = True Then
'                labVerbInstructions1.Caption = labVerbInstructions1.Caption & GetLabel("GoBack") & ";  "
'            Else
                labVerbInstructions2.Caption = labVerbInstructions2.Caption & GetLabel("GoBack") & ";  "
                labVerbInstructions2.Refresh
'            End If
            
'            labVerbInstructions1.Refresh
        End If
        
        CustomerDirection = Direction
        
        LineLen = Sqr(dx ^ 2 + dy ^ 2)
        EndInd = LineLen / 10
        For s = 0 To EndInd
            Line (X0, Y0)-(X0 + dx / EndInd * s, Y0 + dy / EndInd * s), RGB(255, 0, 0)
    
            ' da se uspori iscrtavanje
            Start = Timer   ' Set start time.
            Do While Timer < Start + 0.0006
                DoEvents    ' Yield to other processes.
            Loop
        Next s
    Next i
End Sub

Public Function CalcDirection(ByVal dx As Single, ByVal dy As Single) As Single
    Dim kut_rad As Single
    Dim kut_deg As Single
    Dim rez As Single
    
    ' najprije cemo invertirati y-smjer, zato sto na racunalu, y-os pokazuje prema dolje
    dy = -dy
    
    If dx = 0 Then          ' znaci da se radi o vertikalnom smjeru
        If dy > 0 Then
            rez = 90
        Else
            rez = 270
        End If
    ElseIf dy = 0 Then      ' znaci da se radio o horizontalnom smjeru
        If dx > 0 Then
            rez = 0
        Else
            rez = 180
        End If
    Else
        kut_rad = Atn(dy / dx)
        kut_deg = kut_rad * 180 / 3.14159
        
        If dx < 0 And dy > 0 Then       ' drugi kvadrant
            rez = 180 + kut_deg
        ElseIf dx < 0 And dy < 0 Then   ' treci kvadrant
            rez = 180 + kut_deg
        ElseIf dx > 0 And dy < 0 Then   ' cetvrti kvadrant
            rez = 360 + kut_deg
        Else
            rez = kut_deg
        End If
        
        If rez = 360 Then
            rez = 0
        End If
    End If
    
    CalcDirection = rez
End Function

Public Function CompareDirections(ByVal DirCustomer As Single, ByVal Direction As Single) As Integer
    Dim rez_dir As Single
    
    rez_dir = DirCustomer - Direction
    
    If rez_dir < 180 Then
        rez_dir = rez_dir + 360
    End If
    If rez_dir > 180 Then
        rez_dir = rez_dir - 360
    End If
    
    If rez_dir > -45 And rez_dir < 45 Then
        CompareDirections = DIR_STRAIGHT
    ElseIf rez_dir < -45 And rez_dir > -135 Then
        CompareDirections = DIR_LEFT
    ElseIf rez_dir > 45 And rez_dir < 135 Then
        CompareDirections = DIR_RIGHT
    Else
        CompareDirections = DIR_BACK
    End If
    
End Function

Private Sub cmdShowPathEnd_Click()
    Unload Me
End Sub

Private Sub Form_Load()
    Call SetLabel(labShowPathWhenDone, "ShowPathWhenDone")
    Call SetLabel(cmdShowPathEnd, "End")
    Call SetLabel(labShowPathKioskToRoom, "ShowPathKioskToRoom")
    Call SetLabel(labShowPathLiftToRoom, "ShowPathLiftToRoom")
    Call SetLabel(labShowPathCurrPos, "ShowPathCurrPos")
    Call SetLabel(labShowPathDestPos, "ShowPathDestPos")
    Call SetLabel(labShowPathFloor1, "FloorSmall")
    Call SetLabel(labShowPathFloor2, "FloorSmall")
    
    Timer1.Interval = TIMER_INT
    Timer1.Enabled = True
End Sub

Private Sub Timer1_Timer()
    Unload Me
End Sub
