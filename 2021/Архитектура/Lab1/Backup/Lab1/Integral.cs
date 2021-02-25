using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Lab1
{
    public abstract class Integral
    {
        public double A { get; set; }
        public double B { get; set; }
        public double N { get; set; }
        public Func<double> F { get; set; }

        public Integral(double a, double b, int n, Func<double> f)
        {
            A = a;
            B = b;
            N = n;
            F = f;
        }

        public abstract double Calculate();
    }
}
