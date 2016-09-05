# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdebelle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/16 23:57:13 by mdebelle          #+#    #+#              #
#    Updated: 2016/08/16 23:57:17 by mdebelle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= avm

CXX			= g++ -std=c++11
CXXFLAGS	= -Wall -Werror -Wextra

INC			= -I include
SRC			= main.cpp instructionsClass.cpp Error.cpp factory.cpp
OBJ			= $(SRC:%.cpp=obj/%.o)

all: $(NAME)

$(NAME): obj $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(LIB)

obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -o $@ -c $<

obj:
	mkdir -p obj

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: fclean all clean
