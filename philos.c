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
	
	philo = (t_philo *)philos;
	while(!philo->args->start)
	{
	}
	philo->t_meal = philo->args->t0;
	while(!philo->args->end)
	{
		if(take_fork(philo))
			philo->args->end = 1;
		else
		{
			ft_print(philo, 1);
			philo->n_meals++;
			gettimeofday(&philo->t_meal, NULL);
			ft_wait(philo->args->eat_time);
			philo->n_meals++;
			release_fork(philo);
			ft_print(philo, 2);
			ft_wait(philo->args->sleep_time);
			ft_print(philo, 3);
		}
	}
	return(0);
}
void	ft_philo_init(t_philo *philo, int pos, pthread_mutex_t *forks, t_args *args)
{
	philo->num = pos + 1;
	philo->args = args;
	philo->n_meals = 0;
	philo->forks[0] = &forks[pos];
	philo->forks[1] = &forks[philo->num % args->nphilo];
	gettimeofday(&philo->t_meal, NULL);
}

void	ft_philosophers(t_args *args)
{
	int i;
	t_philo philo[args->nphilo];
	pthread_t philos[args->nphilo];

	i = 0;
	while(i < args->nphilo)
	{
		ft_philo_init(&philo[i], i, args->forks, args);
		i++;
	}
	i = 0;
	while(i < args->nphilo)
	{
		pthread_create(&philos[i], 0, ft_routine, &philo[i]);
		i++;
	}
	gettimeofday(&(args->t0), NULL);
	args->start++;
	ft_death_meals(philo, args);
	i = 0;
	while (i < args->nphilo)
	{
		pthread_join(philos[i], NULL);
		i++;
	}
}