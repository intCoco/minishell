# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 17:29:03 by chuchard          #+#    #+#              #
#    Updated: 2024/03/16 13:38:07 by chuchard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors constants
PURPLE			= \033[38;5;141m
ORANGE			= \033[38;5;214m
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
SEP2			= ${TRANS}════════════════════════════════════════════════════════════════════════════\n${RESET}

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
	@printf "${SEP2}\
${GREEN}»${RESET} [${ORANGE}${BOLD}Makefile${RESET}]: ${GREEN}Welcome to our Minishell project!${RESET}\n\n\
${ITALIC}${TRANS}Authors: npaolin & chuchard${RESET}\n\
${SEP2}"

$(NAME): 		$(OBJS)
	@printf "${SEP2}${CLEAR}${RESET}${GREEN}»${RESET} [${ORANGE}${BOLD}Makefile${RESET}]: ${BOLD}Compilation${RESET}...					 	 ${BOLD}[${RED}✘${RESET}]\n"
	@make -s -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) libft/$(LIBFT) -o $(NAME) -lreadline
	@printf "${SEP}${CLEAR}${RESET}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: Project ${GREEN}compiled${RESET} successfully.			 	 ${BOLD}[${GREEN}✔${RESET}]\n${SEP2}"
	@sleep 0.2
	@tput cuu 6
	@printf "									 ${BOLD}[${GREEN}✔${RESET}]\n${SEP}"
	@tput cud 6

${OBJS}:		| ${OBJ_DIR}

${OBJ_DIR}:
	@mkdir ${OBJ_DIR}

debug:
	@make DEBUG=1 re
	@printf "${RESET}${RED}${BOLD}Compilation done with memory leaks detection${RESET}\n"

clean:
ifeq ($(wildcard objs), objs)
	@printf "${SEP2}${CLEAR}${RESET}${GREEN}»${RESET} [${ORANGE}${BOLD}Makefile${RESET}]: ${BOLD}Removal${RESET}...					 	 ${BOLD}[${RED}✘${RESET}]\n"
	@make clean -s -C libft
	@tput cuu 1
	@for file in $(wildcard ${OBJ_DIR}*.o); do \
		printf "${SEP}${CLEAR}${RESET}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: ${RED}Cleaning${RESET} %s..." $${file}; \
		tput cr; \
		printf "									 ${BOLD}[${RED}✘${RESET}]\n${SEP}"; \
		sleep 0.1; \
		tput cuu 3; \
		${RM} $${file}; \
	done
	@${RM} ${OBJ_DIR}
	@printf "${SEP}${CLEAR}${RESET}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: Objects ${GREEN}cleaned${RESET} successfully.			 	 ${BOLD}[${GREEN}✔${RESET}]\n${RESET}${SEP2}"
	@tput cuu 6
	@printf "									 ${BOLD}[${GREEN}✔${RESET}]\n${SEP}"
	@tput cud 6
else
	@printf "${SEP2}${CLEAR}${RESET}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: Objects ${GREEN}has already been cleaned${RESET}.			 ${BOLD}[${GREEN}✔${RESET}]\n${RESET}${SEP2}"
endif

fclean:
ifeq (,$(or $(wildcard minishell),$(wildcard objs)))
	@printf "${SEP2}${GREEN}»${RESET} [${ORANGE}${BOLD}Makefile${RESET}]: Everything has ${GREEN}already been cleaned${RESET}.			 ${BOLD}[${GREEN}✔${RESET}]\n${RESET}${SEP2}"
else
	@printf "${SEP2}${CLEAR}${RESET}${GREEN}»${RESET} [${ORANGE}${BOLD}Makefile${RESET}]: ${BOLD}Removal${RESET}...					 	 ${BOLD}[${RED}✘${RESET}]\n"
	@make fclean -s -C libft
	@tput cuu 1
	@for file in $(wildcard ${OBJ_DIR}*.o); do \
		printf "${SEP}${CLEAR}${RESET}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: ${RED}Cleaning${RESET} %s..." $${file}; \
		tput cr; \
		printf "									 ${BOLD}[${RED}✘${RESET}]\n${SEP}"; \
		sleep 0.1; \
		tput cuu 3; \
		${RM} $${file}; \
	done
	@${RM} ${OBJ_DIR}
	@printf "${SEP}${CLEAR}${RESET}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: Objects ${GREEN}cleaned${RESET} successfully.			 	 ${BOLD}[${GREEN}✔${RESET}]\n${RESET}"
	@tput cuu 2
ifeq ($(wildcard minishell), minishell)
	@printf "${SEP}${CLEAR}${RESET}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: ${RED}Cleaning${RESET} executable...					 ${BOLD}[${RED}✘${RESET}]\n${SEP}"
	@${RM} ${NAME}
	@sleep 0.2
	@tput cuu 2
	@printf "${CLEAR}${RESET}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: Project ${GREEN}cleaned${RESET} successfully.			 	 ${BOLD}[${GREEN}✔${RESET}]\n${RESET}${SEP2}"
else
	@printf "${SEP}${CLEAR}${RESET}${GREEN}»${RESET} [${BLUE}${BOLD}${NAME}${RESET}]: Executable ${GREEN}has already been cleaned${RESET}.			 ${BOLD}[${GREEN}✔${RESET}]\n${RESET}${SEP2}"
endif
	@tput cuu 6
	@printf "									 ${BOLD}[${GREEN}✔${RESET}]\n${SEP}"
	@tput cud 6
endif

re: 			fclean all

.SILENT: all clean fclean re debug
.PHONY: all clean fclean re debug