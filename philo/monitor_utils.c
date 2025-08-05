/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:20:44 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/08/05 17:24:58 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_call(t_philos philo, char *str) //kill = 0 olduğu durumlarda
{ //philo parametresini neden * sız koyduğumuzu öğren
	pthread_mutex_lock(&philo.info->is_anyphilo_died_m);
	if (philo.had_full == false && philo.info->is_anyphilo_died == false)
	{
		pthread_mutex_lock(&philo.info->print_mutex);
		printf("%ld %d %s\n", get_time() - philo.info->start_time, philo.id + 1, str);
		pthread_mutex_unlock(&philo.info->print_mutex);
	}
	pthread_mutex_unlock(&philo.info->is_anyphilo_died_m);
}

void	print_death(t_philos philo, char *str) //kill = 1 oldğu durumlarda
{
	pthread_mutex_lock(&philo.info->is_anyphilo_died_m);
	philo.info->is_anyphilo_died = true;
	pthread_mutex_unlock(&philo.info->is_anyphilo_died_m);
	pthread_mutex_lock(&philo.info->print_mutex);
	printf("%ld %d %s\n", get_time() - philo.info->start_time, philo.id + 1, str);
	pthread_mutex_unlock(&philo.info->print_mutex);
	return (NULL);
}