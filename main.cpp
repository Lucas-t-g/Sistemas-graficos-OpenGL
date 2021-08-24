// #include<windows.h>
//#ifdef __APPLE__
//#include <GLUT/glut.h>
//#else
#include <GL/glut.h>
//#endif

#include <stdlib.h>
#include <math.h>

void Transposta(float matriz[4][4]){

   float aux;
   for (int i = 0; i < 4; i++) {
      for (int j = i; j >= 0;j--) {
          aux = matriz[i][j];
          matriz[i][j] = matriz[j][i];
          matriz[j][i] = aux;
      }
   }
}

void RotateZ(float ang) {
   float matriz[4][4] = {{1,0,0,0},
                      {0,1,0,0},
                      {0,0,1,0},
                      {0,0,0,1}};

   matriz[0][0] = cos(ang*M_PI/180.0);
   matriz[0][1] = -sin(ang*M_PI/180.0);
   matriz[1][0] = sin(ang*M_PI/180.0);
   matriz[1][1] = cos(ang*M_PI/180.0);
   Transposta(matriz);
   glMultMatrixf((float *) matriz);
}

void RotateY(float ang) {
float matriz[4][4] = {{1,0,0,0},
                      {0,1,0,0},
                      {0,0,1,0},
                      {0,0,0,1}};
   matriz[0][0] = cos(ang*M_PI/180);
   matriz[0][2] = sin(ang*M_PI/180);
   matriz[2][0] = -sin(ang*M_PI/180);
   matriz[2][2] = cos(ang*M_PI/180);
   Transposta(matriz);
   glMultMatrixf((float *) matriz);
}

void RotateX(float ang) {
   float matriz[4][4] = {{1,0,0,0},
                      {0,1,0,0},
                      {0,0,1,0},
                      {0,0,0,1}};
   matriz[1][1] = cos(ang*M_PI/180);                         
   matriz[1][2] = -sin(ang*M_PI/180);                         
   matriz[2][1] = sin(ang*M_PI/180);                         
   matriz[2][2] = cos(ang*M_PI/180);                         
   Transposta(matriz);
   glMultMatrixf((float *) matriz);
}

void Translate(float dx, float dy, float dz) {
   float matriz[4][4] = {{1,0,0,0},
                      {0,1,0,0},
                      {0,0,1,0},
                      {0,0,0,1}};
   matriz[0][3] = dx;
   matriz[1][3] = dy;
   matriz[2][3] = dz;
   Transposta(matriz);
   glMultMatrixf((float *) matriz);
}

void Frustum(float l, float r, float b, float t, float n, float f){
    float matriz[4][4] = {{0,0,0,0},
                      {0,0,0,0},
                      {0,0,0,0},
                      {0,0,0,0}};

    matriz[0][0] = 2*n/(r-l);
    matriz[1][1] = 2*n/(t-b);
    matriz[2][0] = (r+l)/(r-l);
    matriz[2][1] = (t+b)/(t-b);
    matriz[2][2] = -(f+n)/(f-n);
    matriz[2][3] = -1;
    matriz[3][2] = -2*f*n/(f-n);

    glMultMatrixf((float *) matriz);
}

void Ortho(float l, float r, float b, float t, float n, float f){
    float matriz[4][4] = {{0,0,0,0},
                      {0,0,0,0},
                      {0,0,0,0},
                      {0,0,0,0}};

    matriz[0][0] = 2/(r-l);
    matriz[1][1] = 2/(t-b);
    matriz[2][2] = -2/(f-n);
    matriz[3][0] = -(r+l)/(r-l);
    matriz[3][1] = -(t+b)/(t-b);
    matriz[3][2] = -(f+n)/(f-n);
    matriz[3][3] = 1;

    glMultMatrixf((float *) matriz);
}

void display(void){
   glClearColor(1.0, 1.0, 1.0, 0.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glColor3f(0.0, 0.0, 0.0);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glClearDepth(1000.0f);
   glLoadIdentity();
   RotateZ(30);
   // float x_desloc = -2.0, y_desloc = -1.5;
   // glBegin(GL_LINE_LOOP);
   //    glVertex3f(x_desloc+ (-1.0), y_desloc+ (0.0), -2.0); // C
   //    glVertex3f(x_desloc+ (-1.0), y_desloc+ (3.0), -2.0); // B
   //    glVertex3f(x_desloc+ (2.0), y_desloc+ (5.0), -2.0); // A
   //    glVertex3f(x_desloc+ (5.0), y_desloc+ (3.0), -2.0); // F
   //    glVertex3f(x_desloc+ (5.0), y_desloc+ (0.0), -2.0); // E
   //    glVertex3f(x_desloc+ (2.0), y_desloc+ (-2.0), -2.0); // D
   //    glVertex3f(x_desloc+ (-1.0), y_desloc+ (0.0), -2.0); // C

   //    glVertex3f(x_desloc+ (-1.0), y_desloc+ (0.0), -3.0); // C
   //    glVertex3f(x_desloc+ (2.0), y_desloc+ (-2.0), -3.0); // D
   //    glVertex3f(x_desloc+ (5.0), y_desloc+ (0.0), -3.0); // E
   //    glVertex3f(x_desloc+ (5.0), y_desloc+ (3.0), -3.0); // F
   //    glVertex3f(x_desloc+ (2.0), y_desloc+ (5.0), -3.0); // A
   //    glVertex3f(x_desloc+ (-1.0), y_desloc+ (3.0), -3.0); // B
   //    glVertex3f(x_desloc+ (-1.0), y_desloc+ (0.0), -3.0); // C
   // glEnd();

   // glPushMatrix();
   // glTranslatef(0.0, 0.0, -1.0);
   // glutWireCube(7.0);
   // glPopMatrix();

   // glPushMatrix();
   // glTranslatef(0.0, 0.0, -1.0);
   // glutWireCube(6.0);
   // glPopMatrix();

   const int sides = 200;  // The amount of segment to create the circle
   const double radius = 3.5; // The radius of the circle

   glBegin(GL_LINE_LOOP);

   for (int a = 0; a < 360; a += 360 / sides)
   {
      double heading = a * 3.1415926535897932384626433832795 / 180;
      glVertex2d(cos(heading) * radius, sin(heading) * radius);
   }

   glEnd();

   const int sides2 = 6;  // The amount of segment to create the circle
   const double radius2 = 3.5; // The radius of the circle

   glBegin(GL_LINE_LOOP);

   for (int a = 0; a < 360; a += 360 / sides2)
   {
      double heading = a * 3.1415926535897932384626433832795 / 180;
      glVertex2d(cos(heading) * radius2, sin(heading) * radius2);
   }

   glEnd();

   glFlush();
}

void reshape(int w, int h) {
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   // glFrustum(-10.0, 10.0, -10.0, 10.0, 1.5, 20.0);
   // Frustum(-20.0, 20.0, -20.0, 20.0, 1.5, 40.0);

   // glOrtho(-10.0, 10.0, -10.0, 10.0, -1.5, 200.0);
   Ortho(-10.0, 10.0, -10.0, 10.0, -1.5, 200.0);
   glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv){
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(1000, 1000);
   glutInitWindowPosition(10, 10);
   glutCreateWindow(argv[0]);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMainLoop();
   return 0;
}
