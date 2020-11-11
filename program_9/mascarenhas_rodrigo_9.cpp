#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

void generateAudio(signed short int *array, float frequency, unsigned int size, unsigned int length);

int main(int argc, char const *argv[])
{
  float trackLength;
  float frequency;
  printf("\nEnter track length in seconds: ");
  scanf("%f", &trackLength);

  printf("Enter the desired frequency in Hz: ");
  scanf("%f", &frequency);

  // Riff Wave Header
  char chunkId[] = {'R', 'I', 'F', 'F'};
  int chunkSize;
  char format[] = {'W', 'A', 'V', 'E'};

  // Format Subchunk
  char subchunkId[] = {'f', 'm', 't', ' '};
  int subchunkSize = 16;
  short int audioFormat = 1;
  short int numOfChannels = 1;
  int sampleRate = 44100;
  short int bitsPerSample = 16;
  int byteRate = (sampleRate * numOfChannels * (bitsPerSample / 8));
  short int blockAlign = numOfChannels * (bitsPerSample / 8);

  int numOfSamples = (numOfChannels * trackLength * sampleRate);

  // Data Subchunk
  char subchunk2Id[] = {'d', 'a', 't', 'a'};
  int subchunk2Size = numOfChannels * numOfSamples * (bitsPerSample / 8);

  signed short int *data = (short int *)malloc(numOfSamples * sizeof(signed short int));
  generateAudio(data, frequency, sampleRate, numOfSamples);

  chunkSize = 36 + subchunk2Size;

  FILE *filePointer;
  filePointer = fopen("tone1.wav", "wb");

  fwrite(chunkId, 4, 1, filePointer);                                //        4    1-4 (chunkId)
  fwrite(&chunkSize, 4, 1, filePointer);                             //     4    5-8 (chunkSize)
  fwrite(format, 4, 1, filePointer);                                 //          4    9-12 (format)
  fwrite(subchunkId, 4, 1, filePointer);                             //     4    13-16 (subChunk1Id)
  fwrite(&subchunkSize, 4, 1, filePointer);                          //   4    17-20 (subHunk1Size)
  fwrite(&audioFormat, 2, 1, filePointer);                           //    2    21-22 (audioFormat)
  fwrite(&numOfChannels, 2, 1, filePointer);                         //  2    23-24 (channels)
  fwrite(&sampleRate, 4, 1, filePointer);                            //    4    25-28 (sampleRate)
  fwrite(&byteRate, 4, 1, filePointer);                              //       4    29-32 (byteRate)
  fwrite(&blockAlign, 2, 1, filePointer);                            //    2    33-34 (blockAlign)
  fwrite(&bitsPerSample, 2, 1, filePointer);                         // 2    36-36 (bitsPerSample)
  fwrite(&subchunk2Id, 4, 1, filePointer);                           //   4          (subChunk2Id)
  fwrite(&subchunk2Size, 4, 1, filePointer);                         // 4          (subChunkSize2Id)
  fwrite(data, numOfSamples, sizeof(signed short int), filePointer); // (data)

  fclose(filePointer);

  return 0;
}

void generateAudio(signed short int *array, float frequency, unsigned int sampleRate, unsigned int numOfSamples)
{

  int i;
  for (i = 0; i < numOfSamples; i++)
  {
    float omegaT = (2 * M_PI * frequency * i) / (float)sampleRate;
    array[i] = (pow(2, 15) - 1) * sin(omegaT);
  }
}
