#include "philo.h"

unsigned long long	gettime (void)
{
	struct timeval l;
	gettimeofday(&l, NULL);
	return (l.tv_sec * 1000000 + l.tv_usec);
}
void	*make(void *s)
{
	t_philos	*phi;
	int			i;

	phi = (t_philos *) s;
	i = 0;
	while (i < phi->number_of_philos)
	{
		usleep (500);
		pthread_mutex_lock(&phi->fork[phi->philo_id]);
		printf("%llu %d has taken a fork\n", (gettime() - phi->start_time) / 1000, phi->philo_id);
		pthread_mutex_lock(&phi->fork[phi->philo_id + 1]);
		printf("%llu %d has taken a fork\n", (gettime() - phi->start_time) / 1000, phi->philo_id);
		pthread_mutex_unlock(&phi->fork[phi->philo_id]);
		pthread_mutex_unlock(&phi->fork[phi->philo_id +1 ]);
		i++;
	}
	return 0;
}

t_philos	*mutex_init(t_philos *philo)
{
	int			i;
	pthread_mutex_t	*mutex;

	mutex = malloc (sizeof(pthread_mutex_t) * philo->number_of_philos);
	i = 0;
	while (i < philo->number_of_philos)
		pthread_mutex_init(&mutex[i++], NULL);
	usleep (100);
	i = 0;
	while (i < philo->number_of_philos)
	{
		philo[i].fork = mutex;
		i++;
	}
	return (philo);
}
void	create_philos(t_philos *philo)
{
	int			i;

	philo = mutex_init(philo);
	i = 0;
	while (i < philo->number_of_philos )
	{
		pthread_create(&philo[i].th, NULL, &make, &philo[i]);
		i += 2;
	}
	usleep (100);
	i = 1;
	while (i < philo->number_of_philos )
	{
			pthread_create(&philo[i].th, NULL, &make, &philo[i]);
		i += 2;
	}
	i = 0;
	while (i < philo->number_of_philos)
		pthread_join(philo[i++].th, NULL);
}
void	error_printing()
{
	printf("Error\n");
	exit (1);
}
t_philos	*preparing(char **av, int ac, t_philos *philo)
{
	int	i;

	i = 0;
	if (ac != 5 && ac != 6)
		error_printing();
	philo = malloc (sizeof(t_philos) * ft_atoi(av[1]));
	while (i < ft_atoi(av[1]))
	{
		philo[i].start_time = gettime();
		philo[i].philo_id = i + 1;
		philo[i].number_of_philos = ft_atoi(av[1]);
		philo[i].time_to_die = ft_atoi(av[2]);
		philo[i].time_to_eat = ft_atoi(av[3]);
		philo[i].time_to_sleep = ft_atoi(av[4]);
		if(ac == 6)
			philo[i].num_philo_must_eat = ft_atoi(av[5]);
		i++;
	}
	return (philo);
}
int main(int ac, char **av)
{
	t_philos	*philo;
	philo = preparing(av, ac, philo);
	create_philos(philo);
}