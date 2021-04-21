#include <windows.h>
#include <stdio.h>
#include <math.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include "gl/glew.h"
#include "gl/glut.h"


#define BITMAP_ID 0x4D42

bool snapScreen(int width, int height, const char *file) {
	byte *image;
	FILE *fp;
	BITMAPFILEHEADER FileHeader;
	BITMAPINFOHEADER InfoHeader;

	FileHeader.bfType = BITMAP_ID; // BMP identity
	FileHeader.bfOffBits = 14 + sizeof(BITMAPINFOHEADER); // data location
	FileHeader.bfReserved1 = FileHeader.bfReserved2 = 0;
	FileHeader.bfSize = height*width * 24 + FileHeader.bfOffBits; // file size
	InfoHeader.biXPelsPerMeter = InfoHeader.biYPelsPerMeter = 0; // resolution
	InfoHeader.biClrUsed = 0;
	InfoHeader.biClrImportant = 0;
	InfoHeader.biPlanes = 1;
	InfoHeader.biCompression = 0;
	InfoHeader.biBitCount = 24;
	InfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	InfoHeader.biHeight = height;
	InfoHeader.biWidth = width;
	InfoHeader.biSizeImage = height*width * 3;

	image = (byte *)malloc(sizeof(byte)*InfoHeader.biSizeImage);
	if (image == NULL) {
		free(image);
		printf("Exception: No enough space!\n");
		return false;
	}

	// get output image data
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, image);

	fopen_s(&fp,file, "wb");
	if (fp == NULL) {
		printf("Exception: Fail to open file!\n");
		return false;
	}
	fwrite(&FileHeader.bfType, 2, 1, fp);
	fwrite(&FileHeader.bfSize, 4, 1, fp);
	fwrite(&FileHeader.bfReserved1, 2, 1, fp);
	fwrite(&FileHeader.bfReserved2, 2, 1, fp);
	fwrite(&FileHeader.bfOffBits, 4, 1, fp);
	fwrite(&InfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
	fwrite(image, InfoHeader.biSizeImage, 1, fp);
	free(image);
	fclose(fp);
	return true;
}
