using System;
using System.IO;

namespace ProgramLineCounter
{
    /// <summary>
    /// Su�elje za pristup datoteci. 
    /// </summary>
    interface IData
    {
        /// <summary>
        /// 
        /// </summary>
        /// <returns>Vra�a puno ime datoteke.</returns>
        string GetFileName();
        /// <summary>
        /// 
        /// </summary>
        /// <returns>Vra�a liniju datoteke.</returns>
        string GetLine();
    }
}
