/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 09:57:42 by amorion-          #+#    #+#             */
/*   Updated: 2021/10/25 09:57:46 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void   *ft_routine(t_philo *philo)
{
	printf("Philosopher %d created", philo->num);
	return(0);
}
int	ft_init_philo(int i, t_args args, pthread_mutex_t *fork)
{
	t_philo *philo;
	philo = malloc(t_philo);
	philo->num = i;
	philo->forks[0] = fork[i - 1];
	if (i == args.nphilo)
		philo->forks[1] = fork[0];
	else
		philo->forks[1] = fork[i];
	if (pthread_create(philo->thread, NULL, ft_routine, philo))
	{
		printf("Unable to create thread for %d philosopher", i);
		free(philo);
		return(1);
	}
	free(philo);
	return(0);
}

void    ft_philosophers(t_args args, pthread_mutex_t *forks)
{
	int i;
	i = 1;
	while (i < args.nphilo)
	{      
		if (ft_init_philo(i, args, forks))
			break;
		i++;
	}
}