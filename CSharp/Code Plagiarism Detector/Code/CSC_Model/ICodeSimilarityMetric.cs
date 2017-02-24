using System;
using System.Collections.Generic;
using System.Text;

namespace CSC.Model
{
  public interface ICodeSimilarityMetricCalculator
  {
    string GetMetricName();
    double CalculateSimilarityMeasure(StudentSolution sol1, StudentSolution sol2);
  }


  class EditDistance : ICodeSimilarityMetricCalculator
  {
    int[] lastRow;
    int[] currentRow;

    public EditDistance()
    {
      lastRow = new int[10240];
      currentRow = new int[10240];
    }

    public string GetMetricName()
    {
      return "EditDistance";
    }

    public double CalculateSimilarityMeasure(StudentSolution sol1, StudentSolution sol2)
    {
      if (lastRow.Length < sol2.SolutionCode.Length)
      {
        Array.Resize<int>(ref lastRow, sol2.SolutionCode.Length);
        Array.Resize<int>(ref currentRow, sol2.SolutionCode.Length);
      }

      for (int j = 0; j < sol2.SolutionCode.Length; j++)
      {
        currentRow[j] = j;
      }

      Swap<int[]>(ref currentRow, ref lastRow);

      for (int i = 0; i < sol1.SolutionCode.Length; i++)
      {
        currentRow[0] = i;

        for (int j = 1; j < sol2.SolutionCode.Length; j++)
        {
          currentRow[j] = lastRow[j] + 1;
          currentRow[j] = Math.Min(currentRow[j], currentRow[j - 1] + 1);
          currentRow[j] = Math.Min(currentRow[j], lastRow[j - 1] + (sol1.SolutionCode[i] == sol2.SolutionCode[j] ? 0 : 1) + 1);
        }

        Swap<int[]>(ref currentRow, ref lastRow);
      }

      return 1.0 - (double)currentRow[sol2.SolutionCode.Length - 1] / (sol1.SolutionCode.Length + sol2.SolutionCode.Length);
    }

    private void Swap<T>(ref T a, ref T b)
    {
        T t = a;
        a = b;
        b = t;
    }
  }

  public class EditDistanceSimple : ICodeSimilarityMetricCalculator
  {
    public string GetMetricName()
    {
      return "EditDistanceSimple";
    }

    public double CalculateSimilarityMeasure(StudentSolution sol1, StudentSolution sol2)
    {
      return 0.5;
    }
  }
  public class RandomMetric : ICodeSimilarityMetricCalculator
  {
    Random _rnd;

    public RandomMetric()
    {
      _rnd = new Random(DateTime.Now.Millisecond);
    }
    public string GetMetricName()
    {
      return "RandomMetric";
    }

    public double CalculateSimilarityMeasure(StudentSolution sol1, StudentSolution sol2)
    {
      return (_rnd.Next() % 10000) / 10000.0;
    }
  }
}
