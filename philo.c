/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 08:05:20 by ijmari            #+#    #+#             */
/*   Updated: 2022/04/03 14:49:26 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*make(void *s)
{
	t_philos	*phi;
	int			i;

	phi = (t_philos *) s;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&phi->fork[phi->philo_id - 1]);
		pthread_mutex_lock(&phi->is_printing);
		printf("%llu %d has taken a fork\n", \
		(gettime() - phi->start_time) / 1000, phi->philo_id);
		pthread_mutex_unlock(&phi->is_printing);
		pthread_mutex_lock(&phi->fork[(phi->philo_id) % phi->number_of_philos]);
		pthread_mutex_lock(&phi->is_printing);
		printf("%llu %d has taken a fork\n", \
		(gettime() - phi->start_time) / 1000, phi->philo_id);
		pthread_mutex_unlock(&phi->is_printing);
		pthread_mutex_lock(&phi->is_printing);
		printf("%llu %d is eating\n", \
		(gettime() - phi->start_time) / 1000, phi->philo_id);
		pthread_mutex_unlock(&phi->is_printing);
		make_c(phi);
		i++;
	}
	return (0);
}

t_philos	*mutex_init(t_philos *philo)
{
	int				i;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	done_mutex;

	mutex = malloc (sizeof(pthread_mutex_t) * philo->number_of_philos);
	i = 0;
	while (i < philo->number_of_philos)
		pthread_mutex_init(&mutex[i++], NULL);
	pthread_mutex_init(&philo->is_printing, NULL);
	pthread_mutex_init(&philo->done_mutex, NULL);
	i = 0;
	while (i < philo->number_of_philos)
	{
		philo[i].done_mutex = done_mutex;
		philo[i].fork = mutex;
		philo[i].is_eating = 0;
		philo[i].done = 0;
		i++;
	}
	return (philo);
}

void	check_death(t_philos *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		i = i % philo->number_of_philos;
		check_numtoeat(philo);
		if (((gettime() / 1000) - \
		(philo[i].last_meal / 1000)) >= philo[i].time_to_die)
		{
			pthread_mutex_lock(&philo[i].is_printing);
			printf("\033[31;1m%llu %d has died\n", (gettime() / 1000) - \
			(philo[i].start_time / 1000), philo[i].philo_id);
			exit(1);
		}
		ft_usleep(10);
		i++;
	}
}

void	create_philos(t_philos *philo)
{
	int			i;

	philo = mutex_init(philo);
	i = 0;
	while (i < philo->number_of_philos)
	{
		philo[i].last_meal = gettime();
		pthread_create(&philo[i].th, NULL, &make, &philo[i]);
		i += 2;
	}
	usleep (100);
	i = 1;
	while (i < philo->number_of_philos)
	{
		philo[i].last_meal = gettime();
		pthread_create(&philo[i].th, NULL, &make, &philo[i]);
		i += 2;
	}
	check_death(philo);
}

int	main(int ac, char **av)
{
	t_philos	*philo;

	philo = preparing(av, ac, philo);
	create_philos(philo);
}
