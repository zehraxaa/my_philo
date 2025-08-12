/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:21:54 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/08/09 15:53:33 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *str)
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

static int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc == 5 || argc == 6)
	{
		i = 1;
		j = 0;
		while (argv[i])
		{
			j = 0;
			while (argv[i][j])
			{
				if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
					return (write(2, "Error: Arguments must be number!\n", 33));
				j++;
			}
			i++;
		}
	}
	else
		return (write(2, "Error: Wrong number of arguments!\n", 34));
	return (0);
}

static int	initialize_arg(t_info *info, char **argv)
{
	info->num_of_philos = ft_atoi(argv[1]);
	info->die_time = ft_atoi(argv[2]);
	info->eat_time = ft_atoi(argv[3]);
	info->sleep_time = ft_atoi(argv[4]);
	if (argv[5])
		info->eat_count = ft_atoi(argv[5]);
	else
		info->eat_count = -1;
	if (info->eat_count == 0)
		return (write(2, "Error: eat count can't be zero\n", 31));
	info->start_time = get_time();
	info->is_anyphilo_died = false;
	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* info->num_of_philos);
	if (!info->forks)
		return (1);
	if (info-> num_of_philos == 0)
		return (write(2, "Error: philos must be more than 0\n", 34));
	if (mutex_creator_fork(info) != 0)
	{
		free(info->forks);
		return (1);
	}
	return (0);
}

static int	initialize_philo(t_philos *philo, t_info *info)
{
	int	index;

	index = 0;
	while (index < info->num_of_philos)
	{
		philo[index].id = index;
		philo[index].info = info;
		philo[index].last_meal_t = info->start_time;
		philo[index].meals_eaten = 0;
		philo[index].had_full = false;
		if (pthread_mutex_init(&philo[index].had_full_m, NULL))
			return (1);
		if (pthread_mutex_init(&philo[index].last_meal_m, NULL))
			return (1);
		index++;
	}
	return (0);
}

static int	philo_monitor(t_philos *philos, t_info *info)
{
	pthread_t	monitor_thread;
	int			i;

	create_philo(philos, info);
	if (pthread_create(&monitor_thread, NULL, &monitor, philos))
	{
		free(info->forks);
		free(philos);
		return (1);
	}
	i = -1;
	while (++i < info->num_of_philos)
		pthread_join(philos[i].thread, NULL);
	cleanup(&monitor_thread, philos);
	return (0);
}

int	main(int ac, char **av)
{
	t_info		info;
	t_philos	*philos;

	if (check_args(ac, av) || initialize_arg(&info, av))
		return (1);
	philos = (t_philos *)malloc(sizeof(t_philos) * info.num_of_philos);
	if (!philos)
		return (1);
	if (info.num_of_philos == 1)
	{
		one_philo(&info, philos);
		free(philos);
		return (1);
	}
	if (initialize_philo(philos, &info))
	{
		free(info.forks);
		free(philos);
		return (1);
	}
	if (philo_monitor(philos, &info))
		return (1);
	return (0);
}
