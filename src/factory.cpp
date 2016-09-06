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
#include "error.hpp"
#include "NumClass.hpp"

IOperand const * Factory::createOperand( eOperandType type, std::string const & value )
{
	switch(type) {
		case eOperandType::e_int8 : return createInt8(value);
		case eOperandType::e_int16 : return createInt16(value);
		case eOperandType::e_int32 : return createInt32(value);
		case eOperandType::e_float : return createFloat(value);
		case eOperandType::e_double : return createDouble(value);
		case eOperandType::e_invalid : return NULL;
	}
	return NULL;
}

IOperand const * Factory::createInt8( std::string const & value )
{
	int			val = std::stoi(value);
	if (val <= -128 || val >= 127) throw OverflowError(); 
	return (new Num<int8_t>(val,eOperandType::e_int8));
}

IOperand const * Factory::createInt16( std::string const & value )
{
	short int	val = std::stoi(value);
	if (val <= std::numeric_limits<short int>::min() || val >= std::numeric_limits<short int>::max()) throw OverflowError(); 
	return (new Num<int16_t>(val,eOperandType::e_int16));
}

IOperand const * Factory::createInt32( std::string const & value )
{
	int32_t		val = std::stoi(value);
	return (new Num<int32_t>(val,eOperandType::e_int32));
}

IOperand const * Factory::createFloat( std::string const & value )
{
	float		val = std::stof(value);
	if (val <= std::numeric_limits<float>::min() || val >= std::numeric_limits<float>::max()) throw OverflowError(); 
	return (new Num<int8_t>(val,eOperandType::e_float));
}

IOperand const * Factory::createDouble( std::string const & value )
{
	double		val = std::stod(value);
	if (val <= std::numeric_limits<double>::min() || val >= std::numeric_limits<double>::max()) throw OverflowError(); 
	return (new Num<int8_t>(val,eOperandType::e_double));
}
