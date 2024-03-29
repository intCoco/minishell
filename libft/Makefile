# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/16 15:10:19 by chuchard          #+#    #+#              #
#    Updated: 2024/03/20 18:50:05 by chuchard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors constants
PURPLE			= \033[38;5;141m
GREEN			= \033[38;5;46m
BLUE			= \033[38;5;111m
RED				= \033[0;31m
TRANS			= \033[38;5;240m
RESET			= \033[0m
BOLD			= \033[1m
TRANS			= \033[2m
ITALIC			= \033[3m
CLEAR			= \r\033[K
SEP				= ${TRANS}────────────────────────────────────────────────────────────────────────────\n${RESET}

# Executable and compilation
NAME		  	= libft.a

SRC_DIR			= ./sources/
SRCS			= libft/ft_atoi.c \
			    libft/ft_bzero.c \
			    libft/ft_calloc.c \
			    libft/ft_isalnum.c \
			    libft/ft_isalpha.c \
			    libft/ft_isascii.c \
			    libft/ft_isdigit.c \
			    libft/ft_isprint.c \
			    libft/ft_ischarset.c \
			    libft/ft_itoa.c \
			    libft/ft_memchr.c \
			    libft/ft_memcmp.c \
			    libft/ft_memcpy.c \
			    libft/ft_memmove.c \
			    libft/ft_memset.c \
			    libft/ft_putchar_fd.c \
			    libft/ft_putendl_fd.c \
			    libft/ft_putnbr_fd.c \
			    libft/ft_putstr_fd.c \
			    libft/ft_realloc.c \
			    libft/ft_split.c \
			    libft/ft_strchr.c \
			    libft/ft_strdup.c \
			    libft/ft_strndup.c \
			    libft/ft_striteri.c \
			    libft/ft_strjoin.c \
			    libft/ft_strlcat.c \
			    libft/ft_strlcpy.c \
			    libft/ft_strlen.c \
			    libft/ft_strmapi.c \
			    libft/ft_strcmp.c \
			    libft/ft_strncmp.c \
			    libft/ft_strnstr.c \
			    libft/ft_strrchr.c \
			    libft/ft_strtrim.c \
			    libft/ft_substr.c \
			    libft/ft_tolower.c \
			    libft/ft_toupper.c \
				libft/ft_lstnew.c \
				libft/ft_lstadd_front.c \
				libft/ft_lstadd_back.c \
				libft/ft_lstsize.c \
				libft/ft_lstlast.c \
				libft/ft_lstdelone.c \
				libft/ft_lstclear.c \
				libft/ft_lstiter.c \
				libft/ft_lstmap.c \
				ft_printf/ft_printf.c \
				ft_printf/ft_printf_puts.c \
				get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c \
				random/ft_random.c

OBJ_DIR			= ./objs/
OBJS			= ${addprefix ${OBJ_DIR}, ${SRCS:.c=.o}}

RM			  	= rm -rf
CC			  	= gcc
CFLAGS		 	= -Wall -Wextra -Werror

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
	@tput cuu 3
	@printf "${SEP}${CLEAR}${RESET}${GREEN}»${RESET} [${PURPLE}${BOLD}libft${RESET}]: ${GREEN}Compiling ${RESET}%s..." ${notdir $<}
	@tput cr
	@printf "									 ${BOLD}[${RED}✘${RESET}]\n${SEP}"
	@${CC} ${CFLAGS} -I${SRC_DIR} -c $< -o $@


all:
	@printf "${SEP}${CLEAR}${RESET}${GREEN}»${RESET} [${PURPLE}${BOLD}libft${RESET}]: ${GREEN}No modification has been done${RESET} since last make.		 ${BOLD}[${GREEN}✔${RESET}]\n${RESET}${SEP}"
	@make -s all2

all2:	${NAME}

${NAME}: 		${OBJS}
	@ar rcs ${NAME} ${OBJS}
	@tput cuu 3
	@printf "${SEP}${CLEAR}${RESET}${GREEN}»${RESET} [${PURPLE}${BOLD}libft${RESET}]: Library ${GREEN}compiled${RESET} successfully.			 	 ${BOLD}[${GREEN}✔${RESET}]\n${RESET}${SEP}"

${OBJS}:		| ${OBJ_DIR}

${OBJ_DIR}:
	@mkdir ${OBJ_DIR}
	@mkdir ${OBJ_DIR}/libft
	@mkdir ${OBJ_DIR}/ft_printf
	@mkdir ${OBJ_DIR}/get_next_line
	@mkdir ${OBJ_DIR}/random

clean:
ifeq ($(wildcard objs), objs)
	@for file in $(wildcard ${OBJ_DIR}/*/*.o); do \
        printf "${SEP}${CLEAR}${RESET}${GREEN}»${RESET} [${PURPLE}${BOLD}libft${RESET}]: ${RED}Cleaning${RESET} %s..." $$(basename $$file); \
		tput cr; \
		printf "									 ${BOLD}[${RED}✘${RESET}]\n${SEP}"; \
		sleep 0.01; \
		tput cuu 3; \
        ${RM} $${file}; \
    done
	@${RM} ${OBJ_DIR}
	@printf "${SEP}${CLEAR}${RESET}${GREEN}»${RESET} [${PURPLE}${BOLD}libft${RESET}]: Objects ${GREEN}cleaned${RESET} successfully.			 	 ${BOLD}[${GREEN}✔${RESET}]\n${SEP}"
else
	@printf "${SEP}${CLEAR}${RESET}${GREEN}»${RESET} [${PURPLE}${BOLD}libft${RESET}]: Objects ${GREEN}have already been cleaned${RESET}.			 	 ${BOLD}[${GREEN}✔${RESET}]\n${SEP}"
endif

fclean: clean
	@tput cuu 2
ifeq ($(wildcard libft.a), libft.a)
	@printf "${CLEAR}${RESET}${GREEN}»${RESET} [${PURPLE}${BOLD}libft${RESET}]: ${RED}Cleaning${RESET} library..."
	@tput cr
	@printf "									 ${BOLD}[${RED}✘${RESET}]\n${SEP}"
	@${RM} ${NAME}
	@sleep 0.2
	@tput cuu 2
	@printf "${CLEAR}${RESET}${GREEN}»${RESET} [${PURPLE}${BOLD}libft${RESET}]: Library ${GREEN}cleaned${RESET} successfully.			 	 ${BOLD}[${GREEN}✔${RESET}]\n${SEP}"
else
	@printf "${CLEAR}${RESET}${GREEN}»${RESET} [${PURPLE}${BOLD}libft${RESET}]: Library ${GREEN}have already been cleaned${RESET}.			 	 ${BOLD}[${GREEN}✔${RESET}]\n${SEP}"
endif

re: 			fclean all

.SILENT: all clean fclean re
.PHONY: all clean fclean re