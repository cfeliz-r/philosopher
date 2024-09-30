/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:01:47 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/09/30 12:45:25 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	checker_dead(t_global_info *data)
{
	pthread_mutex_lock(data->mutex_to_dead);
	if (*data->dead == 1)
	{
		pthread_mutex_unlock(data->mutex_to_dead);
		return (1);
	}
	pthread_mutex_unlock(data->mutex_to_dead);
	return (0);
}

void	ft_usleep(long long wait, t_global_info *data)
{
	long long	start_time;

	start_time = gettime_ms();
	while (gettime_ms() < start_time + wait)
	{
		if (checker_dead(data) == 1)
			return ;
		usleep(100);
	}
}

long long	gettime_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	simple_atoi(const char *str)
{
	int		i;
	int		num;

	i = 0;
	num = 0;
	while (ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (num);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
