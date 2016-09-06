/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdebelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 04:30:19 by mdebelle          #+#    #+#             */
/*   Updated: 2016/08/19 04:30:21 by mdebelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_HPP
# define IOPERAND_HPP

#include <iostream>
#include "eOperandType.hpp"

class IOperand
{
	public:
		virtual int					getPrecision( void ) const = 0; // Precision of the type of the instance
		virtual eOperandType		getType( void ) const = 0; // Type of the instance
		virtual IOperand const *	operator+( IOperand const & rhs ) const = 0; // Add
		virtual IOperand const *	operator-( IOperand const & rhs ) const = 0; // Sub
		virtual IOperand const *	operator*( IOperand const & rhs ) const = 0; // Mul
		virtual IOperand const *	operator/( IOperand const & rhs ) const = 0; // Div
		virtual IOperand const *	operator%( IOperand const & rhs ) const = 0; // Mod
		virtual std::string const &	toString( void ) const = 0; // String representation of the instance
		virtual	~IOperand( void ) {}
};

#endif