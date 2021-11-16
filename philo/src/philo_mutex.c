/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_mutex.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/15 12:27:15 by pdruart       #+#    #+#                 */
/*   Updated: 2021/11/16 14:30:20 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_mutex.h>

int	philo_mutex_init(pthread_mutex_t *mutex, t_table *table)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
		table->finished = -1;
	return (table->finished);
}

int	philo_mutex_destroy(pthread_mutex_t *mutex, t_table *table)
{
	if (pthread_mutex_destroy(mutex) != 0)
		table->finished = -1;
	return (table->finished);
}

int	philo_mutex_lock(pthread_mutex_t *mutex, t_table *table)
{
	if (pthread_mutex_lock(mutex) != 0)
		table->finished = -1;
	return (table->finished);
}

int	philo_mutex_unlock(pthread_mutex_t *mutex, t_table *table)
{
	if (pthread_mutex_unlock(mutex) != 0)
		table->finished = -1;
	return (table->finished);
}
