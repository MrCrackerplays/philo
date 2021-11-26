/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/21 11:51:14 by pdruart       #+#    #+#                 */
/*   Updated: 2021/11/26 14:20:04 by pdruart       ########   odam.nl         */
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
	int						death_watch;
	pthread_t				self;
	pthread_t				grim_reaper;
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
	int				finished;
	struct timeval	dinner_time;
	pthread_mutex_t	printing;
	pthread_mutex_t	death_check;
	pthread_mutex_t	finish_setting;
	t_philosopher	*first_philo;
}	t_table;

int	prepare_table(t_table *table, char **argv, int argc);
int	clean_philos(t_philosopher *philo, t_table *table);

#endif