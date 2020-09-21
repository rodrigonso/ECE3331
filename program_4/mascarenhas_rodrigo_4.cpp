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
  (ch <= 68 && ch >= 48) ? value = 2 : NULL;
  ch == 32 ? value = 3 : NULL;
  ch == 46 ? value = 4 : NULL;
  ch == 10 ? value = 5 : NULL;

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
    break;
  }

  return ch;
}

char decode(char ch)
{
  int value;
  (ch <= 58 && ch >= 33) ? value = 1 : NULL;
  (ch <= 68 && ch >= 59) ? value = 1 : NULL;
  ch == 69 ? value = 3 : NULL;
  ch == 70 ? value = 4 : NULL;
  ch == 71 ? value = 5 : NULL;

  switch (value)
  {
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
  FILE *file;
  FILE *out;
  file = (action == 'e') ? fopen("decoded.txt", "r") : fopen("encoded.txt", "r");
  out = (action == 'e') ? fopen("encoded.txt", "w") : fopen("decoded.txt", "w");

  while (input != EOF)
  {
    char current;
    char res;
    input = fscanf(file, "%c", &current);
    res = (action == 'e') ? encode(current) : decode(current);
    fprintf(out, "%c", res);
  }

  fclose(file);
  fclose(out);
}
