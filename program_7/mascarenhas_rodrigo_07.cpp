#include <stdio.h>
#include <string.h>

void get_str(char *);
void reverse_str(char *);
int main(int argc, char const *argv[])
{
  char string[201];
  char *pointer = string;

  get_str(pointer);
  reverse_str(pointer);
}

void get_str(char *arr_pointer)
{
  char curr;
  int count = 0;

  printf("\nPlease enter a string press <Enter> when done:\n");
  while (count < 201)
  {
    if (curr == '\n')
      break;
    scanf("%c", &curr);
    arr_pointer[count] = curr;
    count++;
  }
}

void reverse_str(char *arr_pointer)
{

  int i;
  int n = strlen(arr_pointer);
  printf("Reversed: ");
  for (i = n; i >= 0; i--)
  {
    printf("%c", arr_pointer[i]);
  }
  printf("\n");
}
