#include "main.h"

/**
 * get_flags ---
 * @format: ---
 * @i: ---
 * Return: Flags:
 */
int get_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int j = 0, current = *i + 1, flags = 0;
	const char FL_CHAR[] = {45, 43, '0', '#', ' ', '\0'};
	const int FL_ARRAY[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (; format[current] != '\0'; current++)
	{
		for (; FL_CHAR[j] != '\0'; j++)
			if (format[current] == FL_CHAR[j])
			{
				flags |= FL_ARRAY[j];
				break;
			}

		if (FL_CHAR[j] == 0)
			break;
	}

	*i = current - 1;

	return (flags);
}
