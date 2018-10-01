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

void readImage(Img picture, int image[]) {
    int size = picture.width * picture.height;
    for(int index = 0; index < size; index++) {
        int saturation = desaturatePixel(picture.img[index]);
        image[index] = saturation;
    }
}

int desaturatePixel(RGB pixel) {
    int result = (0.3 * pixel.r + 0.59 * pixel.g + 0.11 * pixel.b);
    return result;
}

void createHTML(int img[], int size) {
	FILE *ptrFile = fopen( "index.txt", "w");

	fprintf(ptrFile, "<HTML>\n ");

	for(int index = 0; index < size; index++) {
        fprintf(ptrFile, "%d", img[index]);
    }

	fclose(ptrFile);
}

int main(int argc, char** argv)
{
    Img pic;
    if(argc < 1) {
        printf("loader [img]\n");
        exit(1);
    }
    load(argv[1], &pic);

    int size = pic.width * pic.height;
    int img[size];
    readImage(pic, img);

    for(int index = 0; index < size; index++) {
        printf("%d\n", img[index]);
    }

    createHTML(img, size);

    free(pic.img);
}
