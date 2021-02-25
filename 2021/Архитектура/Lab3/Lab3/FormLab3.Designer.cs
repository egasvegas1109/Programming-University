namespace Lab3
{
    partial class FormLab3
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
            this._tbOut = new System.Windows.Forms.TextBox();
            this._bRun = new System.Windows.Forms.Button();
            this._lN = new System.Windows.Forms.Label();
            this._nudN = new System.Windows.Forms.NumericUpDown();
            ((System.ComponentModel.ISupportInitialize)(this._nudN)).BeginInit();
            this.SuspendLayout();
            // 
            // _tbOut
            // 
            this._tbOut.Location = new System.Drawing.Point(0, 0);
            this._tbOut.Multiline = true;
            this._tbOut.Name = "_tbOut";
            this._tbOut.ReadOnly = true;
            this._tbOut.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this._tbOut.Size = new System.Drawing.Size(518, 328);
            this._tbOut.TabIndex = 0;
            // 
            // _bRun
            // 
            this._bRun.Location = new System.Drawing.Point(408, 334);
            this._bRun.Name = "_bRun";
            this._bRun.Size = new System.Drawing.Size(98, 23);
            this._bRun.TabIndex = 1;
            this._bRun.Text = "Run";
            this._bRun.UseVisualStyleBackColor = true;
            this._bRun.Click += new System.EventHandler(this._bRun_Click);
            // 
            // _lN
            // 
            this._lN.AutoSize = true;
            this._lN.Location = new System.Drawing.Point(12, 339);
            this._lN.Name = "_lN";
            this._lN.Size = new System.Drawing.Size(15, 13);
            this._lN.TabIndex = 3;
            this._lN.Text = "N";
            // 
            // _nudN
            // 
            this._nudN.Location = new System.Drawing.Point(33, 337);
            this._nudN.Maximum = new decimal(new int[] {
            1000000000,
            0,
            0,
            0});
            this._nudN.Name = "_nudN";
            this._nudN.Size = new System.Drawing.Size(120, 20);
            this._nudN.TabIndex = 4;
            this._nudN.Value = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
            // 
            // FormLab3
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(518, 365);
            this.Controls.Add(this._nudN);
            this.Controls.Add(this._lN);
            this.Controls.Add(this._bRun);
            this.Controls.Add(this._tbOut);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormLab3";
            this.ShowIcon = false;
            this.Text = "Kabanov Kirill 3-46";
            ((System.ComponentModel.ISupportInitialize)(this._nudN)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox _tbOut;
        private System.Windows.Forms.Button _bRun;
        private System.Windows.Forms.Label _lN;
        private System.Windows.Forms.NumericUpDown _nudN;
    }
}

