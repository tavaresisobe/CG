Claro, aqui está o código completo com a implementação das rotações nos membros do robô:

```c
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float thetaX = 0.0;
float thetaY = 0.0;
float anguloBracoDireito = 0.0;
float anguloBracoEsquerdo = 0.0;
float anguloPernaDireita = 0.0;
float anguloPernaEsquerda = 0.0;

void cubo() {
  // Função cubo() permanece a mesma
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
  glRotatef(anguloBracoDireito, 1.0, 0.0, 0.0); // Rotação no braço direito
  glScalef(0.15, 0.15, 0.4);
  cubo();
  glPopMatrix();
}

void bracoEsquerdo() {
  glPushMatrix();
  glTranslatef(-0.15, 0.0, 0.0);
  glRotatef(anguloBracoEsquerdo, 1.0, 0.0, 0.0); // Rotação no braço esquerdo
  glScalef(0.15, 0.15, 0.4);
  cubo();
  glPopMatrix();
}

void pernaDireita() {
  glPushMatrix();
  glTranslatef(0.06, 0.0, -0.25);
  glRotatef(anguloPernaDireita, 1.0, 0.0, 0.0); // Rotação na perna direita
  glScalef(0.15, 0.15, 0.4);
  cubo();
  glPopMatrix();
}

void pernaEsquerda() {
  glPushMatrix();
  glTranslatef(-0.06, 0.0, -0.25);
  glRotatef(anguloPernaEsquerda, 1.0, 0.0, 0.0); // Rotação na perna esquerda
  glScalef(0.15, 0.15, 0.4);
  cubo();
  glPopMatrix();
}

void cabeca() {
  glPushMatrix();
  glTranslatef(0.0, 0.0, 0.2);
  glScalef(0.25, 0.25, 0.25);
  cubo();
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
  case GLUT_KEY_PAGE_UP:
    anguloBracoDireito += 2; // Aumenta o ângulo do braço direito
    break;
  case GLUT_KEY_PAGE_DOWN:
    anguloBracoDireito -= 2; // Diminui o ângulo do braço direito
    break;
  case GLUT_KEY_HOME:
    anguloBracoEsquerdo += 2; // Aumenta o ângulo do braço esquerdo
    break;
  case GLUT_KEY_END:
    anguloBracoEsquerdo -= 2; // Diminui o ângulo do braço esquerdo
    break;
  case GLUT_KEY_INSERT:
    anguloPernaDireita += 2; // Aumenta o ângulo da perna direita
    break;
  case GLUT_KEY_DELETE:
    anguloPernaDireita -= 2; // Diminui o ângulo da perna direita
    break;
  case GLUT_KEY_F1:
    anguloPernaEsquerda += 2; // Aumenta o ângulo da perna esquerda
    break;
  case GLUT_KEY_F2:
    anguloPernaEsquerda -= 2; // Diminui o ângulo da perna esquerda
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
```

Agora o código completo inclui a implementação das rotações nos braços direito e esquerdo, bem como nas pernas esquerda e direita do robô. Você pode controlar essas rotações usando as teclas direcionais e as teclas de função, conforme explicado anteriormente.
