/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pl_time.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/04 15:04:51 by pdruart       #+#    #+#                 */
/*   Updated: 2021/10/05 14:56:29 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PL_TIME_H
# define PL_TIME_H
# include <sys/time.h>

int	is_past_by(struct timeval first, struct timeval second, int ms);

#endif