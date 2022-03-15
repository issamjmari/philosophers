#ifndef PHILO_H
#define	PHILO_H
#include <pthread.h>
typedef	struct s_philo
{
	pthread_mutex_t	*fork;
	pthread_t		th;
	int				number_of_philos;
	int				number_of_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_philo_must_eat;
	int				philo_id;
	int				last_meal;
}	t_philos;
#endif