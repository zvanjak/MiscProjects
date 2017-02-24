namespace App_ProgramLineCounter
{
    partial class Form1
    {

        private System.ComponentModel.IContainer components = null;

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
            this.DirectoryBox = new System.Windows.Forms.TextBox();
            this.BrowseButton = new System.Windows.Forms.Button();
            this.DirectoryLabel = new System.Windows.Forms.Label();
            this.ResultGrid = new System.Windows.Forms.DataGridView();
            this.Path = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Extension = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Total_lines = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Blank_lines = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Comments = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Mixed_lines = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.InputGroup = new System.Windows.Forms.GroupBox();
            this.panel2 = new System.Windows.Forms.Panel();
            this.panel1 = new System.Windows.Forms.Panel();
            this.ExtensionLabel = new System.Windows.Forms.Label();
            this.ExtensionJAVA = new System.Windows.Forms.CheckBox();
            this.ExtensionC = new System.Windows.Forms.CheckBox();
            this.ExtensionCPP = new System.Windows.Forms.CheckBox();
            this.ExtensionH = new System.Windows.Forms.CheckBox();
            this.ExtensionCS = new System.Windows.Forms.CheckBox();
            this.AnalyseButton = new System.Windows.Forms.Button();
            this.ResultGroup = new System.Windows.Forms.GroupBox();
            this.Table = new System.Windows.Forms.TableLayoutPanel();
            this.DirectoriesLabel = new System.Windows.Forms.TextBox();
            this.Directories = new System.Windows.Forms.TextBox();
            this.Files = new System.Windows.Forms.TextBox();
            this.FilesLabel = new System.Windows.Forms.TextBox();
            this.FolderBrowser = new System.Windows.Forms.FolderBrowserDialog();
            ((System.ComponentModel.ISupportInitialize)(this.ResultGrid)).BeginInit();
            this.InputGroup.SuspendLayout();
            this.panel2.SuspendLayout();
            this.panel1.SuspendLayout();
            this.ResultGroup.SuspendLayout();
            this.Table.SuspendLayout();
            this.SuspendLayout();
            // 
            // DirectoryBox
            // 
            this.DirectoryBox.Location = new System.Drawing.Point(76, 7);
            this.DirectoryBox.Name = "DirectoryBox";
            this.DirectoryBox.Size = new System.Drawing.Size(206, 20);
            this.DirectoryBox.TabIndex = 2;
            // 
            // BrowseButton
            // 
            this.BrowseButton.Location = new System.Drawing.Point(296, 5);
            this.BrowseButton.Name = "BrowseButton";
            this.BrowseButton.Size = new System.Drawing.Size(75, 23);
            this.BrowseButton.TabIndex = 1;
            this.BrowseButton.Text = "Browse...";
            this.BrowseButton.UseVisualStyleBackColor = true;
            this.BrowseButton.Click += new System.EventHandler(this.BrowseButton_Click);
            // 
            // DirectoryLabel
            // 
            this.DirectoryLabel.AutoSize = true;
            this.DirectoryLabel.Location = new System.Drawing.Point(-3, 10);
            this.DirectoryLabel.Name = "DirectoryLabel";
            this.DirectoryLabel.Size = new System.Drawing.Size(73, 13);
            this.DirectoryLabel.TabIndex = 0;
            this.DirectoryLabel.Text = "Directory path";
            // 
            // ResultGrid
            // 
            this.ResultGrid.AccessibleRole = System.Windows.Forms.AccessibleRole.None;
            this.ResultGrid.AllowUserToDeleteRows = false;
            this.ResultGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.ResultGrid.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Path,
            this.Extension,
            this.Total_lines,
            this.Blank_lines,
            this.Comments,
            this.Mixed_lines});
            this.ResultGrid.ImeMode = System.Windows.Forms.ImeMode.On;
            this.ResultGrid.Location = new System.Drawing.Point(19, 124);
            this.ResultGrid.Name = "ResultGrid";
            this.ResultGrid.ReadOnly = true;
            this.ResultGrid.Size = new System.Drawing.Size(525, 150);
            this.ResultGrid.TabIndex = 3;
            // 
            // Path
            // 
            this.Path.HeaderText = "Path";
            this.Path.Name = "Path";
            this.Path.Width = 180;
            // 
            // Extension
            // 
            this.Extension.HeaderText = "Extension";
            this.Extension.Name = "Extension";
            this.Extension.Width = 60;
            // 
            // Total_lines
            // 
            this.Total_lines.HeaderText = "Total lines";
            this.Total_lines.Name = "Total_lines";
            this.Total_lines.Width = 60;
            // 
            // Blank_lines
            // 
            this.Blank_lines.HeaderText = "Blank lines";
            this.Blank_lines.Name = "Blank_lines";
            this.Blank_lines.Width = 60;
            // 
            // Comments
            // 
            this.Comments.HeaderText = "Comments";
            this.Comments.Name = "Comments";
            this.Comments.Width = 60;
            // 
            // Mixed_lines
            // 
            this.Mixed_lines.HeaderText = "Mixed Lines";
            this.Mixed_lines.Name = "Mixed_lines";
            this.Mixed_lines.Width = 60;
            // 
            // InputGroup
            // 
            this.InputGroup.Controls.Add(this.panel2);
            this.InputGroup.Controls.Add(this.panel1);
            this.InputGroup.Controls.Add(this.AnalyseButton);
            this.InputGroup.Location = new System.Drawing.Point(88, 29);
            this.InputGroup.Name = "InputGroup";
            this.InputGroup.Size = new System.Drawing.Size(420, 157);
            this.InputGroup.TabIndex = 4;
            this.InputGroup.TabStop = false;
            this.InputGroup.Text = "Input";
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.DirectoryLabel);
            this.panel2.Controls.Add(this.DirectoryBox);
            this.panel2.Controls.Add(this.BrowseButton);
            this.panel2.Location = new System.Drawing.Point(19, 31);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(374, 35);
            this.panel2.TabIndex = 12;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.ExtensionLabel);
            this.panel1.Controls.Add(this.ExtensionJAVA);
            this.panel1.Controls.Add(this.ExtensionC);
            this.panel1.Controls.Add(this.ExtensionCPP);
            this.panel1.Controls.Add(this.ExtensionH);
            this.panel1.Controls.Add(this.ExtensionCS);
            this.panel1.Location = new System.Drawing.Point(19, 65);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(374, 41);
            this.panel1.TabIndex = 11;
            // 
            // ExtensionLabel
            // 
            this.ExtensionLabel.AutoSize = true;
            this.ExtensionLabel.Location = new System.Drawing.Point(-3, 11);
            this.ExtensionLabel.Name = "ExtensionLabel";
            this.ExtensionLabel.Size = new System.Drawing.Size(53, 13);
            this.ExtensionLabel.TabIndex = 4;
            this.ExtensionLabel.Text = "Extension";
            // 
            // ExtensionJAVA
            // 
            this.ExtensionJAVA.AutoSize = true;
            this.ExtensionJAVA.Location = new System.Drawing.Point(279, 11);
            this.ExtensionJAVA.Name = "ExtensionJAVA";
            this.ExtensionJAVA.Size = new System.Drawing.Size(49, 17);
            this.ExtensionJAVA.TabIndex = 10;
            this.ExtensionJAVA.Text = ".java";
            this.ExtensionJAVA.UseVisualStyleBackColor = true;
            // 
            // ExtensionC
            // 
            this.ExtensionC.AutoSize = true;
            this.ExtensionC.Location = new System.Drawing.Point(72, 11);
            this.ExtensionC.Name = "ExtensionC";
            this.ExtensionC.Size = new System.Drawing.Size(35, 17);
            this.ExtensionC.TabIndex = 6;
            this.ExtensionC.Text = ".c";
            this.ExtensionC.UseVisualStyleBackColor = true;
            // 
            // ExtensionCPP
            // 
            this.ExtensionCPP.AutoSize = true;
            this.ExtensionCPP.Location = new System.Drawing.Point(220, 11);
            this.ExtensionCPP.Name = "ExtensionCPP";
            this.ExtensionCPP.Size = new System.Drawing.Size(47, 17);
            this.ExtensionCPP.TabIndex = 9;
            this.ExtensionCPP.Text = ".cpp";
            this.ExtensionCPP.UseVisualStyleBackColor = true;
            // 
            // ExtensionH
            // 
            this.ExtensionH.AutoSize = true;
            this.ExtensionH.Location = new System.Drawing.Point(123, 11);
            this.ExtensionH.Name = "ExtensionH";
            this.ExtensionH.Size = new System.Drawing.Size(35, 17);
            this.ExtensionH.TabIndex = 7;
            this.ExtensionH.Text = ".h";
            this.ExtensionH.UseVisualStyleBackColor = true;
            // 
            // ExtensionCS
            // 
            this.ExtensionCS.AutoSize = true;
            this.ExtensionCS.Location = new System.Drawing.Point(174, 11);
            this.ExtensionCS.Name = "ExtensionCS";
            this.ExtensionCS.Size = new System.Drawing.Size(40, 17);
            this.ExtensionCS.TabIndex = 8;
            this.ExtensionCS.Text = ".cs";
            this.ExtensionCS.UseVisualStyleBackColor = true;
            // 
            // AnalyseButton
            // 
            this.AnalyseButton.Location = new System.Drawing.Point(155, 119);
            this.AnalyseButton.Name = "AnalyseButton";
            this.AnalyseButton.Size = new System.Drawing.Size(108, 23);
            this.AnalyseButton.TabIndex = 3;
            this.AnalyseButton.Text = "Analyse!";
            this.AnalyseButton.UseVisualStyleBackColor = true;
            this.AnalyseButton.Click += new System.EventHandler(this.AnalyseButton_Click);
            // 
            // ResultGroup
            // 
            this.ResultGroup.Controls.Add(this.Table);
            this.ResultGroup.Controls.Add(this.ResultGrid);
            this.ResultGroup.Location = new System.Drawing.Point(23, 201);
            this.ResultGroup.Name = "ResultGroup";
            this.ResultGroup.Size = new System.Drawing.Size(564, 301);
            this.ResultGroup.TabIndex = 5;
            this.ResultGroup.TabStop = false;
            this.ResultGroup.Text = "Results";
            // 
            // Table
            // 
            this.Table.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.Single;
            this.Table.ColumnCount = 2;
            this.Table.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 71.42857F));
            this.Table.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 28.57143F));
            this.Table.Controls.Add(this.DirectoriesLabel, 0, 0);
            this.Table.Controls.Add(this.Directories, 1, 0);
            this.Table.Controls.Add(this.Files, 1, 1);
            this.Table.Controls.Add(this.FilesLabel, 0, 1);
            this.Table.Location = new System.Drawing.Point(19, 45);
            this.Table.Name = "Table";
            this.Table.RowCount = 2;
            this.Table.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.Table.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.Table.Size = new System.Drawing.Size(176, 47);
            this.Table.TabIndex = 6;
            // 
            // DirectoriesLabel
            // 
            this.DirectoriesLabel.BackColor = System.Drawing.SystemColors.MenuBar;
            this.DirectoriesLabel.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.DirectoriesLabel.Location = new System.Drawing.Point(4, 4);
            this.DirectoriesLabel.Name = "DirectoriesLabel";
            this.DirectoriesLabel.Size = new System.Drawing.Size(117, 13);
            this.DirectoriesLabel.TabIndex = 2;
            this.DirectoriesLabel.Text = "Total subdirectories";
            // 
            // Directories
            // 
            this.Directories.BackColor = System.Drawing.SystemColors.MenuBar;
            this.Directories.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.Directories.Location = new System.Drawing.Point(128, 4);
            this.Directories.Name = "Directories";
            this.Directories.Size = new System.Drawing.Size(44, 13);
            this.Directories.TabIndex = 0;
            this.Directories.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // Files
            // 
            this.Files.BackColor = System.Drawing.SystemColors.MenuBar;
            this.Files.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.Files.Location = new System.Drawing.Point(128, 27);
            this.Files.Name = "Files";
            this.Files.Size = new System.Drawing.Size(44, 13);
            this.Files.TabIndex = 1;
            this.Files.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // FilesLabel
            // 
            this.FilesLabel.BackColor = System.Drawing.SystemColors.MenuBar;
            this.FilesLabel.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.FilesLabel.Location = new System.Drawing.Point(4, 27);
            this.FilesLabel.Name = "FilesLabel";
            this.FilesLabel.Size = new System.Drawing.Size(117, 13);
            this.FilesLabel.TabIndex = 3;
            this.FilesLabel.Text = "Total files";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(613, 517);
            this.Controls.Add(this.ResultGroup);
            this.Controls.Add(this.InputGroup);
            this.Name = "Form1";
            this.Text = "Code Analyser";
            ((System.ComponentModel.ISupportInitialize)(this.ResultGrid)).EndInit();
            this.InputGroup.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResultGroup.ResumeLayout(false);
            this.Table.ResumeLayout(false);
            this.Table.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox InputGroup;
        private System.Windows.Forms.GroupBox ResultGroup;

        private System.Windows.Forms.TextBox DirectoryBox;
        private System.Windows.Forms.Button BrowseButton;
        private System.Windows.Forms.Label DirectoryLabel;

        private System.Windows.Forms.TableLayoutPanel Table;
        private System.Windows.Forms.TextBox Directories;
        private System.Windows.Forms.TextBox Files;
        private System.Windows.Forms.TextBox DirectoriesLabel;
        private System.Windows.Forms.TextBox FilesLabel;

        private System.Windows.Forms.DataGridView ResultGrid;
        private System.Windows.Forms.DataGridViewTextBoxColumn Path;
        private System.Windows.Forms.DataGridViewTextBoxColumn Extension;
        private System.Windows.Forms.DataGridViewTextBoxColumn Total_lines;
        private System.Windows.Forms.DataGridViewTextBoxColumn Blank_lines;
        private System.Windows.Forms.DataGridViewTextBoxColumn Comments;
        private System.Windows.Forms.DataGridViewTextBoxColumn Mixed_lines;

        private System.Windows.Forms.FolderBrowserDialog FolderBrowser;
        private System.Windows.Forms.Button AnalyseButton;
        private System.Windows.Forms.Label ExtensionLabel;

        private System.Windows.Forms.CheckBox ExtensionC;
        private System.Windows.Forms.CheckBox ExtensionJAVA;
        private System.Windows.Forms.CheckBox ExtensionCPP;
        private System.Windows.Forms.CheckBox ExtensionCS;
        private System.Windows.Forms.CheckBox ExtensionH;

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
    }
}

