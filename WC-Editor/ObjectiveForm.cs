using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace WC_Editor
{
    public partial class ObjectiveForm : Form
    {
        public ObjectiveForm()
        {
            InitializeComponent();
            Visible = false;
        }

        private void ObjectiveForm_Enter(object sender, EventArgs e)
        {
            cbObjective.SelectedIndex = WCEditorMain.mySelf.map.objectiveCom;
            
            switch (cbObjective.SelectedIndex)
            {
                case 0:
                    BuildBox.Enabled = false;
                    RecuitBox.Enabled = false;
                    ConquerBox.Enabled = false;
                    DontLoseBox.Enabled = false;
                    break;
                case 1:
                    BuildBox.Enabled = true;                    
                    RecuitBox.Enabled = false;
                    ConquerBox.Enabled = false;
                    DontLoseBox.Enabled = false;
                    nBuild1.Value = WCEditorMain.mySelf.map.objectivePar1;
                    nBuild2.SelectedIndex = WCEditorMain.mySelf.map.objectivePar2-1;
                    break;
                case 2:
                    BuildBox.Enabled = false;
                    RecuitBox.Enabled = true;
                    ConquerBox.Enabled = false;
                    DontLoseBox.Enabled = false;
                    nRecruit1.Value = WCEditorMain.mySelf.map.objectivePar1;
                    break;
                case 3:
                    BuildBox.Enabled = false;
                    RecuitBox.Enabled = false;
                    ConquerBox.Enabled = true;
                    DontLoseBox.Enabled = false;
                    nConquer1.Value = WCEditorMain.mySelf.map.objectivePar1;
                    nConquer2.Value = WCEditorMain.mySelf.map.objectivePar2;
                    break;
                case 4:
                    BuildBox.Enabled = false;
                    RecuitBox.Enabled = false;
                    ConquerBox.Enabled = false;
                    DontLoseBox.Enabled = true;
                    nLose1.Value = WCEditorMain.mySelf.map.objectivePar1;
                    nLose2.Value = WCEditorMain.mySelf.map.objectivePar2;
                    break;
            }
        }

        private void cbObjective_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (cbObjective.SelectedIndex)
            {
                case 0:
                    BuildBox.Enabled = false;
                    RecuitBox.Enabled = false;
                    ConquerBox.Enabled = false;
                    DontLoseBox.Enabled = false;
                    break;
                case 1:
                    BuildBox.Enabled = true;
                    RecuitBox.Enabled = false;
                    ConquerBox.Enabled = false;
                    DontLoseBox.Enabled = false;
                    break;
                case 2:
                    BuildBox.Enabled = false;
                    RecuitBox.Enabled = true;
                    ConquerBox.Enabled = false;
                    DontLoseBox.Enabled = false;
                    break;
                case 3:
                    BuildBox.Enabled = false;
                    RecuitBox.Enabled = false;
                    ConquerBox.Enabled = true;
                    DontLoseBox.Enabled = false;
                    break;
                case 4:
                    BuildBox.Enabled = false;
                    RecuitBox.Enabled = false;
                    ConquerBox.Enabled = false;
                    DontLoseBox.Enabled = true;
                    break;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            WCEditorMain.mySelf.map.objectiveCom = cbObjective.SelectedIndex;
            WCEditorMain.mySelf.map.objectiveEndsMission = cbEndMission.Checked?1:0;

            switch (cbObjective.SelectedIndex)
            {
                case 0:
                    WCEditorMain.mySelf.map.objectivePar1 = 0;
                    WCEditorMain.mySelf.map.objectivePar2 = 0;
                    break;
                case 1:
                    WCEditorMain.mySelf.map.objectivePar1 = (int)nBuild1.Value;
                    WCEditorMain.mySelf.map.objectivePar2 = nBuild2.SelectedIndex+1;
                    break;
                case 2:
                    WCEditorMain.mySelf.map.objectivePar1 = (int)nRecruit1.Value;
                    WCEditorMain.mySelf.map.objectivePar2 = 0;
                    break;
                case 3:
                    WCEditorMain.mySelf.map.objectivePar1 = (int)nConquer1.Value;
                    WCEditorMain.mySelf.map.objectivePar2 = (int)nConquer2.Value;
                    break;
                case 4:
                    WCEditorMain.mySelf.map.objectivePar1 = (int)nLose1.Value;
                    WCEditorMain.mySelf.map.objectivePar2 = (int)nLose2.Value;
                    break;
            }

            switch (WCEditorMain.mySelf.map.objectiveCom)
            {
                case 0: WCEditorMain.mySelf.objectiveButton.Text = "Objective: Kill"; break;
                case 1: WCEditorMain.mySelf.objectiveButton.Text = "Objective: Build"; break;
                case 2: WCEditorMain.mySelf.objectiveButton.Text = "Objective: Recuit"; break;
                case 3: WCEditorMain.mySelf.objectiveButton.Text = "Objective: Conquer"; break;
                case 4: WCEditorMain.mySelf.objectiveButton.Text = "Objective: Keep"; break;
            }
            
            this.Close();
        }

        private void nConquer2_ValueChanged(object sender, EventArgs e)
        {

        }

       
    }
}