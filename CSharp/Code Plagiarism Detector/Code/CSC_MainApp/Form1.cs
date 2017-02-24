using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using CSC.Model;

namespace CSC.MainApp
{
  public partial class MainForm : Form
  {
    CSCController _controller = new CSCController();

    public MainForm()
    {
      InitializeComponent();

      this.ctrlResults.MouseMove += new System.Windows.Forms.MouseEventHandler(this.ctrlResults_MouseMove);
      this.ctrlResults.MouseClick += new System.Windows.Forms.MouseEventHandler(this.ctrlResults_MouseClick);
    }

     private void ctrlResults_MouseMove(object sender, System.Windows.Forms.MouseEventArgs e)
     {
        if (_controller.CurrProblem == null)
        {
           ResultsToolTip.SetToolTip(ctrlResults, "Do some math first");
           return;
        }
        int x = e.X;
        int y = e.Y;
        float dx = ctrlResults.Width / (float)_controller.CurrProblem.NumSol;
        float dy = ctrlResults.Height / (float)_controller.CurrProblem.NumSol;
        int firstIndex = (int)(x / dx);
        int secondIndex = (int)(y / dy);
        if (firstIndex >= _controller.CurrProblem.ListSolutions.Count || secondIndex >= _controller.CurrProblem.ListSolutions.Count )
        {
           ResultsToolTip.SetToolTip(ctrlResults, "");
           return;
        }
        string first = _controller.CurrProblem.ListSolutions[firstIndex].SolutionID.ToString();
        string second = _controller.CurrProblem.ListSolutions[secondIndex].SolutionID.ToString();
        
        ResultsToolTip.SetToolTip(ctrlResults, first+" vs "+second);
     }

    private void ctrlResults_MouseClick(object sender, System.Windows.Forms.MouseEventArgs e)
    {
      if (_controller.CurrProblem == null)
      {
//        ResultsToolTip.SetToolTip(ctrlResults, "Do some math first");
        return;
      }
      
      int x = e.X;
      int y = e.Y;
      float dx = ctrlResults.Width / (float)_controller.CurrProblem.NumSol;
      float dy = ctrlResults.Height / (float)_controller.CurrProblem.NumSol;
      int firstIndex = (int)(x / dx);
      int secondIndex = (int)(y / dy);
      
      if ( (0 <= firstIndex && firstIndex < _controller.CurrProblem.ListSolutions.Count) && 
           (0 <= secondIndex && secondIndex < _controller.CurrProblem.ListSolutions.Count) )
      {
        // idemo otvoriti formu s prikazom ta dva rješenja
        frmCompareSolutions frm = new frmCompareSolutions();

        frm.SolCode1 = procesSolutionCode(_controller.CurrProblem.ListSolutions[firstIndex].SolutionCode);
        frm.SolCode2 = procesSolutionCode(_controller.CurrProblem.ListSolutions[secondIndex].SolutionCode);

        frm.ShowDialog();

        return;
      }
    }

    private void MainForm_Load(object sender, EventArgs e)
    {
      refreshData();
      //cmbSelMetric.SelectedIndex = 0;
      //cmbSelProblem.SelectedIndex = 0;
    }

    private void loadFormDirectoryToolStripMenuItem_Click(object sender, EventArgs e)
    {
      _controller.LoadFromDirectory();

      refreshData();
      refreshSolutionsList();
    }

    private void refreshData()
    {
      int selIndMetric = cmbSelMetric.SelectedIndex;

      cmbSelProblem.Items.Clear();
      cmbSelMetric.Items.Clear();
      ctrlListProblems.Items.Clear();

      foreach (ICodeSimilarityMetricCalculator metric in _controller.CSCManager.ListDefinedMetrics)
        cmbSelMetric.Items.Add(metric.GetMetricName());

      foreach(ProgrammingProblem prob in _controller.CSCManager.ListLoadedProblems)
      {
        ListViewItem item = new ListViewItem(prob.ProblemID);
        
        string str = prob.ListSolutions.Count.ToString();
        item.SubItems.Add(str);

        cmbSelProblem.Items.Add(prob.ProblemID + " - " + str);
        ctrlListProblems.Items.Add(item);
      }

      if( selIndMetric > -1 )
        cmbSelMetric.SelectedIndex = selIndMetric;
    }

    public void refreshSolutionsList()
    {
      ctrlListSolutions.Items.Clear();

      if( _controller.CurrProblem != null )
      {
        foreach(StudentSolution sol in _controller.CurrProblem.ListSolutions)
        {
          ListViewItem item = new ListViewItem(sol.SolutionID);
          item.SubItems.Add(sol.SolutionCode.Length.ToString());
          ctrlListSolutions.Items.Add(item);
        }
      }
    }

    private void cmbSelProblem_SelectedIndexChanged(object sender, EventArgs e)
    {
      int selInd = cmbSelProblem.SelectedIndex;

      if( selInd > -1 )
      {
        _controller.SetCurrentProblem(selInd);
        refreshSolutionsList();
      }
    }


    private void cmdAnalyze_Click(object sender, EventArgs e)
    {
      int selMetricInd = cmbSelMetric.SelectedIndex;

      if( selMetricInd > -1 && _controller.CurrProblem != null )
      {
        ICodeSimilarityMetricCalculator selMetric = _controller.CSCManager.ListDefinedMetrics[selMetricInd];
        
        SimilarityResult res = _controller.CSCManager.Analyze(selMetric, _controller.CurrProblem);

        ctrlResults.setProblemAndResult(_controller.CurrProblem, res);
        ctrlResults.Invalidate();

        ctrlHistogram.setProblemAndResult(_controller.CurrProblem, res);
		ctrlHistogram.Invalidate();        

        UpdateStats(_controller.CurrProblem, res);
      }
      else
        MessageBox.Show("Metric or curr.problem NOT selected !!!");
    }

     public void UpdateStats(ProgrammingProblem prob,SimilarityResult res)
     {
        int cnt = prob.NumSol * prob.NumSol;
        double sum = 0.0;

		  double max = 0.0;

        for (int i = 0; i < prob.NumSol; i++)
           for (int j = 0; j < prob.NumSol; j++)
           	  if ( i != j )
					  if ( Double.IsNaN(res.getSimilarity(i, j)) == false ){
						sum += res.getSimilarity(i, j);
						max = Math.Max(max, res.getSimilarity(i, j));
					  }
					  
              
        double avg = sum / cnt;
        lblAverage.Text = "Average:" + avg.ToString();
		  lblMax.Text = "Max:" + max.ToString();
     }

     private void ctrlResults_Load(object sender, EventArgs e)
     {

     }

     private void cmdBatchAnalyze_Click(object sender, EventArgs e)
     {
        int selMetricInd = cmbSelMetric.SelectedIndex;

        if (selMetricInd > -1 && _controller.CurrProblem != null)
        {
           ICodeSimilarityMetricCalculator selMetric = _controller.CSCManager.ListDefinedMetrics[selMetricInd];

           SimilarityResult res = _controller.CSCManager.BatchAnalyze(selMetric, _controller.CurrProblem);

           ctrlResults.setProblemAndResult(_controller.CurrProblem, res);
           ctrlResults.Invalidate();

		   ctrlHistogram.setProblemAndResult(_controller.CurrProblem, res);
		   ctrlHistogram.Invalidate();    

           UpdateStats(_controller.CurrProblem, res);
        }
        else
           MessageBox.Show("Metric or curr.problem NOT selected !!!");
     }

    private void ctrlListSolutions_SelectedIndexChanged(object sender, EventArgs e)
    {
    }

    private void ctrlListSolutions_DoubleClick(object sender, EventArgs e)
    {
      if (_controller.CurrProblem != null && ctrlListSolutions.SelectedIndices.Count > 0)
      {
        int solInd = ctrlListSolutions.SelectedIndices[0];
        StudentSolution sol = _controller.CurrProblem.ListSolutions[solInd];

        frmShowSolution frm = new frmShowSolution();

        frm.SolutionCode = procesSolutionCode(sol.SolutionCode);

        frm.ShowDialog();
      }
    }
    string procesSolutionCode(string inCode)
    {
      string ret = inCode.Replace("\t", "    " );

      return ret;
    }

	 private void loadFromDatabaseToolStripMenuItem_Click(object sender, EventArgs e)
	 {
		 _controller.LoadFromDatabase();

		 refreshData();
		 refreshSolutionsList();
	 }


  }
}