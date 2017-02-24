using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Reflection;
using System.Diagnostics;
using System.Data.OleDb;

namespace CSC.Model
{
  public class ModelManager
  {
    List<ICodeSimilarityMetricCalculator> _listDefinedMetrics = new List<ICodeSimilarityMetricCalculator>();
    List<ProgrammingProblem>              _listLoadedProblems = new List<ProgrammingProblem>();

    public List<ICodeSimilarityMetricCalculator> ListDefinedMetrics
    {
      get { return _listDefinedMetrics; }
    }
    public List<ProgrammingProblem> ListLoadedProblems
    {
      get { return _listLoadedProblems; }
    }

    public ModelManager()
    {
        //Treba optimirati ovo uèitavanje razreda dinamièki
      //AssemblyName[] assemblyNames = Assembly.LoadFrom(Process.GetCurrentProcess().ProcessName + ".exe").GetReferencedAssemblies();
      AssemblyName[] assemblyNames = Assembly.LoadFrom("CodeSimilarityChecker" + ".exe").GetReferencedAssemblies();

      Assembly assembly = null;

      foreach (AssemblyName assemblyName in assemblyNames)
      {
          if (assemblyName.Name.Contains("Model"))
          {
              assembly = Assembly.Load(assemblyName);
          }
      }

      if (assembly == null) return;

      foreach (Type razred in assembly.GetTypes())
      {
          Type[] interfaces = razred.GetInterfaces();
          
          foreach (Type sucelje in interfaces)
          {
              if (sucelje.Name == "ICodeSimilarityMetricCalculator")
              {
                  _listDefinedMetrics.Add((ICodeSimilarityMetricCalculator)razred.GetConstructor(System.Type.EmptyTypes).Invoke(new Object[0]));
              }
          }
      }

    }

    public void LoadProblemFromDirectory(string pathName, string problemID)
    {
      ProgrammingProblem newProblem = new ProgrammingProblem();

      newProblem.ProblemID = problemID;

      // uèitavamo sve fajlove
      DirectoryInfo di = new DirectoryInfo(pathName);
      FileInfo[] rgFiles = di.GetFiles("*.txt");
      
      foreach(FileInfo fi in rgFiles)
      {    
        newProblem.addStudentSolution(fi);
      }

      _listLoadedProblems.Add(newProblem);
    }


	 public void LoadProblemFromDatabase(string pathName)
	 {
		 OleDbConnection dbConnection = new OleDbConnection("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + pathName);
		 dbConnection.Open();

		 OleDbCommand dbCommand = dbConnection.CreateCommand();
		 dbCommand.CommandText = "select * from Pitanje";

		 OleDbDataReader dbReader = dbCommand.ExecuteReader();

		 while (dbReader.Read()){
			 int idPitanja = (int)dbReader.GetValue(1);
			 int idPredmeta = (int)dbReader.GetValue(2);
			 ProgrammingProblem newProblem = new ProgrammingProblem();
			 newProblem.ProblemID = Convert.ToString(idPredmeta) + " - " + Convert.ToString(idPitanja);

			 OleDbCommand solCommand = dbConnection.CreateCommand();
			 solCommand.CommandText = "select * from StudentskoRjesenje WHERE IDPitanja = " + Convert.ToString(idPitanja) + " AND IDPredmeta = " + Convert.ToString(idPredmeta);

			 OleDbDataReader solReader = solCommand.ExecuteReader();

			 while (solReader.Read()) {
				 newProblem.addStudentSolution(solReader.GetValue(7).ToString(), solReader.GetValue(1).ToString());
			 }

			 _listLoadedProblems.Add(newProblem);
		 }



		 // uèitavamo sve fajlove
		 /*DirectoryInfo di = new DirectoryInfo(pathName);
		 FileInfo[] rgFiles = di.GetFiles("*.txt");

		 foreach (FileInfo fi in rgFiles)
		 {
			 newProblem.addStudentSolution(fi);
		 }

		 _listLoadedProblems.Add(newProblem);*/

		 dbConnection.Close();
	 }

    public SimilarityResult Analyze(ICodeSimilarityMetricCalculator selMetric, ProgrammingProblem problem)
    {
      DateTime current = DateTime.Now;
      SimilarityResult result = new SimilarityResult(problem, selMetric);

      for(int i=0; i<problem.NumSol; i++ )
        for(int j=0; j<problem.NumSol; j++ )
        {
          if( i != j )
          {
            StudentSolution sol1 = result.getSimilarityObject(i, j).Solution1;
            StudentSolution sol2 = result.getSimilarityObject(i, j).Solution2;

            double measure = selMetric.CalculateSimilarityMeasure(sol1, sol2);

            result.setSimilarity(i, j, measure);
            result.setSimilarity(j, i, measure);
          }
          else
            result.setSimilarity(i, i, 1.0);    // neæemo ga usporeðivati sa samim sobom
        }
      System.Windows.Forms.MessageBox.Show("Runtime: " + DateTime.Now.Subtract(current).ToString());
      return result;
    }

     public SimilarityResult BatchAnalyze(ICodeSimilarityMetricCalculator selMetric, ProgrammingProblem problem)
     {
        DateTime current = DateTime.Now;
        SimilarityResult result = new SimilarityResult(problem, selMetric);
        StudentSolution[] solutions = new StudentSolution[problem.NumSol];
        for (int i = 0; i < problem.NumSol; i++)
           solutions[i] = result.getSimilarityObject(i,i).Solution1;

        double [,]tmp = new double[problem.NumSol, problem.NumSol];
        tmp = selMetric.BatchSimilarityMeasure(solutions);

        for (int i = 0; i < problem.NumSol; i++)
           for (int j = 0; j < problem.NumSol; j++)
           {
              if (i != j)
              {
                 double measure = tmp[i, j];

                 result.setSimilarity(i, j, measure);
                 result.setSimilarity(j, i, measure);
              }
              else
                 result.setSimilarity(i, i, 1.0);    // neæemo ga usporeðivati sa samim sobom
           }
        System.Windows.Forms.MessageBox.Show("Runtime: " + DateTime.Now.Subtract(current).ToString());
        return result;
     }



  }
}
