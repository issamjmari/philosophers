SRC = philo.c ft_atoi.c philo_utils.c
# CFLAGS = -Wall -Wextra -Werror
RM = rm -f
NAME = philo

all : $(NAME)

$(NAME) :
	cc $(SRC) -o $(NAME)
fclean :
	$(RM) $(NAME)
re : fclean all