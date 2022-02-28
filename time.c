/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 13:59:08 by amorion-          #+#    #+#             */
/*   Updated: 2022/02/20 13:59:13 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

long int ft_diff(struct timeval t1, struct timeval t0)
{
	return(t1.tv_sec-t0.tv_sec)*1000000 + (t1.tv_usec-t0.tv_usec);
}
void	ft_wait(long int time)
{
	struct timeval t0;
	struct timeval t;
	gettimeofday(&t0, NULL);
	gettimeofday(&t, NULL);
	while(ft_diff(t,t0) < time)
		gettimeofday(&t, NULL);
}

long int	ft_time_stamp(t_args *args)
{
	struct timeval	t;
	gettimeofday(&t, NULL);
	return(ft_diff(t, args->t0)/1000);
}

void ft_print(t_philo *philo, int type)
{
	if(philo->args->end)
		return;
	pthread_mutex_lock(philo->args->output);
	if (type == 0)
		printf("%li Philosopher %d has taken a fork\n", 
			ft_time_stamp(philo->args), philo->num);
	if (type == 1)
		printf("%li Philosopher %d is eating\n", 
			ft_time_stamp(philo->args), philo->num);
	if (type == 2)
		printf("%li Philosopher %d is sleeping\n", 
			ft_time_stamp(philo->args), philo->num);
	if (type == 3)
		printf("%li Philosopher %d is thinking\n", 
			ft_time_stamp(philo->args), philo->num);
	pthread_mutex_unlock(philo->args->output);
}

void ft_death_meals(t_philo *philo, t_args *args)
{
	int i;
	struct timeval t;
	while(1)
	{
		i = 0;
		args->enaugh = 0;
		gettimeofday(&t, NULL);
		while(i < args->nphilo)
		{
			if(ft_diff(t, philo[i].t_meal) > args->dead_time*1000)
			{
				pthread_mutex_lock(args->output);
				printf("%li Philosopher %d has died\n", ft_time_stamp(args), philo[i].num);
				args->end = 1;
				return;
			}
			if(args->max_meals > 0 && philo[i].n_meals >= 0)
				args->enaugh++;
			i++;
		}
		if(args->enaugh == args->nphilo)
		{
			pthread_mutex_lock(args->output);
			args->end++;
			return;
		}
	}
	return;
}