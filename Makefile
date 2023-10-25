# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/30 15:23:20 by lucocozz          #+#    #+#              #
#    Updated: 2023/10/23 17:31:13 by lucocozz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lemipc

SRCS =	main.c		\
		$(_PARSER)	\
		$(_UTILS)	\
		$(_PROCESS)	\
		$(_BOARD)	\

_PARSER =	parse_config.c

_BOARD =	divide_board_equal_area.c		\
			free_polygons.c					\
			area_id_is.c					\
			halton_sequence.c				\
			spread_players.c				\
			print_board.c					\

_UTILS =	math_utils.c					\
			string_utils.c					\
			io_utils.c						\
			signal_utils.c

_PROCESS = 	init_process.c					\
			clean_process.c					\
			$(_MASTER)						\
			$(_SUB)

_MASTER =	master_process.c				\
			init_teams.c					\
			waiting_players.c				\
			game_loop.c

_SUB =		sub_process.c					\
			player_loop.c					\
			death_check.c					\
			move_to_enemy.c					\
			find_nearest_enemy.c			\
			find_nearest_ally_to_enemy.c	\


OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
DEPENDENCIES = $(OBJS:%.o=%.d)

SRCS_DIR = sources
LIBS_DIR = libs
OBJS_DIR = .objs
INCLUDES_DIR = includes $(LIBS:%=lib%/includes) $(LIBS:%=lib%)

LIBS =

MAKE = make
CC = gcc
RM = rm -f
MKDIR = mkdir -p
DEBUG = off

CFLAGS = -lm -MMD -Wall -Wextra -Werror
CXXFLAGS = $(INCLUDES_DIR:%=-I %)
ifeq ($(DEBUG), on)
	CXXFLAGS += -g3
endif
LDFLAGS = $(LIBS:%=-L lib%) $(LIBS:%=-l%) -lm -lpthread

vpath %.c	$(addprefix $(SRCS_DIR), /.									\
				$(addprefix /board, /. /areas)							\
				$(addprefix /process, /. /master_process /sub_process)	\
				/utils /parser /master_process /sub_process				\
			)

all:
	$(foreach LIB, ${LIBS}, ${MAKE} -C lib${LIB} ;)
	$(MAKE) $(NAME)

scan:
	scan-build $(MAKE)

$(NAME): $(OBJS) | $(LIBS:%=lib%.a)
	$(CC) $(CXXFLAGS) $^ -o $(NAME) $(LDFLAGS)

-include $(DEPENDENCIES)
$(OBJS_DIR)/%.o: %.c $(OBJS_DIR)/debug$(DEBUG) | $(OBJS_DIR) 
	$(CC) $(CFLAGS) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@ 

$(OBJS_DIR):
	$(MKDIR) $(OBJS_DIR)

lib%.a:
	$(MAKE) -C $(@:%.a=%)

$(OBJS_DIR)/debug$(DEBUG): | $(OBJS_DIR)
	$(RM) $(OBJS_DIR)/debug*
	touch $@

clean:
	$(foreach LIB, $(LIBS), $(MAKE) $@ -C lib$(LIB);)
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME) $(foreach LIB, $(LIBS), lib$(LIB)/lib$(LIB).a)

re: fclean all

.PHONY: all clean fclean re scan
