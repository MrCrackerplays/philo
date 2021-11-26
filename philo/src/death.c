/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   death.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/24 13:00:42 by pdruart       #+#    #+#                 */
/*   Updated: 2021/11/24 16:43:20 by pdruart       ########   odam.nl         */
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
	t_table			*table;
	unsigned int	i;
	struct timeval	curr_time;
	t_philosopher	*phil;

	table = (t_table *) arg;
	while (table->finished >= 0 && table->deaths == 0
		&& (unsigned int) table->finished < table->seats)
	{
		i = 0;
		phil = table->first_philo;
		usleep(500);
		gettimeofday(&curr_time, NULL);
		while (i < table->seats && table->finished >= 0 && table->deaths == 0
			&& (unsigned int) table->finished < table->seats)
		{
			should_starve(curr_time, table, phil);
			phil = phil->neighbour;
			i++;
		}
	}
	return (arg);
}

void	start_death(t_table *table, pthread_t *grim_reaper)
{
	if (pthread_create(grim_reaper, NULL, death, table) < 0)
		table->finished = -1;
}

void	catch_death(pthread_t *grim_reaper)
{
	pthread_join(*grim_reaper, NULL);
}
