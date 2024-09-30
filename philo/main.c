/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:00:13 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/09/30 15:09:31 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocate(pthread_t **th, t_global_info **info, t_mutex *mtx, t_input prms)
{
	*th = (pthread_t *) malloc(sizeof(pthread_t) * (prms.total_philos + 1));
	if (!*th)
		return (printf("memory allocation error\n"), 1);
	*info = (t_global_info *) malloc(sizeof(t_global_info) * prms.total_philos);
	if (!*info)
		return (printf("memory allocation error\n"), 1);
	mtx->mutex_fork = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * (prms.total_philos));
	if (!mtx->mutex_fork)
		return (printf("memory allocation error\n"), 1);
	mtx->mutex_extra = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * MUTEX_EXTRA);
	if (!mtx->mutex_extra)
		return (printf("memory allocation error\n"), 1);
	return (0);
}

static int	clean_up(pthread_t *th, t_global_info *info, t_mutex mutex, int n)
{
	int	i;

	i = 0;
	while (i < n)
		pthread_mutex_destroy(&mutex.mutex_fork[i++]);
	i = 0;
	while (i < MUTEX_EXTRA)
		pthread_mutex_destroy(&mutex.mutex_extra[i++]);
	if (info)
	{
		if (info->dead)
			free(info->dead);
		if (info->number_eats)
			free(info->number_eats);
	}
	free(th);
	free(info);
	if (mutex.mutex_fork)
		free(mutex.mutex_fork);
	if (mutex.mutex_extra)
		free(mutex.mutex_extra);
	return (0);
}

int	check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i] != NULL)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (!ft_isdigit(av[i][j]) || simple_atoi(av[i]) == 0)
			{
				if (i == 5 && simple_atoi(av[i]) == 0)
					return (0);
				return (-1);
			}
			j++;
		}
		i++;
	}
	if (simple_atoi(av[1]) > 200)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t		*thread;
	t_input			arguments;
	t_global_info	*info;
	t_mutex			mutex;

	if (argc < 5 || argc > 6)
		return (printf("Invalid argument number\n"), 1);
	if (check_args(argv) == -1)
		return (printf("Invalid arguments\n"), 1);
	init_params(argv, &arguments, argc);
	memset(&mutex, 0, sizeof(t_mutex));
	memset(&info, 0, sizeof(t_global_info *));
	if (allocate(&thread, &info, &mutex, arguments) != 0)
		return (clean_up(thread, info, mutex, arguments.total_philos));
	if (init_mutex(&mutex, arguments.total_philos) != 0)
		return (clean_up(thread, info, mutex, arguments.total_philos));
	if (init_g_info(info, mutex, arguments) != 0)
		return (clean_up(thread, info, mutex, arguments.total_philos));
	ft_world(thread, info);
	clean_up(thread, info, mutex, arguments.total_philos);
	return (0);
}
