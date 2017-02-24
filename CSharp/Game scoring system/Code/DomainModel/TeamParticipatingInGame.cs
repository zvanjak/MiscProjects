using System;
using System.Collections.Generic;
using System.Text;

namespace ZGSS.DomainModel
{
  public class TeamParticipatingInGame
  {
    Team _team;
    TeamStatisticsInGame _teamStat;
    float _rankInGame;

    public Team TeamInGame
    {
      get { return _team; }
      set { _team = value; }
    }
    public float RankInGame
    {
      get { return _rankInGame; }
      set { _rankInGame = value; }
    }
    public TeamStatisticsInGame TeamStat
    {
      get { return _teamStat; }
      set { _teamStat = value; }
    }
  }
}
