using System;
using System.Collections.Generic;
using System.Text;

namespace CSC.Model.Metric
{

    class EditDistanceMarko : ICodeSimilarityMetricCalculator
    {

        public string GetMetricName()
        {
            return "EditDistance Marko";
        }

       public double[,] BatchSimilarityMeasure(StudentSolution[] sols)
       {
          return new double[sols.Length, sols.Length];
       }


        public double CalculateSimilarityMeasure(StudentSolution s1, StudentSolution s2)
        {
            string code1 = s1.SolutionCode;
            string code2 = s2.SolutionCode;
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
