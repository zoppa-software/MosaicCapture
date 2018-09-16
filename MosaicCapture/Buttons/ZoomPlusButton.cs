using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MosaicCapture.Buttons
{
    public sealed class ZoomPlusButton
        : Dwm.CustomDrawButton
    {
        private SolidBrush brush;

        public ZoomPlusButton()
        {
            this.brush = new SolidBrush(Color.Black);
        }

        protected override void Dispose(bool flag)
        {
            base.Dispose(flag);
            if (this.brush != null) {
                this.brush.Dispose();
                this.brush = null;
            }
        }

        public override int SquareLength => 26;

        protected override void DrawMethod(Graphics g, SolidBrush brh, int lft, int top)
        {
            this.brush.Color = this.Enabled ? this.EnableColor : this.NotEnableColor;
            g.FillRectangle(this.brush, 7, 3, 2, 10);
            g.FillRectangle(this.brush, 3, 7, 10, 2);
        }
    }
}
