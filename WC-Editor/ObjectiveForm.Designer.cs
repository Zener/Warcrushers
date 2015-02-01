namespace WC_Editor
{
    partial class ObjectiveForm
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
            this.cbObjective = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.cbEndMission = new System.Windows.Forms.CheckBox();
            this.BuildBox = new System.Windows.Forms.GroupBox();
            this.nBuild2 = new System.Windows.Forms.ComboBox();
            this.nBuild1 = new System.Windows.Forms.NumericUpDown();
            this.RecuitBox = new System.Windows.Forms.GroupBox();
            this.nRecruit1 = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.ConquerBox = new System.Windows.Forms.GroupBox();
            this.nConquer2 = new System.Windows.Forms.NumericUpDown();
            this.nConquer1 = new System.Windows.Forms.NumericUpDown();
            this.DontLoseBox = new System.Windows.Forms.GroupBox();
            this.nLose2 = new System.Windows.Forms.NumericUpDown();
            this.nLose1 = new System.Windows.Forms.NumericUpDown();
            this.button1 = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.BuildBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nBuild1)).BeginInit();
            this.RecuitBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nRecruit1)).BeginInit();
            this.ConquerBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nConquer2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nConquer1)).BeginInit();
            this.DontLoseBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nLose2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nLose1)).BeginInit();
            this.SuspendLayout();
            // 
            // cbObjective
            // 
            this.cbObjective.DisplayMember = "0";
            this.cbObjective.FormattingEnabled = true;
            this.cbObjective.Items.AddRange(new object[] {
            "Kill All Enemy",
            "Build at least",
            "Recruit at least",
            "Conquer cell map",
            "Don\'t lose cell map"});
            this.cbObjective.Location = new System.Drawing.Point(6, 46);
            this.cbObjective.Name = "cbObjective";
            this.cbObjective.Size = new System.Drawing.Size(329, 21);
            this.cbObjective.TabIndex = 0;
            this.cbObjective.SelectedIndexChanged += new System.EventHandler(this.cbObjective_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 30);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(52, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Objective";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.cbEndMission);
            this.groupBox1.Controls.Add(this.cbObjective);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(341, 88);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Main Objective";
            // 
            // cbEndMission
            // 
            this.cbEndMission.AutoSize = true;
            this.cbEndMission.CheckAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.cbEndMission.Location = new System.Drawing.Point(241, 19);
            this.cbEndMission.Name = "cbEndMission";
            this.cbEndMission.Size = new System.Drawing.Size(94, 17);
            this.cbEndMission.TabIndex = 8;
            this.cbEndMission.Text = "Ends Mission?";
            this.cbEndMission.UseVisualStyleBackColor = true;
            // 
            // BuildBox
            // 
            this.BuildBox.Controls.Add(this.nBuild2);
            this.BuildBox.Controls.Add(this.nBuild1);
            this.BuildBox.Enabled = false;
            this.BuildBox.Location = new System.Drawing.Point(12, 106);
            this.BuildBox.Name = "BuildBox";
            this.BuildBox.Size = new System.Drawing.Size(341, 48);
            this.BuildBox.TabIndex = 3;
            this.BuildBox.TabStop = false;
            this.BuildBox.Text = "Build";
            // 
            // nBuild2
            // 
            this.nBuild2.FormattingEnabled = true;
            this.nBuild2.Items.AddRange(new object[] {
            "CAMP/S",
            "FOTRESS/ES",
            "CASTLE/S"});
            this.nBuild2.Location = new System.Drawing.Point(182, 18);
            this.nBuild2.Name = "nBuild2";
            this.nBuild2.Size = new System.Drawing.Size(121, 21);
            this.nBuild2.TabIndex = 1;
            // 
            // nBuild1
            // 
            this.nBuild1.Location = new System.Drawing.Point(9, 19);
            this.nBuild1.Name = "nBuild1";
            this.nBuild1.Size = new System.Drawing.Size(120, 20);
            this.nBuild1.TabIndex = 0;
            // 
            // RecuitBox
            // 
            this.RecuitBox.Controls.Add(this.nRecruit1);
            this.RecuitBox.Controls.Add(this.label2);
            this.RecuitBox.Enabled = false;
            this.RecuitBox.Location = new System.Drawing.Point(12, 160);
            this.RecuitBox.Name = "RecuitBox";
            this.RecuitBox.Size = new System.Drawing.Size(341, 54);
            this.RecuitBox.TabIndex = 4;
            this.RecuitBox.TabStop = false;
            this.RecuitBox.Text = "Recruit";
            // 
            // nRecruit1
            // 
            this.nRecruit1.Location = new System.Drawing.Point(9, 20);
            this.nRecruit1.Maximum = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this.nRecruit1.Name = "nRecruit1";
            this.nRecruit1.Size = new System.Drawing.Size(120, 20);
            this.nRecruit1.TabIndex = 1;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(135, 22);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(42, 13);
            this.label2.TabIndex = 0;
            this.label2.Text = "soldiers";
            // 
            // ConquerBox
            // 
            this.ConquerBox.Controls.Add(this.nConquer2);
            this.ConquerBox.Controls.Add(this.nConquer1);
            this.ConquerBox.Enabled = false;
            this.ConquerBox.Location = new System.Drawing.Point(12, 220);
            this.ConquerBox.Name = "ConquerBox";
            this.ConquerBox.Size = new System.Drawing.Size(341, 58);
            this.ConquerBox.TabIndex = 5;
            this.ConquerBox.TabStop = false;
            this.ConquerBox.Text = "Conquer";
            // 
            // nConquer2
            // 
            this.nConquer2.Location = new System.Drawing.Point(182, 19);
            this.nConquer2.Maximum = new decimal(new int[] {
            9,
            0,
            0,
            0});
            this.nConquer2.Name = "nConquer2";
            this.nConquer2.Size = new System.Drawing.Size(120, 20);
            this.nConquer2.TabIndex = 2;
            this.nConquer2.ValueChanged += new System.EventHandler(this.nConquer2_ValueChanged);
            // 
            // nConquer1
            // 
            this.nConquer1.Location = new System.Drawing.Point(9, 19);
            this.nConquer1.Maximum = new decimal(new int[] {
            4,
            0,
            0,
            0});
            this.nConquer1.Name = "nConquer1";
            this.nConquer1.Size = new System.Drawing.Size(120, 20);
            this.nConquer1.TabIndex = 1;
            // 
            // DontLoseBox
            // 
            this.DontLoseBox.Controls.Add(this.nLose2);
            this.DontLoseBox.Controls.Add(this.nLose1);
            this.DontLoseBox.Enabled = false;
            this.DontLoseBox.Location = new System.Drawing.Point(12, 284);
            this.DontLoseBox.Name = "DontLoseBox";
            this.DontLoseBox.Size = new System.Drawing.Size(341, 63);
            this.DontLoseBox.TabIndex = 6;
            this.DontLoseBox.TabStop = false;
            this.DontLoseBox.Text = "Don\'t lose";
            // 
            // nLose2
            // 
            this.nLose2.Location = new System.Drawing.Point(182, 19);
            this.nLose2.Maximum = new decimal(new int[] {
            9,
            0,
            0,
            0});
            this.nLose2.Name = "nLose2";
            this.nLose2.Size = new System.Drawing.Size(120, 20);
            this.nLose2.TabIndex = 4;
            // 
            // nLose1
            // 
            this.nLose1.Location = new System.Drawing.Point(9, 19);
            this.nLose1.Maximum = new decimal(new int[] {
            4,
            0,
            0,
            0});
            this.nLose1.Name = "nLose1";
            this.nLose1.Size = new System.Drawing.Size(120, 20);
            this.nLose1.TabIndex = 3;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(278, 363);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 7;
            this.button1.Text = "Ok";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // ObjectiveForm
            // 
            this.AcceptButton = this.button1;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(368, 398);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.DontLoseBox);
            this.Controls.Add(this.ConquerBox);
            this.Controls.Add(this.RecuitBox);
            this.Controls.Add(this.BuildBox);
            this.Controls.Add(this.groupBox1);
            this.Name = "ObjectiveForm";
            this.ShowInTaskbar = false;
            this.Text = "ObjectiveForm";
            this.Shown += new System.EventHandler(this.ObjectiveForm_Enter);
            this.Enter += new System.EventHandler(this.ObjectiveForm_Enter);
            this.Activated += new System.EventHandler(this.ObjectiveForm_Enter);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.BuildBox.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.nBuild1)).EndInit();
            this.RecuitBox.ResumeLayout(false);
            this.RecuitBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nRecruit1)).EndInit();
            this.ConquerBox.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.nConquer2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nConquer1)).EndInit();
            this.DontLoseBox.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.nLose2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nLose1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ComboBox cbObjective;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox BuildBox;
        private System.Windows.Forms.GroupBox RecuitBox;
        private System.Windows.Forms.ComboBox nBuild2;
        private System.Windows.Forms.NumericUpDown nBuild1;
        private System.Windows.Forms.NumericUpDown nRecruit1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox ConquerBox;
        private System.Windows.Forms.GroupBox DontLoseBox;
        private System.Windows.Forms.NumericUpDown nConquer2;
        private System.Windows.Forms.NumericUpDown nConquer1;
        private System.Windows.Forms.NumericUpDown nLose2;
        private System.Windows.Forms.NumericUpDown nLose1;
        private System.Windows.Forms.Button button1;
        public System.Windows.Forms.CheckBox cbEndMission;
    }
}