/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 12:01:45 by nakebli           #+#    #+#             */
/*   Updated: 2023/01/17 14:19:46 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "libft/libft.h"
#include "printf/libftprintf.h"

// void	signal_handler(int signum, siginfo_t *info, void *context)
// {
// 	// static char	c = 0x00;
// 	static int	i = 0;

// 	(void) context;
// 	(void) info;
// 	if (signum == SIGUSR1)
// 		printf("1");
// 		// c = (c << 1) | 1;
// 	else if (signum == SIGUSR2)
// 		printf("0");
// 		// c = (c << 1) & 1;
// 	// if (i != 1 && i % 7 == 0)
// 	// 	write(1, &c, 1);
// 	i++;
// }

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static char	c = 'a';
	static int	bit = 0;
	static int	pid = 0;

	(void) context;
	if (!(info)->si_pid)
		return ;
	pid = info->si_pid;
	if (signum == SIGUSR1)
		c = (c << 1) | 1;
	else if (signum == SIGUSR2)
		c = (c << 1) & 1;
	bit++;
	if (bit == 9)
	{
		if (!c)
			kill(pid, SIGUSR1);
		ft_printf("%c", c);
		bit = 0;
		c = 0x00;
	}
}

// void	signal_handler(int signum, siginfo_t *info, void *context)
// {
// 	static char	c = 0xFF;
// 	static int	bit = 0;
// 	static int	pid = 0;

// 	(void) context;
// 	if ((info)->si_pid)
// 		pid = info->si_pid;
// 	if (signum == SIGUSR1)
// 		c |= 0x80 >> bit;
// 	else if (signum == SIGUSR2)
// 		c ^= 0x80 >> bit;
// 	if (++bit == 9)
// 	{
// 		if (!c)
// 			kill(pid, SIGUSR1);
// 		ft_printf("%c", c);
// 		bit = 0;
// 		c = 0xFF;
// 	}
// }

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
