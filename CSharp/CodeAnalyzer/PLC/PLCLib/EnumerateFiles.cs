using System;
using System.IO;
using System.Collections.Generic;


namespace ProgramLineCounter
{
    /// <summary>
    /// Klasa èija je odgovornost za dani naziv direktorija, napraviti popis svih datoteka u tom direktoriju
    /// i njegovim poddirektorijima.
    /// </summary>
    public class EnumerateFiles
    {
        private DirectoryInfo _baseDirectory; 
  
        private List<FileInfo> _listFiles = new List<FileInfo>(); // lista datoteka
        private long _Files;
        /// <summary>
        /// Broj datoteka u zadanom direktoriju.
        /// </summary>
        public long Files   
        {
            set {_Files = value; }
            get {return _Files; }
        }

        private long _Directories;
        /// <summary>
        /// Broj poddirektorija u zadanom direktoriju.
        /// </summary>
        public long Directories
        {
            set {_Directories = value; }
            get{return _Directories; }
        }
        /// <summary>
        /// Konstruktor.
        /// </summary>
        /// <param name="inBaseDirPath">Put do direktorija</param>
        public EnumerateFiles(string inBaseDirPath)
        {
            _baseDirectory = new DirectoryInfo(inBaseDirPath);
            if (!_baseDirectory.Exists)
            {
                throw new DirectoryNotFoundException("Directory doesn't exist.");
            }
            Files = 0;
            Directories = 0;
        }

        public object this[int i]
        {
            get{return _listFiles[i]; }
        }
        /// <summary>
        /// Vraæa broj datoteka u zadanom direktoriju.
        /// </summary>
        public int Duljina
        {
            get {return _listFiles.Count; }
        }

        /// <summary>
        /// Metoda sprema u listu sve datoteke iz zadanog direktorija.  
        /// </summary>
        public void Enumerate()
        {
            // GetFileSystemInfos => vraca sve poddirektorije i fileove direktorija dir. u array tipa FileSystemInfo
            Enumerate(_baseDirectory.GetFileSystemInfos());
        }
        private void Enumerate(FileSystemInfo[] FSInfo)
        {
            if (FSInfo == null)
            {
                throw new ArgumentNullException("FSInfo");
            }
            // Sprema samo fileove.
            foreach (FileSystemInfo i in FSInfo)
            {
                // Provjerava je li element direktorij.
                if (i is DirectoryInfo)
                {
                    Directories++;
                    // Ponavljamo isto i za poddirektorije.
                    DirectoryInfo dInfo = (DirectoryInfo)i;
                    Enumerate(dInfo.GetFileSystemInfos());
                }

                // Provjerava je li element file.
                else if (i is FileInfo)
                {
                    Files++;
                    _listFiles.Add((FileInfo)i);
                }

            }
        }
    }
}