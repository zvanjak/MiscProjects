using System;
using System.Collections.Generic;
using System.Text;

namespace ZGSS.DomainModel
{
  public class Repository_Teams
  {
    List<Team> _listTeams = new List<Team>();

    public Repository_Teams()
    {
    }

    public void addNewTeam(Team inTeam)
    {
      _listTeams.Add(inTeam);
    }
  }
}
