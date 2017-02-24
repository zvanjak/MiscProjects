<%@ Page Language="C#" MasterPageFile="~/ZGSSMasterPage.master" AutoEventWireup="true" CodeFile="frmPlayedGame.aspx.cs" Inherits="frmPlayedGame" Title="Untitled Page" %>
<%@ Reference Control="~\WebControls\ctrlCoHDetailedGameData.ascx" %>
<%@ Reference Control="~\WebControls\ctrlWarcraftDetailedGameData.ascx" %>
<asp:Content ID="Content1" ContentPlaceHolderID="contentMainPage" Runat="Server">
   <br />
    <asp:Table ID="tblData" runat="server" Height="82px" Width="371px">
      <asp:TableRow ID="TableRow0" runat="server">
        <asp:TableCell runat="server">Datum</asp:TableCell>
        <asp:TableCell runat="server"></asp:TableCell>
      </asp:TableRow>
      <asp:TableRow ID="TableRow1" runat="server">
        <asp:TableCell ID="TableCell1" runat="server">Trajanje</asp:TableCell>
        <asp:TableCell ID="cellDuration" runat="server"></asp:TableCell>
      </asp:TableRow>
      <asp:TableRow ID="TableRow2" runat="server">
        <asp:TableCell ID="TableCell3" runat="server">Vrsta igre</asp:TableCell>
        <asp:TableCell ID="TableCell4" runat="server"></asp:TableCell>
      </asp:TableRow>
      <asp:TableRow ID="TableRow3" runat="server">
        <asp:TableCell ID="TableCell5" runat="server">Mapa</asp:TableCell>
        <asp:TableCell ID="TableCell6" runat="server"></asp:TableCell>
      </asp:TableRow>
      <asp:TableRow ID="TableRow4" runat="server">
        <asp:TableCell ID="TableCell7" runat="server">Podatke unio</asp:TableCell>
        <asp:TableCell ID="TableCell8" runat="server"></asp:TableCell>
      </asp:TableRow>
    
    </asp:Table>
  <br />
  <asp:PlaceHolder ID="GameDataPlaceHolder" runat="server"></asp:PlaceHolder>
</asp:Content>

