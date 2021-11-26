/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/20 12:27:34 by pdruart       #+#    #+#                 */
/*   Updated: 2021/11/24 16:43:34 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_mutex.h>
#include <philosophers.h>
#include <pl_threads.h>
#include <phil_behavior.h>
#include <death.h>

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
		if (phil_eat(phil, get_table()) == -1)
			break ;
		if (get_table()->finished >= 0 && get_table()->meal_goal != -1
			&& phil->times_eaten == get_table()->meal_goal)
		{
			if (philo_mutex_lock(&get_table()->finish_setting, get_table()) < 0)
				get_table()->finished = -1;
			if (get_table()->finished >= 0)
				get_table()->finished += 1;
			if (philo_mutex_unlock(&get_table()->finish_setting,
					get_table()) < 0)
				get_table()->finished = -1;
		}
		if (get_table()->finished >= 0 && phil_sleep(phil, get_table()) == -1)
			break ;
	}
	return (arg);
}

void	clean_table(void)
{
	t_table	*table;

	table = get_table();
	philo_mutex_destroy(&table->finish_setting, table);
	philo_mutex_destroy(&table->printing, table);
	philo_mutex_destroy(&table->death_check, table);
}

int	main(int argc, char **argv)
{
	pthread_t	grim_reaper;

	if (argc != 5 && argc != 6)
		return (1);
	if (prepare_table(get_table(), argv, argc) == 0)
		return (clean_philos(get_table()->first_philo, get_table()));
	get_table()->deaths = 0;
	philo_mutex_init(&get_table()->printing, get_table());
	philo_mutex_init(&get_table()->finish_setting, get_table());
	philo_mutex_init(&get_table()->death_check, get_table());
	gettimeofday(&get_table()->dinner_time, NULL);
	start_threads(get_table(), &philosopher);
	start_death(get_table(), &grim_reaper);
	catch_threads(get_table()->first_philo);
	catch_death(&grim_reaper);
	clean_philos(get_table()->first_philo, get_table());
	clean_table();
	if (get_table()->finished < 0)
		return (1);
	return (0);
}
