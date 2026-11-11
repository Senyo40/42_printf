NAME	= libft.a
SRCS	= ft_putnbr.c

OBJS	= $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

AR = ar rcs $(NAME)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
