
#include "ft_utils.h"
#include <stdio.h>


t_data	*data_init(int ac, char *av[], t_data *my_data)
{
	if (ac == 9)
	{
		int		*args;
		char	*scheduler_arg;

		args = ft_parse(ac, av, args);
		if (!args)
			return (write(2, "Error\n", 6), exit(1), 0);
		for (int i = 0; i < ac - 2; i++)
			printf("%d\n", args[i]);
		scheduler_arg = ft_parse_lst_arg(av[8], scheduler_arg);
		if (!scheduler_arg)
			return (write(2, "Error\n", 6), exit(1), 0);
		printf("%s\n", scheduler_arg);
		*my_data = store_my_data(args, scheduler_arg, *my_data);
		printf("%d", (*my_data).dongle_cooldown);
	}
	else
		return(write(2, "the number of arguments is wrong!", 33), exit(1), 0);
	return my_data;
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
	int		parsed;

	i = 1;
	while (i < ac - 1)
	{
		parsed = ft_parse_2(argv[i]);
		if (parsed < 0)
			return (NULL);
		args[i - 1] = parsed;
		i++;
	}
	return (args);
}
int	*data_init(int ac, char *av[], t_data *my_data)
{
	if (ac != 9)	
		return(write(2, "the number of arguments is wrong!", 33), exit(1), 0);
	my_data->number_of_coders = atoi(av[1]);
	if (my_data->number_of_coders <= 0 || my_data->number_of_coders > 200 || !ft_isvalid(av[1]))
		return(write(2, "the value of number_of_coders is invalid!", 41), exit(1), 0);
	my_data->time_to_burnout = av[2];
	my_data->time_to_compile = av[3];
	my_data->time_to_debug = av[4];
	my_data->time_to_refactor = av[5];
	if(my_data->time_to_burnout < 60 || my_data->time_to_compile < 60 || my_data->time_to_debug < 60
	|| my_data->time_to_refactor < 60 || !ft_isvalid(av[2]) || !ft_isvalid(av[3]) || !ft_isvalid(av[4])
	|| !ft_isvalid(av[5]))
		return(write(2, "the time is invalid!", 20), exit(1), 0);
	return (1);
}

int main(int ac, char *av[])
{
	t_data my_data;
	data_init(ac, av, &my_data);

}