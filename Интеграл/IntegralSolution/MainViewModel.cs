using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OxyPlot;

namespace IntegralSolution
{
    public class MainViewModel
    {
        public MainViewModel()
        {
            this.Title = "График";
            this.Points=new List<DataPoint>();
            //this.Points = new List<DataPoint>
            //                  {
            //                      new DataPoint(0, 4),
            //                      new DataPoint(10, 13),
            //                      new DataPoint(20, 15),
            //                      new DataPoint(30, 16),
            //                      new DataPoint(40, 12),
            //                      new DataPoint(50, 12)
            //                  };
        }

        public string Title { get; private set; }

        public IList<DataPoint> Points { get; private set; }
    }
}
