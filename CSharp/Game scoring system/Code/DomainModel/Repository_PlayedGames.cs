using System;
using System.Collections.Generic;
using System.Text;

namespace ZGSS.DomainModel
{
  public class Repository_PlayedGames
  {
    List<PlayedGame> _listPlayedGames = new List<PlayedGame>();

    public int Count
    {
      get { return _listPlayedGames.Count; }
    }
    public PlayedGame this[int i]
    {
      get { return _listPlayedGames[i]; }
    }

    public Repository_PlayedGames()
    {
    }

    public void addNewGame(PlayedGame inGame)
    {
      int Count = _listPlayedGames.Count;

      _listPlayedGames.Add(inGame);
      inGame.GameID = Count;
    }
  }
}
