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

        UpdateStats(_controller.CurrProblem, res);
      }
      else
        MessageBox.Show("Metric or curr.problem NOT selected !!!");
    }

     public void UpdateStats(ProgrammingProblem prob,SimilarityResult res)
     {
        int cnt = prob.NumSol * prob.NumSol;
        double sum = 0.0;

        for (int i = 0; i < prob.NumSol; i++)
           for (int j = 0; j < prob.NumSol; j++)
           {
              sum += res.getSimilarity(i, j);
           }
              
        double avg = sum / cnt;
        lblAverage.Text = "Average:" + avg.ToString();
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

           UpdateStats(_controller.CurrProblem, res);
        }
        else
           MessageBox.Show("Metric or curr.problem NOT selected !!!");
     }

  }
}