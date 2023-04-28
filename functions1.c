#include "main.h"

/**
 * print_octal - ...
 * @types: ...
 * @buffer: ...
 * @width: ...
 * @size:...
 * @flags: ...
 * @precision: ...
 *
 * Return: Characted printed
 */
int print_octal(va_list types, char buffer[], int flags, int width, int precision, int size) {
    int num = va_arg(types, int);
    int j = 0;

    int negative = 0;
    if (num < 0) {
        negative = 1;
        num = -num;
    }

    int i = 0;
    int octal[size];
    while (num != 0) {
        octal[i++] = num % 8;
        num /= 8;
    }

    if (precision < i) precision = i;
    if (width < precision + negative) width = precision + negative;
    int padding = width - precision - negative;

    int buffer_index = 0;
    if (negative) buffer[buffer_index++] = '-';

    for (; j < padding; j++) {
        buffer[buffer_index++] = (flags & FLAG_ZERO) ? '0' : ' ';
    }

    for (int j = i; j < precision; j++) {
        buffer[buffer_index++] = '0';
    }

    for (int j = i - 1; j >= 0; j--) {
        buffer[buffer_index++] = '0' + octal[j];
    }

    buffer[buffer_index] = '\0';

    return buffer_index;
}
/**
 * print_hexa_upper - ...
 * notation
 * @types: ...
 * @buffer: ...
 * @width: fetch width
 * @size: specifies size
 * @flags: ...
 * @precision: ...
 *
 * Return: Characted printed
 */
int print_hexa_upper(va_list types, char buffer[], int width,
		int flags, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
				flags, 88, width, precision, size));
}
/**
 * print_hexadecimal - ...
 * notation
 * @types: list of arguments
 * @buffer: ...
 * @width: ...
 * @size: ...
 * @flags: ...
 * @precision: ...
 * Return: Characted printed
 */
int print_hexadecimal(va_list types, char buffer[], int width,
		int flags, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
				flags, 88, width, precision, size));
}
/**
 * print_unsigned - ...
 * notation
 * @types: ...
 * @buffer: ...
 * @width: fetch width
 * @size: specifies size
 * @flags: ...
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
/**
 * print_hexa - ....
 * @map_to: ...
 * @flag_ch: flag active
 * @size: specification
 * @types: ...
 * @buffer: ...
 * @width: ...
 * @size: ...
 * @flags: ...
 * @precision: ...
 *
 * Return: Characted printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
		int flags, char flag_ch, int width, int precision, int size)
{
	
int print_hexa(va_list types, char map_to[], char buffer[],
              int flags, char flag_ch, int width, int precision, int size) {
    unsigned int value = va_arg(types, unsigned int);
    
    char hex_str[16] = {0};
    int len = 0;
    do {
        hex_str[len++] = map_to[value % 16];
        value /= 16;
    } while (value > 0);
    if (len == 0) {
        hex_str[len++] = '0';
    }
    
    if (precision > len) {
        int padding = precision - len;
        while (padding-- > 0 && len < sizeof(hex_str) - 1) {
            hex_str[len++] = '0';
        }
    }

    if (width > len) {
        int padding = width - len;
        if (flags & 1) {  // left-justify
            // write the hexadecimal string
            memcpy(buffer, hex_str, len);
            buffer += len;
            size -= len;
            // write padding spaces
            while (padding-- > 0 && size > 1) {
                *buffer++ = ' ';
                size--;
            }
        } else {  // right-justify
            // write padding spaces
            while (padding-- > 0 && size > 1) {
                *buffer++ = (flags & 2) ? '0' : ' ';
                size--;
            }
            // write the hexadecimal string
            memcpy(buffer, hex_str, len);
            buffer += len;
            size -= len;
        }
    } else {
        // write the hexadecimal string
        memcpy(buffer, hex_str, len);
        buffer += len;
        size -= len;
    }
    
    // null-terminate the buffer
    if (size > 0) {
        *buffer = '\0';
    }
    
    return len;

}
