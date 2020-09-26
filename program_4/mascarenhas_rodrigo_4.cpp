#include <stdio.h>

char encodeOrDecode()
{
  char action;
  while (true)
  {
    char buffer;
    printf("Enter 'e' to encode or 'd' to decode: ");
    scanf("%c%c", &action, &buffer);
    if (action == 'e' || action == 'd')
      break;
  }
  return action;
}

char encode(char ch)
{
  int value = -1;

  (ch <= 122 && ch >= 97) ? value = 1 : NULL;
  (ch <= 57 && ch >= 48) ? value = 2 : NULL;
  ch == 32 ? value = 3 : NULL;
  ch == 46 ? value = 4 : NULL;
  (ch == 10 || ch == 13) ? value = 5 : NULL;

  switch (value)
  {
  case 1:
    // a-z
    ch -= 64;
    break;
    // break;
  case 2:
    // 0-9
    ch -= 11;
    break;
  case 3:
    // space
    ch = 69;
    break;
  case 4:
    // period
    ch = 70;
    break;
  case 5:
    // new line
    ch = 71;
    break;
  default:
    ch = -1;
    break;
  }

  return ch;
}

char decode(char ch)
{
  int value;
  (ch <= 58 && ch >= 33) ? value = 1 : NULL;
  (ch <= 68 && ch >= 59) ? value = 2 : NULL;
  ch == 69 ? value = 3 : NULL;
  ch == 70 ? value = 4 : NULL;
  ch == 71 ? value = 5 : NULL;

  switch (value)
  {
  case -1:
    // invalid
    ch = -1;
    break;
  case 1:
    // a-z
    ch += 64;
    break;
    // break;
  case 2:
    // 0-9
    ch += 11;
    break;
  case 3:
    // space
    ch = 32;
    break;
  case 4:
    // period
    ch = 46;
    break;
  case 5:
    // new line
    ch = 10;
    break;
  default:
    break;
  }

  return ch;
}

int main()
{
  char action = encodeOrDecode();

  int input;
  FILE *in;
  FILE *out;
  in = fopen("input.txt", "r");
  out = fopen("output.txt", "w");

  while (input != EOF)
  {
    char current;
    char res;
    input = fscanf(in, "%c", &current);
    if (input == EOF)
      break;
    res = (action == 'e') ? encode(current) : decode(current);
    if (res != -1)
      fprintf(out, "%c", res);
  }

  fclose(in);
  fclose(out);
}
