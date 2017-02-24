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

      fileDlg.RootFolder = Environment.SpecialFolder.MyComputer;
		fileDlg.SelectedPath = "d:\\work\\CSC\\kontrolirani\\data";

      if( fileDlg.ShowDialog() == DialogResult.OK )
      {
        string path = fileDlg.SelectedPath;
        string problemID = path.Substring(path.Length - 4, 4);

        _manager.LoadProblemFromDirectory(path, problemID);
      }
    }

	 public void LoadFromDatabase()
	 {
		 OpenFileDialog fileDlg = new OpenFileDialog();

		 fileDlg.DefaultExt = ".mdb";

		 if (fileDlg.ShowDialog() == DialogResult.OK)
		 {
			 string path = fileDlg.FileName;

			 _manager.LoadProblemFromDatabase(path);
		 }
	 }

    public void SetCurrentProblem(int index)
    {
      _currProblem = CSCManager.ListLoadedProblems[index];
    }
  }
}
