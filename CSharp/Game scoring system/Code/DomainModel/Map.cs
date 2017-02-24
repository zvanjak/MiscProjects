using System;
using System.Collections.Generic;
using System.Text;

namespace ZGSS.DomainModel
{
  public class Map
  {
    string _numOfPlayers;
    string _name;
    string _size;
    TypeOfGame _typeOfGame;

    public string NumOfPlayers
    {
      get { return _numOfPlayers; }
      set { _numOfPlayers = value; }
    }
    public string Name
    {
      get { return _name; }
      set { _name = value; }
    }
    public string Size
    {
      get { return _size; }
      set { _size = value; }
    }
    public TypeOfGame GameType
    {
      get { return _typeOfGame; }
      set { _typeOfGame = value; }
    }

    public Map()
    {
    }
    public Map(string inName, string inNumPlayers, string inSize, TypeOfGame inType)
    {
      Name = inName;
      NumOfPlayers = inNumPlayers;
      Size = inSize;
      GameType = inType;
    }
  }
}
