#include "main.h"
/**
 * handle_print - ...
 * @fmt: ---
 * @list: ---
 * @ind: ind.
 * @buffer: ---
 * @flags: ---
 * @width: ---
 * @precision: ---
 * @size: ---
 * Return: 1 or 2;
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0, ulength = 0, prch = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	do {
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fn(list, buffer, flags, width, precision, size));
	i++;
	} while (fmt_types[i].fmt != '\0');
	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
		{
			return (-1);
		}
		ulength = ulength + write(1, "%%", 1);
		if (fmt[*ind - 1] == 32)
			ulength = ulength + write(1, 32, 1);
		else if (width)
		{
			--(*ind);
			do {
				--(*ind);
			}
			if (fmt[*ind] == 32)
			{
				--(*ind);
			} while (fmt[*ind] != 32 && fmt[*ind] != 37);
			else
			return (1);
		}
		ulength = ulength + write(1, &fmt[*ind], 1);
		return (ulength);
	}
	return (prch);
}

