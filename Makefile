# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/03 20:54:43 by nalexand          #+#    #+#              #
#    Updated: 2019/08/03 21:29:52 by nalexand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH = src/corewar:src/asm:src/common:includes

.SECONDARY: $(CORE_OBJ) $(ASM_OBJ)

override ARFLAGS = rcs

CFLAGS = -g

HEADER = -I includes -I libftprintf/includes
INCLUDES = corewar.h

CORE = corewar
ASM = asm

COM_LIB = common.a
CORE_LIB = corewar.a
ASM_LIB = asm.a
LIBFT = libftprintf/libftprintf.a

OBJ_DIR = obj/

COM_SRC =	printer.c

CORE_SRC =	corewar.c

ASM_SRC =	asm.c

COM_OBJ = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(COM_SRC)))
CORE_OBJ = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(CORE_SRC)))
ASM_OBJ = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(ASM_SRC)))

all: $(CORE) $(ASM)

$(CORE): $(COM_LIB) $(CORE_LIB) $(LIBFT)
	gcc -o $@ $^
$(ASM): $(COM_LIB) $(ASM_LIB) $(LIBFT)
	gcc -o $@ $^

$(CORE_LIB):: $(OBJ_DIR)
$(CORE_LIB):: $(CORE_LIB)($(CORE_OBJ))
$(ASM_LIB):: $(OBJ_DIR)
$(ASM_LIB):: $(ASM_LIB)($(ASM_OBJ))
$(COM_LIB):: $(OBJ_DIR)
$(COM_LIB):: $(COM_LIB)($(COM_OBJ))
$(LIBFT):
	make -C libftprintf

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)%.o: %.c $(INCLUDES)
	gcc $(CFLAGS) -c $< -o $@ $(HEADER)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf *.dSYM
	rm -f $(COM_LIB)
	rm -f $(CORE_LIB)
	rm -f $(ASM_LIB)

fclean: clean
	rm -f $(CORE)
	rm -f $(ASM)

re: fclean all

relib:
	make -C libftprintf re
