/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_print.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 11:31:50 by pdruart       #+#    #+#                 */
/*   Updated: 2021/10/05 14:44:46 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <philosophers.h>
#include <pthread.h>
#include <pl_print.h>
#include <stdio.h>

unsigned int	relative_time(t_table *table)
{
	struct timeval	relative;

	gettimeofday(&relative, NULL);
	relative.tv_sec = relative.tv_sec - table->dinner_time.tv_sec;
	if (relative.tv_usec >= table->dinner_time.tv_usec)
		relative.tv_usec = relative.tv_usec - table->dinner_time.tv_usec;
	else
	{
		relative.tv_sec--;
		relative.tv_usec = 1000000 - (table->dinner_time.tv_usec
				- relative.tv_usec);
	}
	return ((relative.tv_sec * 1000) + (relative.tv_usec / 1000));
}

int	thread_safe_print(char *str, t_table *table, unsigned int seat_number,
	int die)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&table->printing);
	if (die == 0)
	{
		pthread_mutex_lock(&table->death_check);
		if (table->deaths > 0)
			ret = -1;
		pthread_mutex_unlock(&table->death_check);
	}
	if (ret == 0)
		ret = printf("%u %u %s", relative_time(table), seat_number, str);
	if (die != 0)
		ret = -1;
	pthread_mutex_unlock(&table->printing);
	return (ret);
}
