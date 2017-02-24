using System;
using System.Collections.Generic;
using System.Text;


namespace CSC.Model.Metric
{

   class EditDistanceLinesSansWs : ICodeSimilarityMetricCalculator
   {

      public string GetMetricName()
      {
         return "NE RADI";
      }

      public double[,] BatchSimilarityMeasure(StudentSolution[] sols)
      {
         return new double[sols.Length, sols.Length];
      }

      public double LineDistance(string a, string b)
      {
         int[,] ret = new int[a.Length + 1, b.Length + 1];

         for (int i = 0; i <= a.Length; i++)
            ret[i, 0] = i;
         for (int i = 0; i <= b.Length; i++)
            ret[0, i] = i;

         for (int i = 1; i <= a.Length; i++)
            for (int j = 1; j <= b.Length; j++)
            {
               ret[i, j] = ret[i - 1, j - 1];
               if (a[i - 1] != b[j - 1]) ret[i, j]++;

               if (ret[i - 1, j] + 1 < ret[i, j]) ret[i, j] = ret[i - 1, j] + 1;
               if (ret[i, j - 1] + 1 < ret[i, j]) ret[i, j] = ret[i, j - 1] + 1;
            }

         int sum = a.Length + b.Length;
         return 1.0 * (sum - ret[a.Length, b.Length]) / sum;
      }

      public double CalculateSimilarityMeasure(StudentSolution s1, StudentSolution s2)
      {
         return 0.0;
         int[,] ret = new int[s1.SolutionLines.Count + 1, s2.SolutionLines.Count + 1];

         for (int i = 0; i <= s1.SolutionLines.Count; i++)
            ret[i, 0] = i;
         for (int i = 0; i <= s2.SolutionLines.Count; i++)
            ret[0, i] = i;

         double suma = 0.0;
         int cnt = 0;
         for (int i = 1; i <= s1.SolutionLines.Count; i++)
            for (int j = 1; j <= s2.SolutionLines.Count; j++)
            {
               double ld = LineDistance(s1.SolutionLines[i - 1].ToString(), s2.SolutionLines[j - 1].ToString());
               ret[i, j] = ret[i - 1, j - 1];
               if (ld < 0.90) ret[i, j]++;

               suma += ld;
               cnt++;

               if (ret[i - 1, j] + 1 < ret[i, j]) ret[i, j] = ret[i - 1, j] + 1;
               if (ret[i, j - 1] + 1 < ret[i, j]) ret[i, j] = ret[i, j - 1] + 1;
            }

         int sum = s1.SolutionLines.Count + s2.SolutionLines.Count;
         return 1.0 * (sum - ret[s1.SolutionLines.Count, s2.SolutionLines.Count]) / sum;
      }

   }
}
