/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdebelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/20 04:01:09 by mdebelle          #+#    #+#             */
/*   Updated: 2016/08/20 04:01:11 by mdebelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "factory.hpp"

factory::factory()
{
	v_factory.pushback()	

}

factory::~factory()
{

}

IOperand const * factory::createOperand( eOperandType type, std::string const & value ) const
{
	switch(type) {
		case eOperandType::e_int8 : return createInt8(value);
		case eOperandType::e_int16 : return createInt16(value);
		case eOperandType::e_int32 : return createInt32(value);
		case eOperandType::e_float : return createFloat(value);
		case eOperandType::e_double : return createDouble(value);
	}
	return NULL;
}

IOperand const * factory::createInt8( std::string const & value ) const
{
	return NULL;
}

IOperand const * factory::createInt16( std::string const & value ) const
{
	return NULL;
}

IOperand const * factory::createInt32( std::string const & value ) const
{
	return NULL;
}

IOperand const * factory::createFloat( std::string const & value ) const
{
	return NULL;
}

IOperand const * factory::createDouble( std::string const & value ) const
{
	return NULL;
}
