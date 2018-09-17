using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using VisualTree;

namespace MosaicCapture
{
    /// <summary>モザイク修正アプリ、メインフォーム。</summary>
    public partial class MainForm
        : Dwm.DwmForm
    {
        #region "const"

        /// <summary>ビットマップリソース名。</summary>
        const string BITMAP_NAME = "bitmap res";

        /// <summary>ラバーバンドカラーリソース名。</summary>
        const string LABER_BAND_CLR_NAME = "laber res";

        /// <summary>スクロールバーのサイズ。</summary>
        const int BarSize = 14;

        #endregion

        #region "field"

        static int[] mosaicTile = { 3, 5, 10, 15 };

        /// <summary>対象モザイクビットマップ。</summary>
        private VisualResourceOfBitmap mosaicBitmap;

        /// <summary>最小スクロール量。</summary>
        private int scrollBarSmallChange;

        /// <summary>拡大、縮小率。</summary>
        private int zoom;

        /// <summary>クリックポイントを記憶する。</summary>
        private Point clickPos;

        /// <summary>ドラッグポイントを記憶する。</summary>
        private Point dragPos;

        /// <summary>摘みの矩形。</summary>
        private Rectangle thumbRec;

        /// <summary>摘みをクリックした位置。</summary>
        private Point thumbPos;

        /// <summary>サイズのインデックス。</summary>
        private int szindex;

        #endregion

        #region ""

        /// <summary>コンストラクタ。</summary>
        public MainForm()
        {
            InitializeComponent();

            this.scrollBarSmallChange = 1;
            this.clickPos = new Point(-1, -1);
            this.zoom = 100;
            this.thumbPos = new Point(-1, -1);
            this.szindex = 1;

            this.DwmExtendFrameIntoClientArea(3, 3, 65, 40);
            //this->DwmExtendFrameIntoClientArea(this->Handle, 3, 3, 65, 40);
        }

        #endregion

        /// <summary>クリップボードの画像を取得する。</summary>
        /// <returns>画像情報。</returns>
        private Bitmap ReadClipBoard()
        {
            var img = Clipboard.GetImage();
            if (img != null) {
                return new Bitmap(img);
            }
            else {
                throw new Exception("クリップボードに画像情報が格納されていない");
            }
        }

        #region ""

        /// <summary>Direct2Dリソース初期化イベントハンドラ。</summary>
        /// <param name="sender">イベント発行元。</param>
        /// <param name="e">イベントオブジェクト。</param>
        private void mainControl_VisualInitialResourceEvent(object sender, EventArgs e)
        {
            this.mainControl.CreateSolidColorBrush(LABER_BAND_CLR_NAME, Color.Blue);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mainControl_VisualRenderEvent(object sender, VisualTree.VisualRenderEventArgs e)
        {
            // 背景色塗り潰し
            e.RenderTarget.Clear(Color.White);

            e.RenderTarget.PushAxisAlignedClip(
                new RectangleF(0, 0,
                this.mainControl.Width - (this.verticalBar.Visible ? BarSize : 0),
                this.mainControl.Height - (this.horizontalBar.Visible ? BarSize : 0)),
                AntialiasMode.ANTIALIAS_MODE_ALIASED
            );

            // スクロール量に合わせて位置を変更
            e.RenderTarget.SetTransform(
                Matrix.Scale((this.zoom / 100.0f), (this.zoom / 100.0f)) *
                Matrix.Translation(-this.horizontalBar.Value, -this.verticalBar.Value)
            );

            // 画像リソースを保持していたら描画する
            if (e.Resources.HasResource(BITMAP_NAME)) {

                e.RenderTarget.DrawBitmap(e.Resources[BITMAP_NAME]);
            }

            //
            e.RenderTarget.SetTransform();
            if (this.clickPos.X >= 0 && this.clickPos.Y >= 0) {
                int x1, x2, y1, y2;
                if (this.clickPos.X < this.dragPos.X) {
                    x1 = this.clickPos.X;
                    x2 = this.dragPos.X;
                }
                else {
                    x2 = this.clickPos.X;
                    x1 = this.dragPos.X;
                }
                if (this.clickPos.Y < this.dragPos.Y) {
                    y1 = this.clickPos.Y;
                    y2 = this.dragPos.Y;
                }
                else {
                    y2 = this.clickPos.Y;
                    y1 = this.dragPos.Y;
                }
                e.RenderTarget.DrawRectangle(new RectangleF(x1, y1, x2 - x1, y2 - y1), e.Resources[LABER_BAND_CLR_NAME], 2);
            }

            e.RenderTarget.PopAxisAlignedClip();
        }

        #endregion

        protected override void OnSizeChanged(EventArgs e)
        {
            base.OnSizeChanged(e);
            this.mainControl?.SetBounds(2, 43, this.Width - 4, this.Height - 70);
            this.CalcScrollBar();
            this.Invalidate(new Rectangle(0, this.Height - 30, this.Width, 30));
        }

        private void CalcScrollBar()
        {
            if (this.mosaicBitmap != null &&
                this.mosaicBitmap.Source?.Width > 0 &&
                this.mosaicBitmap.Source?.Height > 0 &&
                this.mainControl.ClientRectangle.Width > 0 &&
                this.mainControl.ClientRectangle.Height > 0) {

                // 前回の表示状態、今回の表示状態のフラグを設定
                bool oldVBar = this.verticalBar.Visible;
                bool oldHBar = this.horizontalBar.Visible;
                bool showVBar = false;
                bool showHBar = false;
                var scrollableSize = this.mosaicBitmap.Source.Size;
                var canvas = this.mainControl.ClientRectangle;

                int maxWidth = (int)Math.Ceiling(scrollableSize.Width * (this.zoom / 100.0));
                int maxHeight = (int)Math.Ceiling(scrollableSize.Height * (this.zoom / 100.0));

                // 表示可能範囲から表示フラグを設定
                //
                // 1. 水平軸
                // 2. 垂直軸
                if (canvas.Width < maxWidth)      // 1
                {
                    showHBar = true;
                }
                if (canvas.Height < maxHeight)    // 2
                {
                    showVBar = true;
                }

                // スクロールバーの表示状態を考慮して表示フラグを設定
                //
                // 1. 水平軸
                // 2. 垂直軸
                for (int i = 0; i < 2; ++i) {
                    if (showVBar && canvas.Width - BarSize < maxWidth) {                                           // 1
                        showHBar = true;
                    }
                    if (showHBar && canvas.Height - BarSize < maxHeight) {                                           // 2
                        showVBar = true;
                    }
                }

                // 垂直スクロールバーの設定を行う
                //
                // 1. 表示処理
                //    1-1. スクロールバーの表示位置を設定
                //    1-2. スクロール値の設定
                //    1-3. 表示範囲を超えた値のときは丸める
                // 2. 非表示処理
                this.verticalBar.Visible = showVBar;
                if (this.verticalBar.Visible) {
                    var len = (showHBar ?                           // 1-1
                               canvas.Height - BarSize : canvas.Height);
                    this.verticalBar.Location = new Point(canvas.Right - BarSize, 0);
                    this.verticalBar.Size = new Size(BarSize, len);

                    this.verticalBar.LargeChange = len;             // 1-2
                    this.verticalBar.SmallChange = this.scrollBarSmallChange;
                    this.verticalBar.Minimum = 0;
                    this.verticalBar.Maximum = maxHeight + 1;

                    var maxv = maxHeight - 1 - this.verticalBar.LargeChange;
                    if (this.verticalBar.Value > maxv)              // 1-3
                    {
                        this.verticalBar.Value = maxv;
                    }
                }
                else {
                    this.verticalBar.Value = 0;                     // 2
                }

                // 水平スクロールバーの設定を行う
                //
                // 1. 表示処理
                //    1-1. スクロールバーの表示位置を設定
                //    1-2. スクロール値の設定
                //    1-3. 表示範囲を超えた値のときは丸める
                // 2. 非表示処理
                this.horizontalBar.Visible = showHBar;
                if (this.horizontalBar.Visible) {
                    var len = (showVBar ?                           // 1-1
                               canvas.Width - BarSize : canvas.Width);
                    this.horizontalBar.Location = new Point(0, canvas.Bottom - BarSize);
                    this.horizontalBar.Size = new Size(len, BarSize);

                    this.horizontalBar.LargeChange = len;           // 1-2
                    this.horizontalBar.SmallChange = this.scrollBarSmallChange;
                    this.horizontalBar.Minimum = 0;
                    this.horizontalBar.Maximum = maxWidth - 1;

                    var maxv = maxWidth - 1 - this.horizontalBar.LargeChange;
                    if (this.horizontalBar.Value > maxv)            // 1-3
                    {
                        this.horizontalBar.Value = maxv;
                    }
                }
                else {
                    this.horizontalBar.Value = 0;                   // 2
                }

                // 前回と表示が切り替わっていたら再表示を行う
                if (oldVBar != showVBar || oldHBar != showHBar) {
                    this.Invalidate();
                }
            }
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            var g = e.Graphics;
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;

            using (var path = new System.Drawing.Drawing2D.GraphicsPath()) {
                path.AddString($"{this.zoom}％",
                               this.Font.FontFamily,
                               (int)FontStyle.Regular,
                               14.0f,
                               new Point(this.Width - 200, this.Height - 20),
                               StringFormat.GenericDefault);
                if (this.DwmIsCompositionEnabled) {
                    for (int i = 1; i < 8; ++i) {
                        using (var pen = new Pen(Color.FromArgb(32, 255, 255, 255), i)) {
                            pen.LineJoin = System.Drawing.Drawing2D.LineJoin.Round;
                            g.DrawPath(pen, path);
                        }
                    }
                }
                g.FillPath(Brushes.Black, path);
            }

            g.FillRectangle(Brushes.Gray, this.Width - 130, this.Height - 15, 100, 4);
            if (this.zoom == 100) {
                this.thumbRec = new Rectangle(this.Width - 80 - 3, this.Height - 21, 6, 16);
            }
            else if (this.zoom < 100) {
                var pitch = 50.0 / 90.0;
                this.thumbRec = new Rectangle((int)(this.Width - 130 - 3 + (this.zoom - 10) * pitch), this.Height - 21, 6, 16);
            }
            else if (this.zoom > 100) {
                var pitch = 50.0 / 400.0;
                this.thumbRec = new Rectangle((int)(this.Width - 80 - 3 + (this.zoom - 100) * pitch), this.Height - 21, 6, 16);
            }
            g.FillRectangle(Brushes.Black, this.thumbRec);

            using (var path = new System.Drawing.Drawing2D.GraphicsPath()) {
                var msg = string.Format("{0}×{0}", mosaicTile[this.szindex]);
                var sz = g.MeasureString(msg, this.Font);

                path.AddString(msg,
                               this.Font.FontFamily,
                               (int)FontStyle.Regular,
                               14.0f,
                               new Point((int)(25 + (45 - sz.Width) / 2), this.Height - 21),
                               StringFormat.GenericDefault);
                if (this.DwmIsCompositionEnabled) {
                    for (int i = 1; i < 8; ++i) {
                        using (var pen = new Pen(Color.FromArgb(32, 255, 255, 255), i)) {
                            pen.LineJoin = System.Drawing.Drawing2D.LineJoin.Round;
                            g.DrawPath(pen, path);
                        }
                    }
                }
                g.FillPath(Brushes.Black, path);
            }
        }

        private void verticalBar_ValueChanged(object sender, EventArgs e)
        {
            this.mainControl.Invalidate();
        }

        private void horizontalBar_ValueChanged(object sender, EventArgs e)
        {
            this.mainControl.Invalidate();
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            base.OnMouseDown(e);
            if (this.thumbRec.Contains(e.X, e.Y)) {
                this.thumbPos = new Point(e.X, e.Y);
            }
        }

        protected override void OnMouseMove(MouseEventArgs e)
        {
            base.OnMouseMove(e);
            if (this.thumbPos.X >= 0 &&
                this.thumbPos.Y >= 0) {
                this.MoveThumb(e.X, e.Y);
            }
        }

        protected override void OnMouseUp(MouseEventArgs e)
        {
            base.OnMouseUp(e);
            this.thumbPos = new Point(-1, -1);
        }

        protected override void OnMouseLeave(EventArgs e)
        {
            base.OnMouseLeave(e);
            this.thumbPos = new Point(-1, -1);
        }

        protected override void OnMouseClick(MouseEventArgs e)
        {
            base.OnMouseClick(e);
            this.MoveThumb(e.X, e.Y);
        }

        private void MoveThumb(int x, int y)
        {
            if (x >= this.Width - 130 &&
                x < this.Width - 80 &&
                y > this.Height - 30) {
                var pitch = 90.0 / 50.0;
                this.zoom = (int)((x - (this.Width - 130)) * pitch) + 10;
                this.ZoomChanged();
            }
            else if (x >= this.Width - 80 &&
                     x < this.Width - 20 &&
                     y > this.Height - 30) {
                var pitch = 400.0 / 50.0;
                this.zoom = (int)((x - (this.Width - 80)) * pitch) + 100;
                this.ZoomChanged();
            }
        }

        private void mainControl_MouseDown(object sender, MouseEventArgs e)
        {
            this.clickPos = new Point(e.X, e.Y);
            this.dragPos = this.clickPos;
            this.mainControl.Invalidate();
        }

        private void mainControl_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left) {
                this.dragPos = new Point(e.X, e.Y);
                this.mainControl.Invalidate();
            }
        }

        private void mainControl_MouseUp(object sender, MouseEventArgs e)
        {
            if (this.clickPos.X >= 0 || this.clickPos.Y >= 0) {
                this.ConvertMosaic();

                this.clickPos = new Point(-1, -1);
                this.dragPos = new Point(-1, -1);

                this.mainControl.Invalidate();
            }
        }

        private void clipBtn_Click(object sender, EventArgs e)
        {
            this.SetModifiImage();
        }

        private void SetModifiImage()
        {
            try {
                // クリップボードの画像を取得する
                var bitmap = this.ReadClipBoard();

                this.mainControl.Remove(BITMAP_NAME);
                this.mosaicBitmap = this.mainControl.CreateBitmap(BITMAP_NAME, bitmap);
                this.mainControl.Rebuild();
                this.CalcScrollBar();
            }
            catch (Exception ex) {
                MessageBox.Show(ex.Message, "エラー", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void minusBtn_Click(object sender, EventArgs e)
        {
            var nzoom = (Math.Ceiling(this.zoom / 10.0) - 1.0) * 10.0;
            this.zoom = (int)nzoom;
            this.ZoomChanged();
        }

        private void plusBtn_Click(object sender, EventArgs e)
        {
            var nzoom = (Math.Floor(this.zoom / 10.0) + 1.0) * 10.0;
            this.zoom = (int)nzoom;
            this.ZoomChanged();
        }

        private void ZoomChanged()
        {
            if (this.zoom < 10) {
                this.zoom = 10;
            }
            else if (this.zoom > 500) {
                this.zoom = 500;
            }
            else {
                this.mainControl.Invalidate();
                this.Invalidate(new Rectangle(0, this.Height - 30, this.Width, 30));
                this.OnSizeChanged(new EventArgs());
            }
        }

        private void openBtn_Click(object sender, EventArgs e)
        {
            using (var dialog = new OpenFileDialog()) {
                dialog.RestoreDirectory = true;
                dialog.Filter = "画像ファイル|*.bmp;*.jpeg;*.png";
                dialog.Filter = "全てのファイル|*.*";
                dialog.FilterIndex = 0;
                dialog.Title = "画像を選択";
                dialog.Multiselect = false;

                if (dialog.ShowDialog() == DialogResult.OK) {
                    var bitmap = new Bitmap(dialog.FileName);
                    this.mainControl.Remove(BITMAP_NAME);
                    this.mosaicBitmap = this.mainControl.CreateBitmap(BITMAP_NAME, bitmap);
                    this.mainControl.Rebuild();
                    this.CalcScrollBar();
                }
            }
        }

        private void ConvertMosaic()
        {
            if (this.mosaicBitmap?.Source != null) {
                int x1, x2, y1, y2;
                if (this.clickPos.X < this.dragPos.X) {
                    x1 = (int)Math.Floor((this.clickPos.X + this.horizontalBar.Value) / (this.zoom / 100.0));
                    x2 = (int)Math.Ceiling((this.dragPos.X + this.horizontalBar.Value) / (this.zoom / 100.0));
                }
                else {
                    x1 = (int)Math.Floor((this.dragPos.X + this.horizontalBar.Value) / (this.zoom / 100.0));
                    x2 = (int)Math.Ceiling((this.clickPos.X + this.horizontalBar.Value) / (this.zoom / 100.0));
                }
                if (this.clickPos.Y < this.dragPos.Y) {
                    y1 = (int)Math.Floor((this.clickPos.Y + this.verticalBar.Value) / (this.zoom / 100.0));
                    y2 = (int)Math.Ceiling((this.dragPos.Y + this.verticalBar.Value) / (this.zoom / 100.0));
                }
                else {
                    y1 = (int)Math.Floor((this.dragPos.Y + this.verticalBar.Value) / (this.zoom / 100.0));
                    y2 = (int)Math.Ceiling((this.clickPos.Y + this.verticalBar.Value) / (this.zoom / 100.0));
                }

                var size = mosaicTile[this.szindex];
                var bitmap = new Bitmap(this.mosaicBitmap.Source);
                var data = bitmap.LockBits(
                        new Rectangle(0, 0, bitmap.Width, bitmap.Height),
                        System.Drawing.Imaging.ImageLockMode.ReadWrite,
                        System.Drawing.Imaging.PixelFormat.Format32bppArgb);

                var buf = new byte[bitmap.Width * bitmap.Height * 4];
                Marshal.Copy(data.Scan0, buf, 0, buf.Length);

                for (int y = y1; y < bitmap.Height && y < y2; y += size) {
                    for (int x = x1; x < bitmap.Width && x < x2; x += size) {
                        this.AvePixel(bitmap, data, buf, x, y, size);
                    }
                }

                Marshal.Copy(buf, 0, data.Scan0, buf.Length);
                bitmap.UnlockBits(data);

                this.mainControl.Remove(BITMAP_NAME);
                this.mosaicBitmap = this.mainControl.CreateBitmap(BITMAP_NAME, bitmap);
                this.mainControl.Rebuild();
            }
        }

        /// <summary>モザイクの一タイルを作成する。</summary>
        /// <param name="bitmap">元としたビットマップ。</param>
        /// <param name="data">画像情報。</param>
        /// <param name="buf">画像データ。</param>
        /// <param name="x">X位置。</param>
        /// <param name="y">Y位置。</param>
        /// <param name="size">モザイクのタイルサイズ。</param>
        private void AvePixel(Bitmap bitmap, System.Drawing.Imaging.BitmapData data, byte[] buf, int x, int y, int size)
        {
            var r = 0.0;
            var g = 0.0;
            var b = 0.0;
            var c = 0;

            for (int iy = y; iy < bitmap.Height && iy < y + size; ++iy) {
                for (int ix = x; ix < bitmap.Width && ix < x + size; ++ix) {
                    r += buf[data.Stride * iy + (ix * 4) + 0];
                    g += buf[data.Stride * iy + (ix * 4) + 1];
                    b += buf[data.Stride * iy + (ix * 4) + 2];
                    c++;
                }
            }

            r = Math.Round(r / c);
            g = Math.Round(g / c);
            b = Math.Round(b / c);

            for (int iy = y; iy < bitmap.Height && iy < y + size; ++iy) {
                for (int ix = x; ix < bitmap.Width && ix < x + size; ++ix) {
                    buf[data.Stride * iy + (ix * 4) + 0] = (byte)r;
                    buf[data.Stride * iy + (ix * 4) + 1] = (byte)g;
                    buf[data.Stride * iy + (ix * 4) + 2] = (byte)b;
                }
            }
        }

        private void copyBtn_Click(object sender, EventArgs e)
        {
            if (this.mosaicBitmap?.Source != null) {
                Clipboard.SetImage(this.mosaicBitmap.Source);
            }
        }

        private void tileMinusBtn_Click(object sender, EventArgs e)
        {
            this.szindex--;
            this.tileMinusBtn.Enabled = (this.szindex > 0);
            this.tilePlusBtn.Enabled = true;
            this.Invalidate(new Rectangle(0, this.Height - 30, this.Width, 30));
        }

        private void tilePlusBtn_Click(object sender, EventArgs e)
        {
            this.szindex++;
            this.tileMinusBtn.Enabled = true;
            this.tilePlusBtn.Enabled = (this.szindex < mosaicTile.Length - 1);
            this.Invalidate(new Rectangle(0, this.Height - 30, this.Width, 30));
        }

        private void mainControl_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Control) {
                if (e.KeyCode == Keys.V) {
                    this.SetModifiImage();
                }
                else if (e.KeyCode == Keys.C) {
                    if (this.mosaicBitmap?.Source != null) {
                        Clipboard.SetImage(this.mosaicBitmap.Source);
                    }
                }
            }
        }

        private void mainControl_DragEnter(object sender, DragEventArgs e)
        {
            //コントロール内にドラッグされたとき実行される
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
                //ドラッグされたデータ形式を調べ、ファイルのときはコピーとする
                e.Effect = DragDropEffects.Copy;
            else
                //ファイル以外は受け付けない
                e.Effect = DragDropEffects.None;
        }

        private void mainControl_DragDrop(object sender, DragEventArgs e)
        {
            var fileName = (string[])e.Data.GetData(DataFormats.FileDrop, false);
            if (fileName.Length > 0 && System.IO.File.Exists(fileName[0])) {
                try {
                    var bitmap = new Bitmap(fileName[0]);
                    this.mainControl.Remove(BITMAP_NAME);
                    this.mosaicBitmap = this.mainControl.CreateBitmap(BITMAP_NAME, bitmap);
                    this.mainControl.Rebuild();
                    this.CalcScrollBar();
                }
                catch (Exception ex) {
                    MessageBox.Show(ex.Message, "エラー", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }
    }
}
