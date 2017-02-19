/*
** convert.c for navy in /home/artha/signal_test
**
** Made by dylan renard
** Login   <artha@epitech.net>
**
** Started on  Sun Feb 19 09:18:27 2017 dylan renard
** Last update Sun Feb 19 09:19:14 2017 dylan renard
*/

#include "my_signal.h"
#include "gnl.h"
#include <stdlib.h>
#include <fcntl.h>
#include "my.h"

int		packet_convert(char *type, char *lpacket)
{
  int			i;
  int			dec;

  i = 1;
  dec = 0;
  while (i != (8))
    {
      dec = (dec << 1) | lpacket[i];
      i++;
    }
  if (!(my_strcmp(type, "int") == 0))
    {
      if (my_strcmp(type, "char") == 0)
	return (dec = (dec > 255) ? 42 : dec);
      else
	return (-1);
    }
  return ((dec = (lpacket[0] == 1) ? dec * -1 : dec));
}

char		*char_to_bit(char c)
{
  char		*bit;
  int		len;
  int		i;

  bit = malloc(9 * sizeof(char));
  len = 7;
  i = len;
  while (i >= 0)
    {
      bit[len - i] = (c >> i) & 1;
      i--;
    }
  bit[len + 1] = 2;
  return (bit);
}
