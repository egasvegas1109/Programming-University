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
        public long N { get; set; }
        public Func<double, double> F { get; set; }

        public Integral(double a, double b, long n, Func<double, double> f)
        {
            A = a;
            B = b;
            N = n;
            F = f;
        }

        public override bool Equals(object obj)
        {
            if (obj == null || GetType() != obj.GetType())
                return false;

            Integral I = (Integral)obj;

            if ((!A.Equals(I.A)) || (!B.Equals(I.B)) || (!N.Equals(I.N)))
                return false;

            return true;
        }

        public abstract double Calculate();
        public abstract double Calculate(int thr);
    }
}
