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
	this->_line = line;
	this->_lineNumber = number;
	this->_exit = false;
	this->_valid = false;
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
	std::string				str = this->_line;
	trim(str);
	str = SplitComment(";", str);
	if (str.empty())
		this->_valid = true;
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
		this->_exit = true;
	else {
		this->_valid = false;
		this->_etype = eErrorType::e_unknow;
	}
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
		this->_valid = true;
		this->_action = action;
		return true;
	}
	this->_valid = false;
	return false;
}

bool						instructions::isActionValue(std::string comp, std::string str)
{
	if (str.compare(0, comp.length(), comp) == 0)
	{
		std::size_t			found = str.find(" ");
		if (found < str.length())
		{
			this->_action = str.substr(0, found);
			if (this->_action.compare(comp) == 0)
			{
				std::string	value = str.substr(found);
				this->_valid = isValue(trim(value));
				if (this->_valid) return true;
			}
		}
		this->_valid = false;
		return true;
	}
	return false;
}
		
bool						instructions::ExitLoop(bool exit)
{
	std::string				str = this->_line;
	trim(str);
	if (str.compare(";;") == 0)
	{
		if (exit == false)
		{
			this->_valid = false;
			this->_etype = eErrorType::e_exit;
		}
		return true;
	}
	return false;
}

std::vector<IOperand const *> 	instructions::Execute(std::vector<IOperand const *> lst)
{
	action_map::const_iterator iter = this->_m.find(getAction());
	if (iter == this->_m.end()) this->_currentStack = lst;
	else (this->*iter->second)(lst);
	std::cout << getOut();
	return this->_currentStack;
}

bool				instructions::isStackEnought(std::vector<IOperand const *> v)
{
	if (v.size() > 1)
		return true;
	this->_valid = false;
	this->_etype = eErrorType::e_twovalues;
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

std::string					instructions::getLine(void) const { return this->_line; }
int							instructions::getLineNumber(void) const { return this->_lineNumber; }
bool						instructions::getExit(void) const { return this->_exit; }
bool						instructions::getValid(void) const { return this->_valid; }
eErrorType					instructions::geteErrorType(void) const { return this->_etype; }
std::string					instructions::getOut(void) const { return this->_out; }
std::string					instructions::getAction(void) const { return this->_action; }
eOperandType				instructions::getType(void) const { return this->_type; }
std::string					instructions::getSvalue(void) const { return this->_svalue; }
instructions::action_map	instructions::getM(void) const { return this->_m; }

void						instructions::setActionsMap(void)
{
	this->_m.insert(std::make_pair("push", &instructions::ActionPush));
	this->_m.insert(std::make_pair("pop", &instructions::ActionPop));
	this->_m.insert(std::make_pair("dump", &instructions::ActionDump));
	this->_m.insert(std::make_pair("assert", &instructions::ActionAssert));
	this->_m.insert(std::make_pair("add", &instructions::ActionAdd));
	this->_m.insert(std::make_pair("sub", &instructions::ActionSub));
	this->_m.insert(std::make_pair("mul", &instructions::ActionMul));
	this->_m.insert(std::make_pair("div", &instructions::ActionDiv));
	this->_m.insert(std::make_pair("mod", &instructions::ActionMod));
	this->_m.insert(std::make_pair("print", &instructions::ActionPrint));
	this->_m.insert(std::make_pair("exit", &instructions::ActionExit));
}

bool						instructions::setTypes(std::string str)
{
	if (str.compare("int8") == 0
		|| str.compare("int16") == 0
		|| str.compare("int32") == 0
		|| str.compare("float") == 0
		|| str.compare("double") == 0)
	{
		this->_stype = str;
		this->_type = ConvertStringToType(str);
		return true;
	}
	return false;
}

bool						instructions::setValues(std::string str)
{
	bool					virgule = false;

	trim(str);
	if (str.size() == 0) return false;

	if (this->_stype.compare("float") == 0 || this->_stype.compare("double") == 0)
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
	this->_svalue = str;
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
	this->_currentStack = v;
	Factory f;
	this->_currentStack.push_back(f.createOperand(this->getType(), this->getSvalue()));
	return ;
}

/*
 * Unstacks the value from the top of the stack.
 * If the stack is empty, the program execution must stop with an error.
*/
void						instructions::ActionPop(std::vector<IOperand const *> v)
{
	this->_currentStack = v;
	if (v.size() > 0)
		this->_currentStack.pop_back();
	else {
		throw EmptyError();
		this->_valid = false;
	}
	return ;
}

/*
 *	Displays each value of the stack, from the most recent one to the oldest one WITHOUT CHANGING the stack.
 *	Each value is separated from the next one by a newline.
*/
void						instructions::ActionDump(std::vector<IOperand const *> v)
{
	this->_currentStack = v;
	while (v.size() > 0)
	{
		this->_out = v.back()->toString() + "\n" + this->_out;
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
	this->_currentStack = v;
	Factory f;
	auto val = f.createOperand(this->getType(), this->getSvalue());
	if ((v.back()->getType() == val->getType()) && (v.back()->toString() == val->toString()))
		this->_currentStack.push_back(val);
	else {
		throw AssertError();
		this->_valid = false;
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
	this->_currentStack = v;
	if (isStackEnought(v))
	{
		auto i = v.rbegin()[0];
		auto j = v.rbegin()[1];

		this->_currentStack.pop_back();
		this->_currentStack.pop_back();
		this->_currentStack.push_back(*i + *j);
	}
	return ;
}
/*
 * Unstacks the first two values on the stack, subtracts them, then stacks the result.
 * If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error.
*/
void						instructions::ActionSub(std::vector<IOperand const *> v)
{
	this->_currentStack = v;
	if (isStackEnought(v))
	{
		auto i = v.rbegin()[0];
		auto j = v.rbegin()[1];
		
		this->_currentStack.pop_back();
		this->_currentStack.pop_back();
		this->_currentStack.push_back(*j - *i);
	}
	return ;
}

/*
 * Unstacks the first two values on the stack, multiplies them, then stacks the result.
 * If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error.
*/
void						instructions::ActionMul(std::vector<IOperand const *> v)
{
	this->_currentStack = v;
	if (isStackEnought(v))
	{
		auto i = v.rbegin()[0];
		auto j = v.rbegin()[1];

		this->_currentStack.pop_back();
		this->_currentStack.pop_back();
		this->_currentStack.push_back(*j * *i);
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
	this->_currentStack = v;
	if (isStackEnought(v))
	{
		auto i = v.rbegin()[0];
		auto j = v.rbegin()[1];

		this->_currentStack.pop_back();
		this->_currentStack.pop_back();
		this->_currentStack.push_back(*j / *i);
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
	this->_currentStack = v;
	if (isStackEnought(v))
	{
		auto i = v.rbegin()[0];
		auto j = v.rbegin()[1];

		this->_currentStack.pop_back();
		this->_currentStack.pop_back();
		this->_currentStack.push_back(*j % *i);
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
	this->_currentStack = v;
	if (this->_currentStack.back()->getType() == eOperandType::e_int8)
	{
		const Num<int8_t> *tmp = static_cast<const Num<int8_t> * >(this->_currentStack.back());
		std::cout << tmp->getValue();
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
	this->_currentStack = v;
	return ;
}
