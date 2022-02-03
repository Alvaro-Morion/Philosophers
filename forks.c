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

# include "philosophers.h"

pthread_mutex_t	*ft_create_forks(int num)
{
	pthread_mutex_t	*forks;
	int i;
    
    forks = malloc(num);
    i = 0;
    while(i < num)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
	return(forks);
}

void take_fork(t_philo *philo)
{
    if (philo->num < philo->args->nphilo)
    {
        if(!pthread_mutex_lock(&(philo->forks[0])))
            printf("Philosopher %d has taken a fork %d\n", philo->num, philo->num-1);
        if(!pthread_mutex_lock(&(philo->forks[1])))
            printf("Philosopher %d has taken a fork %d \n", philo->num, philo->num);
    }
    else
    {
        if(!pthread_mutex_lock(&(philo->forks[1])))
            printf("Philosopher %d has taken fork %d \n", philo->num, 0);
        if(!pthread_mutex_lock(&(philo->forks[0])))
            printf("Philosopher %d has taken fork %d\n", philo->num, philo->num-1);
    }
}

void release_fork(t_philo *philo)
{
    if (philo->num < philo->args->nphilo)
    {
        if(!pthread_mutex_unlock(&(philo->forks[1])))
            printf("Philosopher %d has released a fork %d\n", philo->num, philo->num);
        if(!pthread_mutex_unlock(&(philo->forks[0])))
            printf("Philosopher %d has released a fork %d \n", philo->num, philo->num-1);
    }
    else
    {
        if(!pthread_mutex_unlock(&(philo->forks[0])))
            printf("Philosopher %d has taken fork %d \n", philo->num, philo->num-1);
        if(!pthread_mutex_lock(&(philo->forks[1])))
            printf("Philosopher %d has taken fork %d\n", philo->num, 0);
    }
}