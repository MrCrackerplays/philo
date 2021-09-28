/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_threads.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/28 13:45:13 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/28 14:40:48 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREADS_H
# define PHILO_THREADS_H
# include <philosophers.h>

void	start_threads(t_table *table, void *(*function)(void *));
void	catch_threads(t_philosopher *phil);

#endif