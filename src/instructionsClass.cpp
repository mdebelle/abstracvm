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
#include "eOperandType.hpp"


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
	_lineNumber = number;
	_exit = false;
	_valid = false;
	setActionsMap();
	ParseInstruction();
	return ;
}
instructions::~instructions(void)
{
	return ;
}

void						instructions::ParseInstruction()
{
	std::string				str = _line;
	trim(str);
	str = SplitComment(";", str);
	if (str.empty())
		_valid = true;
	else if (isActionValue("push", str)
		|| isActionValue("assert", str)
		|| isSimpleAction("pop", str)
		|| isSimpleAction("dump", str)
		|| isSimpleAction("add", str)
		|| isSimpleAction("sub", str)
		|| isSimpleAction("mul", str)
		|| isSimpleAction("div", str)
		|| isSimpleAction("mod", str)
		|| isSimpleAction("print", str))
		;
	else if (isSimpleAction("exit", str))
		_exit = true;
}

bool						instructions::IsComment(std::string comp, std::string str, void (*f)(std::string))
{
	std::size_t				found = str.find(comp);

	if (found <= str.length())
	{
		(*f)(str);
		return true;
	}
	return false;
}

std::string					instructions::SplitComment(std::string sep, std::string str)
{
	std::size_t				pos = str.find(sep);
	if (pos < str.length())
	{
		std::string	ret = str.substr(0,pos);
		return trim(ret);
	}
	return str;
}

bool						instructions::isValue(std::string str)
{
	std::size_t				foundone = str.find("(");
	std::size_t				foundtwo = str.find_last_of(")");
	if (foundone < str.length() && foundtwo < str.length())
	{
		std::string			type = str.substr(0, foundone);
		std::string 		value = str.substr(foundone+1, foundtwo - (foundone+1));
		if (!setTypes(type) || !setValues(value))
			return false;
		return true;
	}
	return false;
}
bool						instructions::isSimpleAction(std::string action, std::string str)
{
	if (action.compare(str) == 0)
	{
		_valid = true;
		_action = action;
		return true;
	}
	_valid = false;
	_error = "Line " + std::to_string(_lineNumber) + ": Error : An instruction is unknown";
	return false;
}

bool						instructions::isActionValue(std::string comp, std::string str)
{
	if (str.compare(0, comp.length(), comp) == 0)
	{
		std::size_t			found = str.find(" ");
		if (found < str.length())
		{
			_action = str.substr(0, found);
			if (_action.compare(comp) == 0)
			{
				std::string	value = str.substr(found);
				_valid = isValue(trim(value));
				if (_valid)
					return true;
			}
		}
		_error = "Line " + std::to_string(_lineNumber) + ": Error : The assembly program includes one or several lexical errors or syntactic errors.";
		_valid = false;
		return true;
	}
	return false;
}

void						instructions::ActionPush(std::vector<instructions> v)
{
	v = v;
	return ;
}
void						instructions::ActionPop(std::vector<instructions> v)
{
	v = v;
	return ;
}

/*
 *	Displays each value of the stack, from the most recent one to the oldest one
 *	WITHOUT CHANGING the stack.
 *	Each value is separated from the next one by a newline.
*/
void						instructions::ActionDump(std::vector<instructions> v)
{
	for (std::vector<instructions>::iterator i = v.begin(); i != v.end(); ++i)
	{
		if (i->getLineNumber() < getLineNumber())
		{
			if (!i->getSvalue().empty())
				_out = i->getSvalue() + "\n" + _out;
		}
	}
	return ;
}
void						instructions::ActionAssert(std::vector<instructions> v)
{
	v = v;
	return ;
}
void						instructions::ActionAdd(std::vector<instructions> v)
{
	v = v;
	return ;
}
void						instructions::ActionSub(std::vector<instructions> v)
{
	v = v;
	return ;
}
void						instructions::ActionMul(std::vector<instructions> v)
{
	v = v;
	return ;
}
void						instructions::ActionDiv(std::vector<instructions> v)
{
	v = v;
	return ;
}
void						instructions::ActionMod(std::vector<instructions> v)
{
	v = v;
	return ;
}
void						instructions::ActionPrint(std::vector<instructions> v)
{
	v = v;
	return ;
}
void						instructions::ActionExit(std::vector<instructions> v)
{
	v = v;
	return ;
}

		
bool						instructions::ExitLoop(bool exit)
{
	std::string				str = _line;
	trim(str);
	if (str.compare(";;") == 0)
	{
		if (exit == false)
		{
			_valid = false;
			_error = "Line " + std::to_string(_lineNumber) + ": Error : The program doesn’t have an exit instruction";
		}
		return true;
	}
	return false;
}

std::vector<instructions> 	instructions::Execute(std::vector<instructions> lst)
{
	for (std::vector<instructions>::iterator i = lst.begin(); i != lst.end(); ++i)
	{
		if (getLineNumber() == i->getLineNumber())
		{
			action_map::const_iterator iter = _m.find(i->getAction());
			if (iter == _m.end())
			{
				std::cerr << "oups" << std::endl;
			} else {
				(this->*iter->second)(lst);
			}
			std::cout << getOut();
			return lst;
		}
	}
	return lst;
}

eOperandType				instructions::ConvertStringToType(std::string str)
{
	if (str.compare("int8") == 0)
		return INT8;
	if (str.compare("int16") == 0)
		return INT16;
	if (str.compare("int32") == 0)
		return INT32;
	if (str.compare("float") == 0)
		return FLOAT;
	if (str.compare("double") == 0)
		return DOUBLE;
	return INVALID;
}

int		 					instructions::ConvertTypeToPrecision(eOperandType eOp)
{
	switch (eOp) {
		case INT8:
			return 1;
		case INT16:
			return 2;
		case INT32:
			return 3;
		case FLOAT:
			return 4;
		case DOUBLE:
			return 5;
		case INVALID:
			return -1;
	}
	return -1;
}

std::string					instructions::getLine(void) const { return _line; }
int							instructions::getLineNumber(void) const { return _lineNumber; }
bool						instructions::getExit(void) const { return _exit; }
bool						instructions::getValid(void) const { return _valid; }
std::string					instructions::getError(void) const { return _error; }
std::string					instructions::getOut(void) const { return _out; }
std::string					instructions::getAction(void) const { return _action; }
std::string					instructions::getStype(void) const { return _stype; }
eOperandType				instructions::getType(void) const { return _type; }
int							instructions::getPrecision(void) const { return _precision; }		
std::string					instructions::getSvalue(void) const { return _svalue; }
int							instructions::getIvalue(void) const { return _ivalue; }
float						instructions::getFvalue(void) const { return _fvalue; }
double						instructions::getDvalue(void) const { return _dvalue; }
instructions::action_map	instructions::getM(void) const { return _m; }

void						instructions::setActionsMap(void)
{
	_m.insert(std::make_pair("push", &instructions::ActionPush));
	_m.insert(std::make_pair("pop", &instructions::ActionPop));
	_m.insert(std::make_pair("dump", &instructions::ActionDump));
	_m.insert(std::make_pair("assert", &instructions::ActionAssert));
	_m.insert(std::make_pair("add", &instructions::ActionAdd));
	_m.insert(std::make_pair("sub", &instructions::ActionSub));
	_m.insert(std::make_pair("mul", &instructions::ActionMul));
	_m.insert(std::make_pair("div", &instructions::ActionDiv));
	_m.insert(std::make_pair("mod", &instructions::ActionMod));
	_m.insert(std::make_pair("print", &instructions::ActionPrint));
	_m.insert(std::make_pair("exit", &instructions::ActionExit));
}

bool						instructions::setTypes(std::string str)
{
	if (str.compare("int8") == 0
		|| str.compare("int16") == 0
		|| str.compare("int32") == 0
		|| str.compare("float") == 0
		|| str.compare("double") == 0)
	{
		_stype = str;
		_type = ConvertStringToType(str);
		_precision = ConvertTypeToPrecision(_type);
		return true;
	}
	return false;
}

bool						instructions::setValues(std::string str)
{
	bool					virgule = false;

	if (_stype.compare("float") == 0 || _stype.compare("double") == 0)
	{
		for (size_t i = 0; i < str.length(); ++i)
		{
			if (i == 0 && str[i] == '-')
				continue ;
			if (!isdigit(str[i]) && str[i] != '.')
				return false;
			else if (str[i] == '.')
			{
				if (!virgule)
					virgule = true;
				else
					return false;
			}
		}
	}
	else
	{
		for (size_t i = 0; i < str.length(); ++i)
		{
			if (i == 0 && str[i] == '-')
				continue ;
			if (!isdigit(str[i]))
				return false;
		}
	}
	_svalue = str;
	return true;
}

