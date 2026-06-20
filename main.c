
#include "ft_utils.h"
#include <stdio.h>


int data_init()
1 i removed the allocated memory i just realized that those 2 variables points to a place in the memory so we don t need to alocate memory for them

1 we will have momery leak

3 How many times are you converting the same string?

i think just once right? what should i erduce here

4 the subject says:

All arguments are mandatory. Reject invalid inputs such

as negative numbers, non-integers, or a scheduler other than fifo or

edf.

5 yes u r right i changed it to strcmp

6

int main(int ac, char *av[])
{
    t_data my_data;
    if (ac == 9)
    {   
        int *args;
        char *scheduler_arg;

        args = ft_parse(ac, av, args);
        if (!args)
            return (write(2, "Error\n", 6), exit(1), 0);
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