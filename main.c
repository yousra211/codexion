
#include "ft_utils.h"
#include <stdio.h>

int main(int ac, char *av[])
{
	t_data my_data;
	if (!data_init(ac, av, &my_data))
		return (1);
	printf("%d", my_data.dongle_cooldown);

}