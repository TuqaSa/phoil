CC = cc
CFLAGS = -Wall -Wextra -Werror -I include -pthread

SRC = phiol.c captain.c init.c phiol_lifecycle.c sync_utils.c utils.c waiter.c

SRCS :=  $(addprefix src/,$(SRC))
ODIR = ofiles
OFILES := $(addprefix ofiles/,$(notdir $(SRC:.c=.o)))

NAME = philo

ofiles/%.o: src/%.c include/phiol.h | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(OFILES) -o $(NAME)

clean:
	rm -rf ofiles

fclean: clean
	rm -rf $(NAME)

re: fclean all

$(ODIR):
	mkdir -p ofiles

.PHONY: dirs all clean fclean re
