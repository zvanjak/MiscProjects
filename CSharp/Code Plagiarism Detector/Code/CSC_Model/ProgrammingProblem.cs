using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace CSC.Model
{
  public class ProgrammingProblem
  {
    string _problemID;
    List<StudentSolution> _listSolutions = new List<StudentSolution>();
    List<SimilarityResult> _listSimilarityResults = new List<SimilarityResult>();

    public List<StudentSolution> ListSolutions
    {
      get { return _listSolutions; }
      set { _listSolutions = value; }
    }
    public string ProblemID
    {
      get { return _problemID; }
      set { _problemID = value; }
    }
    public int NumSol { get { return _listSolutions.Count; } }

    public void addStudentSolution(FileInfo fi)
    {
      StudentSolution newSol = new StudentSolution(fi);

      _listSolutions.Add(newSol);
    }

	 public void addStudentSolution(string code, string id)
	 {
		 StudentSolution newSol = new StudentSolution(code, id);

		 _listSolutions.Add(newSol);
	 }
  }
}
