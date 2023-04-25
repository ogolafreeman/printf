#include "main.h"

/**
 * get_precision - ...
 * @format: ...
 * @i: ...
 * @list: ...
 *
 * Return: Precision.
 */
int get_precision(const char *format, int *i, va_list list)
{
	int current = *i + 1, precision = -1;

	if (format[current] != 46)
		return (precision);

	precision = 0;
	current = current + 1;

	do {
		if (is_digit(format[current]))
		{
			precision = precision * 10;
			precision = precision + format[current] - '0';
		}
		else if (format[current] == 42)
		{
			current++;
			precision = va_arg(list, int);
			break;
		}
		else
		{
			break;
		}
		current++;
	} while (format[current] != '\0');

	*i = current - 1;

	return (precision);
}
