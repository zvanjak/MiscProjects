using System;
using System.Collections.Generic;
using System.Text;

namespace CSC.Model
{
  public class SolutionsSimilarity
  {
    StudentSolution _solution1;
    StudentSolution _solution2;
    double _similarityMeasure = 0.0;

    public StudentSolution Solution1
    {
      get { return _solution1; }
      set { _solution1 = value; }
    }
    public StudentSolution Solution2
    {
      get { return _solution2; }
      set { _solution2 = value; }
    }
    public double SimilarityMeasure
    {
      get { return _similarityMeasure; }
      set { _similarityMeasure = value; }
    }
  }
}
