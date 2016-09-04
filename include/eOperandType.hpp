/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eOperandType.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdebelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/20 05:51:36 by mdebelle          #+#    #+#             */
/*   Updated: 2016/08/20 05:51:38 by mdebelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EOPERANDTYPE_HPP
# define EOPERANDTYPE_HPP

enum class eOperandType
{
	e_int8 = 0,
	e_int16 = 1,
	e_int32 = 2,
	e_float = 3,
	e_double = 4,
	e_invalid = 5
};

#endif