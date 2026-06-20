
#include "ft_utils.h"
#include <stdio.h>

int main(int ac, char *av[])
{
    t_data my_data;
    if (ac == 9)
    {   
        int *args = malloc(sizeof(int) * 7);
        char *scheduler_arg;

        args = ft_parse(ac, av, args);
        if (!args)
            return (write(2, "Error\n", 6), exit(1), 0);
        scheduler_arg = malloc(4);
        for (int i = 0; i < ac - 2; i++)
            printf("%d\n", args[i]);
        scheduler_arg = ft_parse_lst_arg(av[8], scheduler_arg);
        if (!scheduler_arg)
            return (write(2, "Error\n", 6), exit(1), 0);
        printf("%s\n", scheduler_arg);
        my_data = store_my_data(args, scheduler_arg, my_data);
        printf("%d", my_data.dongle_cooldown);
    }
    else
        write(2, "the number of arguments is wrong!", 33);
}