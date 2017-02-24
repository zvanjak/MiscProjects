using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Data.Linq;

using BatchAnalysisModel;

namespace BatchAnalysisApp
{
  class Stud
  {
    private int _ID;
    private int _ProsjecanRang;
    private int _RangPriUpisu;

    public Stud(Student refStud)
    {
      _ID = refStud.IDStudent;
    }
  }
  class Program
  {
    static void Main(string[] args)
    {
      // idemo ispisati sva rješenja studenta s IDem 1
      CSCDataClassesDataContext ctx = new CSCDataClassesDataContext();

      // korištenjem LINQ to SQL classes !!!
      Table<Student> tblStudents = ctx.GetTable<Student>();

      var query =
          from stud in tblStudents
          orderby stud.RangpriUpisu
          where stud.RangpriUpisu < 20 
          select stud ;

      Console.WriteLine("Prosječan rang na upisu za interval ocjena");
      Console.WriteLine("[2.0 - 3.0] = {0}", AverageClassifRang(ctx, 2.0, 3.0));
      Console.WriteLine("[3.0 - 4.0] = {0}", AverageClassifRang(ctx, 3.0, 4.0));
      Console.WriteLine("[4.0 - 4.5] = {0}", AverageClassifRang(ctx, 4.0, 4.5));
      Console.WriteLine("[4.5 - 5.0] = {0}", AverageClassifRang(ctx, 4.5, 5.0));

      //foreach (var stud in query)
      //  Console.WriteLine("id = {0}, rang = {1}, ocjena = {2}", stud.IDStudent, stud.RangpriUpisu, stud.ProsjecnaOcjena);
    }
    public static int AverageClassifRang(CSCDataClassesDataContext refContext, double ocjenaIntervalStart, double ocjenaIntervalEnd)
    {
      Table<Student> tblStudents = refContext.GetTable<Student>();

      var queryAvg =
          from stud in tblStudents
          where stud.ProsjecnaOcjena > ocjenaIntervalStart && stud.ProsjecnaOcjena < ocjenaIntervalEnd
          select stud.RangpriUpisu;

      System.Nullable<double> aveg = queryAvg.Average();

//      Console.WriteLine("Average = {0}", aveg);

      return Convert.ToInt32(aveg.ToString());
    }
  }
}
  