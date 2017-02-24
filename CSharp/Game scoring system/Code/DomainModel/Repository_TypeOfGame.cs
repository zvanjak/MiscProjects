using System;
using System.Collections.Generic;
using System.Text;

namespace ZGSS.DomainModel
{
  public class Repository_TypeOfGame
  {
    List<TypeOfGame> _listTypeOfGame = new List<TypeOfGame>();

    public Repository_TypeOfGame()
    {
      _listTypeOfGame.Add(new TypeOfGame("Warcraft III"));
      _listTypeOfGame.Add(new TypeOfGame("Company of Heroes"));
    }

    public TypeOfGame getGame(string inGameName)
    {
      foreach(TypeOfGame tgame in _listTypeOfGame)
      {
        if( tgame.GameName == inGameName )
          return tgame;
      }
      return null;
    }
  }
}
