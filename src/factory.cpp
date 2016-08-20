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
		case INT8 : return createInt8(value);
		case INT16 : return createInt16(value);
		case INT32 : return createInt32(value);
		case FLOAT : return createFloat(value);
		case DOUBLE : return createDouble(value);
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
