/*
** gameplay.c for navy in /home/artha/signal_test
**
** Made by dylan renard
** Login   <artha@epitech.net>
**
** Started on  Sun Feb 19 09:33:10 2017 dylan renard
** Last update Sun Feb 19 13:57:23 2017 dylan renard
*/

#include "my_signal.h"
#include "gnl.h"
#include <stdlib.h>
#include <fcntl.h>
#include "my.h"

int			is_victory(int touch, int touched)
{
  static int		ss_touch = 0;
  static int		ss_touched = 0;

  if (touch && ss_touched != 14)
    ss_touch++;
  else if (touched && ss_touch != 14)
    ss_touched++;
  if (ss_touch == 14)
    return (0);
  else if (ss_touched == 14)
    return (1);
  else
    return (-1);
}

void			game_handle(int signo, siginfo_t *info, void *context)
{
  if (verif_pid(info->si_pid, 0))
    {
      if (signo == SIGUSR1)
	packet_manage("add", 0);
      else if (signo == SIGUSR2)
	packet_manage("add", 1);
    }
  usleep(1000);
  kill(info->si_pid, SIGUSR1);
}

int			send(char **enemy_map, char **map)
{
  int			pid;
  char			*str;
  int			touch;

  pid = verif_pid(0, 1);
  display_info(enemy_map, map);
  my_putstr("\nattack: ");
  while (str = get_next_line(0))
    {
      if (my_strlen(str) == 2 && verif_arg2(str) != -1)
	{
	  signal_send(pid, str);
	  my_putstr(my_strcat(str, ": "));
	  touch = have_touch(enemy_map);
	  if (touch == 1) make_cross(str, enemy_map);
	  else make_round(str, enemy_map);
	  if (is_victory(0, touch) != -1)
	    return (0);
	  usleep(1000);
	  return (0);
	}
      else my_putstr("wrong position");
      my_putstr("\nattack: ");
    }
}

int			miss_or_touch(char **map, char *pos)
{
  int			touch;

  touch = is_touch(map, pos);
  if (touch == 1)
    my_puts(my_strcat(pos, ": hit\n"));
  else if (touch == 0)
    {
      make_round(pos, map);
      my_puts(my_strcat(pos, ": missed\n"));
    }
  is_victory(touch, 0);
  return (touch);
}

int			wait_player(char **enemy_map, char ** map)
{
  struct sigaction	sig;
  char			pos[2];
  int			i;
  int			touch;

  i = 0;
  touch = 0;
  pos[2] = '\0';
  sig.sa_sigaction = game_handle;
  sig.sa_flags = SA_SIGINFO;
  if (sigaction(SIGUSR1, &sig, NULL) == -1) return (84);
  if (sigaction(SIGUSR2, &sig, NULL) == -1) return (84);
  while (i != 2)
    {
      while (pause() != -1);
      if (packet_manage("conv", 1) != '\0')
	{
	  pos[i] = packet_manage("conv", 1);
	  i++;
	}
    }
  touch = miss_or_touch(map, pos);
  kill(verif_pid(0, 1), (touch == 0) ? SIGUSR1 : SIGUSR2);
  usleep(1000);
  return (is_victory(0, 0));
}
