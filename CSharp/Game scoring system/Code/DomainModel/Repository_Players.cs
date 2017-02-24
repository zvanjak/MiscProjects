using System;
using System.Collections.Generic;
using System.Text;

namespace ZGSS.DomainModel
{
  public class Repository_Players
  {
    List<Player> _listPlayers = new List<Player>();

    public Repository_Players()
    {
    }

    public Player addPlayer(string inPlayerName)
    {
      Player newPlayer = new Player(inPlayerName);
      _listPlayers.Add(newPlayer);

      return newPlayer;
    }
  }
}
