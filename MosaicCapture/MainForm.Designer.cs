namespace MosaicCapture
{
    partial class MainForm
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージド リソースを破棄する場合は true を指定し、その他の場合は false を指定します。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.mainControl = new VisualTree.VisualTeeControl();
            this.verticalBar = new System.Windows.Forms.VScrollBar();
            this.horizontalBar = new System.Windows.Forms.HScrollBar();
            this.tilePlusBtn = new MosaicCapture.Buttons.ZoomPlusButton();
            this.tileMinusBtn = new MosaicCapture.Buttons.ZoomMinusButton();
            this.minusBtn = new MosaicCapture.Buttons.ZoomMinusButton();
            this.plusBtn = new MosaicCapture.Buttons.ZoomPlusButton();
            this.copyBtn = new MosaicCapture.Buttons.CopyButton();
            this.openBtn = new MosaicCapture.Buttons.OpenButton();
            this.clipBtn = new MosaicCapture.Buttons.ClipButton();
            this.mainControl.SuspendLayout();
            this.SuspendLayout();
            // 
            // mainControl
            // 
            this.mainControl.Controls.Add(this.verticalBar);
            this.mainControl.Controls.Add(this.horizontalBar);
            this.mainControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainControl.Font = new System.Drawing.Font("Meiryo UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.mainControl.Location = new System.Drawing.Point(3, 64);
            this.mainControl.Margin = new System.Windows.Forms.Padding(5, 4, 5, 4);
            this.mainControl.Name = "mainControl";
            this.mainControl.Size = new System.Drawing.Size(914, 656);
            this.mainControl.TabIndex = 12;
            this.mainControl.TabStop = false;
            this.mainControl.VisualInitialResourceEvent += new VisualTree.VisualTeeControl.VisualResourceEventHandler(this.mainControl_VisualInitialResourceEvent);
            this.mainControl.VisualRenderEvent += new VisualTree.VisualTeeControl.VisualRenderEventHandler(this.mainControl_VisualRenderEvent);
            this.mainControl.MouseDown += new System.Windows.Forms.MouseEventHandler(this.mainControl_MouseDown);
            this.mainControl.MouseMove += new System.Windows.Forms.MouseEventHandler(this.mainControl_MouseMove);
            this.mainControl.MouseUp += new System.Windows.Forms.MouseEventHandler(this.mainControl_MouseUp);
            // 
            // verticalBar
            // 
            this.verticalBar.Location = new System.Drawing.Point(479, 261);
            this.verticalBar.Name = "verticalBar";
            this.verticalBar.Size = new System.Drawing.Size(31, 238);
            this.verticalBar.TabIndex = 11;
            this.verticalBar.Visible = false;
            this.verticalBar.ValueChanged += new System.EventHandler(this.verticalBar_ValueChanged);
            // 
            // horizontalBar
            // 
            this.horizontalBar.Location = new System.Drawing.Point(198, 433);
            this.horizontalBar.Name = "horizontalBar";
            this.horizontalBar.Size = new System.Drawing.Size(259, 25);
            this.horizontalBar.TabIndex = 10;
            this.horizontalBar.Visible = false;
            this.horizontalBar.ValueChanged += new System.EventHandler(this.horizontalBar_ValueChanged);
            // 
            // tilePlusBtn
            // 
            this.tilePlusBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.tilePlusBtn.DialogResult = System.Windows.Forms.DialogResult.None;
            this.tilePlusBtn.EnableColor = System.Drawing.Color.Black;
            this.tilePlusBtn.FocusColor = System.Drawing.Color.DimGray;
            this.tilePlusBtn.HoverColor = System.Drawing.Color.LightGray;
            this.tilePlusBtn.Location = new System.Drawing.Point(130, 729);
            this.tilePlusBtn.Name = "tilePlusBtn";
            this.tilePlusBtn.NotEnableColor = System.Drawing.Color.LightGray;
            this.tilePlusBtn.Size = new System.Drawing.Size(26, 26);
            this.tilePlusBtn.TabIndex = 4;
            this.tilePlusBtn.Text = "zoomPlusButton1";
            this.tilePlusBtn.Click += new System.EventHandler(this.tilePlusBtn_Click);
            // 
            // tileMinusBtn
            // 
            this.tileMinusBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.tileMinusBtn.DialogResult = System.Windows.Forms.DialogResult.None;
            this.tileMinusBtn.EnableColor = System.Drawing.Color.Black;
            this.tileMinusBtn.FocusColor = System.Drawing.Color.DimGray;
            this.tileMinusBtn.HoverColor = System.Drawing.Color.LightGray;
            this.tileMinusBtn.Location = new System.Drawing.Point(10, 729);
            this.tileMinusBtn.Name = "tileMinusBtn";
            this.tileMinusBtn.NotEnableColor = System.Drawing.Color.LightGray;
            this.tileMinusBtn.Size = new System.Drawing.Size(26, 26);
            this.tileMinusBtn.TabIndex = 3;
            this.tileMinusBtn.Text = "zoomMinusButton1";
            this.tileMinusBtn.Click += new System.EventHandler(this.tileMinusBtn_Click);
            // 
            // minusBtn
            // 
            this.minusBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.minusBtn.DialogResult = System.Windows.Forms.DialogResult.None;
            this.minusBtn.EnableColor = System.Drawing.Color.Black;
            this.minusBtn.FocusColor = System.Drawing.Color.DimGray;
            this.minusBtn.HoverColor = System.Drawing.Color.LightGray;
            this.minusBtn.Location = new System.Drawing.Point(663, 729);
            this.minusBtn.Name = "minusBtn";
            this.minusBtn.NotEnableColor = System.Drawing.Color.LightGray;
            this.minusBtn.Size = new System.Drawing.Size(26, 26);
            this.minusBtn.TabIndex = 5;
            this.minusBtn.Text = "zoomMinusButton1";
            this.minusBtn.Click += new System.EventHandler(this.minusBtn_Click);
            // 
            // plusBtn
            // 
            this.plusBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.plusBtn.DialogResult = System.Windows.Forms.DialogResult.None;
            this.plusBtn.EnableColor = System.Drawing.Color.Black;
            this.plusBtn.FocusColor = System.Drawing.Color.DimGray;
            this.plusBtn.HoverColor = System.Drawing.Color.LightGray;
            this.plusBtn.Location = new System.Drawing.Point(882, 729);
            this.plusBtn.Name = "plusBtn";
            this.plusBtn.NotEnableColor = System.Drawing.Color.LightGray;
            this.plusBtn.Size = new System.Drawing.Size(26, 26);
            this.plusBtn.TabIndex = 6;
            this.plusBtn.Text = "zoomPlusButton1";
            this.plusBtn.Click += new System.EventHandler(this.plusBtn_Click);
            // 
            // copyBtn
            // 
            this.copyBtn.DialogResult = System.Windows.Forms.DialogResult.None;
            this.copyBtn.EnableColor = System.Drawing.Color.DimGray;
            this.copyBtn.FocusColor = System.Drawing.Color.DimGray;
            this.copyBtn.HoverColor = System.Drawing.Color.LightGray;
            this.copyBtn.Location = new System.Drawing.Point(127, 4);
            this.copyBtn.Name = "copyBtn";
            this.copyBtn.NotEnableColor = System.Drawing.Color.LightGray;
            this.copyBtn.Size = new System.Drawing.Size(55, 56);
            this.copyBtn.TabIndex = 2;
            this.copyBtn.Text = "copyButton1";
            this.copyBtn.Click += new System.EventHandler(this.copyBtn_Click);
            // 
            // openBtn
            // 
            this.openBtn.DialogResult = System.Windows.Forms.DialogResult.None;
            this.openBtn.EnableColor = System.Drawing.Color.DimGray;
            this.openBtn.FocusColor = System.Drawing.Color.DimGray;
            this.openBtn.HoverColor = System.Drawing.Color.LightGray;
            this.openBtn.Location = new System.Drawing.Point(67, 4);
            this.openBtn.Name = "openBtn";
            this.openBtn.NotEnableColor = System.Drawing.Color.LightGray;
            this.openBtn.Size = new System.Drawing.Size(55, 56);
            this.openBtn.TabIndex = 1;
            this.openBtn.Text = "openButton1";
            this.openBtn.Click += new System.EventHandler(this.openBtn_Click);
            // 
            // clipBtn
            // 
            this.clipBtn.DialogResult = System.Windows.Forms.DialogResult.None;
            this.clipBtn.EnableColor = System.Drawing.Color.DimGray;
            this.clipBtn.FocusColor = System.Drawing.Color.DimGray;
            this.clipBtn.HoverColor = System.Drawing.Color.LightGray;
            this.clipBtn.Location = new System.Drawing.Point(5, 4);
            this.clipBtn.Name = "clipBtn";
            this.clipBtn.NotEnableColor = System.Drawing.Color.LightGray;
            this.clipBtn.Size = new System.Drawing.Size(55, 56);
            this.clipBtn.TabIndex = 0;
            this.clipBtn.Text = "clipButton1";
            this.clipBtn.Click += new System.EventHandler(this.clipBtn_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(10F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.DimGray;
            this.ClientSize = new System.Drawing.Size(920, 760);
            this.ControlBox = false;
            this.Controls.Add(this.tilePlusBtn);
            this.Controls.Add(this.tileMinusBtn);
            this.Controls.Add(this.minusBtn);
            this.Controls.Add(this.plusBtn);
            this.Controls.Add(this.copyBtn);
            this.Controls.Add(this.openBtn);
            this.Controls.Add(this.clipBtn);
            this.Controls.Add(this.mainControl);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Margin = new System.Windows.Forms.Padding(5, 4, 5, 4);
            this.MinimumSize = new System.Drawing.Size(520, 200);
            this.Name = "MainForm";
            this.Padding = new System.Windows.Forms.Padding(3, 64, 3, 40);
            this.Controls.SetChildIndex(this.mainControl, 0);
            this.Controls.SetChildIndex(this.clipBtn, 0);
            this.Controls.SetChildIndex(this.openBtn, 0);
            this.Controls.SetChildIndex(this.copyBtn, 0);
            this.Controls.SetChildIndex(this.plusBtn, 0);
            this.Controls.SetChildIndex(this.minusBtn, 0);
            this.Controls.SetChildIndex(this.tileMinusBtn, 0);
            this.Controls.SetChildIndex(this.tilePlusBtn, 0);
            this.mainControl.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.VScrollBar verticalBar;
        private System.Windows.Forms.HScrollBar horizontalBar;
        private VisualTree.VisualTeeControl mainControl;
        private Buttons.ClipButton clipBtn;
        private Buttons.OpenButton openBtn;
        private Buttons.CopyButton copyBtn;
        private Buttons.ZoomPlusButton plusBtn;
        private Buttons.ZoomMinusButton minusBtn;
        private Buttons.ZoomMinusButton tileMinusBtn;
        private Buttons.ZoomPlusButton tilePlusBtn;
    }
}

