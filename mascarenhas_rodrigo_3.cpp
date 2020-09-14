#include <stdio.h>
#include <string.h>

int main()
{
    int input;
    char currentChar;
    char enterPlaceholder;
    bool addMore = true;
    float balance;

    FILE *outFile;
    outFile = fopen("out.txt", "w");

    while (addMore == true)
    {
        printf("Please enter your full name: ");
        input = scanf("%c", &currentChar);
        while (currentChar != '\n')
        {
            input = scanf("%c", &currentChar);
            fprintf(outFile, "%c", currentChar);
        }

        fprintf(outFile, ": $");
        printf("Please enter your balance: ");
        input = scanf("%f%c", &balance, &enterPlaceholder);
        fprintf(outFile, "%0.2f", balance);

        char tmp;
        printf("Add another person ? (y/n) : ");
        scanf("%c%c", &tmp, &enterPlaceholder);
        if (tmp == 'n' || tmp == 'N')
        {
            addMore = false;
            break;
        }
    }
    fclose(outFile);
    return 0;
}