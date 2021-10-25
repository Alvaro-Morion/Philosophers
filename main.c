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

int	ft_check_errors(int argc, char **argv)
{
	int		i;
	char	*params[5];

	params[0] = "#philosophers";
	params[1] = "time_dead";
	params[2] = "time_eat";
	params[3] = "time_sleep";
	params[4] = "max_meals";
	if (argc != 5 && argc != 6)
	{
		printf("./philo #philisophers time_dead time_eat time_sleep");
		printf("[max_meals]\n");
		return (1);
	}
	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) < 1)
		{
			printf("parameter %s is invalid", params[i - 1]);
			return (1);
		}
		i++;
	}
	return (0);
}

t_args	ft_assign_args(int argc, char **argv)
{
	t_args	args;

	args.nphilo = ft_atoi(argv[1]);
	args.dead_time = ft_atoi(argv[2]);
	args.eat_time = ft_atoi(argv[3]);
	args.sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		args.max_meals = ft_atoi(argv[5]);
	return (args);
}

pthread_mutex_t	*ft_create_forks(int num)
{
	pthread_mutex_t	*forks;
	forks = malloc(num);
	return(forks);
}

int	main(int argc, char **argv)
{	
	t_args			args;
	pthread_mutex_t	*forks;

	if (ft_check_errors(argc, argv))
		return (0);
	args = ft_assign_args(argc, argv);
	forks = ft_create_forks(args.nphilo);
	if (!forks)
		return(0);
	ft_philosophers(args, forks);
	return (0);
}
