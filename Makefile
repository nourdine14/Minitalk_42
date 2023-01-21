# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/07 11:54:53 by nakebli           #+#    #+#              #
#    Updated: 2023/01/21 14:12:26 by nakebli          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER =    server
CLIENT =    client

SRCS_S = server.c 
SRCS_C	= client.c

libft = libft/libft.a


# B_SRCS = 

OBJS_S = $(SRCS_S:.c=.o)
OBJS_C = $(SRCS_C:.c=.o)

# B_OBJS = $(B_SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra

HEADER = minitalk.h

RM = rm -rf

AR = @ar -rcs

all:  $(libft) $(SERVER) $(CLIENT)

$(CLIENT):$(OBJS_C)
	$(CC) $(SRCS_C) $(libft) -o $(CLIENT)
$(SERVER):$(OBJS_S)
	$(CC) $(SRCS_S) $(libft) -o $(SERVER)

$(libft): 
	make -C ./libft


bonus : $(OBJS)
	$(AR) $(NAME) $(B_OBJS) $(OBJS)

clean:
	@$(RM) $(OBJS_C) $(OBJS_S)
	make clean -C ./libft

fclean:clean
	@$(RM) $(OBJS_C) $(OBJS_S)  $(CLIENT) $(SERVER)
	make fclean -C ./libft

re: fclean all