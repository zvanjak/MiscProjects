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
  public partial class ctrlProblemComparisonResults : UserControl
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

    public ctrlProblemComparisonResults()
    {
      InitializeComponent();
    }

    private void ctrlProblemComparisonResults_Paint(object sender, PaintEventArgs e)
    {
      if( _result != null && _currProblem != null )
      {
        int numSol = _currProblem.ListSolutions.Count;
      
        Graphics g = e.Graphics;
        float dx = this.Width / (float) numSol;
        float dy = this.Height / (float) numSol;
        
        //for(int i=0; i<numSol; i++ )
        //{
        //  g.DrawLine(Pens.Black, 0, i * dy, this.Width, i * dy);
        //  g.DrawLine(Pens.Black, i * dx, 0, i * dx, this.Height);
        //}

        for(int i=0; i<numSol; i++ )
          for(int j=0; j<numSol; j++ )
          {
            double measure = _result.getSimilarity(i, j);
				if (Double.IsNaN(measure))
				{
						Brush myBrush = new SolidBrush(Color.FromArgb(255, 0, 0));

					g.FillRectangle(myBrush, i * dx, j * dy, (i + 1) * dx, (j + 1) + dy);

					myBrush.Dispose();
				}
				else
				{
					int colorVal = 255 - (int)(measure * 255);

					Brush myBrush = new SolidBrush(Color.FromArgb(colorVal, colorVal, colorVal));

					g.FillRectangle(myBrush, i * dx, j * dy, (i + 1) * dx, (j + 1) + dy);

					myBrush.Dispose();
				}
          }
      }
      //else
      //  MessageBox.Show("Prdo");
    }

    public void setProblemAndResult(ProgrammingProblem inProb, SimilarityResult inRes)
    {
      _currProblem = inProb;
      _result = inRes;
    }


  }
}
