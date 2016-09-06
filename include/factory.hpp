/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdebelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/20 04:00:35 by mdebelle          #+#    #+#             */
/*   Updated: 2016/08/20 04:00:37 by mdebelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACTORY_HPP
# define FACTORY_HPP

#include "IOperand.hpp"

class Factory
{
	private:
		static IOperand const * createInt8( std::string const & value );
		static IOperand const * createInt16( std::string const & value );
		static IOperand const * createInt32( std::string const & value );
		static IOperand const * createFloat( std::string const & value );
		static IOperand const * createDouble( std::string const & value );

	public:
		Factory();
		~Factory();
		static IOperand const * createOperand( eOperandType type, std::string const & value );

};

#endif
