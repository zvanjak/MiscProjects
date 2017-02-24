using System;
using System.Collections.Generic;
using System.Text;

namespace CSC.Model
{
  public interface ICodeSimilarityMetricCalculator
  {
    string GetMetricName();
    double CalculateSimilarityMeasure(StudentSolution sol1, StudentSolution sol2);
    double[,] BatchSimilarityMeasure(StudentSolution[] sols);
  }

}
