#include "ft_utils.h"

void    *routine()
{

}


int     create_coders_threads(t_data *data)
{
    int i;

    i = 0;
    while(i < data->number_of_coders)
    {
        if (pthread_create(data->coders[i].thread, NULL, &routine, NULL) != 0) {
            perror("Failed to create thread");
            return 1;
        }
        i++;
    }
    i = 0;
    while(i < data->number_of_coders)
    {
        if (pthread_join(data->coders[i].thread, NULL) != 0) {
            return 2;
        }
        i++;
    }
}
