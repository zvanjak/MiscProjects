<%@ Control Language="C#" AutoEventWireup="true" CodeFile="webctrlListPlayedGames.ascx.cs" Inherits="WebControls_webctrlListPlayedGames" %>
<asp:Table ID="tblGameList" runat="server" BorderStyle="Double" BackColor="Aqua" Caption="List of played games" Height="190px" Width="786px" BorderColor="Black" GridLines="Horizontal">
  <asp:TableRow ID="header" runat="server" BorderColor="Black" BorderStyle="Solid" Font-Bold="True">
    <asp:TableCell runat="server">Datum</asp:TableCell>
    <asp:TableCell runat="server">Trajanje</asp:TableCell>
    <asp:TableCell runat="server">Igra</asp:TableCell>
    <asp:TableCell runat="server">Mapa</asp:TableCell>
    <asp:TableCell runat="server">Igrali su</asp:TableCell>
    <asp:TableCell runat="server">Pobjednik</asp:TableCell>
    <asp:TableCell runat="server">Detalji</asp:TableCell>
  </asp:TableRow>
</asp:Table>