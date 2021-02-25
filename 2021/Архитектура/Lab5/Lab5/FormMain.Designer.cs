namespace Lab5
{
    partial class FormMain
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
            this._bStop = new System.Windows.Forms.Button();
            this._bDownload = new System.Windows.Forms.Button();
            this._tbURL = new System.Windows.Forms.TextBox();
            this._lURL = new System.Windows.Forms.Label();
            this._pgbProgress = new System.Windows.Forms.ProgressBar();
            this._lProgress = new System.Windows.Forms.Label();
            this._lTime = new System.Windows.Forms.Label();
            this._lSpeed = new System.Windows.Forms.Label();
            this._sfd = new System.Windows.Forms.SaveFileDialog();
            this._fbd = new System.Windows.Forms.FolderBrowserDialog();
            this.SuspendLayout();
            // 
            // _bStop
            // 
            this._bStop.Location = new System.Drawing.Point(87, 129);
            this._bStop.Name = "_bStop";
            this._bStop.Size = new System.Drawing.Size(75, 23);
            this._bStop.TabIndex = 0;
            this._bStop.Text = "Stop";
            this._bStop.UseVisualStyleBackColor = true;
            this._bStop.Click += new System.EventHandler(this._bStop_Click);
            // 
            // _bDownload
            // 
            this._bDownload.Location = new System.Drawing.Point(6, 129);
            this._bDownload.Name = "_bDownload";
            this._bDownload.Size = new System.Drawing.Size(75, 23);
            this._bDownload.TabIndex = 1;
            this._bDownload.Text = "Download";
            this._bDownload.UseVisualStyleBackColor = true;
            this._bDownload.Click += new System.EventHandler(this._bDownload_Click);
            // 
            // _tbURL
            // 
            this._tbURL.Location = new System.Drawing.Point(38, 6);
            this._tbURL.Name = "_tbURL";
            this._tbURL.Size = new System.Drawing.Size(421, 20);
            this._tbURL.TabIndex = 2;
            this._tbURL.Text = "http://TestDownloader.k12/Test.zip";
            // 
            // _lURL
            // 
            this._lURL.AutoSize = true;
            this._lURL.Location = new System.Drawing.Point(3, 9);
            this._lURL.Name = "_lURL";
            this._lURL.Size = new System.Drawing.Size(29, 13);
            this._lURL.TabIndex = 3;
            this._lURL.Text = "URL";
            // 
            // _pgbProgress
            // 
            this._pgbProgress.Location = new System.Drawing.Point(6, 32);
            this._pgbProgress.Name = "_pgbProgress";
            this._pgbProgress.Size = new System.Drawing.Size(453, 23);
            this._pgbProgress.TabIndex = 4;
            // 
            // _lProgress
            // 
            this._lProgress.AutoSize = true;
            this._lProgress.Location = new System.Drawing.Point(3, 64);
            this._lProgress.Name = "_lProgress";
            this._lProgress.Size = new System.Drawing.Size(51, 13);
            this._lProgress.TabIndex = 5;
            this._lProgress.Text = "Progress:";
            // 
            // _lTime
            // 
            this._lTime.AutoSize = true;
            this._lTime.Location = new System.Drawing.Point(3, 86);
            this._lTime.Name = "_lTime";
            this._lTime.Size = new System.Drawing.Size(33, 13);
            this._lTime.TabIndex = 6;
            this._lTime.Text = "Time:";
            // 
            // _lSpeed
            // 
            this._lSpeed.AutoSize = true;
            this._lSpeed.Location = new System.Drawing.Point(3, 108);
            this._lSpeed.Name = "_lSpeed";
            this._lSpeed.Size = new System.Drawing.Size(41, 13);
            this._lSpeed.TabIndex = 7;
            this._lSpeed.Text = "Speed:";
            // 
            // _sfd
            // 
            this._sfd.Filter = "ZIP files|*.zip|All files|*.*";
            this._sfd.InitialDirectory = "E:\\";
            this._sfd.Title = "Save directory";
            // 
            // _fbd
            // 
            this._fbd.Description = "Unpack folder";
            this._fbd.RootFolder = System.Environment.SpecialFolder.MyComputer;
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(471, 157);
            this.Controls.Add(this._lSpeed);
            this.Controls.Add(this._lTime);
            this.Controls.Add(this._lProgress);
            this.Controls.Add(this._pgbProgress);
            this.Controls.Add(this._lURL);
            this.Controls.Add(this._tbURL);
            this.Controls.Add(this._bDownload);
            this.Controls.Add(this._bStop);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "FormMain";
            this.ShowIcon = false;
            this.Text = "Kabanov Kirill 3-46";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button _bStop;
        private System.Windows.Forms.Button _bDownload;
        private System.Windows.Forms.TextBox _tbURL;
        private System.Windows.Forms.Label _lURL;
        private System.Windows.Forms.ProgressBar _pgbProgress;
        private System.Windows.Forms.Label _lProgress;
        private System.Windows.Forms.Label _lTime;
        private System.Windows.Forms.Label _lSpeed;
        private System.Windows.Forms.SaveFileDialog _sfd;
        private System.Windows.Forms.FolderBrowserDialog _fbd;
    }
}

