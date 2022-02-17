/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izail <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:05:42 by izail             #+#    #+#             */
/*   Updated: 2022/02/17 12:05:45 by izail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include<signal.h>
#include <sys/types.h>
#include <stdio.h>

void	handler_sigusr1(int signum)
{
   printf("signal %d received.\n", signum);
}

int	main(void)
{
   pid_t	pid;

   pid = getpid();
   printf("PID: %d\n", pid);
   signal(SIGUSR1, handler_sigusr1);
   while (1)
   	pause();
}
