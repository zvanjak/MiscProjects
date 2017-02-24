using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace CSC.MainApp
{
  public partial class frmCompareSolutions : Form
  {
    string _solCode1;

    public string SolCode1
    {
      get { return _solCode1; }
      set { _solCode1 = value; txtSolution1.Text = value; txtSolution1.Text = value; }
    }
    string _solCode2;

    public string SolCode2
    {
      get { return _solCode2; }
      set { _solCode2 = value; txtSolution2.Text = value;}
    }

    public frmCompareSolutions()
    {
      InitializeComponent();
    }

    private void txtSolution1_TextChanged(object sender, EventArgs e)
    {

    }
  }
}