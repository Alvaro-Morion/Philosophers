/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 09:31:06 by amorion-          #+#    #+#             */
/*   Updated: 2021/10/24 09:31:43 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	int	n;
	int	s;

	n = 0;
	s = 1;
	while (*nptr == ' ' || *nptr == '\n' || *nptr == '\t' || *nptr == '\v'
		|| *nptr == '\f' || *nptr == '\r')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			s = -1;
		nptr++;
	}
	while (*nptr <= '9' && *nptr >= '0')
	{
		n = n * 10 + *nptr - '0';
		nptr++;
	}
	return (n * s);
}

void	free_mutex(t_args *args, t_mutex *mutex)
{
	int	i;

	pthread_mutex_unlock(&mutex->output);
	pthread_mutex_destroy(&mutex->output);
	i = 0;
	while (i < args->nphilo)
	{
		if (mutex->forks)
			pthread_mutex_destroy(&mutex->forks[i]);
		if (mutex->m_philo)
			pthread_mutex_destroy(&mutex->m_philo[i]);
		i++;
	}
	if (mutex->forks)
		free(mutex->forks);
	if (mutex->m_philo)
		free(mutex->m_philo);
	if (mutex)
		free(mutex);
}

int	ft_check_death(t_args *args, t_philo philo, t_mutex *mutex)
{
	struct timeval	t;

	pthread_mutex_lock(&mutex->m_philo[philo.num - 1]);
	gettimeofday(&t, NULL);
	if (ft_diff(t, philo.t_meal) >= args->dead_time * 1000)
	{
		args->end++;
		pthread_mutex_lock(&mutex->output);
		printf("%li Philosopher %i has died\n", ft_time_stamp(args), philo.num);
		pthread_mutex_unlock(&mutex->m_philo[philo.num - 1]);
		return (1);
	}
	pthread_mutex_unlock(&mutex->m_philo[philo.num - 1]);
	return (0);
}

void	death_meals(t_args *args, t_philo *philo, t_mutex *mutex)
{
	int				i;

	while (1)
	{
		i = 0;
		while (i < args->nphilo)
		{
			if (ft_check_death(args, philo[i], mutex))
				return ;
			if (args->max_meals > 0 && philo[i].n_meals >= args->max_meals)
				args->enaugh++;
			i++;
		}
		if (args->enaugh == args->nphilo)
		{
			pthread_mutex_lock(&mutex->output);
			args->end++;
			return ;
		}
		args->enaugh = 0;
	}
	return ;
}
