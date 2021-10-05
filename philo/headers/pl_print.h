/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pl_print.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 11:30:43 by pdruart       #+#    #+#                 */
/*   Updated: 2021/10/05 14:43:20 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PL_PRINT_H
# define PL_PRINT_H
# include <philosophers.h>

int	thread_safe_print(char *str, t_table *table, unsigned int seat_number,
	int die);

#endif