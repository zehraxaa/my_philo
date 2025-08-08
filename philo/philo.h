#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

# define THINK "is thinking"
# define TAKE_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define DIE "died"

typedef struct	s_info
{
	int				num_of_philos;
	int				eat_count;
	time_t			die_time;
	time_t			eat_time;
	time_t			sleep_time;
	time_t			start_time;
	bool			is_anyphilo_died;
	pthread_mutex_t	is_anyphilo_died_m;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
}	t_info;

typedef struct		s_philos
{
	int				id;
	bool			had_full;
	int				meals_eaten;
	time_t			last_meal_t;
	pthread_mutex_t	had_full_m;
	pthread_mutex_t	last_meal_m;
	pthread_t		thread;
	t_info			*info;
}	t_philos;

//utils
int		ft_atoi(const char *str);
time_t	get_time();
int		mutex_creator_fork(t_info *info);
void	sleepy_philo(time_t time, t_philos *philo);
void	cleanup(pthread_t *monitor_thread, t_philos *philos);
//monitor
void	*monitor(void *arg);
void	print_call(t_philos philo, char *str);
void	print_death(t_philos philo, char *str);
int		cont_death(t_philos *philo);
int		can_continue(t_philos *philo);
//philos
void	one_philo(t_info *info, t_philos *philo);
void	philo_routine(t_philos *philo);
void	*philos_life(void *arg);
void	create_philo(t_philos *philo, t_info *info);


#endif