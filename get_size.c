#include "main.h"

/**
 * get_size - ---
 * @format: ---
 * @i: ---
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

