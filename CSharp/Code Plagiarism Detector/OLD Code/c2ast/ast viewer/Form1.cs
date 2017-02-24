using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Xml;
using System.Diagnostics;

namespace ast_viewer
{

    public partial class Form1 : Form
    {
        private enum AST_TreeIcons {
            Error = 0,
            Root,
            Delegate,
            Field,
            Method,
            Class,
            Typedef,
            Namespace,
            Intristic,
            Enum,
            Struct,
            Union
        }

        const String include_dir = "include";
#if DEBUG
        const String c2ast_fname = @"..\..\..\debug\c2ast.exe";
#else
        const String c2ast_fname = "c2ast.exe";
#endif


        public Form1()
        {
            InitializeComponent();

            if (File.Exists("temp.txt"))
            {
                textBox1.Text = File.ReadAllText("temp.txt");
                textBox1.SelectionStart = 0;
                textBox1.SelectionLength = 0;
            }
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                String text = File.ReadAllText(openFileDialog1.FileName);
                textBox1.Text = text;
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void treealizeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            String xmloutfname = Path.GetTempFileName();    // tmp fajl za xml

            //////////////////
            // sejva text
            File.WriteAllText("temp.txt", textBox1.Text);

            //////////////////
            // pokrene konvertora...
            String args = "temp.txt \"-x" + xmloutfname + "\"";
            Process c2ast = StartApp(c2ast_fname, args);

            if (c2ast.ExitCode != 0)
            {
                MessageBox.Show(c2ast.StandardOutput.ReadToEnd(), "a2ast error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                File.Delete(xmloutfname);
                return;
            }

            //////////////////
            // filla tree
            try
            {
                XmlDocument xd = new XmlDocument();
                xd.Load(xmloutfname);
                TreeNode[] nod = xmlproc(xd.ChildNodes);

                treeView1.Nodes.Clear();
                treeView1.Nodes.AddRange(nod);
            }
            catch (System.Exception err)
            {
                MessageBox.Show("Greška: " + err.Message, "Error!", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            File.Delete(xmloutfname);
        }

        private static TreeNode[] xmlproc(XmlNodeList nl)
        {
            TreeNode[] r = new TreeNode[0];
            TreeNode t;

            foreach (XmlNode xn in nl)
            {
                t = new TreeNode();

                switch (xn.Name)
                {
                    case "root":
                        t.Text = "root";
                        t.Expand();
                        t.Nodes.AddRange(xmlproc(xn.ChildNodes));
                        t.ImageIndex = (int)AST_TreeIcons.Root;
                        break;

                    case "types":
                        t.Text = "[types]";
                        t.Nodes.AddRange(xmlproc(xn.ChildNodes));
                        t.Tag = "Sadrzi: " + t.Nodes.Count + " tipova.";
                        t.ImageIndex = (int)AST_TreeIcons.Delegate;
                        break;

                    case "type":
                        t.Text = xn.Attributes["name"].InnerText;
                        t.Tag = xn.InnerText;
                        t.ImageIndex = (int)AST_TreeIcons.Typedef;
                        break;

                    case "declarations":
                        t.Text = "[declarations]";
                        t.Nodes.AddRange(xmlproc(xn.ChildNodes));
                        t.Tag = "Sadrzi: " + t.Nodes.Count + " deklaracija.";
                        t.ImageIndex = (int)AST_TreeIcons.Delegate;
                        break;

                    case "decl":
                        t.Text = xn.Attributes["name"].InnerText;
                        t.Tag = "Type: " + xn.Attributes["type"].InnerText + "\r\nValue:\r\n" + xn.InnerText;
                        t.ImageIndex = (int)Type2ati(xn.Attributes["type"].InnerText);
                        break;

                    case "function":
                        t.Text = xn.Attributes["name"].InnerText;
                        t.Tag = "Tip: " + xn.Attributes["type"].InnerText;
                        t.Nodes.AddRange(xmlproc(xn.ChildNodes));
                        t.ImageIndex = (int)AST_TreeIcons.Method;
                        break;

                    case "code":
                        t.Text = "code";
                        t.Nodes.AddRange(xmlproc(xn.ChildNodes));
                        t.ImageIndex = (int)AST_TreeIcons.Namespace;
                        break;

                    case "block":
                        t.Text = "block";
                        t.Tag = xn.InnerText;
                        t.ImageIndex = (int)AST_TreeIcons.Intristic;
                        break;

                    case "if":
                    case "do":
                    case "for":
                    case "while":
                        t.Text = xn.Name;
                        t.Tag = "Uvjet: " + xn.Attributes["condition"].InnerText;
                        t.Nodes.AddRange(xmlproc(xn.ChildNodes));
                        t.ImageIndex = (int)AST_TreeIcons.Namespace;
                        break;

                    case "true":
                    case "false":
                        t.Text = "if -> " + xn.Name;
                        t.Nodes.AddRange(xmlproc(xn.ChildNodes));
                        t.ImageIndex = (int)AST_TreeIcons.Namespace;
                        break;
                        
                    default:
                        throw new System.Exception("Nepoznat nod: " + xn.Name + "!");
                }

                t.SelectedImageIndex = t.ImageIndex;

                System.Array.Resize(ref r, r.GetLength(0) + 1);
                r[r.GetLength(0) - 1] = t;
            }

            return r;
        }

        private static AST_TreeIcons Type2ati(String type)
        {
            int p = type.IndexOf('$');
            if (p > 0)
            {
                switch (type.Substring(0, p))
                {
                    case "struct": return AST_TreeIcons.Struct;
                    case "union": return AST_TreeIcons.Union;
                    case "enum": return AST_TreeIcons.Enum;
                }
                throw new Exception("Neki nepoznati blok-tip: \"" + type.Substring(0, p) + "\"");
            }

            if (type[0] == '{')
            {
                /* detekcija da li je enum ili struct, ili union... ne zvuèi jednostavno...
                 * Dapaèe... Nemoguæe je. Ideja: neka c2ast koristi drugaèije zagrade */
            }
            return AST_TreeIcons.Field;
        }

        private static Process StartApp(String fname, String arguments)
        {
            Process proc = new Process();
            proc.EnableRaisingEvents = false;
            proc.StartInfo.CreateNoWindow = true;
            proc.StartInfo.UseShellExecute = false;
            proc.StartInfo.RedirectStandardOutput = true;
            proc.StartInfo.RedirectStandardError = true;
            proc.StartInfo.FileName = fname;
            proc.StartInfo.Arguments = arguments;
            proc.Start();
            proc.WaitForExit();

            return proc;
        }

        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {
            if (treeView1.SelectedNode != null)
                textBox2.Text = (String)treeView1.SelectedNode.Tag;
        }

        private void expandAllToolStripMenuItem_Click(object sender, EventArgs e)
        {
            treeView1.ExpandAll();
        }

        private void collapseAllToolStripMenuItem_Click(object sender, EventArgs e)
        {
            treeView1.CollapseAll();
        }

        private void precompileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            String tmpfjl_i = Path.GetTempFileName();
            String tmpfjl_o = Path.GetTempFileName();

            File.WriteAllText(tmpfjl_i, textBox1.Text);

            try
            {

                // args: -nostdinc -I<inklud_dir> -E -xc <fajl> -o<outfajl>
                String args = "-nostdinc \"-I" + include_dir + "\" -E -xc \"" + tmpfjl_i + "\" \"-o" + tmpfjl_o + "\"";
                Process gcc = StartApp("gcc", args);

                if (gcc.ExitCode == 0)
                {
                    textBox1.Text = File.ReadAllText(tmpfjl_o);
                }
                else
                {
                    MessageBox.Show(gcc.StandardError.ReadToEnd(), "gcc error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            catch (Exception err)
            {
                MessageBox.Show(err.Message, "Error!", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            File.Delete(tmpfjl_i);
            File.Delete(tmpfjl_o);
        }
    }
}