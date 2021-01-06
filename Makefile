# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/05 15:18:35 by user42            #+#    #+#              #
#    Updated: 2021/01/06 16:20:37 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = clang

CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3 -fno-omit-frame-pointer -I includes/ -I libft/includes/

LIBFT = -L libft -lft

HEADER = minishell.h

MAIN = minishell
BUILTINS = pwd cd echo
EXEC = bin builtin exec
PARSING = parse
UTILS = utilities free

SRCS =	$(addsuffix .c, $(addprefix srcs/main/, $(MAIN))) \
		$(addsuffix .c, $(addprefix srcs/builtins/, $(BUILTINS))) \
		$(addsuffix .c, $(addprefix srcs/parsing/, $(PARSING))) \
		$(addsuffix .c, $(addprefix srcs/exec/, $(EXEC))) \
		$(addsuffix .c, $(addprefix srcs/utils/, $(UTILS)))

OBJS = ${SRCS:.c=.o}

all:		$(NAME)

$(NAME):	$(OBJS)
			@make -C libft/
			@echo "\033[0;32mCompiling minishell..."
			@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
			@echo "\n\033[0mDone !"

%.o:%.c
				@echo "Generating minishell object" $@
				@${CC} ${CFLAGS} -c $< -o $@

clean:
				@echo "\033[0;31mCleaning libft..."
				@make clean -C libft
				@echo "\033[0;31mCleaning minishell objs..."
				@rm -f $(OBJS)
				@echo "\033[0m"

fclean:
				@echo "\033[0;31mCleaning libft..."
				@make fclean -C libft
				@echo "\033[0;31mCleaning minishell objs..."
				@rm -f $(OBJS)
				@echo "\033[0;31mCleaning minishell program..."
				@rm -f $(NAME)
				@echo "\033[0m"

re:				fclean all

.PHONY:			all clean fclean re




