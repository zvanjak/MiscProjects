namespace CSC.MainApp
{
  partial class MainForm
  {
    /// <summary>
    /// Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose(bool disposing)
    {
      if (disposing && (components != null))
      {
        components.Dispose();
      }
      base.Dispose(disposing);
    }

    #region Windows Form Designer generated code

    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
		 this.components = new System.ComponentModel.Container();
		 this.menuStrip1 = new System.Windows.Forms.MenuStrip();
		 this.optionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
		 this.loadFormDirectoryToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
		 this.label1 = new System.Windows.Forms.Label();
		 this.ctrlListProblems = new System.Windows.Forms.ListView();
		 this.columnHeader1 = new System.Windows.Forms.ColumnHeader();
		 this.columnHeader2 = new System.Windows.Forms.ColumnHeader();
		 this.label2 = new System.Windows.Forms.Label();
		 this.cmbSelProblem = new System.Windows.Forms.ComboBox();
		 this.label3 = new System.Windows.Forms.Label();
		 this.cmbSelMetric = new System.Windows.Forms.ComboBox();
		 this.cmdAnalyze = new System.Windows.Forms.Button();
		 this.ctrlListSolutions = new System.Windows.Forms.ListView();
		 this.columnHeader3 = new System.Windows.Forms.ColumnHeader();
		 this.columnHeader4 = new System.Windows.Forms.ColumnHeader();
		 this.label4 = new System.Windows.Forms.Label();
		 this.ctrlResults = new CSC.Presentation.ctrlProblemComparisonResults();
		 this.ResultsToolTip = new System.Windows.Forms.ToolTip(this.components);
		 this.cmdBatchAnalyze = new System.Windows.Forms.Button();
		 this.lblAverage = new System.Windows.Forms.Label();
		 this.ctrlHistogram = new CSC.Presentation.ctrlProblemComparisonFrequency();
		 this.lblMax = new System.Windows.Forms.Label();
		 this.loadFromDatabaseToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
		 this.menuStrip1.SuspendLayout();
		 this.SuspendLayout();
		 // 
		 // menuStrip1
		 // 
		 this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.optionsToolStripMenuItem});
		 this.menuStrip1.Location = new System.Drawing.Point(0, 0);
		 this.menuStrip1.Name = "menuStrip1";
		 this.menuStrip1.Size = new System.Drawing.Size(1168, 24);
		 this.menuStrip1.TabIndex = 0;
		 this.menuStrip1.Text = "menuStrip1";
		 // 
		 // optionsToolStripMenuItem
		 // 
		 this.optionsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.loadFormDirectoryToolStripMenuItem,
            this.loadFromDatabaseToolStripMenuItem});
		 this.optionsToolStripMenuItem.Name = "optionsToolStripMenuItem";
		 this.optionsToolStripMenuItem.Size = new System.Drawing.Size(56, 20);
		 this.optionsToolStripMenuItem.Text = "Options";
		 // 
		 // loadFormDirectoryToolStripMenuItem
		 // 
		 this.loadFormDirectoryToolStripMenuItem.Name = "loadFormDirectoryToolStripMenuItem";
		 this.loadFormDirectoryToolStripMenuItem.Size = new System.Drawing.Size(181, 22);
		 this.loadFormDirectoryToolStripMenuItem.Text = "Load form directory";
		 this.loadFormDirectoryToolStripMenuItem.Click += new System.EventHandler(this.loadFormDirectoryToolStripMenuItem_Click);
		 // 
		 // label1
		 // 
		 this.label1.AutoSize = true;
		 this.label1.Location = new System.Drawing.Point(5, 37);
		 this.label1.Name = "label1";
		 this.label1.Size = new System.Drawing.Size(115, 13);
		 this.label1.TabIndex = 1;
		 this.label1.Text = "List of loaded problems";
		 // 
		 // ctrlListProblems
		 // 
		 this.ctrlListProblems.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2});
		 this.ctrlListProblems.Location = new System.Drawing.Point(12, 57);
		 this.ctrlListProblems.Name = "ctrlListProblems";
		 this.ctrlListProblems.Size = new System.Drawing.Size(152, 150);
		 this.ctrlListProblems.TabIndex = 2;
		 this.ctrlListProblems.UseCompatibleStateImageBehavior = false;
		 this.ctrlListProblems.View = System.Windows.Forms.View.Details;
		 // 
		 // columnHeader1
		 // 
		 this.columnHeader1.Text = "ID";
		 this.columnHeader1.Width = 52;
		 // 
		 // columnHeader2
		 // 
		 this.columnHeader2.Text = "Num.of solutions";
		 this.columnHeader2.Width = 95;
		 // 
		 // label2
		 // 
		 this.label2.AutoSize = true;
		 this.label2.Location = new System.Drawing.Point(190, 37);
		 this.label2.Name = "label2";
		 this.label2.Size = new System.Drawing.Size(89, 13);
		 this.label2.TabIndex = 3;
		 this.label2.Text = "Selected problem";
		 // 
		 // cmbSelProblem
		 // 
		 this.cmbSelProblem.FormattingEnabled = true;
		 this.cmbSelProblem.Location = new System.Drawing.Point(281, 34);
		 this.cmbSelProblem.Name = "cmbSelProblem";
		 this.cmbSelProblem.Size = new System.Drawing.Size(69, 21);
		 this.cmbSelProblem.TabIndex = 4;
		 this.cmbSelProblem.SelectedIndexChanged += new System.EventHandler(this.cmbSelProblem_SelectedIndexChanged);
		 // 
		 // label3
		 // 
		 this.label3.AutoSize = true;
		 this.label3.Location = new System.Drawing.Point(380, 37);
		 this.label3.Name = "label3";
		 this.label3.Size = new System.Drawing.Size(83, 13);
		 this.label3.TabIndex = 5;
		 this.label3.Text = "Selected metric:";
		 // 
		 // cmbSelMetric
		 // 
		 this.cmbSelMetric.FormattingEnabled = true;
		 this.cmbSelMetric.Location = new System.Drawing.Point(469, 34);
		 this.cmbSelMetric.Name = "cmbSelMetric";
		 this.cmbSelMetric.Size = new System.Drawing.Size(165, 21);
		 this.cmbSelMetric.TabIndex = 6;
		 // 
		 // cmdAnalyze
		 // 
		 this.cmdAnalyze.Location = new System.Drawing.Point(679, 34);
		 this.cmdAnalyze.Name = "cmdAnalyze";
		 this.cmdAnalyze.Size = new System.Drawing.Size(75, 23);
		 this.cmdAnalyze.TabIndex = 7;
		 this.cmdAnalyze.Text = "Analyze";
		 this.cmdAnalyze.UseVisualStyleBackColor = true;
		 this.cmdAnalyze.Click += new System.EventHandler(this.cmdAnalyze_Click);
		 // 
		 // ctrlListSolutions
		 // 
		 this.ctrlListSolutions.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader3,
            this.columnHeader4});
		 this.ctrlListSolutions.FullRowSelect = true;
		 this.ctrlListSolutions.Location = new System.Drawing.Point(12, 252);
		 this.ctrlListSolutions.Name = "ctrlListSolutions";
		 this.ctrlListSolutions.Size = new System.Drawing.Size(133, 340);
		 this.ctrlListSolutions.TabIndex = 8;
		 this.ctrlListSolutions.UseCompatibleStateImageBehavior = false;
		 this.ctrlListSolutions.View = System.Windows.Forms.View.Details;
		 this.ctrlListSolutions.SelectedIndexChanged += new System.EventHandler(this.ctrlListSolutions_SelectedIndexChanged);
		 this.ctrlListSolutions.DoubleClick += new System.EventHandler(this.ctrlListSolutions_DoubleClick);
		 // 
		 // columnHeader3
		 // 
		 this.columnHeader3.Text = "ID";
		 // 
		 // columnHeader4
		 // 
		 this.columnHeader4.Text = "Length";
		 this.columnHeader4.Width = 69;
		 // 
		 // label4
		 // 
		 this.label4.AutoSize = true;
		 this.label4.Location = new System.Drawing.Point(8, 233);
		 this.label4.Name = "label4";
		 this.label4.Size = new System.Drawing.Size(177, 13);
		 this.label4.TabIndex = 9;
		 this.label4.Text = "List of solutions for selected problem";
		 // 
		 // ctrlResults
		 // 
		 this.ctrlResults.BackColor = System.Drawing.Color.White;
		 this.ctrlResults.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
		 this.ctrlResults.CurrProblem = null;
		 this.ctrlResults.Location = new System.Drawing.Point(215, 74);
		 this.ctrlResults.Name = "ctrlResults";
		 this.ctrlResults.Result = null;
		 this.ctrlResults.Size = new System.Drawing.Size(598, 496);
		 this.ctrlResults.TabIndex = 10;
		 this.ResultsToolTip.SetToolTip(this.ctrlResults, "Do some analysis first.");
		 this.ctrlResults.Load += new System.EventHandler(this.ctrlResults_Load);
		 // 
		 // ResultsToolTip
		 // 
		 this.ResultsToolTip.ToolTipTitle = "Analysis results:";
		 // 
		 // cmdBatchAnalyze
		 // 
		 this.cmdBatchAnalyze.Location = new System.Drawing.Point(760, 34);
		 this.cmdBatchAnalyze.Name = "cmdBatchAnalyze";
		 this.cmdBatchAnalyze.Size = new System.Drawing.Size(92, 23);
		 this.cmdBatchAnalyze.TabIndex = 13;
		 this.cmdBatchAnalyze.Text = "Batch Analyze";
		 this.cmdBatchAnalyze.UseVisualStyleBackColor = true;
		 this.cmdBatchAnalyze.Click += new System.EventHandler(this.cmdBatchAnalyze_Click);
		 // 
		 // lblAverage
		 // 
		 this.lblAverage.AutoSize = true;
		 this.lblAverage.Location = new System.Drawing.Point(833, 82);
		 this.lblAverage.Name = "lblAverage";
		 this.lblAverage.Size = new System.Drawing.Size(50, 13);
		 this.lblAverage.TabIndex = 14;
		 this.lblAverage.Text = "Average:";
		 // 
		 // ctrlHistogram
		 // 
		 this.ctrlHistogram.BackColor = System.Drawing.Color.White;
		 this.ctrlHistogram.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
		 this.ctrlHistogram.CurrProblem = null;
		 this.ctrlHistogram.Location = new System.Drawing.Point(836, 138);
		 this.ctrlHistogram.Name = "ctrlHistogram";
		 this.ctrlHistogram.Result = null;
		 this.ctrlHistogram.Size = new System.Drawing.Size(320, 314);
		 this.ctrlHistogram.TabIndex = 15;
		 // 
		 // lblMax
		 // 
		 this.lblMax.AutoSize = true;
		 this.lblMax.Location = new System.Drawing.Point(833, 107);
		 this.lblMax.Name = "lblMax";
		 this.lblMax.Size = new System.Drawing.Size(30, 13);
		 this.lblMax.TabIndex = 16;
		 this.lblMax.Text = "Max:";
		 // 
		 // loadFromDatabaseToolStripMenuItem
		 // 
		 this.loadFromDatabaseToolStripMenuItem.Name = "loadFromDatabaseToolStripMenuItem";
		 this.loadFromDatabaseToolStripMenuItem.Size = new System.Drawing.Size(181, 22);
		 this.loadFromDatabaseToolStripMenuItem.Text = "Load from database";
		 this.loadFromDatabaseToolStripMenuItem.Click += new System.EventHandler(this.loadFromDatabaseToolStripMenuItem_Click);
		 // 
		 // MainForm
		 // 
		 this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
		 this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
		 this.ClientSize = new System.Drawing.Size(1168, 597);
		 this.Controls.Add(this.lblMax);
		 this.Controls.Add(this.ctrlHistogram);
		 this.Controls.Add(this.lblAverage);
		 this.Controls.Add(this.cmdBatchAnalyze);
		 this.Controls.Add(this.ctrlResults);
		 this.Controls.Add(this.label4);
		 this.Controls.Add(this.ctrlListSolutions);
		 this.Controls.Add(this.cmdAnalyze);
		 this.Controls.Add(this.cmbSelMetric);
		 this.Controls.Add(this.label3);
		 this.Controls.Add(this.cmbSelProblem);
		 this.Controls.Add(this.label2);
		 this.Controls.Add(this.ctrlListProblems);
		 this.Controls.Add(this.label1);
		 this.Controls.Add(this.menuStrip1);
		 this.MainMenuStrip = this.menuStrip1;
		 this.Name = "MainForm";
		 this.Text = "Code Similarity Calculator";
		 this.Load += new System.EventHandler(this.MainForm_Load);
		 this.menuStrip1.ResumeLayout(false);
		 this.menuStrip1.PerformLayout();
		 this.ResumeLayout(false);
		 this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.MenuStrip menuStrip1;
    private System.Windows.Forms.ToolStripMenuItem optionsToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem loadFormDirectoryToolStripMenuItem;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.ListView ctrlListProblems;
    private System.Windows.Forms.ColumnHeader columnHeader1;
    private System.Windows.Forms.ColumnHeader columnHeader2;
    private System.Windows.Forms.Label label2;
    private System.Windows.Forms.ComboBox cmbSelProblem;
    private System.Windows.Forms.Label label3;
    private System.Windows.Forms.ComboBox cmbSelMetric;
    private System.Windows.Forms.Button cmdAnalyze;
    private System.Windows.Forms.ListView ctrlListSolutions;
    private System.Windows.Forms.ColumnHeader columnHeader3;
    private System.Windows.Forms.ColumnHeader columnHeader4;
    private System.Windows.Forms.Label label4;
     private CSC.Presentation.ctrlProblemComparisonResults ctrlResults;
     private System.Windows.Forms.ToolTip ResultsToolTip;
     private System.Windows.Forms.Button cmdBatchAnalyze;
	 private System.Windows.Forms.Label lblAverage;
	 private CSC.Presentation.ctrlProblemComparisonFrequency ctrlHistogram;
	 private System.Windows.Forms.Label lblMax;
	 private System.Windows.Forms.ToolStripMenuItem loadFromDatabaseToolStripMenuItem;
  }
}

