using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using CalculateLibrary;
using OxyPlot;

namespace IntegralSolution
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void btCalculate_Click(object sender, RoutedEventArgs e)
        {
            Calculate();
            DrawGraph();
        }

        private void DrawGraph()
        {
            MainViewModel model = DataContext as MainViewModel;
            for (int i = 0; i < 10; i++)
            {
                DataPoint point = new DataPoint(2 * i, 2 * i);
                model.Points.Add(point);
            }
            graph.InvalidatePlot(true);
        }

        private void ClearGraph()
        {
            MainViewModel model = DataContext as MainViewModel;
            model.Points.Clear();
            graph.InvalidatePlot(true);
        }

        private void Calculate ()
        {
            double a = Convert.ToDouble(tbLowerBound.Text);
            double b = Convert.ToDouble(tbUpperBound.Text);
            long n = Convert.ToInt64(tbN.Text);

            ICalculator calculator = GetCalculator();
            double result = calculator.Calculate(a, b, n, x => x * x);
            tbResult.Text = Convert.ToString(result);
        }

        private ICalculator GetCalculator()
        {
            switch (cbmMethod.SelectedIndex)
            {
                case 0:return new RectangleCalculator();
                    break;
                case 1:
                    return new TrapCalculator();
                    break;
                default: return new RectangleCalculator();
                    break;
            }
        }

        private void btClear_Click(object sender, RoutedEventArgs e)
        {
            ClearGraph();
        }
    }
}
