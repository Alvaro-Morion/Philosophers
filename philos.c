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

void	*ft_routine(void *philos)
{ 
	t_philo *philo;
	philo = philos;
	int i;
	i = 0;
	while(i < 5)
	{
		printf("Philosopher %d is thinking\n", philo->num);
		take_fork(philo);
		printf("Philosopher %d is eating\n", philo->num);
		usleep(philo->args->eat_time);
		release_fork(philo);
		printf("Philosopher %d is sleeping\n",philo->num);
		usleep(philo->args->sleep_time);
		i++;
	} 
	return(0);
}

void	ft_philo_init(t_philo *philo, int i, t_args *args, pthread_mutex_t *forks)
{
	philo->num = i+1;
	philo->args = args;
	philo->forks[0] = &forks[i];
	philo->forks[1] = &forks[(i+1) % args->nphilo];
}

void ft_philosophers(t_args *args, pthread_mutex_t *forks)
{
	t_philo philos[args->nphilo];
	int i;

	i = 0;
	while(i < args->nphilo)
	{
		ft_philo_init(&philos[i], i, args, forks);
		i++;
	}
}