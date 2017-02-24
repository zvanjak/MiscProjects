using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace CSC.MainApp
{
  public partial class frmShowSolution : Form
  {
    string _solutionCode;

    public string SolutionCode
    {
      get { return _solutionCode; }
      set { _solutionCode = value; richTextSol.Text = value; }
    }

    public frmShowSolution()
    {
      InitializeComponent();
    }
  }
}