Attribute VB_Name = "GraphModule"
Option Explicit
Option Base 0

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
    Dim I As Integer
    Dim J As Integer
    
    Open "C:\Hypo\FloorNum.txt" For Input As #15
    Input #15, ThisKioskPos.Floor
    
'    ThisKioskPos.X = 7170
'    ThisKioskPos.Y = 2940
    
    ThisKioskDirection = 150
    
'    KioskNodeInd = 18
    
'    LiftNodeInd = 23
'    LiftDirection = 300

    For J = 0 To FLOOR_NUM
        nRoomNum(J) = 0
    Next J
    
    For J = 0 To FLOOR_NUM
        For I = 0 To MAX_NODE_NUM
            arrNodes(J, I).ConnNum = 0
        Next I
    Next J
    
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
    Dim I As Integer
    
    For I = 0 To nRoomNum(Floor) - 1
        If arrNodes(Floor, I).Room = Room Then
            GetRoomNodeNumber = I
        End If
     Next I
End Function

Public Function NodeDist(I As Integer, J As Integer, Floor As Integer) As Single
    NodeDist = Sqr((arrNodes(Floor, I).X - arrNodes(Floor, J).X) ^ 2 + (arrNodes(Floor, I).Y - arrNodes(Floor, J).Y) ^ 2)
End Function

Public Function PathNodeDist(I As Integer, J As Integer, Floor As Integer) As Single
    Dim K As Integer
    Dim ret As Single
    
    ret = -1
    
    For K = 0 To arrNodes(Floor, I).ConnNum - 1
        If arrNodes(Floor, I).NodeList(K) = J Then
            ret = arrNodes(Floor, I).NodeDist(K)
        End If
    Next K
    PathNodeDist = ret
End Function

Public Sub LoadData()
    Dim strFiles(6) As String
    
    Dim I As Integer
    Dim J As Integer
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
        For I = 0 To 4
            Input #12, KioskNodes(I)
        Next I
        
        ' ucitaj osnovne podatke o svakom pojedinom cvoru
        For I = 0 To nRoomNum(K) - 1
            Input #12, a, b, arrPos(K, I).Room
            arrPos(K, I).X = a '* PicWidth
            arrPos(K, I).Y = b '* PicHeight
            
'            Input #12, arrPos(K, I).X, arrPos(K, I).Y, arrPos(K, I).Room
            
            arrNodes(K, I).X = arrPos(K, I).X
            arrNodes(K, I).Y = arrPos(K, I).Y
            arrNodes(K, I).Room = arrPos(K, I).Room
        Next I
        
        For I = 0 To nRoomNum(K) - 1
            Input #12, arrNodes(K, I).num, arrNodes(K, I).ConnNum
            
            ' sada ucitaj sa kojima je sve cvorovima povezan
            For J = 0 To arrNodes(K, I).ConnNum - 1
                Input #12, arrNodes(K, I).NodeList(J), arrNodes(K, I).NodeDist(J)
                
    '            arrNodes(i).NodeDist(J) = NodeDist(i, arrNodes(i).NodeList(J))
            Next J
        Next I
        
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
    Dim I As Integer
    Dim J As Integer
    Dim K As Integer
    Dim ind As Integer
    Dim ind_pret As Integer
    Dim ind_pret_i As Integer
    Dim num As Integer
    
    Dim S(100) As Handle
    Dim T(100) As Handle
    Dim S_Num As Integer
    Dim T_Num As Integer
    
    Dim arrRetPathHelp(100) As Integer
    
    Dim Min As Integer
    Dim dist1 As Single
    Dim dist2 As Single
    
    S_Num = 0
    T_Num = 0
    
    S(0).NodeInd = nStart
    S(0).Dist = 0
    S(0).Room = arrPos(nFloor, nStart).Room
    S_Num = 1
    
    ' inicijalizacija
    For I = 0 To nRoomNum(nFloor) - 1
        If nStart <> I Then
            T(T_Num).NodeInd = I
            T(T_Num).Room = arrPos(nFloor, I).Room
            
            If DirectLinkDist(nStart, I, nFloor) > 0 Then
                T(T_Num).Dist = DirectLinkDist(nStart, I, nFloor)
            Else
                T(T_Num).Dist = 1000000#
            End If
            
            T_Num = T_Num + 1
        End If
    Next I
    
    While T_Num > 0
        Min = 0
        For I = 1 To T_Num - 1
            If T(I).Dist < T(Min).Dist Then
                Min = I
            End If
        Next I
        
        ' stavljamo nadjeni cvor s minimalnom udaljenoscu
        S(S_Num).Dist = T(Min).Dist
        S(S_Num).NodeInd = T(Min).NodeInd
        S(S_Num).Room = T(Min).Room
        S_Num = S_Num + 1
        '
        ' a iz T[] izbacujemo nadjeni cvor
        For I = Min To T_Num - 2
            T(I).Dist = T(I + 1).Dist
            T(I).NodeInd = T(I + 1).NodeInd
            T(I).Room = T(I + 1).Room
        Next I
        '
        T_Num = T_Num - 1
        
        ' sada za sve preostale elemente iz T treba provjeriti da li su blizi ihodistu
        ' ako se ide preko ubacenog cvora, ili im je blize kao dosad
        For I = 0 To T_Num
            dist1 = T(I).Dist
            
            K = S(S_Num - 1).NodeInd
            J = T(I).NodeInd
            If DirectLinkDist(K, J, nFloor) < 0 Then
                dist2 = S(S_Num - 1).Dist + 1000000#
            Else
                dist2 = S(S_Num - 1).Dist + DirectLinkDist(K, J, nFloor)
            End If
            
            If dist1 < dist2 Then
                T(I).Dist = dist1
            Else
                T(I).Dist = dist2
            End If
        Next I
    Wend
    
    ' sada treba naci kojim redoslijedom cvorova idemo od pocetka do kraja
    
    ' najprije odredjujemo indeks zavrsnog cvora
    For I = 0 To S_Num - 1
        If S(I).NodeInd = nEnd Then
            PathLen = S(I).Dist
            ind = I
        End If
    Next I
    
    arrRetPathHelp(0) = S(ind).NodeInd
    num = 1
    Do
        ' i sada trazimo njegovor prethodnika
        For I = 0 To S_Num - 1
            dist1 = PathNodeDist(S(I).NodeInd, S(ind).NodeInd, nFloor)
            
            If dist1 < 0 Then
                ' ako nema direktne veze izmedju ta dva cvora, ne radi nista
            Else
                dist2 = S(ind).Dist - S(I).Dist
            
                If Abs(dist1 - dist2) < 0.1 Then
                    ind_pret = S(I).NodeInd
                    ind_pret_i = I
                End If
            End If
        Next I
        
        arrRetPathHelp(num) = ind_pret
        num = num + 1
        ind = ind_pret_i
    Loop While S(ind).NodeInd <> nStart
    
    ' i konacno stavljamo prvi (pocetni) cvor u listu
    arrRetPathHelp(num) = ind
    
    ' sada cemo ih poredati u ispravnom redoslijedu
    For I = 0 To num - 1
        arrRetPath(I) = arrRetPathHelp(num - I - 1)
    Next I
    
    For I = 0 To num - 1
        Debug.Print arrPos(nFloor, arrRetPath(I)).Room
    Next I
    
    nNodeNum = num
End Sub

Public Function DirectLinkDist(I As Integer, J As Integer, nFloor As Integer) As Single
    Dim ret As Single
    Dim K As Integer
    
    ret = -1
    ' nadji vezu izmedju cvorova 'i' i 'j'
    For K = 0 To arrNodes(nFloor, I).ConnNum - 1
        ' ako postoji veza izmedju cvorova 'I' i 'J'
        If arrNodes(nFloor, I).NodeList(K) = J Then
            ret = arrNodes(nFloor, I).NodeDist(K)
        End If
    Next K
    
    DirectLinkDist = ret
End Function

Function AccessDate(d As Date) As String
    AccessDate = Format(d, "\#mm\/dd\/yy\#")
End Function
