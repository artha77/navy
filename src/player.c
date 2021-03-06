/*
** player.c for navy in /home/artha/signal_test
**
** Made by dylan renard
** Login   <artha@epitech.net>
**
** Started on  Sun Feb 19 09:16:31 2017 dylan renard
** Last update Sun Feb 19 13:59:03 2017 dylan renard
*/

#include "my_signal.h"
#include "gnl.h"
#include <stdlib.h>
#include <fcntl.h>
#include "my.h"

int			player1_start(char **map)
{
  char			**enemy_map;
  int			victory;

  if ((enemy_map = map_fill()) == NULL)
    return (84);
  victory = -1;
  while (victory == -1)
    {
      send(enemy_map, map);
      if ((victory = is_victory(0, 0)) == -1)
	{
	  my_puts("\nwaiting for enemy's attack...");
	  victory = wait_player(enemy_map, map);
	}
    }
  if (victory)
    {
      my_putchar('\n');
      display_info(enemy_map, map);
      my_putstr("\nI won");
      return (0);
    }
  display_info(enemy_map, map);
  my_putstr("\nEnemy won");
  return (1);
}

int			player2_start(char **map)
{
  char			**enemy_map;
  int			victory;

  if ((enemy_map = map_fill()) == NULL) return (84);
  victory = -1;
  display_info(enemy_map, map);
  while (victory == -1)
    {
      if ((victory = is_victory(0, 0)) == -1)
	{
	  my_puts("\nwaiting for enemy's attack...");
	  victory = wait_player(enemy_map, map);
	  if (victory == -1)
	    send(enemy_map, map);
	}
    }
  if (victory)
    {
      my_putchar('\n');
      display_info(enemy_map, map);
      return (my_putstr("\nI won"), 0);
    }
  display_info(enemy_map, map);
  return (my_putstr("\nEnemy won"), 1);
}
