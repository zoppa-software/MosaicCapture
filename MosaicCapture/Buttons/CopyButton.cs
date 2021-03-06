﻿using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MosaicCapture.Buttons
{
    public sealed class CopyButton
        : Dwm.CustomDrawButton
    {
        private Bitmap image;

        public CopyButton()
        {
            this.image = Properties.Resources.copy;
        }

        public override int SquareLength => 48;

        protected override void DrawMethod(Graphics g, SolidBrush brh, int lft, int top)
        {
            g.DrawImage(this.image, 0, 0, this.image.Width, this.image.Height);
        }
    }
}
