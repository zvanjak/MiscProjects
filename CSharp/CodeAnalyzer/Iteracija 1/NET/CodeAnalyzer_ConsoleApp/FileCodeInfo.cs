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
        /// Vra�a put (string) do datoteke.
        /// </summary>
        public string FileName
        {
            get { return _FileName; }
        }
        private long _NumberOfLines;
        /// <summary>
        /// Vra�a broj linija u datoteci.
        /// </summary>
        public long NumberOfLines
        {
            set { _NumberOfLines = value; }
            get { return _NumberOfLines; }
        }
        private long _NumberOfEmptyLines;
        /// <summary>
        /// Vra�a broj praznih linija u datoteci.
        /// </summary>
        public long NumberOfEmptyLines
        {
            set { _NumberOfEmptyLines = value; }
            get { return _NumberOfEmptyLines; }
        }
        private long _NumberOfComments;
        /// <summary>
        /// Vra�a broj komentiranih linija u datoteci.
        /// </summary>
        public long NumberOfComments
        {
            set { _NumberOfComments = value; }
            get { return _NumberOfComments; }
        }
        private long _NumberOfMixedLines;
        /// <summary>
        /// Vra�a broj mije�anih linija u datoteci.
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
