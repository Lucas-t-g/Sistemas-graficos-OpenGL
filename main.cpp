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

void linha(float x1, float y1, float z1, float x2, float y2, float z2, float espessura){
   glLineWidth(espessura);
   glBegin(GL_LINES);
      glVertex3f(x1, y1, z1);
      glVertex3f(x2, y2, z2);
   glEnd();
}

void hexagono3d(){
   RotateY(10);
   RotateZ(30);
   glColor3f(0.0, 0.0, 1.0);

   float z1 = -3, z2 = -5;
   const int sides2 = 6;  // The amount of segment to create the circle
   const double radius2 = 3.5; // The radius of the circle
   glBegin(GL_QUAD_STRIP); // faces laterais
   for (int a = 0; a <= 360; a += 360 / sides2)
   {
      double heading = a * 3.1415926535897932384626433832795 / 180;
      glVertex3f(cos(heading) * radius2, sin(heading) * radius2, z1);
      glVertex3f(cos(heading) * radius2, sin(heading) * radius2, z2);
   }
   glEnd();

   // // glPushMatrix();
   // glColor3f(0.0, 0.0, 0.5);
   // // glPopMatrix();
   // glBegin(GL_POLYGON); // face da frente
   // for (int a = 0; a <= 360; a += 360 / sides2)
   // {
   //    double heading = a * 3.1415926535897932384626433832795 / 180;
   //    glVertex3f(cos(heading) * radius2, sin(heading) * radius2, z1);
   // }
   // glEnd();

   // // glPushMatrix();
   // glColor3f(0.5, 0.0, 0.5);
   // // glPopMatrix();
   // glBegin(GL_POLYGON); // face da trás
   // for (int a = 0; a <= 360; a += 360 / sides2)
   // {
   //    double heading = a * 3.1415926535897932384626433832795 / 180;
   //    glVertex3f(cos(heading) * radius2, sin(heading) * radius2, z2);
   // }
   // glEnd();
}

void display(void){
   glClearColor(1.0, 1.0, 1.0, 0.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glColor3f(0.0, 0.0, 0.0);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glClearDepth(1000.0f);
   // eixo x
   glColor3f(1, 0, 0);
   linha(-40, 0, 0, 40, 0, 0, 2);
   // eixo y
   glColor3f(0, 1, 0);
   linha(0, -40, 0, 0, 40, 0, 2);
   // eixo z
   glColor3f(0, 0, 1);
   linha(0, 0, -40, 0, 0, 40, 2);


   glLoadIdentity();
   
   hexagono3d();

   glFlush();
}

void reshape(int w, int h) {
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   // glFrustum(-10.0, 10.0, -10.0, 10.0, 1.5, 20.0);
   // Frustum(-20.0, 20.0, -20.0, 20.0, 1.5, 40.0);

   // glOrtho(-10.0, 10.0, -10.0, 10.0, -1.5, 200.0);
   Ortho(-10.0, 10.0, -10.0, 10.0, -5, 200.0);
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
