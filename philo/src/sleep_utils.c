/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sleep_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/28 13:50:19 by pdruart       #+#    #+#                 */
/*   Updated: 2021/11/16 17:28:03 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <philo_mutex.h>
#include <unistd.h>
#include <pl_sleep.h>
#include <pl_time.h>
#include <pl_print.h>

int	check_starve(struct timeval curr_time, t_table *table, t_philosopher *phil)
{
	int	ret;

	ret = 0;
	if (table->deaths != 0)
		ret = -1;
	else if (is_past_by(curr_time, phil->last_meal, table->starvation_duration))
	{
		table->deaths = 1;
		ret = -1;
		thread_safe_print("has died\n", table, phil->seat_number, 1);
	}
	return (ret);
}

int	check_death(t_table *table)
{
	int	ret;

	ret = 0;
	if (philo_mutex_lock(&table->death_check, table) < 0)
		ret = 1;
	if (table->deaths > 0)
		ret = 1;
	if (philo_mutex_unlock(&table->death_check, table) < 0)
		ret = 1;
	return (ret);
}

int	ms_sleep(int miliseconds, t_table *table,
		t_philosopher *phil)
{
	struct timeval	start_time;
	struct timeval	current_time;
	int				ret;

	gettimeofday(&start_time, NULL);
	current_time = start_time;
	ret = 0;
	while (ret == 0 && is_past_by(current_time, start_time, miliseconds) == 0)
	{
		if (philo_mutex_lock(&table->death_check, table) < 0)
			ret = -1;
		if (ret != -1 && check_starve(current_time, table, phil) == -1)
			ret = -1;
		if (philo_mutex_unlock(&table->death_check, table) < 0)
			ret = -1;
		if (ret != -1 && usleep(100) == -1)
			ret = -1;
		gettimeofday(&current_time, NULL);
	}
	if (check_death(table))
		ret = -1;
	return (ret);
}
