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

void  handler_sigusr(int signum)
{
   static char c = 0xFF;
   static int  bits = 0;

   if (signum == SIGUSR1)
   {
      printf("0");
      c ^= 0x80 >> bits;
   }
   else if (signum == SIGUSR2)
   {
      printf("1");
      c |= 0x80 >> bits;
   }
   bits++;
   if (bits == 8)
   {
      printf("-> %c\n",c);
      bits = 0;
      c = 0xFF;
   }

}

int	main(void)
{
   pid_t	pid;

   pid = getpid();
   printf("PID: %d\n", pid);
   signal(SIGUSR1, handler_sigusr);
   signal(SIGUSR2, handler_sigusr);
   while (1)
   	pause();
}
