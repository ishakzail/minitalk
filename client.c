/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izail <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:05:51 by izail             #+#    #+#             */
/*   Updated: 2022/02/17 12:05:52 by izail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
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

int    check_if_int(char *str)
{
    int i;

    i = 0;
    if (str[i] == '+' || str[i] == '-')
            i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

void	signal_recived(int sig)
{
	if (sig == SIGUSR1)
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
		//printf("send == %d\n", send);
		if (send)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(10000);
	}
}

int	main(int ac, char **av)
{
	int	pid;

	signal(SIGUSR1, &signal_recived);
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		if (!check_if_int(av[1]))
		{
			write(2, "Error pid must be a digit\n",27);
			exit(1);
		}
		while (*av[2])
			send_bits(*av[2]++, pid);
		send_bits(*av[2]++, pid);
	}
	else
		write(2, "Error\n\targument error\n", 22);
}
