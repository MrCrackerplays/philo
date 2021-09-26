/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/20 12:27:34 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/26 14:17:53 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <philosophers.h>

pthread_mutex_t	mutextest;

void	*philosopher(void *arg)
{
	struct timeval	time;

	pthread_mutex_lock(&mutextest);
	usleep(2000000);
	gettimeofday(&time, NULL);
	printf("timethread:%li.%i\n", time.tv_sec, time.tv_usec);
	pthread_mutex_unlock(&mutextest);
	return arg;
}
//odd grab right fork first, even grab left fork first
int	main(int argc, char **argv)
{
	t_table			table;

	if (argc != 5 && argc != 6)
		return (0);
	if (prepare_table(&table, argv, argc) == 0)
		clean_philos(table.first_philo);
	if (argv)
		return (0);
	// struct timeval	time;
	// pthread_t		*phils;
	// int				i;

	// phils = malloc(sizeof(pthread_t) * 4);
	// pthread_mutex_init(&mutextest, NULL);
	// i = 0;
	// while (i < 4)
	// {
	// 	pthread_create(&phils[i], NULL, &philosopher, NULL);
	// 	i++;
	// }
	// usleep(500000);
	// gettimeofday(&time, NULL);
	// printf("timemain:%li.%i\n", time.tv_sec, time.tv_usec);
	// i = 0;
	// while (i < 4)
	// {
	// 	pthread_join(phils[i], NULL);
	// 	printf("received %i\n", i);
	// 	i++;
	// }
	// free(phils);
}
