/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhamdaou <yhamdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 18:10:04 by yhamdaou          #+#    #+#             */
/*   Updated: 2026/07/01 19:53:55 by yhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

// while simulation not stopped
// {
//     request left dongle

//     request right dongle

//     if failed
//     {
//         release left
//         continue
//     }

//     compile

//     release both

//     debug

//     refactor
// }


// lock mutex

// look at scheduler
// look at cooldown
// possibly insert request
// possibly wait

// unlock mutex

// owner == NULL → free.
// owner != NULL → occupied by that coder.



// lock mutex

// insert request (if not already waiting)

// while (
//     I'm not first
//     OR owner != NULL
//     OR cooldown not finished
// )
//     pthread_cond_wait(...)

// scheduler_pop()

// owner = me

// unlock mutex

// compile

void	*routine(void *arg)
{
	t_coder *coder;
	t_queue_node winner;
	t_coder *owner;
	
	owner = NULL;
	coder = (t_coder *)arg;
	while(coder->shared_data->stop_simulation == 0)
	{
		pthread_mutex_lock(&(coder->left_dongle->mutex_dongle));
		scheduler_insert(coder, coder->left_dongle->scheduler);
		winner = scheduler_peek(coder->left_dongle->scheduler);
		// owner = winner->coder;
		// scheduler_peek(coder->left_dongle->scheduler);
		while (coder != winner->coder ||
		owner != NULL ||
		get_current_time() - coder->left_dongle->last_release_time < coder->shared_data->dongle_cooldown)
			pthread_cond_wait(&(coder->left_dongle->cond_dongle), &(coder->left_dongle->mutex_dongle));
		scheduler_pop(coder->left_dongle->scheduler);
		owner = winner;
		pthread_mutex_unlock(&(coder->left_dongle->mutex_dongle));
		usleep(coder->shared_data->time_to_compile);
	}
}


void	*routine(void *arg)
{
	t_coder *coder;
	t_queue_node winner;
	t_coder *owner;
	

	coder = (t_coder *)arg;
	while(coder->shared_data->stop_simulation == 0)
	{
		scheduler_insert(coder, coder->left_dongle->scheduler);
		winner = scheduler_peek(coder->left_dongle->scheduler);
		if (coder == winner->coder)
		{		
			pthread_mutex_lock(&(coder->left_dongle->mutex_dongle));
			while (get_current_time() - coder->left_dongle->last_release_time < coder->shared_data->dongle_cooldown)
				pthread_cond_wait(&(coder->left_dongle->cond_dongle), &(coder->left_dongle->mutex_dongle));
		}
	}
}


int	create_coders_threads(t_data *data)
{
	int i;

	i = 0;
	while(i < data->number_of_coders)
	{
		if (pthread_create(data->coders[i].thread, NULL, routine, &data->coders[i]) != 0)
		{
			perror("Failed to create thread");
			return 1;
		}
		i++;
	}
	i = 0;
	while(i < data->number_of_coders)
	{
		if (pthread_join(data->coders[i].thread, NULL) != 0)
		{
			return 2;
		}
		i++;
	}
}
