NAME = codexion
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
SRC = main.c parsing.c helper.c coders.c dongle.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

execute: 
	./codexion 3 60000 3000 1000 200 6 7 fifo

.PHONY: all clean fclean re execute