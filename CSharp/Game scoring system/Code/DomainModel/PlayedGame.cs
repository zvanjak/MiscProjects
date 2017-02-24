using System;
using System.Collections.Generic;
using System.Text;

namespace ZGSS.DomainModel
{
  public class PlayedGame
  {
    int _gameID;

    DateTime _playedOn;
    TimeSpan _duration;
    TypeOfGame _gameType;
    Map _map;

    Player _dataEnteredBy;
    PlayedGameComments _comments;
    List<TeamParticipatingInGame> _listParticipatingTeams = new List<TeamParticipatingInGame>();

    public int GameID
    {
      get { return _gameID; }
      set { _gameID = value; }
    }
    public DateTime PlayedOn
    {
      get { return _playedOn; }
      set { _playedOn = value; }
    }
    public TimeSpan Duration
    {
      get { return _duration; }
      set { _duration = value; }
    }
    public TypeOfGame GameType
    {
      get { return _gameType; }
      set { _gameType = value; }
    }
    public Map Map
    {
      get { return _map; }
      set { _map = value; }
    }
    public Player DataEnteredBy
    {
      get { return _dataEnteredBy; }
      set { _dataEnteredBy = value; }
    }

    public void addParticipatingTeam(TeamParticipatingInGame inTeam)
    {
      _listParticipatingTeams.Add(inTeam);
    }

    public string getPlayers()
    {
      StringBuilder str = new StringBuilder();

      foreach (TeamParticipatingInGame team in _listParticipatingTeams)
      {
        str.Append(team.TeamInGame.getTeamName());
        str.Append(" (");
        str.Append((team.TeamStat as CoHGameStatistic).PlayedAs);
        str.Append(") ");
        str.Append(", ");
      }
      return str.ToString();
    }

    public TeamParticipatingInGame getWinner()
    {
      foreach(TeamParticipatingInGame team in _listParticipatingTeams)
      {
        if( team.RankInGame == 1.0 )
          return team;
      }
      return null;
    }
  }
}
