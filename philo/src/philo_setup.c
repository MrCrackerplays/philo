/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_setup.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/26 11:56:17 by pdruart       #+#    #+#                 */
/*   Updated: 2021/11/26 14:36:33 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <philo_mutex.h>
#include <stdlib.h>
#include <string.h>

t_philosopher	*new_philo(int seat_number, t_table *table)
{
	t_philosopher	*new_member;

	new_member = malloc(sizeof(t_philosopher));
	if (new_member == NULL)
		return (NULL);
	memset(new_member, '\0', sizeof(t_philosopher));
	new_member->seat_number = seat_number;
	new_member->neighbour = new_member;
	new_member->death_watch = 0;
	philo_mutex_init(&new_member->fork, table);
	return (new_member);
}

t_philosopher	*add_philo(t_philosopher **existing_philo, t_table *table)
{
	t_philosopher	*furthest;
	t_philosopher	*new_member;

	if (existing_philo == NULL)
		return (NULL);
	if (*existing_philo == NULL)
	{
		*existing_philo = new_philo(1, table);
		return (*existing_philo);
	}
	furthest = *existing_philo;
	while (furthest->neighbour->seat_number != 1)
		furthest = furthest->neighbour;
	new_member = new_philo(furthest->seat_number + 1, table);
	if (new_member == NULL)
		return (NULL);
	new_member->neighbour = furthest->neighbour;
	furthest->neighbour = new_member;
	return (new_member);
}

unsigned int	ft_atou(char *str)
{
	unsigned int	number;

	if (str == NULL)
		return (0);
	number = 0;
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (0);
	return (number);
}

int	prepare_table(t_table *table, char **argv, int argc)
{
	unsigned int	i;

	table->first_philo = NULL;
	table->seats = ft_atou(argv[1]);
	table->starvation_duration = ft_atou(argv[2]);
	table->meal_duration = ft_atou(argv[3]);
	table->sleep_duration = ft_atou(argv[4]);
	table->finished = 0;
	table->meal_goal = -1;
	i = 1;
	if (argc == 6)
		i = ft_atou(argv[5]);
	if (table->seats == 0 || table->starvation_duration <= 0
		|| table->meal_duration <= 0 || table->sleep_duration <= 0 || i <= 0)
		return (0);
	if (argc == 6)
		table->meal_goal = i;
	i = 0;
	while (i < table->seats)
	{
		if (add_philo(&table->first_philo, table) == NULL)
			return (0);
		i++;
	}
	return (1);
}

int	clean_philos(t_philosopher *philo, t_table *table)
{
	if (philo == NULL || table == NULL)
		return (1);
	if (philo->neighbour->seat_number != 1)
		clean_philos(philo->neighbour, table);
	philo_mutex_destroy(&philo->fork, table);
	free(philo);
	return (1);
}
