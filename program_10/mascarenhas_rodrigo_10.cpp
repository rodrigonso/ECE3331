#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMPRESSION 0
#define NUM_COLORS 0
#define NUM_PLANES 0
#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40
#define BITS_PER_PIXEL 24
#define BYTES_PER_PIXEL 3 // RGB
#define IMPORTANT_COLORS 0

int *getSize();
char *getFileName();
unsigned char *createBMPFileHeader(int height, int width);
unsigned char *createBMPInfoHeader(int height, int width);
void generateBMPImage(unsigned char *image, int height, int width, char *fileName);
int calculateBytesInImageRow(int width);

int main(int argc, char const *argv[])
{

  int *dimensions = getSize();
  char *fileName = getFileName();

  int height = dimensions[0];
  int width = dimensions[1];

  unsigned char image[height][width][BYTES_PER_PIXEL];
  int i, j;
  for (i = 0; i < height; i++)
  {
    for (j = 0; j < width; j++)
    {
      image[i][j][2] = (unsigned char)(i * 255 / height);
      image[i][j][1] = (unsigned char)(j * 255 / width);
      image[i][j][0] = (unsigned char)((i + j) * 255 / (height + width));
    }
  }

  generateBMPImage((unsigned char *)image, height, width, fileName);
  printf("| BMP File generated and saved in the current directory as: %s |\n", fileName);
  return 0;
}

int *getSize()
{
  static int dimensions[2];

  printf("Please enter the width of the image (in pixels): ");
  scanf("%i", &dimensions[1]);

  printf("Please enter the height of the image (in pixels): ");
  scanf("%i", &dimensions[0]);

  return dimensions;
}

char *getFileName()
{
  static char fileName[256];

  printf("Please enter the desired file name: ");
  scanf("%s", fileName);

  return fileName;
}

unsigned char *createBMPFileHeader(int height, int stride)
{
  int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);
  static unsigned char fileHeader[14];
  fileHeader[0] = (unsigned char)('B');
  fileHeader[1] = (unsigned char)('M');
  fileHeader[2] = (unsigned char)(fileSize);
  fileHeader[3] = (unsigned char)(fileSize >> 8);
  fileHeader[4] = (unsigned char)(fileSize >> 16);
  fileHeader[5] = (unsigned char)(fileSize >> 24);
  fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

  return fileHeader;
}

unsigned char *createBMPInfoHeader(int height, int width)
{
  static unsigned char infoHeader[40];
  infoHeader[0] = (unsigned char)(INFO_HEADER_SIZE);
  infoHeader[4] = (unsigned char)(width);
  infoHeader[5] = (unsigned char)(width >> 8);
  infoHeader[6] = (unsigned char)(width >> 16);
  infoHeader[7] = (unsigned char)(width >> 24);
  infoHeader[8] = (unsigned char)(height);
  infoHeader[9] = (unsigned char)(height >> 8);
  infoHeader[10] = (unsigned char)(height >> 16);
  infoHeader[11] = (unsigned char)(height >> 24);
  infoHeader[12] = (unsigned char)(NUM_PLANES);
  infoHeader[14] = (unsigned char)(BITS_PER_PIXEL);

  return infoHeader;
}

void generateBMPImage(unsigned char *image, int height, int width, char *fileName)
{

  FILE *fp = fopen(fileName, "wb");

  int widthInBytes = width * BYTES_PER_PIXEL;

  unsigned char padding[3] = {0, 0, 0};
  int paddingSize = (4 - (widthInBytes) % 4) % 4;

  int stride = widthInBytes + paddingSize;

  unsigned char *bmpFileHeader = createBMPFileHeader(height, stride);
  fwrite(bmpFileHeader, 1, FILE_HEADER_SIZE, fp);
  unsigned char *bmpInfoHeader = createBMPInfoHeader(height, width);
  fwrite(bmpInfoHeader, 1, INFO_HEADER_SIZE, fp);

  int i;
  for (i = 0; i < height; i++)
  {
    fwrite(image + (i * widthInBytes), BYTES_PER_PIXEL, width, fp);
    fwrite(padding, 1, paddingSize, fp);
  }

  fclose(fp);
}
