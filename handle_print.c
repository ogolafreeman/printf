#include "main.h"
/**
 * handle_print - ...
 * @fmt: ...
 * @list: ...
 * @ind: ind.
 * @buffer: ...
 * @flags: ...
 * @width: get width.
 * @precision: ...
 * @size: Size specifier
 * Return: 1 or 2;
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, ulength = 0, prch = -1;
	fmt_t kinds[] = {
		{99, print_char}, {115, print_string}, {37, print_percent},
		{105, print_int}, {100, print_int}, {98, print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	i = 0;

	do {
		if (fmt[*ind] == kinds[i].fmt)
			return (kinds[i].fn(list, buffer, flags, width, precision, size));
		i++;
	} while (kinds[i].fmt != '\0');

	if (kinds[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		ulength = ulength + write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			ulength = ulength + write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			do {
				--(*ind);
			} while (fmt[*ind] != ' ' && fmt[*ind] != '%');
			if (fmt[*ind] == ' ')
			{
				--(*ind);
			}
			return (1);
		}
		ulength = ulength + write(1, &fmt[*ind], 1);
		return (ulength);
	}
	return (prch);
}

