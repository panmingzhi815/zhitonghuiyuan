using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Collections;
using System.IO;

namespace CSharpTest
{
    //已添加设备信息结构体
    [StructLayout(LayoutKind.Sequential, Pack = 0, CharSet = CharSet.Ansi)]
    public struct AddDeviceInfo
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = LPRSDK.IP_MAX_LEN)]
        public string ucDeviceIP;//设备IP
        public IntPtr ptrDeviceHandle;//设备句柄

    }
    public partial class Form1 : Form
    {
        public DeviceInfoCallback DeviceInfofuc = null;
        public DeviceStatusCallback DeviceStatusfuc = null;
        public VehicleDataCallback VehicleDatafuc = null;
        public JPGStreamCallBack JPGStreamfuc = null;
        public Hashtable DeviceTable;
        public Form1()
        {
            InitializeComponent();
        }

        void fucDeviceInfo(IntPtr pUserData, ref LPRSDK.DeviceInfo pDeviceInfo)
        {
            //将扫描的设备添加到列表
            String sIP = pDeviceInfo.DeviceNetInfo.ucDeviceIP.ToString();
            String sMac = "";
            sMac = string.Format("{0} {1} {2} {3} {4} {5}", pDeviceInfo.ucMAC[0],
                pDeviceInfo.ucMAC[1], pDeviceInfo.ucMAC[2], pDeviceInfo.ucMAC[3],
            pDeviceInfo.ucMAC[4],pDeviceInfo.ucMAC[5]);
            int nIndex = 0;
            bool bFind = false;
            for (nIndex = 0; nIndex < this.listView1.Items.Count; nIndex++)
            {
                if (this.listView1.Items[nIndex].Text.ToString() == sIP)
                {
                    this.listView1.Items[nIndex].SubItems[1].Text = pDeviceInfo.ucDeviceVersion;
                    this.listView1.Items[nIndex].SubItems[2].Text = sMac;
                    bFind = true;
                    break;
                }
            }
            if (bFind)
                return;
            ListViewItem item = this.listView1.Items.Add(sIP);
            item.SubItems.Add(pDeviceInfo.ucDeviceVersion);
            item.SubItems.Add(sMac);
            item.SubItems.Add("未连接");

        }

        void fucDeviceStatus(IntPtr pUserData, ref LPRSDK.DeviceStatus pStatus)
        {

        }
        void fucVehicleData(IntPtr pUserData, ref LPRSDK.VehicleData pData)
        {
            string sIP = "";
             foreach (DictionaryEntry de in DeviceTable)
            {

                AddDeviceInfo info = (AddDeviceInfo)DeviceTable[de.Key];
                if (info.ptrDeviceHandle == pData.pDeviceHandle)
                {
                    sIP = info.ucDeviceIP;
                           break;
                }
            }
           string fileDirectory = string.Empty;
            fileDirectory = string.Format("{0}\\{1}\\{2}-{3}-{4}\\", Application.StartupPath, pData.ucDeviceIP, pData.ucTime[0] + 2000,
                pData.ucTime[1],pData.ucTime[2]);
            if (!Directory.Exists(fileDirectory))
            {
                Directory.CreateDirectory(fileDirectory);
            }

            String strSpeFile = "", strPlateFile = "", strCIFFile = "";



            strSpeFile = string.Format("{0}{1}{2}{3}-({4})-big.jpg", fileDirectory, pData.ucTime[3], pData.ucTime[4], pData.ucTime[5], pData.ucTime[2]);
            strPlateFile = string.Format("{0}{1}{2}{3}-({4})-plate.jpg", fileDirectory, pData.ucTime[3], pData.ucTime[4], pData.ucTime[5], pData.ucTime[2]);
            strCIFFile = string.Format("{0}{1}{2}{3}-({4})-cif.jpg", fileDirectory, pData.ucTime[3], pData.ucTime[4], pData.ucTime[5], pData.ucTime[2]);

            
            if (pData.uiBigImageLen != 0)
            {
                FileStream fs = new FileStream(strSpeFile, FileMode.Create, FileAccess.Write);
                 byte[] bytData = new byte[pData.uiBigImageLen];
                 Marshal.Copy(pData.pucBigImage, bytData, 0, (int)pData.uiBigImageLen);
                try
                {
                    fs.Write(bytData, 0, (int)pData.uiBigImageLen);
                    fs.Close();
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message);
                }

            }
            if (pData.uiCIFImageLen != 0)
            {
                FileStream fs = new FileStream(strCIFFile, FileMode.Create, FileAccess.Write);
                byte[] bytData = new byte[pData.uiCIFImageLen];
                Marshal.Copy(pData.pucCIFImage, bytData, 0, (int)pData.uiCIFImageLen);
                try
                {
                    fs.Write(bytData, 0, (int)pData.uiCIFImageLen);
                    fs.Close();
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message);
                }

            }

            if (pData.uiPlateImageLen != 0)
            {
                FileStream fs = new FileStream(strPlateFile, FileMode.Create, FileAccess.Write);
                byte[] bytData = new byte[pData.uiPlateImageLen];
                Marshal.Copy(pData.pucPlateImage, bytData, 0, (int)pData.uiPlateImageLen);
                try
                {
                    fs.Write(bytData, 0, (int)pData.uiPlateImageLen);
                    fs.Close();
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message);
                }

            }
            //窗口控件绑定变量置空
            this.picBigImage.Image = null;
            this.picCIFImage.Image = null;
            this.picPlateImage.Image = null;

            FileInfo fi = new FileInfo(strSpeFile);
            if (fi.Exists)
            {
                this.picBigImage.Load(strSpeFile);
                //picBigImage.Image = Image.FromFile(strSpeFile);
            }

            fi = new FileInfo(strPlateFile);
            if (fi.Exists)
            {
                this.picPlateImage.Load(strPlateFile);
            }

            fi = new FileInfo(strCIFFile);
            if (fi.Exists)
            {
                this.picCIFImage.Load(strCIFFile);
            }


            ShowPlate(pData.ucPlate.ToString(), pData.PlateColor);

            
        }


        void fucJPGStream(IntPtr pUserData, ref LPRSDK.JPGData pJPGData)
        {

        }
        public void ShowPlate(String strPlate, LPRSDK.PLATE_COLOR nColor)
        {
            labelPlate.Text = strPlate;
            switch (nColor)
            {
                case LPRSDK.PLATE_COLOR.YELLOW_COLOR:
                    labelPlate.BackColor = Color.Yellow;
                    labelPlate.ForeColor = Color.Black;
                    break;
                 case LPRSDK.PLATE_COLOR.BLUE_COLOR:
                    labelPlate.BackColor = Color.Blue;
                    labelPlate.ForeColor = Color.White;
                    break;
                 case LPRSDK.PLATE_COLOR.WHITE_COLOR:
                    labelPlate.BackColor = Color.White;
                    labelPlate.ForeColor = Color.Black;
                    break;
                 case LPRSDK.PLATE_COLOR.BLACK_COLOR:
                    labelPlate.BackColor = Color.Black;
                    labelPlate.ForeColor = Color.White;
                    break;
                default:
                    labelPlate.BackColor = Color.SlateGray;
                    labelPlate.ForeColor = Color.Black;
                    break;
            }
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            DeviceTable = new Hashtable();
            //初始化动态库
            DeviceInfofuc = new DeviceInfoCallback(fucDeviceInfo);
            VehicleDatafuc = new VehicleDataCallback(fucVehicleData);
            JPGStreamfuc = new JPGStreamCallBack(fucJPGStream);
            DeviceStatusfuc = new DeviceStatusCallback(fucDeviceStatus);
            LPRSDK.LPR_IsWriteLog(true);
            LPRSDK.LPR_Init(this.Handle, IntPtr.Zero, DeviceInfofuc,DeviceStatusfuc, VehicleDatafuc, JPGStreamfuc);

        }
        private void BtnScan_Click(object sender, EventArgs e)
        {
            LPRSDK.LPR_ScanDevice();
        }

        private void btnConnectDevice_Click(object sender, EventArgs e)
        {
            if(listView1.SelectedItems.Count == 0)
                return;
            StringBuilder sbIP = new StringBuilder(listView1.SelectedItems[0].Text);
            IntPtr ptrHandle = IntPtr.Zero;
            if ((LPRSDK.FEEKBACK_TYPE)LPRSDK.LPR_ConnectCamera(sbIP, ref ptrHandle) == LPRSDK.FEEKBACK_TYPE.RESULT_OK)
            {
                listView1.SelectedItems[0].SubItems[2].Text = "已连接";
                AddDeviceInfo Info = new AddDeviceInfo();
                Info.ptrDeviceHandle = ptrHandle;
                Info.ucDeviceIP = sbIP.ToString();
                DeviceTable.Add(sbIP, Info);
            }
        }

        private void BtnDisconnect_Click(object sender, EventArgs e)
        {
            if (listView1.SelectedItems.Count == 0)
                return;

            StringBuilder sbIP = new StringBuilder(listView1.SelectedItems[0].Text);
            foreach (DictionaryEntry de in DeviceTable)
            {

                AddDeviceInfo info = (AddDeviceInfo)DeviceTable[de.Key];
                if (info.ucDeviceIP == sbIP.ToString())
                {
                    LPRSDK.LPR_DisconnectCamera(info.ptrDeviceHandle);
                    listView1.SelectedItems[0].SubItems[2].Text = "未连接";
                    break;
                }
            }
        }

        private void BtnCapture_Click(object sender, EventArgs e)
        {
            foreach (DictionaryEntry de in DeviceTable)
            {

                AddDeviceInfo info = (AddDeviceInfo)DeviceTable[de.Key];
                LPRSDK.LPR_Capture(info.ptrDeviceHandle);
                //LPRSDK.LPR_SetShutterValue(info.ptrDeviceHandle, LPRSDK.SHUTTER_PARAMS.SHUTTER_100);
            }
        }
    }
}
