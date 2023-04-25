#include "main.h"

/***** WRITE HANDLE ****/
/**
 * handle_write_char - prints a string
 * @c: char types.
 * @buffer: buffer array
 * @width: gets width
 * @precision: specifies precision
 * @flags: active flags
 * @size: specifies size
 *
 * Return: Number of printed chars
 */
int handle_write_char(char c, char buffer[], int flags,
		int width, int precision, int size)
{
	int x = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

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
			return (write(1, buffer[BUFF_SIZE - x - 1], width - 1) +
					write(1, &buffer[0], 1));
	}
	return (write(1, &buffer[0], 1));
}
