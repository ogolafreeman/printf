#include "main.h"

/**
 * get_size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 *
 * Return: Precision.
 */
int get_size(const char *format, int *i)
{
	int current = *i + 1, magnitude = 0;

	if (format[current] == 49)
		magnitude = S_LONG;
	else if (format[current] == 104)
		magnitude = S_SHORT;

	if (magnitude == 0)
		*i = current - 1;
	else
		*i = current;

	return (magnitude);
}

