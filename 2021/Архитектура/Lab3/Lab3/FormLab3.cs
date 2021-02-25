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

namespace Lab3
{
    public partial class FormLab3 : Form
    {
        public FormLab3()
        {
            InitializeComponent();
        }

        public void Lab()
        {
            const int k = 10;
            
            long N = Convert.ToInt64(_nudN.Value);
            Random rand = new Random();
            int[] m = new int[N];
            Stopwatch stopWatch = new Stopwatch();

            for (int i = 0; i < N; i++)
            {
                m[i] = rand.Next();
            }

            _tbOut.Text = "";

            //LINQ четные
            stopWatch.Start();
                int[] evenNumbers = m.Where(x => x % 2 == 0).ToArray();
                int[] firstTenEN = evenNumbers.Take(k).OrderBy(x => x).ToArray();
            stopWatch.Stop();
            _tbOut.Text += "Even numbers:\r\n LINQ:\r\n   count: " + evenNumbers.Count().ToString() + "   time: " + stopWatch.Elapsed.TotalSeconds.ToString() + "s\r\nFirst ten:\r\n";

            for (int i = 0; i < k; i++)
            {
                _tbOut.Text += " " + firstTenEN[i].ToString() + "\r\n";
            }

            //PLINQ четные
            stopWatch.Restart();
                int[] evenNumbersP = m.AsParallel().Where(x => x % 2 == 0).ToArray();
                int[] firstTenENP = evenNumbersP.Take(k).OrderBy(x => x).ToArray();
            stopWatch.Stop();
            _tbOut.Text += "\r\n PLINQ:\r\n   count: " + evenNumbersP.Count().ToString() + "   time: " + stopWatch.Elapsed.TotalSeconds.ToString() + "s\r\nFirst ten:\r\n";
            
            for (int i = 0; i < k; i++)
            {
                _tbOut.Text += " " + firstTenENP[i].ToString() + "\r\n";
            }
            _tbOut.Text += "\r\n";

            //LINQ нечетные
            stopWatch.Restart();
                int[] oddNumbers = m.Where(x => x % 2 != 0).ToArray();
                int[] firstTenON = oddNumbers.Take(k).OrderBy(x => x).ToArray();
            stopWatch.Stop();
            _tbOut.Text += "Odd numbers:\r\n LINQ:\r\n   count: " + oddNumbers.Count().ToString() + "   time: " + stopWatch.Elapsed.TotalSeconds.ToString() + "s\r\nFirst ten:\r\n";

            for (int i = 0; i < k; i++)
            {
                _tbOut.Text += " " + firstTenON[i].ToString() + "\r\n";
            }

            //PLINQ нечетные
            stopWatch.Restart();
                int[] oddNumbersP = m.AsParallel().Where(x => x % 2 != 0).ToArray();
                int[] firstTenONP = oddNumbersP.Take(k).OrderBy(x => x).ToArray();
            stopWatch.Stop();
            _tbOut.Text += "\r\n PLINQ:\r\n   count: " + oddNumbersP.Count().ToString() + "   time: " + stopWatch.Elapsed.TotalSeconds.ToString() + "s\r\nFirst ten:\r\n";

            for (int i = 0; i < k; i++)
            {
                _tbOut.Text += " " + firstTenONP[i].ToString() + "\r\n";
            }
            _tbOut.Text += "\r\n";

            //LINQ сумма первой и последней цифры равна 6
            stopWatch.Restart();
                int[] sixNumbers = m.Where(x =>
                {
                    string str = x.ToString();
                    int firstNum = Convert.ToInt32(str.First().ToString());
                    int lastNum = Convert.ToInt32(str.Last().ToString());

                    return (firstNum + lastNum == 6);
                }).ToArray();
                int[] firstTenSN = sixNumbers.Take(k).OrderBy(x => x).ToArray();
            stopWatch.Stop();
            _tbOut.Text += "First and last num sum is six:\r\n LINQ:\r\n   count: " + sixNumbers.Count().ToString() + "   time: " + stopWatch.Elapsed.TotalSeconds.ToString() + "s\r\nFirst ten:\r\n";

            for (int i = 0; i < k; i++)
            {
                _tbOut.Text += " " + firstTenSN[i].ToString() + "\r\n";
            }

            //PLINQ сумма первой и последней цифры равна 6
            stopWatch.Restart();
                int[] sixNumbersP = m.AsParallel().Where(x =>
                {
                    string str = x.ToString();
                    int firstNum = Convert.ToInt32(str.First().ToString());
                    int lastNum = Convert.ToInt32(str.Last().ToString());

                    return (firstNum + lastNum == 6);
                }).ToArray();
                int[] firstTenSNP = sixNumbersP.Take(k).OrderBy(x => x).ToArray();
            stopWatch.Stop();
            _tbOut.Text += "\r\n PLINQ:\r\n   count: " + sixNumbersP.Count().ToString() + "   time: " + stopWatch.Elapsed.TotalSeconds.ToString() + "s\r\nFirst ten:\r\n";

            for (int i = 0; i < k; i++)
            {
                _tbOut.Text += " " + firstTenSNP[i].ToString() + "\r\n";
            }
            _tbOut.Text += "\r\n";

            //LINQ содержит 666
            stopWatch.Restart();
                int[] tripleSixNumbers = m.Where(x => x.ToString().Contains("666")).ToArray();
                int[] firstTenTSN = tripleSixNumbers.Take(k).OrderBy(x => x).ToArray();
            stopWatch.Stop();
            _tbOut.Text += "Triple six:\r\n LINQ:\r\n   count: " + tripleSixNumbers.Count().ToString() + "   time: " + stopWatch.Elapsed.TotalSeconds.ToString() + "s\r\nFirst ten:\r\n";

            for (int i = 0; i < k; i++)
            {
                _tbOut.Text += " " + firstTenTSN[i].ToString() + "\r\n";
            }

            //PLINQ содержит 666
            stopWatch.Restart();
                int[] tripleSixNumbersP = m.AsParallel().Where(x => x.ToString().Contains("666")).ToArray();
                int[] firstTenTSNP = tripleSixNumbersP.Take(k).OrderBy(x => x).ToArray();
            stopWatch.Stop();
            _tbOut.Text += "\r\n PLINQ:\r\n   count: " + tripleSixNumbersP.Count().ToString() + "   time: " + stopWatch.Elapsed.TotalSeconds.ToString() + "s\r\nFirst ten:\r\n";

            for (int i = 0; i < k; i++)
            {
                _tbOut.Text += " " + firstTenTSNP[i].ToString() + "\r\n";
            }

            _tbOut.Text += "\r\n______________________________";
        }

        private void _bRun_Click(object sender, EventArgs e)
        {
            Lab();
        }
    }
}
