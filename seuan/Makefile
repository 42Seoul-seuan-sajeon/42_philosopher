# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seuan <seuan@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/26 19:22:40 by seuan             #+#    #+#              #
#    Updated: 2021/08/26 19:22:48 by seuan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET = philo

CC		= gcc $(CFLAGS)

CFLAGS	= -Wall -Wextra -Werror

SRCS = main.c \
		create.c \
		print.c \
		util.c \
		philosopher.c \
		monitor.c \
		free.c \
		error.c \

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(OBJS) -I philo.h -o $(TARGET)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
