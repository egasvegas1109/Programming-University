namespace Lab2
{
    partial class Lab2
    {
        /// <summary>
        /// Требуется переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Обязательный метод для поддержки конструктора - не изменяйте
        /// содержимое данного метода при помощи редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this._lM1 = new System.Windows.Forms.Label();
            this._tcTables = new System.Windows.Forms.TabControl();
            this._tpTable1 = new System.Windows.Forms.TabPage();
            this._bRand1 = new System.Windows.Forms.Button();
            this._dgwTable1 = new System.Windows.Forms.DataGridView();
            this._tpTable2 = new System.Windows.Forms.TabPage();
            this._bRand2 = new System.Windows.Forms.Button();
            this._dgwTable2 = new System.Windows.Forms.DataGridView();
            this._tpTable3 = new System.Windows.Forms.TabPage();
            this._bSave = new System.Windows.Forms.Button();
            this._dgwResult = new System.Windows.Forms.DataGridView();
            this._lTime = new System.Windows.Forms.Label();
            this._tbTime = new System.Windows.Forms.TextBox();
            this._bCalculate = new System.Windows.Forms.Button();
            this._cbOperation = new System.Windows.Forms.ComboBox();
            this._nudM1 = new System.Windows.Forms.NumericUpDown();
            this.sfd = new System.Windows.Forms.SaveFileDialog();
            this._chbParallel = new System.Windows.Forms.CheckBox();
            this._tcTables.SuspendLayout();
            this._tpTable1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this._dgwTable1)).BeginInit();
            this._tpTable2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this._dgwTable2)).BeginInit();
            this._tpTable3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this._dgwResult)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this._nudM1)).BeginInit();
            this.SuspendLayout();
            // 
            // _lM1
            // 
            this._lM1.AutoSize = true;
            this._lM1.Location = new System.Drawing.Point(8, 315);
            this._lM1.Name = "_lM1";
            this._lM1.Size = new System.Drawing.Size(15, 13);
            this._lM1.TabIndex = 1;
            this._lM1.Text = "m";
            // 
            // _tcTables
            // 
            this._tcTables.Controls.Add(this._tpTable1);
            this._tcTables.Controls.Add(this._tpTable2);
            this._tcTables.Controls.Add(this._tpTable3);
            this._tcTables.Location = new System.Drawing.Point(0, 0);
            this._tcTables.Name = "_tcTables";
            this._tcTables.SelectedIndex = 0;
            this._tcTables.Size = new System.Drawing.Size(544, 307);
            this._tcTables.TabIndex = 9;
            // 
            // _tpTable1
            // 
            this._tpTable1.Controls.Add(this._bRand1);
            this._tpTable1.Controls.Add(this._dgwTable1);
            this._tpTable1.Location = new System.Drawing.Point(4, 22);
            this._tpTable1.Name = "_tpTable1";
            this._tpTable1.Padding = new System.Windows.Forms.Padding(3);
            this._tpTable1.Size = new System.Drawing.Size(536, 281);
            this._tpTable1.TabIndex = 0;
            this._tpTable1.Text = "Matrix 1";
            this._tpTable1.UseVisualStyleBackColor = true;
            // 
            // _bRand1
            // 
            this._bRand1.Location = new System.Drawing.Point(6, 6);
            this._bRand1.Name = "_bRand1";
            this._bRand1.Size = new System.Drawing.Size(95, 25);
            this._bRand1.TabIndex = 11;
            this._bRand1.Text = "Random";
            this._bRand1.UseVisualStyleBackColor = true;
            this._bRand1.Click += new System.EventHandler(this._bRand1_Click);
            // 
            // _dgwTable1
            // 
            this._dgwTable1.AllowUserToOrderColumns = true;
            this._dgwTable1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this._dgwTable1.Location = new System.Drawing.Point(7, 34);
            this._dgwTable1.MinimumSize = new System.Drawing.Size(1, 1);
            this._dgwTable1.Name = "_dgwTable1";
            this._dgwTable1.Size = new System.Drawing.Size(523, 241);
            this._dgwTable1.TabIndex = 5;
            // 
            // _tpTable2
            // 
            this._tpTable2.Controls.Add(this._bRand2);
            this._tpTable2.Controls.Add(this._dgwTable2);
            this._tpTable2.Location = new System.Drawing.Point(4, 22);
            this._tpTable2.Name = "_tpTable2";
            this._tpTable2.Padding = new System.Windows.Forms.Padding(3);
            this._tpTable2.Size = new System.Drawing.Size(536, 281);
            this._tpTable2.TabIndex = 1;
            this._tpTable2.Text = "Matrix 2";
            this._tpTable2.UseVisualStyleBackColor = true;
            // 
            // _bRand2
            // 
            this._bRand2.Location = new System.Drawing.Point(6, 6);
            this._bRand2.Name = "_bRand2";
            this._bRand2.Size = new System.Drawing.Size(95, 25);
            this._bRand2.TabIndex = 12;
            this._bRand2.Text = "Random";
            this._bRand2.UseVisualStyleBackColor = true;
            this._bRand2.Click += new System.EventHandler(this._bRand2_Click);
            // 
            // _dgwTable2
            // 
            this._dgwTable2.AllowUserToOrderColumns = true;
            this._dgwTable2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this._dgwTable2.Location = new System.Drawing.Point(7, 34);
            this._dgwTable2.MinimumSize = new System.Drawing.Size(1, 1);
            this._dgwTable2.Name = "_dgwTable2";
            this._dgwTable2.Size = new System.Drawing.Size(523, 241);
            this._dgwTable2.TabIndex = 9;
            // 
            // _tpTable3
            // 
            this._tpTable3.Controls.Add(this._bSave);
            this._tpTable3.Controls.Add(this._dgwResult);
            this._tpTable3.Controls.Add(this._lTime);
            this._tpTable3.Controls.Add(this._tbTime);
            this._tpTable3.Location = new System.Drawing.Point(4, 22);
            this._tpTable3.Name = "_tpTable3";
            this._tpTable3.Size = new System.Drawing.Size(536, 281);
            this._tpTable3.TabIndex = 2;
            this._tpTable3.Text = "Result";
            this._tpTable3.UseVisualStyleBackColor = true;
            // 
            // _bSave
            // 
            this._bSave.Location = new System.Drawing.Point(435, 251);
            this._bSave.Name = "_bSave";
            this._bSave.Size = new System.Drawing.Size(95, 25);
            this._bSave.TabIndex = 16;
            this._bSave.Text = "Save";
            this._bSave.UseVisualStyleBackColor = true;
            this._bSave.Click += new System.EventHandler(this._bSave_Click);
            // 
            // _dgwResult
            // 
            this._dgwResult.AllowUserToOrderColumns = true;
            this._dgwResult.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this._dgwResult.Location = new System.Drawing.Point(7, 7);
            this._dgwResult.MinimumSize = new System.Drawing.Size(1, 1);
            this._dgwResult.Name = "_dgwResult";
            this._dgwResult.Size = new System.Drawing.Size(523, 238);
            this._dgwResult.TabIndex = 6;
            // 
            // _lTime
            // 
            this._lTime.AutoSize = true;
            this._lTime.Location = new System.Drawing.Point(8, 257);
            this._lTime.Name = "_lTime";
            this._lTime.Size = new System.Drawing.Size(30, 13);
            this._lTime.TabIndex = 15;
            this._lTime.Text = "Time";
            // 
            // _tbTime
            // 
            this._tbTime.Location = new System.Drawing.Point(44, 254);
            this._tbTime.Name = "_tbTime";
            this._tbTime.ReadOnly = true;
            this._tbTime.Size = new System.Drawing.Size(173, 20);
            this._tbTime.TabIndex = 14;
            // 
            // _bCalculate
            // 
            this._bCalculate.Location = new System.Drawing.Point(439, 309);
            this._bCalculate.Name = "_bCalculate";
            this._bCalculate.Size = new System.Drawing.Size(95, 25);
            this._bCalculate.TabIndex = 10;
            this._bCalculate.Text = "Calculate";
            this._bCalculate.UseVisualStyleBackColor = true;
            this._bCalculate.Click += new System.EventHandler(this._bCalculate_Click);
            // 
            // _cbOperation
            // 
            this._cbOperation.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this._cbOperation.FormattingEnabled = true;
            this._cbOperation.Items.AddRange(new object[] {
            "Sum",
            "Mul"});
            this._cbOperation.Location = new System.Drawing.Point(176, 312);
            this._cbOperation.Name = "_cbOperation";
            this._cbOperation.Size = new System.Drawing.Size(257, 21);
            this._cbOperation.TabIndex = 11;
            // 
            // _nudM1
            // 
            this._nudM1.Location = new System.Drawing.Point(28, 313);
            this._nudM1.Maximum = new decimal(new int[] {
            654,
            0,
            0,
            0});
            this._nudM1.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this._nudM1.Name = "_nudM1";
            this._nudM1.Size = new System.Drawing.Size(76, 20);
            this._nudM1.TabIndex = 2;
            this._nudM1.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this._nudM1.ValueChanged += new System.EventHandler(this.nudM1_ValueChanged);
            // 
            // sfd
            // 
            this.sfd.DefaultExt = "csv";
            this.sfd.Filter = "CSV table|*.csv";
            this.sfd.Title = "Save results";
            // 
            // _chbParallel
            // 
            this._chbParallel.AutoSize = true;
            this._chbParallel.Location = new System.Drawing.Point(110, 315);
            this._chbParallel.Name = "_chbParallel";
            this._chbParallel.Size = new System.Drawing.Size(60, 17);
            this._chbParallel.TabIndex = 13;
            this._chbParallel.Text = "Parallel";
            this._chbParallel.UseVisualStyleBackColor = true;
            this._chbParallel.CheckedChanged += new System.EventHandler(this._chbParallel_CheckedChanged);
            // 
            // Lab2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(540, 341);
            this.Controls.Add(this._chbParallel);
            this.Controls.Add(this._cbOperation);
            this.Controls.Add(this._bCalculate);
            this.Controls.Add(this._lM1);
            this.Controls.Add(this._tcTables);
            this.Controls.Add(this._nudM1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Lab2";
            this.ShowIcon = false;
            this.Text = "Kabanov Kirill 3-46";
            this._tcTables.ResumeLayout(false);
            this._tpTable1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this._dgwTable1)).EndInit();
            this._tpTable2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this._dgwTable2)).EndInit();
            this._tpTable3.ResumeLayout(false);
            this._tpTable3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this._dgwResult)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this._nudM1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label _lM1;
        private System.Windows.Forms.TabControl _tcTables;
        private System.Windows.Forms.TabPage _tpTable1;
        private System.Windows.Forms.TabPage _tpTable2;
        private System.Windows.Forms.DataGridView _dgwTable1;
        private System.Windows.Forms.DataGridView _dgwTable2;
        private System.Windows.Forms.TabPage _tpTable3;
        private System.Windows.Forms.DataGridView _dgwResult;
        private System.Windows.Forms.Button _bCalculate;
        private System.Windows.Forms.ComboBox _cbOperation;
        private System.Windows.Forms.Button _bRand1;
        private System.Windows.Forms.Button _bRand2;
        private System.Windows.Forms.NumericUpDown _nudM1;
        private System.Windows.Forms.Button _bSave;
        private System.Windows.Forms.Label _lTime;
        private System.Windows.Forms.TextBox _tbTime;
        private System.Windows.Forms.SaveFileDialog sfd;
        private System.Windows.Forms.CheckBox _chbParallel;
    }
}

