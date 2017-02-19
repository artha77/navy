##
## Makefile for my_printf in /home/artha/printf
## 
## Made by dylan renard
## Login   <artha@epitech.net>
## 
## Started on  Mon Nov  7 15:05:57 2016 dylan renard
## Last update Sun Feb 19 09:48:55 2017 dylan renard
##

CC	= 	gcc

RM	= 	rm -f

NAME	= 	navy

SRCS	=	src/touch.c	\
		src/gameplay.c	\
		src/packet.c	\
		src/signal.c	\
		src/convert.c	\
		src/player.c	\
		src/start.c	\
		src/utils.c	\
		src/map_verif.c	\
		src/map.c	\
		src/main.c	\

OBJS	= 	$(SRCS:.c=.o)

CFLAGS	+=	#-W -Wall -Werror -pedantic

CFLAGS	+=	-I./include/

LDFLAGS +=	-L./lib -lmy -lgnl

all: libmy $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) $(CFLAFS) $(LDFLAGS) -lncurses

libmy:
	@$(MAKE) -C lib/my

clean:
	@$(RM) $(OBJS)
	@$(MAKE) clean -C lib/my

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean, re, all, fclean
