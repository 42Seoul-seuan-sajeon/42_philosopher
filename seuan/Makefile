TARGET = philo

CC		= gcc $(CFLAGS)

CFLAGS	= -Wall -Wextra -Werror

SRCS = init.c \
		main.c \
		print.c \
		util.c \
		philosopher.c \
		monitor.c \

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(OBJS) -I philo.h -o $(TARGET)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all

test_case1: 
			./$(TARGET) 5 800 200 200

test_case2: 
			./$(TARGET) 4 310 200 100

test_case3: 
			./$(TARGET) 4 410 200 200

.PHONY: all clean fclean re