/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:56:02 by ijmari            #+#    #+#             */
/*   Updated: 2022/04/03 14:59:51 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	make_c(t_philos *phi)
{
	phi->last_meal = gettime();
	ft_usleep(phi->time_to_eat * 1000);
	phi->is_eating++;
	if (phi->is_eating == phi->num_philo_must_eat)
		phi->done = 1;
	pthread_mutex_unlock(&phi->fork[phi->philo_id - 1]);
	pthread_mutex_unlock(&phi->fork[(phi->philo_id) % \
	phi->number_of_philos]);
	pthread_mutex_lock(&phi->is_printing);
	printf("%llu %d is sleeping\n", \
		(gettime() - phi->start_time) / 1000, phi->philo_id);
	pthread_mutex_unlock(&phi->is_printing);
	ft_usleep(phi->time_to_sleep * 1000);
	pthread_mutex_lock(&phi->is_printing);
	printf("%llu %d is thinking\n", \
	(gettime() - phi->start_time) / 1000, phi->philo_id);
	pthread_mutex_unlock(&phi->is_printing);
}

t_philos	*preparing(char **av, int ac, t_philos *philo)
{
	int	i;

	i = 0;
	philo = malloc (sizeof(t_philos) * ft_atoi(av[1]));
	while (i < ft_atoi(av[1]))
	{
		philo[i].start_time = gettime();
		philo[i].last_meal = gettime();
		philo[i].philo_id = i + 1;
		philo[i].number_of_philos = ft_atoi(av[1]);
		philo[i].time_to_die = ft_atoi(av[2]);
		philo[i].time_to_eat = ft_atoi(av[3]);
		philo[i].time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			philo[i].num_philo_must_eat = ft_atoi(av[5]);
		i++;
	}
	return (philo);
}

void	check_numtoeat(t_philos *philo)
{
	int	j;

	j = 0;
	while (j < philo->number_of_philos)
	{
		if (philo[j].done != 1)
			break ;
		if (j == philo->number_of_philos - 1 && philo[j].done == 1)
			return ;
		j++;
	}
}

unsigned long long	gettime(void)
{
	struct timeval	l;

	gettimeofday(&l, NULL);
	return (l.tv_sec * 1000000 + l.tv_usec);
}

void	ft_usleep(unsigned long long n)
{
	unsigned long long	first_time;

	first_time = gettime();
	while ((gettime() - first_time) < n)
		usleep(10);
}
