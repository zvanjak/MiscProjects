using System;
using System.Collections.Generic;
using System.Text;

namespace CSC.Model.Metric
{

   class EditDistanceSansWs : ICodeSimilarityMetricCalculator
   {

      public string GetMetricName()
      {
         return "EditDistanceSansWs(batch)";
      }

      public double[,] BatchSimilarityMeasure(StudentSolution[] sols)
      {
         string[] code = new string[sols.Length];

         for (int i = 0; i < sols.Length; i++)
         {
            for (int j = 0; j < sols[i].SolutionCode.Length; j++)
            {
               if (!Char.IsWhiteSpace(sols[i].SolutionCode[j]))
               {
                  code[i] += sols[i].SolutionCode[j];
               }
            }
				if (code[i] == null) code[i] = "";
         }

         double[,] ret = new double[sols.Length, sols.Length];

         for (int oi = 0; oi < sols.Length; oi++)
            for (int oj = oi + 1; oj < sols.Length; oj++)
            {
               int len1 = code[oi].Length;
               int len2 = code[oj].Length;
               int[,] sol = new int[2, len2 + 1];
               int current = 1;

               for (int i = 0; i <= len2; i++)
                  sol[0, i] = i;

               for (int i = 1; i <= len1; i++)
               {
                  sol[current, 0] = i;
                  for (int j = 1; j <= len2; j++)
                  {
                     int cost = 1;
                     if (code[oi][i - 1] == code[oj][j - 1]) cost = 0;

                     sol[current, j] = sol[(current + 1) & 1, j] + 1;
                     if (sol[current, j] > sol[current, j - 1] + 1) sol[current, j] = sol[current, j - 1] + 1;
                     if (sol[current, j] > sol[(current + 1) & 1, j - 1] + cost) sol[current, j] = sol[(current + 1) & 1, j - 1] + cost;

                  }
                  if (current == 1) current = 0;
                  else current = 1;
               }
               int sumOfLengths = len1 + len2;

               ret[oi,oj] = ret[oj, oi] = 1.0 * (sumOfLengths - sol[(current + 1) & 1, len2]) / sumOfLengths;
            }

         return ret;
      }


      public double CalculateSimilarityMeasure(StudentSolution s1, StudentSolution s2)
      {
         string code1 = s1.SolutionCode;
         string code2 = s2.SolutionCode;

         for (int i = 1; i < code1.Length; i++)
         {
            if (Char.IsWhiteSpace(code1[i]))
            {
               code1.Remove(i, 1);
               i--;
            }
         }
         for (int i = 1; i < code2.Length; i++)
         {
            if (Char.IsWhiteSpace(code2[i]))
            {
               code2.Remove(i, 1);
               i--;
            }
         }
         int len1 = code1.Length;
         int len2 = code2.Length;

         int[,] sol = new int[2, len2 + 1];
         int current = 1;

         for (int i = 0; i <= len2; i++)
            sol[0, i] = i;

         for (int i = 1; i <= len1; i++)
         {
            sol[current, 0] = i;
            for (int j = 1; j <= len2; j++)
            {
               int cost = 1;
               if (code1[i - 1] == code2[j - 1]) cost = 0;

               sol[current, j] = sol[(current + 1) & 1, j] + 1;
               if (sol[current, j] > sol[current, j - 1] + 1) sol[current, j] = sol[current, j - 1] + 1;
               if (sol[current, j] > sol[(current + 1) & 1, j - 1] + cost) sol[current, j] = sol[(current + 1) & 1, j - 1] + cost;

            }
            if (current == 1) current = 0;
            else current = 1;
         }
         int sumOfLengths = len1 + len2;

         return 1.0 * (sumOfLengths - sol[(current + 1) & 1, len2]) / sumOfLengths;
      }

   }
}
