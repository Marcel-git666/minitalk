# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/02 10:49:09 by mmravec           #+#    #+#              #
#    Updated: 2024/10/03 12:36:38 by mmravec          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_SERVER = server
NAME_CLIENT = client
CC = cc
CFLAGS = -Wall -Werror -Wextra

# Source files for the server
SRCS_SERVER = server.c ft_printf.c ft_printf_utils.c
OBJS_SERVER = $(SRCS_SERVER:.c=.o)

# Source files for the client
SRCS_CLIENT = client.c ft_printf.c ft_printf_utils.c
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

# Path to the libft directory
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Default target to build everything (both server and client)
all: $(NAME_SERVER) $(NAME_CLIENT)  # Build both server and client

# Rule to build the final server executable
$(NAME_SERVER): $(LIBFT) $(OBJS_SERVER)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJS_SERVER) -L$(LIBFT_DIR) -lft

# Rule to build the final client executable
$(NAME_CLIENT): $(LIBFT) $(OBJS_CLIENT)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJS_CLIENT) -L$(LIBFT_DIR) -lft

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build libft by calling its Makefile
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Clean up object files
clean:
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT)
	$(MAKE) -C $(LIBFT_DIR) clean

# Clean up object files and the executables
fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything from scratch
re: fclean all

.PHONY: all clean fclean re
