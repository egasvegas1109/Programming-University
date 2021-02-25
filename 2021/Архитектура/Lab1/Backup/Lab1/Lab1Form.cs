using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Lab1
{
    public partial class Lab1Form : Form
    {
        public Lab1Form()
        {
            InitializeComponent();
        }

        private void bCalc_Click(object sender, EventArgs e)
        {
            Calculate();
        }

        private double f(double x)
        {
            return 32*x-Math.Log(2*x)-41;
        }

        private Integral GetType()
        {
            switch()
        }

        private double Calculate()
        {
            double a = Convert.ToDouble(tbA.Text);
            double b = Convert.ToDouble(tbB.Text);
            int n = Convert.ToInt32(tbN.Text);
            
            Integral integral = new Integral(a, b, n, f);
            
        }
    }
}
