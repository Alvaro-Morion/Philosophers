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
	return(ft_diff(t, args->t0));
}
/*int main()
{
	struct timeval	t0;
	struct timeval	t1;
	int pid;
	pid = fork();
	if (pid == 0)
	{
		gettimeofday(&t0, NULL);
		ft_wait(10);
		gettimeofday(&t1, NULL);
		printf("my time: %li\n", ft_diff(t1,t0));
	}
	else
	{
		gettimeofday(&t0, NULL);
		usleep(10);
		gettimeofday(&t1, NULL);
		printf("usleep time: %li\n", ft_diff(t1,t0));
	}
	return(0);
}*/
