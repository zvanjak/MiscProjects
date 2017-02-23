VERSION 5.00
Object = "{67397AA1-7FB1-11D0-B148-00A0C922E820}#6.0#0"; "MSADODC.OCX"
Object = "{CDE57A40-8B86-11D0-B3C6-00A0C90AEA82}#1.0#0"; "MSDATGRD.OCX"
Begin VB.Form SelectEvent 
   BackColor       =   &H00C0E0FF&
   Caption         =   "Form1"
   ClientHeight    =   11115
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   15240
   LinkTopic       =   "Form1"
   ScaleHeight     =   11115
   ScaleWidth      =   15240
   StartUpPosition =   3  'Windows Default
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
      Left            =   3720
      TabIndex        =   3
      Top             =   10080
      Width           =   5175
   End
   Begin MSAdodcLib.Adodc ADOLecture 
      Height          =   615
      Left            =   3120
      Top             =   9360
      Visible         =   0   'False
      Width           =   2295
      _ExtentX        =   4048
      _ExtentY        =   1085
      ConnectMode     =   0
      CursorLocation  =   3
      IsolationLevel  =   -1
      ConnectionTimeout=   15
      CommandTimeout  =   30
      CursorType      =   3
      LockType        =   3
      CommandType     =   1
      CursorOptions   =   0
      CacheSize       =   50
      MaxRecords      =   0
      BOFAction       =   0
      EOFAction       =   0
      ConnectStringType=   3
      Appearance      =   1
      BackColor       =   -2147483643
      ForeColor       =   -2147483640
      Orientation     =   0
      Enabled         =   -1
      Connect         =   "DSN=Hypo"
      OLEDBString     =   ""
      OLEDBFile       =   ""
      DataSourceName  =   "Hypo"
      OtherAttributes =   ""
      UserName        =   ""
      Password        =   ""
      RecordSource    =   "SELECT * FROM lecture"
      Caption         =   "ADOLecture"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      _Version        =   393216
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
      Left            =   9600
      TabIndex        =   2
      Top             =   10080
      Width           =   2655
   End
   Begin MSDataGridLib.DataGrid GridLecture 
      Bindings        =   "SelectEvent2.frx":0000
      Height          =   3975
      Left            =   120
      TabIndex        =   1
      Top             =   5040
      Width           =   15015
      _ExtentX        =   26485
      _ExtentY        =   7011
      _Version        =   393216
      AllowUpdate     =   0   'False
      HeadLines       =   1
      RowHeight       =   45
      BeginProperty HeadFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   17.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   24
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ColumnCount     =   2
      BeginProperty Column00 
         DataField       =   ""
         Caption         =   ""
         BeginProperty DataFormat {6D835690-900B-11D0-9484-00A0C91110ED} 
            Type            =   0
            Format          =   ""
            HaveTrueFalseNull=   0
            FirstDayOfWeek  =   0
            FirstWeekOfYear =   0
            LCID            =   1050
            SubFormatType   =   0
         EndProperty
      EndProperty
      BeginProperty Column01 
         DataField       =   ""
         Caption         =   ""
         BeginProperty DataFormat {6D835690-900B-11D0-9484-00A0C91110ED} 
            Type            =   0
            Format          =   ""
            HaveTrueFalseNull=   0
            FirstDayOfWeek  =   0
            FirstWeekOfYear =   0
            LCID            =   1050
            SubFormatType   =   0
         EndProperty
      EndProperty
      SplitCount      =   1
      BeginProperty Split0 
         BeginProperty Column00 
         EndProperty
         BeginProperty Column01 
         EndProperty
      EndProperty
   End
   Begin MSAdodcLib.Adodc ADOEvent 
      Height          =   615
      Left            =   600
      Top             =   9840
      Visible         =   0   'False
      Width           =   2175
      _ExtentX        =   3836
      _ExtentY        =   1085
      ConnectMode     =   0
      CursorLocation  =   3
      IsolationLevel  =   -1
      ConnectionTimeout=   15
      CommandTimeout  =   30
      CursorType      =   3
      LockType        =   3
      CommandType     =   1
      CursorOptions   =   0
      CacheSize       =   50
      MaxRecords      =   0
      BOFAction       =   0
      EOFAction       =   0
      ConnectStringType=   3
      Appearance      =   1
      BackColor       =   -2147483643
      ForeColor       =   -2147483640
      Orientation     =   0
      Enabled         =   -1
      Connect         =   "DSN=Hypo"
      OLEDBString     =   ""
      OLEDBFile       =   ""
      DataSourceName  =   "Hypo"
      OtherAttributes =   ""
      UserName        =   ""
      Password        =   ""
      RecordSource    =   "SELECT * FROM event WHERE date_from<Date() AND date_until>Date()"
      Caption         =   "ADOEvent"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      _Version        =   393216
   End
   Begin MSDataGridLib.DataGrid GridEvent 
      Bindings        =   "SelectEvent2.frx":0019
      Height          =   3735
      Left            =   120
      TabIndex        =   0
      Top             =   360
      Width           =   15015
      _ExtentX        =   26485
      _ExtentY        =   6588
      _Version        =   393216
      AllowUpdate     =   0   'False
      HeadLines       =   1
      RowHeight       =   45
      BeginProperty HeadFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   17.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   24
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ColumnCount     =   2
      BeginProperty Column00 
         DataField       =   ""
         Caption         =   ""
         BeginProperty DataFormat {6D835690-900B-11D0-9484-00A0C91110ED} 
            Type            =   0
            Format          =   ""
            HaveTrueFalseNull=   0
            FirstDayOfWeek  =   0
            FirstWeekOfYear =   0
            LCID            =   1050
            SubFormatType   =   0
         EndProperty
      EndProperty
      BeginProperty Column01 
         DataField       =   ""
         Caption         =   ""
         BeginProperty DataFormat {6D835690-900B-11D0-9484-00A0C91110ED} 
            Type            =   0
            Format          =   ""
            HaveTrueFalseNull=   0
            FirstDayOfWeek  =   0
            FirstWeekOfYear =   0
            LCID            =   1050
            SubFormatType   =   0
         EndProperty
      EndProperty
      SplitCount      =   1
      BeginProperty Split0 
         BeginProperty Column00 
         EndProperty
         BeginProperty Column01 
         EndProperty
      EndProperty
   End
End
Attribute VB_Name = "SelectEvent"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Base 0
Option Explicit

Dim SelectedEvent As Integer


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

Private Sub Form_Load()
    Dim str_lang As String
    
    Call SetLabel(cmdShowPath, "ShowPath")
    Call SetLabel(cmdEnd, "End")
    
    cmdShowPath.Enabled = False
    
    ADOEvent.RecordSource = "SELECT * FROM event WHERE date_from<" & AccessDate(Date) & " AND date_until>" & AccessDate(Date)
    ADOEvent.Refresh
    
    GridEvent.Refresh
    
    GridEvent.Columns(0).Visible = False
    GridEvent.Columns(2).Visible = False

    GridEvent.Columns(3).Caption = GetLabel("StartDate")
    GridEvent.Columns(3).Width = 3000
    GridEvent.Columns(4).Caption = GetLabel("EndDate")
    GridEvent.Columns(4).Width = 3000
    
    GridEvent.Columns(1).Caption = GetLabel("EventTitel")
    GridEvent.Columns(1).Width = GridEvent.Width - 6000
    
    SelectedEvent = -1      ' na pocetku nije selektiran nijedan event
    
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
    
    ADOLecture.RecordSource = "SELECT " & str_lang & ", time_from, time_until, room_nbr FROM lecture WHERE date_lec=" + AccessDate(Date) + " AND event_nbr = " & SelectedEvent
    ADOLecture.Refresh
    
    GridLecture.Refresh

    GridLecture.Columns(0).Width = GridLecture.Width - 6000
    GridLecture.Columns(1).Width = 2000
    GridLecture.Columns(2).Width = 2000
    GridLecture.Columns(3).Width = 2000
    
    GridLecture.Columns(0).Caption = GetLabel("LectureDesc")
    GridLecture.Columns(1).Caption = GetLabel("StartTime")
    GridLecture.Columns(2).Caption = GetLabel("EndTime")
    GridLecture.Columns(3).Caption = GetLabel("Room")
End Sub

Private Sub GridEvent_RowColChange(LastRow As Variant, ByVal LastCol As Integer)
    Dim str_lang As String
    
    ' TO DO
    ' provjeriti da li uopce ima neki event
    On Error GoTo lab_end
    
    If SelectedEvent <> GridEvent.Columns(0).Value Then
        ' znaci da smo promijenili odabir eventa
        SelectedEvent = GridEvent.Columns(0).Value
        cmdShowPath.Enabled = False
    End If
    
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
    
    ADOLecture.RecordSource = "SELECT " & str_lang & ", time_from, time_until, room_nbr FROM lecture WHERE date_lec=" + AccessDate(Date) + " AND event_nbr = " & SelectedEvent
    ADOLecture.Refresh
    
    ' TO DO  !!!!!!
    ' ovdje treba provjeriti da li je vracen ijedan zapis ( mozda danas nema predavanja )
    
    GridLecture.Columns(0).Width = GridLecture.Width - 6500
    GridLecture.Columns(1).Width = 2000
    GridLecture.Columns(2).Width = 2000
    GridLecture.Columns(3).Width = 2000
    
    GridLecture.Columns(0).Caption = GetLabel("LectureDesc")
    GridLecture.Columns(1).Caption = GetLabel("StartTime")
    GridLecture.Columns(2).Caption = GetLabel("EndTime")
    GridLecture.Columns(3).Caption = GetLabel("Room")

    GridLecture.Refresh
    GridEvent.Refresh
    
lab_end:
End Sub

Private Sub GridLecture_RowColChange(LastRow As Variant, ByVal LastCol As Integer)
    If SelectedEvent <> -1 Then
        cmdShowPath.Enabled = True
    End If
End Sub
