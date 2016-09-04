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
#include <stdio.h>


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

void						instructions::ActionPush(std::vector<Num> v)
{
	_currentStack = v;
	_currentStack.push_back(Num(getSvalue(), getType()));
	isinlimits(_currentStack);
	// std::cerr << "[Push]" << std::endl;
	return ;
}
void						instructions::ActionPop(std::vector<Num> v)
{
	_currentStack = v;
	if (v.size() > 0)
		_currentStack.pop_back();
	else {
		_error = "Line " + std::to_string(_lineNumber) + ": Error : Instruction pop on an empty stack";
		_valid = false;
	}
	// std::cerr << "[Pop]" << std::endl;
	return ;
}

/*
 *	Displays each value of the stack, from the most recent one to the oldest one WITHOUT CHANGING the stack.
 *	Each value is separated from the next one by a newline.
*/
void						instructions::ActionDump(std::vector<Num> v)
{
	_currentStack = v;
	for (std::vector<Num>::reverse_iterator i = _currentStack.rbegin(); i != _currentStack.rend(); ++i)
	{
		_out = i->getStr() + "\n" + _out;
	}
	// std::cerr << "[Dump]" << std::endl;
	return ;
}

/*
 *	Asserts that the value at the top of the stack is equal to the one passed as parameter for this instruction.
 *	If it is not the case, the program execution must stop with an error.
 *	The value v has the same form that those passed as parameters to the instruction push
*/
void						instructions::ActionAssert(std::vector<Num> v)
{
	// std::cerr << "[Assert]" << std::endl;
	_currentStack = v;
	if (v.back().getStr() == getSvalue())
		_currentStack.push_back(Num(getSvalue(), getType()));
	else {
		_valid = false;
		_error = "Line " + std::to_string(_lineNumber) + ": Error : An assert instruction is not true";
		return; // Stop
	}
	return ;
}

void						instructions::ActionAdd(std::vector<Num> v)
{
	_currentStack = v;
	if (isStackEnought(v))
	{
		auto i = v.rbegin()[0];
		auto j = v.rbegin()[1];

		_currentStack.pop_back();
		_currentStack.pop_back();

		auto p = (i.gettype() >= j.gettype()) ? i.gettype() : j.gettype();
		
		_currentStack.push_back(Num(
			(i.getiNum() + j.getiNum()),
			(i.getfNum() + j.getfNum()),
			(i.getdNum() + j.getdNum()), p));

		isinlimits(_currentStack);
	}
	// std::cerr << "[Add]" << std::endl;
	return ;
}
void						instructions::ActionSub(std::vector<Num> v)
{
	_currentStack = v;
	if (isStackEnought(v))
	{
		auto i = v.rbegin()[0];
		auto j = v.rbegin()[1];
		
		_currentStack.pop_back();
		_currentStack.pop_back();
	
		auto p = (i.gettype() >= j.gettype()) ? i.gettype() : j.gettype();
		
		_currentStack.push_back(Num(
			(i.getiNum() + j.getiNum()),
			(i.getfNum() + j.getfNum()),
			(i.getdNum() + j.getdNum()), p));

	}	// std::cerr << "[Sub]" << std::endl;
	return ;
}
void						instructions::ActionMul(std::vector<Num> v)
{
	_currentStack = v;
	if (isStackEnought(v))
	{
		auto i = v.rbegin()[0];
		auto j = v.rbegin()[1];

		_currentStack.pop_back();
		_currentStack.pop_back();

		auto p = (i.gettype() >= j.gettype()) ? i.gettype() : j.gettype();

		_currentStack.push_back(Num(
			(i.getiNum() * j.getiNum()),
			(i.getfNum() * j.getfNum()),
			(i.getdNum() * j.getdNum()), p));
	}
	// std::cerr << "[Mul]" << std::endl;
	return ;
}
void						instructions::ActionDiv(std::vector<Num> v)
{
	_currentStack = v;
	if (isStackEnought(v))
	{
		auto i = v.rbegin()[0];
		auto j = v.rbegin()[1];

		_currentStack.pop_back();
		_currentStack.pop_back();

		auto p = (i.gettype() >= j.gettype()) ? i.gettype() : j.gettype();

		if (i.getiNum() == 0) {
			setErrorZero();
			return ;
		}

		_currentStack.push_back(Num(
			(j.getiNum() / i.getiNum()),
			(j.getfNum() / i.getfNum()),
			(j.getdNum() / i.getdNum()), p));
	}
	// std::cerr << "[Div]" << std::endl;
	return ;
}
void						instructions::ActionMod(std::vector<Num> v)
{
	_currentStack = v;
	if (isStackEnought(v))
	{
		auto i = v.rbegin()[0];
		auto j = v.rbegin()[1];

		_currentStack.pop_back();
		_currentStack.pop_back();

		if (i.getiNum() == 0) {
			setErrorZero();
			return ;
		}					

		int itmp = j.getiNum() % i.getiNum();
		float ftmp = itmp;
		double dtmp = itmp;

		auto p = (i.gettype() >= j.gettype()) ? i.gettype() : j.gettype();
		p  = (p > eOperandType::e_int32) ? eOperandType::e_int32 : p;

		_currentStack.push_back(Num(itmp, ftmp, dtmp, p));
	}
	// std::cerr << "[Mod]" << std::endl;
	return ;
}
void						instructions::ActionPrint(std::vector<Num> v)
{
	_currentStack = v;
	if (_currentStack.back().gettype() == eOperandType::e_int8)
	{
		char str[3];
		sprintf(str, "%c", _currentStack.back().getiNum());
		
		std::string t(str);
		_out = t;
	}
	// std::cerr << "[Print]" << std::endl;
	return ;
}
void						instructions::ActionExit(std::vector<Num> v)
{
	_currentStack = v;
	// std::cerr << "[Exit]" << std::endl;
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

std::vector<Num> 	instructions::Execute(std::vector<Num> lst)
{
	action_map::const_iterator iter = _m.find(getAction());
	if (iter == _m.end())
	{
		_currentStack = lst;
	} else {
		(this->*iter->second)(lst);
	}
	std::cout << getOut();
	return _currentStack;
}


void				instructions::setErrorZero(void)
{

	_error = "Line " + std::to_string(_lineNumber) + ": Error : Division/modulo by 0";
	_valid = false;
}

bool				instructions::isStackEnought(std::vector<Num> v)
{
	if (v.size() > 1)
		return true;
	_error = "Line " + std::to_string(_lineNumber) + ": Error : The stack is composed of strictly less that two values when an arithmetic instruction is executed.";
	_valid = false;
	return false;
}

void				instructions::setErrorLimits(std::string flow)
{

	_error = "Line " + std::to_string(_lineNumber) + ": Error : " + flow + " on a value";
	_valid = false;
}

bool				instructions::isinlimits(std::vector<Num> v)
{
	auto tmp = v.back();

	if ((tmp.gettype() == eOperandType::e_double && std::numeric_limits<double>::max() < tmp.getdNum())
		|| (tmp.gettype() == eOperandType::e_float && std::numeric_limits<float>::max() < tmp.getfNum())
		|| (tmp.gettype() == eOperandType::e_int32 && std::numeric_limits<int>::max() < tmp.getiNum())
		|| (tmp.gettype() == eOperandType::e_int16 && std::numeric_limits<short int>::max() < tmp.getiNum())
		|| (tmp.gettype() == eOperandType::e_int8 && 255 < tmp.getiNum())){
			setErrorLimits("Overflow");
			return false;
	}
	else if ((tmp.gettype() == eOperandType::e_double && tmp.getdNum() < std::numeric_limits<double>::min()) 
		|| (tmp.gettype() == eOperandType::e_float && tmp.getfNum() < std::numeric_limits<float>::min())
		|| (tmp.gettype() == eOperandType::e_int32 && tmp.getiNum() < std::numeric_limits<int>::min())
		|| (tmp.gettype() == eOperandType::e_int16 && tmp.getiNum() < std::numeric_limits<short int>::min())
		|| (tmp.gettype() == eOperandType::e_int8 && tmp.getiNum() < -255)){
			setErrorLimits("Underflow");
			return false;
		}
	return true;
}

eOperandType				instructions::ConvertStringToType(std::string str)
{
	if (str.compare("int8") == 0)
		return eOperandType::e_int8;
	if (str.compare("int16") == 0)
		return eOperandType::e_int16;
	if (str.compare("int32") == 0)
		return eOperandType::e_int32;
	if (str.compare("float") == 0)
		return eOperandType::e_float;
	if (str.compare("double") == 0)
		return eOperandType::e_double;
	return eOperandType::e_invalid;
}

int		 					instructions::ConvertTypeToPrecision(eOperandType eOp)
{
	switch (eOp) {
		case eOperandType::e_int8:
			return 0;
		case eOperandType::e_int16:
			return 1;
		case eOperandType::e_int32:
			return 2;
		case eOperandType::e_float:
			return 3;
		case eOperandType::e_double:
			return 4;
		case eOperandType::e_invalid:
			return 5;
	}
	return 5;
}

eOperandType				instructions::ConvertPrecisionToType(int eOp)
{
	switch (eOp) {
		case 0:
			return eOperandType::e_int8;
		case 1:
			return eOperandType::e_int16;
		case 2:
			return eOperandType::e_int32;
		case 3:
			return eOperandType::e_float;
		case 4:
			return eOperandType::e_double;
		default :
			return eOperandType::e_invalid;
	}
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

