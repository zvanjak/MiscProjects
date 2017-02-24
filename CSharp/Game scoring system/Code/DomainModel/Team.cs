using System;
using System.Collections.Generic;
using System.Text;

namespace ZGSS.DomainModel
{
  public class Team
  {
    string _name;

    List<Player> _teamPlayers = new List<Player>();

    public Team(string inName)
    {
      _name = inName;
    }
    public Team(string inName, Player team1) : this(inName)
    {
      _teamPlayers.Add(team1);
    }
    public Team(string inName, Player team1, Player team2)
      : this(inName, team1)
    {
      _teamPlayers.Add(team2);
    }

    public string getTeamName()
    {
      StringBuilder str = new StringBuilder();

      int count = 0;
      foreach(Player pl in _teamPlayers)
      {
        str.Append(pl.Name);
        ++count;

        if( count > 1 )
          str.Append(" + ");
      }

      return str.ToString();
    }
  }
}
