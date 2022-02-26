/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izail <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 11:28:01 by izail             #+#    #+#             */
/*   Updated: 2022/02/24 14:40:36 by izail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(char *str)
{
	int	i;
	int	nb;
	int	sign;

	sign = 1;
	i = 0;
	nb = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (str[i] - '0') + (nb * 10);
		i++;
	}
	return (nb * sign);
}

int	check_if_int(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

void	message_recived(int signum)
{
	if (signum == SIGUSR1)
		write(1, "\x1b[32mSignal Recived\n", 20);
}

void	send_bits(int c, int pid)
{
	int	i;
	int	send;

	i = 7;
	while (i > -1)
	{
		send = c >> i-- & 1;
		if (send)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(500);
	}
}

int	main(int ac, char **av)
{
	int	pid;

	signal(SIGUSR1, &message_recived);
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		if (pid <= 0 || !check_if_int(av[1]))
		{
			write(2, "Pid error\n", 11);
			exit(1);
		}
		while (*av[2])
			send_bits(*av[2]++, pid);
		send_bits(*av[2]++, pid);
	}
	else
		write(2, "Aargument error\n", 22);
}
