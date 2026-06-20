#include "ft_utils.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_str_digit(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		if (ft_isdigit(str[i]))
			flag = 1;
		i++;
	}
	if (str[i] == '\0' && !flag)
		return (0);
	return (1);
}


long	ft_atoi(char *str)
{
	int		i;
	int		signe;
	long	n;

	i = 0;
	signe = 1;
	n = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	if (!ft_str_digit(str + i))
		return (LONG_MAX);
	while (str[i] && ft_isdigit(str[i]))
	{
		n = n * 10 + (str[i] - '0');
		if (n * signe > INT_MAX || n * signe < INT_MIN)
			return (LONG_MAX);
		i++;
	}
	return (n * signe);
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

t_data store_my_data(int *args,char *scheduler_arg,t_data my_data)
{
	my_data.number_of_coders = args[0];
	my_data.time_to_burnout = args[1];
	my_data.time_to_compile = args[2];
	my_data.time_to_debug = args[3];
	my_data.time_to_refactor = args[4];
	my_data.number_of_compiles_required = args[5];
	my_data.dongle_cooldown = args[6];
	my_data.scheduler = scheduler_arg;

	return (my_data);
}