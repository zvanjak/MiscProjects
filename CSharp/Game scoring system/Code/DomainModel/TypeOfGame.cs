using System;
using System.Collections.Generic;
using System.Text;

namespace ZGSS.DomainModel
{
  public class TypeOfGame
  {
    string _gameName;

    public string GameName
    {
      get { return _gameName; }
      set { _gameName = value; }
    }

    public TypeOfGame(string inGameName)
    {
      GameName = inGameName;
    }
  }
}
