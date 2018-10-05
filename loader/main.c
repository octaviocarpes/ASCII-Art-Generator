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

void createHTML(int img[], int size, int imgWidth) {
	FILE *ptrFile = fopen( "index.html", "w");

	fprintf(ptrFile, "<!DOCTYPE html>\n ");
	fprintf(ptrFile, "<html>\n" );
	fprintf(ptrFile, "<title>Document</title> \n");
	fprintf(ptrFile, "<head> \n");
	char style = "background-color:black;";
	fprintf(ptrFile, "<body> \n");

	fprintf(ptrFile, "<p>\n");

	char characters[size];

	convertToCharacter(img, characters, size);

	int count = 0;
	for(int index = 0; index < size; index++) {
        if(count == imgWidth){
            fprintf(ptrFile, "\n");
        }
        fprintf(ptrFile, "%c", characters[index]);
    }

	fprintf(ptrFile, "</p>\n");
	fprintf(ptrFile, "</body> \n");
	fprintf(ptrFile, "</html> \n");

	fclose(ptrFile);
}

void convertToCharacter(int img[], char characters[], int imgSize) {
    for(int i = 0; i < imgSize; i++) {
        if(img[i] <= 31) {
            characters[i] = ".";
        } else if((img[i] > 31) && (img[i] < 62)) {
            characters[i] = ":";
        } else if((img[i] >= 62) && (img[i] < 93)) {
            characters[i] = "c";
        } else if((img[i] >= 93) && (img[i] < 124)) {
            characters[i] = "o";
        } else if((img[i] > 124) && (img[i] < 155)) {
            characters[i] = "C";
        } else if((img[i] > 155) && (img[i] < 186)) {
            characters[i] = "O";
        } else if((img[i] > 186) && (img[i] < 217)) {
            characters[i] = "8";
        } else if(img[i] >= 217) {
            characters[i] = "@";
        }
    }
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

    printf("%d\n", pic.height);
    printf("%d\n", pic.width);

    createHTML(img, size, pic.width);

    free(pic.img);
}
