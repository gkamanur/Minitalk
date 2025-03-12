# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/12 15:03:25 by gkamanur          #+#    #+#              #
#    Updated: 2025/03/12 15:24:39 by gkamanur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERV = server
CL   = client

CC = cc

CFLAGS = -Werror -Wall -Wextra -fsanitize=address

RM = rm -rf

SRCS_SER = server_pgm.c
SRCS_CL  = client_pgm.c
SRCS 	= signal_utils.c signal.c

HDR = minitalk.h

$(SERV) : $(HDR)
	cc $(CFLAGS) $(SRCS) $(SRCS_SER) -o $(SERV)
	
$(CL) : $(HDR)
	cc $(CFLAGS) $(SRCS) $(SRCS_CL) -o $(CL)

all : $(SERV) $(CL)

clean :
	$(RM) *.o
	
fclean: clean
	$(RM) $(SERV) $(CL)



re : fclean all
