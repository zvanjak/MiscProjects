using System;
using System.Collections.Generic;
using System.Text;

namespace ZGSS.DomainModel
{
  public class ZGSSController
  {
    ZGSSDataModel _data = new ZGSSDataModel();

    Repository_Players     _repPlayers = new Repository_Players();
    Repository_Teams       _repTeams = new Repository_Teams();
    Repository_PlayedGames _repGames = new Repository_PlayedGames();
    Repository_TypeOfGame  _repTypeOfGame = new Repository_TypeOfGame();
    Repository_Maps        _repMaps = new Repository_Maps();

    public int getNumGames()
    {
      return _repGames.Count;
    }

    public PlayedGame getGame(int inGameID)
    {
      return _repGames[inGameID];
    }

    public List<int> getRecentGames()
    {
      List<int> listGames = new List<int>();

      listGames.Add(5);
      listGames.Add(4);
      listGames.Add(3);
      listGames.Add(2);
      listGames.Add(1);
      listGames.Add(0);

      return listGames;
    }

    public void InitializeData()
    {
      _repMaps.addMap("Angoville", "2", "Small", _repTypeOfGame.getGame("Company of Heroes"));

      Player plZvone  = _repPlayers.addPlayer("Zvone");
      Player plHrvoje = _repPlayers.addPlayer("Hrvoje");
      Player plKrusko = _repPlayers.addPlayer("Kruško");
      Player plJure   = _repPlayers.addPlayer("Jure");
      Player plNidzo  = _repPlayers.addPlayer("Nidžo");

      Team tZv = new Team("Zvone", plZvone);
      Team tHr = new Team("Hrvoje", plHrvoje);
      Team tKr = new Team("Kruško", plKrusko);
      Team tJu = new Team("Jure", plJure);
      Team tNi = new Team("Nidžo", plNidzo);
      Team t1 = new Team("Zvone & Hrvoje", plZvone, plHrvoje);
      Team t2 = new Team("Zvone & Jure", plZvone, plJure);
      Team t3 = new Team("Zvone & Kruško", plZvone, plKrusko);
      Team t4 = new Team("Zvone & Nidžo", plZvone, plNidzo);
      Team t5 = new Team("Hrvoje & Jure", plHrvoje, plJure);

      PlayedGame prva = new PlayedGame();

      prva.Map      = _repMaps.getMap("Angoville");
      prva.GameType = _repTypeOfGame.getGame("Company of Heroes");
      prva.PlayedOn = new DateTime(2007, 1, 19);
      prva.Duration = new TimeSpan(0, 33, 44);
      prva.DataEnteredBy = plZvone;

      TeamParticipatingInGame tg1 = new TeamParticipatingInGame();
      tg1.TeamInGame = tZv;
      tg1.RankInGame = 1.0F;
      tg1.TeamStat = new CoHGameStatistic(CoHSides.AXIS, 500, -1, 28342);
      TeamParticipatingInGame tg2 = new TeamParticipatingInGame();
      tg2.TeamInGame = tKr;
      tg2.RankInGame = 2.0F;
      tg2.TeamStat = new CoHGameStatistic(CoHSides.ALLIED, 500, -1, 14899);

      prva.addParticipatingTeam(tg1);
      prva.addParticipatingTeam(tg2);

      _repGames.addNewGame(prva);

      PlayedGame druga = new PlayedGame();

      druga.Map = _repMaps.getMap("Angoville");
      druga.GameType = _repTypeOfGame.getGame("Company of Heroes");
      druga.PlayedOn = new DateTime(2007, 2, 13,21, 45, 0);
      druga.Duration = new TimeSpan(0, 34, 12);
      druga.DataEnteredBy = plZvone;

      TeamParticipatingInGame tg21 = new TeamParticipatingInGame();
      tg21.TeamInGame = tZv;
      tg21.RankInGame = 1.0F;
      tg21.TeamStat = new CoHGameStatistic(CoHSides.AXIS, 1000, 1000, 24801);
      TeamParticipatingInGame tg22 = new TeamParticipatingInGame();
      tg22.TeamInGame = tKr;
      tg22.RankInGame = 2.0F;
      tg22.TeamStat = new CoHGameStatistic(CoHSides.ALLIED, 1000, 357, 15604);

      druga.addParticipatingTeam(tg21);
      druga.addParticipatingTeam(tg22);

      _repGames.addNewGame(druga);

      PlayedGame treca = new PlayedGame();

      treca.Map = _repMaps.getMap("Angoville");
      treca.GameType = _repTypeOfGame.getGame("Company of Heroes");
      treca.PlayedOn = new DateTime(2007, 2, 25, 21, 30, 0);
      treca.Duration = new TimeSpan(0, 23, 57);
      treca.DataEnteredBy = plZvone;

      TeamParticipatingInGame tg31 = new TeamParticipatingInGame();
      tg31.TeamInGame = tZv;
      tg31.RankInGame = 1.0F;
      tg31.TeamStat = new CoHGameStatistic(CoHSides.AXIS, 500, 497, 15064);
      TeamParticipatingInGame tg32 = new TeamParticipatingInGame();
      tg32.TeamInGame = tKr;
      tg32.RankInGame = 2.0F;
      tg32.TeamStat = new CoHGameStatistic(CoHSides.ALLIED, 500, 94, 4349);

      treca.addParticipatingTeam(tg31);
      treca.addParticipatingTeam(tg32);

      _repGames.addNewGame(treca);

      PlayedGame game4 = new PlayedGame();

      game4.Map = _repMaps.getMap("Angoville");
      game4.GameType = _repTypeOfGame.getGame("Company of Heroes");
      game4.PlayedOn = new DateTime(2007, 2, 13, 21, 45, 0);
      game4.Duration = new TimeSpan(0, 33, 00);
      game4.DataEnteredBy = plZvone;

      TeamParticipatingInGame tg41 = new TeamParticipatingInGame();
      tg41.TeamInGame = tJu;
      tg41.RankInGame = 1.0F;
      tg41.TeamStat = new CoHGameStatistic(CoHSides.AXIS, 500, 370, -1);
      TeamParticipatingInGame tg42 = new TeamParticipatingInGame();
      tg42.TeamInGame = tKr;
      tg42.RankInGame = 2.0F;
      tg42.TeamStat = new CoHGameStatistic(CoHSides.ALLIED, 500, 180, -1);

      game4.addParticipatingTeam(tg41);
      game4.addParticipatingTeam(tg42);

      _repGames.addNewGame(game4);

      PlayedGame game5 = new PlayedGame();

      game5.Map = _repMaps.getMap("Angoville");
      game5.GameType = _repTypeOfGame.getGame("Company of Heroes");
      game5.PlayedOn = new DateTime(2007, 2, 26, 22, 00, 0);
      game5.Duration = new TimeSpan(0, 22,39);
      game5.DataEnteredBy = plZvone;

      TeamParticipatingInGame tg51 = new TeamParticipatingInGame();
      tg51.TeamInGame = tZv;
      tg51.RankInGame = 1.0F;
      tg51.TeamStat = new CoHGameStatistic(CoHSides.AXIS, 500, 498, 13623);
      TeamParticipatingInGame tg52 = new TeamParticipatingInGame();
      tg52.TeamInGame = tJu;
      tg52.RankInGame = 2.0F;
      tg52.TeamStat = new CoHGameStatistic(CoHSides.ALLIED, 500, 126, 8550);

      game5.addParticipatingTeam(tg51);
      game5.addParticipatingTeam(tg52);

      _repGames.addNewGame(game5);

      PlayedGame game6 = new PlayedGame();

      game6.Map = _repMaps.getMap("Angoville");
      game6.GameType = _repTypeOfGame.getGame("Company of Heroes");
      game6.PlayedOn = new DateTime(2007, 2, 26, 22, 30, 0);
      game6.Duration = new TimeSpan(0, 39, 49);
      game6.DataEnteredBy = plZvone;

      TeamParticipatingInGame tg61 = new TeamParticipatingInGame();
      tg61.TeamInGame = tZv;
      tg61.RankInGame = 1.0F;
      tg61.TeamStat = new CoHGameStatistic(CoHSides.AXIS, 500, 312, 32107);
      TeamParticipatingInGame tg62 = new TeamParticipatingInGame();
      tg62.TeamInGame = tJu;
      tg62.RankInGame = 2.0F;
      tg62.TeamStat = new CoHGameStatistic(CoHSides.ALLIED, 500, 123, 22204);

      game6.addParticipatingTeam(tg61);
      game6.addParticipatingTeam(tg62);

      _repGames.addNewGame(game6);

      // sredio Nidžu 2 x Angoville na anihilated, 11.5.2008, prva 40:40, druga 1:10
    }
  }
}
