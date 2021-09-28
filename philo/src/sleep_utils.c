/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sleep_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/28 13:50:19 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/28 14:21:27 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include <pl_sleep.h>

int	ms_sleep(unsigned long long miliseconds)
{
	struct timeval		start_time;
	struct timeval		current_time;
	unsigned long long	delta_time;

	miliseconds *= 1000;
	gettimeofday(&start_time, NULL);
	current_time = start_time;
	delta_time = ((current_time.tv_sec - start_time.tv_sec) * 1000000)
		+ (current_time.tv_usec - start_time.tv_usec);
	while (delta_time < miliseconds)
	{
		if (usleep(100) == -1)
			return (-1);
		gettimeofday(&current_time, NULL);
		delta_time = ((current_time.tv_sec - start_time.tv_sec) * 1000000)
			+ (current_time.tv_usec - start_time.tv_usec);
	}
	return (0);
}
