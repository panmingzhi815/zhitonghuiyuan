namespace CSharpTest
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.listView1 = new System.Windows.Forms.ListView();
            this.columnHeader1 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader2 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader3 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader4 = new System.Windows.Forms.ColumnHeader();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.BtnScan = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.picCIFImage = new System.Windows.Forms.PictureBox();
            this.labelPlate = new System.Windows.Forms.Label();
            this.picPlateImage = new System.Windows.Forms.PictureBox();
            this.picBigImage = new System.Windows.Forms.PictureBox();
            this.btnConnectDevice = new System.Windows.Forms.Button();
            this.BtnDisconnect = new System.Windows.Forms.Button();
            this.BtnCapture = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picCIFImage)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picPlateImage)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picBigImage)).BeginInit();
            this.SuspendLayout();
            // 
            // listView1
            // 
            this.listView1.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2,
            this.columnHeader3,
            this.columnHeader4});
            this.listView1.Location = new System.Drawing.Point(6, 20);
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(331, 226);
            this.listView1.TabIndex = 0;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "设备IP";
            this.columnHeader1.Width = 100;
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "设备版本";
            this.columnHeader2.Width = 100;
            // 
            // columnHeader3
            // 
            this.columnHeader3.Text = "MAC地址";
            this.columnHeader3.Width = 100;
            // 
            // columnHeader4
            // 
            this.columnHeader4.Text = "连接状态";
            this.columnHeader4.Width = 100;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.listView1);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(344, 252);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "设备列表";
            // 
            // BtnScan
            // 
            this.BtnScan.Location = new System.Drawing.Point(12, 282);
            this.BtnScan.Name = "BtnScan";
            this.BtnScan.Size = new System.Drawing.Size(75, 23);
            this.BtnScan.TabIndex = 2;
            this.BtnScan.Text = "扫描设备";
            this.BtnScan.UseVisualStyleBackColor = true;
            this.BtnScan.Click += new System.EventHandler(this.BtnScan_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.picCIFImage);
            this.groupBox2.Controls.Add(this.labelPlate);
            this.groupBox2.Controls.Add(this.picPlateImage);
            this.groupBox2.Controls.Add(this.picBigImage);
            this.groupBox2.Location = new System.Drawing.Point(372, 13);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(406, 506);
            this.groupBox2.TabIndex = 3;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "数据信息";
            // 
            // picCIFImage
            // 
            this.picCIFImage.Location = new System.Drawing.Point(15, 297);
            this.picCIFImage.Name = "picCIFImage";
            this.picCIFImage.Size = new System.Drawing.Size(191, 190);
            this.picCIFImage.TabIndex = 3;
            this.picCIFImage.TabStop = false;
            // 
            // labelPlate
            // 
            this.labelPlate.Font = new System.Drawing.Font("宋体", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelPlate.Location = new System.Drawing.Point(212, 364);
            this.labelPlate.Name = "labelPlate";
            this.labelPlate.Size = new System.Drawing.Size(188, 49);
            this.labelPlate.TabIndex = 2;
            this.labelPlate.Text = "车牌号码";
            // 
            // picPlateImage
            // 
            this.picPlateImage.Location = new System.Drawing.Point(212, 297);
            this.picPlateImage.Name = "picPlateImage";
            this.picPlateImage.Size = new System.Drawing.Size(188, 50);
            this.picPlateImage.TabIndex = 1;
            this.picPlateImage.TabStop = false;
            // 
            // picBigImage
            // 
            this.picBigImage.Location = new System.Drawing.Point(15, 20);
            this.picBigImage.Name = "picBigImage";
            this.picBigImage.Size = new System.Drawing.Size(385, 261);
            this.picBigImage.TabIndex = 0;
            this.picBigImage.TabStop = false;
            // 
            // btnConnectDevice
            // 
            this.btnConnectDevice.Location = new System.Drawing.Point(134, 282);
            this.btnConnectDevice.Name = "btnConnectDevice";
            this.btnConnectDevice.Size = new System.Drawing.Size(75, 23);
            this.btnConnectDevice.TabIndex = 4;
            this.btnConnectDevice.Text = "连接设备";
            this.btnConnectDevice.UseVisualStyleBackColor = true;
            this.btnConnectDevice.Click += new System.EventHandler(this.btnConnectDevice_Click);
            // 
            // BtnDisconnect
            // 
            this.BtnDisconnect.Location = new System.Drawing.Point(243, 282);
            this.BtnDisconnect.Name = "BtnDisconnect";
            this.BtnDisconnect.Size = new System.Drawing.Size(75, 23);
            this.BtnDisconnect.TabIndex = 5;
            this.BtnDisconnect.Text = "断开设备";
            this.BtnDisconnect.UseVisualStyleBackColor = true;
            this.BtnDisconnect.Click += new System.EventHandler(this.BtnDisconnect_Click);
            // 
            // BtnCapture
            // 
            this.BtnCapture.Location = new System.Drawing.Point(243, 328);
            this.BtnCapture.Name = "BtnCapture";
            this.BtnCapture.Size = new System.Drawing.Size(75, 23);
            this.BtnCapture.TabIndex = 6;
            this.BtnCapture.Text = "模拟抓拍";
            this.BtnCapture.UseVisualStyleBackColor = true;
            this.BtnCapture.Click += new System.EventHandler(this.BtnCapture_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(790, 529);
            this.Controls.Add(this.BtnCapture);
            this.Controls.Add(this.BtnDisconnect);
            this.Controls.Add(this.btnConnectDevice);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.BtnScan);
            this.Controls.Add(this.groupBox1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.picCIFImage)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picPlateImage)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picBigImage)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.Button BtnScan;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label labelPlate;
        private System.Windows.Forms.PictureBox picPlateImage;
        private System.Windows.Forms.PictureBox picBigImage;
        private System.Windows.Forms.PictureBox picCIFImage;
        private System.Windows.Forms.Button btnConnectDevice;
        private System.Windows.Forms.Button BtnDisconnect;
        private System.Windows.Forms.ColumnHeader columnHeader4;
        private System.Windows.Forms.Button BtnCapture;
    }
}

