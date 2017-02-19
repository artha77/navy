/*
** map.c for map in /home/artha/signal_test
**
** Made by dylan renard
** Login   <artha@epitech.net>
**
** Started on  Sun Feb 19 08:51:07 2017 dylan renard
** Last update Sun Feb 19 10:18:02 2017 dylan renard
*/

#include "my_signal.h"
#include "gnl.h"
#include <stdlib.h>
#include <fcntl.h>
#include "my.h"

char			**map_fill(void)
{
  char			**map;
  int			i;
  int			j;

  i = 0;
  j = 0;
  if ((map = malloc(8 * sizeof(char *))) == NULL)
    return (NULL);
  while (i != 8)
    {
      if ((map[i] = malloc(8 * sizeof(char))) == NULL)
	return (NULL);
      while (j != 8)
	{
	  map[i][j] = '.';
	  j++;
	}
      j = 0;
      i++;
    }
  return (map);
}

char			**draw_on_map(t_map_info *info, char **map)
{
  int			pos1;
  int			pos2;
  int			pos3;
  int			pos4;

  pos1 = info->first[0] - 'A';
  pos2 = info->first[1] - '0' - 1;
  pos3 = info->last[0] - 'A';
  pos4 = info->last[1] - '0' - 1;
  while (pos1 != pos3 || pos2 != pos4)
    {
      if (map[pos2][pos1] != '.')
	return (NULL);
      map[pos2][pos1] = info->len[0];
      if (pos1 != pos3)
	pos1++;
      else
	pos2++;
    }
  map[pos4][pos3] = info->len[0];
  return (map);
}

void			display_map(char **map)
{
  int			i;
  int			j;

  i = 0;
  j = 0;
  my_putstr(" |A B C D E F G H\n");
  my_putstr("-+---------------\n");
  while (i != 8)
    {
      my_putchar(i + '0' + 1);
      my_putchar('|');
      while (j != 8)
	{
	  my_putchar(map[i][j]);
	  if (j != 7)
	    my_putchar(' ');
	  j++;
	}
      my_putchar('\n');
      i++;
      j = 0;
    }
}

char			**map_gen(t_map_info **info)
{
  char			**map;
  int			i;

  i = 0;
  if ((map = map_fill()) == NULL) return (NULL);
  while (i != 4)
    {
      if ((map = draw_on_map(info[i], map)) == NULL)
	  return (NULL);
      i++;
    }
  return (map);

}

char			**map_load(char *name)
{
  int			fd;
  char			*str;
  t_map_info		*info[4];
  int			count;

  count = 0;
  fd = open(name, O_RDONLY);
  if (fd == -1) return (NULL);
  while (str = get_next_line(fd))
    {
      if (count == 4) return (NULL);
      if ((info[count] = str_cut(str)) == NULL) return (NULL);
      if (verif_arg1(info[count]->len) == -1) return (NULL);
      if (verif_arg2(info[count]->first) == -1) return (NULL);
      if (verif_arg2(info[count]->last) == -1) return (NULL);
      if (verif_len(info[count]) == -1) return (NULL);
      count++;
    }
  if (same_len(info[0]->len, info[1]->len, info[2]->len, info[3]->len) == -1)
    return (NULL);
  close(fd);
  return (map_gen(info));
}
