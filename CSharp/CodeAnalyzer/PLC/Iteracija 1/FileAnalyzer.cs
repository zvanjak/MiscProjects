using System;
using System.IO;

namespace ProgramLineCounter
{
    /// <summary>
    /// Klasa analizira zadanu datoteku; broji retke, komentare...
    /// </summary>
    class FileAnalyzer
    {
        /// <summary>
        /// Metoda analizira zadanu datoteku.
        /// </summary>
        public static FileCodeInfo AnalyseFile(IData File)
        {
            FileCodeInfo Result = new FileCodeInfo(File.GetFileName());

            string Line;
            int Column;
            bool Quote = false;
            bool Slash;
            bool CommentOpened = false; //je li otvoren komentar tipa /* */
            bool Comment = false; //je li otvoren kometar tipa //
            bool Star = false;
            bool Empty = false; //je li linija prazna
            bool Mixed; //je li linija mjesana

            while ((Line = File.GetLine()) != null)
            {
                Result.NumberOfLines++; //brojimo linije
                if (CommentOpened) Result.NumberOfComments++;

                if (Empty)
                {
                    Result.NumberOfEmptyLines++;
                }
                else Empty = true; //pretpostavljamo uvijek da je linija prazna

                Column = 0;
                Slash = false;
                Comment = false;
                Star = false;
                Mixed = false;
                
                //èitamo znak po znak
                while (Column < Line.Length)
                {
                    if (Quote)
                    {
                        if (Line[Column] == '"') Quote = false;
                    }
                    else
                    {   
                        //nismo u navodnicima, možemo tražiti komentare
                        if (CommentOpened) //ako je otvoren komentar /**/ 
                        {
                            //traži kraj
                            if (Line[Column] == '*') Star = true;
                            else if ((Line[Column] == '/')&&(Star)) CommentOpened = false;
                            else Star = false;
                        }
                        else if (!Comment) //ako nije otvoren nijedan komentar
                        {
                            if (Line[Column] == '"')
                            {
                                if (Quote) Quote = false;   //ako su vec otvoreni
                                else Quote = true;  //ako nisu
                            }
                            else
                            {
                                //traži komentare obje vrste
                                if (Line[Column] == '/')
                                {
                                    if (Slash)
                                    {
                                        Result.NumberOfComments++;  //naišli smo na komentar tipa //
                                        Comment = true;
                                        if (Mixed) Result.NumberOfMixedLines++; //mijesana linija
                                    }
                                    else
                                    {
                                        Slash = true;
                                        if (!Empty) Mixed = true;
                                    }
                                }

                                else if (Line[Column] == '*')
                                {
                                    if (Slash)
                                    {
                                        Result.NumberOfComments++;  //naišli smo na komentar tipa /**/
                                        CommentOpened = true;
                                        if (Mixed) Result.NumberOfMixedLines++; //mijesana linija
                                    }
                                }
                                else Slash = false;
                            }

                        }
                           
                     }
                     if ((Line[Column] != ' ') && (Empty)) Empty = false; //ako nadjemo znak != ' ' => nije prazna linija

                     Column++;
                 }
              
              }

            return Result;

        }

    }
}
