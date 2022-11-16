# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 16:02:15 by lorbke            #+#    #+#              #
#    Updated: 2022/11/16 16:39:13 by lorbke           ###   ########.fr        #
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
FLAGS = #-Wall -Wextra -Werror

# path macros
LIB_PATH = lib
MLX_PATH = $(LIB_PATH)/MLX42
MLX_INC = $(MLX_PATH)/include/MLX42
INC = includes
SRC_PATH = src
OBJ_PATH = obj

# src and obj files macros
SRC = main.c
OBJ = $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

# archive macros
MLX_AR = libmlx42.a

# default target
default: makedir all

# file targets
${NAME}: $(OBJ)
	@make -C $(MLX_PATH)
	${CC} ${FLAGS} $(OBJ) ${MLX_PATH}/${MLX_AR} $(GL_FLAG) -L$(GL_AR) -o ${NAME}
	@echo "make: fractol success!"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	${CC} ${FLAGS} -I$(INC) -I$(MLX_INC) -c $< -o $@ 

# phony targets
all: ${NAME}

makedir:
	@mkdir -p $(OBJ_PATH)

clean:
	${RM} -r $(OBJ_PATH)

fclean: clean
	${RM} ${NAME}
	cd $(MLX_PATH) && $(MAKE) fclean

re: fclean makedir all

.PHONY: all clean fclean re