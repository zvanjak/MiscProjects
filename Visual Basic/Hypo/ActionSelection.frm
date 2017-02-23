VERSION 5.00
Begin VB.Form ActionSelection 
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
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   30000
      Left            =   9360
      Top             =   240
   End
   Begin VB.CommandButton SelActEnd 
      Caption         =   "Kraj"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   36
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   975
      Left            =   5400
      TabIndex        =   5
      Top             =   9720
      Width           =   4455
   End
   Begin VB.CommandButton FindEvent 
      Caption         =   "Naði dogaðaj"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   36
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   975
      Left            =   2880
      TabIndex        =   3
      Top             =   7800
      Width           =   9375
   End
   Begin VB.CommandButton FindRoom 
      Caption         =   "Naði sobu"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   36
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   975
      Left            =   2880
      TabIndex        =   2
      Top             =   6120
      Width           =   9375
   End
   Begin VB.CommandButton FindEmp 
      Caption         =   "Naði zaposlenika"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   36
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   975
      Left            =   2880
      TabIndex        =   1
      Top             =   4320
      Width           =   9375
   End
   Begin VB.CommandButton FindDep 
      Caption         =   "Naði odjel"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   36
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   975
      Left            =   2880
      TabIndex        =   0
      Top             =   2640
      Width           =   9375
   End
   Begin VB.Label SelAction 
      BackColor       =   &H00C0E0FF&
      Caption         =   "Što želite"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   36
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   975
      Left            =   600
      TabIndex        =   4
      Top             =   960
      Width           =   8415
   End
End
Attribute VB_Name = "ActionSelection"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub FindDep_Click()
    SelectDepartment.Show
    Unload Me
End Sub

Private Sub FindEmp_Click()
    SelectEmployee.Show
    Unload Me
End Sub

Private Sub FindEvent_Click()
    SelectEvent.Show
    Unload Me
End Sub

Private Sub FindRoom_Click()
    SelectRoom.Show
    Unload Me
End Sub

Private Sub Form_Load()
    Me.Left = 0
    Me.Top = 0
    
    Timer1.Interval = TIMER_INT
    Timer1.Enabled = True
    
    Call SetLabel(SelAction, "SelAction")
    Call SetLabel(FindDep, "FindDep")
    Call SetLabel(FindEmp, "FindEmp")
    Call SetLabel(FindRoom, "FindRoom")
    Call SetLabel(FindEvent, "FindEvent")
    Call SetLabel(SelActEnd, "End")
End Sub


Private Sub SelActEnd_Click()
    Unload Me
End Sub

Private Sub Timer1_Timer()
    Unload Me
End Sub
