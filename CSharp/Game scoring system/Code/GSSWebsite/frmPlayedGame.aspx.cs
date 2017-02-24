using System;
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

/// <summary>
/// Ova stranica preko Request objekta i QueryStringa prima ID odigrane igre koju treba prikazati
/// </summary>
public partial class frmPlayedGame : System.Web.UI.Page
{
  int   _gameID;

  protected void Page_Load(object sender, EventArgs e)
  {
    if (!Page.IsPostBack)
    {
      _gameID = Convert.ToInt32(Request.Params["GameID"]);

      ZGSSController controller = (ZGSSController)Application["Domain"];

      PlayedGame game = controller.getGame(_gameID);

      tblData.Rows[0].Cells[1].Text = game.PlayedOn.ToString();

      if( game.GameType.GameName == "Company of Heroes")
      {
        ASP.webcontrols_ctrlcohdetailedgamedata_ascx newCtrl = (ASP.webcontrols_ctrlcohdetailedgamedata_ascx)LoadControl("~/WebControls/ctrlCoHDetailedGameData.ascx");
        GameDataPlaceHolder.Controls.Add(newCtrl);
      }
      else if( game.GameType.GameName == "Warcraft III")
      {
        ASP.webcontrols_ctrlwarcraftdetailedgamedata_ascx newCtrl = (ASP.webcontrols_ctrlwarcraftdetailedgamedata_ascx)LoadControl("~/WebControls/ctrlWarcraftDetailedGameData.ascx");
        GameDataPlaceHolder.Controls.Add(newCtrl);
      }

    }
  }
}
