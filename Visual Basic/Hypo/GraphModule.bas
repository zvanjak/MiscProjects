Attribute VB_Name = "GraphModule"
Option Explicit
Option Base 0

Global Const TIMER_INT = 60000
'Const LIFT = 1
'Const KIOSK = 2
Global Const FLOOR_NUM = 5
Global Const MAX_CONN_PER_NODE = 30
Global Const MAX_NODE_NUM = 100

Global Lang As String

Global cnn As New adodb.Connection
Global cnnRoom As New adodb.Connection
Global rstRoom   As New adodb.Recordset

' ovo ce nam trebati za dohvat visejezicnih labela
Global cnnLing As adodb.Connection
Global rstGetLabel As adodb.Recordset
Global cmdGetLabel As adodb.Command
Global prmGetLabelLang As adodb.Parameter
Global prmGetLabelLabID As adodb.Parameter

Global PicWidth1 As Integer
Global PicHeight1 As Integer
Global PicWidth2 As Integer
Global PicHeight2 As Integer

Public Type Employee
    Name As String
    Surname As String
    Tel As String
    Titel As String
    Room As String
    Floor As Integer
End Type

Public Type Point
    X As Single
    Y As Single
    Room As String
    Floor As Integer
End Type

Public Type Node
    X As Single
    Y As Single
    num As Integer          ' broj sobe
    Room As String
    
    NodeList(MAX_CONN_PER_NODE) As Integer     ' i-ti cvor s kojime ima vezu
    NodeDist(MAX_CONN_PER_NODE) As Single     ' udaljenost do i-tog povezanog cvora
    ConnNum As Integer          ' sa koliko je cvorova povezan ovaj cvor
End Type

Public Type Handle
    NodeInd As Integer
    Dist As Single
    Room As String
End Type

Global arrPos(FLOOR_NUM, MAX_NODE_NUM) As Point         ' pozicije kontrolnih tocaka
Global nRoomNum(FLOOR_NUM) As Integer          ' broj tocaka u grafu

Global nFirstNode As Integer
Global nSecondNode As Integer

Global nStartPathNode As Integer
Global nEndPathNode As Integer

Global arrNodes(FLOOR_NUM, MAX_NODE_NUM) As Node

Global ThisKioskPos As Point
Global ThisKioskDirection As Integer        ' u stupnjevima, orijentacija posjetitelja kada gleda u ekran
Global KioskNodeInd As Integer          ' indeks cvora u popisu cvorova u kojem se nalaze podaci o kiosku (pozicija i veze)

Global LiftPos(FLOOR_NUM) As Point
Global LiftDirection As Integer
Global LiftNodeInd(FLOOR_NUM) As Integer

Public Sub InitData()
    Dim i As Integer
    Dim j As Integer
    
    Open "C:\Hypo\FloorNum.txt" For Input As #15
    Input #15, ThisKioskPos.Floor
    
'    ThisKioskPos.X = 7170
'    ThisKioskPos.Y = 2940
    
    ThisKioskDirection = 150
    
'    KioskNodeInd = 18
    
'    LiftNodeInd = 23
'    LiftDirection = 300

    For j = 0 To FLOOR_NUM
        nRoomNum(j) = 0
    Next j
    
    For j = 0 To FLOOR_NUM
        For i = 0 To MAX_NODE_NUM
            arrNodes(j, i).ConnNum = 0
        Next i
    Next j
    
    LoadData
End Sub

Public Sub SetLabel(ByRef lab As Object, str As String)
    ' postavi vrijednosti parametra za SQL upit
    prmGetLabelLang.Value = Lang
    prmGetLabelLabID.Value = str
    
    ' izvrsi upit
    Set rstGetLabel = cmdGetLabel.Execute()

    ' postavi vrijednost labele
    lab.Caption = rstGetLabel.Fields(0)
End Sub

Public Function GetLabel(str As String) As String
    prmGetLabelLang.Value = Lang
    prmGetLabelLabID.Value = str
    
    ' izvrsi upit
    Set rstGetLabel = cmdGetLabel.Execute()

    ' postavi vrijednost labele
    GetLabel = rstGetLabel.Fields(0)
End Function

' za dani broj sobe vraca njezinu poziciju (kat i (x,y) koordinate)
Public Function GetRoomPos(Room As String) As Point
    Dim temp As Point
    
    rstRoom.MoveFirst
    
    Do
        If rstRoom.Fields(0) = Room Then
            temp.Floor = rstRoom.Fields(3)
            temp.X = rstRoom.Fields(4)
            temp.Y = rstRoom.Fields(5)
            
            GoTo getroompos_
        End If
        rstRoom.MoveNext
    Loop While Not rstRoom.EOF
    
getroompos_:
    GetRoomPos = temp
End Function

' Za dani broj sobe vraca kat na kojem se soba nalazi
Public Function GetFloorNumber(Room As String) As Integer
    Dim FloorNum As Integer

    rstRoom.MoveFirst
    Do
        If rstRoom.Fields(0) = Room Then
            FloorNum = rstRoom.Fields(3)
        End If
        rstRoom.MoveNext
    Loop While Not rstRoom.EOF

    GetFloorNumber = FloorNum
End Function

Public Function GetRoomNodeNumber(Room As String, Floor As Integer) As Integer
    Dim i As Integer
    
    For i = 0 To nRoomNum(Floor) - 1
        If arrNodes(Floor, i).Room = Room Then
            GetRoomNodeNumber = i
        End If
     Next i
End Function

Public Function NodeDist(i As Integer, j As Integer, Floor As Integer) As Single
    NodeDist = Sqr((arrNodes(Floor, i).X - arrNodes(Floor, j).X) ^ 2 + (arrNodes(Floor, i).Y - arrNodes(Floor, j).Y) ^ 2)
End Function

Public Function PathNodeDist(i As Integer, j As Integer, Floor As Integer) As Single
    Dim K As Integer
    Dim ret As Single
    
    ret = -1
    
    For K = 0 To arrNodes(Floor, i).ConnNum - 1
        If arrNodes(Floor, i).NodeList(K) = j Then
            ret = arrNodes(Floor, i).NodeDist(K)
        End If
    Next K
    PathNodeDist = ret
End Function

Public Sub LoadData()
    Dim strFiles(6) As String
    
    Dim i As Integer
    Dim j As Integer
    Dim K As Integer
    Dim KioskNum As Integer
    Dim KioskNodes(5) As Integer
    
    Dim a As Single
    Dim b As Single
    
'    strFiles(0) = "e:\Users\Zvone\projects\Projects Visual Basic\Hypo\Kat0.txt"
'    strFiles(1) = "e:\Users\Zvone\projects\Projects Visual Basic\Hypo\Kat1.txt"
'    strFiles(2) = "e:\Users\Zvone\projects\Projects Visual Basic\Hypo\Kat2.txt"
'    strFiles(3) = "e:\Users\Zvone\projects\Projects Visual Basic\Hypo\Kat3.txt"
'    strFiles(4) = "e:\Users\Zvone\projects\Projects Visual Basic\Hypo\Kat4.txt"
    strFiles(0) = "C:\Hypo\FloorData0.txt"
    strFiles(1) = "C:\Hypo\FloorData1.txt"
    strFiles(2) = "C:\Hypo\FloorData2.txt"
    strFiles(3) = "C:\Hypo\FloorData3.txt"
    strFiles(4) = "C:\Hypo\FloorData4.txt"
    
    For K = 0 To 4
        Open strFiles(K) For Input As 12
        
        ' procitaj poziciju lifta
        Input #12, a, b, LiftDirection
        LiftPos(K).X = a ' * PicWidth
        LiftPos(K).Y = b ' * PicHeight
        
        ' ucitaj broj cvorova
        Input #12, nRoomNum(K)
        
        ' ucitaj indeks cvora koji odgovara liftu
        Input #12, LiftNodeInd(K)
        
        ' ucitaj broj kioska na katu, i njihove indekse
        Input #12, KioskNum
        For i = 0 To 4
            Input #12, KioskNodes(i)
        Next i
        
        ' ucitaj osnovne podatke o svakom pojedinom cvoru
        For i = 0 To nRoomNum(K) - 1
            Input #12, a, b, arrPos(K, i).Room
            arrPos(K, i).X = a '* PicWidth
            arrPos(K, i).Y = b '* PicHeight
            
'            Input #12, arrPos(K, I).X, arrPos(K, I).Y, arrPos(K, I).Room
            
            arrNodes(K, i).X = arrPos(K, i).X
            arrNodes(K, i).Y = arrPos(K, i).Y
            arrNodes(K, i).Room = arrPos(K, i).Room
        Next i
        
        For i = 0 To nRoomNum(K) - 1
            Input #12, arrNodes(K, i).num, arrNodes(K, i).ConnNum
            
            ' sada ucitaj sa kojima je sve cvorovima povezan
            For j = 0 To arrNodes(K, i).ConnNum - 1
                Input #12, arrNodes(K, i).NodeList(j), arrNodes(K, i).NodeDist(j)
                
    '            arrNodes(i).NodeDist(J) = NodeDist(i, arrNodes(i).NodeList(J))
            Next j
        Next i
        
        ' za pocetak cemo staviti da nam na katu postoji samo jedan kiosk
        If K = ThisKioskPos.Floor Then
            KioskNodeInd = KioskNodes(0)
            
            ThisKioskPos.X = arrNodes(K, KioskNodes(0)).X
            ThisKioskPos.Y = arrNodes(K, KioskNodes(0)).Y
        End If
        
        Close #12
    Next K
End Sub

' Funkcija za nalazenje najkraceg puta Dijkstrinim algoritmom
Public Sub FindPath(nStart As Integer, nEnd As Integer, nFloor As Integer, arrRetPath() As Integer, nNodeNum As Integer, PathLen As Single)
    Dim i As Integer
    Dim j As Integer
    Dim K As Integer
    Dim ind As Integer
    Dim ind_pret As Integer
    Dim ind_pret_i As Integer
    Dim num As Integer
    
    Dim s(100) As Handle
    Dim T(100) As Handle
    Dim S_Num As Integer
    Dim T_Num As Integer
    
    Dim arrRetPathHelp(100) As Integer
    
    Dim Min As Integer
    Dim dist1 As Single
    Dim dist2 As Single
    
    S_Num = 0
    T_Num = 0
    
    s(0).NodeInd = nStart
    s(0).Dist = 0
    s(0).Room = arrPos(nFloor, nStart).Room
    S_Num = 1
    
    ' inicijalizacija
    For i = 0 To nRoomNum(nFloor) - 1
        If nStart <> i Then
            T(T_Num).NodeInd = i
            T(T_Num).Room = arrPos(nFloor, i).Room
            
            If DirectLinkDist(nStart, i, nFloor) > 0 Then
                T(T_Num).Dist = DirectLinkDist(nStart, i, nFloor)
            Else
                T(T_Num).Dist = 1000000#
            End If
            
            T_Num = T_Num + 1
        End If
    Next i
    
    While T_Num > 0
        Min = 0
        For i = 1 To T_Num - 1
            If T(i).Dist < T(Min).Dist Then
                Min = i
            End If
        Next i
        
        ' stavljamo nadjeni cvor s minimalnom udaljenoscu
        s(S_Num).Dist = T(Min).Dist
        s(S_Num).NodeInd = T(Min).NodeInd
        s(S_Num).Room = T(Min).Room
        S_Num = S_Num + 1
        '
        ' a iz T[] izbacujemo nadjeni cvor
        For i = Min To T_Num - 2
            T(i).Dist = T(i + 1).Dist
            T(i).NodeInd = T(i + 1).NodeInd
            T(i).Room = T(i + 1).Room
        Next i
        '
        T_Num = T_Num - 1
        
        ' sada za sve preostale elemente iz T treba provjeriti da li su blizi ihodistu
        ' ako se ide preko ubacenog cvora, ili im je blize kao dosad
        For i = 0 To T_Num
            dist1 = T(i).Dist
            
            K = s(S_Num - 1).NodeInd
            j = T(i).NodeInd
            If DirectLinkDist(K, j, nFloor) < 0 Then
                dist2 = s(S_Num - 1).Dist + 1000000#
            Else
                dist2 = s(S_Num - 1).Dist + DirectLinkDist(K, j, nFloor)
            End If
            
            If dist1 < dist2 Then
                T(i).Dist = dist1
            Else
                T(i).Dist = dist2
            End If
        Next i
    Wend
    
    ' sada treba naci kojim redoslijedom cvorova idemo od pocetka do kraja
    
    ' najprije odredjujemo indeks zavrsnog cvora
    For i = 0 To S_Num - 1
        If s(i).NodeInd = nEnd Then
            PathLen = s(i).Dist
            ind = i
        End If
    Next i
    
    arrRetPathHelp(0) = s(ind).NodeInd
    num = 1
    Do
        ' i sada trazimo njegovor prethodnika
        For i = 0 To S_Num - 1
            dist1 = PathNodeDist(s(i).NodeInd, s(ind).NodeInd, nFloor)
            
            If dist1 < 0 Then
                ' ako nema direktne veze izmedju ta dva cvora, ne radi nista
            Else
                dist2 = s(ind).Dist - s(i).Dist
            
                If Abs(dist1 - dist2) < 0.1 Then
                    ind_pret = s(i).NodeInd
                    ind_pret_i = i
                End If
            End If
        Next i
        
        arrRetPathHelp(num) = ind_pret
        num = num + 1
        ind = ind_pret_i
    Loop While s(ind).NodeInd <> nStart
    
    ' i konacno stavljamo prvi (pocetni) cvor u listu
    arrRetPathHelp(num) = ind
    
    ' sada cemo ih poredati u ispravnom redoslijedu
    For i = 0 To num - 1
        arrRetPath(i) = arrRetPathHelp(num - i - 1)
    Next i
    
    For i = 0 To num - 1
        Debug.Print arrPos(nFloor, arrRetPath(i)).Room
    Next i
    
    nNodeNum = num
End Sub

Public Function DirectLinkDist(i As Integer, j As Integer, nFloor As Integer) As Single
    Dim ret As Single
    Dim K As Integer
    
    ret = -1
    ' nadji vezu izmedju cvorova 'i' i 'j'
    For K = 0 To arrNodes(nFloor, i).ConnNum - 1
        ' ako postoji veza izmedju cvorova 'I' i 'J'
        If arrNodes(nFloor, i).NodeList(K) = j Then
            ret = arrNodes(nFloor, i).NodeDist(K)
        End If
    Next K
    
    DirectLinkDist = ret
End Function

Function AccessDate(d As Date) As String
    AccessDate = Format(d, "\#mm\/dd\/yy\#")
End Function
