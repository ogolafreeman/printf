#include "main.h"

/**
 * handle_write_char - ...
 * @c: char types.
 * @buffer: buffer array
 * @width: gets width
 * @precision: ...
 * @flags: active flags
 * @size: specifies size
 *
 * Return: ...
 */
int handle_write_char(char c, char buffer[], int flags,
		int width, int precision, int size)
{
	int x = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = 48;

	buffer[x++] = c;
	buffer[x] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (x = 0; x < width - 1; x++)
			buffer[BUFF_SIZE - x - 2] = padd;
		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - x - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - x - 1], width - 1) +
					write(1, &buffer[0], 1));
	}
	return (write(1, &buffer[0], 1));
}

/**
 * write_num - ...
 * @ind: ...
 * @buffer: ...
 * @flags: Flags
 * @width: width
 * @prec: ...
 * @length: Number length
 * @padd: Pading char
 * @extra_c: Extra char
 *
 * Return: ...
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	else if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' ';
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - ...
 * @is_negative: ...
 * @ind: ...
 * @buffer: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: ...
 * @size: ...
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1, i = 0;
	char padd = 32, a = width - length;

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0);

	if (precision > 0 && precision < length)
		padd = 32;

	do {
		buffer[--ind] = '0';
		length++;
	}  while (precision > length);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	i = 0;

	if (width > length)
	{
		for (; i < a; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - ...
 * @buffer: Arrays
 * @ind: ...
 * @length: ...
 * @width: Width specifier
 * @flags: Flags specifier
 * @padd: ...
 * @extra_c: ...
 * @padd_start: ...
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int i = 3, a = width - length;

	if (width > length)
	{
		for (; i < a + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
/**
 * write_number - ...
 * @is_negative: ...
 * @ind: char types.
 * @buffer: ...
 * @flags: ...
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: ...
 */

int write_number(int is_negative, int ind, char buffer[],
        int flags, int width, int precision, int size)
{
        int length = BUFF_SIZE - ind - 1;
        char padd = ' ', extra_ch = 0;

        UNUSED(size);

        if ((flags & F_ZERO) && !(flags & F_MINUS))
                padd = '0';
        if (is_negative)
                extra_ch = 45;
        else if (flags & F_PLUS)
                extra_ch = '+';
        else if (flags & F_SPACE)
                extra_ch = ' ';

        return (write_num(ind, buffer, flags, width, precision,
                length, padd, extra_ch));
}
