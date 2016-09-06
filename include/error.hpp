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

#endif
