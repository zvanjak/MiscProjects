using System;
using System.Collections.Generic;
using System.IO;

namespace ProgramLineCounter
{


  /// <summary>
    /// Klasa koja opisuje datoteku (broj linija, broj komentara,...), nastaje kao rezultat analize datoteke.
    /// </summary>
    public class FileCodeInfo : IComparable
    {
        private string _FileName;
        /// <summary>
        /// Vraæa put (string) do datoteke.
        /// </summary>
        public string FileName
        {
            get { return _FileName; }
        }
        private string _Extension;
        /// <summary>
        /// Vraæa ekstenziju datoteke.
        /// </summary>
        public string Extension
        {
          get { return _Extension; }
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
        public FileCodeInfo(string FileName, string Extension) 
        {
            _FileName = FileName;
            _Extension = Extension;
            _NumberOfLines = 0;
            _NumberOfEmptyLines = 0;
            _NumberOfMixedLines = 0;
            _NumberOfComments = 0;
        }
      
      #region IComparable Members

      public int CompareTo(object obj)
      {
        if (this.NumberOfLines < ((FileCodeInfo)obj).NumberOfLines)
            return -1;
        if (this.NumberOfLines > ((FileCodeInfo)obj).NumberOfLines)
            return 1;
        return 0;
      }

      #endregion
       
}

  public class FileCodeInfoCompareFileName_ASC : IComparer<FileCodeInfo>
  {
    public int Compare(FileCodeInfo a, FileCodeInfo b)
    {
      return a.FileName.CompareTo(b.FileName);
    }
  }

  public class FileCodeInfoCompareExtension_ASC : IComparer<FileCodeInfo>
  {
    public int Compare(FileCodeInfo a, FileCodeInfo b)
    {
      return a.Extension.CompareTo(b.Extension);
    }
  }

  public class FileCodeInfoCompareTotalLines_ASC : IComparer<FileCodeInfo>
  {
    public int Compare(FileCodeInfo a, FileCodeInfo b)
    {
      if (a.NumberOfLines < b.NumberOfLines)
        return -1;
      if (a.NumberOfLines > b.NumberOfLines)
        return 1;
      return 0;
    }
  }

  public class FileCodeInfoCompareBlankLines_ASC : IComparer<FileCodeInfo>
  {
    public int Compare(FileCodeInfo a, FileCodeInfo b)
    {
      if (a.NumberOfEmptyLines < b.NumberOfEmptyLines)
        return -1;
      if (a.NumberOfEmptyLines > b.NumberOfEmptyLines)
        return 1;
      return 0;
    }
  }

  public class FileCodeInfoCompareComments_ASC : IComparer<FileCodeInfo>
  {
    public int Compare(FileCodeInfo a, FileCodeInfo b)
    {
      if (a.NumberOfComments < b.NumberOfComments)
        return -1;
      if (a.NumberOfComments > b.NumberOfComments)
        return 1;
      return 0;
    }
  }

  public class FileCodeInfoCompareMixedLines_ASC : IComparer<FileCodeInfo>
  {
    public int Compare(FileCodeInfo a, FileCodeInfo b)
    {
      if (a.NumberOfMixedLines < b.NumberOfMixedLines)
        return -1;
      if (a.NumberOfMixedLines > b.NumberOfMixedLines)
        return 1;
      return 0;
    }
  }



  public class FileCodeInfoCompareFileName_DESC : IComparer<FileCodeInfo>
  {
    public int Compare(FileCodeInfo a, FileCodeInfo b)
    {
      return b.FileName.CompareTo(a.FileName);
    }
  }
  
  public class FileCodeInfoCompareExtension_DESC : IComparer<FileCodeInfo>
  {
    public int Compare(FileCodeInfo a, FileCodeInfo b)
    {
      return b.Extension.CompareTo(a.Extension);
    }
  }

  public class FileCodeInfoCompareTotalLines_DESC : IComparer<FileCodeInfo>
  {
    public int Compare(FileCodeInfo a, FileCodeInfo b)
    {
      if (a.NumberOfLines < b.NumberOfLines)
        return 1;
      if (a.NumberOfLines > b.NumberOfLines)
        return -1;
      return 0;
    }
  }

  public class FileCodeInfoCompareBlankLines_DESC : IComparer<FileCodeInfo>
  {
    public int Compare(FileCodeInfo a, FileCodeInfo b)
    {
      if (a.NumberOfEmptyLines < b.NumberOfEmptyLines)
        return 1;
      if (a.NumberOfEmptyLines > b.NumberOfEmptyLines)
        return -1;
      return 0;
    }
  }

  public class FileCodeInfoCompareComments_DESC : IComparer<FileCodeInfo>
  {
    public int Compare(FileCodeInfo a, FileCodeInfo b)
    {
      if (a.NumberOfComments < b.NumberOfComments)
        return 1;
      if (a.NumberOfComments > b.NumberOfComments)
        return -1;
      return 0;
    }
  }

  public class FileCodeInfoCompareMixedLines_DESC : IComparer<FileCodeInfo>
  {
    public int Compare(FileCodeInfo a, FileCodeInfo b)
    {
      if (a.NumberOfMixedLines < b.NumberOfMixedLines)
        return 1;
      if (a.NumberOfMixedLines > b.NumberOfMixedLines)
        return -1;
      return 0;
    }
  }



}
