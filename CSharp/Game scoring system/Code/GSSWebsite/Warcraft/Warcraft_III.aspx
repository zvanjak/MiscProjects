<%@ Page Language="C#" MasterPageFile="~/ZGSSMasterPage.master" AutoEventWireup="true" CodeFile="Warcraft_III.aspx.cs" Inherits="Warcraft_III" Title="Untitled Page" %>
<asp:Content ID="Content1" ContentPlaceHolderID="contentMainPage" Runat="Server">
  &nbsp;&nbsp;
  <div style="width: 1000px; height: 53px; text-align: center">
    <strong><span style="font-size: 14pt; font-family: Tahoma">
      <br />
      Warcraft III liga</span></strong></div>
  <br />
  Iako je upitno dali æemo ikad više baciti Warc, moguænost ostaje pa je liga i dalje
  "otvorena". Ipak, kraljevska disciplina "U pet" se više nikada neæe odigrati. Stoga,
  te rezultate možemo proglasiti konaènim :<br />
  <br />
  &nbsp;<table bgcolor="#ffffff" border="1" cellspacing="0">
    <font color="#000000" face="Arial">
      <caption>
        <b>Rank</b></caption>
    </font>
    <thead>
      <tr>
        <th bgcolor="#c0c0c0" bordercolor="#000000">
          <font color="#000000" face="Arial" style="font-size: 10pt">Name</font></th>
        <th bgcolor="#c0c0c0" bordercolor="#000000">
          <font color="#000000" face="Arial" style="font-size: 10pt">Average ranking</font></th>
        <th bgcolor="#c0c0c0" bordercolor="#000000">
          <font color="#000000" face="Arial" style="font-size: 10pt">Number of games</font></th>
      </tr>
    </thead>
    <tr valign="top">
      <td bordercolor="#c0c0c0">
        <font color="#000000" face="Arial" style="font-size: 10pt">Kruško</font></td>
      <td align="right" bordercolor="#c0c0c0">
        <font color="#000000" face="Arial" style="font-size: 10pt">2,1</font></td>
      <td align="right" bordercolor="#c0c0c0">
        <font color="#000000" face="Arial" style="font-size: 10pt">5</font></td>
    </tr>
    <tr valign="top">
      <td bordercolor="#c0c0c0">
        <font color="#000000" face="Arial" style="font-size: 10pt">Hrvoje</font></td>
      <td align="right" bordercolor="#c0c0c0">
        <font color="#000000" face="Arial" style="font-size: 10pt">2,4</font></td>
      <td align="right" bordercolor="#c0c0c0">
        <font color="#000000" face="Arial" style="font-size: 10pt">5</font></td>
    </tr>
    <tr valign="top">
      <td bordercolor="#c0c0c0">
        <font color="#000000" face="Arial" style="font-size: 10pt">Jure</font></td>
      <td align="right" bordercolor="#c0c0c0">
        <font color="#000000" face="Arial" style="font-size: 10pt">2,6</font></td>
      <td align="right" bordercolor="#c0c0c0">
        <font color="#000000" face="Arial" style="font-size: 10pt">5</font></td>
    </tr>
    <tr valign="top">
      <td bordercolor="#c0c0c0">
        <font color="#000000" face="Arial" style="font-size: 10pt">Zvone</font></td>
      <td align="right" bordercolor="#c0c0c0">
        <font color="#000000" face="Arial" style="font-size: 10pt">2,9</font></td>
      <td align="right" bordercolor="#c0c0c0">
        <font color="#000000" face="Arial" style="font-size: 10pt">5</font></td>
    </tr>
    <tr valign="top">
      <td bordercolor="#c0c0c0">
        <font color="#000000" face="Arial" style="font-size: 10pt">Nidžo</font></td>
      <td align="right" bordercolor="#c0c0c0">
        <font color="#000000" face="Arial" style="font-size: 10pt">5</font></td>
      <td align="right" bordercolor="#c0c0c0">
        <font color="#000000" face="Arial" style="font-size: 10pt">5</font></td>
    </tr>
    <tfoot>
    </tfoot>
  </table>
  <br />
  <asp:LinkButton ID="LinkButton1" runat="server" PostBackUrl="~/Warcraft/Warcraft_III_Ranks.aspx">Rezultati ostalih liga</asp:LinkButton><br />
</asp:Content>

