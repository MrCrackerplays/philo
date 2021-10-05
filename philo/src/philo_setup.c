/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_setup.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/26 11:56:17 by pdruart       #+#    #+#                 */
/*   Updated: 2021/10/04 17:10:44 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <stdlib.h>
#include <string.h>

t_philosopher	*new_philo(int seat_number)
{
	t_philosopher	*new_member;

	new_member = malloc(sizeof(t_philosopher));
	if (new_member == NULL)
		return (NULL);
	memset(new_member, '\0', sizeof(t_philosopher));
	new_member->seat_number = seat_number;
	new_member->neighbour = new_member;
	new_member->self = malloc(sizeof(pthread_t));
	if (new_member->self == NULL)
	{
		free(new_member);
		return (NULL);
	}
	pthread_mutex_init(&new_member->fork, NULL);
	return (new_member);
}

t_philosopher	*add_philo(t_philosopher **existing_philo)
{
	t_philosopher	*furthest;
	t_philosopher	*new_member;

	if (existing_philo == NULL)
		return (NULL);
	if (*existing_philo == NULL)
	{
		*existing_philo = new_philo(1);
		return (*existing_philo);
	}
	furthest = *existing_philo;
	while (furthest->neighbour->seat_number != 1)
		furthest = furthest->neighbour;
	new_member = new_philo(furthest->seat_number + 1);
	if (new_member == NULL)
		return (NULL);
	new_member->neighbour = furthest->neighbour;
	furthest->neighbour = new_member;
	return (new_member);
}

unsigned int	ft_atou(char *str)
{
	unsigned int		number;

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
	table->meal_goal = -1;
	i = 1;
	if (argc == 6)
		i = ft_atou(argv[5]);
	if (table->seats == 0 || table->starvation_duration == 0
		|| table->meal_duration == 0 || table->sleep_duration == 0 || i == 0)
		return (0);
	if (argc == 6)
		table->meal_goal = i;
	i = 0;
	while (i < table->seats)
	{
		if (add_philo(&table->first_philo) == NULL)
			return (0);
		i++;
	}
	gettimeofday(&table->dinner_time, NULL);
	return (1);
}

void	clean_philos(t_philosopher *philo)
{
	if (philo == NULL)
		return ;
	if (philo->neighbour->seat_number != 1)
		clean_philos(philo->neighbour);
	if (philo->self != NULL)
	{
		free(philo->self);
		philo->self = NULL;
	}
	pthread_mutex_destroy(&philo->fork);
	free(philo);
}
