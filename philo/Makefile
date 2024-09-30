NAME =			philo

CC =			gcc

CFLAGS =		-Wall -Werror -Wextra

SRC_FILES =		main.c \
				init_and_threads.c \
				monitoring_rutines.c \
				utils.c \
				utils2.c \
				philo_rutines.c 


OBJS = $(SRC_FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
