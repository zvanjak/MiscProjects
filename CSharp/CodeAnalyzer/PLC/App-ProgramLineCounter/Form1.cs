using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using ProgramLineCounter;


namespace App_ProgramLineCounter
{
    public partial class Form1 : Form
    {
        string DirectoryName;
        List<string> listExtension = new List<string>();

        public Form1()
        {
            InitializeComponent();
        }

        private void BrowseButton_Click(object sender, EventArgs e)
        {
            //otvara se Browse...
            DialogResult Result = FolderBrowser.ShowDialog();
            if (Result == DialogResult.OK)          
                DirectoryBox.Text = FolderBrowser.SelectedPath;
        }

        private void AnalyseButton_Click(object sender, EventArgs e)
        {
            try
            {
                ResultGrid.RowCount = 1; //prebriše dosadašnje rezultate (ako ih je bilo)
                listExtension.Clear();  //isprazni listu

                DirectoryName = DirectoryBox.Text;
                if (DirectoryName == "")
                {
                    throw new DirectoryNotFoundException("Enter directory path!");
                }

                //pregledavam checkirane ekstenzije
                if (ExtensionC.Checked) listExtension.Add(ExtensionC.Text);
                if (ExtensionH.Checked) listExtension.Add(ExtensionH.Text);
                if (ExtensionCPP.Checked) listExtension.Add(ExtensionCPP.Text);
                if (ExtensionJAVA.Checked) listExtension.Add(ExtensionJAVA.Text);
                if (ExtensionCS.Checked) listExtension.Add(ExtensionCS.Text);

                EnumerateFiles EnumFiles = new EnumerateFiles(DirectoryName);
                EnumFiles.Enumerate();

                //ispis (broj datoteka, direktorija)
                Directories.Text = (EnumFiles.Directories).ToString();
                Files.Text = (EnumFiles.Files).ToString();

                //ispis rezultata za pojedinu datoteku
                FileCodeInfo Info;
                string[] ResultRow;
                for (int i = 0; i < EnumFiles.Duljina; i++)
                {
                    if (listExtension.Contains(((FileInfo)EnumFiles[i]).Extension))
                    {
                        Data1 data = new Data1((FileInfo)EnumFiles[i]);
                        Info = FileAnalyzer.AnalyseFile(data);
                        ResultRow = new string[] { Info.FileName, ((FileInfo)EnumFiles[i]).Extension, (Info.NumberOfLines).ToString(), (Info.NumberOfEmptyLines).ToString(), (Info.NumberOfComments).ToString(), (Info.NumberOfMixedLines).ToString() };
                        ResultGrid.Rows.Add(ResultRow);
                        data.Dispose();
                    }
                }

            }
            catch (Exception ex)
            {
                //alert
                MessageBox.Show(ex.Message);
            }
        }
            


    }
}