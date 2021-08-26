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
