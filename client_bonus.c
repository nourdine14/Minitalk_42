/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 11:37:00 by nakebli           #+#    #+#             */
/*   Updated: 2023/01/21 13:29:49 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

void	send_bits(int pid, char c)
{
	int	bit;
	int	k_ret;

	bit = -1;
	while (++bit < 8)
	{
		if (c & (128 >> bit))
		{
			k_ret = kill(pid, SIGUSR1);
			if (k_ret == -1)
				exit(1);
		}
		else
		{
			k_ret = kill(pid, SIGUSR2);
			if (k_ret == -1)
				exit(1);
		}
		usleep(2000);
	}
}

void	send_msg(int pid, char *msg)
{
	int	i;

	i = 0;
	if (!msg)
		exit(EXIT_FAILURE);
	while (1)
	{
		send_bits(pid, msg[i]);
		if (!msg[i])
			break ;
		i++;
	}
}

void	recieved(int sing)
{
	if (sing == SIGUSR1)
		ft_putstr_fd("\x1B[32m MESSAGE RECEIVED 🤓\x1B[0m\n", 1);
}

int	check_pid(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
	}
	return (1);
}

int	main(int ac, char **av)
{
	int		i;
	int		pid;

	if (ac == 3 && strlen(av[2]))
	{
		pid = ft_atoi(av[1]);
		if (!pid)
		{
			ft_putstr_fd("\x1B[31mERORR : BAD PROCESS ID\x1B[0m\n", 1);
			return (0);
		}
		signal(SIGUSR1, recieved);
		i = 0;
		send_msg(pid, av[2]);
		i++;
		usleep(200);
		return (0);
	}
	else
		ft_putstr_fd("\x1B[31mSYNTAX ERROR: ./client + PID + MESSAGE\x1B[0m\n", 1);
}
