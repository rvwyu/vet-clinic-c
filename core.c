/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Rhowen Vaughn Wendelle Yu
Student ID#: 142671221
Email      : rvwyu@myseneca.ca
Section    : IPC144-ZRA

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "core.h"

//
// Copy your work done from Milestone #1 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
// - Also copy the commented "sections" to help with finding functions quickly!
//

// Clear the standard input buffer 
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue 
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

// takes an integer input from the user and checks if it's a whole number
int inputInt(void)
{
    int input;
    char newline = ' ';

    do
    {
        scanf("%d%c", &input, &newline);

        if (newline != '\n') {
            clearInputBuffer();
            printf("ERROR! Input a whole number: ");
        }
    } while (newline != '\n');

    return input;
}

// takes a positive integer input from the user, making sure it is > 0
int inputIntPositive(void)
{
    int input;
    char newline = ' ';

    do
    {
        scanf("%d%c", &input, &newline);

        if (newline != '\n') {
            clearInputBuffer();
            printf("ERROR! Input a number: ");
        }

        if (input <= 0) {
            printf("ERROR! Value must be > 0: ");
        }
    } while (input <= 0);

    return input;
}

// takes an integer input from the user within a specified range (minNumber and maxNumber)
int inputIntRange(int minNumber, int maxNumber)
{
    char newline = ' ';
    int numberInput;

    do
    {
        scanf("%d%c", &numberInput, &newline);

        if (newline != '\n') {
            clearInputBuffer();
            printf("ERROR! Input a whole number: ");
        }

        else if (!(numberInput <= maxNumber && numberInput >= minNumber)) {
            printf("ERROR! Value must be between %d and %d inclusive: ", minNumber, maxNumber);
        }
    } while (!(numberInput <= maxNumber && numberInput >= minNumber));

    return numberInput;
}

// validates a character input based on an array of valid characters
char inputCharOption(char str[])
{
    char value = 'x';
    int flag = 1;

    while (flag)
    {
        // get input character from user and check if it's in the given string
        scanf(" %c", &value);

        if (strchr(str, value) != NULL)
        {
            flag = 0;
        }
        else
        {
            printf("ERROR: Character must be one of [%s]: ", str);
        }
    }

    clearInputBuffer();
    return value;
}

// takes a string input from the user within a given length range (minChar and maxChar)
void inputCString(char* str, int minChar, int maxChar)
{
    int flag = 1;
    char c = 'x';

    while (flag)
    {
        int len = 0;

        // takes a string as input until it sees a newline character
        while (c != '\n' && len <= maxChar)
        {
            c = getchar(); // get a character from user input
            str[len] = c;  // store the character in the string
            len++;
        };

        if (c == '\n' && len <= (maxChar + 1))
        {
            len--;
            str[len] = '\0'; // set null terminator at end of string
        }

        else
        {
            str[maxChar] = '\0';
            clearInputBuffer();
        }

        if (minChar == maxChar && len != minChar)
        {
            printf("ERROR: String length must be exactly %d chars: ", minChar);
            c = 'x'; // reset the character
        }
        else if (len < minChar || len > maxChar)
        {
            if (len > maxChar)
            {
                printf("ERROR: String length must be no more than %d chars: ", maxChar);
                c = 'x'; // reset the character
            }
            else if (len < minChar)
            {
                printf("ERROR: String length must be between %d and %d chars: ", minChar, maxChar);
                c = 'x'; // reset the character
            }
        }
        else
        {
            flag = 0;
        }
    }
}

// takes a string input of numbers from the user within a given length range (minChar and maxChar)
void inputCStringNumbers(char* str, int minChar, int maxChar)
{
    int flag = 1;
    char ch = 'a';

    while (flag)
    {
        int len = 0;
        // takes a string as input until it sees a newline character
        while (ch != '\n' && len <= maxChar)
        {
            ch = getchar();
            str[len] = ch;
            len++;
        };

        // if the string is less than or equal to the maxChars, add '\0' to the end to mark the end of the string
        if (ch == '\n' && len <= (maxChar + 1))
        {
            len--;
            str[len] = '\0';
        }
        else
        {
            str[maxChar] = '\0';
            clearInputBuffer();
        }

        if (minChar == maxChar && len != minChar)
        {
            printf("Invalid 10-digit number! Number: ");
            ch = 'a';
        }
        else
        {
            flag = 0;
        }
    }
}

// checks if the phone number is valid (10 digits) and formats it
void displayFormattedPhone(const char* string)
{
    int number = 0, i;

    while (string != NULL && string[number] && isdigit(string[number])) {
        number++;
    }

    if (number == 10)
    {
        i = 0;
        printf("(");
        while (i < 3) {
            printf("%c", string[i]);
            i++;
        }
        printf(")");

        while (i < 6) {
            printf("%c", string[i]);
            i++;
        }
        printf("-");

        while (i < 10) {
            printf("%c", string[i]);
            i++;
        }
    }

    else {
        printf("(___)___-____");
    }

    if (string != 0) {
        for (i = 0; string[i] != '\0'; i++)
            number++;
    }
}

// checks if the given year is a leap year
int isLeapYear(int year) {
    if ((year % 400 == 0) || (year % 100 != 0 && year % 4 == 0)) {
        return 1; // Leap year
    }
    return 0; // Not a leap year
}
