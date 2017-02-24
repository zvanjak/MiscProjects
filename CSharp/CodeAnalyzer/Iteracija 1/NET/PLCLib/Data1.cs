using System;
using System.IO;

namespace ProgramLineCounter
{
    /// <summary>
    /// Klasa koja datoteci pristupa liniju po liniju.
    /// </summary>
    public class Data1: IData
    {
        FileInfo _File;
        StreamReader _MyReader;

        public Data1(FileInfo File)
        {
            _File = File;
            FileStream MyStream = File.Open(FileMode.Open, FileAccess.Read);
            _MyReader = new StreamReader(MyStream);
        }
        ~Data1()
        {
          Dispose();
        }
        
        public void Dispose()
        {
            _MyReader.Close();
            GC.SuppressFinalize(this);
        }
        #region IData Members
        public string GetFileName()
        {
            return _File.FullName;
        }
        public string GetExtension()
        {
            return _File.Extension;
        }
        public string GetLine()
        {
            return _MyReader.ReadLine();
        }
        #endregion
    }
}
