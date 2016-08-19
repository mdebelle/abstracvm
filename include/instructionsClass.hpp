/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructionsClass.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdebelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 04:30:28 by mdebelle          #+#    #+#             */
/*   Updated: 2016/08/19 04:30:30 by mdebelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

class instructions {

	private :
		std::string		_line;
		int				_number;
		bool			_valid;
		bool			_exit;
		std::string		_error;
		std::string		_type;

		void			defineInstruction();
		bool			checkComment(std::string comp, std::string str, void (*f)(std::string));
		bool			checkSimpleAction(std::string action, std::string str);
		int				checkActionValue(std::string comp, std::string str);
		std::string		splitcomment(std::string sep, std::string str);
		int				actionPush(std::string val);
		int				actionAssert(std::string val);

	public:
		instructions(std::string line, int number);
		~instructions();
		
		bool			exitLoop(bool exit);

		std::string		getLine(void) const;
		int				getNumber(void) const;
		bool			getValid(void) const;
		bool			getExit(void) const;
		std::string		getError(void) const;
		std::string		getType(void) const;
};
