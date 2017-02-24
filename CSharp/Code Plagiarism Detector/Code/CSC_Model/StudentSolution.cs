using System;
using System.Collections.Generic;
using System.Collections;
using System.Text;
using System.IO;

namespace CSC.Model
{
  public class StudentSolution
  {
    string _solutionID;
    string _solutionCode;
    ArrayList _solutionLines;

    public ArrayList SolutionLines
    {
       get { return _solutionLines; }
       set { _solutionLines = value; }
    }

    FileInfo _solutionFI;
      

    public FileInfo SolutionFI
    {
       get { return _solutionFI; }
       set { _solutionFI = value; }
    }

    public string SolutionID
    {
      get { return _solutionID; }
      set { _solutionID = value; }
    }
  
    public string SolutionCode
    {
      get { return _solutionCode; }
      set { _solutionCode = value; }
    }

	 public StudentSolution(string code, string id)
	 {
		 _solutionFI = null;
		 _solutionID = id;
		 _solutionLines = new ArrayList();

		 string tmpCode = "";

		 string[] line = code.Split('\n');
		 for (int i = 0; i < line.Length; i++)
		 {
			 tmpCode += line[i];
			 tmpCode += "\n";
			 _solutionLines.Add(line[i]);
		 }

		 if (tmpCode == null) tmpCode = "";
		 _solutionCode = tmpCode;
	 }

    public StudentSolution(FileInfo inFI)
    {
       _solutionFI = inFI;
      _solutionID = inFI.Name;
      _solutionLines = new ArrayList();

      string tmpCode = "";

      using (StreamReader sr = new StreamReader(inFI.FullName))
      {
         string line;
         while ((line = sr.ReadLine()) != null)
         {
            tmpCode += line;
           tmpCode += "\n";
            _solutionLines.Add(line);
         }
      }

		if (tmpCode == null) tmpCode = "";
      _solutionCode = tmpCode;
    }
  }
}
