/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdebelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 22:33:08 by mdebelle          #+#    #+#             */
/*   Updated: 2016/09/05 22:33:11 by mdebelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HPP
# define ERROR_HPP

#include <exception>
#include <sstream>
#include <string>


enum class eErrorType
{
	e_lexical = 0,
	e_unknow = 1,
	e_exit = 2,
	e_zero = 3,
	e_twovalues = 4,
};


class AVM: public std::exception
{
	public:
		virtual std::string msg() const = 0;
		virtual char const * what() const throw() = 0;
};

class OverflowError: public AVM
{
	public:
		OverflowError();
		~OverflowError() throw();
		std::string	msg() const;
		char const * what() const throw();
};

class ZeroError: public AVM
{
	public:
		ZeroError();
		~ZeroError() throw();
		std::string	msg() const;
		char const * what() const throw();
};

class EmptyError: public AVM
{
	public:
		EmptyError();
		~EmptyError() throw();
		std::string	msg() const;
		char const * what() const throw();
};

class AssertError: public AVM
{
	public:
		AssertError();
		~AssertError() throw();
		std::string	msg() const;
		char const * what() const throw();
};

class TwovaluesError: public AVM
{
	public:
		TwovaluesError();
		~TwovaluesError() throw();
		std::string	msg() const;
		char const * what() const throw();
};

class LexicalError: public AVM
{
	public:
		LexicalError();
		~LexicalError() throw();
		std::string	msg() const;
		char const * what() const throw();
};

class UnknownError: public AVM
{
	public:
		UnknownError();
		~UnknownError() throw();
		std::string	msg() const;
		char const * what() const throw();
};

class ExitError: public AVM
{
	public:
		ExitError();
		~ExitError() throw();
		std::string	msg() const;
		char const * what() const throw();
};



#endif
