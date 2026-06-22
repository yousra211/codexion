#ifndef FT_UTILS_H
# define FT_UTILS_H

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <limits.h>
#include <string.h>

typedef struct s_data
{
    int     number_of_coders;
    int     time_to_burnout;
    int     time_to_compile;
    int     time_to_debug;
    int     time_to_refactor;
    int     number_of_compiles_required;
    int     dongle_cooldown;
    char    *scheduler;
    int     stop_simulation;
    int     simulation_start_time;
}   t_data;



typedef struct s_queue
{
    int             coder_id;
    unsigned long   request_timestamp;
    int             deadline;    

}   queue_node;


typedef struct s_scheduler
{
    queue_node      **heap;
    int             size;
    int             capacity;
}   t_scheduler;


typedef struct s_dongle
{
    pthread_mutex_t mutex_dongle;
    pthread_cond_t  cond_dungle;
    unsigned long   last_release_time;
    t_scheduler     *scheduler;
    t_data          *data;
}   t_dongle;

typedef struct s_coder
{
    int             id;
    unsigned long   last_compile_start;
    int             number_of_compiles;
    t_dongle        *left_dongle;
    t_dongle        *right_dongle;
    t_data          *shared_data;
    pthread_t		thread;
}   t_coder;


int     ft_isdigit(int c);
int	    ft_isvalid(char *str);


#endif