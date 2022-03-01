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
void	ft_wait(long int time, t_args *args)
{
	struct timeval t0;
	struct timeval t;
	gettimeofday(&t0, NULL);
	gettimeofday(&t, NULL);
	while(ft_diff(t,t0) < time && !args->end)
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
	pthread_mutex_lock(&philo->args->output);
	if (type == 0)
		printf("%li %d has taken a fork\n"/*"%li Philosopher %d has taken a fork\n"*/, 
			ft_time_stamp(philo->args), philo->num);
	if (type == 1)
		printf("%li %d is eating\n"/*"%li Philosopher %d is eating\n"*/, 
			ft_time_stamp(philo->args), philo->num);
	if (type == 2)
		printf("%li %d is sleeping\n"/*"%li Philosopher %d is sleeping\n"*/, 
			ft_time_stamp(philo->args), philo->num);
	if (type == 3)
		printf("%li %d is thinking\n"/*"%li Philosopher %d is thinking\n"*/, 
			ft_time_stamp(philo->args), philo->num);
	pthread_mutex_unlock(&philo->args->output);
}
 
void death_meals(t_args *args, t_philo *philo)
{
	int i;
	struct timeval t;

	while(1)
	{
		i = 0;
		while(i < args->nphilo)
		{
			gettimeofday(&t, NULL);
			pthread_mutex_lock(&philo[i].m_philo);
			if(ft_diff(t, philo[i].t_meal) >= args->dead_time*1000)
			{
				args->end++;
				pthread_mutex_lock(&args->output);
				printf("%li Philosopher %i has died\n", ft_time_stamp(args), philo[i].num);
				pthread_mutex_unlock(&philo[i].m_philo);
				return;
			}
			pthread_mutex_unlock(&philo[i].m_philo);
			if (philo[i].n_meals >= args->max_meals)
				args->enaugh++;
			i++;

		}
		if(args->max_meals >= 0 && args->enaugh == args->nphilo)
		{
			pthread_mutex_lock(&args->output);
			args->end++;
			return;
		}
		args->enaugh = 0;
	}
	return;
}