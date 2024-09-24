#include "bmp.h"
#include <GL/glut.h>
#include <stdio.h>

BMPImage *image;

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  if (image) {
    drawBMP(image);
  }
  glFlush();
}

int main() {
  char filename[256];

  // Pedir al usuario el nombre del archivo BMP
  printf("Ingrese el nombre del archivo BMP (con extensión): ");
  scanf("%255s", filename);

  image = readBMP(filename);
  if (!image) return 1;

  // Inicializar GLUT
  int argc = 1; // Necesario para evitar problemas con glutInit
  char *argv[1] = { "" }; // Argumento vacío para GLUT
  glutInit(&argc, argv);

  // Establecer el modo de visualización
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(image->infoHeader.width, image->infoHeader.height);
  glutCreateWindow("Visualizador de BMP");

  glLoadIdentity();
  glOrtho(0, image->infoHeader.width, image->infoHeader.height, 0, -1, 1);

  glutDisplayFunc(display);
  glutMainLoop();

  freeBMP(image);
  return 0;
}
