#include "bmp.h"
#include <GL/glut.h>

BMPImage* readBMP(const char *filename) {
  BMPImage *image = malloc(sizeof(BMPImage));
  FILE *file = fopen(filename, "rb");

  if (!file) {
    fprintf(stderr, "No se puede abrir el archivo %s\n", filename);
    free(image);
    return NULL;
  }

  fread(&image->fileHeader, sizeof(struct BMPFileHeader), 1, file);
  if (image->fileHeader.fileType != 0x4D42) {
    printf("El archivo no es un BMP válido.\n");
    fclose(file);
    free(image);
    return NULL;
  }

  fread(&image->infoHeader, sizeof(struct BMPInfoHeader), 1, file);
  image->data = (unsigned char *)malloc(image->infoHeader.imageSize);

  fseek(file, image->fileHeader.dataOffset, SEEK_SET);
  fread(image->data, 1, image->infoHeader.imageSize, file);
  fclose(file);

  return image;
}

void freeBMP(BMPImage *image) {
  free(image->data);
  free(image);
}

void drawBMP(BMPImage *image) {
  glDrawPixels(image->infoHeader.width, image->infoHeader.height, GL_BGR, GL_UNSIGNED_BYTE, image->data);
}
