/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructionsClass.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdebelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 04:30:40 by mdebelle          #+#    #+#             */
/*   Updated: 2016/08/19 04:30:42 by mdebelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructionsClass.hpp"


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

instructions::instructions(std::string line, int number)
{
	_line = line;
	_number = number;
	_exit = false;
	_valid = false;
	defineInstruction();
	return ;
}
instructions::~instructions(void)
{
	return ;
}

void			instructions::defineInstruction(void)
{
	std::string str = _line;
	trim(str);
	str = splitcomment(";", str);
	if (str.empty()
		|| checkActionValue("push", str) == 1
		|| checkActionValue("assert", str) == 1
		|| checkSimpleAction("pop", str) == 1
		|| checkSimpleAction("dump", str) == 1
		|| checkSimpleAction("add", str) == 1
		|| checkSimpleAction("sub", str) == 1
		|| checkSimpleAction("mul", str) == 1
		|| checkSimpleAction("div", str) == 1
		|| checkSimpleAction("mod", str) == 1
		|| checkSimpleAction("print", str) == 1) {
		_valid = true;
	} else if (checkSimpleAction("exit", str) == 1)
		_exit = true;
}

bool			instructions::exitLoop(bool exit)
{
	std::string str = _line;
	trim(str);

	if (str.compare(";;") == 0)
	{
		if (exit == false)
		{
			_valid = false;
			_error = "Line " + std::to_string(_number) + ": Error : The program doesn’t have an exit instruction";
		}
		return true;
	}
	return false;
}

std::string		instructions::getLine(void) const
{
	return _line ;
}

int				instructions::getNumber(void) const
{
	return _number;
}

bool			instructions::getValid(void) const
{
	return  _valid;
}

bool			instructions::getExit(void) const
{
	return  _exit;
}

std::string		instructions::getError(void) const
{
	return _error;
}

std::string		instructions::getType(void) const
{
	return _type;
}


bool	instructions::checkComment(std::string comp, std::string str, void (*f)(std::string))
{
	std::size_t found = str.find(comp);

	if (found <= str.length())
	{
		(*f)(str);
		return true;
	}
	return false;
}


int	instructions::actionPush(std::string val)
{
	std::cout << "this is a Push line. Value is " << val << std::endl;
	return 1;
}


int	instructions::actionAssert(std::string val)
{
	std::cout << "this is a Assert line. Value is " << val << std::endl;
	return 1;
}


bool	instructions::checkSimpleAction(std::string action, std::string str)
{
	if (action.compare(str) == 0)
	{
		_valid = true;
		_type = action;
		return true;
	}
	_valid = false;
	_error = "Line " + std::to_string(_number) + ": Error : An instruction is unknown";
	return false;
}

int		instructions::checkActionValue(std::string comp, std::string str)
{
	std::size_t found = str.find(" ");

	if (found < str.length())
	{
		std::string action = str.substr(0, found);
		if (action.compare(comp) == 0)
		{
			std::string value = str.substr(found);
			return (1);
		}
	}
	return (2);
}

std::string	instructions::splitcomment(std::string sep, std::string str)
{
	std::size_t pos = str.find(sep);

	if (pos < str.length())
	{
		std::string ret = str.substr(0,pos);
		return trim(ret);
	}
	return str;
}

