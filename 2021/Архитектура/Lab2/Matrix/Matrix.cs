using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MatrixLib
{
    public class Matrix<T>
    {
        public int M { get; private set; }
        private T[,] Mat;
        public static bool parallel;

        public Matrix()
        {
            M = 1;
            Mat = new T[M, M];
        }

        public Matrix(int m)
        {
            M = m;
            Mat = new T[M, M];
        }

        public T this[int i, int j]
        {
            set
            {
                Mat[i, j] = value;
            }

            get
            {
                return Mat[i, j];
            }
        }

        public static Matrix<T> operator +(Matrix<T> m1, Matrix<T> m2)
        {
            Matrix<T> m = new Matrix<T>(m1.M);
            
            if(m1.M == m2.M)
            {
                if (parallel)
                {
                    for (int i = 0; i < m1.M; i++)
                        Parallel.For(0, m1.M, j =>
                        {
                            m[i, j] = (dynamic)m1[i, j] + (dynamic)m2[i, j];
                        });
                }
                else
                {
                    for (int i = 0; i < m1.M; i++)
                        for (int j = 0; j < m1.M; j++)
                            m[i, j] = (dynamic)m1[i, j] + (dynamic)m2[i, j];
                }
            }

            return m;
        }

        public static Matrix<T> operator *(Matrix<T> m1, Matrix<T> m2)
        {
            Matrix<T> m = new Matrix<T>(m1.M);

            if (m1.M == m2.M)
            {
                if (parallel)
                {
                    for (int i = 0; i < m1.M; i++)
                    {
                        Parallel.For(0, m1.M, j =>
                        {
                            for (int k = 0; k < m1.M; k++)
                            {
                                m[i, j] += (dynamic)m1[i, k] * (dynamic)m2[k, j];
                            }
                        });
                    }
                }
                else
                {
                    for (int i = 0; i < m1.M; i++)
                    {
                        for (int j = 0; j < m1.M; j++)
                        {
                            for (int k = 0; k < m1.M; k++)
                            {
                                m[i, j] += (dynamic)m1[i, k] * (dynamic)m2[k, j];
                            }
                        }
                    }
                }
            }

            return m;
        }

        public void ChangeSize(int size)
        {
            M = size;

            Mat = new T[M, M];
        }

        public void GenerateMatrix(Func<int, int, T> f)
        {
            for (int i = 0; i < M; i++)
                for (int j = 0; j < M; j++)
                    this[i, j] = f(i, j);
        }
    }
}
