# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: salegari <salegari@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/29 19:00:46 by salegari          #+#    #+#              #
#    Updated: 2026/09/29 19:46:12 by salegari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ARFLAGS = -rcs

RM = rm -f

CC = gcc

CCFLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

SRC =	ft_intpchar.c \
		ft_intpstr.c \
		ft_intputnbr.c \
		ft_printf.c \
		ft_putnbr_base.c \
		ft_putnbr_unsg.c \
		ft_putptr.c \
		utils.c

OBJ = $(SRC:.c=.o)

INCLUDE = ft_printf.h

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $<
clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
