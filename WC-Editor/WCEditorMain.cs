using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace WC_Editor
{
    public partial class WCEditorMain : Form
    {
        public Mapa map;
        Image []imgMiniConstructions = new Image[7];
        public Image[] imgConstructions = new Image[5];

        //Image[] imgMiniGrounds = new Image[2];
        
        public static WCEditorMain mySelf;
        public PictureBox[,] pictures = new PictureBox[5, 10];
        public static ObjectiveForm objForm = new ObjectiveForm();
        public static AboutForm abtForm = new AboutForm();


        public WCEditorMain()
        {
            InitializeComponent();

            imgMiniConstructions[0] = Image.FromFile("res\\miniInvalid.bmp");
            imgMiniConstructions[1] = Image.FromFile("res\\miniGrass.bmp");
            imgMiniConstructions[2] = Image.FromFile("res\\miniCamp.bmp");
            imgMiniConstructions[3] = Image.FromFile("res\\miniFortress.bmp");
            imgMiniConstructions[4] = Image.FromFile("res\\miniCastle.bmp");
            imgMiniConstructions[5] = Image.FromFile("res\\miniVillage.bmp");
            imgMiniConstructions[6] = Image.FromFile("res\\miniCity.bmp");


            imgConstructions[0] = Image.FromFile("res\\camp.png");
            imgConstructions[1] = Image.FromFile("res\\fortress.png");
            imgConstructions[2] = Image.FromFile("res\\castle.png");
            imgConstructions[3] = Image.FromFile("res\\village.png");
            imgConstructions[4] = Image.FromFile("res\\city.png");
            
            //prueba para pintar algo
            //mapPictureBox.ima
            mySelf = this;

            pictures[0, 0] = pictureBox1;
            pictures[0, 1] = pictureBox2;
            pictures[0, 2] = pictureBox3;
            pictures[0, 3] = pictureBox4;
            pictures[0, 4] = pictureBox5;
            pictures[0, 5] = pictureBox6;
            pictures[0, 6] = pictureBox7;
            pictures[0, 7] = pictureBox8;
            pictures[0, 8] = pictureBox9;
            pictures[0, 9] = pictureBox10;
        
            pictures[1, 9] = pictureBox11;
            pictures[1, 8] = pictureBox12;
            pictures[1, 7] = pictureBox13;
            pictures[1, 6] = pictureBox14;
            pictures[1, 5] = pictureBox15;
            pictures[1, 4] = pictureBox16;
            pictures[1, 3] = pictureBox17;
            pictures[1, 2] = pictureBox18;
            pictures[1, 1] = pictureBox19;
            pictures[1, 0] = pictureBox20;

            pictures[2, 9] = pictureBox21;
            pictures[2, 8] = pictureBox22;
            pictures[2, 7] = pictureBox23;
            pictures[2, 6] = pictureBox24;
            pictures[2, 5] = pictureBox25;
            pictures[2, 4] = pictureBox26;
            pictures[2, 3] = pictureBox27;
            pictures[2, 2] = pictureBox28;
            pictures[2, 1] = pictureBox29;
            pictures[2, 0] = pictureBox30;

            pictures[3, 9] = pictureBox31;
            pictures[3, 8] = pictureBox32;
            pictures[3, 7] = pictureBox33;
            pictures[3, 6] = pictureBox34;
            pictures[3, 5] = pictureBox35;
            pictures[3, 4] = pictureBox36;
            pictures[3, 3] = pictureBox37;
            pictures[3, 2] = pictureBox38;
            pictures[3, 1] = pictureBox39;
            pictures[3, 0] = pictureBox40;

            pictures[4, 9] = pictureBox41;
            pictures[4, 8] = pictureBox42;
            pictures[4, 7] = pictureBox43;
            pictures[4, 6] = pictureBox44;
            pictures[4, 5] = pictureBox45;
            pictures[4, 4] = pictureBox46;
            pictures[4, 3] = pictureBox47;
            pictures[4, 2] = pictureBox48;
            pictures[4, 1] = pictureBox49;
            pictures[4, 0] = pictureBox50;
        

            for(int i = 0; i < 5;i++)
                for (int j = 0; j < 10; j++)
                {
                    pictures[i, j].Click += mapCell_Click;
                    pictures[i, j].SizeMode = PictureBoxSizeMode.Zoom;
                }

            objForm.Visible = false;

            map = new Mapa();
            map.Init();
            map.Select(0, 0);
            
        }

        private void mapCell_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 10;j++)
                    if (pictures[i, j] == sender)
                       map.Select(i, j);
        }

        String curFile = "";

        public void LoadMap(String filename)
        {
            System.IO.FileStream file;
            System.IO.StreamReader reader;

            curFile = filename;
            file = System.IO.File.OpenRead(filename);
            reader = new System.IO.StreamReader(file);

            map.inix = int.Parse(reader.ReadLine());
            map.iniy = int.Parse(reader.ReadLine());
            map.inigold = int.Parse(reader.ReadLine());
            map.cpugold = int.Parse(reader.ReadLine());
            map.daytime = int.Parse(reader.ReadLine());
            map.dificulty = int.Parse(reader.ReadLine());

            map.objectiveCom = int.Parse(reader.ReadLine());
            map.objectivePar1 = int.Parse(reader.ReadLine());
            map.objectivePar2 = int.Parse(reader.ReadLine());
            map.objectiveEndsMission = int.Parse(reader.ReadLine());



            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 10; j++)
                {
                    map.areas[i, j].Reset();
                    map.areas[i, j].construccion = int.Parse(reader.ReadLine());
                    map.areas[i, j].unidentro = int.Parse(reader.ReadLine());
                    map.areas[i, j].unifuera = int.Parse(reader.ReadLine());
                    map.areas[i, j].unienemigo = int.Parse(reader.ReadLine());
                    map.areas[i, j].people = int.Parse(reader.ReadLine());
                    map.areas[i, j].raceowner = int.Parse(reader.ReadLine());
                    map.areas[i, j].racestriker = int.Parse(reader.ReadLine());
                    map.areas[i, j].integrity = int.Parse(reader.ReadLine());
                    map.areas[i, j].explored = int.Parse(reader.ReadLine());
                    map.areas[i, j].evervisible = int.Parse(reader.ReadLine());
                }

            
            StartAreaButton.Text = map.inix+" , "+map.iniy;
            cDaytime.SelectedIndex = map.daytime;
            cDificulty.SelectedIndex = map.dificulty;
            switch(map.objectiveCom)
            {
                case 0: objectiveButton.Text = "Objective: Kill";break;
                case 1: objectiveButton.Text = "Objective: Build"; break;
                case 2: objectiveButton.Text = "Objective: Recuit"; break;
                case 3: objectiveButton.Text = "Objective: Conquer"; break;
                case 4: objectiveButton.Text = "Objective: Keep"; break;
            }
            
            map.Select(map.iniy, map.inix);
            
            /*
               ReadLn(fichero, map.inix);
                  ReadLn(fichero, map.iniy);
                  ReadLn(fichero, map.inigold);
                  ReadLn(fichero, map.daytime);
                  ReadLn(fichero, map.dificulty);
                  for i:= 0 to 4 do
                     for j:=0 to 9 do begin
                        ReadLn(fichero, map.areas[i,j].construccion);
                        ReadLn(fichero, map.areas[i,j].unidentro);
                        ReadLn(fichero, map.areas[i,j].unifuera);
                        ReadLn(fichero, map.areas[i,j].unienemigo);
                        ReadLn(fichero, map.areas[i,j].people);
                        ReadLn(fichero, map.areas[i,j].raceowner);
                        ReadLn(fichero, map.areas[i,j].racestriker);
                        ReadLn(fichero, map.areas[i,j].integrity);
                        ReadLn(fichero, map.areas[i,j].explored);
                        ReadLn(fichero, map.areas[i,j].evervisible);
                     end;
                  CloseFile(fichero);

                  // Init forms
                  ValueListEditor2.Values[ValueListEditor2.Keys[1]] := IntToStr(map.inigold);
                  ValueListEditor2.Values[ValueListEditor2.Keys[2]] := IntToStr(map.iniy);
                  ValueListEditor2.Values[ValueListEditor2.Keys[3]] := IntToStr(map.inix);
                  map.selx := map.inix;
                  map.sely := map.iniy;
            */

            //MessageBox.Show(reader.ReadLine(), reader.ReadLine());
            //reader.ReadLine();

            file.Close();
        }

        public void SaveMap(String filename)
        {
            System.IO.FileStream file;
            System.IO.StreamWriter writer;

            file = System.IO.File.Open(filename, System.IO.FileMode.Create, System.IO.FileAccess.Write);
            
            writer = new System.IO.StreamWriter(file);
            writer.AutoFlush = true;

            writer.WriteLine(map.inix);
            writer.WriteLine(map.iniy);
            writer.WriteLine(map.inigold);
            writer.WriteLine(map.cpugold);
            writer.WriteLine(map.daytime);
            writer.WriteLine(map.dificulty);

            writer.WriteLine(map.objectiveCom);
            writer.WriteLine(map.objectivePar1);
            writer.WriteLine(map.objectivePar2);
            writer.WriteLine(map.objectiveEndsMission);

            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 10; j++)
                {
                    //writer.WriteLine(i+", "+j+".........");
                    writer.WriteLine(map.areas[i, j].construccion);
                    writer.WriteLine(map.areas[i, j].unidentro);
                    writer.WriteLine(map.areas[i, j].unifuera);
                    writer.WriteLine(map.areas[i, j].unienemigo);
                    writer.WriteLine(map.areas[i, j].people);
                    writer.WriteLine(map.areas[i, j].raceowner);

                    //if (map.areas[i, j].unienemigo > 0) 
                    writer.WriteLine(map.areas[i, j].racestriker);
                    //else WriteLn(fichero, 0);
                    writer.WriteLine(map.areas[i, j].integrity);
                    writer.WriteLine(map.areas[i, j].explored);
                    writer.WriteLine(map.areas[i, j].evervisible);
                }
            file.Flush();
                /* AssignFile(fichero, SaveDialog1.Filename);
          Rewrite(fichero);
          WriteLn(fichero, map.inix);
          WriteLn(fichero, map.iniy);
          WriteLn(fichero, map.inigold);
          WriteLn(fichero, map.daytime);
          WriteLn(fichero, map.dificulty);
          for i:= 0 to 4 do
             for j:=0 to 9 do begin
                WriteLn(fichero, map.areas[i,j].construccion);
                WriteLn(fichero, map.areas[i,j].unidentro);
                WriteLn(fichero, map.areas[i,j].unifuera);
                WriteLn(fichero, map.areas[i,j].unienemigo);
                WriteLn(fichero, map.areas[i,j].people);
                WriteLn(fichero, map.areas[i,j].raceowner);

                if map.areas[i,j].unienemigo > 0 then WriteLn(fichero, map.areas[i,j].racestriker)
                else WriteLn(fichero, 0);
                WriteLn(fichero, map.areas[i,j].integrity);
                WriteLn(fichero, map.areas[i,j].explored);
                WriteLn(fichero, map.areas[i,j].evervisible);
             end;
          CloseFile(fichero);
                */
                file.Close();
        }



        // OPEN
        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                LoadMap(openFileDialog1.FileName);
                RefreshAll();
            }
        }

        public void RefreshAll()
        {
            map.Refresh();
            Refresh();
        }

        private void groupBox2_Enter(object sender, EventArgs e)
        {

        }

        private void WCEditorMain_Load(object sender, EventArgs e)
        {

        }

        public static void SetImage(int i, int j, int k)
        {
            mySelf.pictures[i, j].Image = mySelf.imgMiniConstructions[k+1];
        }

        private void invalidButton_Click(object sender, EventArgs e)
        {
            map.Build(-1);
        }

        private void noneButton_Click(object sender, EventArgs e)
        {
            map.Build(0);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            map.Build(1);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            map.Build(2);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            map.Build(3);
        }

        private void button6_Click(object sender, EventArgs e)
        {
            map.Build(4);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            map.Build(5);
        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void comboBox3_SelectedIndexChanged(object sender, EventArgs e)
        {
            ComboBox cb;
            cb = (ComboBox)sender;
            map.ChangeRaceStriker(cb.SelectedIndex);
        }

        private void cbConstruction_SelectedIndexChanged(object sender, EventArgs e)
        {
            ComboBox cb;
            cb = (ComboBox)sender;
            map.Build(cb.SelectedIndex-1);
        }

        private void nUnitsOutside_ValueChanged(object sender, EventArgs e)
        {
            NumericUpDown nud;
            nud = (NumericUpDown)sender;
            map.ChangeUnitsOutside(Convert.ToInt32(nud.Value));
        }

        private void nIntegrity_ValueChanged(object sender, EventArgs e)
        {
            NumericUpDown nud;
            nud = (NumericUpDown)sender;
            map.ChangeIntegrity(Convert.ToInt32(nud.Value));
        }

        private void nUnitsInside_ValueChanged(object sender, EventArgs e)
        {
            NumericUpDown nud;
            nud = (NumericUpDown)sender;
            map.ChangeUnitsInside(Convert.ToInt32(nud.Value));
        }

        private void nUnitsEnemy_ValueChanged(object sender, EventArgs e)
        {
            NumericUpDown nud;
            nud = (NumericUpDown)sender;
            map.ChangeUnitsAttacking(Convert.ToInt32(nud.Value));
        }

        private void nPeople_ValueChanged(object sender, EventArgs e)
        {
            NumericUpDown nud;
            nud = (NumericUpDown)sender;
            map.ChangePeople(Convert.ToInt32(nud.Value));
        }

        private void cbRaceOwner_SelectedIndexChanged(object sender, EventArgs e)
        {
            ComboBox cb;
            cb = (ComboBox)sender;
            map.ChangeRaceOwner(cb.SelectedIndex);
        }

        private void checkExplored_CheckedChanged(object sender, EventArgs e)
        {
            CheckBox cb;
            cb = (CheckBox)sender;
            map.setExplored(cb.Checked);
        }

        private void checkPermanVisible_CheckedChanged(object sender, EventArgs e)
        {
            CheckBox cb;
            cb = (CheckBox)sender;
            map.setPermanVisible(cb.Checked);
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {/*
            object o = null;
            

            WebBrowser wb = new WebBrowser();
            wb.Document =  HtmlDocument;
            wb.Document.Window.Open(new Uri("http;//www.microsoft.com"), "displayWindow", "status=yes,width=200,height=400",false);
            wb.Show();
            //HtmlDocument hd = 
            //hd.OpenNew(false);*/
        }

        // SAVE
        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                SaveMap(saveFileDialog1.FileName);
                RefreshAll();
            }
        }

        private void objectiveButton_Click(object sender, EventArgs e)
        {
            objForm.ShowDialog();
        }

        private void nHumanGold_ValueChanged(object sender, EventArgs e)
        {
            NumericUpDown nud;
            nud = (NumericUpDown)sender;
            map.ChangeHumanGold(Convert.ToInt32(nud.Value));
        }

        private void nComputerGold_ValueChanged(object sender, EventArgs e)
        {
            NumericUpDown nud;
            nud = (NumericUpDown)sender;
            map.ChangeComputerGold(Convert.ToInt32(nud.Value));
        }

        private void button4_Click(object sender, EventArgs e)
        {
            map.inix = map.selx;
            map.iniy = map.sely;
            StartAreaButton.Text = map.inix + " , " + map.iniy;
        }

        private void cDaytime_SelectedIndexChanged(object sender, EventArgs e)
        {
            ComboBox cb;
            cb = (ComboBox)sender;
            map.daytime = cb.SelectedIndex;
        }

        private void cDificulty_SelectedIndexChanged(object sender, EventArgs e)
        {
            ComboBox cb;
            cb = (ComboBox)sender;
            map.dificulty = cb.SelectedIndex;
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (curFile == "")
            {
                if (saveFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    SaveMap(saveFileDialog1.FileName);
                    RefreshAll();
                }
            }
            else SaveMap(curFile);
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            map.Build(-1);
        }

        private void toolStripButton2_Click(object sender, EventArgs e)
        {
            map.Build(0);
        }

        private void toolStripButton5_Click(object sender, EventArgs e)
        {
            map.Build(3);
        }

        private void toolStripButton6_Click(object sender, EventArgs e)
        {
            map.Build(4);

        }

        private void toolStripButton3_Click(object sender, EventArgs e)
        {
            map.Build(1);
        }

        private void toolStripButton4_Click(object sender, EventArgs e)
        {
            map.Build(2);
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            map.Reset();
        }

        private void quitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            abtForm.ShowDialog();
        }

        private void toolStripButton7_Click(object sender, EventArgs e)
        {
            map.Build(5);
        }

      

        
    
        

        
        
    }
}