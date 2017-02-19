/*
** start.c for navy in /home/artha/signal_test
**
** Made by dylan renard
** Login   <artha@epitech.net>
**
** Started on  Sun Feb 19 09:09:28 2017 dylan renard
** Last update Sun Feb 19 10:07:52 2017 dylan renard
*/

#include "my_signal.h"
#include "gnl.h"
#include <stdlib.h>
#include <fcntl.h>
#include "my.h"

void			start_handle(int signo, siginfo_t *info, void *context)
{
  verif_pid(info->si_pid, 0);
  usleep(1000);
  kill(info->si_pid, SIGUSR1);
}

void			sig_connect(int sig, siginfo_t *info, void *context)
{
  verif_pid(info->si_pid, 0);
}

int			sig_start_wait(char *map_name)
{
  struct sigaction	sig;
  char			**map;
  int			ret;

  if ((map = map_load(map_name)) == NULL)
    return (84);
  sig.sa_sigaction = start_handle;
  sig.sa_flags = SA_SIGINFO;
  my_puts(my_strcat("my_pid: ", to_string(getpid())));
  my_puts("waiting for enemy connexion...");
  if (sigaction(SIGUSR1, &sig, NULL) == -1)
    return (84);
  while (pause() != -1);
  my_puts("enemy connected\n");
  if ((ret = player1_start(map)) == 84)
    return (84);
  return (ret);
}

int			sig_start(int pid, char *map_name)
{
  struct sigaction	sig;
  char			**map;
  int			ret;

  if ((map = map_load(map_name)) == NULL)
    return (84);
  sig.sa_sigaction = sig_connect;
  sig.sa_flags = SA_SIGINFO;
  if (sigaction(SIGUSR1, &sig, NULL) == -1)
    return (84);
  my_puts(my_strcat("my_pid: ", to_string(getpid())));
  usleep(1000);
  kill(pid, SIGUSR1);
  while (pause() != -1);
  my_puts("successfully connected");
  if ((ret = player2_start(map)) == 84) return (84);
  return (ret);
}
