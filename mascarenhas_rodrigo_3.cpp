#include <stdio.h>
#include <string.h>

int main()
{
    bool scan = true;
    FILE *outFile;
    outFile = fopen("out.txt", "w");

    while (scan)
    {
        float balance;
        char name;

        printf("Enter your name: \n");
        int input = scanf("%c", &name);

        fprintf(outFile, "%c", name);

        if (name == '\n')
        {
            printf("Enter your balance:");
            input = scanf("%f", &balance);
            fprintf(outFile, "$%.2f\n======================", balance);
            break;
        }
    }
    fclose(outFile);
}