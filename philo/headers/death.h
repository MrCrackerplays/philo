/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   death.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/24 14:17:54 by pdruart       #+#    #+#                 */
/*   Updated: 2021/11/24 14:24:18 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEATH_H
# define DEATH_H
# include <philosophers.h>
# include <pl_time.h>

void	start_death(t_table *table, pthread_t *grim_reaper);
void	catch_death(pthread_t *grim_reaper);

#endif