/* Programa: Palhaço (interaja usando as setas do teclado).
   Autor: Gustavo Henrique Tavares Isobe - RA: 158552
   Versao: 1.0 - 28/09/2023
*/

// ##################### Bibliotecas Externas ##############################

#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ##################### Variaveis Globais ##############################

float angX = 0.0;
float angY = 0.0;
int opcao = 0;
int pausado = 0;

// ###################### Funcoes e Procedimentos do programa ##############

void init(){
     glClearColor(0.0, 0.0, 0.0, 0.0);
     glEnable(GL_DEPTH_TEST);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     glOrtho(-7.0, 7.0, -7.0, 7.0, -7.0, 7.0);
     glPushMatrix();
}

void palhaco()
{
     //cabeça:
     glColor3f(1.0, 1.0, 0.0);  //amarelo
     glutSolidSphere(2.0, 50, 50);  //desenha cabeça
     //olhos:
     glPushMatrix();
     glColor3f(0.0, 0.0, 0.0);
     glTranslatef(-0.5, 1.0, 1.5);  //olho esquerdo
     glutSolidSphere(0.2, 30, 30);  //desenha
     glTranslatef(1.0, 0.0, 0.0);   //olho direito
     glutSolidSphere(0.2, 30, 30);  //desenha
     glPopMatrix();

     //nariz:
     glPushMatrix();
     glColor3f(1.0, 0.0, 0.0);  //vermelho
     glTranslatef(0.0, 0.0, 2.0);  //posição do nariz
     glutSolidCone(0.2, 1.0, 30, 30);  //desenha o nariz
     glPopMatrix();

     //boca:
     glColor3f(0.0, 0.0, 0.0);  //preto
     glPushMatrix();
     glTranslatef(0.0, -1.0, 1.5); //posição da boca
     glRotatef(0.0, 0.0, 0.0, 0.0);  //rotação da boca definida em 0
     glutSolidTorus(0.1, 0.5, 30, 30);  //desenha https://www.opengl.org/resources/libraries/glut/spec3/node84.html
     glPopMatrix();

 /*    //chapeu  //nao ficou bom
     glPushMatrix();
     glColor3f(1.0, 1.0, 1.0);
     glTranslatef(0.0, 1.8, 1.8);  //posição do chapeu
     glutSolidCone(0.5, 1.0, 30, 30);  //desenha o chapeu
     glPopMatrix();*/
}

void display()
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glColor3f(0.0, 0.0, 1.0);
     glPopMatrix();
     glPushMatrix();
     glRotatef(angX, 1.0, 0.0, 0.0);
     glRotatef(angY, 0.0, 1.0, 0.0);

     if (!pausado) {
         glRotatef(angX, 1.0, 0.0, 0.0);
         glRotatef(angY, 0.0, 1.0, 0.0);
     }
     //desenha o rosto
     palhaco();
     glFlush();
}

void timerFunc(int value)
{
    switch (opcao) {
        case 1:
            angX += 5;
            break;
        case 2:
            angX -= 5;
            break;
        case 3:
            angY += 5;
            break;
        case 4:
            angY -= 5;
            break;
        case 5:
            angX = 0 ;
            angY = 0 ;
        default:
            break;
    }
    glutPostRedisplay();
    glutTimerFunc(10, timerFunc, 1);
}

void rotacoes(int key, int x, int y){
     switch (key){
        case GLUT_KEY_UP :
           opcao = 1;
           break ;
        case GLUT_KEY_DOWN :
           opcao = 2;
           break ;
        case GLUT_KEY_LEFT :
           opcao = 3;
           break ;
        case GLUT_KEY_RIGHT :
           opcao = 4;
           break ;
        case GLUT_KEY_F1 :
           opcao = 5 ;
           break ;
        default:
           break;
     }
     // S ou s para parar a rotacao
     if (key == 'S' || key == 's') {
         pausado = !pausado;
     }
     glutPostRedisplay() ;
}

// ############################ Principal ###################################

int main(int argc, char *argv[])
{
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
     glutInitWindowPosition(50, 50);
     glutInitWindowSize(600, 600);
     glutCreateWindow("Palhaço");
     glutDisplayFunc(display);
     glutSpecialFunc(rotacoes);
     glutTimerFunc(10, timerFunc, 1);
     init();
     glutMainLoop();
     return 0;
}
