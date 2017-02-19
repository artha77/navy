/*
** utils.c for navy in /home/artha/signal_test
**
** Made by dylan renard
** Login   <artha@epitech.net>
**
** Started on  Sun Feb 19 09:01:58 2017 dylan renard
** Last update Sun Feb 19 10:20:59 2017 dylan renard
*/

#include "my_signal.h"
#include "gnl.h"
#include <stdlib.h>
#include <fcntl.h>
#include "my.h"

t_map_info		*str_cut(char *str)
{
  int			i;
  t_map_info		*info;
  int			phase;

  i = 0;
  phase = 0;
  if (str == NULL) return (NULL);
  if ((info = malloc(sizeof(t_map_info))) == NULL) return (NULL);
  while (1)
    {
      if (str[i] == ':' || str[i] == '\0')
	{
	  phase++;
	  if (phase == 4) return (NULL);
	  else if (phase == 1) info->len = my_strndup(str, i);
	  else if (phase == 2) info->first = my_strndup(str, i);
	  else if (phase == 3) info->last = my_strndup(str, i);
	  if (str[i] == '\0')
	    return ((phase == 3) ? info : NULL);
	  str += i + 1;
	  i = 0;
	}
      else i++;
    }
}

int			is_num(char *str)
{
  int			i;

  i = 0;
  while (str[i] != '\0')
    {
      if (!(str[i] >= '0' && str[i] <= '9'))
	return (-1);
      i++;
    }
  return (0);
}

void			make_cross(char *pos, char **map)
{
  map[pos[1] - '0' - 1][pos[0] - 'A'] = 'x';
}

void			make_round(char *pos, char **map)
{
  map[pos[1] - '0' - 1][pos[0] - 'A'] = 'o';
}
