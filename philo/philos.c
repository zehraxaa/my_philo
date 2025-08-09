/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:04:31 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/08/09 14:29:26 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*one_philo_life(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	pthread_mutex_lock(&philo->info->forks[0]);
	print_call(*philo, TAKE_FORK);
	sleepy_philo(philo->info->die_time, philo);
	print_death(*philo, DIE);
	pthread_mutex_unlock(&philo->info->forks[0]);
	return (NULL);
}

void	one_philo(t_info *info, t_philos *philo)
{
	philo->id = 0;
	philo->info = info;
	philo->last_meal_t = info->start_time;
	philo->meals_eaten = 0;
	pthread_mutex_init(&philo->had_full_m, NULL);
	pthread_mutex_init(&philo->last_meal_m, NULL);
	pthread_create(&philo->thread, NULL, one_philo_life, philo);
	pthread_join(philo->thread, NULL);
	pthread_mutex_destroy(&philo->had_full_m);
	pthread_mutex_destroy(&philo->last_meal_m);
	free(info->forks);
}

void	philo_routine(t_philos *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->id]);
	pthread_mutex_lock(&philo->info->forks[(philo->id + 1)
		% philo->info->num_of_philos]);
	print_two_forks(philo);
	pthread_mutex_lock(&philo->last_meal_m);
	philo->last_meal_t = get_time();
	pthread_mutex_unlock(&philo->last_meal_m);
	print_call(*philo, EAT);
	sleepy_philo(philo->info->eat_time, philo);
	pthread_mutex_unlock(&philo->info->forks[(philo->id + 1)
		% philo->info->num_of_philos]);
	pthread_mutex_unlock(&philo->info->forks[philo->id]);
	print_call(*philo, SLEEP);
	sleepy_philo(philo->info->sleep_time, philo);
	print_call(*philo, THINK);
}

void	*philos_life(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->id % 2 == 0)
		sleepy_philo(philo->info->eat_time / 2, philo);
	while (can_continue(philo))
	{
		philo_routine(philo);
		philo->meals_eaten++;
		if (philo->info->eat_count != -1
			&& philo->meals_eaten == philo->info->eat_count)
			break ;
	}
	pthread_mutex_lock(&philo->had_full_m);
	philo->had_full = true;
	pthread_mutex_unlock(&philo->had_full_m);
	return (NULL);
}

void	create_philo(t_philos *philo, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philos)
	{
		pthread_create(&philo[i].thread, NULL, &philos_life, &philo[i]);
		i++;
	}
}
