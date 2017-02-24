using System;
using System.IO;

namespace ProgramLineCounter
{
    /// <summary>
    /// Klasa koja opisuje datoteku (broj linija, broj komentara,...), nastaje kao rezultat analize datoteke.
    /// </summary>
    class FileCodeInfo
    {
        private string _FileName;
        /// <summary>
        /// Vraæa put (string) do datoteke.
        /// </summary>
        public string FileName
        {
            get { return _FileName; }
        }
        private long _NumberOfLines;
        /// <summary>
        /// Vraæa broj linija u datoteci.
        /// </summary>
        public long NumberOfLines
        {
            set { _NumberOfLines = value; }
            get { return _NumberOfLines; }
        }
        private long _NumberOfEmptyLines;
        /// <summary>
        /// Vraæa broj praznih linija u datoteci.
        /// </summary>
        public long NumberOfEmptyLines
        {
            set { _NumberOfEmptyLines = value; }
            get { return _NumberOfEmptyLines; }
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
        private long _NumberOfMixedLines;
        /// <summary>
        /// Vraæa broj miješanih linija u datoteci.
        /// </summary>
        public long NumberOfMixedLines
        {
            set { _NumberOfMixedLines = value; }
            get { return _NumberOfMixedLines; }
        }
        /// <summary>
        /// Konstruktor.
        /// </summary>
        public FileCodeInfo(string FileName) 
        {
            _FileName = FileName;
            _NumberOfLines = 0;
            _NumberOfEmptyLines = 0;
            _NumberOfMixedLines = 0;
            _NumberOfComments = 0;
        }
    }
}
