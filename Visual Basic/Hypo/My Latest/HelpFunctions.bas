Attribute VB_Name = "HelpFunctions"
Public Sub ShowScreenKeyboard(nTop As Integer, nLeft As Integer, sizeX As Integer, sizeY As Integer, DX As Integer, DY As Integer, NumInRow As Integer, strLetters As String, Obj As Object)
    Dim X As Integer
    Dim Y As Integer
    Dim i As Integer
    Dim row As Integer
    Dim col As Integer
    
    Obj(0).Visible = False
    For i = 1 To Len(strLetters)
        Load Obj(i)
        
        col = (i - 1) Mod NumInRow
        row = Int((i - 1) / NumInRow)
        X = nLeft + (col) * (sizeX + DX)
        Y = nTop + (row) * (sizeY + DY)
        
        Obj(i).Top = Y
        Obj(i).Left = X
        Obj(i).Caption = Mid(strLetters, i, 1)
        Obj(i).Visible = True
    Next i
End Sub

