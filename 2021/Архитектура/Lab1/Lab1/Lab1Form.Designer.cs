namespace Lab1
{
    partial class Lab1Form
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
            this._tbA = new System.Windows.Forms.TextBox();
            this._tbB = new System.Windows.Forms.TextBox();
            this._lA = new System.Windows.Forms.Label();
            this._lB = new System.Windows.Forms.Label();
            this._lN = new System.Windows.Forms.Label();
            this._nudN = new System.Windows.Forms.NumericUpDown();
            this._lResult = new System.Windows.Forms.Label();
            this._tbResult = new System.Windows.Forms.TextBox();
            this._bCalc = new System.Windows.Forms.Button();
            this._cbMethod = new System.Windows.Forms.ComboBox();
            this._lMethod = new System.Windows.Forms.Label();
            this._nudThreads = new System.Windows.Forms.NumericUpDown();
            this._lThreads = new System.Windows.Forms.Label();
            this._tbTime = new System.Windows.Forms.TextBox();
            this._lTime = new System.Windows.Forms.Label();
            this._tbTest = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this._nudN)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this._nudThreads)).BeginInit();
            this.SuspendLayout();
            // 
            // _tbA
            // 
            this._tbA.Location = new System.Drawing.Point(32, 9);
            this._tbA.Name = "_tbA";
            this._tbA.Size = new System.Drawing.Size(100, 20);
            this._tbA.TabIndex = 0;
            this._tbA.Text = "1";
            // 
            // _tbB
            // 
            this._tbB.Location = new System.Drawing.Point(32, 35);
            this._tbB.Name = "_tbB";
            this._tbB.Size = new System.Drawing.Size(100, 20);
            this._tbB.TabIndex = 1;
            this._tbB.Text = "100000";
            // 
            // _lA
            // 
            this._lA.AutoSize = true;
            this._lA.Location = new System.Drawing.Point(12, 12);
            this._lA.Name = "_lA";
            this._lA.Size = new System.Drawing.Size(14, 13);
            this._lA.TabIndex = 3;
            this._lA.Text = "A";
            // 
            // _lB
            // 
            this._lB.AutoSize = true;
            this._lB.Location = new System.Drawing.Point(12, 39);
            this._lB.Name = "_lB";
            this._lB.Size = new System.Drawing.Size(14, 13);
            this._lB.TabIndex = 4;
            this._lB.Text = "B";
            // 
            // _lN
            // 
            this._lN.AutoSize = true;
            this._lN.Location = new System.Drawing.Point(146, 38);
            this._lN.Name = "_lN";
            this._lN.Size = new System.Drawing.Size(51, 13);
            this._lN.TabIndex = 5;
            this._lN.Text = "N(per thr)";
            // 
            // _nudN
            // 
            this._nudN.Location = new System.Drawing.Point(197, 37);
            this._nudN.Maximum = new decimal(new int[] {
            1316134912,
            2328,
            0,
            0});
            this._nudN.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this._nudN.Name = "_nudN";
            this._nudN.Size = new System.Drawing.Size(100, 20);
            this._nudN.TabIndex = 6;
            this._nudN.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            // 
            // _lResult
            // 
            this._lResult.AutoSize = true;
            this._lResult.Location = new System.Drawing.Point(12, 128);
            this._lResult.Name = "_lResult";
            this._lResult.Size = new System.Drawing.Size(37, 13);
            this._lResult.TabIndex = 7;
            this._lResult.Text = "Result";
            // 
            // _tbResult
            // 
            this._tbResult.Location = new System.Drawing.Point(55, 125);
            this._tbResult.Name = "_tbResult";
            this._tbResult.ReadOnly = true;
            this._tbResult.Size = new System.Drawing.Size(100, 20);
            this._tbResult.TabIndex = 8;
            // 
            // _bCalc
            // 
            this._bCalc.Location = new System.Drawing.Point(15, 90);
            this._bCalc.Name = "_bCalc";
            this._bCalc.Size = new System.Drawing.Size(282, 29);
            this._bCalc.TabIndex = 15;
            this._bCalc.Text = "Calculate";
            this._bCalc.UseVisualStyleBackColor = true;
            this._bCalc.Click += new System.EventHandler(this.bCalc_Click);
            // 
            // _cbMethod
            // 
            this._cbMethod.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this._cbMethod.FormattingEnabled = true;
            this._cbMethod.Items.AddRange(new object[] {
            "Trap",
            "Simpson"});
            this._cbMethod.Location = new System.Drawing.Point(62, 63);
            this._cbMethod.Name = "_cbMethod";
            this._cbMethod.Size = new System.Drawing.Size(236, 21);
            this._cbMethod.TabIndex = 16;
            // 
            // _lMethod
            // 
            this._lMethod.AutoSize = true;
            this._lMethod.Location = new System.Drawing.Point(13, 66);
            this._lMethod.Name = "_lMethod";
            this._lMethod.Size = new System.Drawing.Size(43, 13);
            this._lMethod.TabIndex = 17;
            this._lMethod.Text = "Method";
            // 
            // _nudThreads
            // 
            this._nudThreads.Location = new System.Drawing.Point(197, 10);
            this._nudThreads.Maximum = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this._nudThreads.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this._nudThreads.Name = "_nudThreads";
            this._nudThreads.Size = new System.Drawing.Size(100, 20);
            this._nudThreads.TabIndex = 18;
            this._nudThreads.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // _lThreads
            // 
            this._lThreads.AutoSize = true;
            this._lThreads.Location = new System.Drawing.Point(145, 12);
            this._lThreads.Name = "_lThreads";
            this._lThreads.Size = new System.Drawing.Size(46, 13);
            this._lThreads.TabIndex = 19;
            this._lThreads.Text = "Threads";
            // 
            // _tbTime
            // 
            this._tbTime.Location = new System.Drawing.Point(197, 125);
            this._tbTime.Name = "_tbTime";
            this._tbTime.ReadOnly = true;
            this._tbTime.Size = new System.Drawing.Size(100, 20);
            this._tbTime.TabIndex = 21;
            // 
            // _lTime
            // 
            this._lTime.AutoSize = true;
            this._lTime.Location = new System.Drawing.Point(161, 128);
            this._lTime.Name = "_lTime";
            this._lTime.Size = new System.Drawing.Size(30, 13);
            this._lTime.TabIndex = 20;
            this._lTime.Text = "Time";
            // 
            // _tbTest
            // 
            this._tbTest.Location = new System.Drawing.Point(16, 151);
            this._tbTest.Name = "_tbTest";
            this._tbTest.Size = new System.Drawing.Size(100, 20);
            this._tbTest.TabIndex = 22;
            // 
            // Lab1Form
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(310, 183);
            this.Controls.Add(this._tbTest);
            this.Controls.Add(this._tbTime);
            this.Controls.Add(this._lTime);
            this.Controls.Add(this._lThreads);
            this.Controls.Add(this._nudThreads);
            this.Controls.Add(this._lMethod);
            this.Controls.Add(this._cbMethod);
            this.Controls.Add(this._bCalc);
            this.Controls.Add(this._tbResult);
            this.Controls.Add(this._lResult);
            this.Controls.Add(this._nudN);
            this.Controls.Add(this._lN);
            this.Controls.Add(this._lB);
            this.Controls.Add(this._lA);
            this.Controls.Add(this._tbB);
            this.Controls.Add(this._tbA);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Lab1Form";
            this.ShowIcon = false;
            this.Text = "Kabanov Kirill 3-46";
            ((System.ComponentModel.ISupportInitialize)(this._nudN)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this._nudThreads)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox _tbA;
        private System.Windows.Forms.TextBox _tbB;
        private System.Windows.Forms.Label _lA;
        private System.Windows.Forms.Label _lB;
        private System.Windows.Forms.Label _lN;
        private System.Windows.Forms.NumericUpDown _nudN;
        private System.Windows.Forms.Label _lResult;
        private System.Windows.Forms.TextBox _tbResult;
        private System.Windows.Forms.Button _bCalc;
        private System.Windows.Forms.ComboBox _cbMethod;
        private System.Windows.Forms.Label _lMethod;
        private System.Windows.Forms.NumericUpDown _nudThreads;
        private System.Windows.Forms.Label _lThreads;
        private System.Windows.Forms.TextBox _tbTime;
        private System.Windows.Forms.Label _lTime;
        private System.Windows.Forms.TextBox _tbTest;
    }
}

