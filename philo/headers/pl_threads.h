/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pl_threads.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/28 13:45:13 by pdruart       #+#    #+#                 */
/*   Updated: 2021/10/05 14:08:38 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PL_THREADS_H
# define PL_THREADS_H
# include <philosophers.h>

void	start_threads(t_table *table, void *(*function)(void *));
void	catch_threads(t_philosopher *phil);

#endif