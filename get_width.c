#include "main.h"

/**
 * get_width - ...
 * @format: ...
 * @i: ...
 * @list: list of arguments.
 *
 * Return: width.
 */
int get_width(const char *format, int *i, va_list list)
{
	int current = *i + 1, width = 0;

	do {
		if (is_digit(format[current]))
		{
			width = width * 10;
			width = width + format[current] - '0';
		}
		else if (format[current] == '*')
		{
			current++;
			width = va_arg(list, int);
			break;
		}
		else
		{
			break;
		}
		current++;
	} while (format[current] != '\0');

	*i = curent - 1;

	return (width);
}
