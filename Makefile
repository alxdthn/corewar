# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/03 20:54:43 by nalexand          #+#    #+#              #
#    Updated: 2019/08/04 15:00:21 by nalexand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH = src/corewar:src/asm:src/common:includes

.SECONDARY: $(CORE_OBJ) $(ASM_OBJ)

override ARFLAGS = rcs

CFLAGS = -g

HEADER = -I includes -I lib/libftprintf/includes
INCLUDES = corewar.h op.h

CORE = corewar
ASM = asm

COM_LIB = lib/common.a
CORE_LIB = lib/corewar.a
ASM_LIB = lib/asm.a
LIBFT = lib/libftprintf/libftprintf.a

OBJ_DIR = obj/
LIB_DIR = lib/

COM_SRC =	print_memory.c \
			op.c

CORE_SRC =	corewar.c

ASM_SRC =	asm.c

COM_OBJ = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(COM_SRC)))
CORE_OBJ = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(CORE_SRC)))
ASM_OBJ = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(ASM_SRC)))

all: $(CORE) $(ASM)

$(CORE): $(COM_LIB) $(CORE_LIB) $(LIBFT)
	gcc $(CFLAGS) -o $@ $^
$(ASM): $(COM_LIB) $(ASM_LIB) $(LIBFT)
	gcc $(CFLAGS) -o $@ $^

$(CORE_LIB):: $(OBJ_DIR) $(LIB_DIR)
$(CORE_LIB):: $(CORE_LIB)($(CORE_OBJ))
$(ASM_LIB):: $(OBJ_DIR) $(LIB_DIR)
$(ASM_LIB):: $(ASM_LIB)($(ASM_OBJ))
$(COM_LIB):: $(OBJ_DIR) $(LIB_DIR)
$(COM_LIB):: $(COM_LIB)($(COM_OBJ))
$(LIBFT): lib/libftprintf.a
	make -C lib/libftprintf
	cp lib/libftprintf/libftprintf.a ../

$(OBJ_DIR):
	mkdir -p $@
$(LIB_DIR):
	mkdir -p $@

$(OBJ_DIR)%.o: %.c $(INCLUDES)
	gcc $(CFLAGS) -c $< -o $@ $(HEADER)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(COM_LIB)
	@rm -f $(COR_LIB)
	@rm -f $(ASM_LIB)
	@rm -rf *.dSYM

fclean: clean
	@rm -f $(CORE)
	@rm -f $(ASM)

re: fclean all

relib:
	make -C lib/libftprintf re
