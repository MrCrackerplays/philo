/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/04 15:08:18 by pdruart       #+#    #+#                 */
/*   Updated: 2021/10/07 12:33:30 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pl_time.h>

int	is_past_by(struct timeval first, struct timeval second, int ms)
{
	int	seconds;
	int	micro_seconds;

	seconds = ms / 1000;
	micro_seconds = (ms % 1000) * 1000;
	micro_seconds += second.tv_usec;
	seconds += micro_seconds / 1000000;
	micro_seconds = micro_seconds % 1000000;
	seconds += second.tv_sec;
	if ((first.tv_sec > seconds)
		|| (first.tv_sec == seconds && first.tv_usec >= micro_seconds))
		return (1);
	return (0);
}
