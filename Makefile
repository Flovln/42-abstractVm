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
			Lexer.cpp

FLAGS = -Wall -Wextra -Werror
# Genere les fichiers objet automatiquement depuis la liste des fichiers sources
OBJ = $(SRC:.cpp=.o)

# -- execution des commandes

# cible : dependance/s
#   commande

# all: regroupe les executables a produire
all: $(NAME)

$(NAME): $(OBJ)
	clang++ $(FLAGS) $(OBJ) -o $(NAME)

# $@ nom de la cible
# $< nom de la premiere dependance

# construire un .o a partir d'un .cpp
%.o : %.cpp
	clang++ $(FLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

# PHONY permet de definir les dependences systematiquement reconstruites
.PHONY: all clean fclean re