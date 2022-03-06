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
	int				nphilo;
	int				dead_time;
	int				eat_time;
	int				sleep_time;
	int				max_meals;
	int				enaugh;
	int				end;
	struct timeval	t0;
}	t_args;

typedef struct s_mutex
{
	pthread_mutex_t	output;
	pthread_mutex_t	*m_philo;
	pthread_mutex_t	*forks;
}	t_mutex;

typedef struct s_philo
{
	int				num;
	int				n_meals;
	struct timeval	t_meal;
	t_args			*args;
	t_mutex			*mutex;
}	t_philo;

int				ft_atoi(const char *nptr);
void			ft_philosophers(t_args *args, t_mutex *mutex);
pthread_mutex_t	*ft_create_forks(int num);
int				take_fork(t_philo *philo);
void			release_fork(t_philo *philo);
void			ft_wait(long int time, t_args *args);
long int		ft_time_stamp(t_args *args);
void			ft_print(t_philo *philo, int type);
void			death_meals(t_args *args, t_philo *philo, t_mutex *mutex);
void			free_mutex(t_args *args, t_mutex *mutex);
#endif