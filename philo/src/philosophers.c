/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/20 12:27:34 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/22 13:54:00 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <philosophers.h>

void	test(void)
{
	return ;
}

int	main(int argc, char **argv)
{
	struct timeval	time;
	gettimeofday(&time, NULL);
	printf("time:%li\n", time.tv_sec);
	if (argc != 5 && argc != 6)
		return (0);
	if (argv)
		return (0);
}
