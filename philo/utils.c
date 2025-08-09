/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:22:09 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/08/09 14:16:33 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_usec / 1000 + time.tv_sec * 1000));
}

int	mutex_creator_fork(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philos)
	{
		if (pthread_mutex_init(&info->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&info->is_anyphilo_died_m, NULL))
		return (1);
	if (pthread_mutex_init(&info->print_mutex, NULL))
		return (1);
	return (0);
}

void	cleanup(pthread_t *monitor_thread, t_philos *philos)
{
	int	i;

	pthread_join(*monitor_thread, NULL);
	i = 0;
	while (i < philos->info->num_of_philos)
	{
		pthread_mutex_destroy(&philos[i].last_meal_m);
		pthread_mutex_destroy(&philos[i].info->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philos[0].info->print_mutex);
	free(philos->info->forks);
	free(philos);
}

void	sleepy_philo(time_t time, t_philos *philo)
{
	time_t	wake_up;

	wake_up = get_time() + time;
	while (get_time() < wake_up)
	{
		if (cont_death(philo))
			break ;
		usleep(100);
	}
}

void	print_two_forks(t_philos *philo)
{
	bool	allow;

	pthread_mutex_lock(&philo->info->is_anyphilo_died_m);
	allow = (philo->had_full == false
			&& philo->info->is_anyphilo_died == false);
	pthread_mutex_unlock(&philo->info->is_anyphilo_died_m);
	if (!allow)
		return ;
	pthread_mutex_lock(&philo->info->print_mutex);
	printf("%ld %d %s\n", get_time() - philo->info->start_time,
		philo->id + 1, TAKE_FORK);
	printf("%ld %d %s\n", get_time() - philo->info->start_time,
		philo->id + 1, TAKE_FORK);
	pthread_mutex_unlock(&philo->info->print_mutex);
}
