using System;
using System.Collections.Generic;
using System.Text;

namespace CSC.Model
{
  public class SimilarityResult
  {
    ICodeSimilarityMetricCalculator _usedMetric;
    SolutionsSimilarity[,] _matSolutionsSimilarity = null;

    public SimilarityResult(ProgrammingProblem inProblem, ICodeSimilarityMetricCalculator inMetric)
    {
      _usedMetric = inMetric;

      int numSol = inProblem.ListSolutions.Count;

      _matSolutionsSimilarity = new SolutionsSimilarity[numSol, numSol];
      for(int i=0; i<numSol; i++ )
        for(int j=0; j<numSol; j++ )
        {
          _matSolutionsSimilarity[i,j] = new SolutionsSimilarity();

          _matSolutionsSimilarity[i, j].Solution1 = inProblem.ListSolutions[i];
          _matSolutionsSimilarity[i, j].Solution2 = inProblem.ListSolutions[j];
          _matSolutionsSimilarity[i, j].SimilarityMeasure = 0.0;
        }
    }
    public SolutionsSimilarity getSimilarityObject(int i, int j)
    {
      return _matSolutionsSimilarity[i, j];
    }
    public double getSimilarity(int sol1, int sol2)
    {
      return _matSolutionsSimilarity[sol1,sol2].SimilarityMeasure;
    }
    public void setSimilarity(int sol1, int sol2, double measure)
    {
      _matSolutionsSimilarity[sol1, sol2].SimilarityMeasure = measure;
    }
  }
}
