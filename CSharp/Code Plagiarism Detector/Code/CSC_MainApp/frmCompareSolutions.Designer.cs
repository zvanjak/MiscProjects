namespace CSC.MainApp
{
  partial class frmCompareSolutions
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
      this.button1 = new System.Windows.Forms.Button();
      this.txtSolution1 = new System.Windows.Forms.RichTextBox();
      this.txtSolution2 = new System.Windows.Forms.RichTextBox();
      this.SuspendLayout();
      // 
      // button1
      // 
      this.button1.DialogResult = System.Windows.Forms.DialogResult.OK;
      this.button1.Location = new System.Drawing.Point(399, 563);
      this.button1.Name = "button1";
      this.button1.Size = new System.Drawing.Size(75, 23);
      this.button1.TabIndex = 2;
      this.button1.Text = "Close";
      this.button1.UseVisualStyleBackColor = true;
      // 
      // txtSolution1
      // 
      this.txtSolution1.Location = new System.Drawing.Point(12, 24);
      this.txtSolution1.Name = "txtSolution1";
      this.txtSolution1.Size = new System.Drawing.Size(415, 517);
      this.txtSolution1.TabIndex = 3;
      this.txtSolution1.Text = "";
      this.txtSolution1.TextChanged += new System.EventHandler(this.txtSolution1_TextChanged);
      // 
      // txtSolution2
      // 
      this.txtSolution2.Location = new System.Drawing.Point(441, 24);
      this.txtSolution2.Name = "txtSolution2";
      this.txtSolution2.Size = new System.Drawing.Size(420, 517);
      this.txtSolution2.TabIndex = 4;
      this.txtSolution2.Text = "";
      // 
      // frmCompareSolutions
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(873, 603);
      this.Controls.Add(this.txtSolution2);
      this.Controls.Add(this.txtSolution1);
      this.Controls.Add(this.button1);
      this.Name = "frmCompareSolutions";
      this.Text = "Compare solutions";
      this.ResumeLayout(false);

    }

    #endregion

    private System.Windows.Forms.Button button1;
    private System.Windows.Forms.RichTextBox txtSolution1;
    private System.Windows.Forms.RichTextBox txtSolution2;
  }
}