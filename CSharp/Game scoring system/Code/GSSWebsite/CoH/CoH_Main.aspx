<%@ Page Language="C#" MasterPageFile="~/ZGSSMasterPage.master" AutoEventWireup="true" CodeFile="CoH_Main.aspx.cs" Inherits="CoH_Main" Title="Untitled Page" %>

<asp:Content ID="Content1" ContentPlaceHolderID="contentMainPage" Runat="Server">
  <div style="width: 1000px; height: 53px; text-align: center">
    <strong><span style="font-size: 14pt; font-family: Tahoma">
      <br />
      Company of Heroes liga</span></strong></div>
  <br />
  <asp:Label ID="Label1" runat="server" Text="Number of games"></asp:Label>
  <asp:TextBox ID="txtNumGames" runat="server" Enabled="false"></asp:TextBox>
  <br />
  <br />
</asp:Content>

