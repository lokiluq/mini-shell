# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbaey <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/13 12:01:00 by cbaey             #+#    #+#              #
#    Updated: 2024/10/04 15:46:38 by lnul-hak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell
SRCS =	srcs/parsing/env_word_checking.c \
	srcs/parsing/command.c  \
	srcs/parsing/syntax_checking.c \
	srcs/parsing/env_word_checking_utils.c \
	srcs/parsing/parsing.c \
	srcs/parsing/flattening.c \
	srcs/execution/cd.c \
	srcs/execution/open_fd.c \
	srcs/execution/output_builtins.c \
	srcs/execution/heredoc.c \
	srcs/execution/processes.c \
	srcs/execution/exit.c \
	srcs/execution/exportunset.c \
	srcs/execution/find_built_ins.c \
	srcs/execution/redirections.c \
	srcs/execution/find_command_path.c \
	srcs/execution/generate_args.c \
	srcs/execution/exec.c \
	srcs/utils/init_env_list.c \
	srcs/utils/init_main_list.c \
	srcs/utils/init_word_list.c \
	srcs/utils/free.c \
	srcs/main.c 
OBJSDIR = object_files
OBJS = $(addprefix $(OBJSDIR)/,$(notdir $(SRCS:.c=.o)))
CC = cc -g
CFLAGS = -Wall -Wextra -Werror -Iinc -I$(LIBFT_DIR)
LIBFT_DIR = inc/libft
LIBFT = $(LIBFT_DIR)/libft.a
VPATH = $(dir $(SRCS))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -L$(LIBFT_DIR) $(OBJS) -o $(NAME) -lreadline -lft

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJSDIR)/%.o:%.c
	@mkdir -p $(OBJSDIR)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJSDIR)
	make -C$(LIBFT_DIR) clean

fclean : clean
	rm -f $(NAME)
	make -C$(LIBFT_DIR) fclean

re : fclean all

.PHONY : all clean fclean re
