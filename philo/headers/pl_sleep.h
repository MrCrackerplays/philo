/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pl_sleep.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/28 14:13:53 by pdruart       #+#    #+#                 */
/*   Updated: 2021/10/05 12:25:36 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PL_SLEEP_H
# define PL_SLEEP_H
# include <philosophers.h>

int	ms_sleep(int miliseconds, t_table *table,
		t_philosopher *phil);

#endif