/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 10:56:18 by amorion-          #+#    #+#             */
/*   Updated: 2021/10/22 10:56:20 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

t_args	*ft_set_arguments(argc,argv)
{
	t_args *args;
	if (!(argc > 4 && argc < 7))
	{	
		printf("./philo/ #philosophers dead_time eat_time sleep_time [max # meals]\n");
		return (0);
	}
	args = malloc(t_args)
	if (!args)
		return(NULL);
	args->nphilo = ft_atoi(argv[1]);
	args->deadtime = ft_atoi(argv[2]);
	args->etime = ft_atoi(argv[3]);
	args->stime = ft_atoi(argv[4]);
	if (argc == 6)
	args->maxe = ft_atoi(argv[5]);
	if (args->)
}

int	main(int argc, char **argv)
{	
	return(0);
}