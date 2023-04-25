#include "main.h"

/**
 * convert_size_unsgnd - ...
 * @num: ...
 * @size: ...
 *
 * Return: Casted value of num
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
	{
		return (num);
	}
	else if (size == S_SHORT)
	{
		return ((unsigned short)num);
	}

	return ((unsigned int)num);
}

/**
 * append_hexa_code - ...
 * @buffer: ...
 * @i: ...
 * @a: ...
 * Return: Always 3
 */
int append_hexa_code(char a, char buffer[], int i)
{
	char connect[] = "0123456789ABCDEF";

	if (a < 0)
		a = a * -1;

	buffer[i++] = '\\';
	buffer[i++] = 120;

	buffer[i++] = connect[a / 16];
	buffer[i] = connect[a % 16];

	return (3);
}


/**
 * convert_size_number - ...
 * @num: ...
 * @size: ...
 *
 * Return: Casted value of num
 */
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
	{
		return (num);
	}
	else if (size == S_SHORT)
	{
		return ((short)num);
	}
	else
	{
	return ((int)num);
	}
}

/**
 * is_printable - ...
 * @c: ...
 * Return: ...
 */
int is_printable(char c)
{
	if (c >= ' ' && c < 127)
		return (1);

	return (0);
}

/**
 * is_digit - ...
 * @c: ...
 * Return: 1 if c is a digit, 0 otherwise
 */
int is_digit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);

	return (0);
}
