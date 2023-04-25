#include "main.h"

/******* Print unsigned number in octal *****/
/**
 * print_octal - prints unsigned number in octal
 * @types: list of arguments
 * @buffer: BUffer array to handle print
 * @width: fetch width
 * @size: specifies size
 * @flags: Calculates active flags
 * @precision: specifies precision
 *
 * Return: Characted printed
 */
int print_octal(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int x = BUFF_SIZE - 2;
	unsigned long int number = va_arg(types, unsigned long int);
	unsigned long int int_num = number;

	UNUSED(width);

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		buffer[x--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[x--] = (number % 8) + '0';
		number /= 8;
	}
	if (flags & F_HASH && int_num != 0)
		buffer[x--] = '0';
	x++;

	return (write_unsgnd(0, x, buffer, flags, width, precision, size));
}
/******** print unsigned number in upper hexadecimal *****/
/**
 * print_hexa_upper - prints unsigned number in upper hexadecimal
 * notation
 * @types: list of arguments
 * @buffer: BUffer array to handle print
 * @width: fetch width
 * @size: specifies size
 * @flags: Calculates active flags
 * @precision: specifies precision
 *
 * Return: Characted printed
 */
int print_hexa_upper(va_list types, char buffer[], int width,
		int flags, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
				flags, 'X', width, precision, size));
}
/******** print unsigned number in hexadecimal *****/
/**
 * print_hexadecimal - prints unsigned number in hexadecimal notation
 * notation
 * @types: list of arguments
 * @buffer: BUffer array to handle print
 * @width: fetch width
 * @size: specifies size
 * @flags: Calculates active flags
 * @precision: specifies precision
 * Return: Characted printed
 */
int print_hexadecimal(va_list types, char buffer[], int width,
		int flags, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
				flags, 'X', width, precision, size));
}
/******** print unsigned number *****/
/**
 * print_unsigned - prints unsigned number
 * notation
 * @types: list of arguments
 * @buffer: BUffer array to handle print
 * @width: fetch width
 * @size: specifies size
 * @flags: Calculates active flags
 * @precision: specifies precision
 *
 * Return: Characted printed
 */
int print_unsigned(va_list types, char buffer[], int width,
		int flags, int precision, int size)
{
	int x = BUFF_SIZE - 2;
	unsigned long int number = va_arg(types, unsigned long int);

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		buffer[x--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[x--] = (number % 10) + '0';
		number /= 10;
	}
	x++;

	return (write_unsgnd(0, x, buffer, flags, width, precision, size));
}
/******** print hexx number in lower or upper *****/
/**
 * print_hexa - prints a hexadecimal number in lower or upper
 * @map_to: Array values to map the number to
 * @flag_ch: flag active
 * @size: specification
 * @types: list of arguments
 * @buffer: BUffer array to handle print
 * @width: fetch width
 * @size: specifies size
 * @flags: Calculates active flags
 * @precision: specifies precision
 *
 * Return: Characted printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
		int flags, char flag_ch, int width, int precision, int size)
{
	int x = BUFF_SIZE - 2;
	unsigned long int number = va_arg(types, unsigned long int);
	unsigned long int int_num = number;

	UNUSED(width);

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		buffer[x--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[x--] = map_to[number % 16];
		number /= 16;
	}
	if (flags & F_HASH && int_num != 0)
	{
		buffer[x--] = flag_ch;
		buffer[x--] = '0';
	}
	x++;

	return (write_unsgnd(0, x, buffer, flags, width, precision, size));
}
