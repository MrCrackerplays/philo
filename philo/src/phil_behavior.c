/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   phil_behavior.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/05 14:11:01 by pdruart       #+#    #+#                 */
/*   Updated: 2021/12/02 12:25:23 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <phil_behavior.h>
#include <philo_mutex.h>
#include <pl_print.h>
#include <pl_sleep.h>
#include <death.h>
#include <unistd.h>

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
	t_death_target	target;
	int				ret;

	if (table->seats % 2 == 1 && phil->seat_number % 2)
		usleep(500);
	target.phil = phil;
	target.table = table;
	start_death(&target);
	if (philo_mutex_lock(fork, table) < 0)
		return (-1);
	catch_death(phil);
	ret = thread_safe_print("has taken a fork\n", table, phil->seat_number, 0);
	if (phil->neighbour->seat_number == phil->seat_number)
		return (ms_sleep(table->starvation_duration + 10, table, phil));
	return (ret);
}

//odd grab right fork first, even grab left fork first

int	phil_eat(t_philosopher *phil, t_table *table)
{
	int	ret;

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
	if (philo_mutex_unlock(&phil->neighbour->fork, table) < 0)
		ret = -1;
	if (philo_mutex_unlock(&phil->fork, table) < 0)
		ret = -1;
	return (ret);
}
