/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhamdaou <yhamdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 12:44:55 by yhamdaou          #+#    #+#             */
/*   Updated: 2026/06/25 12:44:58 by yhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"
#include <stdio.h>

int main(int ac, char *av[])
{
	t_data my_data;
	if (!data_init(ac, av, &my_data))
		return (1);
	printf("%d", my_data.dongle_cooldown);

}
