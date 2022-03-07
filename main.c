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

#include "./philosophers.h"

void ft_leaks (void)
{
	system("leaks philo");
}

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
			printf("%s is invalid\n", params[i - 1]);
			return (1);
		}
		i++;
	}
	return (0);
}

t_args	*ft_assign_args(int argc, char **argv)
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	args->nphilo = ft_atoi(argv[1]);
	args->dead_time = ft_atoi(argv[2]);
	args->eat_time = ft_atoi(argv[3]);
	args->sleep_time = ft_atoi(argv[4]);
	args->enaugh = 0;
	args->end = 0;
	if (argc == 6)
		args->max_meals = ft_atoi(argv[5]);
	else
		args->max_meals = -1;
	return (args);
}

t_mutex	*ft_create_mutex(t_args args)
{
	t_mutex	*mutex;

	mutex = malloc(sizeof(t_mutex));
	if (!mutex)
		return (NULL);
	if (pthread_mutex_init(&mutex->output, NULL))
	{
		free(mutex);
		return (NULL);
	}
	mutex->m_philo = ft_create_forks(args.nphilo);
	mutex->forks = ft_create_forks(args.nphilo);
	if (!mutex->m_philo || !mutex->forks)
	{
		free_mutex(&args, mutex);
		return (NULL);
	}
	return (mutex);
}

int	main(int argc, char **argv)
{	
	t_args	*args;
	t_mutex	*mutex;

	atexit(ft_leaks);
	if (ft_check_errors(argc, argv))
		return (1);
	args = ft_assign_args(argc, argv);
	if (!args)
		return (1);
	mutex = ft_create_mutex(*args);
	if (!mutex)
		return (1);
	ft_philosophers(args, mutex);
	free(args);
	return (0);
}
