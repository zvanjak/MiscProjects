namespace CSC.Presentation
{
	partial class ctrlProblemComparisonFrequency
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

    #region Component Designer generated code

    /// <summary> 
    /// Required method for Designer support - do not modify 
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
		 this.labelPeak = new System.Windows.Forms.Label();
		 this.SuspendLayout();
		 // 
		 // labelPeak
		 // 
		 this.labelPeak.AutoSize = true;
		 this.labelPeak.Location = new System.Drawing.Point(164, 29);
		 this.labelPeak.Name = "labelPeak";
		 this.labelPeak.Size = new System.Drawing.Size(0, 13);
		 this.labelPeak.TabIndex = 0;
		 // 
		 // ctrlProblemComparisonFrequency
		 // 
		 this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
		 this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
		 this.BackColor = System.Drawing.Color.White;
		 this.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
		 this.Controls.Add(this.labelPeak);
		 this.Name = "ctrlProblemComparisonFrequency";
		 this.Size = new System.Drawing.Size(300, 300);
		 this.Paint += new System.Windows.Forms.PaintEventHandler(this.ctrlProblemComparisonFrequency_Paint);
		 this.ResumeLayout(false);
		 this.PerformLayout();

    }

    #endregion

	 private System.Windows.Forms.Label labelPeak;
  }
}
