/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   death.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/24 13:00:42 by pdruart       #+#    #+#                 */
/*   Updated: 2021/11/26 14:43:47 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <death.h>
#include <pl_print.h>
#include <unistd.h>

void	should_starve(struct timeval curr_time,
			t_table *table, t_philosopher *phil)
{
	if (table->deaths == 0
		&& is_past_by(curr_time, phil->last_meal, table->starvation_duration))
	{
		table->deaths = 1;
		thread_safe_print("has died\n", table, phil->seat_number, 1);
	}
}

void	*death(void *arg)
{
	t_death_target	*target;
	t_table			*table;
	struct timeval	curr_time;
	t_philosopher	*phil;

	target = (t_death_target *) arg;
	table = target->table;
	phil = target->phil;
	while (phil->death_watch == 1 && table->finished >= 0 && table->deaths == 0
		&& (unsigned int) table->finished < table->seats)
	{
		usleep(500);
		gettimeofday(&curr_time, NULL);
		should_starve(curr_time, table, phil);
	}
	return (arg);
}

void	start_death(t_death_target *target)
{
	target->phil->death_watch = 1;
	if (pthread_create(&target->phil->grim_reaper, NULL, death, target) < 0)
		target->table->finished = -1;
}

void	catch_death(t_philosopher *phil)
{
	phil->death_watch = 0;
	pthread_join(phil->grim_reaper, NULL);
}
