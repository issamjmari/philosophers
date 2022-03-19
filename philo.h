#ifndef PHILO_H
#define	PHILO_H
#include <pthread.h>
#include "li/libft.h"
#include <stdio.h>
#include <sys/time.h>
typedef	struct s_philo
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	is_printing;
	pthread_t		th;
	unsigned long long				start_time;
	unsigned long long				last_meal;
	int				number_of_philos;
	int				number_of_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_philo_must_eat;
	int				philo_id;
}	t_philos;
#endif