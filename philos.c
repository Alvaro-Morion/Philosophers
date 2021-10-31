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
		printf("Philospher %d is thinking\n", philo->num + 1);
		usleep(100);
		printf("Philosopher %d woke up\n", philo->num+1);
	return(philo);
}

t_philo	ft_philo_init(int i, t_args *args, pthread_mutex_t *forks)
{
	t_philo philo;

	philo.num = i;
	philo.args = args;
	philo.forks[0] = forks[i];
	philo.forks[1] = forks[(i+1)% args->nphilo];
	return(philo);
}

void    ft_philosophers(t_args *args, pthread_mutex_t *forks)
{
	int			i;
	pthread_t	*philosophers;
	t_philo		*philo;

	i = 0;
	philosophers = malloc(args->nphilo);
	philo = malloc(args->nphilo);
	while(i < args->nphilo)
	{
		printf(" "); // Cuando no se pone esto da un error extraño.-
		philo[i]= ft_philo_init(i, args, forks);
		if(pthread_create(&philosophers[i], NULL, ft_routine, &philo[i]))
		{
			break;
		}
		pthread_join(philosophers[i], NULL);
		i++;
	}
}