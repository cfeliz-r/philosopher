/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:50:39 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/09/30 12:44:47 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_eat(t_global_info *data)
{
	pthread_mutex_lock(data->mutex_l_ate);
	data->last_ate = gettime_ms() - data->start_time;
	pthread_mutex_unlock(data->mutex_l_ate);
	printf("%lld %d is eating\n", data->last_ate, data->philo);
	pthread_mutex_lock(data->mutex_to_eats);
	data->number_eats[data->philo - 1] += 1;
	pthread_mutex_unlock(data->mutex_to_eats);
}

void	ft_print_death(t_global_info *data)
{
	pthread_mutex_lock(data->mutex_to_print);
	printf("%lld %d died\n", gettime_ms() - data->start_time, data->philo);
	pthread_mutex_unlock(data->mutex_to_print);
}

void	ft_print(t_global_info *data, int action)
{
	pthread_mutex_lock(data->mutex_to_print);
	if (checker_dead(data) == 0)
	{
		if (action == FORK)
			printf("%lld %d has taken a fork\n",
				gettime_ms() - data->start_time, data->philo);
		else if (action == EAT)
			print_eat(data);
		else if (action == SLEEP)
			printf("%lld %d is sleeping\n",
				gettime_ms() - data->start_time, data->philo);
		else if (action == THINK)
			printf("%lld %d is thinking\n",
				gettime_ms() - data->start_time, data->philo);
	}
	pthread_mutex_unlock(data->mutex_to_print);
}
