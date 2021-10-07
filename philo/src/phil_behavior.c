/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   phil_behavior.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/05 14:11:01 by pdruart       #+#    #+#                 */
/*   Updated: 2021/10/07 12:34:32 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <phil_behavior.h>
#include <pl_print.h>
#include <pl_sleep.h>
#include <stdio.h>

int	phil_sleep(t_philosopher *phil, t_table *table)
{
	if (thread_safe_print("is sleeping\n", table, phil->seat_number, 0) == -1
		|| ms_sleep(table->sleep_duration, table, phil) == -1
		|| thread_safe_print("is thinking\n", table,
			phil->seat_number, 0) == -1)
		return (-1);
	return (0);
}

int	take_fork(pthread_mutex_t *fork, t_philosopher *phil, t_table *table)
{
	pthread_mutex_lock(fork);
	return (thread_safe_print("has taken a fork\n", table,
			phil->seat_number, 0));
}

//odd grab right fork first, even grab left fork first

int	phil_eat(t_philosopher *phil, t_table *table)
{
	int				ret;
	struct timeval	t;

	ret = 0;
	if (phil->seat_number % 2 == 1
		&& take_fork(&phil->neighbour->fork, phil, table) == -1)
		ret = -1;
	if (ret != -1 && take_fork(&phil->fork, phil, table) == -1)
		ret = -1;
	if (ret != -1 && phil->seat_number % 2 == 0
		&& take_fork(&phil->neighbour->fork, phil, table) == -1)
		ret = -1;
	phil->times_eaten++;
	if (ret != -1)
		gettimeofday(&phil->last_meal, NULL);
	if (ret != -1 && (thread_safe_print("is eating\n", table,
				phil->seat_number, 0) == -1
			|| ms_sleep(table->meal_duration, table, phil) == -1))
		ret = -1;
	pthread_mutex_unlock(&phil->neighbour->fork);
	pthread_mutex_unlock(&phil->fork);
	gettimeofday(&t, NULL);
	return (ret);
}
