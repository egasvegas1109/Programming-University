using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1
{
    class Trap : Integral
    {
        public Trap(double a, double b, long n, Func<double, double> f)
            : base(a, b, n, f)
        {

        }

        public override string ToString()
        {
            return "Метод Трапеций, A = " + A.ToString() + " B = " + B.ToString() + " N = " + N.ToString();
        }

        public override double Calculate()
        {
            double I = (F(A) + F(B)) / 2.0, h = (B - A) / N;

            for (int i = 1; i < N; i++)
            {
                I += F(A + i * h);
            }

            I *= h;

            return I;
        }

        private double Calculate(double a, double b)
        {
            double I = (F(a) + F(b)) / 2.0, h = (b - a) / N;

            for (int i = 1; i < N; i++)
            {
                I += F(a + i * h);
            }

            I *= h;

            return I;
        }

        public override double Calculate(int thr)
        {
            if (thr.Equals(1)) return Calculate();

            double thrH = (B-A)/thr;
            double I = 0.0;

            Task<double>[] tasks = new Task<double>[thr];
            for (int i = 0; i < thr; i++)
            {
                int myID = i;
                
                tasks[i] = new Task<double>(() =>
                {
                    double myA = A + thrH*myID;
                    double myB = A + thrH*(myID+1);

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
