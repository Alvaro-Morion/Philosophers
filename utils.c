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

void	free_mutex(t_args * args, t_mutex *mutex)
{
	int i;

	pthread_mutex_unlock(&mutex->output);
	pthread_mutex_destroy(&mutex->output);
	i = 0;
	while(i < args->nphilo)
	{
		if(mutex->forks)
			pthread_mutex_destroy(&mutex->forks[i]);
		if(mutex->m_philo)
			pthread_mutex_destroy(&mutex->m_philo[i]);
		i++;
	}
	if(mutex->forks)
		free(mutex->forks);
	if(mutex->m_philo)
		free(mutex->m_philo);
	if(mutex)
		free(mutex);
}