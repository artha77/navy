/*
** packet.c for navy in /home/artha/signal_test
**
** Made by dylan renard
** Login   <artha@epitech.net>
**
** Started on  Sun Feb 19 09:26:05 2017 dylan renard
** Last update Sun Feb 19 09:26:39 2017 dylan renard
*/

#include "my_signal.h"
#include "gnl.h"
#include <stdlib.h>
#include <fcntl.h>
#include "my.h"

char			*packet_fill(void)
{
  char			*packet;
  int			i;

  i = 0;
  if ((packet = malloc(8 * sizeof(char))) == NULL)
    return (NULL);
  while (i != 8)
  {
    packet[i] == 0;
    i++;
  }
  return (packet);
}

char			packet_manage(char *mode, int num)
{
  static char		*packet = NULL;
  static int		pos = 0;

  if (packet == NULL)
    packet = packet_fill();
  if (my_strcmp(mode, "conv") == 0)
    {
      if (pos == 8)
	return (packet_convert("char", packet));
      else
	return ('\0');
    }
  else if (my_strcmp(mode, "add") == 0)
    {
      if (pos == 8)
	pos = 0;
      packet[pos] = num;
      pos++;
    }
}
