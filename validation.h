#ifndef VALIDATION_H
#define VALIDATION_H

/* Whole number from min to max (inclusive). */
int readInt(char prompt[], int min, int max);

/* Decimal number from min to max (inclusive). */
double readDouble(char prompt[], double min, double max);

/* Text that is not empty. Stored in text[]; size is the array size. */
void readString(char prompt[], char text[], int size);

/* Menu choice from min to max. */
int readChoice(int min, int max);

#endif
