/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:22:09 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/08/06 18:15:20 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (str[i])
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num);
}

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
	if (pthread_mutex_init(&info->is_anyphilo_died_m, NULL)) //oluşmadıysa 1 döner
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

void	sleepy_philo(time_t time)
{
	time_t	wake_up;

	wake_up = get_time() + time;
	while (get_time() < wake_up)
		usleep(100);
}
