using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

using CSC.Model;

namespace CSCConsole
{
  class Program
  {
    static void Main(string[] args)
    {
      ModelManager _manager = new ModelManager();

      string path = "D:\\Users\\Zvone\\Projects\\Code Plagiarism Detector\\Data\\Complete data\\";

      string[] listDir = Directory.GetDirectories(path);

      foreach(string str in listDir)
      {
        string problemID = str.Substring(str.Length - 7, 7);
        Console.WriteLine(problemID);
        
        _manager.LoadProblemFromDirectory(str, problemID);
      }
    }
  }
}
