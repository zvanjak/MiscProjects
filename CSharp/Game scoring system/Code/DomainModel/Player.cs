using System;
using System.Collections.Generic;
using System.Text;

namespace ZGSS.DomainModel
{
  public class Player
  {
    string _name;

    public string Name
    {
      get { return _name; }
      set { _name = value; }
    }

    public Player(string inName)
    {
      _name = inName;
    }
  }
}
