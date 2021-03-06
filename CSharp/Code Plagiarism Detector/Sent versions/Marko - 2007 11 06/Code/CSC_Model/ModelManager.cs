using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Reflection;
using System.Diagnostics;

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
        //Treba optimirati ovo u�itavanje razreda dinami�ki
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

//      LoadProblemFromDirectory(@"D:\Users\Zvone\Projects\Code Plagiarism Detector\Data\TestPodaci\3217", "3217");
//      LoadProblemFromDirectory(@"D:\Users\Zvone\Projects\Code Plagiarism Detector\Data\TestPodaci\3222", "3222");
    }

    public void LoadProblemFromDirectory(string pathName, string problemID)
    {
      ProgrammingProblem newProblem = new ProgrammingProblem();

      newProblem.ProblemID = problemID;

      // u�itavamo sve fajlove
      DirectoryInfo di = new DirectoryInfo(pathName);
      FileInfo[] rgFiles = di.GetFiles("*.txt");
      
      foreach(FileInfo fi in rgFiles)
      {    
        newProblem.addStudentSolution(fi);
      }

      _listLoadedProblems.Add(newProblem);
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
            result.setSimilarity(i, i, 1.0);    // ne�emo ga uspore�ivati sa samim sobom
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
                 result.setSimilarity(i, i, 1.0);    // ne�emo ga uspore�ivati sa samim sobom
           }
        System.Windows.Forms.MessageBox.Show("Runtime: " + DateTime.Now.Subtract(current).ToString());
        return result;
     }



  }
}
