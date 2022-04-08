/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:53:53 by ijmari            #+#    #+#             */
/*   Updated: 2022/04/08 15:33:46 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0
typedef struct s_philo
{
	pthread_mutex_t					*fork;
	pthread_mutex_t					*is_printing;
	pthread_t						th;
	pthread_mutex_t					*done_mutex;
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
	int								while_eating;
	
}	t_philos;
int					ft_atoi(const char *str);
t_philos			*preparing(char **av, int ac, t_philos *philo);
unsigned long long	gettime(void);
void				ft_usleep(unsigned long long n);
void				make_c(t_philos *phi);
int					check_numtoeat(t_philos *philo);
#endif