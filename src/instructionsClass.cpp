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

#include "factory.hpp"
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
		if (!setTypes(type) || !setValues(value)) return false;
		else return true;
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
				if (_valid) return true;
			}
		}
		_error = "Line " + std::to_string(_lineNumber) + ": Error : The assembly program includes one or several lexical errors or syntactic errors.";
		_valid = false;
		return true;
	}
	return false;
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

std::vector<IOperand const *> 	instructions::Execute(std::vector<IOperand const *> lst)
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

bool				instructions::isStackEnought(std::vector<IOperand const *> v)
{
	if (v.size() > 1)
		return true;
	_error = "Line " + std::to_string(_lineNumber) + ": Error : The stack is composed of strictly less that two values when an arithmetic instruction is executed.";
	_valid = false;
	return false;
}

eOperandType				instructions::ConvertStringToType(std::string str)
{
	if (str.compare("int8") == 0) return eOperandType::e_int8;
	if (str.compare("int16") == 0) return eOperandType::e_int16;
	if (str.compare("int32") == 0) return eOperandType::e_int32;
	if (str.compare("float") == 0) return eOperandType::e_float;
	if (str.compare("double") == 0) return eOperandType::e_double;
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

	trim(str);
	if (str.size() == 0) return false;

	if (_stype.compare("float") == 0 || _stype.compare("double") == 0)
	{
		for (size_t i = 0; i < str.length(); ++i)
		{
			if (i == 0 && str[i] == '-') continue;
			if (!isdigit(str[i]) && str[i] != '.') return false;
			else if (str[i] == '.')
			{
				if (!virgule) virgule = true;
				else return false;
			}
		}
	}
	else
	{
		for (size_t i = 0; i < str.length(); ++i)
		{
			if (i == 0 && str[i] == '-') continue;
			if (!isdigit(str[i])) return false;
		}
	}
	_svalue = str;
	return true;
}

/*************************/

/*
 * Pushes the value v at the top of the stack.
 * The value v must have one of the following form:
 * ◦ int8(n) : Creates an 8-bit integer with value n.
 * ◦ int16(n) : Creates a 16-bit integer with value n.
 * ◦ int32(n) : Creates a 32-bit integer with value n.
 * ◦ float(z) : Creates a float with value z.
 * ◦ double(z) : Creates a double with value z.
*/
void						instructions::ActionPush(std::vector<IOperand const *> v)
{
	_currentStack = v;
	// _currentStack.push_back(Factory::createOperand(getType(), getSvalue()));
	// isinlimits(_currentStack);
	return ;
}

/*
 * Unstacks the value from the top of the stack.
 * If the stack is empty, the program execution must stop with an error.
*/
void						instructions::ActionPop(std::vector<IOperand const *> v)
{
	_currentStack = v;
	if (v.size() > 0)
		_currentStack.pop_back();
	else {
		_error = "Line " + std::to_string(_lineNumber) + ": Error : Instruction pop on an empty stack";
		_valid = false;
	}
	return ;
}

/*
 *	Displays each value of the stack, from the most recent one to the oldest one WITHOUT CHANGING the stack.
 *	Each value is separated from the next one by a newline.
*/
void						instructions::ActionDump(std::vector<IOperand const *> v)
{
	_currentStack = v;
	while (v.size() > 0)
	{
		_out = v.back()->toString() + "\n" + _out;
		v.pop_back();
	}
	return ;
}

/*
 *	Asserts that the value at the top of the stack is equal to the one passed as parameter for this instruction.
 *	If it is not the case, the program execution must stop with an error.
 *	The value v has the same form that those passed as parameters to the instruction push
*/
void						instructions::ActionAssert(std::vector<IOperand const *> v)
{
	_currentStack = v;
	if (v.back()->toString() == getSvalue())
;		// _currentStack.push_back(createOperand(getType(), getSvalue()));
	else {
		_valid = false;
		_error = "Line " + std::to_string(_lineNumber) + ": Error : An assert instruction is not true";
		return ;
	}
	return ;
}

/*
 * Unstacks the first two values on the stack, adds them together and stacks the result.
 * If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error.
*/
void						instructions::ActionAdd(std::vector<IOperand const *> v)
{
	_currentStack = v;
	if (isStackEnought(v))
	{
		auto i = v.rbegin()[0];
		auto j = v.rbegin()[1];

		_currentStack.pop_back();
		_currentStack.pop_back();
		_currentStack.push_back(*i + *j);
	}
	return ;
}
/*
 * Unstacks the first two values on the stack, subtracts them, then stacks the result.
 * If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error.
*/
void						instructions::ActionSub(std::vector<IOperand const *> v)
{
	_currentStack = v;
	if (isStackEnought(v))
	{
		auto i = v.rbegin()[0];
		auto j = v.rbegin()[1];
		
		_currentStack.pop_back();
		_currentStack.pop_back();
		_currentStack.push_back(*j - *i);
	}
	return ;
}

/*
 * Unstacks the first two values on the stack, multiplies them, then stacks the result.
 * If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error.
*/
void						instructions::ActionMul(std::vector<IOperand const *> v)
{
	_currentStack = v;
	if (isStackEnought(v))
	{
		auto i = v.rbegin()[0];
		auto j = v.rbegin()[1];

		_currentStack.pop_back();
		_currentStack.pop_back();
		_currentStack.push_back(*j * *i);
	}
	return ;
}

/*
 * Unstacks the first two values on the stack, divides them, then stacks the result.
 * If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error.
 * Moreover, if the divisor is equal to 0, the program execution must stop with an error too.
 * Chatting about floating point values is relevant a this point.
 * If you don’t understand why, some will understand.
 * The linked question is an open one, there’s no definitive answer.
*/
void						instructions::ActionDiv(std::vector<IOperand const *> v)
{
	_currentStack = v;
	if (isStackEnought(v))
	{
		auto i = v.rbegin()[0];
		auto j = v.rbegin()[1];

		_currentStack.pop_back();
		_currentStack.pop_back();
		_currentStack.push_back(*j / *i);
	}
	return ;
}

/*
 * Unstacks the first two values on the stack, calculates the modulus, then stacks the result.
 * If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error.
 * Moreover, if the divisor is equal to 0, the program execution must stop with an error too.
 * Same note as above about fp values.
*/
void						instructions::ActionMod(std::vector<IOperand const *> v)
{
	_currentStack = v;
	if (isStackEnought(v))
	{
		auto i = v.rbegin()[0];
		auto j = v.rbegin()[1];

		_currentStack.pop_back();
		_currentStack.pop_back();
		_currentStack.push_back(*j % *i);
	}
	return ;
}

/*
 * Asserts that the value at the top of the stack is an 8-bit integer.
 * (If not, see the instruction assert)
 * Then interprets it as an ASCII value and displays the corresponding character on the standard output.
*/
void						instructions::ActionPrint(std::vector<IOperand const *> v)
{
	_currentStack = v;
	if (_currentStack.back()->getType() == eOperandType::e_int8)
	{
		const Num<int> *tmp = static_cast<const Num<int> * >(_currentStack.back());

		std::cout << tmp->getValue();
		// _out = t;
	}
	return ;
}

/*
 * Terminate the execution of the current program.
 * If this instruction does not appears while all others instruction has been processed,
 * the execution must stop with an error.
*/
void						instructions::ActionExit(std::vector<IOperand const *> v)
{
	_currentStack = v;
	return ;
}






