#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// Para usar strings

// SOIL é a biblioteca para leitura das imagens
#include "SOIL.h"

// Um pixel RGB
typedef struct {
    unsigned char r, g, b;
} RGB;

// Uma imagem em RGB
typedef struct {
    int width, height;
    RGB* img;
} Img;

// Protótipos
void load(char* name, Img* pic);

// Carrega uma imagem para a struct Img
void load(char* name, Img* pic)
{
    int chan;
    pic->img = (unsigned char*) SOIL_load_image(name, &pic->width, &pic->height, &chan, SOIL_LOAD_RGB);
    if(!pic->img)
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        exit(1);
    }
    printf("Load: %d x %d x %d\n", pic->width, pic->height, chan);
}

void printImage(Img picture) {
    for(int i = 0; i < picture.width; i++) {
        for(int j = 0; j < picture.height; j++) {
            printf("[%02X %02X %02X] ", picture.img[i].r, picture.img[i].g, picture.img[i].b);
        }
        printf("\n");
    }
}

void desturateImage(Img *picture, int index) {
    int color = (0.3 * picture->img[index].r + 0.59 * picture->img[index].g + 0.11 * picture->img[index].b);

}

void setColor(RGB *pixel, int color) {
    *pixel.r = color;
    *pixel.g = color;
    *pixel.b = color;
}

int main(int argc, char** argv)
{
    Img pic;
    if(argc < 1) {
        printf("loader [img]\n");
        exit(1);
    }
    load(argv[1], &pic);

    printf("Primeiros 10 pixels da imagem:\n");
    for(int i=0; i<10; i++) {
        printf("[%02X %02X %02X] ", pic.img[i].r, pic.img[i].g, pic.img[i].b);
    }
    printf("\n");

    printImage(pic);

    free(pic.img);
}
