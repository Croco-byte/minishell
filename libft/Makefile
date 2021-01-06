# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/19 15:27:24 by user42            #+#    #+#              #
#    Updated: 2021/01/06 12:15:36 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = clang

CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3 -fno-omit-frame-pointer -I includes/

HEADERS = libft.h get_next_line.h ft_printf.h

FTGNL = get_next_line get_next_line_utils
FTIS = alnum alpha ascii digit print space instr
FTLST = add_back add_front clear delone iter last map new size
FTMEM = ccpy chr cmp cpy move set
FTPRINTF = flag_parse ft_itoa_dot ft_printf ft_ptr_itoa_dot ft_un_itoa_base_dot ft_un_itoa_dot handle_char handle_int handle_p handle_percent handle_str handle_u handle_x utilities utilities2
FTPUT = char endl nbr str
FTSTR = split strchr strdup strjoin strlcat strlcpy strlen strmapi strncmp strcmp strncpy strnstr strrchr strtrim substr
FTTO = atoi itoa tolower toupper

SRCS = 	$(addsuffix .c, $(addprefix ft_gnl/, $(FTGNL))) \
		$(addsuffix .c, $(addprefix ft_is/ft_is, $(FTIS))) \
		$(addsuffix .c, $(addprefix ft_lst/ft_lst, $(FTLST))) \
		$(addsuffix .c, $(addprefix ft_mem/ft_mem, $(FTMEM))) \
		$(addsuffix .c, $(addprefix ft_printf/, $(FTPRINTF))) \
		$(addsuffix _fd.c, $(addprefix ft_put/ft_put, $(FTPUT))) \
		$(addsuffix .c, $(addprefix ft_str/ft_, $(FTSTR))) \
		$(addsuffix .c, $(addprefix ft_to/ft_, $(FTTO)))

OBJS = ${SRCS:.c=.o}

all:	$(NAME)

$(NAME):	$(OBJS)
				@echo "\n\n\033[0;32mCompiling libft..."
				@ar rc $(NAME) $^
				@ranlib $(NAME)
				@echo "\033[0m"

%.o:%.c
				@echo "Generating libft object" $@
				@${CC} ${CFLAGS} -c $< -o $@

clean:
				@rm -f $(OBJS)

fclean:		clean
				@rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
