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

int	ft_assign_args(int argc, char **argv, t_args *args)
{
	pthread_mutex_init(&args->output, NULL);
	args->forks = ft_create_forks(args->nphilo);
	if(!args->forks)
		return(1);
	args->nphilo = ft_atoi(argv[1]);
	args->dead_time = ft_atoi(argv[2]);
	args->eat_time = ft_atoi(argv[3]);
	args->sleep_time = ft_atoi(argv[4]);
	args->enaugh = 0;
	if (argc == 6)
		args->max_meals = ft_atoi(argv[5]);
	else
		args->max_meals = -1;
	return(0);
}

void ft_print_args(t_args *args)
{
	int i;

	i = 0;
	printf("nphilo: %d\n", args->nphilo);
	printf("dead_time %d\n", args->dead_time);
	printf("eat_time %d\n", args->eat_time);
	printf("sleep_time %d\n", args->sleep_time);
	printf("enaugh %d\n", args->enaugh);
	printf("max_meals %d\n", args->max_meals);
	printf("output %p\n", &args->output);
	while(i < args->nphilo)
	{
		printf("Fork %d: %p\n", i, &args->forks[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{	
	t_args	*args;

	if (ft_check_errors(argc, argv))
		return (0);
	args = (t_args *)malloc(1);
	if(!args)
		return(0);
	args = (t_args *)malloc(1);
	if(ft_assign_args(argc, argv, args))
		return(0);
	ft_philosophers(args);
	return (0);
}
