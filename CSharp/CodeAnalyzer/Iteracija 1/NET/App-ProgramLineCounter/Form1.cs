using System;
using System.Collections;
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
        List<FileCodeInfo> al = new List<FileCodeInfo>();
        bool[] ColumnClicked = new bool[6];

        public Form1()
        {
            InitializeComponent();
            for (int i = 0; i < 6; i++)
              ColumnClicked[i] = false;
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

                listView1.Items.Clear();    //
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


                FileCodeInfo Info;

                al.Clear();
                //BindingList<FileCodeInfo> bindList= new BindingList<FileCodeInfo>();

                for (int i = 0; i < EnumFiles.Duljina; i++)
                {

                  if (listExtension.Contains(((FileInfo)EnumFiles[i]).Extension))
                  {

                    Data1 data = new Data1((FileInfo)EnumFiles[i]);
                    Info = FileAnalyzer.AnalyseFile(data);

                    al.Add(Info);
                    //bindList.Add(Info);
                    //Binding_source.Add(Info);
                    //ResultRow = new string[] { Info.FileName, ((FileInfo)EnumFiles[i]).Extension, (Info.NumberOfLines).ToString(), (Info.NumberOfEmptyLines).ToString(), (Info.NumberOfComments).ToString(), (Info.NumberOfMixedLines).ToString() };  
                    //ResultGrid.Rows.Add(ResultRow);

                    data.Dispose();
                  }

                }

                for (int j = 0; j < al.Count; j++)
                {
                  ListViewItem listItem = new ListViewItem(al[j].FileName);
                  listItem.SubItems.Add(al[j].Extension);
                  listItem.SubItems.Add((al[j].NumberOfLines).ToString());
                  listItem.SubItems.Add((al[j].NumberOfEmptyLines).ToString());
                  listItem.SubItems.Add((al[j].NumberOfComments).ToString());
                  listItem.SubItems.Add((al[j].NumberOfMixedLines).ToString());
                  listView1.Items.Add(listItem);
                }

            }
            catch (Exception ex)
            {
                //alert
                MessageBox.Show(ex.Message);
            }
        }

 
      private void listView1_ColumnClick(object sender, ColumnClickEventArgs e)
      {
        /*
        switch(e.Column)
        {
          case 0: al.Sort(new FileCodeInfoCompareFileName());
                  break;
          case 1: al.Sort(new FileCodeInfoCompareExtension());
                  break;
          case 2: al.Sort(new FileCodeInfoCompareTotalLines());
                  break;
          case 3: al.Sort(new FileCodeInfoCompareBlankLines());
                  break;
          case 4: al.Sort(new FileCodeInfoCompareComments());
                  break;
          case 5: al.Sort(new FileCodeInfoCompareMixedLines());
                  break;

        }
        */

        switch (e.Column)
        {
          case 0:
            if (!ColumnClicked[0])
            {
              al.Sort(new FileCodeInfoCompareFileName_ASC());
              ColumnClicked[0] = true;
            }
            else
            {
              al.Sort(new FileCodeInfoCompareFileName_DESC());
              ColumnClicked[0] = false;
            }
            break;
          case 1: 
            if (!ColumnClicked[1])
            {
              al.Sort(new FileCodeInfoCompareExtension_ASC());
              ColumnClicked[1] = true;
            }
            else
            {
              al.Sort(new FileCodeInfoCompareExtension_DESC());
              ColumnClicked[1] = false;
            }
            break;
          case 2:
            if (!ColumnClicked[2])
            {
              al.Sort(new FileCodeInfoCompareTotalLines_ASC());
              ColumnClicked[2] = true;
            }
            else
            {
              al.Sort(new FileCodeInfoCompareTotalLines_DESC());
              ColumnClicked[2] = false;
            }
            break;
          case 3:
            if (!ColumnClicked[3])
            {
              al.Sort(new FileCodeInfoCompareBlankLines_ASC());
              ColumnClicked[3] = true;
            }
            else
            {
              al.Sort(new FileCodeInfoCompareBlankLines_DESC());
              ColumnClicked[3] = false;
            }
            break;
          case 4: 
            if (!ColumnClicked[4])
            {
              al.Sort(new FileCodeInfoCompareComments_ASC());
              ColumnClicked[4] = true;
            }
            else
            {
              al.Sort(new FileCodeInfoCompareComments_DESC());
              ColumnClicked[4] = false;
            }
            break;
          case 5:
            if (!ColumnClicked[5])
            {
              al.Sort(new FileCodeInfoCompareMixedLines_ASC());
              ColumnClicked[5] = true;
            }
            else
            {
              al.Sort(new FileCodeInfoCompareMixedLines_DESC());
              ColumnClicked[5] = false;
            }
            break;

        }


        listView1.Items.Clear();
        for (int i = 0; i < al.Count; i++)
        {
          ListViewItem listItem = new ListViewItem(al[i].FileName);
          listItem.SubItems.Add(al[i].Extension);
          listItem.SubItems.Add((al[i].NumberOfLines).ToString());
          listItem.SubItems.Add((al[i].NumberOfEmptyLines).ToString());
          listItem.SubItems.Add((al[i].NumberOfComments).ToString());
          listItem.SubItems.Add((al[i].NumberOfMixedLines).ToString());
          listView1.Items.Add(listItem);
        }
      }
    }
}

  