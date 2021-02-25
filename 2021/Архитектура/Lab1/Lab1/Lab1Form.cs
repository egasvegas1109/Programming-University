using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;

namespace Lab1
{
    public partial class Lab1Form : Form
    {
        public Lab1Form()
        {
            InitializeComponent();
            _cbMethod.SelectedIndex = 0;
        }

        private void bCalc_Click(object sender, EventArgs e)
        {
            Calculate();
        }

        private double f(double x)
        {
            //return 32*x-Math.Log(2*x)-41;
            //return 1 / (Math.Sqrt(9 + x * x));
            return x * x;
        }

        private Integral IntegralGetFromType(double a, double b, long n, Func<double, double> f)
        {
            switch (_cbMethod.SelectedIndex)
            {
                case 0: return new Trap(a, b, n, f);
                case 1: return new Simpson(a, b, n, f);
                default: return new Trap(a, b, n, f);
            }
        }

        private void Calculate()
        {
            double a = Convert.ToDouble(_tbA.Text);
            double b = Convert.ToDouble(_tbB.Text);
            long n = Convert.ToInt64(_nudN.Text);
            int thr = Convert.ToInt32(_nudThreads.Text);

            Stopwatch stopWatch = new Stopwatch();

            Integral integral = IntegralGetFromType(a, b, n, f);
            stopWatch.Start();
                _tbResult.Text = integral.Calculate(thr).ToString();
            stopWatch.Stop();

            _tbTime.Text = stopWatch.Elapsed.TotalSeconds.ToString() + " s";

            Integral integral1 = new Simpson(a, b, n, f);

            if (integral == integral1)
            {
                _tbTest.Text = integral.ToString();
            }
        }
    }
}
