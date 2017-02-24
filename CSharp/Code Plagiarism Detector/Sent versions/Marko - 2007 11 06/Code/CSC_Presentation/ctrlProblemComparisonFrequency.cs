using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

using CSC.Model;

namespace CSC.Presentation
{
  public partial class ctrlProblemComparisonFrequency : UserControl
  {
     ProgrammingProblem _currProblem = null;

     public ProgrammingProblem CurrProblem
     {
        get { return _currProblem; }
        set { _currProblem = value; }
     }

     SimilarityResult _result = null;

     public SimilarityResult Result
     {
        get { return _result; }
        set { _result = value; }
     }

    public ctrlProblemComparisonFrequency()
    {
      InitializeComponent();
    }

    private void ctrlProblemComparisonFrequency_Paint(object sender, PaintEventArgs e)
    {
      if( _result != null && _currProblem != null )
      {
        int numSol = _currProblem.ListSolutions.Count;
      
        Graphics g = e.Graphics;
        int[] count = new int[101];
        int maxCount = -1;

        for(int i=0; i<numSol; i++ )
          for(int j=0; j<numSol; j++ )
          {
            double measure = _result.getSimilarity(i, j);
            count[(int)(measure)]++;
            if (count[(int)(measure)] > maxCount ) maxCount = count[(int)(measure)];
          }

       Brush myBrush = new SolidBrush(Color.FromArgb(255, 0, 0));

       float dx = this.Width / (float)(101.0);
       for (int i = 0; i <= 101; i++)
       {
          float x, y, h;
          x = i * dx;
          y = maxCount - count[i];
          h = this.Height - y;
          g.FillRectangle(myBrush, x, y, dx, h);
       }


       myBrush.Dispose();
      }

    }

    public void setProblemAndResult(ProgrammingProblem inProb, SimilarityResult inRes)
    {
      _currProblem = inProb;
      _result = inRes;
    }


  }
}
