using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Diagnostics;
using System.IO;
using System.IO.Compression;

namespace Lab5
{
    public partial class FormMain : Form
    {
        WebClient webClient = new WebClient();
        Stopwatch stopwatch = new Stopwatch();
        Stopwatch stopwatchSpeed = new Stopwatch();
        double lastTime = 0.0;
        long totalToRecv = 0;
        long prevRecv = 0;
        
        public FormMain()
        {
            InitializeComponent();

            webClient.DownloadProgressChanged += webClientDownloadProgress;
            webClient.DownloadFileCompleted += webClientDownloadComplete;

            this._lProgress.Text = "Progress: 0% (0.00 MB / 0.00 MB)";
            this._lTime.Text = "Time:       0.00 s / 0.00 s";
            this._lSpeed.Text = "Speed:    0.00 MB/s";
        }

        private void _bDownload_Click(object sender, EventArgs e)
        {
            _sfd.FileName = "";
            _sfd.ShowDialog();
            
            if(!String.IsNullOrEmpty(_sfd.FileName))
            {
                try
                {
                    webClient.DownloadFileAsync(new Uri(_tbURL.Text), _sfd.FileName);

                    lastTime = 0.0;
                    totalToRecv = 0;
                    prevRecv = 0;

                    stopwatch.Restart();
                    stopwatchSpeed.Restart();

                    _bDownload.Enabled = false;
                    _tbURL.Enabled = false;
                }
                catch(Exception ex)
                {
                    MessageBox.Show(ex.ToString(), "ERROR");
                }
            }
            else
            {
                MessageBox.Show("File name must be defined!", "ERROR");
            }
        }

        private void webClientDownloadProgress(object sender, DownloadProgressChangedEventArgs e)
        {
            if(stopwatch.Elapsed.TotalSeconds - lastTime > 0.1)
            {
                double speed = ((e.BytesReceived - prevRecv) / 1024f / 1024f) / stopwatchSpeed.Elapsed.TotalSeconds;
                
                _pgbProgress.Value = e.ProgressPercentage;
                this._lProgress.Text = "Progress: " + e.ProgressPercentage.ToString() + "% (" + (e.BytesReceived / 1024f / 1024f).ToString("0.00") + " MB / " + (e.TotalBytesToReceive / 1024f / 1024f).ToString("0.00") + " MB)";
                this._lTime.Text = "Time:       " + stopwatch.Elapsed.TotalSeconds.ToString("0.00") + " s / " + (((e.TotalBytesToReceive - e.BytesReceived) / 1024f / 1024f) / speed).ToString("0.00") + " s";
                this._lSpeed.Text = "Speed:    " + speed.ToString("0.00") + " MB/s";
                
                lastTime = stopwatch.Elapsed.TotalSeconds;
                totalToRecv = e.TotalBytesToReceive;
                prevRecv = e.BytesReceived;

                stopwatchSpeed.Restart();
            }
        }

        private void webClientDownloadComplete(object sender, AsyncCompletedEventArgs e)
        {
            stopwatch.Stop();
            stopwatchSpeed.Stop();

            if (totalToRecv == 0)
            {
                MessageBox.Show("File can't be downloaded!", "Download");
            }
            else
            {
                if (e.Cancelled)
                {
                    _pgbProgress.Value = 0;
                    this._lProgress.Text = "Progress: 0% (0.00 MB / 0.00 MB)";
                    this._lTime.Text = "Time:       0.00 s / 0.00 s";
                    this._lSpeed.Text = "Speed:    0.00 MB/s";

                    MessageBox.Show("Download was cancelled!", "Download");
                }
                else
                {
                    _pgbProgress.Value = 100;
                    this._lProgress.Text = "Progress: 100% (" + (totalToRecv / 1024f / 1024f).ToString("0.00") + " MB / " + (totalToRecv / 1024f / 1024f).ToString("0.00") + " MB)";
                    this._lTime.Text = "Time:       " + stopwatch.Elapsed.TotalSeconds.ToString("0.00") + " s / 0.00" + " s";
                    this._lSpeed.Text = "Speed:    " + (((totalToRecv - prevRecv) / 1024f / 1024f) / stopwatchSpeed.Elapsed.TotalSeconds).ToString("0.00") + " MB/s";

                    MessageBox.Show("File downloaded successfully!", "Download");

                    _fbd.SelectedPath = "";

                    do
                    {
                        _fbd.ShowDialog();

                        if (String.IsNullOrEmpty(_fbd.SelectedPath))
                        {
                            MessageBox.Show("Path must be defined!", "ERROR");
                        }

                    } while (String.IsNullOrEmpty(_fbd.SelectedPath));

                    int codePage = System.Globalization.CultureInfo.CurrentCulture.TextInfo.OEMCodePage;//Вернет 866
                    ZipFile.ExtractToDirectory(_sfd.FileName, _fbd.SelectedPath, Encoding.GetEncoding(codePage));

                    string textFile = Directory.GetFiles(_fbd.SelectedPath, "*.txt", SearchOption.AllDirectories).FirstOrDefault();

                    if (!String.IsNullOrEmpty(_fbd.SelectedPath))
                    {
                        MessageBox.Show(File.ReadAllText(textFile), textFile);
                    }
                    else
                    {
                        MessageBox.Show("Text file not found in zip!", "ERROR");
                    }

                }
            }

            _bDownload.Enabled = true;
            _tbURL.Enabled = true;
        }

        private void _bStop_Click(object sender, EventArgs e)
        {
            webClient.CancelAsync();
        }
    }
}
