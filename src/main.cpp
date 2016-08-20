/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdebelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 23:43:22 by mdebelle          #+#    #+#             */
/*   Updated: 2016/08/16 23:57:00 by mdebelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <vector>
#include "instructionsClass.hpp"

// • The assembly program includes one or several lexical errors or syntactic errors.
// • An instruction is unknown
// • Overflow on a value
// • Underflow on a value
// • Instruction pop on an empty stack
// • Division/modulo by 0
// • The program doesn’t have an exit instruction
// • An assert instruction is not true
// • The stack is composed of strictly less that two values when an arithmetic instruction is executed.

int main(int argc, char **argv)
{
	if (argc > 1)
		std::cout << argv[0] << std::endl;
	else
	{
		int			i = 2;
		int			count = 0;
		std::vector<instructions> v;
		bool		exit = false;

		while (i != 0)
		{			
			char	line[1024];
			std::cin.getline(line, 1024);
			count++;
			std::string str(line);
			v.push_back(instructions(str, count));
			if (v.back().getExit())
				exit = true;
			if (v.back().exitLoop(exit))
				break ;
		}
		std::cout << "---------- instructions ---------" << std::endl;

		for (std::vector<instructions>::iterator i = v.begin(); i != v.end(); ++i)
		{
			if (!i->getValid())
			{
				std::cout << i->getError() << std::endl;
			}
		}
	}
	return (0);
}
