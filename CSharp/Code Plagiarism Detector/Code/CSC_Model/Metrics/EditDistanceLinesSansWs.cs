using System;
using System.Collections.Generic;
using System.Collections;
using System.Text;


namespace CSC.Model.Metric {

   class EditDistanceLinesSansWs : ICodeSimilarityMetricCalculator {

      public string GetMetricName() {
         return "EDLinesNoWs(batch)";
      }

      public double[,] BatchSimilarityMeasure(StudentSolution[] sols) {
         string[][] solutions = new string[sols.Length][];
         for (int i = 0; i < sols.Length; i++) {
            solutions[i] = new string[sols[i].SolutionLines.Count];
            for (int j = 0; j < sols[i].SolutionLines.Count; j++) {
               string line = sols[i].SolutionLines[j].ToString();
               string tmp = "";
               for (int k = 0; k < line.Length; k++) {
                  if (!Char.IsWhiteSpace(line[k])) tmp += line[k];
               }
               solutions[i][j] = tmp;
            }
         }

         double[,] ret = new double[sols.Length, sols.Length];

         for (int i = 0; i < solutions.Length; i++)
            for (int j = i + 1; j < solutions.Length; j++) {
               int[,] sol = new int[solutions[i].Length + 1, solutions[j].Length + 1];

               for (int k = 0; k <= solutions[i].Length; k++)
                  sol[k, 0] = k;
               for (int k = 0; k <= solutions[j].Length; k++)
                  sol[0, k] = k;

               for (int k = 1; k <= solutions[i].Length; k++)
                  for (int l = 1; l <= solutions[j].Length; l++) {
                     double ld = LineDistance(solutions[i][k - 1], solutions[j][l - 1]);
                     sol[k, l] = sol[k - 1, l - 1];
                     if (ld < 0.90) sol[k, l]++;

                     if (sol[k - 1, l] + 1 < sol[k, l]) sol[k, l] = sol[k - 1, l] + 1;
                     if (sol[k, l - 1] + 1 < sol[k, l]) sol[k, l] = sol[k, l - 1] + 1;
                  }

               int sum = solutions[i].Length + solutions[j].Length;
               ret[i, j] = ret[j, i] = 1.0 * (sum - sol[solutions[i].Length, solutions[j].Length]) / sum;

            }

         return ret;
      }

      public double LineDistance(string a, string b) {
         int[,] ret = new int[a.Length + 1, b.Length + 1];

         for (int i = 0; i <= a.Length; i++)
            ret[i, 0] = i;
         for (int i = 0; i <= b.Length; i++)
            ret[0, i] = i;

         for (int i = 1; i <= a.Length; i++)
            for (int j = 1; j <= b.Length; j++) {
               ret[i, j] = ret[i - 1, j - 1];
               if (a[i - 1] != b[j - 1]) ret[i, j]++;

               if (ret[i - 1, j] + 1 < ret[i, j]) ret[i, j] = ret[i - 1, j] + 1;
               if (ret[i, j - 1] + 1 < ret[i, j]) ret[i, j] = ret[i, j - 1] + 1;
            }

         int sum = a.Length + b.Length;
         return 1.0 * (sum - ret[a.Length, b.Length]) / sum;
      }

      public double CalculateSimilarityMeasure(StudentSolution s1, StudentSolution s2) {
         return 0.0;
      }

   }
}
