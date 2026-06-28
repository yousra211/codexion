/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhamdaou <yhamdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 18:10:04 by yhamdaou          #+#    #+#             */
/*   Updated: 2026/06/28 18:25:51 by yhamdaou         ###   ########.fr       */
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

void	*routine(void *arg)
{
	t_coder *coder;

	coder = (t_coder *)arg;
	while(coder->shared_data->stop_simulation == 0)
	{
		pthread_mutex_lock(&(coder->left_dongle->mutex_dongle));
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
