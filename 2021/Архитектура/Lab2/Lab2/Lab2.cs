using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using MatrixLib;

namespace Lab2
{
    public partial class Lab2 : Form
    {
        Matrix<double> matrix1 = new Matrix<double>();
        Matrix<double> matrix2 = new Matrix<double>();
        Matrix<double> matrixRes = new Matrix<double>();
        
        public Lab2()
        {
            InitializeComponent();

            _dgwTable1.RowCount = 1;
            _dgwTable1.ColumnCount = 1;

            _dgwTable2.RowCount = 1;
            _dgwTable2.ColumnCount = 1;

            _dgwResult.RowCount = 1;
            _dgwResult.ColumnCount = 1;
        }

        private void nudM1_ValueChanged(object sender, EventArgs e)
        {
            int size = Convert.ToInt32(_nudM1.Value);

            matrix1.ChangeSize(size);
            matrix2.ChangeSize(size);
            matrixRes.ChangeSize(size);

            _dgwTable1.RowCount = size;
            _dgwTable1.ColumnCount = size;

            _dgwTable2.RowCount = size;
            _dgwTable2.ColumnCount = size;

            _dgwResult.RowCount = size;
            _dgwResult.ColumnCount = size;
        }

        private void _bCalculate_Click(object sender, EventArgs e)
        {
            int size = Convert.ToInt32(_nudM1.Value);
            
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                {
                    matrix1[i, j] = Convert.ToDouble(_dgwTable1.Rows[i].Cells[j].Value);
                    matrix2[i, j] = Convert.ToDouble(_dgwTable2.Rows[i].Cells[j].Value);
                }

            Stopwatch stopWatch = new Stopwatch();
            stopWatch.Start();

            switch (_cbOperation.SelectedIndex)
            {
                case 0:
                {
                    matrixRes = matrix1 + matrix2;
                    break;
                }
                case 1:
                {
                    matrixRes = matrix1 * matrix2;
                    break;
                }
            }

            stopWatch.Stop();

            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    _dgwResult.Rows[i].Cells[j].Value = matrixRes[i, j];

            _tcTables.SelectedIndex = 2;
            _tbTime.Text = stopWatch.Elapsed.TotalSeconds.ToString() + " s";
        }

        private double func(int i, int j)
        {
            Random rand = new Random();
            return i + 10.56f * j + j * 1.45f - 3 + rand.Next(-15, 15);
        }

        private void _bRand1_Click(object sender, EventArgs e)
        {
            int size = Convert.ToInt32(_nudM1.Value);
            
            //matrix1.GenerateMatrix(func);
            matrix1.GenerateMatrix((i, j) =>
                {
                  return 1;
                }
            );
            
            for(int i=0; i<size; i++)
                for(int j=0; j<size; j++)
                    _dgwTable1.Rows[i].Cells[j].Value = matrix1[i, j];
        }

        private void _bRand2_Click(object sender, EventArgs e)
        {
            int size = Convert.ToInt32(_nudM1.Value);

            //matrix2.GenerateMatrix(func);
            matrix2.GenerateMatrix((i, j) =>
            {
                return 2;
            }
            );

            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    _dgwTable2.Rows[i].Cells[j].Value = matrix2[i, j];
        }

        private void _bSave_Click(object sender, EventArgs e)
        {
            sfd.ShowDialog();

            if (!String.IsNullOrEmpty(sfd.FileName))
            {
                int size = Convert.ToInt32(_nudM1.Value);
                
                using (System.IO.StreamWriter file = new System.IO.StreamWriter(sfd.FileName))
                {
                    for (int i = 0; i < size; i++)
                    {
                        for (int j = 0; j < size; j++)
                        {
                            file.Write(_dgwResult.Rows[i].Cells[j].Value.ToString());
                            if (j < size - 1) file.Write(";");
                        }

                        file.Write("\n");
                    }
                }
            }
        }

        private void _chbParallel_CheckedChanged(object sender, EventArgs e)
        {
            Matrix<double>.parallel = _chbParallel.Checked;
        }
    }
}
