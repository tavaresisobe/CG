#include <GL/glut.h>
#include <stdio.h>

int windowWidth = 800;
int windowHeight = 600;

//coordenadas da janela de recorte
double X_MIN = 100.0;
double X_MAX = 400.0;
double Y_MIN = 100.0;
double Y_MAX = 300.0;

//pontos inciais e finais das linhas
double x1, y1, x2, y2;
int desenharLinha = 0;

//funcao para calcular bit
int calcularCodigoRegiao(double x, double y) {
    int codigo = 0;

    if (x < X_MIN) {
        codigo |= 1;
    }
    if (x > X_MAX) {
        codigo |= 2;
    }
    if (y < Y_MIN) {
        codigo |= 4;
    }
    if (y > Y_MAX) {
        codigo |= 8;
    }

    return codigo;
}

//função para recortar a linha
void recortarLinha() {
    int codigo1 = calcularCodigoRegiao(x1, y1);
    int codigo2 = calcularCodigoRegiao(x2, y2);

    if (!(codigo1 | codigo2)) {
        //caso ambos pontos estiverem dentro da janela de recorte
        desenharLinha = 1;
    } else if (codigo1 & codigo2) {
        //caso ambos os pontos estiverem fora de uma mesma borda da janela de recorte
        desenharLinha = 0;
    } else {
        while (codigo1 || codigo2) {
            if (codigo1 & codigo2) {
                //caso a linha estiver completamente fora da janela de recorte
                desenharLinha = 0;
                break;
            }

            int codigoFora = codigo1 ? codigo1 : codigo2;
            double x, y;

            if (codigoFora & 8) {
                x = x1 + (x2 - x1) * (Y_MAX - y1) / (y2 - y1);
                y = Y_MAX;
            } else if (codigoFora & 4) {
                x = x1 + (x2 - x1) * (Y_MIN - y1) / (y2 - y1);
                y = Y_MIN;
            } else if (codigoFora & 2) {
                y = y1 + (y2 - y1) * (X_MAX - x1) / (x2 - x1);
                x = X_MAX;
            } else {
                y = y1 + (y2 - y1) * (X_MIN - x1) / (x2 - x1);
                x = X_MIN;
            }

            if (codigoFora == codigo1) {
                x1 = x;
                y1 = y;
                codigo1 = calcularCodigoRegiao(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                codigo2 = calcularCodigoRegiao(x2, y2);
            }
        }

        desenharLinha = 1;
    }
}

//desenhando janela
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0); //janela de recorte (vermelho)
    glBegin(GL_LINE_LOOP);
    glVertex2d(X_MIN, Y_MIN);
    glVertex2d(X_MAX, Y_MIN);
    glVertex2d(X_MAX, Y_MAX);
    glVertex2d(X_MIN, Y_MAX);
    glEnd();

    if (desenharLinha) {
        glColor3f(0.0, 0.0, 1.0); //reta (azul)
        glBegin(GL_LINES);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
        glEnd();
    }

    glFlush();
}

//captando cliques do mouse
void mouse(int button, int state, int mouseX, int mouseY) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (!desenharLinha) {
            x1 = (double)mouseX / windowWidth * (X_MAX - X_MIN) + X_MIN;
            y1 = (1.0 - (double)mouseY / windowHeight) * (Y_MAX - Y_MIN) + Y_MIN;
            desenharLinha = 1;
        } else {
            x2 = (double)mouseX / windowWidth * (X_MAX - X_MIN) + X_MIN;
            y2 = (1.0 - (double)mouseY / windowHeight) * (Y_MAX - Y_MIN) + Y_MIN;
            recortarLinha();
        }
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Recorte de Linha Cohen-Sutherland");
    glOrtho(0.0, windowWidth, 0.0, windowHeight, -1.0, 1.0);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}
