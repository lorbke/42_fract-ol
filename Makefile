# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 16:02:15 by lorbke            #+#    #+#              #
#    Updated: 2022/11/24 00:26:11 by lorbke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# name macros
NAME = fractol

# command macros
CC = cc
AR = ar rcs
RM = rm -f
GL_AR = "/Users/$(USER)/.brew/opt/glfw/lib/"
GL_FLAG = -lglfw
ADD_FLAGS = #-I include
FLAGS = -O3 #-Wall -Wextra -Werror

# path macros
LIB_PATH = lib
LFT_PATH = $(LIB_PATH)/libft
LFT_INC = $(LFT_PATH)/includes
MLX_PATH = $(LIB_PATH)/MLX42
MLX_INC = $(MLX_PATH)/include/MLX42
INC = includes
SRC_PATH = src
OBJ_PATH = obj

# src and obj files macros
SRC = hooks.c fractals.c colors.c main.c
OBJ = $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

# archive macros
LFT_AR = libft.a
MLX_AR = libmlx42.a

# default target
default: makedir all

# file targets
${NAME}: $(OBJ)
	@make -C $(MLX_PATH)
	@make -C $(LFT_PATH)
	${CC} ${FLAGS} $(OBJ) -L$(MLX_PATH) -lmlx42 -L$(LFT_PATH) -lft $(GL_FLAG) -L$(GL_AR) -o ${NAME}
	@echo "make: fractol success!"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	${CC} ${FLAGS} -I$(INC) -I$(MLX_INC) -I$(LFT_INC) -c $< -o $@ 

# phony targets
all: ${NAME}

makedir:
	@mkdir -p $(OBJ_PATH)

clean:
	${RM} -r $(OBJ_PATH)

fclean: clean
	${RM} ${NAME}
	cd $(MLX_PATH) && $(MAKE) fclean
	cd $(LFT_PATH) && $(MAKE) fclean

re: fclean makedir all

.PHONY: all clean fclean re