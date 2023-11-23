#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float thetaX = 90.00;
float thetaY = 180.00;

void cubo() {
  glColor3f(1.0, 0.0, 0.0);
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
  glScalef(0.15, 0.15, 0.4);
  cubo();
  glPopMatrix();
}

void bracoEsquerdo() {
  glPushMatrix();
  glTranslatef(-0.15, 0.0, 0.0);
  glScalef(0.15, 0.15, 0.4);
  cubo();
  glPopMatrix();
}

void pernaDireita() {
  glPushMatrix();
  glTranslatef(0.06, 0.0, -0.25);
  glScalef(0.15, 0.15, 0.4);
  cubo();
  glPopMatrix();
}

void pernaEsquerda() {
  glPushMatrix();
  glTranslatef(-0.06, 0.0, -0.25);
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
  glClearColor(0, 0, 0, 0);
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
To add lighting to your code, you need to enable lighting, set up light sources, and specify material properties. Here's a modified version of your code with basic lighting:

```c
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float thetaX = 90.00;
float thetaY = 180.00;

void init() {
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

  glShadeModel(GL_FLAT);
}

void cubo() {
  // ... (same as before)
}

void tronco() {
  glPushMatrix();
  glScalef(0.4, 0.4, 0.6);
  cubo();
  glPopMatrix();
}

// ... (other body parts functions)

void desenha() {
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
  // ... (same as before)
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400, 400);
  glutCreateWindow("Robo");

  init(); // Initialize lighting

  glutDisplayFunc(desenha);
  glutSpecialFunc(tecladoEspecial);
  glutMainLoop();
  return 0;
}
```

This code initializes lighting, sets up a basic light source, and enables color material for shading. Keep in mind that this is a simple setup, and you might want to explore more advanced lighting techniques based on your specific requirements.
To implement animation for the arms and legs using the 'a' and 'd' keys, you can modify the functions `bracoDireito()`, `bracoEsquerdo()`, `pernaDireita()`, and `pernaEsquerda()` to include rotation angles controlled by global variables. Here's the modified code:

```c
// Declare global variables for animation control
float angleBracoDireito = 0.0;
float angleBracoEsquerdo = 0.0;
float anglePernaDireita = 0.0;
float anglePernaEsquerda = 0.0;

// ... (other functions)

void bracoDireito() {
  glPushMatrix();
  glTranslatef(0.15, 0.0, 0.0);
  glRotatef(angleBracoDireito, 1.0, 0.0, 0.0);  // Rotate around x-axis
  glScalef(0.15, 0.15, 0.4);
  cubo();
  glPopMatrix();
}

void bracoEsquerdo() {
  glPushMatrix();
  glTranslatef(-0.15, 0.0, 0.0);
  glRotatef(angleBracoEsquerdo, 1.0, 0.0, 0.0);  // Rotate around x-axis
  glScalef(0.15, 0.15, 0.4);
  cubo();
  glPopMatrix();
}

void pernaDireita() {
  glPushMatrix();
  glTranslatef(0.06, 0.0, -0.25);
  glRotatef(anglePernaDireita, 1.0, 0.0, 0.0);  // Rotate around x-axis
  glScalef(0.15, 0.15, 0.4);
  cubo();
  glPopMatrix();
}

void pernaEsquerda() {
  glPushMatrix();
  glTranslatef(-0.06, 0.0, -0.25);
  glRotatef(anglePernaEsquerda, 1.0, 0.0, 0.0);  // Rotate around x-axis
  glScalef(0.15, 0.15, 0.4);
  cubo();
  glPopMatrix();
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
    default:
      break;
  }

  glutPostRedisplay();
}

void tecladoNormal(unsigned char key, int x, int y) {
  switch (key) {
    case 'a':
      // Increment the rotation angle for left arm and left leg
      angleBracoEsquerdo += 5.0;
      anglePernaEsquerda += 5.0;
      break;
    case 'd':
      // Increment the rotation angle for right arm and right leg
      angleBracoDireito += 5.0;
      anglePernaDireita += 5.0;
      break;
    default:
      break;
  }

  glutPostRedisplay();
}

int main(int argc, char *argv[]) {
  // ... (other setup code)

  glutKeyboardFunc(tecladoNormal);

  // ... (rest of the main function)
}
```

This code introduces new global variables to control the rotation angles of the arms and legs. The `tecladoNormal` function is added to handle the 'a' and 'd' keys and update the rotation angles accordingly. The modified arm and leg drawing functions now include rotations based on these angles.
