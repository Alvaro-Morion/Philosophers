/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 11:08:21 by amorion-          #+#    #+#             */
/*   Updated: 2021/10/22 11:08:24 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include<stdio.h>
# include<stdlib.h>
# include<pthread.h>
# include<unistd.h>
# include<sys/time.h>
typedef struct s_args
{
	int	nphilo;
	int	dead_time;
	int	eat_time;
	int	sleep_time;
	int	max_meals;
	int t_start;
}	t_args;

typedef struct s_philo
{
	int				num;
	int				n_meals;
	t_args			*args;
	pthread_mutex_t *forks[2];
}	t_philo;

int				ft_atoi(const char *nptr);
void    		ft_philosophers(t_args *args, pthread_mutex_t *forks);
pthread_mutex_t	*ft_create_forks(int num);
void 			take_fork(t_philo *philo);
void 			release_fork(t_philo *philo);
#endif