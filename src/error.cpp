/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdebelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 22:38:36 by mdebelle          #+#    #+#             */
/*   Updated: 2016/09/05 22:38:38 by mdebelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.hpp"

OverflowError::OverflowError(){}
OverflowError::~OverflowError() throw() {}
const char * OverflowError::what() const throw()
{
	std::string s = msg();
	return (s.c_str());

}
std::string OverflowError::msg() const
{
	std::stringstream ss;
	ss << "Error : Underflow/Overflow on a value" << std::endl;
	return ss.str();
}

ZeroError::ZeroError(){}
ZeroError::~ZeroError() throw() {}
const char * ZeroError::what() const throw()
{
	std::string s = msg();
	return (s.c_str());

}
std::string ZeroError::msg() const
{
	std::stringstream ss;
	ss << "Error : Division/modulo by 0" << std::endl;
	return ss.str();
}

LexicalError::LexicalError(){}
LexicalError::~LexicalError() throw() {}
const char * LexicalError::what() const throw()
{
	std::string s = msg();
	return (s.c_str());

}
std::string LexicalError::msg() const
{
	std::stringstream ss;
	ss << "Error : The assembly program includes one or several lexical errors or syntactic errors." << std::endl;
	return ss.str();
}

EmptyError::EmptyError(){}
EmptyError::~EmptyError() throw() {}
const char * EmptyError::what() const throw()
{
	std::string s = msg();
	return (s.c_str());

}
std::string EmptyError::msg() const
{
	std::stringstream ss;
	ss << "Error : Instruction pop on an empty stack." << std::endl;
	return ss.str();
}

AssertError::AssertError(){}
AssertError::~AssertError() throw() {}
const char * AssertError::what() const throw()
{
	std::string s = msg();
	return (s.c_str());

}
std::string AssertError::msg() const
{
	std::stringstream ss;
	ss << "Error : An assert instruction is not true." << std::endl;
	return ss.str();
}

TwovaluesError::TwovaluesError(){}
TwovaluesError::~TwovaluesError() throw() {}
const char * TwovaluesError::what() const throw()
{
	std::string s = msg();
	return (s.c_str());

}
std::string TwovaluesError::msg() const
{
	std::stringstream ss;
	ss << "Error : The stack is composed of strictly less than two values when an arithmetic instruction is executed." << std::endl;
	return ss.str();
}

UnknownError::UnknownError(){}
UnknownError::~UnknownError() throw() {}
const char * UnknownError::what() const throw()
{
	std::string s = msg();
	return (s.c_str());

}
std::string UnknownError::msg() const
{
	std::stringstream ss;
	ss << "Error : An instruction is unknown" << std::endl;
	return ss.str();
}

ExitError::ExitError(){}
ExitError::~ExitError() throw() {}
const char * ExitError::what() const throw()
{
	std::string s = msg();
	return (s.c_str());

}
std::string ExitError::msg() const
{
	std::stringstream ss;
	ss << "Error : The program doesn’t have an exit instruction." << std::endl;
	return ss.str();
}

