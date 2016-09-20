namespace spinningCube
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.openglPanel = new Tao.Platform.Windows.SimpleOpenGlControl();
            this.SuspendLayout();
            // 
            // openglPanel
            // 
            this.openglPanel.AccumBits = ((byte)(0));
            this.openglPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.openglPanel.AutoCheckErrors = false;
            this.openglPanel.AutoFinish = false;
            this.openglPanel.AutoMakeCurrent = true;
            this.openglPanel.AutoSwapBuffers = true;
            this.openglPanel.BackColor = System.Drawing.Color.Black;
            this.openglPanel.ColorBits = ((byte)(32));
            this.openglPanel.DepthBits = ((byte)(16));
            this.openglPanel.Location = new System.Drawing.Point(12, 12);
            this.openglPanel.Name = "openglPanel";
            this.openglPanel.Size = new System.Drawing.Size(620, 519);
            this.openglPanel.StencilBits = ((byte)(0));
            this.openglPanel.TabIndex = 0;
            this.openglPanel.Paint += new System.Windows.Forms.PaintEventHandler(this.openglPanel_Paint);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(644, 543);
            this.Controls.Add(this.openglPanel);
            this.Name = "Form1";
            this.Text = "Monitor";
            this.ResumeLayout(false);

        }

        #endregion

        private Tao.Platform.Windows.SimpleOpenGlControl openglPanel;
    }
}

