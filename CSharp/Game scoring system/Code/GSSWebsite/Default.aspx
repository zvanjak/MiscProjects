<%@ Page Language="C#" AutoEventWireup="true"  CodeFile="Default.aspx.cs" Inherits="_Default" %>

<%@ Register Src="WebControls/webctrlListPlayedGames.ascx" TagName="webctrlListPlayedGames"
  TagPrefix="uc1" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>ZGSS Main page</title>
    <link href="StyleSheet.css" rel="stylesheet" type="text/css" />
</head>
<body>
    <form id="form1" runat="server">
    <div style="text-align: center">
      <span style="font-size: 16pt; font-family: Tahoma"><strong>Zvonin Game Scoring System<br />
      </strong></span>
      <br />
    </div>
    <h1>Aktivne igre </h1>
    <div style="text-align: left">
        <ul>
          <li>
            <asp:LinkButton ID="LinkButton1" runat="server" PostBackUrl="~/Warcraft/Warcraft_III.aspx">Warcraft III</asp:LinkButton></li>
          <li>
            <asp:LinkButton ID="LinkButton2" runat="server" PostBackUrl="~/CoH/CoH_Main.aspx">Company of Heroes</asp:LinkButton></li>
        </ul>
    </div>
    <h1>Recently played games</h1>
    <p>
      <asp:HyperLink ID="HyperLink1" runat="server" NavigateUrl="~/frmPlayedGame.aspx?GameID=0">HyperLink</asp:HyperLink>&nbsp;</p>
    <p>
      <uc1:webctrlListPlayedGames ID="ctrlRecentlyPlayedGames" runat="server" />&nbsp;
    </p>
    <p>&nbsp;</p>
    <p>
      <asp:Panel ID="Panel1" runat="server" Height="127px" Width="523px">
      </asp:Panel>
    </p>
    <br />Novosti:<br />
    </form>
</body>
</html>
