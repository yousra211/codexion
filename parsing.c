#include "ft_utils.h"
#include <stdio.h>
// int	ft_isdigit(int c)
// {
// 	if (c >= '0' && c <= '9')
// 		return (1);
// 	return (0);
// }

static int	ft_isvalid(char *str)
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



static int ft_parse_2(char *str)
{
    long nbr;

    if (!ft_isvalid(str))
        return (-1);
    nbr = ft_atoi(str);
    if (nbr == LONG_MAX)
        return (-1);
    return (nbr);
}


int	*ft_parse(int ac, char *argv[], int *args)
{
	int		i;

	i = 1;
	while (i < ac - 1)
	{
		if (ft_parse_2(argv[i]) < 0)
			return (NULL);
		args[i - 1] = ft_parse_2(argv[i]);
		i++;
	}
	return (args);
}

char *ft_parse_lst_arg(char *arg, char *scheduler_arg)
{
	if (ft_strlen(arg) != 3 && ft_strlen(arg) != 4)
		return (NULL);
	
	if (ft_strlen(arg) == 3)
		if (arg[0] == 'e' && arg[1] == 'd' && arg[2] == 'f')
		{
			scheduler_arg = "edf";
				return (scheduler_arg);
		}
		else
			return (NULL);

	if (ft_strlen(arg) == 4)
	{
		if (arg[0] == 'f' && arg[1] == 'i' && arg[2] == 'f' && arg[3] == 'o')
		{
			scheduler_arg = "fifo";
				return (scheduler_arg);
		}
		else
			return (NULL);		
	}
	
}