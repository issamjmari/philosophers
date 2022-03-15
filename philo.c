#include "philo.h"
#include "li/libft.h"
#include <stdio.h>
#include <pthread.h>

void	*make(void *s)
{
	t_philos	*phi;

	phi = (t_philos *) s;
	pthread_mutex_lock(phi[0].fork);
	printf("DONE\n");
	pthread_mutex_unlock(phi[0].fork);
	sleep(1);
	printf("DONE\n");
	return 0;
}

t_philos	*mutex_init(t_philos *philo)
{
	int			i;
	pthread_mutex_t	*mutex;

	mutex = malloc (sizeof(pthread_mutex_t) * philo->number_of_philos);
	while (i < philo->number_of_philos)
		pthread_mutex_init(&mutex[i++], NULL);
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
	while (i < philo->number_of_philos)
		pthread_create(&philo[i++].th, NULL, &make, philo);
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