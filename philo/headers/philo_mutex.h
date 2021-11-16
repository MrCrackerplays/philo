/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_mutex.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/15 12:27:27 by pdruart       #+#    #+#                 */
/*   Updated: 2021/11/16 14:30:27 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_MUTEX_H
# define PHILO_MUTEX_H
# include <pthread.h>
# include <philosophers.h>

int	philo_mutex_init(pthread_mutex_t *mutex, t_table *table);
int	philo_mutex_destroy(pthread_mutex_t *mutex, t_table *table);
int	philo_mutex_lock(pthread_mutex_t *mutex, t_table *table);
int	philo_mutex_unlock(pthread_mutex_t *mutex, t_table *table);

#endif