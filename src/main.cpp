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

void	actionComment(std::string)
{
	std::cout << "this is a Comment line" << std::endl;
	return ;
}

int	actionPush(std::string)
{
	std::cout << "this is a Push line" << std::endl;
	return 1;
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

int	actionAssert(std::string)
{
	std::cout << "this is a Assert line" << std::endl;
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

static std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

static std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

static std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

bool	checkComment(std::string comp, std::string str, void (*f)(std::string))
{
	std::size_t found = str.find(comp);
	if (found <= str.length()) {
		(*f)(str);
		return true;
	}
	return false;
}

int		checkAction(std::string comp, std::string str, int (*f)(std::string))
{

	std::size_t found = str.find(comp);

	if (found == 0) {	
		checkComment(";", str, actionComment);
		return (*f)(str);
	}
	return (2);
}

int main(int argc, char **argv)
{
	if (argc > 1) {
		std::cout << argv[0] << std::endl;
	} else {
		
		int			i = 2;

		while (i != 0)
		{			
			char	line[1024];
			std::cin.getline(line, 1024);

			std::string str(line);
			trim(str);
			if (checkAction(";;", str, actionExit) == 0)
				break ;
			else if (checkAction("push ", str, actionPush) == 1
				|| checkAction("pop", str, actionPop) == 1
				|| checkAction("dump", str, actionDump) == 1
				|| checkAction("assert ", str, actionAssert) == 1
				|| checkAction("add", str, actionAdd) == 1
				|| checkAction("sub", str, actionSub) == 1
				|| checkAction("mul", str, actionMul) == 1
				|| checkAction("div", str, actionDiv) == 1
				|| checkAction("mod", str, actionMod) == 1
				|| checkAction("print", str, actionPrint) == 1)
			{
				std::cout << "valid line" << std::endl;
				continue ;
			} else if (!checkComment(";", str, actionComment)){
				std::cout << "Error line: no instruction" << std::endl;
			}
		}
	}
	return (0);
}
