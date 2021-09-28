/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/20 12:27:34 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/28 14:47:18 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <philosophers.h>
#include <philo_threads.h>
#include <pl_sleep.h>

pthread_mutex_t	g_mutextest;

void	*philosopher(void *arg)
{
	struct timeval	time;
	t_table			*table;

	table = (t_table *)arg;
	pthread_mutex_lock(&g_mutextest);
	ms_sleep(table->starvation_duration);
	gettimeofday(&time, NULL);
	printf("timethread:%li.%06i\n", time.tv_sec, time.tv_usec);
	pthread_mutex_unlock(&g_mutextest);
	return (NULL);
}

//odd grab right fork first, even grab left fork first

int	main(int argc, char **argv)
{
	t_table			table;
	struct timeval	time;

	if (argc != 5 && argc != 6)
		return (0);
	if (prepare_table(&table, argv, argc) == 0)
		clean_philos(table.first_philo);
	gettimeofday(&time, NULL);
	printf("timema1n:%li.%06i\n", time.tv_sec, time.tv_usec);
	start_threads(&table, &philosopher);
	ms_sleep(3000);
	catch_threads(table.first_philo);
	clean_philos(table.first_philo);
}
