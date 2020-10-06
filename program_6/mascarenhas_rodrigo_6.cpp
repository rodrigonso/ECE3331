#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

void initiate_probs(float *array);
int main(int argc, char const *argv[])
{
  float prob_interval[] = {0.2, 0.27, 0.22, 0.14, 0.09, 0.08};
  initiate_probs(prob_interval);

  int num_letters = 2;
  srand((long)&num_letters);
  int num_words = rand() % (20 + 1 - 10) + 10;

  for (int i = 0; i < num_words; i++)
  {
    float x = rand() / (float)(RAND_MAX);

    for (int j = 1; j < 6; j++)
    {
      if (x >= prob_interval[j - 1] && x <= prob_interval[j])
        num_letters = j + 2;
    }
    for (int k = 0; k < num_letters; k++)
    {
      int letter = rand() % (122 + 1 - 97) + 97;
      printf("%c", i == 0 && k == 0 ? toupper(letter) : letter);
    }
    i > 0 ? (i == num_words - 1) ? printf(".\n") : printf(" ") : NULL;
  }
  return 0;
}

void initiate_probs(float *array)
{
  for (int i = i; i < 6; i++)
  {
    array[i] += array[i - 1];
  }
}
