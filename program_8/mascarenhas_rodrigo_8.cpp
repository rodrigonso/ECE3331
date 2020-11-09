#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// function signatures
FILE *get_file();

int main(int argc, char const *argv[])

{
  FILE *file_pointer = NULL;
  while (file_pointer == NULL)
  {
    file_pointer = get_file();
  }

  char *header = (char *)malloc(44);
  fread(header, 1, 44, file_pointer);
  int size[] = {4, 4, 4, 4, 4, 2, 2, 4, 4, 2, 2, 4, 4};
  // int size[] = {0, 4, 8, 12, 4, 2, 2, 4, 4, 2, 2, 4, 4};
  char form[] = {'c', 'u', 'c', 'c', 'u', 's', 's', 's', 's', 's', 's', 'c', 'u'};

  char *chunk_id = header;
  unsigned int *chunk_size = (unsigned int *)header + 4;
  char *format = (char *)header + 8;
  char *subchunk1_id = header + 12;
  unsigned int *subchunk1_size = (unsigned int *)header + 16;
  unsigned short int *audio_format = (unsigned short int *)header + 20;
  unsigned short int *num_channels = (unsigned short int *)header + 22;
  unsigned short int *sample_rate = (unsigned short int *)header + 24;
  unsigned short int *byte_rate = (unsigned short int *)header + 28;
  unsigned short int *block_align = (unsigned short int *)header + 32;
  unsigned short int *bytes_per_sample = (unsigned short int *)header + 34;
  char *subchunk2_id = header + 36;
  unsigned int *subchunk2_size = (unsigned int *)header + 40;

  int prev = 0;
  for (int i = 0; i < 13; i++)
  {
    printf("\n");
    int j = prev;
    int k = prev + size[i];
    prev = prev + size[i];
    while (j < k)
    {
      if (form[i] == 'c')
      {
        printf("%c", *(header + j));
      }
      else if (form[i] == 's')
      {
        printf("%hu", *(header + j));
      }
      else
      {
        printf("%u", *(header + j));
      }
      j++;
    }
  }
  fclose(file_pointer);
  return 0;
}

FILE *get_file()
{
  char file_path[255];
  printf("Please enter the absolute path of the .wav file: \n");
  int res = scanf("%s", &file_path[0]);

  if (res == -1)
    return NULL;
  char *ext = file_path + strlen(file_path) - 4;
  if (ext[0] != '.')
    return NULL;
  if (tolower(ext[1]) != 'w')
    return NULL;
  if (tolower(ext[2]) != 'a')
    return NULL;
  if (tolower(ext[3]) != 'v')
    return NULL;
  else
  {
    FILE *res = fopen(file_path, "rb");
    if (res == NULL)
    {
      printf("The file entered does not exist, please try again\n");
      return NULL;
    }
    else
    {
      return res;
    }
  };
}
