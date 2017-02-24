using System;
using System.Collections.Generic;
using System.Collections;
using System.Text;

namespace CSC.Model.Metric {

   class Fingerprint : ICodeSimilarityMetricCalculator {

      public string GetMetricName() {
         return "Winnowing Fingerprint (batch)";
      }

      public double[,] BatchSimilarityMeasure(StudentSolution[] sols) {
         string[] code = new string[sols.Length];

         for (int i = 0; i < sols.Length; i++) {
            for (int j = 0; j < sols[i].SolutionCode.Length; j++) {
               if (!Char.IsWhiteSpace(sols[i].SolutionCode[j])) {
                  code[i] += sols[i].SolutionCode[j];
               }
            }
         }

         int k = 50, w = 4; // vrlo vrlo neosjetljiv, kad ovaj baci > 50%, to je ~1.0 sigurnosti
         List<int>[] fingerprints = new List<int>[sols.Length];

         for (int i = 0; i < code.Length; i++) {
            List<int> tmp = new List<int>();
            for (int j = 0; j <= code[i].Length - k; j++) {
               tmp.Add(code[i].Substring(j, k).GetHashCode());
            }
            if (code[i].Length < k) tmp.Add(code[i].GetHashCode());

            List<int> winnowed = new List<int>();
            int pos = -1;
            for (int j = 0; j + w < tmp.Count; j++) {
               int minp = j;
               for (int l = 1; l < w; l++)
                  if (tmp[j + l] < tmp[minp])
                     minp = j + l;
               if (minp != pos)
                  winnowed.Add(tmp[minp]);
            }

            fingerprints[i] = winnowed;
         }

         double[,] ret = new double[sols.Length, sols.Length];

         for (int oi = 0; oi < sols.Length; oi++)
            for (int oj = 0; oj < sols.Length; oj++) {
               if (oi == oj) {
                  ret[oi, oj] = 1.0;
                  continue;
               }

               int cnt = 0;
               for (int i = 0; i < fingerprints[oi].Count; i++) {
                  bool match = false;
                  for (int j = 0; j < fingerprints[oj].Count && !match; j++) {
                     if (fingerprints[oi][i] == fingerprints[oj][j]) {
                        match = true;
                        cnt++;
                     }
                  }
               }
               /*if (cnt > 10) cnt = 10;
               ret[oi, oj] = 0.1 * cnt;*/ // Malo poigravanje s funkcijom, treba to razmisliti
               ret[oi, oj] = 1.0 * cnt / fingerprints[oi].Count;
            }

         return ret;
      }


      public double CalculateSimilarityMeasure(StudentSolution s1, StudentSolution s2) {
         return 0.0;
      }

   }
}
