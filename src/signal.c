/*
** signal.c for navy in /home/artha/signal_test
**
** Made by dylan renard
** Login   <artha@epitech.net>
**
** Started on  Sun Feb 19 09:21:41 2017 dylan renard
** Last update Sun Feb 19 09:24:42 2017 dylan renard
*/

#include "my_signal.h"
#include "gnl.h"
#include <stdlib.h>
#include <fcntl.h>
#include "my.h"

int			verif_pid(int pid, int mode)
{
  static int		app_pid = -1;

  if (mode == 0)
    {
      if (app_pid == -1)
	app_pid = pid;
      else if (app_pid == pid)
	return (1);
      else
	return (0);
    }
  else if (mode == 1)
    return (app_pid);
}

void			ping_handle(int signo, siginfo_t *info, void *context)
{
  if (signo == SIGUSR1 || signo == SIGUSR2)
    return ;
}

int			send_bit_to_pid(int pid, char *bit)
{
  struct sigaction	sig;
  int			i;

  i = 0;
  sig.sa_sigaction = ping_handle;
  sig.sa_flags = SA_SIGINFO;
  if (sigaction(SIGUSR1, &sig, NULL) == -1) return (84);
  if (sigaction(SIGUSR2, &sig, NULL) == -1) return (84);
  while (bit[i] != 2)
    {
      if (bit[i] == 0)
	kill(pid, SIGUSR1);
      else
	kill(pid, SIGUSR2);
      while (pause() != -1);
      i++;
    }
  return (1);
}

int			signal_send(int pid, char *str)
{
  int			i;
  char			*bit;

  i = 0;
  while (str[i] != '\0')
    {
      bit = char_to_bit(str[i]);
      if (send_bit_to_pid(pid, bit) == 84)
	return (84);
      i++;
    }
  return (1);
}
