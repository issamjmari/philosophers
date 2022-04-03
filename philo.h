/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:53:53 by ijmari            #+#    #+#             */
/*   Updated: 2022/04/03 14:55:37 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include "li/libft.h"
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_mutex_t					*fork;
	pthread_mutex_t					is_printing;
	pthread_t						th;
	pthread_mutex_t					done_mutex;
	unsigned long long				start_time;
	unsigned long long				last_meal;
	int								number_of_philos;
	int								number_of_forks;
	int								time_to_die;
	int								time_to_eat;
	int								time_to_sleep;
	int								num_philo_must_eat;
	int								philo_id;
	int								is_eating;
	int								done;
}	t_philos;
t_philos			*preparing(char **av, int ac, t_philos *philo);
unsigned long long	gettime(void);
void				ft_usleep(unsigned long long n);
void				make_c(t_philos *phi);
void				check_numtoeat(t_philos *philo);
#endif