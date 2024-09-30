/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_threads.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:51:26 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/09/30 15:09:31 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_params(char **argv, t_input *arg, int argc)
{
	arg->total_philos = simple_atoi(argv[1]);
	arg->time_to_die = (simple_atoi(argv[2]));
	arg->time_to_eat = (simple_atoi(argv[3]));
	arg->time_to_sleep = (simple_atoi(argv[4]));
	if (argc == 6)
		arg->count_meals_required = (simple_atoi(argv[5]));
	else
		arg->count_meals_required = 0;
}

int	init_mutex(t_mutex *mutex, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_init(&mutex->mutex_fork[i], NULL);
		i++;
	}
	i = 0;
	while (i < MUTEX_EXTRA)
	{
		pthread_mutex_init(&mutex->mutex_extra[i], NULL);
		i++;
	}
	return (0);
}

int	ft_world(pthread_t *th, t_global_info *data)
{
	int		i;

	i = 0;
	if (data->params.total_philos == 1)
	{
		printf("0  1 has taken a fork\n");
		ft_usleep(data->params.time_to_die, data);
		printf("%d  1 died\n", data->params.time_to_die);
		return (1);
	}
	while (i < data->params.total_philos)
	{
		data[i].start_time = gettime_ms();
		pthread_create(&th[i], NULL, &philo_routine, &data[i]);
		i++;
		if (i == data->params.total_philos)
			pthread_create(&th[i], NULL, &routine_monitor, data);
	}
	i = 0;
	while (i <= data->params.total_philos)
		pthread_join(th[i++], NULL);
	return (0);
}

static int	init_dead_and_eat(int **dead, int **eat, t_input arg)
{
	*dead = (int *) malloc(sizeof(int));
	if (!*dead)
		return (printf("memory allocation error\n"), 1);
	**dead = 0;
	*eat = (int *) malloc(sizeof(int) * arg.total_philos);
	if (!*eat)
		return (printf("memory allocation error\n"), 1);
	memset(*eat, 0, sizeof(int) * arg.total_philos);
	return (0);
}

int	init_g_info(t_global_info *data, t_mutex mutex, t_input arg)
{
	int	*dead;	
	int	*eat;
	int	i;

	if (init_dead_and_eat(&dead, &eat, arg) != 0)
		return (1);
	i = 0;
	while (i < arg.total_philos)
	{
		data[i].philo = i + 1;
		data[i].params = arg;
		data[i].fork = mutex.mutex_fork;
		data[i].dead = dead;
		data[i].last_ate = 0;
		data[i].number_eats = eat;
		data[i].mutex_to_print = &mutex.mutex_extra[0];
		data[i].mutex_to_dead = &mutex.mutex_extra[1];
		data[i].mutex_to_eats = &mutex.mutex_extra[2];
		data[i].mutex_l_ate = &mutex.mutex_extra[3];
		i++;
	}
	return (0);
}
