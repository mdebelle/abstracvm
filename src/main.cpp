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
#include <vector>
#include "instructionsClass.hpp"
#include "NumClass.hpp"
#include "error.hpp"

void							exitlexicalerror(eErrorType error)
{
	switch (error){
		case eErrorType::e_lexical: throw LexicalError();
		case eErrorType::e_unknow: throw UnknownError();
		case eErrorType::e_exit: throw ExitError();
		case eErrorType::e_zero: throw ZeroError();
		case eErrorType::e_twovalues: throw TwovaluesError();
	}
}

void							launchexec(std::vector<instructions> v)
{
	std::vector<IOperand const *> 			vOperand;

	for (std::vector<instructions>::iterator i = v.begin(); i != v.end(); ++i)
	{
		try {
			if (!i->getValid()) return exitlexicalerror(i->geteErrorType());
			else
			{
				vOperand = i->Execute(vOperand);
				if (!i->getValid()) return exitlexicalerror(i->geteErrorType());;
			}
		} catch (std::exception & e) {
			std::cerr << "Line: " << i->getLineNumber() << ": " << e.what();
		}
	}
}

void							fileArgument(char **argv)
{
	int							count = 0;
	std::string					line;
	std::string					filename(argv[1]);
	std::ifstream				avmfile(filename);
	std::vector<instructions>	v;

	if (avmfile.is_open())
	{
			while(getline(avmfile,line))
			{
				count++;
				v.push_back(instructions(line, count));
			}
	}		
	launchexec(v);
	return ;
}

int		main(int argc, char **argv)
{
	if (argc > 1) fileArgument(argv);
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
			if (v.back().getExit()) exit = true;
			if (v.back().ExitLoop(exit)) break ;
		}
		launchexec(v);
	}
	return (0);
}
