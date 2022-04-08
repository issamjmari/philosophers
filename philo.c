/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 08:05:20 by ijmari            #+#    #+#             */
/*   Updated: 2022/04/08 15:34:56 by ijmari           ###   ########.fr       */
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
		pthread_mutex_lock(phi->is_printing);
		printf("%llu %d has taken a fork\n", \
		(gettime() - phi->start_time) / 1000, phi->philo_id);
		pthread_mutex_unlock(phi->is_printing);
		pthread_mutex_lock(&phi->fork[(phi->philo_id) % phi->number_of_philos]);
		pthread_mutex_lock(phi->is_printing);
		printf("%llu %d has taken a fork\n", \
		(gettime() - phi->start_time) / 1000, phi->philo_id);
		pthread_mutex_unlock(phi->is_printing);
		phi->while_eating = TRUE;
		phi->last_meal = gettime();
		pthread_mutex_lock(phi->is_printing);
		printf("%llu %d is eating\n", \
		(gettime() - phi->start_time) / 1000, phi->philo_id);
		pthread_mutex_unlock(phi->is_printing);
		make_c(phi);
		i++;
	}
	return (0);
}

t_philos	*mutex_init(t_philos *philo)
{
	int				i;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*is_printing;
	pthread_mutex_t	*done_mutex;

	mutex = malloc (sizeof(pthread_mutex_t) * philo->number_of_philos);
	is_printing = malloc(sizeof(pthread_mutex_t));
	done_mutex = malloc(sizeof(pthread_mutex_t));
	i = 0;
	while (i < philo->number_of_philos)
		pthread_mutex_init(&mutex[i++], NULL);
	pthread_mutex_init(is_printing, NULL);
	pthread_mutex_init(done_mutex, NULL);
	i = 0;
	while (i < philo->number_of_philos)
	{
		philo[i].is_printing = is_printing;
		philo[i].fork = mutex;
		philo[i].is_eating = 0;
		philo[i].done_mutex = done_mutex;
		philo[i].done = 0;
		philo[i].while_eating = FALSE;
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
		if (check_numtoeat(philo))
			return ;
		if (((gettime() / 1000) - \
		(philo[i].last_meal / 1000)) >= philo[i].time_to_die && philo[i].while_eating == FALSE)
		{
			printf("---------  %d\n", philo[i].while_eating);
			pthread_mutex_lock(philo[i].is_printing);
			printf("\033[31;1m%llu %d has died (last_meal == %llu)\033[0m\n", (gettime() / 1000) - \
			(philo[i].start_time / 1000), philo[i].philo_id, \
			((gettime() / 1000) - (philo[i].last_meal / 1000)));
			return ;
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
