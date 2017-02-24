using System;
using System.Collections.Generic;
using System.Text;

namespace ZGSS.DomainModel
{
  public class CoHGameStatistic : TeamStatisticsInGame
  {
    CoHSides _playedAs;

    int _victoryPointsTotalInGame;
    int _victoryPointsRemaining;
    int _totalPoints;

    public CoHSides PlayedAs
    {
      get { return _playedAs; }
      set { _playedAs = value; }
    }
    public int VictoryPointsTotalInGame
    {
      get { return _victoryPointsTotalInGame; }
      set { _victoryPointsTotalInGame = value; }
    }
    public int VictoryPointsRemaining
    {
      get { return _victoryPointsRemaining; }
      set { _victoryPointsRemaining = value; }
    }
    public int TotalPoints
    {
      get { return _totalPoints; }
      set { _totalPoints = value; }
    }

    public CoHGameStatistic(CoHSides inSide, int inVPTotal, int inVPRemaining, int inPoints)
    {
      _playedAs = inSide;
      _victoryPointsTotalInGame = inVPTotal;
      _victoryPointsRemaining = inVPRemaining;
      _totalPoints = inPoints;
    }
  }
}
