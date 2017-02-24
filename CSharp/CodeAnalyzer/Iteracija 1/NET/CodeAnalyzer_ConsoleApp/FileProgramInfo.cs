using System;
using System.IO;

namespace ProgramLineCounter
{
    /// <summary>
    /// Klasa koja opisuje datoteku (broj linija, broj komentara,...), nastaje kao rezultat analize datoteke.
    /// </summary>
    class FileProgramInfo
    {
        private string _FileName;
        private long _NumberOfLines;
        /// <summary>
        /// Vraæa broj linija u datoteci.
        /// </summary>
        public long NumberOfLines
        {
            set { _NumberOfLines = value; }
            get { return _NumberOfLines; }
        }
        private long _NumberOfComments;
        /// <summary>
        /// Vraæa broj komentiranih linija u datoteci.
        /// </summary>
        public long NumberOfComments
        {
            set { _NumberOfComments = value; }
            get { return _NumberOfComments; }
        }
        /// <summary>
        /// Vraæa put (string) do datoteke.
        /// </summary>
        /*public string FullName
        {
            get { return _File.FullName; }
        }*/
        /// <summary>
        /// Konstruktor.
        /// </summary>
        public FileProgramInfo() 
        {
            //_File = File;
            _NumberOfLines = 0;
            _NumberOfComments = 0;
        }
    }
}
