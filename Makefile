# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fviolin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/13 10:38:46 by fviolin           #+#    #+#              #
#    Updated: 2017/12/13 10:38:51 by fviolin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -- definition de variables
NAME = avm

SRC = main.cpp\
		Vm.cpp\
		Instruction.cpp\
		Factory.cpp

FLAGS = -Wall -Wextra -Werror
# Genere les fichiers objet automatiquement depuis la liste des fichiers sources
OBJ = $(SRC:.cpp=.o)

# -- execution des commandes

# cible : dependance/s
#   commande

# all: regroupe les executables a produire
all: $(NAME)

$(NAME): $(OBJ)
	clang++ -std=c++11 $(FLAGS) $(OBJ) -o $(NAME)

# $@ nom de la cible
# $< nom de la premiere dependance

# construire un .o a partir d'un .cpp
%.o : %.cpp
	clang++ -std=c++11 $(FLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

# PHONY permet de definir les dependences systematiquement reconstruites
.PHONY: all clean fclean re