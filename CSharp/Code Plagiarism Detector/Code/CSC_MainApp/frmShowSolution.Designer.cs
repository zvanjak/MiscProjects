namespace CSC.MainApp
{
  partial class frmShowSolution
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
      this.richTextSol = new System.Windows.Forms.RichTextBox();
      this.SuspendLayout();
      // 
      // button1
      // 
      this.button1.DialogResult = System.Windows.Forms.DialogResult.OK;
      this.button1.Location = new System.Drawing.Point(203, 438);
      this.button1.Name = "button1";
      this.button1.Size = new System.Drawing.Size(75, 23);
      this.button1.TabIndex = 1;
      this.button1.Text = "Close";
      this.button1.UseVisualStyleBackColor = true;
      // 
      // richTextSol
      // 
      this.richTextSol.Location = new System.Drawing.Point(12, 12);
      this.richTextSol.Name = "richTextSol";
      this.richTextSol.Size = new System.Drawing.Size(480, 410);
      this.richTextSol.TabIndex = 0;
      this.richTextSol.Text = "";
      // 
      // frmShowSolution
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(520, 473);
      this.Controls.Add(this.button1);
      this.Controls.Add(this.richTextSol);
      this.Name = "frmShowSolution";
      this.Text = "frmShowSolution";
      this.ResumeLayout(false);

    }

    #endregion

    private System.Windows.Forms.Button button1;
    private System.Windows.Forms.RichTextBox richTextSol;
  }
}