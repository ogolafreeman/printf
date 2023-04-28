#include "main.h"

/**
 * print_octal - ...
 * @types: ...
 * @buffer: ...
 * @width: ...
 * @size: ...
 * @flags: ...
 * @precision: ...
 *
 * Return: Characted printed
 */
int print_pointer(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char ex_c = 0, padd = ' ';
	int index = BUFF_SIZE - 2, len = 2, pd_start = 1;
	unsigned long no_adds;
	char map_to[] = "0123456789abcdef";
	void *address = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (address == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	no_adds = (unsigned long)address;

	for (; no_adds > 0; no_adds /= 16, len++)
	{
		buffer[index--] = map_to[no_adds % 16];
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		ex_c = '+', len++;
	else if (flags & F_SPACE)
		ex_c = ' ', len++;
	index++;

	return (write_pointer(buffer, index, len,
				width, flags, padd, ex_c, pd_start));
}

/**
 * print_non_prinatble - ...
 * @types: ...
 * @buffer: ...
 * @width: fetch width
 * @size: ...
 * @flags: ...
 * @precision: ...
 *
 * Return: Characted printed
 */
int print_non_printable(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int x = 0, os = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);
	UNUSED(precision);

	if (str == NULL)
		return (write(1, "(null)", 6));

	do {
		if (is_printable(str[x]))
			buffer[x + os] = str[x];
		else
			os = os + append_hexa_code(str[x], buffer, x + os);
		x++;
	} while (str[x - 1] != '\0');
	buffer[x + os] = '\0';

	return (write(1, buffer, x + os));
}

/**
 * print_reverse -...
 * @types: ...
 * @buffer: ...
 * @width: ...
 * @size: ...
 * @flags: ...
 * @precision: ...
 *
 * Return: Characted printed
 */
int print_reverse(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char *str;
	int x, cnt = 0;

	UNUSED(flags);
	UNUSED(size);
	UNUSED(width);
	UNUSED(buffer);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = "(Null)";
	}

	x = 0;
	do {
		x++;
	} while (str[x]);

	x--;

	do {
		char z = str[x];

		write(1, &z, 1);
		cnt++;
		x--;
	} while (x >= 0);

	return (cnt);
}
/**
 * print_rot13string - ...
 * @types: ...
 * @buffer: ...
 * @width: ...
 * @size: ...
 * @flags: ...
 * @precision: specifies precision
 *
 * Return: Characted printed
 */
int print_rot13string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char m;
	char *str;
	unsigned int n, o;
	int cnt = 0;
	char in[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] =
		"NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(size);
	UNUSED(precision);
	UNUSED(flags);
	UNUSED(buffer);
	UNUSED(width);

	if (str == NULL)
		str = "(AHYY)";
	n = 0;
	do {
		o = 0;
		while (in[o] && in[o] != str[n])
			o++;
		if (in[o] == str[n])
			m = out[o];
		else
			m = str[n];
		write(1, &m, 1);
		cnt++;
		m++;
	} while (str[n - 1]);

	return (cnt);
}
