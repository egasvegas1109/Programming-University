using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1
{
    class Simpson : Integral
    {
        public Simpson(double a, double b, long n, Func<double, double> f)
            : base(a, b, n, f)
        {

        }

        public override string ToString()
        {
            return "Метод Симпсона, A = " + A.ToString() + " B = " + B.ToString() + " N = " + N.ToString();
        }

        public override double Calculate()
        {
            double I = (F(B) - F(A)) / 2.0, h = (B - A) / N;

            for (int i = 0; i < N; i++)
            {
                I += F(A + i * h) + 2.0 * F(A + i * h + h / 2.0);
            }

            I *= h / 3;

            return I;
        }

        private double Calculate(double a, double b)
        {
            double I = (F(b) - F(a)) / 2.0, h = (b - a) / N;

            for (int i = 0; i < N; i++)
            {
                I += F(a + i * h) + 2.0 * F(a + i * h + h / 2.0);
            }

            I *= h / 3;

            return I;
        }

        public override double Calculate(int thr)
        {
            if (thr.Equals(1)) return Calculate();

            double thrH = (B - A) / thr;
            double I = 0.0;

            Task<double>[] tasks = new Task<double>[thr];
            for (int i = 0; i < thr; i++)
            {
                int myID = i;

                tasks[i] = new Task<double>(() =>
                {
                    double myA = A + thrH * myID;
                    double myB = A + thrH * (myID + 1);

                    return Calculate(myA, myB);
                });

                tasks[i].Start();
            }

            Task.WaitAll(tasks);

            for (int i = 0; i < thr; i++)
            {
                I += tasks[i].Result;
            }

            return I;
        }
    }
}
