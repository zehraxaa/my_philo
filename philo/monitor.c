/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:22:04 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/08/05 17:25:00 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	cont_death(t_philos *philo) //check_death'in which == 1 kısmı
{
	pthread_mutex_lock(&philo->last_meal_m);
	pthread_mutex_lock(&philo->had_full_m);
	if (philo->had_full == false && get_time() - philo->last_meal_t
		> philo->info->die_time)
		return (pthread_mutex_unlock(&philo->last_meal_m),
			pthread_mutex_unlock(&philo->had_full_m), 1);
	pthread_mutex_unlock(&philo->last_meal_m);
	pthread_mutex_unlock(&philo->had_full_m);
	return (0);
}

int	can_continue(t_philos *philo) //check_death'in which == 0 kısmı
{
	pthread_mutex_lock(&philo->info->is_anyphilo_died_m);
	if (philo->info->is_anyphilo_died == false)
	{
		pthread_mutex_unlock(&philo->info->is_anyphilo_died_m);
		return (1); // olumlu durum olarak 1 ile çıkış yapsın
	}
	return (0); //olumsuz durumda 0 la çıksın
}

void	*monitor(void *arg)
{
	int			index;
	int			count;
	t_philos	*philo;

	philo = (void *)arg;
	while (1)
	{
		index = -1;
		count = 0;
		while (++index < philo->info->num_of_philos)
		{
			if (cont_death(&philo[index]))
			{
				print_death(philo[index], DIE);
				return(NULL);
			}
			pthread_mutex_lock(&philo[index].had_full_m);
			if (philo[index].had_full == true)
				count++;
			pthread_mutex_unlock(&philo[index].had_full_m);
		}
		if (count == philo->info->eat_count)
			break;
	}
	return (NULL);
}
