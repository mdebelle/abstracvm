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

void	actionComment(std::string)
{
	std::cout << "this is a Comment line" << std::endl;
	return ;
}

int	actionPop(std::string)
{
	std::cout << "this is a Pop line" << std::endl;
	return 1;
}

int	actionDump(std::string)
{
	std::cout << "this is a Dump line" << std::endl;
	return 1;
}

int	actionAssert(std::string val)
{
	std::cout << "this is a Assert line. Value is " << val << std::endl;
	return 1;
}

int	actionAdd(std::string)
{
	std::cout << "this is a Add line" << std::endl;
	return 1;
}

int	actionSub(std::string)
{
	std::cout << "this is a Sub line" << std::endl;
	return 1;
}

int	actionMul(std::string)
{
	std::cout << "this is a Mul line" << std::endl;
	return 1;
}

int	actionDiv(std::string)
{
	std::cout << "this is a Div line" << std::endl;
	return 1;
}

int	actionMod(std::string)
{
	std::cout << "this is a Mod line" << std::endl;
	return 1;
}

int	actionPrint(std::string)
{
	std::cout << "this is a Print line" << std::endl;
	return 1;
}

int	actionExit(std::string)
{
	std::cout << "this is a Exit line" << std::endl;
	return 0;
}

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
		std::cout << "---------- insttructions ---------" << std::endl;
		
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
