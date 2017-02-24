using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Windows.Forms;

using CSC.Model;

namespace CSC.MainApp
{
  public class CSCController
  {
    ModelManager _manager = new ModelManager();

    ProgrammingProblem _currProblem = null;

    public ProgrammingProblem CurrProblem
    {
      get { return _currProblem; }
      set { _currProblem = value; }
    }

    public ModelManager CSCManager
    {
      get { return _manager; }
      set { _manager = value; }
    }

    public void LoadFromDirectory()
    {
      FolderBrowserDialog  fileDlg = new FolderBrowserDialog ();

      fileDlg.RootFolder = Environment.SpecialFolder.MyDocuments;
//      fileDlg.SelectedPath = "D:\\Users\\Zvone\\Projects\\Code Plagiarism Detector\\Data\\TestPodaci\\3217";

      if( fileDlg.ShowDialog() == DialogResult.OK )
      {
        string path = fileDlg.SelectedPath;
        string problemID = path.Substring(path.Length - 4, 4);

        _manager.LoadProblemFromDirectory(path, problemID);
      }
    }

    public void SetCurrentProblem(int index)
    {
      _currProblem = CSCManager.ListLoadedProblems[index];
    }
  }
}
