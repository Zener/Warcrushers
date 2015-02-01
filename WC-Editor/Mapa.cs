using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace WC_Editor
{
    public class Mapa
    {
        public Area [,]areas = new Area[5,10];
        public int inix, iniy;
        public int inigold;
        public int cpugold;
        public int selx, sely;
        public int daytime;
        public int dificulty;
        private Image groundImg;

        public int objectiveCom;
        public int objectivePar1;
        public int objectivePar2;
        public int objectiveEndsMission;

        public void Reset()
        {
            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 10; j++)
                {
                    areas[i, j].Reset();
                }
            Refresh();
        }

        
        public void Init()
        {
            groundImg = Image.FromFile("res\\ground00.bmp");

            selx = sely = -1;

            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 10; j++)
                    areas[i, j] = new Area();
            Reset();
            //Select(0, 0);
        }


        public void Refresh()
        {

            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 10; j++)
                {
                    WCEditorMain.SetImage(i, j, areas[i, j].construccion);
                }

            WCEditorMain.mySelf.nHumanGold.Value = inigold;
            WCEditorMain.mySelf.nComputerGold.Value = cpugold;
            WCEditorMain.mySelf.cDaytime.SelectedIndex = daytime;
            WCEditorMain.mySelf.cDificulty.SelectedIndex = dificulty;

            WCEditorMain.mySelf.StartAreaButton.Text = inix + " , " + iniy;
            WCEditorMain.mySelf.cDaytime.SelectedIndex = daytime;
            WCEditorMain.mySelf.cDificulty.SelectedIndex = dificulty;
            if (sely != -1) Select(sely, selx);            
        }


        public void DrawRect()
        {
        }


        public void Build(int i)
        {
            
            areas[sely, selx].construccion = i;
            if (i > 0) areas[sely, selx].integrity = 100;
            else areas[sely, selx].integrity = 0;
            Select(sely, selx);
            Refresh();
        }

        public void Select(int i, int j)
        {
            if (selx != -1)
            {
                WCEditorMain.mySelf.pictures[sely, selx].BorderStyle = System.Windows.Forms.BorderStyle.None;
                WCEditorMain.mySelf.pictures[sely, selx].SetBounds(WCEditorMain.mySelf.pictures[sely, selx].Bounds.X + 10,
                    WCEditorMain.mySelf.pictures[sely, selx].Bounds.Y + 8,
                    WCEditorMain.mySelf.pictures[sely, selx].Bounds.Width - 20,
                    WCEditorMain.mySelf.pictures[sely, selx].Bounds.Height - 16
                    );
       
            }
                WCEditorMain.mySelf.pictures[i, j].BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
                WCEditorMain.mySelf.pictures[i, j].SetBounds(WCEditorMain.mySelf.pictures[i, j].Bounds.X - 10,
                    WCEditorMain.mySelf.pictures[i, j].Bounds.Y - 8,
                    WCEditorMain.mySelf.pictures[i, j].Bounds.Width + 20,
                    WCEditorMain.mySelf.pictures[i, j].Bounds.Height + 16
                    );
                WCEditorMain.mySelf.pictures[i, j].BringToFront();
            
            selx = j; sely = i;

            WCEditorMain.mySelf.cbConstruction.SelectedIndex = areas[sely, selx].construccion + 1;
            WCEditorMain.mySelf.nIntegrity.Value = areas[sely, selx].integrity;
            WCEditorMain.mySelf.nPeople.Value = areas[sely, selx].people;
            WCEditorMain.mySelf.nUnitsEnemy.Value = areas[sely, selx].unienemigo;
            WCEditorMain.mySelf.nUnitsInside.Value = areas[sely, selx].unidentro;
            WCEditorMain.mySelf.nUnitsOutside.Value = areas[sely, selx].unifuera;
            WCEditorMain.mySelf.cbRaceOwner.SelectedIndex = areas[sely, selx].raceowner;
            WCEditorMain.mySelf.cbRaceStriker.SelectedIndex = areas[sely, selx].racestriker;
            WCEditorMain.mySelf.checkExplored.Checked = areas[sely, selx].explored == 1;
            WCEditorMain.mySelf.checkPermanVisible.Checked = areas[sely, selx].evervisible == 1;

            UpdateMainScreen(sely, selx);
        }

        public void UpdateMainScreen(int yactual, int xactual)
        {
            int i1, i2, i3, i4;
            i1 = 4 + xactual * 7 * yactual * 2 - (xactual - yactual) * 13;
            i2 = 2 + (yactual - xactual) * 13 - 10 * 3 + xactual * 17;
            i3 = 1 + i1 + xactual;
            i4 = 3 + i1 + i2;
            i1 = (i1+225) % 5;
            i2 = (i2+225) % 5;
            i3 = (i3+225) % 5;
            i4 = (i4+225) % 5;

            Graphics gr = WCEditorMain.mySelf.mainScreen.CreateGraphics();
            if (areas[yactual, xactual].construccion >= 0)
            {
                gr.DrawImage(groundImg, new Rectangle(0, 0, 320, 200), i1 * 320, 0, 320, 200, GraphicsUnit.Pixel);
                gr.DrawImage(groundImg, new Rectangle(320, 0, 320, 200), i2 * 320, 0, 320, 200, GraphicsUnit.Pixel);
                gr.DrawImage(groundImg, new Rectangle(0, 200, 320, 200), i3 * 320, 0, 320, 200, GraphicsUnit.Pixel);
                gr.DrawImage(groundImg, new Rectangle(320, 200, 320, 200), i4 * 320, 0, 320, 200, GraphicsUnit.Pixel);
            }
            else
                gr.FillRectangle(Brushes.DarkBlue, 0, 0, 640, 400);

            if (areas[yactual, xactual].construccion > 0)
                gr.DrawImage(WCEditorMain.mySelf.imgConstructions[areas[yactual, xactual].construccion-1],
                    new Rectangle(0, 0, 640, 180), 0, 0, 640, 180, GraphicsUnit.Pixel);
        }


        public void AreaOwner(int i)
        {
            
        }


        public void ChangeIntegrity(int val)
        {
            areas[sely, selx].integrity = val;
        }

        public void ChangeUnitsInside(int val)
        {
            areas[sely, selx].unidentro = val;
        }

        public void ChangeUnitsOutside(int val)
        {
            areas[sely, selx].unifuera = val;
        }

        public void ChangeUnitsAttacking(int val)
        {
            areas[sely, selx].unienemigo = val;
        }

        public void ChangePeople(int val)
        {
            areas[sely, selx].people = val;
        }

        public void ChangeRaceOwner(int val)
        {
            areas[sely, selx].raceowner = val;
        }

        public void ChangeRaceStriker(int val)
        {
            areas[sely, selx].racestriker = val;
        }

        public void setExplored(bool value)
        {
            areas[sely, selx].explored = value?1:0;
        }

        public void setPermanVisible(bool value)
        {
            areas[sely, selx].evervisible = value?1:0;
        }

        public void ChangeHumanGold(int val)
        {
            inigold = val;
        }

        public void ChangeComputerGold(int val)
        {
            cpugold = val;
        }
    }
}
