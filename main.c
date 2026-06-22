
#include "ft_utils.h"
#include <stdio.h>

int validate_args(char *av[])
{
	int size;

	size = strlen(av[8]);
	if (!ft_isvalid(av[1]))
		return(write(2, "the value of number_of_coders is invalid!", 41), 0);
	if (!ft_isvalid(av[2]) || !ft_isvalid(av[3]) || !ft_isvalid(av[4]) || !ft_isvalid(av[5]))
		return(write(2, "the time is invalid!", 20), 0);
	if (!ft_isvalid(av[6]))
		return(write(2, "the number_of_compiles_required is invalid!", 43), 0);
	if (!ft_isvalid(av[7]))
		return(write(2, "Invalid cooldown!", 17), 0);
	if ((size != 3 && size != 4)
	|| (strcmp(av[8], "edf") != 0)
	|| (strcmp(av[8], "fifo") != 0))
		return(write(2, "Invalid scheduler!", 18), 0);
	return (1);
}


int	data_init(int ac, char *av[], t_data *my_data)
{
	if (ac != 9)	
		return(write(2, "the number of arguments is wrong!", 33), 0);
	if (!validate_args(av))
		return (0);
	
	my_data->number_of_coders = atoi(av[1]);
	my_data->time_to_burnout = atoi(av[2]);
	my_data->time_to_compile = atoi(av[3]);
	my_data->time_to_debug = atoi(av[4]);
	my_data->time_to_refactor = atoi(av[5]);
	my_data->number_of_compiles_required = atoi(av[6]);
	my_data->dongle_cooldown = atoi(av[7]);
	if (my_data->dongle_cooldown < 0)
		return(write(2, "Invalid cooldown!", 17), 0);
	my_data->scheduler = av[8];
	
	my_data->stop_simulation = 0;
	my_data->simulation_start_time = 0;
	return (1);
}

int main(int ac, char *av[])
{
	t_data my_data;
	if (!data_init(ac, av, &my_data))
		return (1);
	printf("%d", my_data.dongle_cooldown);

}