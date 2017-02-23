VERSION 5.00
Begin VB.Form SelectEmployee 
   BackColor       =   &H00C0E0FF&
   ClientHeight    =   11115
   ClientLeft      =   60
   ClientTop       =   60
   ClientWidth     =   15240
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   Moveable        =   0   'False
   ScaleHeight     =   11115
   ScaleWidth      =   15240
   StartUpPosition =   2  'CenterScreen
   WindowState     =   2  'Maximized
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   30000
      Left            =   7440
      Top             =   1920
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
      Height          =   675
      Index           =   0
      Left            =   10200
      TabIndex        =   19
      Top             =   2520
      Width           =   735
   End
   Begin VB.CommandButton cmdEmpListDown 
      Height          =   735
      Left            =   8040
      Picture         =   "SelectEmployee.frx":0000
      Style           =   1  'Graphical
      TabIndex        =   18
      Top             =   6960
      Width           =   855
   End
   Begin VB.CommandButton cmdEmpListUp 
      DisabledPicture =   "SelectEmployee.frx":06C2
      Height          =   735
      Left            =   8040
      Picture         =   "SelectEmployee.frx":0D84
      Style           =   1  'Graphical
      TabIndex        =   17
      Top             =   2520
      Width           =   855
   End
   Begin VB.CommandButton cmdEmpList 
      Caption         =   "Command1"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   21.75
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Index           =   0
      Left            =   480
      TabIndex        =   16
      Top             =   2520
      Width           =   6855
   End
   Begin VB.CommandButton SelEmpEnd 
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
      Height          =   705
      Left            =   8760
      TabIndex        =   15
      Top             =   10200
      Width           =   5055
   End
   Begin VB.CommandButton SelEmpShowPath 
      Caption         =   "Show path"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   27.75
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   720
      Left            =   2040
      TabIndex        =   14
      Top             =   10200
      Width           =   6015
   End
   Begin VB.CommandButton SelEmpBySurName 
      Caption         =   "Select by surname"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   24
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1215
      Left            =   8040
      TabIndex        =   1
      Top             =   480
      Width           =   6735
   End
   Begin VB.CommandButton SelEmpByName 
      Caption         =   "Select by first name"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   24
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1215
      Left            =   480
      TabIndex        =   0
      Top             =   480
      Width           =   6855
   End
   Begin VB.Label Tel 
      BackColor       =   &H00C0E0FF&
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   26.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   13080
      TabIndex        =   13
      Top             =   9000
      Width           =   1575
   End
   Begin VB.Label Room 
      Alignment       =   2  'Center
      BackColor       =   &H00C0E0FF&
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   26.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   10800
      TabIndex        =   12
      Top             =   9000
      Width           =   2055
   End
   Begin VB.Label Floor 
      Alignment       =   2  'Center
      BackColor       =   &H00C0E0FF&
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   26.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   9360
      TabIndex        =   11
      Top             =   9000
      Width           =   1095
   End
   Begin VB.Label Surname 
      BackColor       =   &H00C0E0FF&
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   26.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Left            =   5280
      TabIndex        =   10
      Top             =   9000
      Width           =   3615
   End
   Begin VB.Label LabName 
      BackColor       =   &H00C0E0FF&
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   26.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Left            =   2400
      TabIndex        =   9
      Top             =   9000
      Width           =   2655
   End
   Begin VB.Label Titel 
      BackColor       =   &H00C0E0FF&
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   26.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   240
      TabIndex        =   8
      Top             =   9000
      Width           =   1935
   End
   Begin VB.Label SelEmpTel 
      Alignment       =   2  'Center
      BackColor       =   &H00C0E0FF&
      Caption         =   "Telefon"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   20.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   12840
      TabIndex        =   7
      Top             =   8280
      Width           =   2175
   End
   Begin VB.Label SelEmpRoom 
      Alignment       =   2  'Center
      BackColor       =   &H00C0E0FF&
      Caption         =   "Soba"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   20.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   11160
      TabIndex        =   6
      Top             =   8280
      Width           =   1455
   End
   Begin VB.Label SelEmpFloor 
      Alignment       =   2  'Center
      BackColor       =   &H00C0E0FF&
      Caption         =   "Kat"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   20.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   9240
      TabIndex        =   5
      Top             =   8280
      Width           =   1455
   End
   Begin VB.Label SelEmpSurName 
      BackColor       =   &H00C0E0FF&
      Caption         =   "Prezime"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   20.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   5280
      TabIndex        =   4
      Top             =   8280
      Width           =   2295
   End
   Begin VB.Label SelEmpName 
      BackColor       =   &H00C0E0FF&
      Caption         =   "Ime"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   20.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   2400
      TabIndex        =   3
      Top             =   8280
      Width           =   2535
   End
   Begin VB.Label SelEmpTitel 
      BackColor       =   &H00C0E0FF&
      Caption         =   "Titula"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   20.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   240
      TabIndex        =   2
      Top             =   8280
      Width           =   1815
   End
End
Attribute VB_Name = "SelectEmployee"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Base 0
Option Explicit

Dim clsSelEmp As New Selector

Dim Selection As Integer

Private Sub Form_Load()
    Dim i As Integer
    Dim j As Integer
    Dim str As String
    Dim arr(6) As String
    
    Timer1.Interval = TIMER_INT
    Timer1.Enabled = True
    
    arr(1) = " "
    arr(2) = " "
    arr(3) = " "
    arr(4) = " "
    arr(5) = " "
    arr(6) = " "

    Call SetLabel(SelEmpByName, "SelEmpByName")
    Call SetLabel(SelEmpBySurName, "SelEmpBySurName")
    Call SetLabel(SelEmpTitel, "SelEmpTitel")
    Call SetLabel(SelEmpTel, "SelEmpTel")
    Call SetLabel(SelEmpName, "SelEmpName")
    Call SetLabel(SelEmpSurName, "SelEmpSurName")
    Call SetLabel(SelEmpRoom, "SelEmpRoom")
    Call SetLabel(SelEmpFloor, "SelEmpFloor")
    Call SetLabel(SelEmpShowPath, "ShowPath")
    Call SetLabel(SelEmpEnd, "End")

    ' initial selection is 'Select by surname'
    Selection = 2
    
    
    Dim addTitel As String
    For i = 1 To EmpNum
        addTitel = ""
        If Selection = 1 Then
            If EmpTitel(arrIndSortName(i)) <> " " Then
                addTitel = " ; " & EmpTitel(arrIndSortName(i))
            End If
            arrNames(i) = EmpNames(arrIndSortName(i)) & " " & EmpSurnames(arrIndSortName(i)) & addTitel
        Else
            If EmpTitel(arrIndSortSurname(i)) <> " " Then
                addTitel = " ; " & EmpTitel(arrIndSortSurname(i))
            End If
            arrNames(i) = EmpSurnames(arrIndSortSurname(i)) & " " & EmpNames(arrIndSortSurname(i)) & addTitel
        End If
    Next i
        
    Call clsSelEmp.InitializeButtons(6, EmpNum - 1, 1, arrNames, cmdEmpList)
    
    str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    Call ShowScreenKeyboard(cmdKeyEmp(0).Top, cmdKeyEmp(0).Left, cmdKeyEmp(0).Width, cmdKeyEmp(0).Height, 225, 222, 5, str, cmdKeyEmp)
    Call RefreshData
End Sub

Private Sub SelEmpByName_Click()
    If Selection <> 1 Then
        Selection = 1
        
        Call SetDataEmpty
        SelEmpShowPath.Enabled = False
        
        Call RefreshData
    End If
    
    Call RestartTimer
End Sub

Private Sub SelEmpBySurName_Click()
    If Selection <> 2 Then
        Selection = 2
        
        Call SetDataEmpty
        SelEmpShowPath.Enabled = False
        
        Call RefreshData
    End If
    
    Call RestartTimer
End Sub

Sub RefreshData()
    Dim i As Integer
    Dim addTitel As String
    
    For i = 1 To EmpNum
        addTitel = ""
        If Selection = 1 Then
            If EmpTitel(arrIndSortName(i)) <> " " Then
                addTitel = " ; " & EmpTitel(arrIndSortName(i))
            End If
            arrNames(i) = EmpNames(arrIndSortName(i)) & " " & EmpSurnames(arrIndSortName(i)) & addTitel
        Else
            If EmpTitel(arrIndSortSurname(i)) <> " " Then
                addTitel = " ; " & EmpTitel(arrIndSortSurname(i))
            End If
            arrNames(i) = EmpSurnames(arrIndSortSurname(i)) & " " & EmpNames(arrIndSortSurname(i)) & addTitel
        End If
    Next i
        
    Call clsSelEmp.ChangeCaptions(6, EmpNum - 1, 1, arrNames, cmdEmpList)
    
    SelEmpShowPath.Enabled = False
    Call SetDataEmpty
    
    Call RestartTimer
End Sub

Private Sub SelEmpEnd_Click()
    Unload Me
End Sub

Private Sub SelEmpShowPath_Click()
    Dim RoomStr As String
    
    ShowPath.Show
    RoomStr = Room.Caption
    ShowPath.DrawPath (RoomStr)
    
    Unload Me
End Sub

Private Sub SetDataEmpty()
    Titel.Caption = ""
    LabName.Caption = ""
    Surname.Caption = ""
    Floor.Caption = ""
    Room.Caption = ""
    Tel.Caption = ""
End Sub

Private Sub cmdEmpList_Click(Index As Integer)
    Dim num As Integer
    Dim ind As Integer
    Dim item As String
    Dim var As String
    Dim i As Integer
            
    If Selection = 1 Then
        ind = arrIndSortName(Index + clsSelEmp.GetStartIndex() - 1)
    Else
        ind = arrIndSortSurname(Index + clsSelEmp.GetStartIndex() - 1)
    End If
    
    Titel.Caption = EmpTitel(ind)
    LabName.Caption = EmpNames(ind)
    Surname.Caption = EmpSurnames(ind)
    Floor.Caption = EmpFloor(ind)
    Room.Caption = EmpRoom(ind)
    Tel.Caption = EmpTel(ind)
    
    SelEmpShowPath.Enabled = True
    
    Call RestartTimer
End Sub

Private Sub cmdEmpListDown_Click()
    Call clsSelEmp.MoveDown

    Call SetDataEmpty
    
    SelEmpShowPath.Enabled = False
    
    Call RestartTimer
End Sub

Private Sub cmdEmpListUp_Click()
    Call clsSelEmp.MoveUp

    Call SetDataEmpty
    
    SelEmpShowPath.Enabled = False

    Call RestartTimer
End Sub

Private Sub cmdKeyEmp_Click(Index As Integer)
    Dim i As Integer
    
    Call SetDataEmpty
    
    SelEmpShowPath.Enabled = False
    For i = 1 To EmpNum
        If UCase(Mid(arrNames(i), 1, 1)) >= UCase(cmdKeyEmp(Index).Caption) Then
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

