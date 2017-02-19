/*
** map_verif.c for navy in /home/artha/signal_test
**
** Made by dylan renard
** Login   <artha@epitech.net>
**
** Started on  Sun Feb 19 08:57:04 2017 dylan renard
** Last update Sun Feb 19 09:01:47 2017 dylan renard
*/

#include "my_signal.h"
#include "gnl.h"
#include <stdlib.h>
#include <fcntl.h>
#include "my.h"

int			verif_arg1(char *len)
{
  if (len == NULL) return (-1);
  if (my_strlen(len) != 1) return (-1);
  if (!(len[0] >= '2' && len[0] <= '5')) return (-1);
  return (0);
}

int			verif_arg2(char *pos)
{
  if (pos == NULL) return (-1);
  if (my_strlen(pos) != 2) return (-1);
  if (!(pos[0] >= 'A' && pos[0] <= 'H')) return (-1);
  if (!(pos[1] >= '0' && pos[1] <= '8')) return (-1);
  return (0);
}

int			calc_pos_len(char *s1, char *s2)
{
  if (s1[0] == s2[0])
    {
      return (((s1[1] - s2[1]) <= 0) ? (s1[1] - s2[1]) * -1 : (s1[1] - s2[1]));
    }
  else if (s1[1] == s2[1])
    {
      return (((s1[0] - s2[0]) <= 0) ? (s1[0] - s2[0]) * -1 : (s1[0] - s2[0]));
    }
  else
    return (-1);
}

int			verif_len(t_map_info *info)
{
  int			len;
  int			len_pos;

  len = (int)(info->len[0] - '0');
  if ((len_pos = calc_pos_len(info->first, info->last)) == -1)
    return (-1);
  if (len != len_pos + 1)
    return (-1);
  return (0);
}

int			same_len(char *len1, char *len2, char *len3, char *len4)
{
  char			*str;
  int			i;
  int			j;
  int			find;

  i = 2;
  j = 0;
  find = 0;
  str = my_strcat(len1, len2);
  str = my_strcat(str, len3);
  str = my_strcat(str, len4);
  while (i != 6)
    {
      while (str[j] != '\0')
	{
	  if ((str[j] - '0') == i)
	    find++;
	  if (find > 1) return (-1);
	  j++;
	}
      i++;
      j = 0;
      find = 0;
    }
  return (0);
}
