#include "main.h"

/**
 * print_char - ...
 * @types: ...
 * @buffer: ...
 * @width: ...
 * @size: ...
 * @flags: ...
 * @precision: ...
 *
 * Return: Characted printed
 */
int print_char(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	char a = va_arg(types, int);

	return (handle_write_char(a, buffer, flags, width, precision, size));
}

/**
 * print_string - ...
 * @types: ...
 * @size: ...
 * @width: ...
 * @buffer: ...
 * @precision: ...
 * @flags: active flags
 *
 * Return: ...
 */
int print_string(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int len = 0, x;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(width);
	UNUSED(size);
	UNUSED(precision);
	UNUSED(flags);

	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = " ";
	}
	while (str[len] != '\0')
		len++;
	if (precision >= 0 && precision < len)
		len = precision;
	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], len);
			for (x = width - len; x > 0; x--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (x = width - len; x > 0; x--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}
	return (write(1, str, len));
}

/**
 * print_percent - ...
 * @types: ...
 * @buffer: ...
 * @size: ...
 * @width: width
 * @precision: ...
 * @flags: active flags
 *
 * Return: Number of printed chars
 */
int print_percent(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	UNUSED(buffer);
	UNUSED(types);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * print_int - ...
 * @types: ...
 * @buffer: ...
 * @size: ...
 * @width: width
 * @precision: ...
 * @flags: ...
 *
 * Return: ...
 */
int print_int(va_list types, char buffer[], int width,
		int flags, int precision, int size)
{
	int x = BUFF_SIZE - 2;
	int negative = 0;
	long int y = va_arg(types, long int);
	unsigned long int number;

	y = convert_size_number(y, size);
	if (y == 0)
		buffer[x--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	number = (unsigned long int)y;

	if (y < 0)
	{
		number = (unsigned long int)((-1) * y);
		negative = 1;
	}
	while (number > 0)
	{
		buffer[x--] = (number % 10) + '0';
		number /= 10;
	}
	x++;

	return (write_number(negative, x, buffer, flags, width, precision, size));
}
/****** print binary *****/
/**
 * print_binary - 
 * @types: list arguments
 * @buffer: ...
 * @size: ...
 * @width: width
 * @precision: ...
 * @flags: ...
 *
 * Return: Number of printed chars
 */
int print_binary(va_list types, char buffer[], int precision,
		int size, int width, int flags)
{
	unsigned int o, p, q, r;
	unsigned int a[32];
	int count;

	UNUSED(flags);
	UNUSED(size);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(buffer);

	o = va_arg(types, unsigned int);
	p = 2147483648;
	a[0] = o / p;
	for (q = 1; q < 32; q++)
	{
		p /= 2;
		a[q] = (o / p) % 2;
	}
	for (q = 0, r = 0, count = 0; q < 32; q++)
	{
		r += a[q];
		if (r || q == 31)
		{
			char z = '0' + a[q];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
