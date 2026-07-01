/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhamdaou <yhamdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 12:49:22 by yhamdaou          #+#    #+#             */
/*   Updated: 2026/06/30 20:54:26 by yhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <string.h>
# include <sys/time.h>

typedef enum e_scheduler_type
{
	FIFO,
	EDF
}	t_scheduler_type;

typedef struct s_queue
{
	struct s_coder	*coder;
	unsigned long	request_timestamp;

}	t_queue_node;

typedef struct s_scheduler
{
	t_queue_node	*heap;
	int				size;
	int				capacity;
}	t_scheduler;

typedef struct s_dongle
{
	pthread_mutex_t	mutex_dongle;
	pthread_cond_t	cond_dongle;
	unsigned long	last_release_time;
	t_scheduler		scheduler;
	struct s_data	*data;
}	t_dongle;

typedef struct s_coder
{
	int				id;
	unsigned long	last_compile_start;
	int				number_of_compiles;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	struct s_data	*shared_data;
	pthread_t		thread;
}	t_coder;

typedef struct s_data
{
	int					number_of_coders;
	int					time_to_burnout;
	int					time_to_compile;
	int					time_to_debug;
	int					time_to_refactor;
	int					number_of_compiles_required;
	int					dongle_cooldown;
	t_scheduler_type	scheduler_type;
	int					stop_simulation;
	unsigned long		simulation_start_time;
	t_coder				*coders;
	t_dongle			*dongles;
}	t_data;

int				ft_isdigit(int c);
int				ft_isvalid(char *str);
int				validate_args(char *av[]);
int				data_init(int ac, char *av[], t_data *my_data);
int				coders_init(t_data *data);
int				dongles_init(t_data *data);
unsigned long	get_current_time(void);
int				scheduler_init(t_scheduler *scheduler, int capacity);
t_queue_node		scheduler_peek(t_scheduler *scheduler);


#endif