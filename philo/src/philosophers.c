/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/20 12:27:34 by pdruart       #+#    #+#                 */
/*   Updated: 2021/10/13 11:25:51 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <philosophers.h>
#include <pl_threads.h>
#include <phil_behavior.h>

t_table	*get_table(void)
{
	static t_table	table;

	return (&table);
}

void	*philosopher(void *arg)
{
	t_philosopher	*phil;

	phil = (t_philosopher *)arg;
	gettimeofday(&phil->last_meal, NULL);
	while (get_table()->meal_goal == -1
		|| phil->times_eaten < get_table()->meal_goal)
	{
		if (phil_eat(phil, get_table()) == -1
			|| phil_sleep(phil, get_table()) == -1)
			break ;
	}
	return (arg);
}

int	main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	if (prepare_table(get_table(), argv, argc) == 0)
	{
		clean_philos(get_table()->first_philo);
		return (1);
	}
	pthread_mutex_init(&get_table()->printing, NULL);
	get_table()->deaths = 0;
	pthread_mutex_init(&get_table()->death_check, NULL);
	start_threads(get_table(), &philosopher);
	catch_threads(get_table()->first_philo);
	clean_philos(get_table()->first_philo);
	return (0);
}
