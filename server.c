/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 12:01:45 by nakebli           #+#    #+#             */
/*   Updated: 2023/01/18 19:55:05 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "libft/libft.h"
#include "printf/libftprintf.h"

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static char	c = 0x00;
	static int	bit = 0;
	static int	pid = 0;

	(void) context;
	if (pid && pid != info->si_pid)
	{
		bit = 0;
		c = 0x00;
	}
	if ((info)->si_pid)
		pid = info->si_pid;
	if (signum == SIGUSR1)
		c = (c << 1) | 1;
	else if (signum == SIGUSR2)
		c = (c << 1);
	if (++bit == 8)
	{
		if (!c)
			kill(pid, SIGUSR1);
		ft_printf("%c", c);
		bit = 0;
		c = 0x00;
	}
}

int	main(void)
{
	struct sigaction	act;

	ft_printf("pid is : %d\n", getpid());
	act.sa_sigaction = signal_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
