SRC = philo.c li/ft_atoi.c
# CFLAGS = -Wall -Wextra -Werror
RM = rm -f
NAME = philo

all : $(NAME)

$(NAME) :
	cc $(SRC) -fsanitize=address -o $(NAME)
fclean :
	$(RM) $(NAME)
re : fclean all