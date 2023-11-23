#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float angleBracoDireito = 0.0;
float angleBracoEsquerdo = 0.0;
float anglePernaDireita = 0.0;
float anglePernaEsquerda = 0.0;

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

To add appropriate lighting to the arms, legs, and body of the robot, you can set material properties and modify the `init()` function. Here's the updated code:

```c
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float angleBracoDireito = 0.0;
float angleBracoEsquerdo = 0.0;
float anglePernaDireita = 0.0;
float anglePernaEsquerda = 0.0;

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

  GLfloat material_specular[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat material_shininess[] = {50.0};

  // Set material properties for arms, legs, and body
  glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

  glShadeModel(GL_FLAT);
}

// ... (rest of the code)

```

In this modified `init()` function, I've added material properties for specular reflection and shininess. The `GL_SPECULAR` property controls the specular reflection of light, and `GL_SHININESS` controls the shininess of the material.

These changes should provide more realistic lighting on the arms, legs, and body of the robot. Adjust the material properties according to your preferences for the desired appearance.



Certainly! Here's an example of how to load a texture using only OpenGL, without relying on external libraries. This example uses a simple BMP (Windows Bitmap) file format. You can replace it with your image file format, but you may need to implement a loader for that specific format.

1. Include the necessary headers in your code:

```c
#include <GL/glut.h>
#include <cstdio>
```

2. Load the texture in the `init()` function:

```c
GLuint textureID; // Global variable to store the texture ID

void loadTexture() {
  FILE *file;
  unsigned char header[54];
  unsigned int dataPos;
  unsigned int imageSize;
  unsigned int width, height;
  unsigned char *data;

  // Open the file
  file = fopen("path/to/your/image.bmp", "rb");

  if (!file) {
    fprintf(stderr, "Could not open file\n");
    return;
  }

  // Read the BMP header
  if (fread(header, 1, 54, file) != 54) {
    fprintf(stderr, "Not a correct BMP file\n");
    fclose(file);
    return;
  }

  // Check if it's a BMP file
  if (header[0] != 'B' || header[1] != 'M') {
    fprintf(stderr, "Not a correct BMP file\n");
    fclose(file);
    return;
  }

  // Read data position and image size from header
  dataPos = *(int*)&(header[0x0A]);
  imageSize = *(int*)&(header[0x22]);
  width = *(int*)&(header[0x12]);
  height = *(int*)&(header[0x16]);

  // Adjust image size for uncompressed BMP
  if (imageSize == 0) imageSize = width * height * 3;

  // Set position to the beginning of image data
  fseek(file, dataPos, SEEK_SET);

  // Allocate buffer for image data
  data = new unsigned char[imageSize];

  // Read image data
  fread(data, 1, imageSize, file);

  // Close the file
  fclose(file);

  // Generate OpenGL texture
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);

  // Set texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Upload image data to OpenGL texture
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

  // Free the allocated buffer
  delete[] data;
}

void init() {
  // ... (existing code)

  // Load texture
  loadTexture();

  // ... (rest of the init code)
}
```

Replace `"path/to/your/image.bmp"` with the actual path to your BMP texture image. Note that this example assumes a 24-bit BMP image. If your image uses a different bit-depth or format, you may need to adjust the code accordingly.

3. Modify your `cubo()` function to include texture coordinates:

```c
void cubo() {
  // ... (existing code)

  glBindTexture(GL_TEXTURE_2D, textureID);
  glBegin(GL_POLYGON);
  glTexCoord2f(0.0, 0.0);
  glVertex3f(-0.25, 0.25, 0.25);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(0.25, 0.25, 0.25);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(0.25, -0.25, 0.25);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-0.25, -0.25, 0.25);
  glEnd();

  // ... (repeat for other sides)
}
```

This example uses a simple BMP file format for illustration purposes. Depending on your specific needs, you may need to implement a loader for your particular image file format.

  Certainly! Below is the complete modified code with different textures for each part of the robot:

```c
#include <GL/glut.h>
#include <cstdio>

// Struct to hold texture information
struct Texture {
  GLuint id;
  int width;
  int height;
  unsigned char* data;
};

// Global variables for robot angles
float angleBracoDireito = 0.0;
float angleBracoEsquerdo = 0.0;
float anglePernaDireita = 0.0;
float anglePernaEsquerda = 0.0;

float thetaX = 90.00;
float thetaY = 180.00;

// Global variables for robot textures
Texture robotTextures[6]; // One for each surface
Texture earthTexture;

// Function to load texture data
void loadTextureData(const char* filename, Texture& texture) {
  FILE* file = fopen(filename, "rb");

  if (!file) {
    fprintf(stderr, "Could not open file\n");
    return;
  }

  // Assuming it's a simple 24-bit BMP file
  fseek(file, 18, SEEK_SET);
  fread(&texture.width, sizeof(int), 1, file);
  fread(&texture.height, sizeof(int), 1, file);
  int imageSize = texture.width * texture.height * 3;

  texture.data = new unsigned char[imageSize];
  fread(texture.data, sizeof(unsigned char), imageSize, file);

  fclose(file);
}

// Function to initialize texture
void initTexture(Texture& texture) {
  glGenTextures(1, &texture.id);
  glBindTexture(GL_TEXTURE_2D, texture.id);

  // Set texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Upload image data to OpenGL texture
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_BGR, GL_UNSIGNED_BYTE, texture.data);

  // Free the allocated buffer
  delete[] texture.data;
}

// Function to initialize all textures
void initTextures() {
  loadTextureData("path/to/your/surface1.bmp", robotTextures[0]);
  initTexture(robotTextures[0]);

  loadTextureData("path/to/your/surface2.bmp", robotTextures[1]);
  initTexture(robotTextures[1]);

  loadTextureData("path/to/your/surface3.bmp", robotTextures[2]);
  initTexture(robotTextures[2]);

  loadTextureData("path/to/your/surface4.bmp", robotTextures[3]);
  initTexture(robotTextures[3]);

  loadTextureData("path/to/your/surface5.bmp", robotTextures[4]);
  initTexture(robotTextures[4]);

  loadTextureData("path/to/your/surface6.bmp", robotTextures[5]);
  initTexture(robotTextures[5]);

  loadTextureData("path/to/your/earthTexture.bmp", earthTexture);
  initTexture(earthTexture);
}

// Function to draw a textured cube
void cubo(int textureIndex) {
  glBindTexture(GL_TEXTURE_2D, robotTextures[textureIndex].id);

  glBegin(GL_POLYGON);
  glTexCoord2f(0.0, 0.0);
  glVertex3f(-0.25, 0.25, 0.25);

  glTexCoord2f(1.0, 0.0);
  glVertex3f(0.25, 0.25, 0.25);

  glTexCoord2f(1.0, 1.0);
  glVertex3f(0.25, -0.25, 0.25);

  glTexCoord2f(0.0, 1.0);
  glVertex3f(-0.25, -0.25, 0.25);
  glEnd();

  // ... (repeat for other sides)
}

// Update your existing draw functions to use the modified cubo function
void tronco() {
  glPushMatrix();
  glScalef(0.4, 0.4, 0.6);
  cubo(0); // Use texture for surface1
  glPopMatrix();
}

void bracoDireito() {
  glPushMatrix();
  glTranslatef(0.15, 0.0, 0.0);
  glRotatef(angleBracoDireito, 1.0, 0.0, 0.0);
  glScalef(0.15, 0.15, 0.4);
  cubo(1); // Use texture for surface2
  glPopMatrix();
}

void bracoEsquerdo() {
  glPushMatrix();
  glTranslatef(-0.15, 0.0, 0.0);
  glRotatef(angleBracoEsquerdo, 1.0, 0.0, 0.0);
  glScalef(0.15, 0.15, 0.4);
  cubo(2); // Use texture for surface3
  glPopMatrix();
}

void pernaDireita() {
  glPushMatrix();
  glTranslatef(0.06, 0.0, -0.25);
  glRotatef(anglePernaDireita, 1.0, 0.0, 0.0);
  glScalef(0.15, 0.15, 0.4);
  cubo(3); // Use texture for surface4
  glPopMatrix();
}

void pernaEsquerda() {
  glPushMatrix();
  glTranslatef(-0.06, 0.0, -0.25);
  glRotatef(anglePernaEsquerda, 1.0, 0.0, 0.0);
  glScalef(0.15, 0.15, 0.4);
  cubo(4); // Use texture for surface5
  glPopMatrix();
}

void cabeca() {
  glPushMatrix();
  glTranslatef(0.0, 0.0, 0.2);
  glScalef(0.25, 0.25, 0.25);
  cubo(5); // Use texture for surface6
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
  switch (tecla)
