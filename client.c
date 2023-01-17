/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 11:37:00 by nakebli           #+#    #+#             */
/*   Updated: 2023/01/17 14:06:19 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// void	ft_convert_byte(char c, int pid)
// {
// 	int		i;

// 	i = 1;
// 	while (i)
// 	{
// 		if (c & 128)
// 			kill(pid, SIGUSR1);
// 		else if (!(c & 128))
// 			kill(pid, SIGUSR2);
// 		c = c << 1;
// 		i++;
// 		if (i == 9)
// 			i = 0;
// 	}
// }

void	send_bits(int pid, char *message)
{
	int	i;
	int	bit;

	bit = -1;
	i = 0;
	if (!message)
		exit(EXIT_FAILURE);
	while (1)
	{
		bit = -1;
		while (++bit < 9)
		{
			if (message[i] & (128 >> bit))
			{
				if (kill(pid, SIGUSR1) == -1)
					exit(1);
			}
			else if (kill(pid, SIGUSR2) == -1)
				exit(1);
			usleep(100);
		}
		if (!message[i])
			break ;
		++i;
	}
}

void	recieved(int sing)
{
	if (sing == SIGUSR1)
		printf("message recieved :)\n");
}

int	main(int ac, char **av)
{
	int		i;
	int		pid;

	if (ac == 3 && strlen(av[2]))
	{
		pid = atoi(av[1]);
		signal(SIGUSR1, recieved);
		i = 0;
		send_bits(pid, av[2]);
		i++;
		usleep(200);
		return (0);
	}
}
