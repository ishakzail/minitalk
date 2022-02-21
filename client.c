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

void  send_message(char *message, int pid)
{
   int   i;
   int   shift;

   shift = -1;
   i = 0;
   while (message[i])
   {
      while (++shift < 8)
      {
         if (message[i] & (0x80 >> shift))
         {
               if (kill(pid, SIGUSR2) == -1)
                  exit(-1);
         }
         else
         {
               if (kill(pid, SIGUSR1) == -1)
                  exit(-1);
         }
         usleep(50);
      }
      i++;
   }
}

int	main(int argc, char *argv[])
{
   int		pid;

   if (argc != 3)
   {
   	printf("client: invalid arguments\n");
   	printf("\tcorrect format [./%s SERVER_PID MESSAGE\n]", argv[0]);
   	exit(EXIT_FAILURE);
   }
   pid = atoi(argv[1]);
   send_message(argv[2], pid);
   return (0);
}