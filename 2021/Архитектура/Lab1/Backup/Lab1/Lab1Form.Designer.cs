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
            this.tbA = new System.Windows.Forms.TextBox();
            this.tbB = new System.Windows.Forms.TextBox();
            this.labelA = new System.Windows.Forms.Label();
            this.labelB = new System.Windows.Forms.Label();
            this.labelN = new System.Windows.Forms.Label();
            this.nudN = new System.Windows.Forms.NumericUpDown();
            this.labelResult = new System.Windows.Forms.Label();
            this.tbResult = new System.Windows.Forms.TextBox();
            this.bCalc = new System.Windows.Forms.Button();
            this.cbMethod = new System.Windows.Forms.ComboBox();
            this.labelMethod = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.nudN)).BeginInit();
            this.SuspendLayout();
            // 
            // tbA
            // 
            this.tbA.Location = new System.Drawing.Point(32, 9);
            this.tbA.Name = "tbA";
            this.tbA.Size = new System.Drawing.Size(100, 20);
            this.tbA.TabIndex = 0;
            // 
            // tbB
            // 
            this.tbB.Location = new System.Drawing.Point(32, 35);
            this.tbB.Name = "tbB";
            this.tbB.Size = new System.Drawing.Size(100, 20);
            this.tbB.TabIndex = 1;
            // 
            // labelA
            // 
            this.labelA.AutoSize = true;
            this.labelA.Location = new System.Drawing.Point(12, 12);
            this.labelA.Name = "labelA";
            this.labelA.Size = new System.Drawing.Size(14, 13);
            this.labelA.TabIndex = 3;
            this.labelA.Text = "A";
            // 
            // labelB
            // 
            this.labelB.AutoSize = true;
            this.labelB.Location = new System.Drawing.Point(12, 39);
            this.labelB.Name = "labelB";
            this.labelB.Size = new System.Drawing.Size(14, 13);
            this.labelB.TabIndex = 4;
            this.labelB.Text = "B";
            // 
            // labelN
            // 
            this.labelN.AutoSize = true;
            this.labelN.Location = new System.Drawing.Point(12, 64);
            this.labelN.Name = "labelN";
            this.labelN.Size = new System.Drawing.Size(15, 13);
            this.labelN.TabIndex = 5;
            this.labelN.Text = "N";
            // 
            // nudN
            // 
            this.nudN.Location = new System.Drawing.Point(32, 62);
            this.nudN.Maximum = new decimal(new int[] {
            1316134912,
            2328,
            0,
            0});
            this.nudN.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nudN.Name = "nudN";
            this.nudN.Size = new System.Drawing.Size(100, 20);
            this.nudN.TabIndex = 6;
            this.nudN.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            // 
            // labelResult
            // 
            this.labelResult.AutoSize = true;
            this.labelResult.Location = new System.Drawing.Point(154, 15);
            this.labelResult.Name = "labelResult";
            this.labelResult.Size = new System.Drawing.Size(37, 13);
            this.labelResult.TabIndex = 7;
            this.labelResult.Text = "Result";
            // 
            // tbResult
            // 
            this.tbResult.Location = new System.Drawing.Point(197, 12);
            this.tbResult.Name = "tbResult";
            this.tbResult.Size = new System.Drawing.Size(100, 20);
            this.tbResult.TabIndex = 8;
            // 
            // bCalc
            // 
            this.bCalc.Location = new System.Drawing.Point(157, 55);
            this.bCalc.Name = "bCalc";
            this.bCalc.Size = new System.Drawing.Size(140, 27);
            this.bCalc.TabIndex = 15;
            this.bCalc.Text = "Calculate";
            this.bCalc.UseVisualStyleBackColor = true;
            this.bCalc.Click += new System.EventHandler(this.bCalc_Click);
            // 
            // cbMethod
            // 
            this.cbMethod.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbMethod.FormattingEnabled = true;
            this.cbMethod.Items.AddRange(new object[] {
            "Trap",
            "Simpson"});
            this.cbMethod.Location = new System.Drawing.Point(61, 91);
            this.cbMethod.Name = "cbMethod";
            this.cbMethod.Size = new System.Drawing.Size(236, 21);
            this.cbMethod.TabIndex = 16;
            // 
            // labelMethod
            // 
            this.labelMethod.AutoSize = true;
            this.labelMethod.Location = new System.Drawing.Point(12, 94);
            this.labelMethod.Name = "labelMethod";
            this.labelMethod.Size = new System.Drawing.Size(43, 13);
            this.labelMethod.TabIndex = 17;
            this.labelMethod.Text = "Method";
            // 
            // Lab1Form
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(310, 123);
            this.Controls.Add(this.labelMethod);
            this.Controls.Add(this.cbMethod);
            this.Controls.Add(this.bCalc);
            this.Controls.Add(this.tbResult);
            this.Controls.Add(this.labelResult);
            this.Controls.Add(this.nudN);
            this.Controls.Add(this.labelN);
            this.Controls.Add(this.labelB);
            this.Controls.Add(this.labelA);
            this.Controls.Add(this.tbB);
            this.Controls.Add(this.tbA);
            this.Name = "Lab1Form";
            this.Text = "Kabanov Kirill 3-46";
            ((System.ComponentModel.ISupportInitialize)(this.nudN)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox tbA;
        private System.Windows.Forms.TextBox tbB;
        private System.Windows.Forms.Label labelA;
        private System.Windows.Forms.Label labelB;
        private System.Windows.Forms.Label labelN;
        private System.Windows.Forms.NumericUpDown nudN;
        private System.Windows.Forms.Label labelResult;
        private System.Windows.Forms.TextBox tbResult;
        private System.Windows.Forms.Button bCalc;
        private System.Windows.Forms.ComboBox cbMethod;
        private System.Windows.Forms.Label labelMethod;
    }
}

