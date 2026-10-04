#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "validation.h"

void clearInputLine(void);

/*throws away the rest of the current input line */
void clearInputLine(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

int readInt(char prompt[], int min, int max)
{
    int value = 0;
    int result;
    int next;
    int valid = 0;

    while (!valid)
    {
        printf("%s", prompt);
        result = scanf("%d", &value);

        if (result == EOF)
        {
            printf("\nInput ended. Closing the program.\n");
            exit(0);
        }
        /*the character straight after the number must be Enter*/
        next = getchar();

        if (result != 1)
        {
            printf(" Invalid input. Please enter a whole number.\n");

            if (next != '\n')
            {
                clearInputLine();
            }
        }
        else if (next != '\n')
        {
            printf(" Invalid input. Enter the number only.\n");
            clearInputLine();
        }
        else if (value < min || value > max)
        {
            printf(" Invalid input. Please enter a number from %d to %d.\n", min, max);
        }
        else
        {
            valid = 1;
        }
    }
    return value;
}

double readDouble(char prompt[], double min, double max)
{
    double value = 0.0;
    int result;
    int next;
    int valid = 0;

    while (!valid)
    {
        printf("%s", prompt);
        result = scanf("%lf", &value);

        if (result == EOF)
        {
            printf("\nInput ended. Closing the program.\n");
            exit(0);
        }

        next = getchar();

        if (result != 1)
        {
            printf(" Invalid input. Please enter a decimal number.\n");

            if (next != '\n')
            {
                clearInputLine();
            }
        }
        else if (next != '\n')
        {
            printf(" Invalid input. Enter the number only.\n");
            clearInputLine();
        }
        else if (!(value >= min && value <= max))
        {
            printf(" Invalid input. Please enter a number from %.2f to %.2f.\n", min, max);
        }
        else
        {
            valid = 1;
        }
    }
    return value;
}

void readString(char prompt[], char text[], int size)
{
    int valid = 0;
    int length;
    int i;
    int hasText;

    while (!valid)
    {
        printf("%s", prompt);
        if (fgets(text, size, stdin) == NULL)
        {
            printf("\nInput ended. Closing the program.\n");
            exit(0);
        }

        /*remove newline that fgets() keeps */
        length = (int)strcspn(text, "\n");

        if (text[length] != '\n')
        {

            /*no newline found: the line was longer than the array*/
            clearInputLine();
            printf(" Input too long (maximum %d characters). \n", size - 1);
            continue;
        }

        text[length] = '\0';

        hasText = 0;
        for (i = 0; i < length; i++)
        {
            if (text[i] != ' ')
            {
                hasText = 1;
            }
        }
        if (hasText)
        {
            valid = 1;
        }
        else
        {
            printf("This field cannot be empty.\n");
        }
    }
}
int readChoice(int min, int max)
{
    return readInt("Enter your choice: ", min, max);
}
