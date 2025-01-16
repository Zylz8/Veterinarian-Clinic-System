/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 1
Full Name  : Jackey Zhou
Student ID#: 164431223
Email      : jzhou200@myseneca.ca
Section    : NDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include "core.h"

// As demonstrated in the course notes:
// https://intro2c.sdds.ca/D-Modularity/input-functions#clearing-the-buffer
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

int inputInt(void) {
    char newLine = 'x';
    int value;

    while (newLine != '\n') {

        scanf("%d%c", &value, &newLine);

        if (newLine != '\n') {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    }
    return value;
}

int inputIntPositive(void) {
    int value;

    do {

        value = inputInt();
        if (value <= 0) {
            printf("ERROR! Value must be > 0: ");
        }
    } while (value <= 0);
    return value;
}

int inputIntRange(int lowerBoundRange, int upperBoundRange) {
    int value;

    do {

        value = inputInt();
        if (value < lowerBoundRange || value > upperBoundRange) {
            printf("ERROR! Value must be between -3 and 11 inclusive: ");
        }

    } while (value < lowerBoundRange || value > upperBoundRange);
    return value;
}

char inputCharOption(const char cStringArray[]) {
    char validCharacterFound = 0;
    char value;
    int i;

    do {

        scanf("%c", &value);

        for (i = 0; cStringArray[i] != '\0'; i++) {
            if (cStringArray[i] == value) {
                validCharacterFound++;
            }
        }

        if (validCharacterFound == 0) {
            printf("ERROR: Character must be one of [%s]: ", cStringArray);
            clearInputBuffer();
        }

    } while (validCharacterFound == 0);
    return value;
}

void inputCString(char* cString, int minimum, int maximum) {
    char value[100];
    int characterLength;
    int validate = 0;
    int i;

    do {

        scanf(" %99[^\n]", value);

        characterLength = 0;
        while (value[characterLength] != '\0') {
            characterLength++;
        }

        if (characterLength >= minimum && characterLength <= maximum) {
            for (i = 0; i < characterLength; i++) {
                cString[i] = value[i];
            }
            cString[characterLength] = '\0';
            validate = 1;
        }
        else {
            if (minimum == maximum) {
                printf("ERROR: String length must be exactly %d chars: ", minimum);
            }
            else if (characterLength > maximum) {
                printf("ERROR: String length must be no more than %d chars: ", maximum);
            }
            else {
                printf("ERROR: String length must be between %d and %d chars: ", minimum, maximum);
            }
        }
    } while (validate != 1);
}

void displayFormattedPhone(const char* phoneFormat) {
    
    int digit = 0;
    int countDigit = 0;
    int i;

    if (phoneFormat == NULL) {
        printf("(___)___-____"); 
    }
    else {
        for (i = 0; phoneFormat[i] != '\0'; i++) {
            if (phoneFormat[i] >= '0' && phoneFormat[i] <= '9') {
                countDigit++;
                digit++;
            }
        }
        if (digit == 10 || countDigit == 10) {
            printf("(%c%c%c)%c%c%c-%c%c%c%c",
                phoneFormat[0], phoneFormat[1], phoneFormat[2],
                phoneFormat[3], phoneFormat[4], phoneFormat[5],
                phoneFormat[6], phoneFormat[7], phoneFormat[8],
                phoneFormat[9]);
        }
        else {
            printf("(___)___-____");
        }
    }
}
