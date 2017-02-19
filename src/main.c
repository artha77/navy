/*
** main.c for signal in /home/artha/signal_test/src
**
** Made by dylan renard
** Login   <artha@epitech.net>
**
** Started on  Fri Feb 10 11:24:49 2017 dylan renard
** Last update Sun Feb 19 18:36:23 2017 dylan renard
*/

#include "my_signal.h"
#include "gnl.h"
#include <stdlib.h>
#include <fcntl.h>
#include "my.h"

void			display_info(char **enemy_map, char **map)
{
  my_puts("my positions:");
  display_map(map);
  my_putchar('\n');
  my_puts("enemy's positions:");
  display_map(enemy_map);
}

void			show_manual(void)
{
  my_puts("USAGE");
  my_puts("\t\t./navy [frist_player_pid] navy_positions\n");
  my_puts("DESCRIPTION");
  my_putstr("\t\tfrist_player_pid\tonly for the second player. ");
  my_puts("pid of the first player.");
  my_puts("\t\tnavy_positions\t\tfile representing the positions of ship.");
}

int			main(int ac, char **av)
{
  int			ret;

  if (ac == 2 && my_strcmp(av[1], "-h") != 0)
    {
      if ((ret = sig_start_wait(av[1])) == 84)
	return (84);
      return (ret);
    }
  else if (ac == 3)
    {
      if (is_num(av[1]) == -1)
	return (84);
      else if ((ret = sig_start(my_atoi(av[1]), av[2])) == 84)
	return (84);
      return (ret);
    }
  else if (ac == 2 && my_strcmp(av[1], "-h") == 0)
    show_manual();
  return (0);
}
