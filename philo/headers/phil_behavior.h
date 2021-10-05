/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   phil_behavior.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/05 14:09:20 by pdruart       #+#    #+#                 */
/*   Updated: 2021/10/05 14:14:17 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHIL_BEHAVIOR_H
# define PHIL_BEHAVIOR_H
# include <philosophers.h>

int	phil_eat(t_philosopher *phil, t_table *table);
int	phil_sleep(t_philosopher *phil, t_table *table);

#endif