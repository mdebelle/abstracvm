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

void							exiterror(std::string str)
{
	std::cerr << str << std::endl;
}

void							launchexec(std::vector<instructions> v)
{
	std::vector<Num> 			vNum;

	for (std::vector<instructions>::iterator i = v.begin(); i != v.end(); ++i)
	{
		if (!i->getValid()) return exiterror(i->getError());
		else
		{
			vNum = i->Execute(vNum);
			if (!i->getValid()) return exiterror(i->getError());
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
