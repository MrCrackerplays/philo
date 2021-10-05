/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sleep_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/28 13:50:19 by pdruart       #+#    #+#                 */
/*   Updated: 2021/10/05 14:56:38 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
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

int	ms_sleep(int miliseconds, t_table *table,
		t_philosopher *phil)
{
	struct timeval		start_time;
	struct timeval		current_time;
	int					ret;

	gettimeofday(&start_time, NULL);
	current_time = start_time;
	ret = 0;
	while (ret == 0 && is_past_by(current_time, start_time, miliseconds) == 0)
	{
		pthread_mutex_lock(&table->death_check);
		if (check_starve(current_time, table, phil) == -1)
			ret = -1;
		pthread_mutex_unlock(&table->death_check);
		if (ret != -1 && usleep(100) == -1)
			ret = -1;
		gettimeofday(&current_time, NULL);
	}
	pthread_mutex_lock(&table->death_check);
	if (table->deaths > 0)
		ret = -1;
	pthread_mutex_unlock(&table->death_check);
	return (ret);
}