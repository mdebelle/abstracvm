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
#include <fstream>
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

void	fileArgument(char **argv)
{
	int							count = 0;
	std::string					line;
	std::string					filename(argv[1]);
	std::ifstream				avmfile(filename);
	std::vector<instructions>	v;

	if (avmfile.is_open())
		while(getline(avmfile,line))
		{
			count++;
			v.push_back(instructions(line, count));
		}
	for (std::vector<instructions>::iterator i = v.begin(); i != v.end(); ++i)
	{
		if (!i->getValid())
			std::cout << i->getError() << std::endl;
		else
			i->Execute(v);
	}
	return ;
}

int main(int argc, char **argv)
{
	if (argc > 1)
		fileArgument(argv);
	else
	{
		int							count = 0;
		std::vector<instructions>	v;
		bool						exit = false;

		while (42)
		{
			char					line[1024];
			std::cin.getline(line, 1024);
			std::string				str(line);
			count++;
			v.push_back(instructions(str, count));
			if (v.back().getExit())
				exit = true;
			if (v.back().ExitLoop(exit))
				break ;
		}
		std::cout << "---------- instructions ---------" << std::endl;
		for (std::vector<instructions>::iterator i = v.begin(); i != v.end(); ++i)
			if (!i->getValid())
				std::cout << i->getError() << std::endl;
	}
	return (0);
}
