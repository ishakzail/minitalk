/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izail <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:05:42 by izail             #+#    #+#             */
/*   Updated: 2022/02/24 13:20:17 by izail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putnbr(int nb)
{
	if (nb >= 10)
		ft_putnbr(nb / 10);
	write(1, &"0123456789"[nb % 10], 1);
}

void	ft_putstr_fd(char *str, int fd)
{
	if (str)
		while (*str)
			write(fd, str++, 1);
}

void	reciver(int sig, siginfo_t *info, void *unused)
{
	static int	bit;
	static char	c;
	static int	pid_client = 0;

	(void)unused;
	if (info->si_pid != pid_client)
	{
		bit = 0;
		c = 0;
		pid_client = info->si_pid;
	}
	c = c << 1 | (sig - 30);
	if (++bit < 8)
		return ;
	write(1, &c, 1);
	bit = 0;
	c = 0;
}

int	main(void)
{
	struct sigaction	s_action;

	ft_putstr_fd("Pid :", 1);
	ft_putnbr(getpid());
	s_action.sa_sigaction = &reciver;
	s_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_action, NULL);
	sigaction(SIGUSR2, &s_action, NULL);
	write(1, "\n", 1);
	while (1)
		pause();
}
