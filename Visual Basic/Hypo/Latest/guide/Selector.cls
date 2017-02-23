VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Selector"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private m_Start As Integer
Private m_NumTotal As Integer
Private m_NumToShow As Integer

Private m_arrCaptions() As String
Private m_Obj As Object

Private Sub Class_Initialize()
    m_Start = 1
    m_NumTotal = 0
    m_NumToShow = 0
    
    Set m_Obj = Nothing
End Sub

Public Function GetStartIndex() As Integer
    GetStartIndex = m_Start
End Function

Public Sub SetStart(start As Integer)
    If m_NumTotal - start < m_NumToShow Then
        m_Start = m_NumTotal - m_NumToShow + 1
    Else
        m_Start = start
    End If
    
    Call ShowButtons
End Sub

Public Sub MoveDown()
    If m_Start <= m_NumTotal - m_NumToShow Then
        m_Start = m_Start + 1
        Call ShowButtons
    End If
End Sub

Public Sub MoveUp()
    If m_Start > 1 Then
        m_Start = m_Start - 1
        Call ShowButtons
    End If
End Sub

Public Sub InitializeButtons(NumToShow As Integer, NumTotal As Integer, StartWith As Integer, arrCaptions() As String, Obj As Object)
    Dim ind As Integer
    Dim i As Integer
    
    m_NumToShow = NumToShow
    m_NumTotal = NumTotal
    m_Start = StartWith
    Set m_Obj = Obj
    
    ReDim m_arrCaptions(m_NumTotal) As String
    For i = 1 To m_NumTotal
        m_arrCaptions(i) = arrCaptions(i)
    Next i
    
    m_Obj(0).Visible = False
    For i = 1 To m_NumToShow
        Load m_Obj(i)
        
        ind = m_Start + i - 1
        m_Obj(i).Caption = arrCaptions(ind)
        m_Obj(i).Top = m_Obj(0).Top + (i - 1) * m_Obj(i).Height
        m_Obj(i).Visible = True
    Next i
End Sub

Public Sub ChangeCaptions(NumToShow As Integer, NumTotal As Integer, StartWith As Integer, arrCaptions() As String, Obj As Object)
    Dim ind As Integer
    Dim i As Integer
    
    m_NumToShow = NumToShow
    m_NumTotal = NumTotal
    m_Start = StartWith
    Set m_Obj = Obj
    
    ReDim m_arrCaptions(m_NumTotal) As String
    For i = 1 To m_NumTotal
        m_arrCaptions(i) = arrCaptions(i)
    Next i
    
    m_Obj(0).Visible = False
    For i = 1 To m_NumToShow
        ind = m_Start + i - 1
        m_Obj(i).Caption = arrCaptions(ind)
        m_Obj(i).Top = m_Obj(0).Top + (i - 1) * m_Obj(i).Height
        m_Obj(i).Visible = True
    Next i
End Sub

Public Sub ShowButtons()
    Dim ind As Integer
    Dim i As Integer
    
    For i = 1 To m_NumToShow
        ind = m_Start + i - 1
        
        m_Obj(i).Caption = m_arrCaptions(ind)
        m_Obj(i).Top = m_Obj(0).Top + (i - 1) * m_Obj(i).Height
        m_Obj(i).Visible = True
    Next i
End Sub
