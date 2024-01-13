#include "shell.h"

/**
 * _itoa - convert number of base 10 to string
 * @num: number
 * @is_unsigned: is number unsigned
 * Return: converted number in string format or NULL if malloc failed
 */

char *_itoa(long int num, int is_unsigned)
{
	char *digits = "0123456789";
	unsigned long int unsigned_num = num;
	size_t i, str_len = 0;
	int sign = 0;
	char *str;

	if (!is_unsigned && num < 0)
	{
		unsigned_num = -num;
		sign = 1;
	}

	str_len = unsigned_num == 0 ? 1 : count_digit(unsigned_num);

	if (sign)
		str_len++;

	str = (char *)malloc(str_len + 1);
	if (!str)
	{
		errno = ENOMEM, perror("Error");
		return (NULL);
	}

	str[str_len] = '\0';
	i = str_len - 1;

	if (unsigned_num == 0)
		str[0] = '0';

	while (unsigned_num)
	{
		str[i--] = digits[unsigned_num % 10];
		unsigned_num /= 10;
	}
	if (sign)
		str[0] = '-';

	return (str);
}

/**
 * _atoi - convert string to number
 * @str: string
 * Return: number after converted from string
 */
long int _atoi(char *str)
{
	long int num = 0;
	int i = 0, sign = 1;

	if (!str || *str == '\0')
		return (0);

	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}

	while (str[i])
	{
		if (_isdigit(str[i]))
			num = (num * 10) + (str[i] - '0');
		else
			break;

		i++;
	}

	return (num * sign);
}

/**
 * is_pos_int - check if str is number or not
 * @str: string
 * Return: 1 if condition true 0 otherwise
 */
int is_pos_int(char *str)
{
	size_t i;

	if (!str)
		return (0);

	for (i = 0; str[i]; i++)
		if (!_isdigit(str[i]))
			return (0);

	return (1);
}
