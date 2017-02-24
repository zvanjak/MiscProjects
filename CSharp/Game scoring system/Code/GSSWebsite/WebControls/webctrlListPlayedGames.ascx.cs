using System;
using System.Collections.Generic;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;

using ZGSS.DomainModel;

public partial class WebControls_webctrlListPlayedGames : System.Web.UI.UserControl
{
  List<int> _listGameIDs = null;

  public int NumGames
  {
    get { return _listGameIDs.Count; }
  }

  public void setGameList(List<int> inGames)
  {
    _listGameIDs = inGames;
  }

  protected void Page_Load(object sender, EventArgs e)
  {
    for (int i = 0; i < NumGames; i++)
    {
      ZGSSController controller = (ZGSSController)Application["Domain"];
      PlayedGame game = controller.getGame(_listGameIDs[i]);

      TableRow tempRow = new TableRow();

      TableCell tempCell1 = new TableCell();
      tempCell1.Text = game.PlayedOn.ToShortDateString();
      tempRow.Cells.Add(tempCell1);

      TableCell tempCell2 = new TableCell();
      tempCell2.Text = game.Duration.ToString();
      tempRow.Cells.Add(tempCell2);

      TableCell tempCell3 = new TableCell();
      tempCell3.Text = game.GameType.GameName;
      tempRow.Cells.Add(tempCell3);

      TableCell tempCell4 = new TableCell();
      tempCell4.Text = game.Map.Name;
      tempRow.Cells.Add(tempCell4);

      string players = game.getPlayers();
      TableCell tempCell5 = new TableCell();
      tempCell5.Text = players;
      tempRow.Cells.Add(tempCell5);

      TeamParticipatingInGame winner = game.getWinner();
      TableCell tempCell6 = new TableCell();
      tempCell6.Text = winner.TeamInGame.getTeamName();
      tempRow.Cells.Add(tempCell6);

      TableCell tempCell7 = new TableCell();
      tempCell7.Text = "<a href=\"frmPlayedGame.aspx?GameID=" + game.GameID.ToString() + "\">detalji </a>";
//      tempCell7.Text = "<asp:HyperLink ID=\"HyperLink1\" runat=\"server\" NavigateUrl=\"~/frmPlayedGame.aspx?GameID=0\">detalji</asp:HyperLink>&nbsp;</p>";
      tempRow.Cells.Add(tempCell7);



      tblGameList.Rows.Add(tempRow);
    }

  }
}
