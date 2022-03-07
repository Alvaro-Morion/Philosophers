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
	t_philo	*philo;

	philo = (t_philo *)philos;
	philo->t_meal = philo->args->t0;
	while (!philo->args->end)
	{
		if (take_fork(philo))
			philo->args->end = 1;
		pthread_mutex_lock(&philo->mutex->m_philo[philo->num - 1]);
		ft_print(philo, 1);
		gettimeofday(&philo->t_meal, NULL);
		philo->n_meals ++;
		pthread_mutex_unlock(&philo->mutex->m_philo[philo->num - 1]);
		ft_wait(philo->args->eat_time * 1000, philo->args);
		release_fork(philo);
		ft_print(philo, 2);
		ft_wait(philo->args->sleep_time * 1000, philo->args);
		ft_print(philo, 3);
		if (!philo->args->end)
			usleep(100);
	}
	return (0);
}

void	ft_philo_init(t_philo *philo, int pos, t_args *args, t_mutex *mutex)
{
	philo->num = pos + 1;
	philo->n_meals = 0;
	philo->args = args;
	philo->mutex = mutex;
	gettimeofday(&philo->t_meal, NULL);
}

void	ft_philos_threads(t_args *args, t_philo *philo,
	t_mutex *mutex, pthread_t *philos)
{
	int	i;

	i = 0;
	while (i < args->nphilo)
	{
		ft_philo_init(&philo[i], i, args, mutex);
		i++;
	}
	i = 0;
	gettimeofday(&args->t0, NULL);
	while (i < args->nphilo)
	{
		pthread_create(&philos[i], 0, ft_routine, &philo[i]);
		i++;
	}
}

void	ft_philosophers(t_args *args, t_mutex *mutex)
{
	int			i;
	t_philo		*philo;
	pthread_t	*philos;

	philo = malloc(sizeof(t_philo) * args->nphilo);
	if (!philo)
		return ;
	philos = (pthread_t *)malloc(sizeof(pthread_t) * args->nphilo);
	if (!philos)
	{
		free(philo);
		return ;
	}
	ft_philos_threads(args, philo, mutex, philos);
	death_meals(args, philo, mutex);
	i = 0;
	while (i < args->nphilo)
	{
		pthread_join(philos[i], NULL);
		i++;
	}
	free_mutex(args, mutex);
	free(philo);
	free(philos);
}
