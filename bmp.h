#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Estructura para el encabezado del archivo BMP (14 bytes)
struct BMPFileHeader {
    uint16_t fileType;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t dataOffset;
};

// Estructura para el encabezado de información de la imagen (40 bytes)
struct BMPInfoHeader {
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitCount;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t colorsUsed;
    uint32_t importantColors;
};

typedef struct {
    struct BMPFileHeader fileHeader;
    struct BMPInfoHeader infoHeader;
    unsigned char *data; // Datos de la imagen (array de píxeles)
} BMPImage;

BMPImage* readBMP(const char *filename);
void freeBMP(BMPImage *image);
void drawBMP(BMPImage *image);

#endif // BMP_H
