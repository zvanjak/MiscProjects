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

public partial class CoH_Main : System.Web.UI.Page
{

  protected void Page_Load(object sender, EventArgs e)
  {
    ZGSSController controller = (ZGSSController) Application["Domain"];

    txtNumGames.Text = controller.getNumGames().ToString();

  }
}
