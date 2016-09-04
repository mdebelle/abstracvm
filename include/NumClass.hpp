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
#include "eOperandType.hpp"

class Num {

	private:
		int				_iNum;
		float			_fNum;
		double			_dNum;
		std::string		_str;
		eOperandType	_type;

	public:
		Num(int iNum, float _fNum, double _dNum, eOperandType type);
		Num(std::string str, eOperandType type);
		~Num(void);

		int				getiNum(void) const;
		float			getfNum(void) const;
		double			getdNum(void) const;
		std::string		getStr(void) const;
		eOperandType	gettype(void) const;
};

#endif
