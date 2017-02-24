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
  public partial class ctrlProblemComparisonFrequency: UserControl
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
        int totalCount = 0;
		int maxCount = 0, maxI = -1;

        for(int i=0; i<numSol; i++ )
          for(int j=0; j<numSol; j++ )
				 if (i != j)
				 {
					 double measure = 100.0 * _result.getSimilarity(i, j);
					 if (Double.IsNaN(measure)) continue;
					 count[(int)(measure)]++;
					 if (count[(int)(measure)] > maxCount){
						 maxCount = count[(int)(measure)];
						 maxI = (int)(measure);
					 }
				 }

	   totalCount = numSol * (numSol - 1);

       float dx = this.Width / (float)(101.0);
       for (int i = 0; i < 101; i++)
       {
          double x, y, h;
          x = i * dx;
          y = (1.1 - (float)(count[i]) / (float)(maxCount)) * this.Height;
          h = this.Height;
		  g.FillRectangle(new SolidBrush(Color.FromArgb(i * 255 / 101, 0, 0)), (float)x, (float)y, (float)dx, (float)h);
       }


		 labelPeak.Text = Convert.ToString(Math.Round((float)(count[maxI]) / (float)(totalCount) * 100.0, 2)) + " - " + Convert.ToString(maxI);
		 labelPeak.Top = 0;
		 labelPeak.Left = (int)(maxI * dx);
      }

    }

    public void setProblemAndResult(ProgrammingProblem inProb, SimilarityResult inRes)
    {
      _currProblem = inProb;
      _result = inRes;
    }


  }
}
