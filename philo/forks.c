/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 11:20:40 by amorion-          #+#    #+#             */
/*   Updated: 2022/01/23 11:20:42 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t	*ft_create_forks(int num)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < num)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			break ;
		i++;
	}
	if (i < num)
	{
		while (i - 1 >= 0)
		{
			pthread_mutex_destroy(&forks[i]);
			i--;
		}
		free(forks);
		return (NULL);
	}
	return (forks);
}

int	take_fork(t_philo *philo)
{
	if (philo->num % 2 == 0)
	{
		pthread_mutex_lock(&philo->mutex->forks[philo->num - 1]);
		ft_print(philo, 0);
		pthread_mutex_lock(&philo->mutex->forks[philo->num
			% philo->args->nphilo]);
		ft_print(philo, 0);
	}
	else
	{
		pthread_mutex_lock(&philo->mutex->forks[philo->num
			% philo->args->nphilo]);
		ft_print(philo, 0);
		if (philo->args->nphilo == 1)
			return (1);
		pthread_mutex_lock(&philo->mutex->forks[philo->num - 1]);
		ft_print(philo, 0);
	}
	return (0);
}

void	release_fork(t_philo *philo)
{
	if (philo->num % 2 == 0)
	{
		pthread_mutex_unlock(&philo->mutex->forks[philo->num
			% philo->args->nphilo]);
		pthread_mutex_unlock(&philo->mutex->forks[philo->num - 1]);
	}
	else
	{
		pthread_mutex_unlock(&philo->mutex->forks[philo->num - 1]);
		pthread_mutex_unlock(&philo->mutex->forks[philo->num
			% philo->args->nphilo]);
	}
}
