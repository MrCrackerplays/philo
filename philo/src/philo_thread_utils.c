/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_thread_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/28 13:38:54 by pdruart       #+#    #+#                 */
/*   Updated: 2021/11/26 14:06:21 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pl_threads.h>

void	start_threads(t_table *table, void *(*function)(void *))
{
	unsigned int	start_seat;
	t_philosopher	*phil;

	phil = table->first_philo;
	start_seat = phil->seat_number;
	while (1)
	{
		if (pthread_create(&phil->self, NULL, function, (void *)phil) < 0)
			table->finished = -1;
		phil = phil->neighbour;
		if (phil->seat_number == start_seat)
			break ;
	}
}

void	catch_threads(t_philosopher *phil)
{
	unsigned int	start_seat;

	start_seat = phil->seat_number;
	while (1)
	{
		pthread_join(phil->self, NULL);
		phil = phil->neighbour;
		if (phil->seat_number == start_seat)
			break ;
	}
}
