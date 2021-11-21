// #include<windows.h>
//#ifdef __APPLE__
//#include <GLUT/glut.h>
//#else
#include <GL/glut.h>
//#endif

#include <stdio.h>
// #include <iostream>
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

void DDA(float x1, float y1, float x2, float y2, float z){
    float steps;
    float x = x1;
    float y = y1;

    if(abs(x2-x1) >= abs(y2-y1))
        steps = abs(x2-x1);
    else
        steps = abs(y2-y1);

    float dx = abs(x2-x1)/steps;
    float dy = abs(y2-y1)/steps;
    //std::cout << dx << "\n";
    //std::cout << dy << "\n";

    glBegin(GL_LINE_STRIP);
        for(int i=0; i<=steps; i++){
            // std::cout << round(x) << ", ";
      //   std::cout << round(y) << "\n";
            glVertex3f(round(x), round(y), z);
            x += dx;
            y += dy;
        }
    glEnd();

    glFlush();
}

void Scale(float sx,float sy,float sz) {
   float matriz[4][4] = {{1,0,0,0},
                      {0,1,0,0},
                      {0,0,1,0},
                      {0,0,0,1}};
   matriz[0][0] = sx;                         
   matriz[1][1] = sy;                         
   matriz[2][2] = sz;                         
   Transposta(matriz);
   glMultMatrixf((float *) matriz);
}

struct TipoPontos {
  float x, y, z;
};

void Lighting(){
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);
    //glShadeModel(GL_FLAT);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
   //  glEnable(GL_DEPTH_TEST);
}

void reduzParaUnitario( TipoPontos *vector ){
   GLfloat length;

   // Calculate the length of the vector
   length = (GLfloat) sqrt((vector->x * vector->x) +
                           (vector->y * vector->y) +
                           (vector->z * vector->z));

   // Keep the program from blowing up by providing an exceptable
   // value for vectors that may calculated too close to zero.
   if (length == 0.0f)
      length =  1.0f;

   // Dividing each element by the length will result in a
   // unit normal vector.
   vector->x = vector->x / length;
   vector->y = vector->y / length;
   vector->z = vector->z / length;
}

void calculaNormal(TipoPontos p1,
                TipoPontos      p2,
                TipoPontos      p3,
                TipoPontos      *retorno        )

/* Assume que p1, p2, & p3 estão especificados em        */
/* sentido anti-horario. Se voce passar os parametros em */
/* outra ordem, o vetor vai apontar para o lado errado.  */
/* ===================================================== */
   {
   TipoPontos v1,v2;

   // Calcula dois vetores a partir dos tres pontos.
   v1.x = p1.x - p2.x;
   v1.y = p1.y - p2.y;
   v1.z = p1.z - p2.z;

   v2.x = p2.x - p3.x;
   v2.y = p2.y - p3.y;
   v2.z = p2.z - p3.z;

   // Take the cross product of the two vectors to get
   // the normal vector which will be stored in out
   retorno->x = v1.y * v2.z - v1.z * v2.y;
   retorno->y = v1.z * v2.x - v1.x * v2.z;
   retorno->z = v1.x * v2.y - v1.y * v2.x;

   // Normaliza o vector, reduzindo comprimento para um
   reduzParaUnitario(retorno);
   }


void hexagono3d(double radius, double z1, double z2, GLfloat frontColor[], GLfloat sideColor[], GLfloat backColor[]){
   const int sides = 6;  // The amount of segment to create the circle
   double heading;
   TipoPontos normal, p1, p2, p3;
   int cont;

   // Translate(0, 0, +(z1 + (z2-z1)/2) );
   // RotateY(45);
   // Translate(0, 0, -(z1 + (z2-z1)/2) );
   // printf("z: %f", -(z1 + (z2-z1)/2));
   // RotateZ(30);
   glColor3f(sideColor[0], sideColor[1], sideColor[2]);

   glBegin(GL_QUAD_STRIP); // faces laterais
   for (int a = 0; a <= 360; a += 360 / sides)
   {
      heading = a * 3.1415926535897932384626433832795 / 180;
      p1.x = cos(heading) * radius;
      p1.y = sin(heading) * radius;
      p1.z = z1;
      p2.x = cos(heading) * radius;
      p2.y = sin(heading) * radius;
      p2.z = z2;
      glVertex3f(p1.x, p1.y, z1);
      glVertex3f(p2.x, p2.y, z2);
      heading = (a + 360 / sides) * 3.1415926535897932384626433832795 / 180;
      p3.x = cos(heading) * radius;
      p3.y = sin(heading) * radius;
      p3.z = z1;

      calculaNormal(p1, p2, p3, &normal);
      glNormal3f(normal.x, normal.y, normal.z);
   }
   glEnd();

   // glPushMatrix();
   glColor3f(sideColor[0], sideColor[1], sideColor[2]);
   // glPopMatrix();
   glBegin(GL_POLYGON); // face da frente
   cont = 0;
   for (int a = 0; a <= 360; a += 360 / sides)
   {
      heading = a * 3.1415926535897932384626433832795 / 180;
      cont++;
      switch (cont)
      {
      case 1:
         p1.x = cos(heading) * radius;
         p1.y = sin(heading) * radius;
         p1.z = z1;
         break;
      case 2:
         p2.x = cos(heading) * radius;
         p2.y = sin(heading) * radius;
         p2.z = z1;
         break;
      case 3:
         p3.x = cos(heading) * radius;
         p3.y = sin(heading) * radius;
         p3.z = z1;
         break;
      } 
      glVertex3f(cos(heading) * radius, sin(heading) * radius, z1);
   }
   calculaNormal(p1, p2, p3, &normal);
   glNormal3f(normal.x, normal.y, normal.z);
   // printf("x: %f  y: %f  z: %f", normal.x, normal.y, normal.z);
   glEnd();

   // glPushMatrix();
   glColor3f(sideColor[0], sideColor[1], sideColor[2]);
   // glPopMatrix();
   glBegin(GL_POLYGON); // face da trás
   cont = 0;
   for (int a = 0; a <= 360; a += 360 / sides)
   {
      heading = a * 3.1415926535897932384626433832795 / 180;
      cont++;
      switch (cont)
      {
      case 1:
         p1.x = cos(heading) * radius;
         p1.y = sin(heading) * radius;
         p1.z = z2;
         break;
      case 2:
         p2.x = cos(heading) * radius;
         p2.y = sin(heading) * radius;
         p2.z = z2;
         break;
      case 3:
         p3.x = cos(heading) * radius;
         p3.y = sin(heading) * radius;
         p3.z = z2;
         break;
      } 
      glVertex3f(cos(heading) * radius, sin(heading) * radius, z2);
   }
   calculaNormal(p1, p2, p3, &normal);
   glNormal3f(normal.x, normal.y, normal.z);
   // printf("x: %f  y: %f  z: %f", normal.x, normal.y, normal.z);
   glEnd();
   
   // glLoadIdentity();
}

void display(void){
   glClearColor(1.0, 1.0, 1.0, 0.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glColor3f(0.0, 0.0, 0.0);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glClearDepth(1000.0f);
   // Lighting();

   // float z_coord_lines = -3;
   // // eixo x
   // glColor3f(1, 0, 0);
   // linha(-40, 0, z_coord_lines, 40, 0, z_coord_lines, 2);
   // // eixo y
   // glColor3f(0, 1, 0);
   // linha(0, -40, z_coord_lines, 0, 40, z_coord_lines, 2);
   // // eixo z
   // glColor3f(0, 0, 1);
   // linha(0, 0, -40, 0, 0, 40, 2);

   // DDA(2, 3, 6, 7, -3);

   glLoadIdentity();
   float z1 = -5, z2 = -7;

   Translate(0, 0, +(z1 + (z2-z1)/2) );
   RotateY(45);
   Translate(0, 0, -(z1 + (z2-z1)/2) );
   
   RotateZ(30);
   // Scale(0.5, 1, 0.5);

   GLfloat hexColor1[] = {0.5, 0.5, 0.5};
   GLfloat hexColor2[] = {1.0, 1.0, 1.0};
   GLfloat hexColor3[] = {0.0, 0.0, 0.5};
   GLfloat hexColor4[] = {0.0, 0.0, 0.8};
   GLfloat hexColor5[] = {1.0, 1.0, 1.0};
   GLfloat hexColor6[] = {0.5, 0.5, 0.5};
   GLfloat hexColor7[] = {1.0, 1.0, 1.0};
   GLfloat hexColor8[] = {0.0, 0.0, 0.8};
   GLfloat hexColor9[] = {1.0, 1.0, 1.0};

   // float radius[9] = {3.5, 3.4, 3.2, 2.9, 2.0, 1.8, 1.3, 1.1, 0.8};

   hexagono3d(3.5, -5.0, -7.0, hexColor1, hexColor1, hexColor1);
   hexagono3d(3.4, -4.99, -7.01, hexColor2, hexColor2, hexColor2);
   hexagono3d(3.2, -4.98, -7.02, hexColor3, hexColor3, hexColor3);
   hexagono3d(2.9, -4.97, -7.03, hexColor4, hexColor4, hexColor4);
   hexagono3d(2.0, -4.96, -7.04, hexColor5, hexColor5, hexColor5);
   hexagono3d(1.8, -4.95, -7.05, hexColor6, hexColor6, hexColor6);
   hexagono3d(1.3, -4.94, -7.06, hexColor7, hexColor7, hexColor7);
   hexagono3d(1.1, -4.93, -7.07, hexColor8, hexColor8, hexColor8);
   hexagono3d(0.8, -4.92, -7.08, hexColor9, hexColor9, hexColor9);

   glColor3f(1.0, 1.0, 1.0);
   linha(0.0, 0.0, -4.90, 3.5, 0.0, -4.98, 4.5);
   linha(0.0, 0.0, -4.90, -1.75, 3.05, -4.98, 4.5);
   linha(0.0, 0.0, -4.90, -1.75, -3.05, -4.98, 4.5);

   glFlush();
}

void reshape(int w, int h) {
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   // glFrustum(-10.0, 10.0, -10.0, 10.0, 1.5, 20.0);
   // Frustum(-10.0, 10.0, -10.0, 10.0, 1.5, 20.0);

   // glOrtho(-10.0, 10.0, -10.0, 10.0, -10, 200.0);
   Ortho(-10.0, 10.0, -10.0, 10.0, -10, 200.0);
   glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv){
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(1000, 1000);
   glutInitWindowPosition(10, 10);
   glutCreateWindow(argv[0]);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMainLoop();
   return 0;
}
