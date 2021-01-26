# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/05 15:18:35 by user42            #+#    #+#              #
#    Updated: 2021/01/26 16:48:50 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = clang

CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3 -fno-omit-frame-pointer -I includes/ -I libft/includes/

LIBFT = -L libft -lft

HEADER = minishell.h

MAIN = minishell signal redir
BUILTINS = pwd cd echo env export unset exit
EXEC = bin builtin exec
PARSING = line tokens expansion
UTILS = utilities free parser token type init fd expansion_tools
ENV = init utilities shlvl

SRCS =	$(addsuffix .c, $(addprefix srcs/main/, $(MAIN))) \
		$(addsuffix .c, $(addprefix srcs/builtins/, $(BUILTINS))) \
		$(addsuffix .c, $(addprefix srcs/parsing/, $(PARSING))) \
		$(addsuffix .c, $(addprefix srcs/exec/, $(EXEC))) \
		$(addsuffix .c, $(addprefix srcs/utils/, $(UTILS))) \
		$(addsuffix .c, $(addprefix srcs/env/, $(ENV))) \
		$(addsuffix .c, $(addprefix srcs/bonus/, $(BONUS)))

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




