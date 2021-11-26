/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   death.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/24 14:17:54 by pdruart       #+#    #+#                 */
/*   Updated: 2021/11/26 14:41:43 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEATH_H
# define DEATH_H
# include <philosophers.h>
# include <pl_time.h>

typedef struct s_death_target
{
	t_philosopher	*phil;
	t_table			*table;
}	t_death_target;

void	start_death(t_death_target *target);
void	catch_death(t_philosopher *phil);

#endif