/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/21 11:51:14 by pdruart       #+#    #+#                 */
/*   Updated: 2021/10/13 16:58:04 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	unsigned int			seat_number;
	int						times_eaten;
	pthread_t				*self;
	pthread_mutex_t			fork;
	struct timeval			last_meal;
	struct s_philosopher	*neighbour;
}	t_philosopher;

typedef struct s_table
{
	unsigned int	seats;
	int				starvation_duration;
	int				meal_duration;
	int				sleep_duration;
	int				meal_goal;
	int				deaths;
	struct timeval	dinner_time;
	pthread_mutex_t	printing;
	pthread_mutex_t	death_check;
	t_philosopher	*first_philo;
}	t_table;

int		prepare_table(t_table *table, char **argv, int argc);
void	clean_philos(t_philosopher *philo);

#endif