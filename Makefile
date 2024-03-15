# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 17:29:03 by chuchard          #+#    #+#              #
#    Updated: 2024/03/15 18:59:39 by chuchard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors constants
PURPLE			= \033[38;5;141m
GREEN			= \033[38;5;46m
BLUE			= \033[38;5;111m
RED				= \033[0;31m
TRANS			= \033[38;5;240m
BOLD			= \033[1m
TRANS			= \033[2m
ITALIC			= \033[3m
RESET			= \033[0m
CLEAR			= \r\033[K
SEP				= ${TRANS}────────────────────────────────────────────────────────────────────────────\n${RESET}

# Executable and compilation
NAME			= minishell
LIBFT 			= libft.a

SRC_DIR			= ./srcs/
SRCS			= main.c

OBJ_DIR			= ./objs/
OBJS			= ${addprefix ${OBJ_DIR}, ${SRCS:.c=.o}}

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
INCLUDE			= -I include
RM				= rm -rf

ifdef DEBUG
	CFLAGS += -g -fsanitize=address
endif

# Checking OS type
UNAME_S 		= $(shell uname -s)

ifneq ($(UNAME_S),Linux)
ifneq ($(UNAME_S),Darwin)
	$(error Unsupported OS $(UNAME_S))
endif
endif

# Adding a specific flag for MacOS not Intel based
ifeq ($(UNAME_S),Darwin)
	CFLAGS += -arch x86_64
endif

${OBJ_DIR}%.o:	${SRC_DIR}%.c
	@printf "${SEP}${CLEAR}${RESET}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: Compiling ${GREEN}%s${RESET}...\n${SEP}" ${notdir $<}
	@${CC} ${CFLAGS} -I${SRC_DIR} -c $< -o $@
	@sleep 0.1
	@tput cuu 3

all:			$(NAME)
	@printf "${SEP}\
${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: ${GREEN}Welcome to my Minishell project!${RESET}\n\
${SEP}"

$(NAME): 		$(OBJS)
	@make -s -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) libft/$(LIBFT) -o $(NAME) -lreadline
	@printf "${SEP}${CLEAR}${RESET}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: Project compiled ${GREEN}successfully${RESET}.\n"
	@sleep 0.2

${OBJS}:		| ${OBJ_DIR}

${OBJ_DIR}:
	@mkdir ${OBJ_DIR}

debug:
	@make DEBUG=1 re
	@printf "${RESET}${RED}${BOLD}Compilation done with data race detection${RESET}\n"

clean:
	@for file in $(wildcard ${OBJ_DIR}*.o); do \
        printf "${SEP}${CLEAR}${RESET}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: ${RED}Clearing${RESET} %s...\n${SEP}" $${file}; \
		sleep 0.1; \
		tput cuu 3; \
        ${RM} $${file}; \
    done
	@${RM} ${OBJ_DIR}
	@printf "${SEP}${CLEAR}${RESET}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: Objects cleaned ${GREEN}successfully${RESET}.\n${RESET}${SEP}"

fclean: 		
	@make fclean -s -C libft
	@make clean -s
	@tput cuu 1
	@printf "${CLEAR}${RESET}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: ${RED}Clearing${RESET} executable...\n${SEP}"
	@${RM} ${NAME}
	@sleep 0.2
	@tput cuu 2
	@printf "${CLEAR}${RESET}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: Project cleaned ${GREEN}successfully${RESET}.\n${RESET}${SEP}"

re: 			fclean all

.SILENT: all clean fclean re debug
.PHONY: all clean fclean re debug