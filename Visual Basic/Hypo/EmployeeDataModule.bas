Attribute VB_Name = "EmployeeDataModule"
' globalne varijable u koje æe se uèitati podaci o zaposlenicima
Global EmpNames(1000) As String
Global EmpSurnames(1000) As String
Global EmpTel(1000) As String
Global EmpTitel(1000) As String
Global EmpFloor(1000) As Integer
Global EmpRoom(1000) As String

Global arrEmp(1000) As Employee

Global arrIndSortName(1000) As Integer      ' sortirani indexi
Global arrIndSortSurname(1000) As Integer

Global arrNames(1000) As String

Global EmpNum As Integer

Global cnnEmp As New adodb.Connection
Global rstEmp As New adodb.Recordset

