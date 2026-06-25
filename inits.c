/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhamdaou <yhamdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 12:44:40 by yhamdaou          #+#    #+#             */
/*   Updated: 2026/06/25 12:45:32 by yhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"


int validate_args(char *av[])
{
	if (!ft_isvalid(av[1]))
		return(write(2, "the value of number_of_coders is invalid!", 41), 0);
	if (!ft_isvalid(av[2]) || !ft_isvalid(av[3]) || !ft_isvalid(av[4]) || !ft_isvalid(av[5]))
		return(write(2, "the time is invalid!", 20), 0);
	if (!ft_isvalid(av[6]))
		return(write(2, "the number_of_compiles_required is invalid!", 43), 0);
	if (!ft_isvalid(av[7]))
		return(write(2, "Invalid cooldown!", 17), 0);
	if ((strcmp(av[8], "edf") != 0)
	&& (strcmp(av[8], "fifo") != 0))
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
	if (strcmp(av[8], "fifo") == 0)
		my_data->scheduler_type = FIFO;
	else
		my_data->scheduler_type = EDF;
	my_data->stop_simulation = 0;
	my_data->simulation_start_time = get_current_time();
	return (1);
}


void    dongles_cleanup(t_data *data, int initialized_count)
{
	int i;

	i = 0;
	while (i < initialized_count)
	{
		pthread_mutex_destroy(&(data->dongles[i].mutex_dongle));
		pthread_cond_destroy(&(data->dongles[i].cond_dongle));
		i++;
	}
	free(data->dongles);
	data->dongles = NULL;
}


int     dongles_init(t_data *data)
{
	int		i;
	int		n;

	i = 0;
	n = data->number_of_coders;
	data->dongles = malloc(n * sizeof(t_dongle));
	if(!data->dongles)
		return (0);
	while(i < n)
	{

		if (pthread_mutex_init(&(data->dongles[i].mutex_dongle), NULL) != 0)
		{
			dongles_cleanup(data, i);
			return (0);
		}
		if (pthread_cond_init(&(data->dongles[i].cond_dongle), NULL) != 0)
		{
			dongles_cleanup(data, i);
			return (0);
		}
		data->dongles[i].last_release_time = 0;
		data->dongles[i].data = data;
		i++;
	}
	scheduler_init(&data->dongles[i].scheduler,
			   data->number_of_coders);
	return (1);
}


int     coders_init(t_data *data)
{
	int		i;
	int		n;

	i = 0;
	n = data->number_of_coders;
	data->coders = malloc(n * sizeof(t_coder));
	if (!data->coders)
	{
		free(data->dongles);
		return (0);
	}
	while(i < n)
	{
		data->coders[i].id = i + 1;
		data->coders[i].last_compile_start = data->simulation_start_time;
		data->coders[i].number_of_compiles = 0;
		data->coders[i].left_dongle = &(data->dongles[i]);
		data->coders[i].right_dongle = &(data->dongles[(i + 1) % n]);
		data->coders[i].shared_data = data;
		i++;
		
	}
	return (1);
}

int scheduler_init(t_scheduler *scheduler, int capacity)
{
	scheduler->heap = malloc(sizeof(t_queue_node) * capacity);
	if (!scheduler->heap)
		return(0);
	scheduler->size = 0;
	scheduler->capacity = capacity;
	return (1);	
}