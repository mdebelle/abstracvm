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
	ss << "Error : Underflow/Overflow on a value";
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
	ss << "Error : Underflow/Overflow on a value";
	return ss.str();
}
