using System;
using System.Collections.Generic;
using System.Text;

namespace ZGSS.DomainModel
{
  public class Repository_Maps
  {
    List<Map> _listMaps = new List<Map>();

    public Repository_Maps()
    {
    }

    public Map getMap(string inMapName)
    {
      foreach (Map tmap in _listMaps)
      {
        if (tmap.Name == inMapName)
          return tmap;
      }
      return null;
    }
    public void addMap(string inName, string inNumPlayers, string inSize, TypeOfGame inType)
    {
      Map newMap = new Map(inName, inNumPlayers, inSize, inType);
      _listMaps.Add(newMap);
    }

  }
}
