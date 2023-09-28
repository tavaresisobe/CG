#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float thetaX = 0.0;
float thetaY = 0.0;

void cubo() {
  // Função cubo permanece a mesma
  // ...
}

void tronco() {
  glPushMatrix();
  glScalef(0.4, 0.4, 0.6);
  cubo();
  glPopMatrix();
}

void bracoDireito() {
  glPushMatrix();
  glTranslatef(0.3, 0.0, 0.4);
  glScalef(0.15, 0.15, 0.4);
  cubo();
  glPopMatrix();
}

void bracoEsquerdo() {
  glPushMatrix();
  glTranslatef(-0.3, 0.0, 0.4);
  glScalef(0.15, 0.15, 0.4);
  cubo();
  glPopMatrix();
}

void pernaDireita() {
  glPushMatrix();
  glTranslatef(0.2, 0.0, -0.4);
  glScalef(0.15, 0.15, 0.4);
  cubo();
  glPopMatrix();
}

void pernaEsquerda() {
  glPushMatrix();
  glTranslatef(-0.2, 0.0, -0.4);
  glScalef(0.15, 0.15, 0.4);
  cubo();
  glPopMatrix();
}

void cabeca() {
  glPushMatrix();
  glTranslatef(0.0, 0.0, 0.8);
  glScalef(0.3, 0.3, 0.3);
  glutSolidSphere(1.0, 20, 20);
  glPopMatrix();
}

void desenha() {
  // Restante da função desenha permanece a mesma
  // ...

  // Criação do tronco do robô
  glPushMatrix();
  glRotatef(thetaX, 1.0, 0.0, 0.0);
  glRotatef(thetaY, 0.0, 1.0, 0.0);
  tronco();
  glPopMatrix();

  // Criação dos braços do robô
  glPushMatrix();
  glRotatef(thetaX, 1.0, 0.0, 0.0);
  glRotatef(thetaY, 0.0, 1.0, 0.0);
  bracoDireito();
  bracoEsquerdo();
  glPopMatrix();

  // Criação das pernas do robô
  glPushMatrix();
  glRotatef(thetaX, 1.0, 0.0, 0.0);
  glRotatef(thetaY, 0.0, 1.0, 0.0);
  pernaDireita();
  pernaEsquerda();
  glPopMatrix();

  // Criação da cabeça do robô
  glPushMatrix();
  glRotatef(thetaX, 1.0, 0.0, 0.0);
  glRotatef(thetaY, 0.0, 1.0, 0.0);
  cabeca();
  glPopMatrix();

  glFlush();
}

int main(int argc, char *argv[]) {
  // Restante da função main permanece a mesma
  // ...

  glutMainLoop();
  return 0;
}
```

Neste exemplo, foram adicionadas funções separadas para criar cada parte do robô, incluindo o tronco, braços direito e esquerdo, pernas direita e esquerda e a cabeça. As partes são posicionadas e dimensionadas usando as transformações apropriadas. Você pode continuar personalizando e expandindo o robô de acordo com suas necessidades.Claro! Aqui está uma versão expandida do código com funções para criar o tronco, braços direito e esquerdo, pernas direita e esquerda, e a cabeça de um robô simples. Lembre-se de que este é apenas um exemplo básico, e você pode personalizá-lo e adicionar mais detalhes conforme desejar.

```c
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float thetaX = 0.0;
float thetaY = 0.0;

void cubo() {
  // Função cubo permanece a mesma
  // ...
}

void tronco() {
  glPushMatrix();
  glScalef(0.4, 0.4, 0.6);
  cubo();
  glPopMatrix();
}

void bracoDireito() {
  glPushMatrix();
  glTranslatef(0.3, 0.0, 0.4);
  glScalef(0.15, 0.15, 0.4);
  cubo();
  glPopMatrix();
}

void bracoEsquerdo() {
  glPushMatrix();
  glTranslatef(-0.3, 0.0, 0.4);
  glScalef(0.15, 0.15, 0.4);
  cubo();
  glPopMatrix();
}

void pernaDireita() {
  glPushMatrix();
  glTranslatef(0.2, 0.0, -0.4);
  glScalef(0.15, 0.15, 0.4);
  cubo();
  glPopMatrix();
}

void pernaEsquerda() {
  glPushMatrix();
  glTranslatef(-0.2, 0.0, -0.4);
  glScalef(0.15, 0.15, 0.4);
  cubo();
  glPopMatrix();
}

void cabeca() {
  glPushMatrix();
  glTranslatef(0.0, 0.0, 0.8);
  glScalef(0.3, 0.3, 0.3);
  glutSolidSphere(1.0, 20, 20);
  glPopMatrix();
}

void desenha() {
  // Restante da função desenha permanece a mesma
  // ...

  // Criação do tronco do robô
  glPushMatrix();
  glRotatef(thetaX, 1.0, 0.0, 0.0);
  glRotatef(thetaY, 0.0, 1.0, 0.0);
  tronco();
  glPopMatrix();

  // Criação dos braços do robô
  glPushMatrix();
  glRotatef(thetaX, 1.0, 0.0, 0.0);
  glRotatef(thetaY, 0.0, 1.0, 0.0);
  bracoDireito();
  bracoEsquerdo();
  glPopMatrix();

  // Criação das pernas do robô
  glPushMatrix();
  glRotatef(thetaX, 1.0, 0.0, 0.0);
  glRotatef(thetaY, 0.0, 1.0, 0.0);
  pernaDireita();
  pernaEsquerda();
  glPopMatrix();

  // Criação da cabeça do robô
  glPushMatrix();
  glRotatef(thetaX, 1.0, 0.0, 0.0);
  glRotatef(thetaY, 0.0, 1.0, 0.0);
  cabeca();
  glPopMatrix();

  glFlush();
}

int main(int argc, char *argv[]) {
  // Restante da função main permanece a mesma
  // ...

  glutMainLoop();
  return 0;
}
