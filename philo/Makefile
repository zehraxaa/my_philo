NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c utils.c monitor.c philos.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) 
	@echo "✅ $(NAME) compiled"

clean:
	@rm -f $(OBJ)
	@echo "🧹 bye bye object files"

fclean:
	@rm -rf $(OBJ)
	@rm -f $(NAME)
	@echo "🧼 fully cleaned up"

re: fclean all

.PHONY: all clean fclean re 