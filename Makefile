# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skrystin <skrystin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/03 20:54:43 by nalexand          #+#    #+#              #
#    Updated: 2019/08/05 15:07:04 by skrystin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH = src/corewar:src/asm:src/common:includes

.SECONDARY: $(COR_OBJ) $(ASM_OBJ) $(COM_OBJ)

override ARFLAGS = rcs

#МЫ НЕ ЗАБУДЕМ ДОБАВИТЬ ФЛАГИ -Wall -Werror -Wextra
CFLAGS = -g

HEADER = -I includes -I lib/libftprintf/includes
INCLUDES = corewar.h op.h

CORE = corewar
ASM = asm

COM_LIB = lib/common.a
COR_LIB = lib/corewar.a
ASM_LIB = lib/asm.a
LIBFT = lib/libftprintf.a
LIBFT_PATH = lib/libftprintf/

OBJ_DIR = obj/
LIB_DIR = lib/

COM_SRC =	print_memory.c \
			op.c

COR_SRC =	corewar.c \
			cw_clear_exit.c \
			cw_debug.c

ASM_SRC =	asm.c \
			first_validation.c \

COM_OBJ = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(COM_SRC)))
COR_OBJ = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(COR_SRC)))
ASM_OBJ = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(ASM_SRC)))

all: $(CORE) $(ASM)

$(CORE): $(COM_LIB) $(COR_LIB) $(LIBFT)
	gcc $(CFLAGS) -o $@ $^
$(ASM): $(COM_LIB) $(ASM_LIB) $(LIBFT)
	gcc $(CFLAGS) -o $@ $^

$(COR_LIB):: $(OBJ_DIR) $(LIB_DIR)
$(COR_LIB):: $(COR_LIB)($(COR_OBJ))
$(ASM_LIB):: $(OBJ_DIR) $(LIB_DIR)
$(ASM_LIB):: $(ASM_LIB)($(ASM_OBJ))
$(COM_LIB):: $(OBJ_DIR) $(LIB_DIR)
$(COM_LIB):: $(COM_LIB)($(COM_OBJ))
$(LIBFT): $(LIBFT_PATH)libftprintf.a
	cp $< lib/

$(LIBFT_PATH)libftprintf.a:
	make -C $(LIBFT_PATH)

$(OBJ_DIR):
	mkdir -p $@
$(LIB_DIR):
	mkdir -p $@

$(OBJ_DIR)%.o: %.c $(INCLUDES)
	@gcc $(CFLAGS) -c $< -o $@ $(HEADER)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(COM_LIB)
	@rm -f $(COR_LIB)
	@rm -f $(ASM_LIB)
	@rm -f $(LIBFT)
	@rm -rf *.dSYM

fclean: clean
	@rm -f $(CORE)
	@rm -f $(ASM)

re: fclean all

relib:
	make -C lib/libftprintf re
