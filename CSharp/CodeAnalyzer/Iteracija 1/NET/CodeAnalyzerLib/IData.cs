using System;
using System.IO;

namespace ProgramLineCounter
{
    /// <summary>
    /// Suèelje za pristup datoteci. 
    /// </summary>
    public interface IData
    {
        /// <summary>
        /// 
        /// </summary>
        /// <returns>Vraæa puno ime datoteke.</returns>
        string GetFileName();
        /// <summary>
        /// 
        /// </summary>
        /// <returns>Vraæa liniju datoteke.</returns>
        string GetLine();
    }
}
