/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumClass.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdebelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/04 13:46:42 by mdebelle          #+#    #+#             */
/*   Updated: 2016/09/04 13:46:44 by mdebelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUM_HPP
# define NUM_HPP

#include <iostream>
#include "IOperand.hpp"
#include "factory.hpp"
#include "eOperandType.hpp"
#include "error.hpp"

template <typename T>
class Num : public IOperand {

	private:
		T						_value;
		eOperandType			_type;
		std::string				_str;

	public:
		Num();
		Num(T value, eOperandType type);
		Num(Num const &);
		virtual ~Num(void);

		int						getPrecision( void ) const ;
		eOperandType			getType( void ) const;
		T						getValue( void ) const;

		IOperand const *		operator+( IOperand const & rhs ) const;
		IOperand const *		operator-( IOperand const & rhs ) const;
		IOperand const *		operator*( IOperand const & rhs ) const;
		IOperand const *		operator/( IOperand const & rhs ) const;
		IOperand const *		operator%( IOperand const & rhs ) const;
		bool					operator==( IOperand const & rhs ) const;
		std::string const &		toString( void ) const;
};

template <typename T>
Num<T>::Num() : _value(0), _type(eOperandType::e_int32), _str("0")
{
	return ;
}

template <typename T>
Num<T>::Num(T value, eOperandType type) : _value(value), _type(type), _str(std::to_string(value))
{
	if (_type == eOperandType::e_int8 &&
		(_value <= -128 || _value >= 127)){
			throw OverflowError();
	}
	if (_type == eOperandType::e_int16 &&
		(_value <= std::numeric_limits<short int>::min() || _value >= std::numeric_limits<short int>::max())) {
			throw OverflowError();
		}
}

template <typename T>
Num<T>::Num(Num const &l)
{
	*this = l;
}

template <typename T>
Num<T>::~Num(void)
{
	return;
}

template <typename T>
int					Num<T>::getPrecision( void ) const {
	return static_cast<int>(this->_type);
}

template <typename T>
eOperandType		Num<T>::getType( void ) const {
	return this->_type;
}

template <typename T>
T					Num<T>::getValue(void) const {
	return this->_value;
}

template <typename T>
IOperand const *	Num<T>::operator+( IOperand const & rhs ) const
{
	Factory f;
	eOperandType newType = (this->_type > rhs.getType()) ? this->_type : rhs.getType();
	double val = std::stod(rhs.toString());
	return (f.createOperand(newType, std::to_string(this->_value + val)));
}

template <typename T>
IOperand const *	Num<T>::operator-( IOperand const & rhs ) const
{
	Factory f;
	eOperandType newType = (this->_type > rhs.getType()) ? this->_type : rhs.getType();
	double val = std::stod(rhs.toString());
	return (f.createOperand(newType, std::to_string(this->_value - val)));
}

template <typename T>
IOperand const *	Num<T>::operator*( IOperand const & rhs ) const
{
	Factory f;
	eOperandType newType = (this->_type > rhs.getType()) ? this->_type : rhs.getType();
	double val = std::stod(rhs.toString());
	return (f.createOperand(newType, std::to_string(this->_value * val)));
}

template <typename T>
IOperand const *	Num<T>::operator/( IOperand const & rhs ) const
{
	Factory f;
	eOperandType newType = (this->_type > rhs.getType()) ? this->_type : rhs.getType();
	double val = std::stod(rhs.toString());
	if (val == 0) throw ZeroError();
	return (f.createOperand(newType, std::to_string(this->_value / val)));
}

template <typename T>
IOperand const *	Num<T>::operator%( IOperand const & rhs ) const
{
	Factory f;
	eOperandType newType = (this->_type > rhs.getType()) ? this->_type : rhs.getType();
	newType = (newType > eOperandType::e_int32) ? eOperandType::e_int32 : newType;
	int	valint = static_cast<int>(this->_value);
	int val = std::stoi(rhs.toString());
	if (val == 0) throw ZeroError();
	return (f.createOperand(newType, std::to_string(valint % val)));
}

template <typename T>
std::string const &		Num<T>::toString( void ) const
{
	return this->_str;
}

#endif
