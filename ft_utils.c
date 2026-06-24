#include "ft_utils.h"
#include <stdio.h>

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isvalid(char *str)
{
	int	i;
	int	has_digit;

	i = 0;
	has_digit = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else if ((str[i] == '+')
			&& ft_isdigit(str[i + 1])
			&& (i == 0 || str[i - 1] == ' '))
			i++;
		else if (ft_isdigit(str[i]))
		{
			has_digit = 1;
			i++;
		}
		else
			return (0);
	}
	return (has_digit);
}

unsigned long get_current_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000UL) + (tv.tv_usec / 1000UL);
}