/*
** touch.c for navy in /home/artha/signal_test
**
** Made by dylan renard
** Login   <artha@epitech.net>
**
** Started on  Sun Feb 19 09:38:23 2017 dylan renard
** Last update Sun Feb 19 09:42:18 2017 dylan renard
*/

#include "my_signal.h"
#include "gnl.h"
#include <stdlib.h>
#include <fcntl.h>
#include "my.h"

void			istouch_handle(int signo, siginfo_t *sa, void *context)
{
  return ;
}

int			is_touch(char **map, char *pos)
{
  struct sigaction	sig;

  sig.sa_sigaction = istouch_handle;
  sig.sa_flags = SA_SIGINFO;
  if (sigaction(SIGUSR1, &sig, NULL) == -1) return (84);
  if (sigaction(SIGUSR2, &sig, NULL) == -1) return (84);
  if (map[pos[1] - '0'][pos[0] - 'A'] >= '0'
      && map[pos[1] - '0'][pos[0] - 'A'] <= '9')
    {
      kill(verif_pid(0, 1), SIGUSR2);
      while (pause() != -1);
      return (make_cross(pos, map), 1);
    }
  kill(verif_pid(0, 1), SIGUSR1);
  while (pause() != -1);
  return (0);
}

int			stat_touch(char *mode, int touch)
{
  static int		ltouch = 0;

  if (my_strcmp(mode, "set") == 0)
    {
      ltouch = touch;
      return (0);
    }
  else if (my_strcmp(mode, "get") == 0)
    {
      return (ltouch);
    }
}

void			touch_handle(int signo, siginfo_t *sa, void *context)
{
  if (signo == SIGUSR1)
    {
      my_puts("missed");
      stat_touch("set", 0);
    }
  else if (signo == SIGUSR2)
    {
      stat_touch("set", 1);
      my_puts("hit");
    }
}

int			have_touch(char **enemy_map)
{
  struct sigaction	sig;

  sig.sa_sigaction = touch_handle;
  sig.sa_flags = SA_SIGINFO;
  if (sigaction(SIGUSR1, &sig, NULL) == -1) return (84);
  if (sigaction(SIGUSR2, &sig, NULL) == -1) return (84);
  kill(verif_pid(0, 1), SIGUSR1);
  usleep(1000);
  return (stat_touch("get", 0));
}