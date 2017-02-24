/* 13.03.2006. 
    Za dani direktorij program ispisuje broj svih datoteka i poddirektorija; 
    Ispisuje i put i broj linija za svaku datoteku cija je ekstenzija jednaka zadanoj.
 */


using System;
using System.IO;
using ProgramLineCounter;

class Test
{
    static void Main(string[] args)
    {

        try
        {
            /*
            Console.WriteLine("Unesi put do direktorija:");
            string DirectoryName = Console.ReadLine();

            Console.WriteLine("Unesi ekstenziju:");
            string MyExtension = Console.ReadLine();
            */
            string DirectoryName = "C:\\TestDir";
            string MyExtension = ".txt";
  
            EnumerateFiles EnumFiles = new EnumerateFiles(DirectoryName);
            EnumFiles.Enumerate();

            Console.WriteLine("{0,-25} {1}", "Ukupno poddirektorija:", EnumFiles.Directories);
            Console.WriteLine("{0,-25} {1}", "Ukupno fileova:", EnumFiles.Files);
            Console.WriteLine();
            Console.WriteLine("{0,-35} {1,-10} {2, -10} {3, -10} {4,-10}", "Path:", "Ukupno:", "Praznih:", "Komentara:", "Miješano");
            
            FileCodeInfo Info;
            for (int i = 0; i < EnumFiles.Duljina; i++)
            {
                if (((FileInfo)EnumFiles[i]).Extension == MyExtension)
                {
                    Data1 data = new Data1((FileInfo)EnumFiles[i]);
                    Info = FileAnalyzer.AnalyseFile(data);
                    Console.WriteLine("{0,-35} {1,-10} {2, -10} {3, -10} {4,-10}", Info.FileName, Info.NumberOfLines, Info.NumberOfEmptyLines, Info.NumberOfComments, Info.NumberOfMixedLines);
                }
            }
        }
        catch (Exception e)
        {
            Console.WriteLine(e.Message);
        }
        finally
        {
            Console.ReadLine();
        }
    }

}