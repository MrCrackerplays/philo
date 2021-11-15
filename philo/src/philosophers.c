/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/20 12:27:34 by pdruart       #+#    #+#                 */
/*   Updated: 2021/11/15 14:28:56 by pdruart       ########   odam.nl         */
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
	while (get_table()->finished >= 0
		&& (unsigned int)get_table()->finished < get_table()->seats)
	{
		if (phil_eat(phil, get_table()) == -1
			|| phil_sleep(phil, get_table()) == -1)
			break ;
		if (phil->times_eaten == get_table()->meal_goal)
		{
			pthread_mutex_lock(&get_table()->finish_setting);
			get_table()->finished += 1;
			pthread_mutex_unlock(&get_table()->finish_setting);
		}
	}
	return (arg);
}

int	clean_table(void)
{
	t_table	*table;
	int		ret;

	table = get_table();
	ret = pthread_mutex_destroy(&table->finish_setting);
	ret += pthread_mutex_destroy(&table->printing);
	ret += pthread_mutex_destroy(&table->death_check);
	return (ret);
}

int	main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	if (prepare_table(get_table(), argv, argc) == 0)
	{
		clean_philos(get_table()->first_philo, get_table());
		return (1);
	}
	pthread_mutex_init(&get_table()->printing, NULL);
	get_table()->deaths = 0;
	pthread_mutex_init(&get_table()->finish_setting, NULL);
	get_table()->finished = 0;
	pthread_mutex_init(&get_table()->death_check, NULL);
	start_threads(get_table(), &philosopher);
	catch_threads(get_table()->first_philo);
	clean_philos(get_table()->first_philo, get_table());
	clean_table();
	return (0);
}
