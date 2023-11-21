#include <GL/glut.h>
#include <stdio.h>


//var globais para o posicionamento do personahem e asteroid:

float playerX = 50.0f;
float playerY = 50.0f;

float obstaculoX = 200.0f;
float obstaculoY = 200.0f;
float obstacleSpeed = 2.0f;

void desenhaPlayer() {
    glBegin(GL_QUADS);
    glVertex2f(playerX, playerY);
    glVertex2f(playerX + 20, playerY);
    glVertex2f(playerX + 20, playerY + 20);
    glVertex2f(playerX, playerY + 20);
    glEnd();
}

void desenhaObstaculo() {
    glBegin(GL_QUADS);
    glVertex2f(obstaculoX, obstaculoY);
    glVertex2f(obstaculoX + 20, obstaculoY);
    glVertex2f(obstaculoX + 20, obstaculoY + 20);
    glVertex2f(obstaculoX, obstaculoY + 20);
    glEnd();
}

void updateObstaculo() {
    obstaculoY -= obstacleSpeed;

    if (obstaculoY < 0) {
        obstaculoY = 400.0f; //posiciona o asteroide no ponto mais alto da janela
        obstaculoX = rand() % 400; //define uma posicao aleatoria do asteroide no eixo x
    }
}

void checaColisao() {
    if ((playerX < obstaculoX + 20) &&
        (playerX + 20 > obstaculoX) &&
        (playerY < obstaculoY + 20) &&
        (playerY + 20 > obstaculoY)) {
        printf("Voce Perdeu !\n");
        exit(0);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    //desenha jogador (quadrado vermelho)
    glColor3f(1.0, 0.0, 0.0);
    desenhaPlayer();

    //desenha asteroid (quadrados azuis
    glColor3f(0.0, 0.0, 1.0);
    desenhaObstaculo();

    //atualiza posicao do asteroid
    updateObstaculo();

    //verfica colisão
    checaColisao();

    glutSwapBuffers();
}

void tecladoPress(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            playerX -= 5.0f;
            break;
        case GLUT_KEY_RIGHT:
            playerX += 5.0f;
            break;
        case GLUT_KEY_UP:
            playerY += 5.0f;
            break;
        case GLUT_KEY_DOWN:
            playerY -= 5.0f;
            break;
    }

    glutPostRedisplay();
}

void update(int value) {
    glutTimerFunc(16, update, 0);
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Projeto Final CG:");

    gluOrtho2D(0, 400, 0, 400);

    glutDisplayFunc(display);
    glutSpecialFunc(tecladoPress);
    glutTimerFunc(25, update, 0);

    glClearColor(0, 0, 0, 0); // cor janela (preta)
    glutMainLoop();
    return 0;
}
