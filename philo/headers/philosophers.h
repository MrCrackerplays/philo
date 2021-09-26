/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/21 11:51:14 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/26 14:18:13 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>

typedef struct s_philosopher
{
	unsigned int			seat_number;
	unsigned int			times_eaten;
	pthread_t				*self;
	struct s_philosopher	*neighbour;
	pthread_mutex_t			fork;
}	t_philosopher;

typedef struct s_table
{
	unsigned int	seats;
	unsigned int	starvation_duration;
	unsigned int	meal_duration;
	unsigned int	sleep_duration;
	unsigned int	meal_goal;
	t_philosopher	*first_philo;
}	t_table;

int		prepare_table(t_table *table, char **argv, int argc);
void	clean_philos(t_philosopher *philo);

#endif