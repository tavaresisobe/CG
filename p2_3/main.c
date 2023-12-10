/* Programa: STEVE ROBÔ ANIMADO
   Autor: Gustavo Henrique Tavares Isobe
   Versao: 1.0 - 09/12/2023 - 23:42h
*/

// ##################### Bibliotecas Externas ##############################

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// ##################### Var Gloabais ##############################

GLfloat ombrodir = 0.0 ;
GLfloat ombroesq = 0.0 ;
GLfloat bracodir = 0.0 ;
GLfloat bracoesq = 0.0 ;
GLfloat pernadir = 0.0 ;
GLfloat pernaesq = 0.0 ;
GLfloat pe_dir = 0.0 ;
GLfloat pe_esq = 0.0 ;
GLfloat x = 0.0 ;
GLfloat y = 0.0 ;
GLfloat z = 0.0 ;
GLfloat auxtransalacao = 0.0;
GLfloat auxbracotransalacao = 0.0 ;

// ########################## TAD X.h (TEXTURA) ######################################

typedef struct BMPImagem
{
    int   width;
    int   height;
    char *data;
}BMPImage;

/* Qtd máxima de texturas a serem usadas no programa */
#define MAX_NO_TEXTURES 5

/* vetor com os números das texturas */
GLuint texture_id[MAX_NO_TEXTURES];

char* filenameArray[MAX_NO_TEXTURES] = {
        "skin1.bmp",
        "ciano5.bmp",
        "lataria.bmp",
        "purple1.bmp",
        "head600.bmp"
};

GLUquadricObj *obj;

GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;
bool pernaParaFrente = true;
bool bracoParaFrente = true;

//-----------------------------------------------------------------------------
// Name: getBitmapImageData()
// Desc: Simply image loader for 24 bit BMP files.
//-----------------------------------------------------------------------------

// ###################### Funcoes e Procedimentos do programa - TEXTURA ##############

void getBitmapImageData( char *pFileName, BMPImage *pImage )
{
    FILE *pFile = NULL;
    unsigned short nNumPlanes;
    unsigned short nNumBPP;
    int i;

    if( (pFile = fopen(pFileName, "rb") ) == NULL )
        printf("ERROR: getBitmapImageData - %s not found.\n", pFileName);

    // Seek forward to width and height info
    fseek( pFile, 18, SEEK_CUR );

    if( (i = fread(&pImage->width, 4, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read width from %s.\n ", pFileName);

    if( (i = fread(&pImage->height, 4, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read height from %s.\n ", pFileName);

    if( (fread(&nNumPlanes, 2, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read plane count from %s.\n", pFileName);

    if( nNumPlanes != 1 )
        printf("ERROR: getBitmapImageData - Plane count from %s.\n ", pFileName);

    if( (i = fread(&nNumBPP, 2, 1, pFile)) != 1 )
        printf( "ERROR: getBitmapImageData - Couldn't read BPP from %s.\n ", pFileName);

    if( nNumBPP != 24 )
        printf("ERROR: getBitmapImageData - BPP from %s.\n ", pFileName);

    // Seek forward to image data
    fseek( pFile, 24, SEEK_CUR );

    // Calculate the image's total size in bytes. Note how we multiply the
    // result of (width * height) by 3. This is becuase a 24 bit color BMP
    // file will give you 3 bytes per pixel.
    int nTotalImagesize = (pImage->width * pImage->height) * 3;

    pImage->data = (char*) malloc( nTotalImagesize );

    if( (i = fread(pImage->data, nTotalImagesize, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read image data from %s.\n ", pFileName);

    char charTemp;
    for( i = 0; i < nTotalImagesize; i += 3 )
    {
        charTemp = pImage->data[i];
        pImage->data[i] = pImage->data[i+2];
        pImage->data[i+2] = charTemp;
    }
}


/*Função para Carregar uma imagem .BMP */
void CarregaTexturas()
{
    BMPImage textura;

    /* Define quantas texturas serão usadas no programa  */
    glGenTextures(MAX_NO_TEXTURES, texture_id); /* 1 = uma textura; */
                                /* texture_id = vetor que guardas os números das texturas */

    int i;
    for ( i=0; i<MAX_NO_TEXTURES; i++ ) {
        getBitmapImageData( filenameArray[i], &textura);
        glBindTexture(GL_TEXTURE_2D, texture_id[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, textura.width, textura.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textura.data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    }
}

void initTexture (void)
{

    /* Habilita o uso de textura bidimensional  */
    glEnable ( GL_TEXTURE_2D );
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    /*Carrega os arquivos de textura */
  //  CarregaTextura("tunnelTexture.bmp");
    //CarregaTextura("tex2.bmp");
    CarregaTexturas();

}

// ###################### Funcoes e Procedimentos do programa ##############

void lightning() {
    GLfloat light0_pos[] = {2.0f, 2.0f, 2.0f, 1.0f};
    GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);

    // Ajuste a intensidade da luz difusa e especular para tornar a luz mais forte
    GLfloat increasedIntensity = 1000.0f;
    GLfloat increasedWhite[] = {increasedIntensity, increasedIntensity, increasedIntensity, 1.0f};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, increasedWhite);
    glLightfv(GL_LIGHT0, GL_SPECULAR, increasedWhite);

    // Fonte de Luz Direcional - Efeito de Holofote
    GLfloat light1_pos[] = {4.0f, 0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);

    // Ajuste a intensidade da luz difusa e especular para tornar a luz mais forte
    glLightfv(GL_LIGHT1, GL_DIFFUSE, increasedWhite);
    glLightfv(GL_LIGHT1, GL_SPECULAR, increasedWhite);

    GLfloat direction[] = {-1.0f, 0.0f, 0.0f};
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0f);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.1f);

    // Parâmetros definidos globalmente
    GLfloat global_ambient[] = {0.1f, 0.1f, 0.1f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

void init(void)
{
    glEnable ( GL_COLOR_MATERIAL );
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //define a cor de fundo
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade

    //glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_MODELVIEW); //define que a matrix é a model view
    glLoadIdentity(); //carrega a matrix de identidade
    gluLookAt(1.0, 2.0, 4.0,   //posição da câmera
              0.0, 0.0, 0.0,   //para onde a câmera aponta
              0.0, 1.0, 0.0);  //vetor view-up

    glMatrixMode(GL_PROJECTION); //define que a matrix é a de projeção
    glLoadIdentity(); //carrega a matrix de identidade
    //glOrtho(-2.0, 2.0, -2.0, 2.0, 2.0, 8.0); //define uma projeção ortogonal
    gluPerspective(45.0, 1.0, 2.0, 8.0); //define uma projeção perspectiva
    //glFrustum(-2.0, 2.0, -2.0, 2.0, 2.0, 8.0); //define uma projeção perspectiva simétrica
    //glFrustum(-2.0, 1.0, -1.0, 2.0, 2.0, 8.0); //define uma projeção perspectiva obliqua
    glViewport(0, 0, 500, 500);

    lightning();
}

void cubo()
{
    glBegin(GL_POLYGON);
        glNormal3f(-0.25,0.25,0.25);
        glTexCoord2f(0.0f,0.0f);
        glVertex3f(-0.25,0.25,0.25);
        glNormal3f(0.25,0.25,0.25);
        glTexCoord2f(1.0f,0.0f);
        glVertex3f(0.25,0.25,0.25);
        glNormal3f(-0.25,-0.25,0.25);
        glTexCoord2f(1.0f,1.0f);
        glVertex3f(0.25,-0.25,0.25);
        glNormal3f(-0.25,-0.25,0.25);
        glTexCoord2f(0.0f,1.0f);
        glVertex3f(-0.25,-0.25,0.25);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(-0.25,0.25,-0.25);
        glTexCoord2f(0.0f,0.0f);
        glVertex3f(-0.25,0.25,-0.25);
        glNormal3f(0.25,0.25,-0.25);
        glTexCoord2f(1.0f,0.0f);
        glVertex3f(0.25,0.25,-0.25);
        glNormal3f(0.25,-0.25,-0.25);
        glTexCoord2f(1.0f,1.0f);
        glVertex3f(0.25,-0.25,-0.25);
        glNormal3f(-0.25,-0.25,-0.25);
        glTexCoord2f(0.0f,1.0f);
        glVertex3f(-0.25,-0.25,-0.25);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(0.25,-0.25,0.25);
        glTexCoord2f(0.0f,0.0f);
        glVertex3f(0.25,-0.25,0.25);
        glNormal3f(0.25,0.25,0.25);
        glTexCoord2f(1.0f,0.0f);
        glVertex3f(0.25,0.25,0.25);
        glNormal3f(0.25,0.25,-0.25);
        glTexCoord2f(1.0f,1.0f);
        glVertex3f(0.25,0.25,-0.25);
        glNormal3f(0.25,-0.25,-0.25);
        glTexCoord2f(0.0f,1.0f);
        glVertex3f(0.25,-0.25,-0.25);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(-0.25,-0.25,0.25);
        glTexCoord2f(0.0f,0.0f);
        glVertex3f(-0.25,-0.25,0.25);
        glNormal3f(-0.25,0.25,0.25);
        glTexCoord2f(1.0f,0.0f);
        glVertex3f(-0.25,0.25,0.25);
        glNormal3f(-0.25,0.25,-0.25);
        glTexCoord2f(1.0f,1.0f);
        glVertex3f(-0.25,0.25,-0.25);
        glNormal3f(-0.25,-0.25,-0.25);
        glTexCoord2f(0.0f,1.0f);
        glVertex3f(-0.25,-0.25,-0.25);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(-0.25,0.25,0.25);
        glTexCoord2f(0.0f,0.0f);
        glVertex3f(-0.25,0.25,0.25);
        glNormal3f(0.25,0.25,0.25);
        glTexCoord2f(1.0f,0.0f);
        glVertex3f(0.25,0.25,0.25);
        glNormal3f(0.25,0.25,-0.25);
        glTexCoord2f(1.0f,1.0f);
        glVertex3f(0.25,0.25,-0.25);
        glNormal3f(-0.25,0.25,-0.25);
        glTexCoord2f(0.0f,1.0f);
        glVertex3f(-0.25,0.25,-0.25);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(-0.25,-0.25,0.25);
        glTexCoord2f(0.0f,0.0f);
        glVertex3f(-0.25,-0.25,0.25);
        glNormal3f(0.25,-0.25,0.25);
        glTexCoord2f(1.0f,0.0f);
        glVertex3f(0.25,-0.25,0.25);
        glNormal3f(0.25,-0.25,-0.25);
        glTexCoord2f(1.0f,1.0f);
        glVertex3f(0.25,-0.25,-0.25);
        glNormal3f(-0.25,-0.25,-0.25);
        glTexCoord2f(0.0f,1.0f);
        glVertex3f(-0.25,-0.25,-0.25);
    glEnd();
}

void robo()
{
    glMatrixMode(GL_MODELVIEW);

    //Cabeça
    glBindTexture(GL_TEXTURE_2D, texture_id[4]);
    //glBindTexture(GL_TEXTURE_2D, texture_id[0]); descomentar para visualizar a cabeça no mesmo tom da pele
    glPushMatrix();
    glTranslatef(0.0,0.85,z);
    glRotatef(0.0, 1.0, 0.0, 0.0) ;
    glRotatef(x, 0.0, 1.0, 0.0) ;
    glScalef(0.5,0.5,0.5);
    cubo();
    glPopMatrix();

    //Corpo
    glBindTexture(GL_TEXTURE_2D, texture_id[1]);
    glPushMatrix();
    glTranslatef(0.0,0.48,-0.01 + z);
    glRotatef(0.0, 1.0, 0.0, 0.0) ;
    glRotatef(x, 0.0, 1.0, 0.0) ;
    glScalef(1.0,1.0,0.5);
    cubo();
    glPopMatrix();

    //Perna Superior Esquerda
    glBindTexture(GL_TEXTURE_2D, texture_id[3]);
    glPushMatrix();
    glTranslatef(-0.125,0.02,z);
    glRotatef(pernaesq, 1.0, 0.0,0.0) ;
    glRotatef(x, 0.0, 1.0, 0.0) ;
    glScalef(0.50,0.85,0.25);
    cubo();
    glPopMatrix();

    // Pe Esquerdo
    glBindTexture(GL_TEXTURE_2D, texture_id[0]);
    glPushMatrix();
    glTranslatef(-0.125,-0.28,-auxtransalacao + z);
    glRotatef(pernaesq, 1.0, 0.0, 0.0) ;
    glRotatef(x, 0.0, 1.0, 0.0) ;
    glScalef(0.50, 0.4,0.25);
    cubo();
    glPopMatrix();

    //Perna Superior Direita
    glBindTexture(GL_TEXTURE_2D, texture_id[3]);
    glPushMatrix();
    glTranslatef(0.125,0.02,z);
    glRotatef(-pernaesq, 1.0, 0.0,0.0) ;
    glRotatef(x, 0.0, 1.0, 0.0) ;
    glScalef(0.50,0.85,0.25);
    cubo();
    glPopMatrix();

    //Pe Direito
    glBindTexture(GL_TEXTURE_2D, texture_id[2]);
    glPushMatrix();
    glTranslatef(0.125,-0.28, auxtransalacao + z);
    glRotatef(-pernaesq, 1.0, 0.0, 0.0) ;
    glRotatef(x, 0.0, 1.0, 0.0) ;
    glScalef(0.50,0.4,0.25);
    cubo();
    glPopMatrix();

    //Ombro Esquerdo
    glBindTexture(GL_TEXTURE_2D, texture_id[1]);
    glPushMatrix();
    glTranslatef(-0.347,0.63,z);
    glRotatef(bracoesq, 1.0, 0.0, 0.0) ;
    glRotatef(x, 0.0, 1.0, 0.0) ;
    glScalef(0.40,0.40,0.25);
    cubo();
    glPopMatrix();

    //Braço esquerdo
    glBindTexture(GL_TEXTURE_2D, texture_id[2]);
    glPushMatrix();
    glTranslatef(-0.35, 0.40, -auxbracotransalacao + z);
    glRotatef(bracoesq, 1.0, 0.0, 0.0) ;
    glRotatef(x, 0.0, 1.0, 0.0) ;
    glScalef(0.28,0.63,0.25);
    cubo();
    glPopMatrix();

    //Ombro Direito
    glBindTexture(GL_TEXTURE_2D, texture_id[1]);
    glPushMatrix();
    glTranslatef(0.347,0.63,z);
    glRotatef(-bracoesq, 1.0, 0.0, 0.0) ;
    glRotatef(x, 0.0, 1.0, 0.0) ;
    glScalef(0.40,0.40,0.25);
    cubo();
    glPopMatrix();

    //  Braço Direito
    glBindTexture(GL_TEXTURE_2D, texture_id[2]);
    glPushMatrix();
    glTranslatef(0.35, 0.40, auxbracotransalacao + z);
    glRotatef(-bracoesq, 1.0, 0.0, 0.0) ;
    glRotatef(x, 0.0, 1.0, 0.0) ;
    glScalef(0.28,0.63,0.25);
    cubo();
    glPopMatrix();
}

void displayFunc() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer

        glMatrixMode(GL_MODELVIEW); //define que a matrix é a de modelo
        glBindTexture(GL_TEXTURE_2D, texture_id[0]);
        glPushMatrix();
        glRotatef(angleX,1.0,0.0,0.0);
        glRotatef(angleY,0.0,1.0,0.0);
        robo();
        glPopMatrix();

        glFlush();                  //força o desenho das primitivas
}

void animaPerna(int valor) {
    if (pernaParaFrente) {
        pernaesq += 1.0;
        auxtransalacao += 0.005 ;
        if (pernaesq >= 25.0){
            pernaParaFrente = false;
        }
    } else {
        pernaesq -= 1.0;
        auxtransalacao += -0.005 ;
        if (pernaesq <= -25.0) {
            pernaParaFrente = true;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(20, animaPerna, 0);
}

void animaBraco(int valor) {
    if (bracoParaFrente) {
        bracoesq += 1.0;
        auxbracotransalacao += 0.004 ;
        if (bracoesq >= 30.0) {
            bracoParaFrente = false;
        }
    } else {
        bracoesq -= 1.0;
        auxbracotransalacao += -0.004 ;
        if (bracoesq <= -30.0) {
            bracoParaFrente = true;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(20, animaBraco, 0);
}


void rotacoes(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            z += 0.03 ;
            break;
        case GLUT_KEY_DOWN:
            z += -0.03 ;
            break;
        case GLUT_KEY_LEFT:
            angleY -= 15;
            break;
        case GLUT_KEY_RIGHT:
            angleY += 15;
            break;
        case GLUT_KEY_F1:
            glutTimerFunc(0, animaPerna, 0);
            glutTimerFunc(0, animaBraco, 0);
            break;
        case GLUT_KEY_F4:
            x += 10.0 ;
            break ;
        case GLUT_KEY_F5:
            x += -10.00 ;
            break;
        default:
            break;
        }
    glutPostRedisplay();
}

// ############################ Principal ###################################

int main(int argc, char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(500,500);
    glutCreateWindow("STEVE: CYBORG");
    glutDisplayFunc(displayFunc);
    glutSpecialFunc(rotacoes);
    glutTimerFunc(0, animaPerna, 0);
    glutTimerFunc(0, animaBraco, 0);
    init();
    initTexture();
    glutMainLoop();
    return 0;
}
