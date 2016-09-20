/*
	Copyright (c) 2016 Batuhan KINDAN
	Distributed under the MIT License.
	See License.txt or http://www.opensource.org/licenses/mit-license.php.
*/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Tao.OpenGl;
using Tao.Platform.Windows;

namespace spinningCube
{
    public partial class Form1 : Form
    {

        float spin = 0;

        public Form1()
        {
            InitializeComponent();
            openglPanel.InitializeContexts();
        }

        private void openglPanel_Paint(object sender, PaintEventArgs e)
        {
            draw();
        }

        public void draw()
        {
            Gl.glClearColor(0.255f, 0.412f, 0.882f, 0); // default background color
            Gl.glMatrixMode(Gl.GL_PROJECTION);
            Gl.glLoadIdentity();
            Gl.glViewport(0, 0, openglPanel.Width, openglPanel.Height); // dynamic viewport
            Gl.glOrtho(-openglPanel.Width / 2, openglPanel.Width / 2, -openglPanel.Height / 2, openglPanel.Height / 2, -300, 300); // dynamic origin alignment
            // Clear the Color and Depth Buffer
            Gl.glClear(Gl.GL_COLOR_BUFFER_BIT | Gl.GL_DEPTH_BUFFER_BIT);
            Gl.glClearDepth(1.0f);  // Set the Depth buffer value (ranges[0,1])
            Gl.glEnable(Gl.GL_DEPTH_TEST);  // Enable Depth test
            Gl.glDepthFunc(Gl.GL_LEQUAL);  // If two objects on the same coordinate 
            Gl.glHint(Gl.GL_PERSPECTIVE_CORRECTION_HINT, Gl.GL_NICEST);
            Gl.glEnable(Gl.GL_POLYGON_SMOOTH);
            Gl.glHint(Gl.GL_POLYGON_SMOOTH_HINT, Gl.GL_NICEST);

            Gl.glLineWidth(2);
            Gl.glPushMatrix();

            // rotating and scaling matrix before defining the cube
            Gl.glScaled(2, 2, 2);
            Gl.glRotatef(spin += 0.2f, 1.0f, 1.0f, 1.0f);
            Gl.glRotatef(spin += 0.2f, 0.0f, 0.0f, 1.0f);

            // defining cube
            Gl.glBegin(Gl.GL_POLYGON); // 1
            Gl.glColor3f(0.0f, 0.0f, 1.0f);
            Gl.glVertex3f(50.0f, 50.0f, 50.0f);
            Gl.glColor3f(1.0f, 0.0f, 0.0f);
            Gl.glVertex3f(50.0f, -50.0f, 50.0f);
            Gl.glColor3f(0.0f, 1.0f, 0.0f);
            Gl.glVertex3f(-50.0f, -50.0f, 50.0f);
            Gl.glColor3f(80.0f, 80.0f, 0.0f);
            Gl.glVertex3f(-50.0f, 50.0f, 50.0f);
            Gl.glEnd();
            Gl.glBegin(Gl.GL_POLYGON); // 2
            Gl.glColor3d(0.824, 0.412, 0.118);
            Gl.glVertex3f(50.0f, 50.0f, -50.0f);
            Gl.glVertex3f(50.0f, -50.0f, -50.0f);
            Gl.glVertex3f(-50.0f, -50.0f, -50.0f);
            Gl.glVertex3f(-50.0f, 50.0f, -50.0f);
            Gl.glEnd();
            Gl.glBegin(Gl.GL_POLYGON); // 3
            Gl.glColor3d(0.373, 0.620, 0.627);
            Gl.glVertex3f(50.0f, 50.0f, 50.0f);
            Gl.glVertex3f(50.0f, 50.0f, -50.0f);
            Gl.glVertex3f(50.0f, -50.0f, -50.0f);
            Gl.glVertex3f(50.0f, -50.0f, 50.0f);
            Gl.glEnd();
            Gl.glBegin(Gl.GL_POLYGON); // 4
            Gl.glColor3d(0.184, 0.310, 0.310);
            Gl.glVertex3f(-50.0f, 50.0f, 50.0f);
            Gl.glVertex3f(-50.0f, -50.0f, 50.0f);
            Gl.glVertex3f(-50.0f, -50.0f, -50.0f);
            Gl.glVertex3f(-50.0f, 50.0f, -50.0f);
            Gl.glEnd();
            Gl.glBegin(Gl.GL_POLYGON); // 5
            Gl.glColor3d(0.196, 0.804, 0.196);
            Gl.glVertex3f(50.0f, 50.0f, 50.0f);
            Gl.glVertex3f(50.0f, 50.0f, -50.0f);
            Gl.glVertex3f(-50.0f, 50.0f, -50.0f);
            Gl.glVertex3f(-50.0f, 50.0f, 50.0f);
            Gl.glEnd();
            Gl.glBegin(Gl.GL_POLYGON); // 6
            Gl.glColor3d(0.467, 0.533, 0.600);
            Gl.glVertex3f(50.0f, -50.0f, 50.0f);
            Gl.glVertex3f(50.0f, -50.0f, -50.0f);
            Gl.glVertex3f(-50.0f, -50.0f, -50.0f);
            Gl.glVertex3f(-50.0f, -50.0f, 50.0f);
            Gl.glEnd();

            Gl.glPopMatrix();

            openglPanel.Invalidate();
        }

        

    }
}

