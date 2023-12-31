#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct BMPImagem
{
    int   width;
    int   height;
    char *data;
}BMPImage;

#define MAX_NO_TEXTURES 6

GLuint texture_id[MAX_NO_TEXTURES];

char* filenameArray[MAX_NO_TEXTURES] = {
        "earthTexture.bmp",
        "surface1.bmp",
        "surface2.bmp",
        "surface3.bmp",
        "surface4.bmp",
        "surface5.bmp"
};

GLUquadricObj *obj;

GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;

float angleBracoDireito = 0.0;
float angleBracoEsquerdo = 0.0;
float anglePernaDireita = 0.0;
float anglePernaEsquerda = 0.0;

float thetaX = 90.00;
float thetaY = 180.00;

void init() { //iluminação
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
  GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

  GLfloat material_specular[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat material_shininess[] = {50.0};

  glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

  glShadeModel(GL_FLAT);
}

void cubo() {
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_POLYGON);
  glVertex3f(-0.25, 0.25, 0.25);
  glVertex3f(0.25, 0.25, 0.25);
  glVertex3f(0.25, -0.25, 0.25);
  glVertex3f(-0.25, -0.25, 0.25);
  glEnd();

  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_POLYGON);
  glVertex3f(-0.25, 0.25, -0.25);
  glVertex3f(0.25, 0.25, -0.25);
  glVertex3f(0.25, -0.25, -0.25);
  glVertex3f(-0.25, -0.25, -0.25);
  glEnd();

  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_POLYGON);
  glVertex3f(0.25, -0.25, 0.25);
  glVertex3f(0.25, 0.25, 0.25);
  glVertex3f(0.25, 0.25, -0.25);
  glVertex3f(0.25, -0.25, -0.25);
  glEnd();

  glColor3f(1.0, 1.0, 0.0);
  glBegin(GL_POLYGON);
  glVertex3f(-0.25, -0.25, 0.25);
  glVertex3f(-0.25, 0.25, 0.25);
  glVertex3f(-0.25, 0.25, -0.25);
  glVertex3f(-0.25, -0.25, -0.25);
  glEnd();

  glColor3f(1.0, 0.0, 1.0);
  glBegin(GL_POLYGON);
  glVertex3f(-0.25, 0.25, 0.25);
  glVertex3f(0.25, 0.25, 0.25);
  glVertex3f(0.25, 0.25, -0.25);
  glVertex3f(-0.25, 0.25, -0.25);
  glEnd();

  glColor3f(0.0, 1.0, 1.0);
  glBegin(GL_POLYGON);
  glVertex3f(-0.25, -0.25, 0.25);
  glVertex3f(0.25, -0.25, 0.25);
  glVertex3f(0.25, -0.25, -0.25);
  glVertex3f(-0.25, -0.25, -0.25);
  glEnd();
}

void tronco() {
  glPushMatrix();
  glScalef(0.4, 0.4, 0.6);
  cubo();
  glPopMatrix();
}

void bracoDireito() {
  glPushMatrix();
  glTranslatef(0.15, 0.0, 0.0);
  glRotatef(angleBracoDireito, 1.0, 0.0, 0.0);
  glScalef(0.15, 0.15, 0.4);
  cubo();
  glPopMatrix();
}

void bracoEsquerdo() {
  glPushMatrix();
  glTranslatef(-0.15, 0.0, 0.0);
  glRotatef(angleBracoEsquerdo, 1.0, 0.0, 0.0);
  glScalef(0.15, 0.15, 0.4);
  cubo();
  glPopMatrix();
}

void pernaDireita() {
  glPushMatrix();
  glTranslatef(0.06, 0.0, -0.25);
  glRotatef(anglePernaDireita, 1.0, 0.0, 0.0);
  glScalef(0.15, 0.15, 0.4);
  cubo();
  glPopMatrix();
}

void pernaEsquerda() {
  glPushMatrix();
  glTranslatef(-0.06, 0.0, -0.25);
  glRotatef(anglePernaEsquerda, 1.0, 0.0, 0.0);
  glScalef(0.15, 0.15, 0.4);
  cubo();
  glPopMatrix();
}

void cabeca() {
  glPushMatrix();
  glTranslatef(0.0, 0.0, 0.2);
  glScalef(0.25, 0.25, 0.25);
  cubo() ;
  glPopMatrix();
}

void desenha() {
  glClearColor(1.3, 0.5, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glPushMatrix();

  glTranslatef(0.0, 0.0, 0.0);
  glRotatef(thetaX, 1.0, 0.0, 0.0);
  glRotatef(thetaY, 0.0, 1.0, 0.0);

  tronco();
  bracoDireito();
  bracoEsquerdo();
  pernaDireita();
  pernaEsquerda();
  cabeca();
  glPopMatrix();
  glFlush();
}

void tecladoEspecial(int tecla, int x, int y) {
  switch (tecla) {
  case GLUT_KEY_RIGHT:
    thetaY += 2;
    break;
  case GLUT_KEY_LEFT:
    thetaY -= 2;
    break;
  case GLUT_KEY_UP:
    thetaX += 2;
    break;
  case GLUT_KEY_DOWN:
    thetaX -= 2;
    break;
  case GLUT_KEY_F1:
    angleBracoDireito += 3.0;
    anglePernaDireita += 3.0;
  break;
  case GLUT_KEY_F2:
    angleBracoDireito -= 3.0;
    anglePernaDireita -= 3.0;
    break;
  case GLUT_KEY_F3:
    angleBracoEsquerdo += 3.0;
    anglePernaEsquerda += 3.0;
    break;
  case GLUT_KEY_F4:
    angleBracoEsquerdo -= 3.0;
    anglePernaEsquerda -= 3.0;
    break;
   default:
    break;
  }
  glutPostRedisplay();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400, 400);
  glutCreateWindow("Robo");
  glutDisplayFunc(desenha);
  glutSpecialFunc(tecladoEspecial);
  glutMainLoop();
  return 0;
}
