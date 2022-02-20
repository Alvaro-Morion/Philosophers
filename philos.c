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
	int j;
	t_philo *philo;
	
	philo = (t_philo *)philos;
	j = 0;
	while(j < 5)
	{
		printf("Philosopher %d is thinking\n", philo->num);
		take_fork(philo);
		printf("Philosopher %d is eating\n", philo->num);
		usleep(philo->args->eat_time); // crear función específica para manejar el tiempo
		release_fork(philo);
		printf("Philosopher %d is sleeping\n",philo->num);
		usleep(philo->args->sleep_time);
		j++;
	} 
	return(0);
}
void	ft_philo_init(t_philo *philo, int pos, pthread_mutex_t *forks, t_args *args)
{
	philo->num = pos + 1;
	philo->args = args;
	philo->forks[0] = &forks[pos];
	philo->forks[1] = &forks[philo->num % args->nphilo];
}

void	ft_philosophers(t_args *args, pthread_mutex_t *forks)
{
	int i;
	t_philo philo[args->nphilo];
	pthread_t philos[args->nphilo];

	i = 0;
	while(i < args->nphilo)
	{
		ft_philo_init(&philo[i], i, forks, args);
		pthread_create(&philos[i], 0, ft_routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < args->nphilo)
	{
		pthread_join(philos[i], NULL);
		i++;
	}
}